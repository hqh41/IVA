#include <QApplication>
#include <QDir>
#include <libgen.h>		// for basename
#include <iostream>		// for cout
#include <fstream>		// for ifstream for reading algos parameters

using namespace std;

#include "QcvVideoCapture.h"
#include "CaptureFactory.h"
#include "QcvDMR.h"
#include "mainwindow.h"

/**
 * @mainpage Qt/OpenCV Process example.
 *
 * @section Usage
 * @par usage : <Progname> [--device | -d] <#> | [--file | -f ] \<filename\>
 * [--mirror | -m] [--size | -s] \<width\>x\<height\>
 * 	- device : [--device | -d] <device #> (0, 1, ...) Opens capture device #
 * 	- filename : [--file | -f ] \<filename\> Opens a video file or URL (including rtsp)
 * 	- mirror : mirrors image horizontally before display
 *	- render : use Qimage and Qlabel or QGLWidget for image rendering in QtWidget
 *		[-r | --render] [IM | LBL | GL]
 *		- IM for image rendering with painter
 *		- LBL for image in Label rendering
 *		- GL for OpenGL rendering
 *	- size : [--size | -s] \<width\>x\<height\> resize capture to fit desired \<width\>
 *	and \<height\>
 *
 * @section Manual
 */

/**
 * Usage function shown just before launching QApp
 * @param name the name of the program (argv[0])
 */
void usage(char * name);

/**
 * Setup the correct working directory in order to locate resources and files
 * in subdirectories such as sounds (located in sound/...)
 *	- if system is windows and programm have been generated in a debug
 *		or relase subdirectory, then move up one time
 *	- if system is macOS the real executable is located in
 *		CookingClock.app/Contents/MacOS/ subdirectory, so move up 3 times to get
 *		to the right working directory
 */
void setWorkingDirectory();

/**
 * Test program OpenCV2 + QT5
 * @param argc argument count
 * @param argv argument values
 * @return QTApp return value
 * @par usage : \<Progname\> [--device | -d] \<#\> | [--file | -f ] \<filename\>
 * [--mirror | -m] [--size | -s] \<width\>x\<height\>
 * 	- device : [--device | -d] \<device #\> (0, 1, ...) Opens capture device #
 * 	- filename : [--file | -f ] \<filename\> Opens a video file or URL (including rtsp)
 * 	- mirror : mirrors image horizontally before display
 *	- render : use Qimage and Qlabel or QGLWidget for image rendering in QtWidget
 *		[-r | --render] [IM | LBL | GL]
 *		- IM for image rendering with painter
 *		- LBL for image in Label rendering
 *		- GL for OpenGL rendering
 *	- size : [--size | -s] \<width\>x\<height\> resize capture to fit desired \<width\>
 *	and \<height\>
 */
int main(int argc, char *argv[])
{
	// ------------------------------------------------------------------------
	// Default values for Detector/Matcher/Registrar
	// ------------------------------------------------------------------------
	CvDetector::FeatureType featureType = CvDetector::ORB_FEATURE;
	CvDetector::DescriptorExtractorType descriptorExtractorType = CvDetector::ORB_DESCRIPTOR;
	CvMatcher::MatcherType matcherType = CvMatcher::BRUTEFORCE_MATCHER;
	CvMatcher::MatchType matchType = CvMatcher::SIMPLE_MATCH;

//	string cameraFilename = "cameras/EyeSight_param.yaml";
	string cameraFilename = "cameras/Logitech_640x480.yaml";

	double reprojectionError = 5.0;

	CvProcessor::VerboseLevel verboseLevel = CvProcessor::VERBOSE_WARNINGS; // verbose up to warnings

	// Lena model
	string modelFilename = "images/LenaColor512.jpg";
	double printSize = 178.1;

	// All detectors/extractors algorithms parameters
	string algoParamsFilename("Algorithms_params.csv");

	// ------------------------------------------------------------------------
	// Instanciate QApplication to receive special QT args
	// ------------------------------------------------------------------------
	QApplication app(argc, argv);

	// Gets arguments after QT specials removed
	QStringList argList = QCoreApplication::arguments();

	// ------------------------------------------------------------------------
	// Others arguments parsing
	// ------------------------------------------------------------------------
	int threadNumber = 3;
	for (QListIterator<QString> it(argList); it.hasNext(); )
	{
		QString currentArg(it.next());

		if (currentArg == "--model")
		{
			// Next argument should be a model filename
			if (it.hasNext())
			{
				modelFilename = (it.next()).toStdString();
			}
			else
			{
				qWarning("Warning: model tag found with no following filename");
			}
		}
		else if (currentArg == "--camera")
		{
			// Next argument should be a camera calibration file
			if (it.hasNext())
			{
				cameraFilename = (it.next()).toStdString();
			}
			else
			{
				qWarning("Warning: camera tag found with no following filename");
			}
		}
		else if (currentArg == "--print")
		{
			// next argument should be a model print size in mm
			if (it.hasNext())
			{
				QString printSizeString(it.next());
				bool convertOk;
				double newPrintSize = printSizeString.toDouble(&convertOk);
				if (!convertOk || newPrintSize <= 0)
				{
					qWarning("Invalid printSize %f", newPrintSize);
				}
				else
				{
					printSize = newPrintSize;
				}
			}
			else
			{
				qWarning("Warning: print tag found with no following print size in mm");
			}
		}
		else if (currentArg == "--verbose")
		{
			// next argument should be a verbose level (from 0 to 4)
			if (it.hasNext())
			{
				QString verboseLevelString(it.next());
				bool convertOk;
				int newVerboseLevel = verboseLevelString.toUInt(&convertOk, 10);
				if (!convertOk ||
					newVerboseLevel < 0 ||
					newVerboseLevel > (int)CvProcessor::NBVERBOSELEVEL)
				{
					qWarning("Invalid verbose level %d", newVerboseLevel);
				}
				else
				{
					verboseLevel = (CvProcessor::VerboseLevel)newVerboseLevel;
				}
			}
			else
			{
				qWarning("Warning: print tag found with no following print size in mm");
			}
		}
		else if (currentArg == "--feature")
		{
			// next argument should be a feature point name
			if (it.hasNext())
			{
				QString featureName(it.next().toUpper());
				for (size_t f = 0; f < CvDetector::FEATURE_NUMBER; f++)
				{
					if (featureName.toStdString() == CvDetector::FeatureNames[f])
					{
						featureType = (CvDetector::FeatureType)f;
						break;
					}
				}
			}
			else
			{
				qWarning("Warning: feature tag found with no following feature type");
			}
		}
		else if (currentArg == "--descriptor")
		{
			// next argument should be a descriptor name to compute on points
			if (it.hasNext())
			{
				QString descriptorName(it.next().toUpper());
				for (size_t d = 0; d < CvDetector::DESCRIPTOR_NUMBER; d++)
				{
					if (descriptorName.toStdString() == CvDetector::DescriptorNames[d])
					{
						descriptorExtractorType = (CvDetector::DescriptorExtractorType)d;
						break;
					}
				}
			}
			else
			{
				qWarning("Warning: descriptor tag found with no following descriptor type");
			}
		}
		else if (currentArg == "--matcher")
		{
			// next argument should be  a matcher name
			if (it.hasNext())
			{
				QString matcherName(it.next().toUpper());

				if (matcherName.startsWith("BRUTE"))
				{
					if (matcherName.endsWith("MATCHER"))
					{
						matcherType = CvMatcher::BRUTEFORCE_MATCHER;
					}
					else if (matcherName.endsWith("L1"))
					{
						matcherType = CvMatcher::BRUTEFORCE_L1;
					}
					else if (matcherName.contains("HAMMING"))
					{
						if (matcherName.endsWith("LUT"))
						{
							matcherType = CvMatcher::BRUTEFORCE_HAMMINGLUT;
						}
						else
						{
							matcherType = CvMatcher::BRUTEFORCE_HAMMING;
						}
					}
				}
				else if (matcherName.startsWith("FLANN"))
				{
					matcherType = CvMatcher::FLANNBASED_MATCHER;
				}
			}
			else
			{
				qWarning("Warning: matcher tag found with no following matcher type");
			}
		}
		else if (currentArg == "--algoparams")
		{
			if (it.hasNext())
			{
				QString algoParamsFile(it.next());
				algoParamsFilename = algoParamsFile.toStdString();
			}
			else
			{
				qWarning("Warning: algorithm parameters tag found with no following file name");
			}
		}
		else if (currentArg == "-t" || currentArg =="--threads")
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
	// Set correct working directory to find resources and files
	// ------------------------------------------------------------------------
	setWorkingDirectory();

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
	// Get algorithms parameters data base
	// ------------------------------------------------------------------------
	ifstream algoParamStream(algoParamsFilename.c_str());
	// New Algo paremeters sets with no lock (yet) and no parent
	QcvAlgoParamSets * paramSets = new QcvAlgoParamSets(algoParamStream);

	// ------------------------------------------------------------------------
	// Create processor
	// ------------------------------------------------------------------------

	qDebug("Instaciating DMR Processor with : -------------------------------");
	qDebug("Model filename = %s", modelFilename.c_str());
	qDebug("Camera parameters filename = %s", cameraFilename.c_str());
	qDebug("Feature type = %s", CvDetector::FeatureNames[featureType].c_str());
	qDebug("Descriptor type = %s", CvDetector::DescriptorNames[descriptorExtractorType].c_str());
	qDebug("Matcher Type = %s", CvMatcher::MatcherNames[matcherType].c_str());
	qDebug("Match Mode = %s", CvMatcher::MatchTypeNames[matchType].c_str());
	qDebug("Reprojection error = %f", reprojectionError);
	qDebug("Print Size = %f", printSize);
	qDebug("Verbose Level = %d", verboseLevel);
	qDebug("-----------------------------------------------------------------");

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
	QcvDMR * processor = NULL;
	if (procThread == NULL)
	{
		processor = new QcvDMR(capture->getImage(),
							   modelFilename,
							   cameraFilename,
							   featureType,
							   descriptorExtractorType,
							   matcherType,
							   matchType,
							   reprojectionError,
							   printSize,
							   paramSets,
							   verboseLevel);
	}
	else
	{
		if (procThread != capThread)
		{
			processor = new QcvDMR(capture->getImage(),
								   modelFilename,
								   cameraFilename,
								   featureType,
								   descriptorExtractorType,
								   matcherType,
								   matchType,
								   reprojectionError,
								   printSize,
								   paramSets,
								   verboseLevel,
								   capture->getMutex(),
								   procThread);
		}
		else // procThread == capThread ==> No interlock
		{
			processor = new QcvDMR(capture->getImage(),
								   modelFilename,
								   cameraFilename,
								   featureType,
								   descriptorExtractorType,
								   matcherType,
								   matchType,
								   reprojectionError,
								   printSize,
								   paramSets,
								   verboseLevel,
								   NULL,
								   procThread);
		}
	}

	// ------------------------------------------------------------------------
	// Connects capture to processor
	// ------------------------------------------------------------------------
	// Connects capture update to processor update
	QObject::connect(capture, SIGNAL(updated()),
					 processor, SLOT(update()),
					 ((threadNumber < 3) ? Qt::DirectConnection :
										   Qt::QueuedConnection));

	// connect capture changed image to processor set input
	QObject::connect(capture, SIGNAL(imageChanged(Mat*)),
					 processor, SLOT(setSourceImage(Mat*)),
					 ((threadNumber < 3) ? Qt::DirectConnection :
										   Qt::QueuedConnection));


	// connect capture restart to processor reset measured times
	QObject::connect(capture, SIGNAL(restarted()),
					 processor, SLOT(resetMeanProcessTime()),
					 ((threadNumber < 3) ? Qt::DirectConnection :
										   Qt::QueuedConnection));


	// ------------------------------------------------------------------------
	// Now that Capture & processor are on then
	// add our MainWindow as toplevel
	// and launches app
	// ------------------------------------------------------------------------
	MainWindow w(capture, processor);
	// w.setWindowState(Qt::WindowMaximized);
	w.show();

//	usage(argv[0]);

	int retVal = app.exec();

	// ------------------------------------------------------------------------
	// Cleanup & return
	// ------------------------------------------------------------------------
	delete capture;
	delete processor;

	bool sameThread = capThread == procThread;

	if (capThread != NULL)
	{
		delete capThread;
	}

	if (procThread != NULL && !sameThread)
	{
		delete procThread;
	}

	delete paramSets;

	return retVal;
}

/*
 * Usage function shown just before launching QApp
 * @param name the name of the program (argv[0])
 */
void usage(char * name)
{
	char *  shortname = basename(name);
	cout << " usage : " << shortname << endl
		 << "Options : "
		 << "\t[-d or --device <device number>] " << endl
		 << "\t[-v or --video <video filename>] " << endl
		 << "\t[-i or --image <image filename>] " << endl
		 << "\t[-r or --reduce <reduce factor>] " << endl
		 << "\t[--model <model image filename>] " << endl
		 << "\t[--print <model printed width>] "  << endl
		 << "\t[--feature <feature type = (FAST | STAR | SIFT | SURF | ORB| BRISK | MSER | GFTT | HARRIS)>] "  << endl
		 << "\t[--descriptor <descriptor type = (SIFT | SURF | ORB | BRISK | BRIEF)>] "  << endl
		 << "\t[--matcher <matcher type = (BRUTEFORCE_MATCHER | BRUTEFORCE_L1 | BRUTEFORCE_L1 | BRUTEFORCE_HAMMINGLUT | FLANNBASED_MATCHER)>] "  << endl
		 << "\t[--camera <camera calibration file (*.yaml)>] "  << endl
		 << "\t[--verbose <verbose level 0,...,4>] "  << endl
		 << "\t[--help : prints this help and quits] "  << endl
		 << "Keys : " << endl
		 << "\t g: toggles color/gray source image" << endl
		 << "\t r: toggle between image sizes" << endl
		 << "\t d: toggle feature points detection" << endl
		 << "\t m: toggle points matching between model and scene" << endl
		 << "\t t: cycles through matcher types" << endl
		 << "\t y: cycles through matching modes" << endl
		 << "\t h: toggles registration" << endl
		 << "\t p: cycles through keypoints modes (all, matched, inliers)" << endl
		 << "\t f: show/hides model frame in scene image" << endl
		 << "\t b: show/hides model box in scene image" << endl
		 << "\t v: cycles through verbose levels" << endl
		 << "\t ESCAPE | CTRL-Q quits" << endl;
}

/*
 * Setup the correct working directory in order to locate resources adn files
 * in subdirectories such as sounds (located in sound/...)
 *	- if system is windows and programm have been generated in a debug
 *		or relase subdirectory, then move up one time
 *	- if system is macOS the real executable is located in
 *		CookingClock.app/Contents/MacOS/ subdirectory, so move up 3 times to get
 *		to the right working directory
 */
void setWorkingDirectory()
{
	QDir dir(QCoreApplication::applicationDirPath());

	#if defined(Q_OS_WIN)
		if (dir.dirName().toLower() == "debug" ||
			dir.dirName().toLower() == "release")
		{
			dir.cdUp();
		}
	#elif defined(Q_OS_MAC)
		if (dir.dirName() == "MacOS")
		{
			dir.cdUp();
			dir.cdUp();
			dir.cdUp();
		}
	#endif

	QDir::setCurrent(dir.absolutePath());
}
