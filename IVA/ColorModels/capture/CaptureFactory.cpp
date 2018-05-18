/*
 * CaptureFactory.cpp
 *
 *  Created on: 11 févr. 2012
 *	  Author: davidroussel
 */

#include <cstdlib>	// for NULL
#include <QDebug>
#include <QFile>
#include <QtGlobal>
#include <QStringListIterator>
#include "CaptureFactory.h"

/*
 * Capture Factory constructor.
 * Arguments can be
 * 	- [-d | --device] <device number> : camera number
 * 	- [-f | --file] <filename> : video file name
 * 	- [-m | --mirror] : flip image horizontally
 * 	- [-g | --gray] : convert to gray level
 * 	- [-s | --size] <width>x<height>: preferred width and height
 * @param argList program the argument list provided as a list of
 * strings
 */
CaptureFactory::CaptureFactory(const QStringList & argList) :
	capture(NULL),
	deviceNumber(0),
	liveVideo(true),
	flippedVideo(false),
	grayVideo(false),
	skipImages(false),
	preferredWidth(0),
	preferredHeight(0),
	videoPath()
{
	// C++ Like iterator
	// for (QStringList::const_iterator it = argList.begin(); it != argList.end(); ++it)
	// Java like iterator (because we use hasNext multiple times)
	for (QListIterator<QString> it(argList); it.hasNext(); )
	{
		QString currentArg(it.next());

		if (currentArg == "-d" || currentArg =="--device")
		{
			// Next argument should be device number integer
			if (it.hasNext())
			{
				QString deviceString(it.next());
				bool convertOk;
				deviceNumber = deviceString.toInt(&convertOk,10);
				if (!convertOk || deviceNumber < 0)
				{
					qWarning("Warning: Invalid device number %d",deviceNumber);
					deviceNumber = 0;
				}
				liveVideo = true;
			}
			else
			{
				qWarning("Warning: device tag found with no following device number");
			}
		}
		else if (currentArg == "-v" || currentArg == "--video")
		{
			// Next argument should be a path name to video file or URL
			if (it.hasNext())
			{
				videoPath = it.next();
				liveVideo = false;
			}
			else
			{
				qWarning("file tag found with no following filename");
			}
		}
		else if (currentArg == "-m" || currentArg == "--mirror")
		{
			flippedVideo = true;
		}
		else if (currentArg == "-g" || currentArg == "--gray")
		{
			grayVideo = true;
		}
		else if (currentArg == "-k" || currentArg == "--skip")
		{
			skipImages = true;
		}
		else if (currentArg == "-s" || currentArg == "--size")
		{
			if (it.hasNext())
			{
				// search for <width>x<height>
				QString sizeString = it.next();
				int xIndex = sizeString.indexOf(QChar('x'), 0,
					Qt::CaseInsensitive);
				if (xIndex != -1)
				{
					QString widthString = sizeString.left(xIndex);
					preferredWidth = widthString.toUInt();
					qDebug("preferred width is %d", preferredWidth);

					QString heightString = sizeString.remove(0, xIndex+1);
					preferredHeight = heightString.toUInt();
					qDebug("preferred height is %d", preferredHeight);
				}
				else
				{
					qWarning("invalid <width>x<height>");
				}
			}
			else
			{
				qWarning("size not found after --size");
			}
		}
	}
}

/*
 * Capture factory destructor
 */
CaptureFactory::~CaptureFactory()
{
}

/*
 * Set the capture to live (webcam) or file source
 * @param live the video source
 */
void CaptureFactory::setLiveVideo(const bool live)
{
	liveVideo = live;
}

/*
 * Set device number to use when instanciating the capture with
 * live video.
 * @param deviceNumber the device number to use
 */
void CaptureFactory::setDeviceNumber(const int deviceNumber)
{
	if (deviceNumber >= 0)
	{
		this->deviceNumber = deviceNumber;
	}
	else
	{
		qWarning("CaptureFactory::setDeviceNumber: invalid number %d", deviceNumber);
	}
}

/*
 * Set path to video file when #liveVideo is false
 * @param path the path to the video file source
 */
void CaptureFactory::setFile(const QString & path)
{
	if (QFile::exists(path))
	{
		videoPath = path;
	}
	else
	{
		qWarning() << QObject::tr("CaptureFactory::setFile: path") << path
				   << QObject::tr(" does not exist");
	}
}

/*
 * Set video horizontal flip state (useful for selfies)
 * @param flipped the horizontal flip state
 */
void CaptureFactory::setFlipped(const bool flipped)
{
	flippedVideo = flipped;
}

/*
 * Set gray conversion
 * @param gray the gray conversion state
 */
void CaptureFactory::setGray(const bool gray)
{
	grayVideo = gray;
}

/*
 * Set video grabbing skippable. When true, grabbing is skipped when
 * previously grabbed image has not been processed yet. Otherwise,
 * grabbing new image wait for the previous image to be processed.
 * This only applies if capture is run in a separate thread.
 * @param skip the video grabbing skippable state
 */
void CaptureFactory::setSkippable(const bool skip)
{
	skipImages = skip;
}

/*
 * Set video size (independently of video source actual size)
 * @param width the desired image width
 * @param height the desired image height
 */
void CaptureFactory::setSize(const size_t width, const size_t height)
{
	preferredWidth = (int)width;
	preferredHeight = (int)height;
}

/*
 * Set video size (independently of video source actual size)
 * @param size the desired video size
 */
void CaptureFactory::setSize(const QSize & size)
{
	preferredWidth = size.width();
	preferredHeight = size.height();
}

/*
 * Provide capture instanciated according to values
 * extracted from argument lists
 * @param updateThread the thread to run this capture or NULL if this
 * capture run in the current thread
 * @return the new capture instance
 */
QcvVideoCapture * CaptureFactory::getCaptureInstance(QThread * updateThread)
{
	// ------------------------------------------------------------------------
	// Opening Video Capture
	// ------------------------------------------------------------------------
	if (liveVideo)
	{
		qDebug() << "opening device # " << deviceNumber;
	}
	else
	{
		qDebug() << "opening video file " << videoPath;
	}

	qDebug() << "Opening ";
	if (liveVideo)
	{
		// Live video feed
		qDebug() << "Live Video ... from camera # " << deviceNumber;
		capture = new QcvVideoCapture(deviceNumber,
									  flippedVideo,
									  grayVideo,
									  skipImages,
									  preferredWidth,
									  preferredHeight,
									  updateThread);
	}
	else
	{
		// Video file or stream
		qDebug() << videoPath << " ... ";
		capture = new QcvVideoCapture(videoPath,
									  flippedVideo,
									  grayVideo,
									  skipImages,
									  preferredWidth,
									  preferredHeight,
									  updateThread);
	}

	return capture;
}