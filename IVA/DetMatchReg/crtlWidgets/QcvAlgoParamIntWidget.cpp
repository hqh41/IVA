#include <QDebug>

#include "QcvAlgoParam.h"

#include "QcvAlgoParamIntWidget.h"
#include "ui_QcvAlgoParamIntWidget.h"

/*
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
QcvAlgoParamIntWidget::QcvAlgoParamIntWidget(CvAlgoParam * param,
											 const bool slider,
											 const bool direct,
											 QWidget *parent) :
	QcvAlgoParamWidget(param, direct, parent),
	ui(new Ui::QcvAlgoParamIntWidget),
	slider(slider)
{
	ui->setupUi(this);

	assert(parameter->getType() == CvAlgoParam::INT);
	assert(parameter->getStepMode() != CvAlgoParam::MUL);

	// Setup title
	ui->label->setText(QString::fromStdString(parameter->getName()));

	// Setup tooltip
	ui->label->setToolTip(QString::fromStdString(parameter->getDescription()));

	// Setup QSpinBox
	ui->spinBox->blockSignals(true);

	ui->spinBox->setRange(parameter->getIntValue(CvAlgoParam::MINVALUE),
						  parameter->getIntValue(CvAlgoParam::MAXVALUE));
	ui->spinBox->setSingleStep(parameter->getIntValue(CvAlgoParam::STEPVALUE));

	ui->spinBox->setValue(parameter->getIntValue());
	bool settable = parameter->isSettable();
	if (!settable)
	{
		ui->spinBox->setEnabled(false);
	}

	ui->spinBox->blockSignals(false);

	if (slider)
	{
		// Setup QSlider
		ui->horizontalSlider->blockSignals(true);

		ui->horizontalSlider->setRange(parameter->getIntValue(CvAlgoParam::MINVALUE),
									   parameter->getIntValue(CvAlgoParam::MAXVALUE));
		ui->horizontalSlider->setSingleStep(parameter->getIntValue(CvAlgoParam::STEPVALUE));

		ui->horizontalSlider->setValue(parameter->getIntValue());

		if (!settable)
		{
			ui->horizontalSlider->setEnabled(false);
			ui->resetButton->setEnabled(false);
		}

		ui->horizontalSlider->blockSignals(false);
	}
	else
	{
		// Disconnect ui->spinBox <--> ui->horizontalSlider connections
		disconnect(ui->spinBox, SIGNAL(valueChanged(int)),
				   ui->horizontalSlider, SLOT(setValue(int)));
		disconnect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
				   ui->spinBox, SLOT(setValue(int)));

		// Delete slider
		ui->sliderHorizontalLayout->removeWidget(ui->horizontalSlider);
		ui->horizontalSlider->setParent(NULL);
		ui->horizontalSlider->deleteLater();
	}

	// Setup connections if no direct operations
	if (!directOp && settable)
	{
		QcvAlgoParam * qParameter = dynamic_cast<QcvAlgoParam *>(parameter);
		if (qParameter != NULL)
		{
			connect(this, SIGNAL(parameterUpdated(int)),
					qParameter, SLOT(setIntValue(int)));
			connect(this, SIGNAL(parameterReset()),
					qParameter, SLOT(resetToDefaultValue()));
		}
		else
		{
			qDebug() << "QcvAlgoParamIntWidget unable to convert param"
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
QcvAlgoParamIntWidget::~QcvAlgoParamIntWidget()
{
	delete ui;
	// All signals deconnection is performed in ~QcvAlgoParamWidget()
}

/*
 * Slot triggered when the spinbox value changes
 * @param value the new spinbox value
 * @note if the parameter is not settable, this method should
 * (theoretically) never be triggered
 * @post the associated parameter is set to this value and
 * parameterUpdated() signal is emitted
 */
void QcvAlgoParamIntWidget::on_spinBox_valueChanged(int value)
{
	if (directOp)
	{
		parameter->setIntValue(value);
	}
	else
	{
		emit(parameterUpdated(value));
	}

	emit(parameterUpdated());
}

/*
 * Slot triggered when reset button is clicked.
 * @post default value is retreived from parameter and spinbox
 * value is changed to this value (this implies a call to
 * on_spinBox_valueChanged())
 */
void QcvAlgoParamIntWidget::on_resetButton_clicked()
{
	int iValue = parameter->getIntValue(CvAlgoParam::DEFAULTVALUE);
	ui->spinBox->blockSignals(true);
	ui->spinBox->setValue(iValue); // will trigger on_spinBox_valueChanged (if signals aren't blocked)
	ui->spinBox->blockSignals(false);

	if (slider)
	{
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

	emit(parameterUpdated());
}
