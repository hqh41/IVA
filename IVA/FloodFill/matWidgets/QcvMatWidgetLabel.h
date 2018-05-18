
#ifndef QCVMATWIDGETLABEL_H
#define QCVMATWIDGETLABEL_H

#include <QLabel>

#include "QcvMatWidget.h"

/**
 * OpenCV Widget for QT with QImage display
 */
class QcvMatWidgetLabel : public QcvMatWidget
{
	private:
		/**
		 * The Image Label
		 */
		QLabel * imageLabel;

	public:
		/**
		 * OpenCV QT Widget default constructor
		 * @param parent parent widget
		 * @param mouseSense mouse sensivity
		 */
		QcvMatWidgetLabel(QWidget *parent = NULL,
						  MouseSense mouseSense = MOUSE_NONE);

		/**
		 * OpenCV QT Widget constructor
		 * @param sourceImage the source OpenCV qImage
		 * @param parent parent widget
		 * @param mouseSense mouse sensivity
		 */
		QcvMatWidgetLabel(Mat * sourceImage,
						  QWidget *parent = NULL,
						  MouseSense mouseSense = MOUSE_NONE);

		/**
		 * OpenCV Widget destructor.
		 */
		virtual ~QcvMatWidgetLabel(void);

	private:
		/**
		 * Widget setup
		 * @pre imageLabel has been allocated
		 * @post imageLabel has been added to the layout
		 */
		void setup();

	protected:
		/**
		 * paint event reimplemented to draw content
		 * @param event the paint event
		 * @pre imageLabel has been allocated
		 * @post displayImage has been set as pixmap of the imageLabel
		 */
		void paintEvent(QPaintEvent * event);

};

#endif //QCVMATWIDGETLABEL_H
