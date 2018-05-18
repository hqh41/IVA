/*
 * QcvVideoCapture.cpp
 *
 *  Created on: 29 janv. 2012
 *	  Author: davidroussel
 */

#include <QElapsedTimer>
#include <QDebug>

#include "QcvVideoCapture.h"

#include <opencv2/imgproc/imgproc.hpp>

/*
 * default time interval between refresh
 */
int QcvVideoCapture::defaultFrameDelay = 33;

/*
 * Number of frames to test frame rate
 */
size_t QcvVideoCapture::defaultFrameNumberTest = 5;

/*
 * Default message showing time (at least 2000 ms)
 */
int QcvVideoCapture::messageDelay = 5000;

/*
 * QcvVideoCapture constructor.
 * Opens the default camera (0)
 * @param flipVideo mirror image status
 * @param gray convert image to gray status
 * @param skip indicates capture can skip an image. When the capture
 * result has not been processed yet, or when false that capture should
 * wait for the result to be processed before grabbing a new image.
 * This only applies when #updateThread is not NULL.
 * @param width desired width or 0 to keep capture width
 * @param height desired height or 0 to keep capture height
 * otherwise capture is updated in the current thread.
 * @param updateThread the thread used to run this capture
 * @param parent the parent QObject
 */
QcvVideoCapture::QcvVideoCapture(const bool flipVideo,
								 const bool gray,
								 const bool skip,
								 const unsigned int width,
								 const unsigned int height,
								 QThread * updateThread,
								 QObject * parent) :
	QcvVideoCapture(0, flipVideo, gray, skip, width, height, updateThread,
					parent)
{
}

/*
 * QcvVideoCapture constructor with device Id
 * @param deviceId the id of the camera to open
 * @param flipVideo mirror image
 * @param gray convert image to gray
 * @param skip indicates capture can skip an image. When the capture
 * result has not been processed yet, or when false that capture should
 * wait for the result to be processed before grabbing a new image.
 * This only applies when #updateThread is not NULL.
 * @param width desired width or 0 to keep capture width
 * @param height desired height or 0 to keep capture height
 * @param updateThread the thread used to run this capture
 * @param parent the parent QObject
 */
QcvVideoCapture::QcvVideoCapture(const int deviceId,
								 const bool flipVideo,
								 const bool gray,
								 const bool skip,
								 const unsigned int width,
								 const unsigned int height,
								 QThread * updateThread,
								 QObject * parent) :
	QObject(parent),
	filename(),
	capture(deviceId),
	timer(new QTimer(updateThread == NULL ? this : NULL)),
	updateThread(updateThread),
	mutex(QMutex::NonRecursive),
	lockLevel(0),
	liveVideo(true),
	flipVideo(flipVideo),
	resize(false),
	directResize(false),
	gray(gray),
	skip(skip),
	size(0, 0),
	originalSize(0, 0),
	frameRate(0.0),
	statusMessage()
{
	if (updateThread != NULL)
	{
		moveToThread(this->updateThread);
		connect(this, SIGNAL(finished()), updateThread, SLOT(quit()),
				Qt::DirectConnection);
	}

	timer->setSingleShot(false);
	connect(timer, SIGNAL(timeout()), SLOT(update()));

	if (grabTest())
	{
		setSize(width, height);
		QString message("Camera ");
		message.append(QString::number(deviceId));
		message.append(" ");
		int delay = grabInterval(message);
		if (updateThread != NULL)
		{
			updateThread->start();
		}
		timer->start(delay);
		qDebug("timer started with %d ms delay", delay);
		emit timerChanged(delay);
	}
	else
	{
		qDebug() << "QcvVideoCapture::QcvVideoCapture(" << deviceId
				 << ") : grab test failed";
	}
}

/*
 * QcvVideoCapture constructor from file name
 * @param fileName video file to open
 * @param flipVideo mirror image
 * @param gray convert image to gray
 * @param skip indicates capture can skip an image. When the capture
 * result has not been processed yet, or when false that capture should
 * wait for the result to be processed before grabbing a new image.
 * This only applies when #updateThread is not NULL.
 * @param width desired width or 0 to keep capture width
 * @param height desired height or 0 to keep capture height
 * @param updateThread the thread used to run this capture
 * @param parent the parent QObject
 */
QcvVideoCapture::QcvVideoCapture(const QString & fileName,
								 const bool flipVideo,
								 const bool gray,
								 const bool skip,
								 const unsigned int width,
								 const unsigned int height,
								 QThread * updateThread,
								 QObject * parent) :
	QObject(parent),
	filename(fileName),
	capture(fileName.toStdString()),
	timer(new QTimer(updateThread == NULL ? this : NULL)),
	updateThread(updateThread),
	mutex(QMutex::NonRecursive),
	lockLevel(0),
	liveVideo(false),
	flipVideo(flipVideo),
	resize(false),
	directResize(false),
	gray(gray),
	skip(skip),
	size(0, 0),
	originalSize(0, 0),
	frameRate(0.0),
	statusMessage()
{
	if (updateThread != NULL)
	{
		moveToThread(this->updateThread);
		connect(this, SIGNAL(finished()), updateThread, SLOT(quit()),
				Qt::DirectConnection);
	}

	timer->setSingleShot(false);
	connect(timer, SIGNAL(timeout()), SLOT(update()));

	if (grabTest())
	{
		setSize(width, height);
		QString message("File ");
		message.append(fileName);
		message.append(" ");

		int delay = grabInterval(message);
		if (updateThread != NULL)
		{
			updateThread->start();
		}
		timer->start(delay);
		qDebug("timer started with %d ms delay", delay);
		emit timerChanged(delay);
	}
}

/*
 * QcvVideoCapture destructor.
 * releases video capture and image
 */
QcvVideoCapture::~QcvVideoCapture()
{
	// wait for the end of an update
	if (updateThread != NULL)
	{
		if (lockLevel == 0)
		{
			// qDebug() << "QcvVideoCapture::~QcvVideoCapture: lock in thread"
			// 		 << QThread::currentThread();
			mutex.lock();
		}
		lockLevel++;

		emit finished();
	}

	if (timer != NULL)
	{
		if (timer->isActive())
		{
			timer->stop();
			qDebug("timer stopped");
		}

		timer->disconnect(SIGNAL(timeout()), this, SLOT(update()));
	}

	if (updateThread != NULL)
	{
		lockLevel--;
		if (lockLevel == 0)
		{
			mutex.unlock();
		}

		// Wait until the updateThread receives the "finished" signal through
		// "quit" slot
		updateThread->wait();

		delete timer; // delete unparented timer
	}

	// relesase OpenCV ressources
	filename.clear();
	capture.release();
	imageDisplay.release();
	imageFlipped.release();
	imageResized.release();
	image.release();

//	qDebug() << "QcvVideoCapture destroyed";
}

/*
 * Open new device Id
 * @param deviceId device number to open
 * @param width desired width or 0 to keep capture width
 * @param height desired height or 0 to keep capture height
 * @return true if device has been opened and checked and timer launched
 */
bool QcvVideoCapture::open(const int deviceId,
						   const unsigned int width,
						   const unsigned int height)
{
	if (updateThread != NULL)
	{
		if (lockLevel == 0)
		{
			mutex.lock();
		}
		lockLevel++;
	}

	filename.clear();
	if (timer->isActive())
	{
		timer->stop();
		qDebug("timer stopped");
	}

	if (capture.isOpened())
	{
		capture.release();
	}

	if (!image.empty())
	{
		image.release();
	}

	capture.open(deviceId);

	bool grabbed = grabTest();

	if (grabbed)
	{
		setSize(width, height);

		statusMessage.clear();
		statusMessage.append("Camera ");
		statusMessage.append(QString::number(deviceId));
		statusMessage.append(" ");
		int delay = grabInterval(statusMessage);
		timer->start(delay);
		liveVideo = true;
		qDebug("timer started with %d ms delay", delay);
		emit timerChanged(delay);
		emit imageChanged(&imageDisplay);
	}
	if (updateThread != NULL)
	{
		lockLevel--;
		if (lockLevel == 0)
		{
			mutex.unlock();
		}
	}

	return grabbed;
}

/*
 * Open new video file
 * @param fileName video file to open
 * @param width desired width or 0 to keep capture width
 * @param height desired height or 0 to keep capture height
 * @return true if video has been opened and timer launched
 */
bool QcvVideoCapture::open(const QString & fileName,
						   const unsigned int width,
						   const unsigned int height)
{
	filename = fileName;

	if (timer->isActive())
	{
		timer->stop();
		qDebug("timer stopped");
	}

	if (updateThread != NULL)
	{
		if (lockLevel == 0)
		{
			mutex.lock();
		}
		lockLevel++;
	}

	if (capture.isOpened())
	{
		capture.release();
	}

	if (!image.empty())
	{
		image.release();
	}

	capture.open(fileName.toStdString());

	bool grabbed = grabTest();

	if (grabbed)
	{
		setSize(width, height);
		// qDebug() << "open setSize done";
		statusMessage.clear();
		statusMessage.append("file ");
		statusMessage.append(fileName);
		statusMessage.append(" opened");

		int delay = grabInterval(statusMessage);
		timer->start(delay);
		liveVideo = false;
		qDebug("timer started with %d ms delay", delay);
		emit timerChanged(delay);
		emit imageChanged(&imageDisplay);
	}

	if (updateThread != NULL)
	{
		lockLevel--;
		if(lockLevel == 0)
		{
			mutex.unlock();
		}
	}

	return grabbed;
}

/*
 * Size accessor
 * @return the image size
 */
const QSize & QcvVideoCapture::getSize() const
{
	return size;
}

/*
 * Sets #imageDisplay size according to preferred width and height
 * @param width desired width
 * @param height desired height
 * @pre a first image have been grabbed
 */
void QcvVideoCapture::setSize(const unsigned int width,
							  const unsigned int height)
{
	if ((updateThread != NULL))
	{
		if (lockLevel == 0)
		{
			mutex.lock();
		}
		lockLevel++;
	}

	unsigned int preferredWidth;
	unsigned int preferredHeight;

	// if not empty then release it
	if (!imageResized.empty())
	{
		imageResized.release();
	}

	if ((width == 0) && (height == 0)) // reset to original size
	{
		if (directResize) // direct set size to original size
		{
			setDirectSize((unsigned int)originalSize.width(),
						  (unsigned int)originalSize.height());
			// image is updated into setDirectSize
		}
		preferredWidth = image.cols;
		preferredHeight = image.rows;

		resize = false;
		imageResized = image;
	}
	else // width != 0 or height != 0
	{
		if ((width == (unsigned int)image.cols) &&
			(height == (unsigned int)image.rows)) // unchanged
		{
			preferredWidth = image.cols;
			preferredHeight = image.rows;
			imageResized = image;

			if (((int)preferredWidth == originalSize.width()) &&
				((int)preferredHeight == originalSize.height()))
			{
				resize = false;
			}
			else
			{
				resize = true;
			}
		}
		else // width or height have changed
		{
			/*
			 * Resize needed
			 */
			preferredWidth = width;
			preferredHeight = height;

			resize = true;

			if (directResize)
			{
				setDirectSize(preferredWidth, preferredHeight);
				imageResized = image;
			}
			else
			{
				imageResized = Mat(preferredHeight, preferredWidth, image.type());
			}
		}
	}

	if (updateThread != NULL)
	{
		lockLevel--;
		if (lockLevel == 0)
		{
			mutex.unlock();
		}
	}

	qDebug("QcvVideoCapture resize is %s [%s]",
		   (resize ? "ON" : "OFF"),
		   (directResize ? "direct" : "soft"));

	size.setWidth(preferredWidth);
	size.setHeight(preferredHeight);
	statusMessage.clear();
	statusMessage.sprintf("Size set to %dx%d", preferredWidth, preferredHeight);
	emit messageChanged(statusMessage, messageDelay);


	/*
	 * imageChanged signal is delayed until setGray is called into
	 * setFlipVideo
	 */
	// Refresh image chain
	setFlipVideo(flipVideo);
}

/*
 * Sets #imageDisplay size according to preferred width and height
 * @param size new desired size to set
 * @pre a first image have been grabbed
 */
void QcvVideoCapture::setSize(const QSize & size)
{
	setSize(size.width(), size.height());
}

/*
 * Sets video flipping
 * @param flipVideo flipped video or not
 */
void QcvVideoCapture::setFlipVideo(const bool flipVideo)
{
	bool previousFlip = this->flipVideo;
	this->flipVideo = flipVideo;

	if (updateThread != NULL)
	{
		if (lockLevel == 0)
		{
			mutex.lock();
		}
		lockLevel++;
	}

	if (!imageFlipped.empty())
	{
		imageFlipped.release();
	}

	if (flipVideo)
	{
		imageFlipped = Mat(imageResized.size(), imageResized.type());
	}
	else
	{
		imageFlipped = imageResized;
	}

	if (updateThread != NULL)
	{
		lockLevel--;
		if (lockLevel == 0)
		{
			mutex.unlock();
		}
	}

	if (previousFlip != flipVideo)
	{
		statusMessage.clear();
		statusMessage.sprintf("flip video is %s", (flipVideo ? "on" : "off"));
		emit messageChanged(statusMessage, messageDelay);
		emit imageChanged(&imageDisplay);
	}

	/*
	 * imageChanged signal is delayed until setGray is called
	 */
	// refresh image chain
	setGray(gray);
}

/*
 * Sets video conversion to gray
 * @param grayConversion the gray conversion status
 */
void QcvVideoCapture::setGray(const bool grayConversion)
{
	bool previousGray = gray;

	gray = grayConversion;

	if (updateThread != NULL)
	{
		if (lockLevel == 0)
		{
			mutex.lock();
		}
		lockLevel++;
	}

	if (!imageDisplay.empty())
	{
		imageDisplay.release();
	}

	if (gray)
	{
		imageDisplay = Mat(imageFlipped.size(), CV_8UC1);
	}
	else
	{
		imageDisplay = imageFlipped;
	}

	if (updateThread != NULL)
	{
		lockLevel--;
		if (lockLevel == 0)
		{
			mutex.unlock();
		}
	}

	if (previousGray != grayConversion)
	{
		statusMessage.clear();
		statusMessage.sprintf("gray video is %s", (gray ? "on" : "off"));
		emit messageChanged(statusMessage, messageDelay);
	}

	/*
	 * In any cases emit image changed since
	 * 	- setSize may have been called
	 * 	- setFlipVideo may have been called
	 */
	emit imageChanged(&imageDisplay);
}

/*
 * Gets resize state.
 * @return true if imageDisplay have been resized to preferred width and
 * height, false otherwise
 */
bool QcvVideoCapture::isResized() const
{
	return resize;
}

/*
 * Gets direct resize state.
 * @return true if image can be resized directly into capture.
 * @note direct resize capabilities are tested into #grabTest which is
 * called in all constructors. So #isDirectResizeable should not be
 * called before #grabTest
 */
bool QcvVideoCapture::isDirectResizeable() const
{
	return directResize;
}

/*
 * Gets video flipping status
 * @return flipped video status
 */
bool QcvVideoCapture::isFlipVideo() const
{
	return flipVideo;
}

/*
 * Gets video gray converted status
 * @return the converted to gray status
 */
bool QcvVideoCapture::isGray() const
{
	return gray;
}

/*
 * Gets the image skipping policy
 * @return true if new image can be skipped when previous one has not
 * been processed yet, false otherwise.
 */
bool QcvVideoCapture::isSkippable() const
{
	return skip;
}

/*
 * Gets the current frame rate
 * @return the current frame rate
 */
double QcvVideoCapture::getFrameRate() const
{
	return frameRate;
}

/*
 * Image accessor
 * @return the image
 */
Mat * QcvVideoCapture::getImage()
{
	return &imageDisplay;
}

/*
 * The source image mutex
 * @return  the mutex used on image access
 */
QMutex * QcvVideoCapture::getMutex()
{
	return &mutex;
}

/*
 * Performs a grab test to fill #image
 * @return true if capture is opened and successfully grabs a first
 * frame into #image, false otherwise
 */
bool QcvVideoCapture::grabTest()
{
//	qDebug("Grab test");
	bool result = false;

	if (capture.isOpened())
	{
#ifndef Q_OS_LINUX // V4L does not support these queries
		int capWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
		int capHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

		qDebug("Capture grab test with %d x %d image", capWidth, capHeight);
#endif
		// grabs first frame
		if (capture.grab())
		{
			bool retrieved = capture.retrieve(image);
			if (retrieved)
			{
				size.setWidth(image.cols);
				size.setHeight(image.rows);
				originalSize.setWidth(image.cols);
				originalSize.setHeight(image.rows);

				/*
				 * Tries to determine if direct resizing in capture is possible
				 * by setting original size through properties
				 * Typically :
				 * 	- camera capture might be resizable
				 * 	- video file capture may not be resizable
				 */
				directResize = setDirectSize(image.cols, image.rows);

				qDebug("Capture direct resizing is %s",
					   (directResize ? "on" : "off"));

				result = true;
			}
			else
			{
				qFatal("Video Capture unable to retreive image");
			}
		}
		else
		{
			qFatal("Video Capture can not grab");
		}
	}
	else
	{
		qFatal("Video Capture is not opened");
	}

	return result;
}

/*
 * Get or compute interval between two frames
 * @return interval between two frames
 * @pre capture is already instanciated
 */
int QcvVideoCapture::grabInterval(const QString & message)
{
	int frameDelay = defaultFrameDelay;

	// Tries to get framerate from capture
	// --------------------------------------------------------------------
	// Caution : on some systems getting video parameters is forbidden !
	// For instance it does not work with linuxes equipped with V4L
	// --------------------------------------------------------------------
#ifndef Q_OS_LINUX
	frameRate = capture.get(CV_CAP_PROP_FPS);
#else
	frameRate = -1.0;
#endif

	/*
	 * if capture obtained frameRate is inconsistent, then we'll try to find out
	 * by ourselves
	 */
	if (frameRate <= 0.0)
	{
		/*
		 * If live Video : grab a few images and measure elapsed time
		 */
		if (liveVideo)
		{
			QElapsedTimer localTimer;
			localTimer.start();

			for (size_t i=0; i < defaultFrameNumberTest; i++)
			{
				capture >> image;
			}

			frameDelay = (int)(localTimer.elapsed() / defaultFrameNumberTest);
			frameRate = 1.0/((double)frameDelay/1000.0);
			qDebug("Measured capture frame rate is  %4.2f images/s", frameRate);
		}
		/*
		 * FIXME else ???
		 * video files read through capture should provide framerate with
		 * capture.get(CV_CAP_PROP_FPS) but what happens if they don't ???
		 */
	}
	else
	{
		qDebug("%s Capture frame rate = %4.2f", message.toStdString().c_str(),
												frameRate);
		frameDelay = 1000/frameRate;
	}

	statusMessage.sprintf("%s frame rate = %4.2f images/s",
						   message.toStdString().c_str(), frameRate);
	emit messageChanged(statusMessage, messageDelay);

	return frameDelay;
}

/*
 * Tries to set capture size directly on capture by using properties.
 * 	- CV_CAP_PROP_FRAME_WIDTH to set frame width
 * 	- CV_CAP_PROP_FRAME_HEIGHT to set frame height
 * @param width the width property to set on capture
 * @param height the height property to set on capture
 * @return true if capture is opened and if width and height have been
 * set successfully through @code capture.set(...) @endcode. Returns
 * false otherwise.
 * @post if at least width or height have been set successfully, capture
 * image is released then updated again so it will have the right
 * dimensions.
 */
bool QcvVideoCapture::setDirectSize(const unsigned int width,
									const unsigned int height)
{
#ifdef Q_OS_LINUX
	Q_UNUSED(width);
	Q_UNUSED(height);
#endif
	bool done = false;

	/*
	 * We absolutely need this lock in order to safely set width and
	 * height directly into the capture, so if mutex is already locked
	 * we should wait for it to be unlocked before continuing. Moreover,
	 * if mutex is NON-recursive and already locked, the call to lock() could
	 * lead to a DEADlock, so mutex HAS to be recursive !
	 */

#ifndef Q_OS_LINUX
	if (capture.isOpened())
	{
		bool setWidth = capture.set(CV_CAP_PROP_FRAME_WIDTH, (double)width);
		bool setHeight = capture.set(CV_CAP_PROP_FRAME_HEIGHT, (double)height);
		if (setWidth || setHeight)
		{
			// release old capture image
			image.release();

			// force image update to get the right size
			capture >> image;

			done = true;
		}
	}
#endif

	return done;
}

/*
 * update slot trigerred by timer : Grabs a new image and sends updated()
 * signal iff new image has been grabbed, otherwise there is no more
 * images to grab so kills timer
 */
void QcvVideoCapture::update()
{
	bool locked = true;
	bool image_updated = false;

	if (updateThread != NULL)
	{
		if (skip)
		{
			locked = mutex.tryLock();
			if (locked)
			{
				lockLevel++;
			}
		}
		else
		{
			if (lockLevel == 0)
			{
				mutex.lock();
			}
			lockLevel++;
		}
	}

	if (capture.isOpened() && locked)
	{
		capture >> image;

		if (!image.data) // captured image has no data
		{
			statusMessage.clear();

			if (liveVideo)
			{
				if (timer->isActive())
				{
					timer->stop();
					qDebug("timer stopped");
				}

				capture.release();

				statusMessage.sprintf("No more frames to capture ...");
				emit messageChanged(statusMessage, 0);
				qDebug("%s", statusMessage.toStdString().c_str());
			}
			else // not live video ==> video file
			{
				// We'll try to rewind the file back to frame 0
				bool restart = capture.set(CV_CAP_PROP_POS_FRAMES, 0.0);

				if (restart)
				{
					statusMessage.sprintf("Capture restarted");
					emit messageChanged(statusMessage,
										QcvVideoCapture::messageDelay);
					emit restarted();
					qDebug("%s", statusMessage.toStdString().c_str());

					// Refresh image chain resized -> flipped -> gray
					setSize(size);
				}
				else
				{
					capture.release();

					statusMessage.sprintf("Failed to restart capture ...");
					emit messageChanged(statusMessage, 0);
					emit finished();
					qDebug("%s", statusMessage.toStdString().c_str());
				}
			}
		}
		else // capture image has data
		{
			/*
			 * CAUTION
			 * image->imageResized->imageFlipped->imageDisplay
			 * constitute an image chain, so when size is changed with
			 * setSize it should call setFlipVideo which should call
			 * setGray
			 */

			// resize image
			if (resize && !directResize)
			{
				cv::resize(image, imageResized, imageResized.size(), 0, 0,
					INTER_AREA);
			}
			/*
			 * else imageResized.data is already == image.data
			 */

			// flip image horizontally if required
			if (flipVideo)
			{
				flip(imageResized, imageFlipped, 1);
			}
			/*
			 * else imageFlipped.data is already == imageResized.data
			 */

			// convert image to gray if required
			if (gray)
			{
				cvtColor(imageFlipped, imageDisplay, CV_BGR2GRAY);
			}
			/*
			 * else imageDisplay.data is already == imageFlipped.data
			 */
			image_updated = true;
		}

		if (updateThread != NULL)
		{
			lockLevel--;
			if (lockLevel == 0)
			{
				mutex.unlock();
			}
		}

		if (image_updated)
		{
			emit updated();
		}
	}
	else
	{
		// mutex hasn't been locked, so we skipped one capture
		// qDebug() << "Capture skipped an image (level " << lockLevel << ")";
	}
}
