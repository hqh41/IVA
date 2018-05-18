//#include <iostream>
#include <QtDebug>
#include "QcvMatWidgetLabel.h"

using namespace std;

/*
 * OpenCV QT Widget default constructor
 * @param parent parent widget
 */
QcvMatWidgetLabel::QcvMatWidgetLabel(QWidget *parent,
									 MouseSense mouseSense) :
	QcvMatWidget(parent, mouseSense),
	imageLabel(new QLabel())
{
	setup();
}

/*
 * OpenCV QT Widget constructor
 * @param the source OpenCV qImage
 * @param parent parent widget
 */
QcvMatWidgetLabel::QcvMatWidgetLabel(Mat * sourceImage,
									 QWidget *parent,
									 MouseSense mouseSense) :
	QcvMatWidget(sourceImage, parent, mouseSense),
	imageLabel(new QLabel())
{
	setup();
}

/*
 * Widget setup
 * @pre imageLabel has been allocated
 */
void QcvMatWidgetLabel::setup()
{
	layout->addWidget(imageLabel,0,Qt::AlignCenter);
}

/*
 * OpenCV Widget destructor.
 */
QcvMatWidgetLabel::~QcvMatWidgetLabel(void)
{
	delete imageLabel;
}

/*
 * paint event reimplemented to draw content
 * @param event the paint event
 */
void QcvMatWidgetLabel::paintEvent(QPaintEvent * event)
{
//	qDebug("QcvMatWidgetLabel::paintEvent");
	QcvMatWidget::paintEvent(event);

	if (displayImage.data != NULL)
	{
		// Builds Qimage from RGB image data
		// and sets image as Label pixmap
		imageLabel->setPixmap(QPixmap::fromImage(QImage((uchar *) displayImage.data,
														displayImage.cols,
														displayImage.rows,
														displayImage.step,
														QImage::Format_RGB888)));
	}
	else
	{
		qWarning("QcvMatWidgetLabel::paintEvent : image.data is NULL");
	}
}
