/********************************************************************************
** Form generated from reading UI file 'QcvAlgoParamBooleanWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCVALGOPARAMBOOLEANWIDGET_H
#define UI_QCVALGOPARAMBOOLEANWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QcvAlgoParamBooleanWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QPushButton *resetButton;

    void setupUi(QWidget *QcvAlgoParamBooleanWidget)
    {
        if (QcvAlgoParamBooleanWidget->objectName().isEmpty())
            QcvAlgoParamBooleanWidget->setObjectName(QStringLiteral("QcvAlgoParamBooleanWidget"));
        QcvAlgoParamBooleanWidget->resize(200, 23);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QcvAlgoParamBooleanWidget->sizePolicy().hasHeightForWidth());
        QcvAlgoParamBooleanWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(QcvAlgoParamBooleanWidget);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        checkBox = new QCheckBox(QcvAlgoParamBooleanWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        checkBox->setFont(font);

        horizontalLayout->addWidget(checkBox, 0, Qt::AlignLeft|Qt::AlignVCenter);

        resetButton = new QPushButton(QcvAlgoParamBooleanWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(resetButton->sizePolicy().hasHeightForWidth());
        resetButton->setSizePolicy(sizePolicy1);
        resetButton->setMaximumSize(QSize(20, 20));
        resetButton->setFont(font);
        resetButton->setText(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/rotate-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetButton->setIcon(icon);
        resetButton->setShortcut(QStringLiteral(""));
        resetButton->setAutoDefault(false);
        resetButton->setFlat(false);

        horizontalLayout->addWidget(resetButton, 0, Qt::AlignRight|Qt::AlignVCenter);


        retranslateUi(QcvAlgoParamBooleanWidget);

        resetButton->setDefault(false);


        QMetaObject::connectSlotsByName(QcvAlgoParamBooleanWidget);
    } // setupUi

    void retranslateUi(QWidget *QcvAlgoParamBooleanWidget)
    {
        QcvAlgoParamBooleanWidget->setWindowTitle(QApplication::translate("QcvAlgoParamBooleanWidget", "Form", 0));
        checkBox->setText(QApplication::translate("QcvAlgoParamBooleanWidget", "CheckBox", 0));
    } // retranslateUi

};

namespace Ui {
    class QcvAlgoParamBooleanWidget: public Ui_QcvAlgoParamBooleanWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCVALGOPARAMBOOLEANWIDGET_H
