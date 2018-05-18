/*
 * QcvFloodFill.h
 *
 *  Created on: 25 févr. 2012
 *      Author: davidroussel
 */

#ifndef QCVFLOODFILL_H_
#define QCVFLOODFILL_H_

#include <QMutex>
#include <QPoint>

#include "QcvProcessor.h"
#include "CvFloodFill.h"

/**
 * Qt oriented CvProcessor example
 */
class QcvFloodFill : public QcvProcessor, public CvFloodFill
{
	Q_OBJECT

	protected:
		/**
		 * Self lock for operations from multiple threads
		 * @note may be NULL if there is no update thread.
		 */
		QMutex * selfLock;

	public:
		/**
		 * QcvFloodFill constructor
		 * @param inFrame the input frame from capture
		 * @param imageLock the mutex for concurrent access to the source image.
		 * In order to avoid concurrent access to the same image
		 * @param updateThread the thread in which this processor should run
		 * @param parent object
		 */
		QcvFloodFill(Mat * inFrame,
					 QMutex * imageLock = NULL,
					 QThread * updateThread = NULL,
					 QObject * parent = NULL);

		/**
		 * QcvFloodFill destructor
		 */
		virtual ~QcvFloodFill();

	public slots:
		/**
		 * Update computed images and sends displayImageChanged signal if
		 * required
		 */
		void update();

		/**
		 * Select image to set in displayImage and sends notification message
		 * @param index select the index to select display image
		 */
		void setDisplayMode(const ImageDisplay index);

		/**
		 * Sets a new flooding mode (absolute or relative) with notification
		 * @param ffillMode the new flooding mode
		 */
		void setFfillMode(const FloodFillMode ffillMode);

		/**
		 * Sets a new lower difference in pixels values for flooding
		 * @param loDiff the new lower difference for flooding
		 */
		void setLoDiff(const int loDiff);

		/**
		 * Sets a new upper difference in pixels values for flooding
		 * @param upDiff the new upper difference for flooding
		 */
		void setUpDiff(const int upDiff);

		/**
		 * Sets a new connectivity for pixels neighbors for flooding with
		 * notification
		 * @param connectivity the new connectivity for pixels neighbors
		 * for flooding
		 */
		void setConnectivity(const int connectivity);

		/**
		 * Sets an new initial seed
		 * @param initialSeed the new initial seed
		 */
		void setInitialSeed(const Point & initialSeed);

		/**
		 * Sets new show/hide seed point status with notification
		 * @param showSeed the new show/hide seed point status
		 */
		void setShowSeed(const bool showSeed);

		/**
		 * Set the show/hide bounding box status with notification
		 * @param showBoundingBox the new show/hide bounding box status
		 */
		void setShowBoundingBox(const bool showBoundingBox);

		/**
		 * Slot to clear current flood when left or right mouse button is
		 * pressed (should be connected to QcvMatWigdet::pressPoint signal)
		 * Later relase event will evt trigger new seed for flood
		 * @param p the point the event occured
		 * @param button the pressed button
		 */
		void clearFloodPoint(const QPoint & p, const Qt::MouseButton & button);

		/**
		 * Slot to set intialSeed point (should be connected to
		 * QcvMatWidget::releasePoint signal)
		 * @param p the initial seed point
		 * @param button the button pressed and released
		 */
		void setSeedPoint(const QPoint & p, const Qt::MouseButton & button);

};

#endif /* QCVFLOODFILL_H_ */
