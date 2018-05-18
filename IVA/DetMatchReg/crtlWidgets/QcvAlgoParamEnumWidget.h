#ifndef QCVALGOPARAMENUMWIDGET_H
#define QCVALGOPARAMENUMWIDGET_H

#include <QWidget>

#include "QcvAlgoParamWidget.h"

namespace Ui {
	class QcvAlgoParamEnumWidget;
}

/**
 * Widget class to view and control a enumerated integer algorithm parameter
 * @author David Roussel
 * @date 2014/05/13
 */
class QcvAlgoParamEnumWidget : public QcvAlgoParamWidget
{
	Q_OBJECT

	public:
		/**
		 * Constructor
		 * @param param the associated parameter
		 * @param direct direct operation: if true indicates that parameter
		 * value setting is performed directly through
		 * param->setIndexValue(...) which is blocking in
		 * multithread environments. If false indicates that parameter value
		 * setting is performed through signal/slot mechanism, which in
		 * multithreaded environments is non blocking with queued connections.
		 * @param parent the parent widget
		 */
		explicit QcvAlgoParamEnumWidget(CvAlgoParam * param,
										const bool direct = true,
										QWidget *parent = 0);
		/**
		 * Destructor.
		 * Clears the UI.
		 */
		virtual ~QcvAlgoParamEnumWidget();

	signals:
		/**
		 * Signal emitted when the parameter value has been changed
		 */
		void parameterUpdated();

		/**
		 * Signal with new index emitted when selected index changes in
		 * the combobox
		 * @param index the new index value in the combobox
		 */
		void parameterUpdated(const int index);

	private slots:
		/**
		 * Slot triggered when combobox item has changed
		 * @param index the new index of the combobox
		 * @note if the parameter is not settable, this method should
		 * (theoretically) never be triggered
		 * @post the integer value correponding to the new index is set
		 * on the parameter and parameterUpdated() signal is emitted.
		 */
		void on_comboBox_currentIndexChanged(int index);

		/**
		 * Slot triggered when reset button is clicked.
		 * @post the default value index is retreived from paramter and set
		 * on the combobox (This implies a call to
		 * on_comboBox_currentIndexChanged())
		 */
		void on_resetButton_clicked();

	private:
		/**
		 * UI from designer
		 */
		Ui::QcvAlgoParamEnumWidget *ui;
};

#endif // QCVALGOPARAMENUMWIDGET_H
