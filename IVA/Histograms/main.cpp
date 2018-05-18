#include <QApplication>
#include <QThread>
#include <QDebug>
#include <libgen.h>		// for basename
#include <iostream>		// for cout

#include "QcvVideoCapture.h"
#include "CaptureFactory.h"
#include "QcvHistograms.h"
#include "mainwindow.h"

/**
 * Usage function shown just before launching QApp
 * @param name the name of the program (argv[0])
 */
void usage(char * name);

/**
 * Test program OpenCV2 + QT5
 * @param argc argument count
 * @param argv argument values
 * @return QTApp return value
 * @par usage : <Progname> [--device | -d] <#> | [--file | -f ] <filename>
 * [--mirror | -m] [--gray | -g] [--size | -s] <width>x<height>
 * 	- device : [--device | -d] <device #> (0, 1, ...) Opens capture device #
 * 	- filename : [--file | -f ] <filename> Opens a video file or URL (including rtsp)
 * 	- mirror : mirrors image horizontally before display
 * 	- gray : turns on source image gray conversion
 *	- size : [--size | -s] <width>x<height> resize capture to fit desired <width>
 *	and <height>
 */
int main(int argc, char *argv[])
{
	// ------------------------------------------------------------------------
	// Meta types registration for using these types in queued signal / slots
	// ------------------------------------------------------------------------
	qRegisterMetaType<CvProcessor::ProcessTime>("CvProcessor::ProcessTime");

	// ------------------------------------------------------------------------
	// Instanciate QApplication to receive special QT args
	// ------------------------------------------------------------------------
	QApplication app(argc, argv);

	// Gets arguments after QT specials removed
	QStringList argList = QCoreApplication::arguments();

	int threadNumber = 3;
	// parse arguments for --threads tag
	for (QListIterator<QString> it(argList); it.hasNext(); )
	{
		QString currentArg(it.next());

		if (currentArg == "-t" || currentArg =="--threads")
		{
			// Next argument should be thread number integer
			if (it.hasNext())
			{
				QString threadString(it.next());
				bool convertOk;
				threadNumber = threadString.toInt(&convertOk,10);
				if (!convertOk || threadNumber < 1 || threadNumber > 3)
				{
					qWarning("Warning: Invalid thread number %d",threadNumber);
					threadNumber = 3;
				}
			}
			else
			{
				qWarning("Warning: thread tag found with no following thread number");
			}
		}
	}
	// ------------------------------------------------------------------------
	// Create Capture factory using program arguments and
	// open Video Capture
	// ------------------------------------------------------------------------
	CaptureFactory factory(argList);
	factory.setSkippable(true);

	// Helper thread for capture
	QThread * capThread = NULL;
	if (threadNumber > 1)
	{
		capThread = new QThread();
	}

	// Capture
	QcvVideoCapture * capture = factory.getCaptureInstance(capThread);

	// ------------------------------------------------------------------------
	// Create QHistandLUT
	// ------------------------------------------------------------------------
	// Helper thread for processor
	QThread * procThread = NULL;
	if (threadNumber > 2)
	{
		procThread = new QThread();
	}
	else
	{
		if (threadNumber > 1)
		{
			procThread = capThread;
		}
	}

	// Processsor
	QcvHistograms * histograms = NULL;
	if (procThread == NULL)
	{
		histograms = new QcvHistograms(capture->getImage());
	}
	else
	{
		if (procThread != capThread)
		{
			histograms = new QcvHistograms(capture->getImage(),
										   capture->getMutex(),
										   procThread);
		}
		else // procThread == capThread
		{
			histograms = new QcvHistograms(capture->getImage(),
										   NULL,
										   procThread);
		}
	}

	// ------------------------------------------------------------------------
	// Connects capture to Histograms
	// ------------------------------------------------------------------------
	// Connects capture update to QHistandLUT update
	QObject::connect(capture, SIGNAL(updated()),
					 histograms, SLOT(update()),
					 ((threadNumber < 3) ? Qt::DirectConnection :
										   Qt::QueuedConnection));

	// connect capture changed image to QHistandLUT set input
	QObject::connect(capture, SIGNAL(imageChanged(Mat*)),
					 histograms, SLOT(setSourceImage(Mat*)),
					 ((threadNumber < 3) ? Qt::DirectConnection :
										   Qt::QueuedConnection));
	// ------------------------------------------------------------------------
	// Now that Capture & QHistandLUT are on then
	// add our MainWindow as toplevel
	// and launches app
	// ------------------------------------------------------------------------
	MainWindow w(capture, histograms);
	w.show();

	usage(argv[0]);

	int retVal = app.exec();

	// ------------------------------------------------------------------------
	// Cleanup & return
	// ------------------------------------------------------------------------
	delete histograms;
	delete capture;
	qDebug() << "Processor and Capture deleted";
	bool sameThread = capThread == procThread;

	if (capThread != NULL)
	{
		delete capThread;
		qDebug() << "Capture Thread deleted";
	}

	if (procThread != NULL && !sameThread)
	{
		delete procThread;
		qDebug() << "Processor Thread deleted";
	}

	return retVal;
}

/*
 * Usage function shown just before launching QApp
 * @param name the name of the program (argv[0])
 */
void usage(char * name)
{
	cout << "usage  : " << basename(name) << " "
		 << "[-d | --device] <device number> "
		 << "[-v | --video] <video file> "
		 << "[-s | --size] <width>x<height> "
		 << "[-m | --mirror]"
		 << "[-t | --threads] <number of threads [1..3]>"
		 << endl;
}
