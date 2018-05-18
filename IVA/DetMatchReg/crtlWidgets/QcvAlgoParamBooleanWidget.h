#ifndef QCVALGOPARAMBOOLEANWIDGET_H
#define QCVALGOPARAMBOOLEANWIDGET_H

#include <QWidget>

#include "QcvAlgoParamWidget.h"

namespace Ui {
	class QcvAlgoParamBooleanWidget;
}

/**
 * Widget class to view and control a boolean algorithm parameter
 * @author David Roussel
 * @date 2014/05/13
 */
class QcvAlgoParamBooleanWidget : public QcvAlgoParamWidget
{
	Q_OBJECT

	public:
		/**
		 * Constructor
		 * @param param the associated parameter
		 * @param direct direct operation: if true indicates that parameter
		 * value setting is performed directly through
		 * param->setBoolValue(...) which is blocking in
		 * multithread environments. If false indicates that parameter value
		 * setting is performed through signal/slot mechanism, which in
		 * multithreaded environments is non blocking with queued connections.
		 * @param parent the parent widget
		 */
		explicit QcvAlgoParamBooleanWidget(CvAlgoParam * param,
										   const bool direct = true,
										   QWidget *parent = NULL);

		/**
		 * Destructor.
		 * Clears the UI.
		 */
		virtual ~QcvAlgoParamBooleanWidget();

	signals:
		/**
		 * Signal emitted when the parameter value has been changed
		 */
		void parameterUpdated();

		/**
		 * Signal with new boolean value emitted when a boolean parameter
		 * has been updated
		 * @param value the new boolean value
		 */
		void parameterUpdated(const bool value);

	private slots:
		/**
		 * Slot triggered when the checkbox value changes
		 * @param value the checkbox state:
		 * 	- Qt::Unchecked
		 * 	- Qt::PartiallyChecked
		 * 	- Qt::Checked
		 * 	@note when value is Unchecked or PartiallyChecked the state is
		 * 	considered to be off.
		 * @note if the parameter is not settable, this method should
		 * (theoretically) never be triggered
		 * @post the new boolean value is set on the parameter and
		 * parameterUpdated() signal is emitted.
		 */
		void on_checkBox_stateChanged(int value);

		/**
		 * Slot triggered when the reset button is clicked in order to reset
		 * the value to its default (if it has one)
		 * @post default value is retrieved from parameter and applied to
		 * checkbox (this imples another call to on_checkBox_stateChanged()).
		 */
		void on_resetButton_clicked();

	private:
		/**
		 * UI from designer
		 */
		Ui::QcvAlgoParamBooleanWidget *ui;
};

#endif // QCVALGOPARAMBOOLEANWIDGET_H
