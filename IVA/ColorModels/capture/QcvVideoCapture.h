/*
 * QcvVideoCapture.h
 *
 *  Created on: 29 janv. 2012
 *	  Author: davidroussel
 */

#ifndef QCVVIDEOCAPTURE_H_
#define QCVVIDEOCAPTURE_H_

#include <QObject>
#include <QSize>
#include <QTimer>
#include <QThread>
#include <QMutex>

#include <opencv2/highgui/highgui.hpp>
using namespace cv;

/**
 * Qt Class for capturing videos from cameras of files with OpenCV.
 * QcvVideoCapture opens streams and refresh itself automatically.
 * When frame has been refreshed a signal is emitted.
 */
class QcvVideoCapture: public QObject
{
	Q_OBJECT

	private:

		/**
		 * file name used to open video file.
		 * Used to reopen video file when video is finished.
		 */
		QString filename;

		/**
		 * Video capture instance
		 * @warning capture is regularly updated by a timer, but can also be
		 * manipulated by other methods (such as #setDirectSize). So capture
		 * access for new images should be protected by a mutex to ensure
		 * atomic access to capture object at a time.
		 */
		VideoCapture capture;

		/**
		 * refresh timer
		 */
		QTimer * timer;

		/**
		 * Independant thread to update capture.
		 * If independant thread is required, then update method is called
		 * from within this thread. Otherwise, update method is called from
		 * main thread.
		 */
		QThread * updateThread;

		/**
		 * Mutex lock to ensure atomic access capture grabbing new image.
		 * @warning if QcvVideoCapture object is not updated in the
		 * #updateThread, then trying to lock mutex multiple times with
		 * mutex.lock() will lead to a deadlock, so if this object has no
		 * #updateThread (if #updateThread == NULL) we should use
		 * mutex.tryLock() instead and give up when lock can't be obtained with
		 * tryLock(). For instance when tryLock into #update method fails, this
		 * means that capture object is locked in some other method, so we don't
		 * grab any new image this time and hope, we'll be able to do it next
		 * time #update will be called.
		 */
		QMutex mutex;

		/**
		 * Mutex lock state memory to avoid locking the mutex multiple times
		 * across multiple methods. When a mutex.lock() is performed locked
		 * should be set to true until mutex.unlock(). Hence, if a method
		 * requiring lock is performed, a second lock is avoided by checking
		 * this attribute.
		 */
		size_t lockLevel;

		/**
		 * Image Matrix to obtain from capture
		 */
		Mat image;

		/**
		 * image resized (if required)
		 */
		Mat imageResized;

		/**
		 * [resized] image flipped (if required)
		 */
		Mat imageFlipped;

		/**
		 * Image converted for display:
		 * 	- scaled
		 * 	- flipped horizontally
		 * 	- converted to gray
		 */
		Mat imageDisplay;

		/**
		 * Live video indication (from cam)
		 */
		bool liveVideo;

		/**
		 * flipVideo to mirror image
		 */
		bool flipVideo;

		/**
		 * scale image to preferred width and height
		 */
		bool resize;

		/**
		 * scaling is performed into capture rather than through cv::resize
		 * function
		 */
		bool directResize;

		/**
		 * image converted to gray
		 */
		bool gray;

		/**
		 * Allow capture to skip an image capture when lock can't be acquired
		 * before grabbing a new image. Otherwise we'll wait until the lock
		 * is acquired before grabbing an new image. The lock might be acquired
		 * by another lenghty thread/processor during image processing.
		 */
		bool skip;

		/**
		 * Current Image size (might be different from natural capture image
		 * size)
		 */
		QSize size;

		/**
		 * Capture natural image size (without resizing)
		 */
		QSize originalSize;

		/**
		 * Capture frame rate obtained either by getting the CV_CAP_PROP_FPS
		 * VideoCapture property or by computing capture time on several images
		 * @see #grabInterval
		 */
		double frameRate;

		/**
		 * default time interval between refresh
		 */
		static int defaultFrameDelay;

		/**
		 * Number of frames to test frame rate
		 */
		static size_t defaultFrameNumberTest;

		/**
		 * Status message to send when something changes
		 */
		QString statusMessage;

		/**
		 * Default message showing time (at least 2000 ms)
		 */
		static int messageDelay;

	public:
		/**
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
		QcvVideoCapture(const bool flipVideo = false,
						const bool gray = false,
						const bool skip = true,
						const unsigned int  width = 0,
						const unsigned int height = 0,
						QThread * updateThread = NULL,
						QObject * parent = NULL);

		/**
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
		QcvVideoCapture(const int deviceId,
						const bool flipVideo = false,
						const bool gray = false,
						const bool skip = true,
						const unsigned int  width = 0,
						const unsigned int height = 0,
						QThread * updateThread = NULL,
						QObject * parent = NULL);

		/**
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
		QcvVideoCapture(const QString & fileName,
						const bool flipVideo = false,
						const bool gray = false,
						const bool skip = true,
						const unsigned int  width = 0,
						const unsigned int height = 0,
						QThread * updateThread = NULL,
						QObject * parent = NULL);

		/**
		 * QcvVideoCapture destructor.
		 * releases video capture and image
		 */
		virtual ~QcvVideoCapture();

		/**
		 * Size accessor
		 * @return the image size
		 */
		const QSize & getSize() const;

		/**
		 * Gets resize state.
		 * @return true if imageDisplay have been resized to preferred width and
		 * height, false otherwise
		 */
		bool isResized() const;

		/**
		 * Gets direct resize state.
		 * @return true if image can be resized directly into capture.
		 * @note direct resize capabilities are tested into #grabTest which is
		 * called in all constructors. So #isDirectResizeable should not be
		 * called before #grabTest
		 */
		bool isDirectResizeable() const;

		/**
		 * Gets video flipping status
		 * @return flipped video status
		 */
		bool isFlipVideo() const;

		/**
		 * Gets video gray converted status
		 * @return the converted to gray status
		 */
		bool isGray() const;

		/**
		 * Gets the image skipping policy
		 * @return true if new image can be skipped when previous one has not
		 * been processed yet, false otherwise.
		 */
		bool isSkippable() const;

		/**
		 * Gets the current frame rate
		 * @return the current frame rate
		 */
		double getFrameRate() const;

		/**
		 * Image accessor
		 * @return the image to display
		 */
		Mat * getImage();

		/**
		 * The source image mutex
		 * @return  the mutex used on image access
		 */
		QMutex * getMutex();

	public slots:
		/**
		 * Open new device Id
		 * @param deviceId device number to open
		 * @param width desired width or 0 to keep capture width
		 * @param height desired height or 0 to keep capture height
		 * @return true if device has been opened and checked and timer launched
		 */
		bool open(const int deviceId,
				  const unsigned int width = 0,
				  const unsigned int height = 0);

		/**
		 * Open new video file
		 * @param fileName video file to open
		 * @param width desired width or 0 to keep capture width
		 * @param height desired height or 0 to keep capture height
		 * @return true if video has been opened and timer launched
		 */
		bool open(const QString & fileName,
				  const unsigned int width = 0,
				  const unsigned int height = 0);
		/**
		 * Sets video flipping
		 * @param flipVideo flipped video or not
		 */
		void setFlipVideo(const bool flipVideo);

		/**
		 * Sets video conversion to gray
		 * @param grayConversion the gray conversion status
		 */
		void setGray(const bool grayConversion);

		/**
		 * Sets #imageDisplay size according to preferred width and height
		 * @param size new desired size to set
		 * @param alreadyLocked mutex lock has already been aquired so setSize does not have
		 * to acquire the lock
		 * @pre a first image have been grabbed
		 */
		void setSize(const QSize & size);

	private:
		/**
		 * Performs a grab test to fill #image.
		 * if capture is opened then tries to grab and if grab succeeds then
		 * tries to retrieve image from grab and sets image size.
		 * @return true if capture is opened and successfully grabbed a first
		 * frame into #image, false otherwise
		 * @post Moreover this method determines if direct resizing is allowed
		 * on this capture instance by trying to set
		 * CV_CAP_PROP_FRAME_WIDTH and CV_CAP_PROP_FRAME_HEIGHT.
		 */
		bool grabTest();

		/**
		 * Get or compute interval between two frames in ms and sets the
		 * frameRate attribute.
		 * Tries to get CV_CAP_PROP_FPS from capture and if not available
		 * computes times between frames by grabbing defaultNumberTest images
		 * @return interval between two frames
		 * @param message message passed to grabInterval and display ahead of
		 * the framerate computed during grabInterval
		 * @pre capture is already instanciated
		 * @post message indicating frame rate has been emitted and interval
		 * between two frames has been returned
		 */
		int grabInterval(const QString & message);

		/**
		 * Sets #imageDisplay size according to preferred width and height
		 * @param width desired width
		 * @param height desired height
		 * @pre a first image have been grabbed
		 */
		void setSize(const unsigned int width,
					 const unsigned int height);

		/**
		 * Tries to set capture size directly on capture by setting properties.
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
		 * @warning if mutex lock can't be obtained to ensure atomic access to
		 * capture object, then we start recursing until we obtain that lock,
		 * which is gross and should be fixed !!!
		 */
		bool setDirectSize(const unsigned int width, const unsigned int height);

	protected slots:
		/**
		 * update slot trigerred by timer : Grabs a new image and sends updated()
		 * signal iff new image has been grabbed, otherwise there is no more
		 * images to grab so kills timer.
		 * @note If lock on OpenCV capture object can not be obtained then
		 * capture is skipped. This is not critical since update is called
		 * regularly by the #timer, so we'll try updating image next time.
		 */
		void update();

	signals:
		/**
		 * Signal emitted when a new image has been grabbed
		 */
		void updated();

		/**
		 * Signal emitted when capture is released
		 */
		void finished();

		/**
		 * Signal to send update message when something changes
		 * @param message the message
		 * @param timeout number of ms the message should be displayed
		 */
		void messageChanged(const QString & message, int timeout = 0);

		/**
		 * Signal to send when image has changed after opening new device or
		 * setting new display size
		 * @param image the new image to send
		 */
		void imageChanged(Mat * image);

		/**
		 * Signal emitted when timer is started whith a new delay
		 * @param delay the new timer delay value
		 */
		void timerChanged(const int delay);

		/**
		 * Signal to send when video capture is restarted (typically when
		 * playing video file and reaching the end of the file, the capture
		 * will try to go back to the beginning and play it again from start).
		 */
		void restarted();
};

#endif /* QCVVIDEOCAPTURE_H_ */

