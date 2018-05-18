/*
 * QcvGFilter.h
 *
 *  Created on: 27 févr. 2012
 *      Author: davidroussel
 */

#ifndef QCVGFILTER_H_
#define QCVGFILTER_H_

#include "QcvProcessor.h"
#include "CvGFilter.h"

/**
 * QT flavored class to process source image with gaussian filters
 */
class QcvGFilter: public QcvProcessor, public CvGFilter
{
	Q_OBJECT

	protected:
		/**
		 * Self lock for operations from multiple threads
		 * @note may be NULL ift there is no update thread
		 */
		QMutex * selfLock;

	public:

		/**
		 * QcvGFilter constructor
		 * @param image the source image
		 * @param imageLock the mutex on source image
		 * @param updateThread the thread in which this processor runs
		 * @param parent parent QObject
		 */
		QcvGFilter(Mat * image,
				   QMutex * imageLock = NULL,
				   QThread * updateThread = NULL,
				   QObject * parent = NULL);

		/**
		 * QcvGFilter destructor
		 */
		virtual ~QcvGFilter();

		// --------------------------------------------------------------------
		// Options settings with message notification
		// --------------------------------------------------------------------

	public slots:
		/**
		 * Update computed images slot and sends updated signal
		 * required
		 */
		void update();

		/**
		 * Changes source image slot.
		 * Attributes needs to be cleaned up then set up again
		 * @param image the new source Image
		 */
		void setSourceImage(Mat * image)
			throw (CvProcessorException);

		/**
		 * Sets the a new kernel size
		 * @param kernelSize the new kernel size
		 * @post if new size is in range [3..15]
		 * with a step of 2;
		 * 	- the new kernel size is set up, and remains unchanged otherwise.
		 *	- gaussian kernels are eventually recomputed
		 */
		void setKernelSize(int kernelSize);

		/**
		 * Sets a new value for gaussian variance
		 * @param sigma the new value of gaussian variance
		 */
		void setSigma(double sigma);

		/**
		 * Sets new threshold level for edge map
		 * @param thresholdLevel the new threshold level
		 */
		void setThresholdLevel(int thresholdLevel);

		/**
		 * Sets new Harris parameter Kappa
		 * @param harrisKappa the new parameter to set
		 */
		void setHarrisKappa(double harrisKappa);

		/**
		 * Sets a new display mode and emit corresponding imageChanged(Mat*)
		 * signal
		 * @param displayMode the new display mode to set
		 */
		void setDisplayMode(const ImageDisplay displayMode);

		/**
		 * Set a new edge didsplay mode and emit corresponding
		 * imageChanged(Mat*) signal if needed
		 * @param edgeMode the new edge mode
		 * @param standalone if setEdgeMode is used by itself then true, but
		 * false when used inside setDisplayMode
		 */
		void setEdgeMode(const EdgeDisplay edgeMode, const bool standalone = true);

	signals:
		/**
		 * Signal emitted when kernelSize changed because sigma values (min,
		 * max, step & value) are changed by new kernel size values
		 * @param kernelSize the new kernelSize
		 */
		void kernelSizeChanged(int kernelSize);

};

#endif /* QCVGFILTER_H_ */
