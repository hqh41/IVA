/********************************************************************************
** Form generated from reading UI file 'QcvAlgoParamEnumWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCVALGOPARAMENUMWIDGET_H
#define UI_QCVALGOPARAMENUMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QcvAlgoParamEnumWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *resetButton;

    void setupUi(QWidget *QcvAlgoParamEnumWidget)
    {
        if (QcvAlgoParamEnumWidget->objectName().isEmpty())
            QcvAlgoParamEnumWidget->setObjectName(QStringLiteral("QcvAlgoParamEnumWidget"));
        QcvAlgoParamEnumWidget->resize(233, 32);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QcvAlgoParamEnumWidget->sizePolicy().hasHeightForWidth());
        QcvAlgoParamEnumWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(QcvAlgoParamEnumWidget);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(QcvAlgoParamEnumWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        horizontalLayout->addWidget(label, 0, Qt::AlignLeft|Qt::AlignVCenter);

        comboBox = new QComboBox(QcvAlgoParamEnumWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setFont(font);

        horizontalLayout->addWidget(comboBox, 0, Qt::AlignVCenter);

        resetButton = new QPushButton(QcvAlgoParamEnumWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(resetButton->sizePolicy().hasHeightForWidth());
        resetButton->setSizePolicy(sizePolicy2);
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


        retranslateUi(QcvAlgoParamEnumWidget);

        resetButton->setDefault(false);


        QMetaObject::connectSlotsByName(QcvAlgoParamEnumWidget);
    } // setupUi

    void retranslateUi(QWidget *QcvAlgoParamEnumWidget)
    {
        QcvAlgoParamEnumWidget->setWindowTitle(QApplication::translate("QcvAlgoParamEnumWidget", "Form", 0));
        label->setText(QApplication::translate("QcvAlgoParamEnumWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class QcvAlgoParamEnumWidget: public Ui_QcvAlgoParamEnumWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCVALGOPARAMENUMWIDGET_H
