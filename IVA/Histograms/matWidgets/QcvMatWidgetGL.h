/*
 * QcvMatWidgetGL.h
 *
 *  Created on: 28 févr. 2011
 *	  Author: davidroussel
 */

#ifndef QOPENCVWIDGETQGL_H_
#define QOPENCVWIDGETQGL_H_

#include <QGLWidget>

#include "QcvMatWidget.h"
#include "QGLImageRender.h"

/**
 * OpenCV Widget for QT with QGLWidget display
 */
class QcvMatWidgetGL: public QcvMatWidget
{
	private:
		/**
		 * QGLWidget to draw in
		 */
		QGLImageRender * gl;

	public:

		/**
		 * OpenCV QT Widget default constructor
		 * @param parent parent widget
		 * @param mouseSense mouse sensivity
		 */
		QcvMatWidgetGL(QWidget *parent = NULL,
					   MouseSense mouseSense = MOUSE_NONE);

		/**
		 * OpenCV QT Widget constructor
		 * @param sourceImage the source image
		 * @param parent parent widget
		 * @param mouseSense mouse sensivity
		 */
		QcvMatWidgetGL(Mat * sourceImage,
					   QWidget *parent = NULL,
					   MouseSense mouseSense = MOUSE_NONE);

		/**
		 * Sets new source image
		 * @param sourceImage the new source image
		 */
		void setSourceImage(Mat * sourceImage);

		/**
		 * OpenCV Widget destructor.
		 */
		virtual ~QcvMatWidgetGL();

	protected:
		/*
		 * paint event reimplemented to draw content
		 * @param event the paint event
		 */
		void paintEvent(QPaintEvent * event);
};

#endif /* QOPENCVWIDGETQGL_H_ */
