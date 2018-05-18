/********************************************************************************
** Form generated from reading UI file 'QcvAlgoParamConstWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCVALGOPARAMCONSTWIDGET_H
#define UI_QCVALGOPARAMCONSTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QcvAlgoParamConstWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *valueLabel;

    void setupUi(QWidget *QcvAlgoParamConstWidget)
    {
        if (QcvAlgoParamConstWidget->objectName().isEmpty())
            QcvAlgoParamConstWidget->setObjectName(QStringLiteral("QcvAlgoParamConstWidget"));
        QcvAlgoParamConstWidget->resize(200, 30);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QcvAlgoParamConstWidget->sizePolicy().hasHeightForWidth());
        QcvAlgoParamConstWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(QcvAlgoParamConstWidget);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(QcvAlgoParamConstWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        valueLabel = new QLabel(QcvAlgoParamConstWidget);
        valueLabel->setObjectName(QStringLiteral("valueLabel"));
        sizePolicy.setHeightForWidth(valueLabel->sizePolicy().hasHeightForWidth());
        valueLabel->setSizePolicy(sizePolicy);
        valueLabel->setFont(font);

        horizontalLayout->addWidget(valueLabel, 0, Qt::AlignRight);


        retranslateUi(QcvAlgoParamConstWidget);

        QMetaObject::connectSlotsByName(QcvAlgoParamConstWidget);
    } // setupUi

    void retranslateUi(QWidget *QcvAlgoParamConstWidget)
    {
        QcvAlgoParamConstWidget->setWindowTitle(QApplication::translate("QcvAlgoParamConstWidget", "Form", 0));
        label->setText(QApplication::translate("QcvAlgoParamConstWidget", "Title", 0));
        valueLabel->setText(QApplication::translate("QcvAlgoParamConstWidget", "Value", 0));
    } // retranslateUi

};

namespace Ui {
    class QcvAlgoParamConstWidget: public Ui_QcvAlgoParamConstWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCVALGOPARAMCONSTWIDGET_H
