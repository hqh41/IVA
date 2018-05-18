/*
 * QcvMatWidget.cpp
 *
 *  Created on: 28 févr. 2011
 *	  Author: davidroussel
 */
#include <QtDebug>

#include <opencv2/imgproc.hpp>

#include "QcvMatWidget.h"

/*
 * Default size when no image has been set
 */
QSize QcvMatWidget::defaultSize(640, 480);

/*
 * Default aspect ratio when image is not set yet
 */
double QcvMatWidget::defaultAspectRatio = 4.0/3.0;

/*
 * Drawing color
 */
const Scalar QcvMatWidget::drawingColor(0xFF,0xCC,0x00,0x88);

/*
 * Drawing width
 */
const int QcvMatWidget::drawingWidth(3);

/*
 * OpenCV QT Widget default constructor
 * @param parent parent widget
 * @param mouseSense mouse sensivity
 */
QcvMatWidget::QcvMatWidget(QWidget *parent,
						   MouseSense mouseSense) :
	QWidget(parent),
	sourceImage(NULL),
	aspectRatio(defaultAspectRatio),
	mousePressed(false),
	mouseSense(mouseSense),
//	count(0)
	pixelScale(devicePixelRatioF())
{
	setup();
}

/*
 * OpenCV QT Widget constructor
 * @param the source image
 * @param parent parent widget
 * @param mouseSense mouse sensivity
 */
QcvMatWidget::QcvMatWidget(Mat * sourceImage,
						   QWidget *parent,
						   MouseSense mouseSense) :
	QWidget(parent),
	sourceImage(sourceImage),
	aspectRatio((double)sourceImage->cols / (double)sourceImage->rows),
	mousePressed(false),
	mouseSense(mouseSense),
//	count(0)
	pixelScale(devicePixelRatioF())
{
	setup();
}

/*
 * OpenCV Widget destructor.
 * Releases displayImage.
 */
QcvMatWidget::~QcvMatWidget()
{
	displayImage.release();
}

/*
 * paint event reimplemented to draw content (in this case only
 * draw in display image since final rendering method is not yet available)
 * @param event the paint event
 */
void QcvMatWidget::paintEvent(QPaintEvent * event)
{
	Q_UNUSED(event);

	if (displayImage.data != NULL)
	{
		// evt draw in image
		if (mousePressed)
		{
			// if MOUSE_CLICK only draws a cross
			if (mouseSense > MOUSE_NONE)
			{
				if (!(mouseSense & MOUSE_DRAG))
				{
					if (mouseMoved)
					{
						drawCross(draggedPoint);
					}
					else
					{
						drawCross(pressedPoint);
					}
				}
				else  // else if MOUSE_DRAG starts drawing a rectangle
				{
					drawRectangle(selectionRect);
				}
			}
		}
	}
	else
	{
		qWarning("QcvMatWidget::paintEvent : image.data is NULL");
	}
}

/*
 * Widget setup
 */
void QcvMatWidget::setup()
{
	layout = new QHBoxLayout();
	layout->setContentsMargins(0,0,0,0);
	setLayout(layout);
}

/*
 * Sets new source image
 * @param sourceImage the new source image
 */
void QcvMatWidget::setSourceImage(Mat * sourceImage)
{
	// qDebug("QcvMatWidget::setSourceImage");

	this->sourceImage = sourceImage;

	// re-setup geometry since height x width may have changed
	aspectRatio = (double)sourceImage->cols / (double)sourceImage->rows;
	// qDebug ("aspect ratio changed to %4.2f", aspectRatio);

}

/*
 * Converts BGR or Gray source image to RGB display image
 * @see #sourceImage
 * @see #displayImage
 */
void QcvMatWidget::convertImage()
{
//	qDebug("Convert image");

	int depth = sourceImage->depth();
	int channels = sourceImage->channels();

	// Converts any image type to RGB format
	switch (depth)
	{
		case CV_8U:
			switch (channels)
			{
				case 1: // gray level image
					cvtColor(*sourceImage, displayImage,CV_GRAY2RGB);
					break;
				case 3: // Color image (OpenCV produces BGR images)
					cvtColor(*sourceImage, displayImage, CV_BGR2RGB);
					break;
				default:
					qFatal("This number of channels (%d) is not supported",
						   channels);
					break;
			}
			break;
		default:
			qFatal("This image depth (%d) is not implemented in QcvMatWidget",
				   depth);
			break;
	}
}

/*
 * Callback called when mouse button pressed event occurs.
 * reimplemented to send pressPoint signal when left mouse button is
 * pressed
 * @param event mouse event
 */
void QcvMatWidget::mousePressEvent(QMouseEvent *event)
{
	if (mouseSense > MOUSE_NONE)
	{
//		qDebug("mousePressEvent(%d, %d) with button %d",
//			   event->pos().x(), event->pos().y(), event->button());
		mousePressed = true;
		pressedPoint = event->pos();
		pressedButton = event->button();

		if((event->button() == Qt::LeftButton) && (mouseSense & MOUSE_DRAG))
		{
			// initialise selection rect
			selectionRect.setTopLeft(pressedPoint);
			selectionRect.setBottomRight(pressedPoint);
		}

		emit pressPoint(pressedPoint, pressedButton);
	}
}

/*
 * Callback called when mouse move event occurs.
 * reimplemented to send dragPoint signal when mouse is dragged
 * (after left mouse button has been pressed)
 * @param event mouse event
 */
void QcvMatWidget::mouseMoveEvent(QMouseEvent *event)
{
	mouseMoved = true;
	draggedPoint = event->pos();

	if ((mouseSense & MOUSE_DRAG) && mousePressed)
	{
//		qDebug("mouseMoveEvent(%d, %d) with button %d",
//			   event->pos().x(), event->pos().y(), event->button());

		selectionRectFromPoints(pressedPoint, draggedPoint);

		emit dragPoint(draggedPoint);
	}
}

/*
 * Callback called when mouse button released event occurs.
 * reimplemented to send releasePoint signal when left mouse button is
 * released
 * @param event mouse event
 */
void QcvMatWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if ((mouseSense > MOUSE_NONE) && mousePressed)
	{
//		qDebug("mouseReleaseEvent(%d, %d) with button %d",
//			   event->pos().x(), event->pos().y(), event->button());
		mousePressed = false;
		mouseMoved = false;
		releasedPoint = event->pos();
		emit releasePoint(releasedPoint, pressedButton);

		if ((event->button() == Qt::LeftButton) && (mouseSense & MOUSE_DRAG))
		{
			selectionRectFromPoints(pressedPoint, releasedPoint);
			emit releaseSelection(selectionRect, event->button());
		}
	}
}

/*
 * Draw Cross
 * @param p the cross center
 */
void QcvMatWidget::drawCross(const QPoint & p)
{
	int x0 = p.x();
	int y0 = p.y();
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
	int offset = 10;

	x1 = x0 - 2*offset;
	x2 = x0 - offset;
	x3 = x0 + offset;
	x4 = x0 + 2*offset;
	y1 = y0 - 2*offset;
	y2 = y0 - offset;
	y3 = y0 + offset;
	y4 = y0 + 2*offset;

	Point p1a(x1, y0);
	Point p1b(x2, y0);
	Point p2a(x3, y0);
	Point p2b(x4, y0);
	Point p3a(x0, y1);
	Point p3b(x0, y2);
	Point p4a(x0, y3);
	Point p4b(x0, y4);

	line(displayImage, p1a, p1b, drawingColor, drawingWidth, CV_AA);
	line(displayImage, p2a, p2b, drawingColor, drawingWidth, CV_AA);
	line(displayImage, p3a, p3b, drawingColor, drawingWidth, CV_AA);
	line(displayImage, p4a, p4b, drawingColor, drawingWidth, CV_AA);
}

/*
 * Draw rectangle
 * @param r the rectangle to draw
 */
void QcvMatWidget::drawRectangle(const QRect & r)
{
	int x1 = r.left();
	int x2 = r.right();
	int y1 = r.top();
	int y2 = r.bottom();

	Point p1(x1, y1);
	Point p2(x2, y2);

	rectangle(displayImage, p1, p2, drawingColor, drawingWidth, CV_AA);
}

/*
 * Modifiy selectionRect using two points
 * @param p1 first point
 * @param p2 second point
 */
void QcvMatWidget::selectionRectFromPoints(const QPoint & p1, const QPoint & p2)
{
	int left, right, top, bottom;
	if (p1.x() < p2.x())
	{
		left = p1.x();
		right = p2.x();
	}
	else
	{
		left = p2.x();
		right = p1.x();
	}

	if (p1.y() < p2.y())
	{
		top = p1.y();
		bottom = p2.y();
	}
	else
	{
		top = p2.y();
		bottom = p1.y();
	}

	selectionRect.setLeft(left);
	selectionRect.setRight(right);
	selectionRect.setTop(top);
	selectionRect.setBottom(bottom);
}



/*
 * Widget minimum size is set to the contained image size
 * @return le size of the image within
 */
//QSize QcvMatWidget::minimumSize() const
//{
//	return sizeHint();
//}


/*
 * Size hint (because size depends on sourceImage properties)
 * @return size obtained from sourceImage
 */
QSize QcvMatWidget::sizeHint() const
{
	if (sourceImage != NULL)
	{
		return QSize(sourceImage->cols, sourceImage->rows);
	}
	else
	{
		return defaultSize;
	}
}

/*
 * Gets Mat widget mouse clickable status
 * @return true if widget is sensitive to mouse click
 */
bool QcvMatWidget::isMouseClickable() const
{
	return (mouseSense & MOUSE_CLICK);
}

/*
 * Gets Mat widget mouse dragable status
 * @return true if widget is sensitive to mouse drag
 */
bool QcvMatWidget::isMouseDragable() const
{
	return (mouseSense & MOUSE_DRAG);
}

/*
 * Update slot customized to include convertImage before actually
 * updating
 */
void QcvMatWidget::update()
{
//	count++;
//	qDebug() << "QcvMatWidget::update " << count;
//	std::cerr << "{o";
	convertImage();
	QWidget::update();
//	std::cerr << "}";
}

/*
 * Recompute pixel scale according to screen pixel scale.
 * Used with Hi DPI devices (such as retina screens)
 * @post pixel scale have been updated according to
 * devicePixelRatioF provided by the QPaintDevice super class
 */
void QcvMatWidget::screenChanged()
{
	pixelScale = devicePixelRatioF();
//	qDebug() << "Pixel scale updated to" << pixelScale;
}

// ----------------------------------------------------------------------------
// convertImage old algorithm
// ----------------------------------------------------------------------------
//	int cvIndex, cvLineStart;
//	// switch between bit depths
//	switch (displayImage.depth())
//	{
//		case CV_8U:
//			switch (displayImage.channels())
//			{
//				case 1: // Gray level images
//					if ( (displayImage.cols != image.width()) ||
//						 (displayImage.rows != image.height()) )
//					{
//						QImage temp(displayImage.cols, displayImage.rows,
//								QImage::Format_RGB32);
//						image = temp;
//					}
//					cvIndex = 0;
//					cvLineStart = 0;
//					for (int y = 0; y < displayImage.rows; y++)
//					{
//						unsigned char red, green, blue;
//						cvIndex = cvLineStart;
//						for (int x = 0; x < displayImage.cols; x++)
//						{
//							// DO it
//							red   = displayImage.data[cvIndex];
//							green = displayImage.data[cvIndex];
//							blue  = displayImage.data[cvIndex];
//
//							image.setPixel(x, y, qRgb(red, green, blue));
//							cvIndex++;
//						}
//						cvLineStart += displayImage.step;
//					}
//					break;
//				case 3: // BGR images (Regular OpenCV Color Capture)
//					if ( (displayImage.cols != image.width()) ||
//						 (displayImage.rows != image.height()) )
//					{
//						QImage temp(displayImage.cols, displayImage.rows,
//								QImage::Format_RGB32);
//						image = temp;
//					}
//					cvIndex = 0;
//					cvLineStart = 0;
//					for (int y = 0; y < displayImage.rows; y++)
//					{
//						unsigned char red, green, blue;
//						cvIndex = cvLineStart;
//						for (int x = 0; x < displayImage.cols; x++)
//						{
//							// DO it
//							red   = displayImage.data[cvIndex + 2];
//							green = displayImage.data[cvIndex + 1];
//							blue  = displayImage.data[cvIndex + 0];
//
//							image.setPixel(x, y, qRgb(red, green, blue));
//							cvIndex += 3;
//						}
//						cvLineStart += displayImage.step;
//					}
//					break;
//				default:
//					printf("This number of channels is not supported\n");
//					break;
//			}
//			break;
//		default:
//			printf("This type of Image is not implemented in QcvMatWidget\n");
//			break;
//	}

