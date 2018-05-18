#include <QDebug>

#include "QcvAlgoParam.h"

#include "QcvAlgoParamEnumWidget.h"
#include "ui_QcvAlgoParamEnumWidget.h"

/*
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
QcvAlgoParamEnumWidget::QcvAlgoParamEnumWidget(CvAlgoParam * param,
											   const bool direct,
											   QWidget *parent) :
	QcvAlgoParamWidget(param, direct, parent),
	ui(new Ui::QcvAlgoParamEnumWidget)
{
	ui->setupUi(this);

	assert(parameter->isEnum());

	// Setup title
	ui->label->setText(QString::fromStdString(parameter->getName()));

	// Setup tooltip
	ui->label->setToolTip(QString::fromStdString(parameter->getDescription()));

	// Setup combobox
	ui->comboBox->blockSignals(true);

	vector<string> valueDescriptions = parameter->getValueDescriptions();
	for (size_t i = 0; i < valueDescriptions.size(); i++)
	{
		ui->comboBox->addItem(QString::fromStdString(valueDescriptions[i]),
							  QVariant::fromValue<int>(parameter->getIntValueFromIndex(i)));
	}

	// Set currently selected item
	ui->comboBox->setCurrentIndex(parameter->getValueIndex());
	bool settable = parameter->isSettable();
	if (!settable)
	{
		ui->comboBox->setEnabled(false);
		ui->resetButton->setEnabled(false);
	}

	ui->comboBox->blockSignals(false);

	// Setup connections if no direct operations
	if (!directOp && settable)
	{
		QcvAlgoParam * qParameter = dynamic_cast<QcvAlgoParam *>(parameter);
		if (qParameter != NULL)
		{
			connect(this, SIGNAL(parameterUpdated(int)),
					qParameter, SLOT(setIndexValue(int)));
			connect(this, SIGNAL(parameterReset()),
					qParameter, SLOT(resetToDefaultValue()));
		}
		else
		{
			qDebug() << "QcvAlgoParamEnumWidget unable to convert param"
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
QcvAlgoParamEnumWidget::~QcvAlgoParamEnumWidget()
{
	delete ui;
	// All signals deconnection is performed in ~QcvAlgoParamWidget()
}

/*
 * Slot triggered when combobox item has changed
 * @param index the new index of the combobox
 * @note if the parameter is not settable, this method should
 * (theoretically) never be triggered
 * @post the integer value correponding to the new index is set
 * on the parameter and parameterUpdated() signal is emitted.
 */
void QcvAlgoParamEnumWidget::on_comboBox_currentIndexChanged(int index)
{
	if (directOp)
	{
		parameter->setIntValue(ui->comboBox->itemData(index).toInt());
		// or
		// parameter->setIndexValue(index);
	}
	else
	{
		emit parameterUpdated(index);
	}

	emit parameterUpdated();
}

/*
 * Slot triggered when reset button is clicked.
 * @post the default value index is retreived from paramter and set
 * on the combobox (This implies a call to
 * on_comboBox_currentIndexChanged())
 */
void QcvAlgoParamEnumWidget::on_resetButton_clicked()
{
	int defValIndex = parameter->getValueIndex(CvAlgoParam::DEFAULTVALUE);
	ui->comboBox->blockSignals(true);
	ui->comboBox->setCurrentIndex(defValIndex);
	ui->comboBox->blockSignals(false);

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
