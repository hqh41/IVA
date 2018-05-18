/*
 * QGLImageRender.cpp
 *
 *  Created on: 28 févr. 2011
 *	  Author: davidroussel
 */
#include <QDebug>
#ifdef __APPLE__
	#include <gl.h>
	#include <glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
#include "QGLImageRender.h"

/*
 * QGLImageRender Constructor
 * @param image the RGB image to draw in the pixel buffer
 * @param format pixel format
 * @param pixelScale pixel scale pointer from container
 * @param parent the parent widget
 */
QGLImageRender::QGLImageRender(const Mat & image,
							   const GLenum format,
							   float * pixelScale,
							   QWidget *parent) :
	QGLWidget(parent),
	image(image),
	pixelFormat(format),
	pixelScale(pixelScale)
{
	if (!doubleBuffer())
	{
		qWarning("QGLImageRender::QGLImageRender caution : no double buffer");
	}
	if (this->image.data == NULL)
	{
		qWarning("QGLImageRender::QGLImageRender caution : image data is null");
	}
	if (this->pixelScale == NULL)
	{
		qCritical("QGLImageRender::QGLImageRender caution : pixel scale is null");
	}
}

QGLImageRender::~QGLImageRender()
{
	image.release();
}

void QGLImageRender::initializeGL()
{
//	qDebug("GL init ...");
	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void QGLImageRender::resizeGL(int width, int height)
{
//	qDebug("GL resizeGL ...");

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (image.data != NULL)
	{
		glOrtho(0, (GLdouble) image.cols, 0, (GLdouble) image.rows, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void QGLImageRender::paintGL()
{
//	qDebug("GL drawing pixels ...");

	glClear(GL_COLOR_BUFFER_BIT);

	if (image.data != NULL)
	{
		/* apply the right translate so the image drawing starts top left */
		glRasterPos4f(0.0f,(GLfloat)(image.rows), 0.0f, 1.0f);
		/*
		 * for hi dpi displays
		 *	typically pixelScale =
		 *	- 1.0 for normal displays
		 *	- 2.0 for hidpi displays
		 */
		glPixelZoom(*pixelScale, -(*pixelScale));

		glDrawPixels(image.cols, image.rows, pixelFormat,
					 GL_UNSIGNED_BYTE, image.data);
		// In any circumstance you should NOT use glFlush or swapBuffers() here
	}
	else
	{
		qWarning("Nothing to draw");
	}
}

QSize QGLImageRender::sizeHint () const
{
	return minimumSizeHint();
}

QSize QGLImageRender::minimumSizeHint() const
{
	if (image.data != NULL)
	{
		return QSize(image.cols, image.rows);
	}
	else
	{
		qWarning("QGLImageRender::minimumSizeHint : probably invalid sizeHint");
		return QSize(320,240);
	}
}

QSizePolicy	QGLImageRender::sizePolicy () const
{
	return QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
