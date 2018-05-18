#include <cmath>	// for round

#include <QDebug>

#include "QcvAlgoParam.h"

#include "QcvAlgosParamRealWidget.h"
#include "ui_QcvAlgosParamRealWidget.h"

/*
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
QcvAlgosParamRealWidget::QcvAlgosParamRealWidget(CvAlgoParam * param,
												 const bool slider,
												 const bool direct,
												 QWidget *parent) :
	QcvAlgoParamWidget(param, direct, parent),
	ui(new Ui::QcvAlgosParamRealWidget),
	slider(slider)
{
	ui->setupUi(this);

	assert(parameter->getType() == CvAlgoParam::REAL);

	// Setup title
	ui->label->setText(QString::fromStdString(parameter->getName()));

	// Setup tooltip
	ui->label->setToolTip(QString::fromStdString(parameter->getDescription()));

	// Setup QDoubleSpinBox
	ui->doubleSpinBox->blockSignals(true);

	double minValue = parameter->getDoubleValue(CvAlgoParam::MINVALUE);
	double maxValue = parameter->getDoubleValue(CvAlgoParam::MAXVALUE);
	ui->doubleSpinBox->setRange(minValue,maxValue);

	double stepValue = parameter->getDoubleValue(CvAlgoParam::STEPVALUE);
	ui->doubleSpinBox->setSingleStep(stepValue);

	double stepIncrement = stepValue;
	int nbDecimals = 0;
	while (stepIncrement != round(stepIncrement))
	{
		stepIncrement *= 10;
		nbDecimals++;
	}
	ui->doubleSpinBox->setDecimals(nbDecimals);

	double value = parameter->getDoubleValue(CvAlgoParam::VALUE);
	ui->doubleSpinBox->setValue(value);

	bool settable = parameter->isSettable();
	if (!settable)
	{
		ui->doubleSpinBox->setEnabled(false);
		ui->resetButton->setEnabled(false);
	}

	ui->doubleSpinBox->blockSignals(false);

	if (slider)
	{
		// Setup QSlider
		ui->horizontalSlider->blockSignals(true);

		ui->horizontalSlider->setMinimum(0);
		ui->horizontalSlider->setMaximum(double2intValue(minValue,
														 stepValue,
														 maxValue));
		ui->horizontalSlider->setSingleStep(1);

		ui->horizontalSlider->setValue(double2intValue(minValue,
													   stepValue,
													   value));
		if (!settable)
		{
			ui->horizontalSlider->setEnabled(false);
		}
		ui->horizontalSlider->blockSignals(false);
	}
	else
	{
		// delete QSlider
		ui->sliderHorizontalLayout->removeWidget(ui->horizontalSlider);
		ui->horizontalSlider->setParent(NULL);
		ui->horizontalSlider->deleteLater();
	}

	// Setup connections if no direct operations
	if (!directOp)
	{
		QcvAlgoParam * qParameter = dynamic_cast<QcvAlgoParam *>(parameter);
		if (qParameter != NULL)
		{
			connect(this, SIGNAL(parameterUpdated(double)),
					qParameter, SLOT(setDoubleValue(double)));
			connect(this, SIGNAL(parameterReset()),
					qParameter, SLOT(resetToDefaultValue()));
		}
		else
		{
			qDebug() << "QcvAlgoParamRealWidget unable to convert param"
					 << parameter->getName().c_str()
					 << "to Qt flavored param with signals/slots";
			directOp = true;
		}
	}
}

/*
 * Destructor.
 * Clears the UI.
 */
QcvAlgosParamRealWidget::~QcvAlgosParamRealWidget()
{
	delete ui;
	// All signals deconnection is performed in ~QcvAlgoParamWidget()
}

/*
 * Slot triggered when doubleSpinBox value changes
 * @note if the parameter is not settable, this method should
 * (theoretically) never be triggered
 * @param dvalue the new double value
 */
void QcvAlgosParamRealWidget::on_doubleSpinBox_valueChanged(double dvalue)
{
	int iValue = double2intValue(ui->doubleSpinBox->minimum(),
								 ui->doubleSpinBox->singleStep(),
								 dvalue);

	if (slider)
	{
		ui->horizontalSlider->blockSignals(true);
		ui->horizontalSlider->setValue(iValue);
		ui->horizontalSlider->blockSignals(false);
	}

	if (directOp)
	{
		parameter->setDoubleValue(dvalue);
	}
	else
	{
		emit(parameterUpdated(dvalue));
	}

	emit(parameterUpdated());
}

/*
 * Slot triggered when the Slider (integer) value changes
 * @note if the parameter is not settable, this method should
 * (theoretically) never be triggered
 * @param ivalue the new slider value
 */
void QcvAlgosParamRealWidget::on_horizontalSlider_valueChanged(int ivalue)
{
	double dvalue = int2doubleValue(ui->doubleSpinBox->minimum(),
									ui->doubleSpinBox->singleStep(),
									ivalue);

	ui->doubleSpinBox->blockSignals(true);
	ui->doubleSpinBox->setValue(dvalue);
	ui->doubleSpinBox->blockSignals(false);

	if (directOp)
	{
		parameter->setDoubleValue(dvalue);
	}
	else
	{
		emit(parameterUpdated(dvalue));
	}

	emit(parameterUpdated());
}

/*
 * Slot triggered when reset button is clicked.
 * @post default value is retreived from parameter and spinbox
 * value is changed to this value (this implies a call to
 * on_doubleSpinBox_valueChanged())
 */
void QcvAlgosParamRealWidget::on_resetButton_clicked()
{
	double dValue = parameter->getDoubleValue(CvAlgoParam::DEFAULTVALUE);

	ui->doubleSpinBox->blockSignals(true);
	ui->doubleSpinBox->setValue(dValue); // will trigger on_doubleSpinBox_valueChanged
	ui->doubleSpinBox->blockSignals(false);

	if (slider)
	{
		int iValue = double2intValue(ui->doubleSpinBox->minimum(),
									 ui->doubleSpinBox->singleStep(),
									 dValue);
		ui->horizontalSlider->blockSignals(true);
		ui->horizontalSlider->setValue(iValue);
		ui->horizontalSlider->blockSignals(false);
	}

	if (directOp)
	{
		parameter->resetToDefaultValue();
	}
	else
	{
		emit parameterReset();
	}

	emit parameterUpdated();

}

/*
 * Convert value of double spin box to integer slider
 * @param min minimum value of the double spin box
 * @param step step value of the double spin box
 * @param value current value of the double spin box or max value to obtain
 * integer slider max value
 * @return the integer value to set on the integer slider
 */
int QcvAlgosParamRealWidget::double2intValue(const double min,
									   const double step,
									   const double value)
{
	return (int)((value - min)/step)+1;
}

/*
 * Convert integer value from slider to double value of double spin box
 * @param dmin the minimum double value of the spin box
 * @param dstep the step value of the double spin box
 * @param ivalue the integer value of the integer slider
 * @return the value of the double spin box
 */
double QcvAlgosParamRealWidget::int2doubleValue(const double dmin,
										  const double dstep,
										  const int ivalue)
{
	return (dmin + ((double)ivalue * dstep));
}
