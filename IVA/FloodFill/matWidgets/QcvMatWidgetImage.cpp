/*
 * QcvMatWidgetImage.cpp
 *
 *  Created on: 31 janv. 2012
 *	  Author: davidroussel
 */

#include "QcvMatWidgetImage.h"
#include <QPaintEvent>
#include <QSizePolicy>
#include <QDebug>

/*
 * Default Constructor
 * @param parent parent widget
 */
QcvMatWidgetImage::QcvMatWidgetImage(QWidget *parent,
									 MouseSense mouseSense) :
	QcvMatWidget(parent, mouseSense),
	qImage(NULL)
{
	setup();
}

/*
 * Constructor
 * @param sourceImage source image
 * @param parent parent widget
 */
QcvMatWidgetImage::QcvMatWidgetImage(Mat * sourceImage,
									 QWidget *parent,
									 MouseSense mouseSense) :
	QcvMatWidget(sourceImage, parent, mouseSense),
	qImage(NULL)
{
	setSourceImage(sourceImage);

	setup();
}

/*
 * Setup widget (defines size policy)
 */
void QcvMatWidgetImage::setup()
{
//	qDebug("QcvMatWidgetImage::Setup");

	/*
	 * Customize size policy
	 */
	QSizePolicy qsp(QSizePolicy::Fixed, QSizePolicy::Fixed);
	// sets height depends on width (also need to reimplement heightForWidth())
	qsp.setHeightForWidth(true);
	setSizePolicy(qsp);

	/*
	 * Customize layout
	 */

	// size policy has changed to call updateGeometry
	updateGeometry();
}

/*
 * Destructor.
 */
QcvMatWidgetImage::~QcvMatWidgetImage()
{
	if (qImage != NULL)
	{
		delete qImage;
	}
}

/*
 * Sets new source image
 * @param sourceImage the new source image
 */
void QcvMatWidgetImage::setSourceImage(Mat * sourceImage)
{
	if (qImage != NULL)
	{
		delete qImage;
	}
	// setup and convert image
	QcvMatWidget::setSourceImage(sourceImage);
	convertImage();
	qImage = new QImage((uchar *) displayImage.data, displayImage.cols,
		displayImage.rows, displayImage.step,
		QImage::Format_RGB888);

	// re-setup geometry since height x width may have changed
	updateGeometry();
}

/*
 * Size policy to keep aspect ratio right
 * @return
 */
//QSizePolicy QcvMatWidgetImage::sizePolicy () const
//{
//	return policy;
//}

/*
 * aspect ratio method
 * @param w width
 * @return the required height fo r this width
 */
int QcvMatWidgetImage::heightForWidth(int w) const
{
//	qDebug ("height  = %d for width  = %d called", (int)((double)w/aspectRatio), w);
	return (int)((double)w/aspectRatio);
}

/*
 * Minimum size hint according to aspect ratio and min height of 100
 * @return minimum size hint
 */
//QSize QcvMatWidgetImage::minimumSizeHint () const
//{
//	// qDebug("min size called");
//	// return QSize((int)(100.0*aspectRatio), 100);
//	return sizeHint();
//}


/*
 * paint event reimplemented to draw content
 * @param event the paint event
 */
void QcvMatWidgetImage::paintEvent(QPaintEvent *event)
{
//	qDebug("QcvMatWidgetImage::paintEvent");

	// evt draws in image directly
	QcvMatWidget::paintEvent(event);

	if (displayImage.data != NULL)
	{
		// then draw image
		QPainter painter(this);
		painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
		if (event == NULL)
		{
			painter.drawImage(0, 0, *qImage);
		}
		else // partial repaint
		{
			painter.drawImage(event->rect(), *qImage);
		}
	}
	else
	{
		qWarning("QcvMatWidgetImage::paintEvent : image.data is NULL");
	}
}
