/********************************************************************************
** Form generated from reading UI file 'QcvAlgoParamIntWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCVALGOPARAMINTWIDGET_H
#define UI_QCVALGOPARAMINTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QcvAlgoParamIntWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *spinnerHorizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QPushButton *resetButton;
    QHBoxLayout *sliderHorizontalLayout;
    QSlider *horizontalSlider;

    void setupUi(QWidget *QcvAlgoParamIntWidget)
    {
        if (QcvAlgoParamIntWidget->objectName().isEmpty())
            QcvAlgoParamIntWidget->setObjectName(QStringLiteral("QcvAlgoParamIntWidget"));
        QcvAlgoParamIntWidget->resize(200, 60);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QcvAlgoParamIntWidget->sizePolicy().hasHeightForWidth());
        QcvAlgoParamIntWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(QcvAlgoParamIntWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        spinnerHorizontalLayout = new QHBoxLayout();
        spinnerHorizontalLayout->setSpacing(9);
        spinnerHorizontalLayout->setObjectName(QStringLiteral("spinnerHorizontalLayout"));
        spinnerHorizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(QcvAlgoParamIntWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        spinnerHorizontalLayout->addWidget(label, 0, Qt::AlignLeft|Qt::AlignVCenter);

        spinBox = new QSpinBox(QcvAlgoParamIntWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy1);
        spinBox->setFont(font);
        spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        spinnerHorizontalLayout->addWidget(spinBox, 0, Qt::AlignVCenter);

        resetButton = new QPushButton(QcvAlgoParamIntWidget);
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
#ifndef Q_OS_MAC
        sliderHorizontalLayout->setSpacing(-1);
#endif
        sliderHorizontalLayout->setObjectName(QStringLiteral("sliderHorizontalLayout"));
        sliderHorizontalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalSlider = new QSlider(QcvAlgoParamIntWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        sizePolicy1.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy1);
        horizontalSlider->setOrientation(Qt::Horizontal);

        sliderHorizontalLayout->addWidget(horizontalSlider);


        verticalLayout->addLayout(sliderHorizontalLayout);


        retranslateUi(QcvAlgoParamIntWidget);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

        resetButton->setDefault(false);


        QMetaObject::connectSlotsByName(QcvAlgoParamIntWidget);
    } // setupUi

    void retranslateUi(QWidget *QcvAlgoParamIntWidget)
    {
        QcvAlgoParamIntWidget->setWindowTitle(QApplication::translate("QcvAlgoParamIntWidget", "Form", 0));
        label->setText(QApplication::translate("QcvAlgoParamIntWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class QcvAlgoParamIntWidget: public Ui_QcvAlgoParamIntWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCVALGOPARAMINTWIDGET_H
