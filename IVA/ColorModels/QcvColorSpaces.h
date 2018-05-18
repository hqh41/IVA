/*
 * QcvColorSpaces.h
 *
 *  Created on: 25 févr. 2012
 *      Author: davidroussel
 */

#ifndef QCVCOLORSPACES_H_
#define QCVCOLORSPACES_H_

#include <QMutex>

#include "QcvProcessor.h"
#include "CvColorSpaces.h"

/**
 * Qt oriented Colorspaces
 */
class QcvColorSpaces : public QcvProcessor, public CvColorSpaces
{
	Q_OBJECT
	
	protected:
		/**
		 * Self lock for operations in multiple threads
		 * @note may be NULL if not multithreaded
		 */
		QMutex * selfLock;

	public:
		/**
		 * QcvColorSpaces constructor
		 * @param inFrame the input frame from capture
		 * @param imageLock the mutex on source image
		 * @param updateThread the thread in which this processor runs
		 * @param parent object
		 */
		QcvColorSpaces(Mat * inFrame,
					   QMutex * imageLock = NULL,
					   QThread * updateThread = NULL,
					   QObject * parent = NULL);

		/**
		 * QcvColorSpaces destructor
		 */
		virtual ~QcvColorSpaces();

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
		void setDisplayImageIndex(const Display index);

		/**
		 * Sets the color display status of selected component and sends
		 * notification message
		 * @param c the selected component:
		 * @param value the value to set on the selected component
		 */
		void setColorChannel(const ShowColor c, const bool value);

		/**
		 * Select hue display mode and sends notification message
		 * @param mode the mode so select
		 */
		void setHueDisplayMode(const HueDisplay mode);
};

#endif /* QCVCOLORSPACES_H_ */
