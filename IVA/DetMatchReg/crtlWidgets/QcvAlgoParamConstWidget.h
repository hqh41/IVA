#ifndef QCVALGOPARAMCONSTWIDGET_H
#define QCVALGOPARAMCONSTWIDGET_H

//#include "ParamAlgos.h"
#include "QcvAlgoParamWidget.h"
#include <QWidget>

namespace Ui {
	class QcvAlgoParamConstWidget;
}

/**
 * Widget clas to view (only) a constant parameter.
 * Constant parameters can not be changed
 * @author David Roussel
 * @date 2014/05/14
 */
class QcvAlgoParamConstWidget : public QcvAlgoParamWidget
{
	Q_OBJECT

	public:
		/**
		 * Constructor
		 * @param param the parameter to illustrate
		 * @param parent the parent widget
		 */
		explicit QcvAlgoParamConstWidget(CvAlgoParam * param,
								   QWidget *parent = 0);

		/**
		 * Destructor.
		 * @note delete the UI
		 */
		virtual ~QcvAlgoParamConstWidget();

	private:
		/**
		 * [Not yet]Slot triggered when reset button is clicked.
		 * @note Actually this [pseudo]slot is never triggered since there is no
		 * reset button in this widget, so implementation is empty
		 */
		void on_resetButton_clicked();

	private:
		/**
		 * The UI part of the widget
		 */
		Ui::QcvAlgoParamConstWidget *ui;
};

#endif // QCVALGOPARAMCONSTWIDGET_H
