/*
 * CaptureFactory.h
 *
 *  Created on: 11 févr. 2012
 *	  Author: davidroussel
 */

#ifndef CAPTUREFACTORY_H_
#define CAPTUREFACTORY_H_

#include <QString>
#include <QStringList>
#include <QThread>
#include "QcvVideoCapture.h"

/**
 * Capture Factory creates QcvVideoCapture from arguments list
 */
class CaptureFactory
{
	private:
		/**
		 * The capture instance to create
		 */
		QcvVideoCapture *capture;

		/**
		 * Device number to open. Generally :
		 * 	- 0 is internal or fisrt camera
		 * 	- 1 is external or second camera
		 */
		int deviceNumber;

		/**
		 * Indicates capture opens camera or file.
		 * Default value is true
		 */
		bool liveVideo;

		/**
		 * Video should be flipped horizontally for mirror effect
		 * Default value is false
		 */
		bool flippedVideo;

		/**
		 * Video should be converted to gray during capture.
		 * Default value is false
		 */
		bool grayVideo;

		/**
		 * Capture can skip capturing new image when previous image has not
		 * been processed yet, or can wait for the previous image to be
		 * processed before grabbing a new image.
		 */
		bool skipImages;

		/**
		 * Video preferred width (evt resize video)
		 * Default value is 0 which means no preferred width
		 */
		int preferredWidth;

		/**
		 * Video preferred height (evt resize video)
		 * Default value is 0 which means no preferred height
		 */
		int preferredHeight;

		/**
		 * Path to video file
		 */
		QString videoPath;

	public:
		/**
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
		CaptureFactory(const QStringList & argList);

		/**
		 * Capture factory destructor
		 */
		virtual ~CaptureFactory();

		/**
		 * Set the capture to live (webcam) or file source
		 * @param live the video source
		 */
		void setLiveVideo(const bool live);

		/**
		 * Set device number to use when instanciating the capture with
		 * live video.
		 * @param deviceNumber the device number to use
		 */
		void setDeviceNumber(const int deviceNumber);

		/**
		 * Set path to video file when #liveVideo is false
		 * @param path the path to the video file source
		 */
		void setFile(const QString & path);

		/**
		 * Set video horizontal flip state (useful for selfies)
		 * @param flipped the horizontal flip state
		 */
		void setFlipped(const bool flipped);

		/**
		 * Set gray conversion
		 * @param gray the gray conversion state
		 */
		void setGray(const bool gray);

		/**
		 * Set video grabbing skippable. When true, grabbing is skipped when
		 * previously grabbed image has not been processed yet. Otherwise,
		 * grabbing new image wait for the previous image to be processed.
		 * This only applies if capture is run in a separate thread.
		 * @param skip the video grabbing skippable state
		 */
		void setSkippable(const bool skip);

		/**
		 * Set video size (independently of video source actual size)
		 * @param width the desired image width
		 * @param height the desired image height
		 */
		void setSize(const size_t width, const size_t height);

		/**
		 * Set video size (independently of video source actual size)
		 * @param size the desired video size
		 */
		void setSize(const QSize & size);

		/**
		 * Provide capture instanciated according to values
		 * extracted from argument lists
		 * @param updateThread the thread to run this capture or NULL if this
		 * capture run in the current thread
		 * @return the new capture instance
		 */
		QcvVideoCapture * getCaptureInstance(QThread * updatethread = NULL);
};

#endif /* CAPTUREFACTORY_H_ */
