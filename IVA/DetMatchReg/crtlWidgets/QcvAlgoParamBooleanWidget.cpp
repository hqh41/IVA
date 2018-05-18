#include <QDebug>

#include "QcvAlgoParam.h"

#include "QcvAlgoParamBooleanWidget.h"
#include "ui_QcvAlgoParamBooleanWidget.h"

/*
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
QcvAlgoParamBooleanWidget::QcvAlgoParamBooleanWidget(CvAlgoParam * param,
													 const bool direct,
													 QWidget *parent) :
	QcvAlgoParamWidget(param, direct, parent),
	ui(new Ui::QcvAlgoParamBooleanWidget)
{
	ui->setupUi(this);

	assert(parameter->getType() == CvAlgoParam::BOOLEAN);

	// Setup title
	ui->checkBox->setText(QString::fromStdString(parameter->getName()));

	// Setup tooltip
	ui->checkBox->setToolTip(QString::fromStdString(parameter->getDescription()));

	// Set current state
	ui->checkBox->blockSignals(true);
	ui->checkBox->setChecked(parameter->getBoolValue());
	bool settable = parameter->isSettable();
	if (!settable)
	{
		ui->checkBox->setEnabled(false);
		ui->resetButton->setEnabled(false);
	}
	ui->checkBox->blockSignals(false);

	// Setup connections if no direct operations
	if (!directOp && settable)
	{
		QcvAlgoParam * qParameter = dynamic_cast<QcvAlgoParam *>(parameter);
		if (qParameter != NULL)
		{
			connect(this, SIGNAL(parameterUpdated(bool)),
					qParameter, SLOT(setBoolValue(bool)));
			connect(this, SIGNAL(parameterReset()),
					qParameter, SLOT(resetToDefaultValue()));
		}
		else
		{
			qDebug() << "QcvAlgoParamBooleanWidget unable to convert param "
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
QcvAlgoParamBooleanWidget::~QcvAlgoParamBooleanWidget()
{
	delete ui;
	// All signals deconnection is performed in ~QcvAlgoParamWidget()
}

/*
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
void QcvAlgoParamBooleanWidget::on_checkBox_stateChanged(int value)
{
	bool booleanValue = parameter->getBoolValue();

	switch (value)
	{
		case Qt::Unchecked:
		case Qt::PartiallyChecked:
			booleanValue = false;
			break;
		case Qt::Checked:
			booleanValue = true;
			break;
		default:
			break;
	}

	if (directOp)
	{
		parameter->setBoolValue(booleanValue);
	}
	else
	{
		emit parameterUpdated(booleanValue);
	}

	emit parameterUpdated();
}

/*
 * Slot triggered when the reset button is clicked in order to reset
 * the value to its default (if it has one)
 * @post default value is retrieved from parameter and applied to
 * checkbox (this imples another call to on_checkBox_stateChanged()).
 */
void QcvAlgoParamBooleanWidget::on_resetButton_clicked()
{
	bool dValue = parameter->getBoolValue(CvAlgoParam::DEFAULTVALUE);

	ui->checkBox->blockSignals(true);
	ui->checkBox->setChecked(dValue);
	ui->checkBox->blockSignals(false);

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
