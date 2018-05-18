#include <cmath> // for round

#include "QcvAlgoParamConstWidget.h"
#include "ui_QcvAlgoParamConstWidget.h"

/*
 * Constructor
 * @param param the parameter to illustrate
 * @param parent the parent widget
 */
QcvAlgoParamConstWidget::QcvAlgoParamConstWidget(CvAlgoParam * param,
												 QWidget * parent)
	: QcvAlgoParamWidget(param, true, parent),
	  ui(new Ui::QcvAlgoParamConstWidget)
{
	ui->setupUi(this);

	assert(parameter->isConstant());

	// Setup title
	ui->label->setText(QString::fromStdString(parameter->getName()));

	// Setup tooltip
	ui->label->setToolTip(QString::fromStdString(parameter->getDescription()));

	// Setup value label
	switch (parameter->getType())
	{
		case CvAlgoParam::BOOLEAN:
			ui->valueLabel->setText(
				(parameter->getBoolValue() ? "true" : "false"));
			break;
		case CvAlgoParam::INT:
			ui->valueLabel->setText(QString::number(parameter->getIntValue()));
			break;
		case CvAlgoParam::REAL:
		{
			double dStepValue =
				parameter->getDoubleValue(CvAlgoParam::STEPVALUE);
			int precision = 0;
			while (dStepValue != round(dStepValue))
			{
				dStepValue *= 10;
				precision++;
			}
			ui->valueLabel->setText(QString::number(parameter->getDoubleValue(),
													'f', precision));
			break;
		}
		default:
			ui->valueLabel->setText("");
			break;
	}
}

/*
 * Destructor.
 * @note delete the UI
 */
QcvAlgoParamConstWidget::~QcvAlgoParamConstWidget()
{
	delete ui;
}

/*
 * Slot triggered when reset button is clicked.
 * @note Actually this signal is never emitted since there is no
 * reset button in this widget, so implementation is empty
 */
void QcvAlgoParamConstWidget::on_resetButton_clicked()
{
	// Nothing
}

