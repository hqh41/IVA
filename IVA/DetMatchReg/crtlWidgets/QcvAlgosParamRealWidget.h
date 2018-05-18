#ifndef QCVALGOSPARAMREALWIDGET_H
#define QCVALGOSPARAMREALWIDGET_H

#include <QWidget>

#include "QcvAlgoParamWidget.h"

namespace Ui {
	class QcvAlgosParamRealWidget;
}

/**
 * Widget class to view and control an real number algorithm parameter
 * @author David Roussel
 * @date 2014/05/13
 */
class QcvAlgosParamRealWidget : public QcvAlgoParamWidget
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
		 * param->setDoubleValue(...) which is blocking in
		 * multithread environments. If false indicates that parameter value
		 * setting is performed through signal/slot mechanism, which in
		 * multithreaded environments is non blocking with queued connections.
		 * @param parent the parent widget
		 */
		explicit QcvAlgosParamRealWidget(CvAlgoParam * param,
										 const bool slider = true,
										 const bool direct = false,
										 QWidget *parent = 0);
		/**
		 * Destructor.
		 * Clears the UI.
		 */
		virtual ~QcvAlgosParamRealWidget();

	signals:
		/**
		 * Signal emitted when the parameter value has been changed
		 */
		void parameterUpdated();

		/**
		 * Signal with double value emitted when double value changes
		 * @param value the new double value
		 */
		void parameterUpdated(const double value);

	private slots:
		/**
		 * Slot triggered when doubleSpinBox value changes
		 * @note if the parameter is not settable, this method should
		 * (theoretically) never be triggered
		 * @param dvalue the new double value
		 */
		void on_doubleSpinBox_valueChanged(double dvalue);

		/**
		 * Slot triggered when the Slider (integer) value changes
		 * @note if the parameter is not settable, this method should
		 * (theoretically) never be triggered
		 * @param ivalue the new slider value
		 */
		void on_horizontalSlider_valueChanged(int ivalue);

		/**
		 * Slot triggered when reset button is clicked.
		 * @post default value is retreived from parameter and spinbox
		 * value is changed to this value (this implies a call to
		 * on_doubleSpinBox_valueChanged())
		 */
		void on_resetButton_clicked();

	private:
		/**
		 * UI from designer
		 */
		Ui::QcvAlgosParamRealWidget *ui;

		/**
		 * Indicate if slider hould be used or removed
		 */
		bool slider;

		/**
		 * Convert value of double spin box to integer slider
		 * @param min minimum value of the double spin box
		 * @param step step value of the double spin box
		 * @param value current value of the double spin box or max value to
		 * obtain integer slider max value
		 * @return the integer value to set on the integer slider
		 */
		static int double2intValue(const double min,
								   const double step,
								   const double value);

		/**
		 * Convert integer value from slider to double value of double spin box
		 * @param dmin the minimum double value of the spin box
		 * @param dstep the step value of the double spin box
		 * @param ivalue the integer value of the integer slider
		 * @return the value of the double spin box
		 */
		static double int2doubleValue(const double dmin,
									  const double dstep,
									  const int ivalue);
};

#endif // QCVALGOSPARAMREAL_H
