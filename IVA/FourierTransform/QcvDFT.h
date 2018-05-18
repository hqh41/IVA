/*
 * QcvDFT.h
 *
 *  Created on: 22 févr. 2012
 *      Author: davidroussel
 */

#ifndef QCVDFT_H_
#define QCVDFT_H_

#include <QMutex>

#include "QcvProcessor.h"
#include "CvDFT.h"

class QcvDFT: public QcvProcessor, public CvDFT
{
	Q_OBJECT

	protected:
		/**
		 * Self lock for operation from multiple threads
		 * @note May be NULL if there is no update thread
		 */
		QMutex * selfLock;
	public:

		/**
		 * QcvDFT constructor
		 * @param image the source image
		 * @param imageLock the mutex for concurrent access to the source image.
		 * In order to avoid concurrent access to the same image
		 * @param updateThread the thread in which this processor should run
		 * @param parent parent QObject
		 */
		QcvDFT(Mat * image,
			   QMutex * imageLock = NULL,
			   QThread * updateThread = NULL,
			   QObject * parent = NULL);

		/**
		 * QcvDFT destructor
		 */
		virtual ~QcvDFT();

	public slots:
		/**
		 * Update computed images slot and sends updated signal
		 * required
		 */
		void update();

		// --------------------------------------------------------------------
		// Options settings with message notification
		// --------------------------------------------------------------------
		/**
		 * Changes source image slot.
		 * Attributes needs to be cleaned up then set up again
		 * @param image the new source Image
		 */
		void setSourceImage(Mat * image)
			throw (CvProcessorException);

		/**
		 * Filter type setting with notification
		 * @param filterType ne new filter type
		 */
		void setFilterType(FilterType filterType);

		/**
		 * Setting filtering status with notification
		 * @param filtering ne new filtering status
		 */
		void setFiltering(bool filtering);

		/**
		 * Setting the log scale factor
		 * @param logScaleFactor the new log scale factor
		 */
		void setLogScaleFactor(double logScaleFactor);

		/**
		 * Low pass filter size setting
		 * @param channel channel index. If channel index == number of channels
		 * then set value for all channels
		 * @param filterSize the new value of low pass filter size.
		 * @note filterSize is limited to range
		 * [highPassFilterSize...filterMaxSize]
		 */
		void setLowPassFilterSize(const int channel,
								  const int filterSize);

		/**
		 * High pass filter size setting
		 * @param channel channel index. If channel index == number of channels
		 * then set value for all channels
		 * @param filterSize the new value of high pass filter size.
		 * @note filterSize is limited to range
		 * [filterMinSize...lowPassFilterSize]
		 */
		void setHighPassFilterSize(const int channel,
								   const int filterSize);

	signals:

//		/**
//		 * Signal sent when source image changes to adjust max filter sizes
//		 */
//		void dftSizeChanged();

		/**
		 * Signal sent when input dftSize square image has been reallocated
		 * @param image the new in square image
		 */
		void squareImageChanged(Mat * image);

		/**
		 * Signal sent when spectrum image has been reallocated
		 * @param image the new spectrum image
		 */
		void spectrumImageChanged(Mat * image);

		/**
		 * Signal sent when inverse image has been reallocated
		 * @param image the new inverse image
		 */
		void inverseImageChanged(Mat * image);
};

#endif /* QCVDFT_H_ */
