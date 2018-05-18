#ifndef QCVALGOPARAMWIDGET_H
#define QCVALGOPARAMWIDGET_H

#include <QWidget>

#include "CvAlgoParam.h"

/**
 * Common abstract class to all QcvAlgoParamXXX representing the visualisation
 * and interaction widget for a CvAlgoParam.
 * @author David Roussel
 * @date 2014/05/13
 */
class QcvAlgoParamWidget : public QWidget
{
	Q_OBJECT

	public:
		/**
		 * Constructor
		 * @param param the algorithm parameter
		 * @param direct direct operation: if true indicates that parameter
		 * value setting is performed directly through
		 * param->set[Bool|Int|Double]Value(...) which is blocking in
		 * multithread environments. If false indicates that parameter value
		 * setting is performed through signal/slot mechanism, which in
		 * multithreaded environments is non blocking with queued connections.
		 * @param parent the parent widget
		 */
		explicit QcvAlgoParamWidget(CvAlgoParam * param,
									const bool direct,
									QWidget * parent);

		/**
		 * Destructor.
		 * does nothing here but except removing all algorithms from parameter
		 * and clears UI in subclasses.
		 * @post the algorithms associated to this parameter have been released
		 * from this parameter before it is destroyed.
		 */
		virtual ~QcvAlgoParamWidget();

	signals:
		/**
		 * Signal emitted when reset button is clicked in order to reset
		 * parameter to its default value (if it has any)
		 */
		void parameterReset();

		/**
		 * Signal emitted when the parameter value has been changed
		 */
		void parameterUpdated();

	private:
		/**
		 * [Not yet]Slot triggered when reset button is clicked.
		 * @note abstract method is reimplemented in every subclass in order
		 * to reset the algorithm parameter to its default value
		 */
		virtual void on_resetButton_clicked() = 0;

	protected:
		/**
		 * The algorithm parameter to be modified by this widget
		 */
		CvAlgoParam * parameter;

		/**
		 * Indicates if operations should be performed directly on parameter
		 * (if true) or through signal/slot mechanism (if false).
		 */
		bool directOp;
};

#endif // QCVALGOPARAMWIDGET_H
