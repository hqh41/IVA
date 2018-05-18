/*
 * QcvMatWidgetImage.h
 *
 *  Created on: 31 janv. 2012
 *	  Author: davidroussel
 */

#ifndef QCVMATWIDGETIMAGE_H_
#define QCVMATWIDGETIMAGE_H_

#include <QImage>
#include <QPainter>

#include "QcvMatWidget.h"

/**
 * OpenCV Widget for QT with a QPainter to draw image
 */
class QcvMatWidgetImage: public QcvMatWidget
{
	private:
		/**
		 * the Qimage to display in the widget with a QPainter
		 */
		QImage * qImage;

//		/**
//		 * Size Policy returned by
//		 */
//		QSizePolicy policy;

	public:
		/**
		 * Default Constructor
		 * @param parent parent widget
		 * @param mouseSense mouse sensivity
		 */
		QcvMatWidgetImage(QWidget *parent = NULL,
						  MouseSense mouseSense = MOUSE_NONE);

		/**
		 * Constructor
		 * @param sourceImage source image
		 * @param parent parent widget
		 * @param mouseSense mouse sensivity
		 */
		QcvMatWidgetImage(Mat * sourceImage,
						  QWidget *parent = NULL,
						  MouseSense mouseSense = MOUSE_NONE);

		/**
		 * Destructor.
		 */
		virtual ~QcvMatWidgetImage();

//		/**
//		 * Minimum size hint according to aspect ratio and min height of 100
//		 * @return minimum size hint
//		 */
//		QSize minimumSizeHint() const;

		/**
		 * aspect ratio method
		 * @param w width
		 * @return the required height fo r this width
		 */
		int heightForWidth ( int w ) const;

//		/**
//		 * Size policy to keep aspect ratio right
//		 * @return
//		 */
//		QSizePolicy sizePolicy () const;

		/**
		 * Sets new source image
		 * @param sourceImage the new source image
		 */
		virtual void setSourceImage(Mat * sourceImage);

	private:
		/**
		 * Setup widget (defines size policy)
		 */
		void setup();

	protected:
		/**
		 * paint event reimplemented to draw content
		 * @param event the paint event
		 */
		void paintEvent(QPaintEvent * event);

};

#endif /* QCVMATWIDGETIMAGE_H_ */
