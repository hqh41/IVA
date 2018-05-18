/*
 * QcvMatWidget.h
 *
 *  Created on: 28 févr. 2011
 *	  Author: davidroussel
 */

#ifndef QCVMATWIDGET_H_
#define QCVMATWIDGET_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPoint>

#include <opencv2/core/mat.hpp>
using namespace cv;

/**
 * Abstract widget to show OpenCV Mat image into QT.
 * Should be refined in
 * 	- QcvMatWidgetLabel
 * 	- QcvMatWidgetImage
 * 	- QcvMatWidgetGL
 */
class QcvMatWidget : public QWidget
{
	Q_OBJECT

	public:
		/**
		 * Mouse sensivity of the image widget
		 */
		typedef enum
		{
			/**
			 * Sensitive to no mouse click or drag
			 */
			MOUSE_NONE = 0,
			/**
			 * Sensitive to mouse clicks
			 */
			MOUSE_CLICK = 1,
			/**
			 * Sensitive to mouse drag
			 */
			MOUSE_DRAG = 2,
			/**
			 * Sensitive to mouse click and drag
			 */
			MOUSE_CLICK_AND_DRAG = 3
		} MouseSense;

	protected:
		/**
		 * The widget layout
		 */
		QHBoxLayout * layout;

		/**
		 * The OpenCV BGR or gray image
		 */
		Mat * sourceImage;

		/**
		 * The OpenCV RGB image converted from gray or BGR OpenCV image
		 */
		Mat displayImage;

		/**
		 * Default size when no image has been set
		 */
		static QSize defaultSize;

		/**
		 * the aspect ratio ofthe image to draw
		 */
		double aspectRatio;

		/**
		 * Default aspect ratio when image is not set yet
		 */
		static double defaultAspectRatio;

		/**
		 * Indicate a mouse button is currently pressed within the widget
		 */
		bool mousePressed;

		/**
		 * Indicate a mouse is moved after a button has been pressed
		 */
		bool mouseMoved;

		/**
		 * Mouse sensivity
		 */
		MouseSense mouseSense;

		/**
		 * mouse pressed location
		 */
		QPoint pressedPoint;

		/**
		 * Mouse pressed button
		 */
		Qt::MouseButton pressedButton;

		/**
		 * mouse drag location
		 */
		QPoint draggedPoint;

		/**
		 * mouse release location
		 */
		QPoint releasedPoint;

		/**
		 * Selection rectangle
		 */
		QRect selectionRect;

		/**
		 * Drawing color
		 */
		static const Scalar drawingColor;

		/**
		 * Drawing width
		 */
		static const int drawingWidth;

//		size_t count;

		/**
		 * Pixel scale used to draw images.
		 * Used in OpenGL contexts in order to draw images with the right pixel
		 * scale on Hi DPI devices (such as retina screens)
		 */
		float pixelScale;

	public:

		/**
		 * OpenCV QT Widget default constructor
		 * @param parent parent widget
		 * @param mouseSense mouse sensivity
		 */
		QcvMatWidget(QWidget *parent = NULL,
					 MouseSense mouseSense = MOUSE_NONE);

		/**
		 * OpenCV QT Widget constructor
		 * @param sourceImage the source image
		 * @param parent parent widget
		 * @param mouseSense mouse sensivity
		 * @pre sourceImage is not NULL
		 */
		QcvMatWidget(Mat * sourceImage,
					 QWidget *parent = NULL,
					 MouseSense mouseSense = MOUSE_NONE);

		/**
		 * OpenCV Widget destructor.
		 * Releases displayImage.
		 */
		virtual ~QcvMatWidget(void);

//		/**
//		 * Widget minimum size is set to the contained image size
//		 * @return le size of the image within
//		 */
//		QSize minimumSize() const;

		/**
		 * Size hint (because size depends on sourceImage properties)
		 * @return size obtained from sourceImage or defaultSize if sourceImage
		 * is not set yet
		 */
		QSize sizeHint() const;

		/**
		 * Gets Mat widget mouse clickable status
		 * @return true if widget is sensitive to mouse click
		 */
		bool isMouseClickable() const;

		/**
		 * Gets Mat widget mouse dragable status
		 * @return true if widget is sensitive to mouse drag
		 */
		bool isMouseDragable() const;

	protected:

		/**
		 * paint event reimplemented to draw content (in this case only
		 * draw in display image since final rendering method is not yet available)
		 * @param event the paint event
		 */
		virtual void paintEvent(QPaintEvent * event);

		/**
		 * Widget setup
		 * @post new Layout has been created and set for this widget
		 */
		void setup();

		/**
		 * Converts BGR or Gray source image to RGB display image
		 * @pre sourceImage is not NULL
		 * @post BGR or Gray source image has been converted to RGB displayimage
		 * @see #sourceImage
		 * @see #displayImage
		 */
		void convertImage();

		/**
		 * Callback called when mouse button pressed event occurs.
		 * reimplemented to send pressPoint signal when left mouse button is
		 * pressed
		 * @param event mouse event
		 */
		void mousePressEvent(QMouseEvent *event);

		/**
		 * Callback called when mouse move event occurs.
		 * reimplemented to send dragPoint signal when mouse is dragged
		 * (after left mouse button has been pressed)
		 * @param event mouse event
		 */
		void mouseMoveEvent(QMouseEvent *event);

		/**
		 * Callback called when mouse button released event occurs.
		 * reimplemented to send releasePoint signal when left mouse button is
		 * released
		 * @param event mouse event
		 */
		void mouseReleaseEvent(QMouseEvent *event);

		/**
		 * Draw Cross
		 * @param p the cross center
		 */
		virtual void drawCross(const QPoint & p);

		/**
		 * Draw rectangle
		 * @param r the rectangle to draw
		 */
		virtual void drawRectangle(const QRect & r);

//		/*
//		 * paint event reimplemented to draw content
//		 * @param event the paint event
//		 */
//		virtual void paintEvent(QPaintEvent * event) = 0;

		/**
		 * Modifiy selectionRect using two points
		 * @param p1 first point
		 * @param p2 second point
		 */
		void selectionRectFromPoints(const QPoint & p1, const QPoint & p2);

	public slots:
		/**
		 * Sets new source image
		 * @param sourceImage the new source image
		 * @pre sourceimage is not NULL
		 * @post new sourceImage has been set and aspectRatio has been updated
		 */
		virtual void setSourceImage(Mat * sourceImage);

		/**
		 * Update slot customized to include convertImage before actually
		 * updating
		 * @post sourceImage have been converted to RGB and widget updated
		 */
		virtual void update();

		/**
		 * Recompute pixel scale according to screen pixel scale.
		 * Slot triggered by a screenChanged(QScreen*) emitted by the containing
		 * window handle.
		 * Used with Hi DPI devices (such as retina screens).
		 * @post pixel scale have been updated according to
		 * devicePixelRatioF provided by the QPaintDevice super class
		 */
		virtual void screenChanged();

	signals:

		/**
		 * Signal sent to transmit the point in the widget where a mouse
		 * button has been pressed
		 * @param p the point where any mouse button has been pressed
		 * @param button the button pressed
		 */
		void pressPoint(const QPoint & p, const Qt::MouseButton & button);

		/**
		 * Signal sent to transmit the point in the widget where mouse cursor is
		 * currently dragged to (which suppose a mouse button has been
		 * previously pressed)
		 * @param p the point where the mouse cursor is dragged to
		 */
		void dragPoint(const QPoint & p);

		/**
		 * Signal sent to transmit the point in the widget where a mouse
		 * button has been released
		 * @param p the point where left mouse button has been released
		 * @param button the button pressed
		 */
		void releasePoint(const QPoint & p, const Qt::MouseButton & button);

		/**
		 * Signal sent to transmit the rectangle selection when mouse button
		 * has been clicked, dragged and released
		 * @param r the rectangle selection
		 * @param button the button pressed during dragging
		 */
		void releaseSelection(const QRect & r, const Qt::MouseButton & button);
};

#endif /* QCVMATWIDGET_H_ */
