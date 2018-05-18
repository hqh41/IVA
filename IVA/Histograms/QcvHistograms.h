/*
 * QcvHistograms.h
 *
 *  Created on: 14 févr. 2012
 *      Author: davidroussel
 */

#ifndef QCVEHISTOGRAMS_H_
#define QCVEHISTOGRAMS_H_

#include <QString>
#include <QMutex>

#include "QcvProcessor.h"
#include "CvHistograms.h"

/**
 * Defines type for Histograms of 8 bits and 3 channels images.
 * @note this is because QObjects subclasses can NOT be templates,
 * so QcvHistograms should inherit CvHistograms<uchar,3> rather than
 * CvHistograms<T,channels>
 */
typedef CvHistograms<uchar,3> CvHistograms8UC3;

/**
 * OpenCV Color Image Histogram processing class with QT flavor
 */
class QcvHistograms: public QcvProcessor, public CvHistograms8UC3
{
	Q_OBJECT

	protected:

		/**
		 * String containing update histogram formatted time
		 */
		QString updateHistogramTime1String;

		/**
		 * String containing formatted LUT computing time
		 */
		QString computeLUTTimeString;

		/**
		 * String containing formatted LUT drawng time
		 */
		QString drawLUTTimeString;

		/**
		 * String containing formatted LUT apply time
		 */
		QString applyLUTTimeString;

		/**
		 * String containing formatted histogram update time after
		 * LUT applied
		 */
		QString updateHistogramTime2String;

		/**
		 * String containing formatted histogram drawing time
		 */
		QString drawHistogramTimeString;

		/**
		 * Self lock for operations from multiple threads
		 * @note may be NULL if there is no update thread
		 */
		QMutex * selfLock;

	public:

		/**
		 * QcvHistograms constructor
		 * @param image the source image
		 * @param computeGray indicates if an aditionnal gray level histogram
		 * should be computed
		 * @param drawHeight histogram drawing height
		 * @param drawWidth histogram drawing width
		 * @param timeCumulation indicates if timecumulation is on for histogram
		 * @param imageLock the mutex for concurrent access to the source image.
		 * In order to avoid concurrent access to the same image
		 * @param updateThread the thread in which this processor should run
		 * @param parent parent QObject
		 * computation
		 */
		QcvHistograms(Mat * image,
					  QMutex * imageLock = NULL,
					  QThread * updateThread = NULL,
					  const bool computeGray = true,
					  const size_t drawHeight = 256,
					  const size_t drawWidth = 512,
					  const bool timeCumulation = false,
					  QObject * parent = NULL);

		/**
		 * QImageHistogram destructor
		 */
		virtual ~QcvHistograms();

	protected:

		/**
		 * Draws selected histogram(s) in drawing frame and notifies the drawing
		 * frame
		 * @return the updated drawing frame.
		 */
		void drawHistograms();

		/**
		 * Draws selected transfert function in drawing frame and notifies the
		 * drawing frame
		 * @param lut the LUT to draw : the LUT may contains 1 or several
		 * channels
		 * @return the updated drawing frame
		 */
		void drawTransfertFunc(const Mat * lut);

		/**
		 * Apply current LUT (if != NULL) to the source image to produce the
		 * outFrame and notifies the drawing frame
		 * @return true if LUT has been applied, false if lut is NULL or
		 * lutType is NONE
		 */
		bool drawTransformedImage();

	public slots:
		/**
		 * Update computed images slot and sends displayImageChanged signal if
		 * required
		 */
		void update();

		/**
		 * Changes source image slot.
		 * Attributes needs to be cleaned up then set up again
		 * @param image the new source Image
		 */
		void setSourceImage(Mat * image) throw (CvProcessorException);

		/**
		 * Time cumulative histogram setting with notification
		 * @param value the value to set for time cumulative status
		 */
		void setTimeCumulative(const bool value);

		/**
		 * Cumulative histogram status setting with notification
		 * @param value the value to set for cumulative status
		 */
		void setCumulative(const bool value);

		/**
		 * Ith histogram component show setting with notifications
		 * @param i the ith histogram component
		 * @param value the value to set for this component show status
		 */
		void setShowComponent(const size_t i, const bool value);
		/**
		 * Current LUT setting with notification
		 * @param lutType the new LUT type
		 */
		void setLutType(const TransfertType lutType);

		/**
		 * Reset mean and std process time in order to re-start computing
		 * new mean and std process time values.
		 */
		virtual void resetMeanProcessTime();

	signals:
		/**
		 * Signal sent when update is completed AND transformed image is updated
		 */
		void outImageUpdated();

		/**
		 * Signal sent when transformed image has been reallocated
		 * @param image the new transformed image
		 */
		void outImageChanged(Mat * image);

		/**
		 * Signal sent when update is completed AND histogram image changes
		 */
		void histogramImageUpdated();

		/**
		 * Signal sent when histogram image has been reallocated
		 * @param image the new histogram image
		 */
		void histogramImageChanged(Mat * image);

		/**
		 * Signal sent when update is completed AND LUT image changes
		 */
		void lutImageUpdated();

		/**
		 * Signal sent when lut image has been reallocated;
		 * @param image the new LUT image
		 */
		void lutImageChanged(Mat * image);

		/**
		 * Signal emitted when histogram is updated with a new image
		 * @param formattedValue string containing the formatted time value
		 */
		void histogramTime1Updated(const QString & formattedValue);

		/**
		 * Signal emitted when LUT is computed
		 * @param formattedValue string containing the formatted time value
		 */
		void computeLUTTimeUpdated(const QString & formattedValue);

		/**
		 * Signal emitted when LUT is drawn
		 * @param formattedValue string containing the formatted time value
		 */
		void drawLUTTimeUpdated(const QString & formattedValue);

		/**
		 * Signal emitted when LUT is applied on image
		 * @param formattedValue string containing the formatted time value
		 */
		void applyLUTTimeUpdated(const QString & formattedValue);

		/**
		 * Signal emitted when histogram is updated after LUT has been applied
		 * @param formattedValue string containing the formatted time value
		 */
		void histogramTime2Updated(const QString & formattedValue);

		/**
		 * Signal emitted when histogram is drawn
		 * @param formattedValue string containing the formatted time value
		 */
		void drawHistogramTimeUpdated(const QString & formattedValue);
};

#endif /* QCVEHISTOGRAMS_H_ */
