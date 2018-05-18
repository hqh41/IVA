#include "QcvAlgoParamWidget.h"

/*
 * Constructor
 * @param param the algorithm parameter
 * @param parent teh parent widget
 */
QcvAlgoParamWidget::QcvAlgoParamWidget(CvAlgoParam * param,
									   const bool direct,
									   QWidget *parent) :
	QWidget(parent),
	parameter(param),
	directOp(direct)
{
	assert(parameter != NULL);
}

/*
 * Destructor.
 * does nothing here but except removing all algorithms from parameter
 * and clears UI in subclasses.
 * @post the algorithms associated to this parameter have been released
 * from this parameter before it is destroyed.
 */
QcvAlgoParamWidget::~QcvAlgoParamWidget()
{
	// Disconnect anything still connected to any signal
	// disconnect(this, 0, 0, 0);
	disconnect();

	parameter->removeAllAlgorithms();
}
