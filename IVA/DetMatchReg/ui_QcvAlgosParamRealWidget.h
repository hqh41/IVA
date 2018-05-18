/********************************************************************************
** Form generated from reading UI file 'QcvAlgosParamRealWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCVALGOSPARAMREALWIDGET_H
#define UI_QCVALGOSPARAMREALWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QcvAlgosParamRealWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *spinnerHorizontalLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *resetButton;
    QHBoxLayout *sliderHorizontalLayout;
    QSlider *horizontalSlider;

    void setupUi(QWidget *QcvAlgosParamRealWidget)
    {
        if (QcvAlgosParamRealWidget->objectName().isEmpty())
            QcvAlgosParamRealWidget->setObjectName(QStringLiteral("QcvAlgosParamRealWidget"));
        QcvAlgosParamRealWidget->resize(200, 60);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QcvAlgosParamRealWidget->sizePolicy().hasHeightForWidth());
        QcvAlgosParamRealWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(QcvAlgosParamRealWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        spinnerHorizontalLayout = new QHBoxLayout();
        spinnerHorizontalLayout->setSpacing(9);
        spinnerHorizontalLayout->setObjectName(QStringLiteral("spinnerHorizontalLayout"));
        spinnerHorizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(QcvAlgosParamRealWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        spinnerHorizontalLayout->addWidget(label, 0, Qt::AlignLeft|Qt::AlignVCenter);

        doubleSpinBox = new QDoubleSpinBox(QcvAlgosParamRealWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBox->sizePolicy().hasHeightForWidth());
        doubleSpinBox->setSizePolicy(sizePolicy1);
        doubleSpinBox->setFont(font);
        doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        spinnerHorizontalLayout->addWidget(doubleSpinBox, 0, Qt::AlignVCenter);

        resetButton = new QPushButton(QcvAlgosParamRealWidget);
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

        spinnerHorizontalLayout->addWidget(resetButton, 0, Qt::AlignRight|Qt::AlignVCenter);


        verticalLayout->addLayout(spinnerHorizontalLayout);

        sliderHorizontalLayout = new QHBoxLayout();
        sliderHorizontalLayout->setObjectName(QStringLiteral("sliderHorizontalLayout"));
        sliderHorizontalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalSlider = new QSlider(QcvAlgosParamRealWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        sizePolicy1.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy1);
        horizontalSlider->setOrientation(Qt::Horizontal);

        sliderHorizontalLayout->addWidget(horizontalSlider);


        verticalLayout->addLayout(sliderHorizontalLayout);


        retranslateUi(QcvAlgosParamRealWidget);

        resetButton->setDefault(false);


        QMetaObject::connectSlotsByName(QcvAlgosParamRealWidget);
    } // setupUi

    void retranslateUi(QWidget *QcvAlgosParamRealWidget)
    {
        QcvAlgosParamRealWidget->setWindowTitle(QApplication::translate("QcvAlgosParamRealWidget", "Form", 0));
        label->setText(QApplication::translate("QcvAlgosParamRealWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class QcvAlgosParamRealWidget: public Ui_QcvAlgosParamRealWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCVALGOSPARAMREALWIDGET_H
