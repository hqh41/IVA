#ifndef QCVALGOPARAMINTWIDGET_H
#define QCVALGOPARAMINTWIDGET_H

#include <QWidget>

#include "QcvAlgoParamWidget.h"

namespace Ui {
	class QcvAlgoParamIntWidget;
}


/**
 * Widget class to view and control an integer algorithm parameter
 * @author David Roussel
 * @date 2014/05/13
 */
class QcvAlgoParamIntWidget : public QcvAlgoParamWidget
{
	Q_OBJECT

	public:
		/**
		 * Constructor
		 * @param param the associated parameter
		 * @param slider indicates if there should be a slider beneath label
		 * and spinbox
		 * @param direct direct operation: if true indicates that parameter
		 * value setting is performed directly through
		 * param->setIntValue(...) which is blocking in
		 * multithread environments. If false indicates that parameter value
		 * setting is performed through signal/slot mechanism, which in
		 * multithreaded environments is non blocking with queued connections.
		 * @param parent the parent widget
		 */
		explicit QcvAlgoParamIntWidget(CvAlgoParam * param,
									   const bool slider = true,
									   const bool direct = false,
									   QWidget *parent = 0);
		/**
		 * Destructor.
		 * Clears the UI.
		 */
		virtual ~QcvAlgoParamIntWidget();

	signals:
		/**
		 * Signal emitted when the parameter value has been changed
		 */
		void parameterUpdated();

		/**
		 * Signal with integer value emitted when integer value changes
		 * @param value the new integer value
		 */
		void parameterUpdated(const int value);

	private slots:
		/**
		 * Slot triggered when the spinbox value changes
		 * @param value the new spinbox value
		 * @note if the parameter is not settable, this method should
		 * (theoretically) never be triggered
		 * @post the associated parameter is set to this value and
		 * parameterUpdated() signal is emitted
		 */
		void on_spinBox_valueChanged(int value);

		/**
		 * Slot triggered when reset button is clicked.
		 * @post default value is retreived from parameter and spinbox
		 * value is changed to this value (this implies a call to
		 * on_spinBox_valueChanged())
		 */
		void on_resetButton_clicked();

	private:
		/**
		 * UI from designer
		 */
		Ui::QcvAlgoParamIntWidget *ui;

		/**
		 * Indicate if slider hould be used or removed
		 */
		bool slider;
};

#endif // QCVALGOPARAMINTWIDGET_H
