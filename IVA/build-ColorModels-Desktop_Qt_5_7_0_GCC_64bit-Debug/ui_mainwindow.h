/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QcvMatWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCamera_0;
    QAction *actionCamera_1;
    QAction *actionFile;
    QAction *actionFlip;
    QAction *actionOriginalSize;
    QAction *actionConstrainedSize;
    QAction *actionQuit;
    QAction *actionRenderImage;
    QAction *actionRenderPixmap;
    QAction *actionRenderOpenGL;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QcvMatWidget *widgetImage;
    QTabWidget *tabWidget;
    QWidget *sizeTab;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonOrigSize;
    QRadioButton *radioButtonCustomSize;
    QLabel *labelWidth;
    QSpinBox *spinBoxWidth;
    QLabel *labelHeight;
    QSpinBox *spinBoxHeight;
    QCheckBox *checkBoxFlip;
    QSpacerItem *verticalSpacer;
    QWidget *colorTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *displayBox;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButtonInput;
    QRadioButton *radioButtonGray;
    QRadioButton *radioButtonRed;
    QRadioButton *radioButtonGreen;
    QRadioButton *radioButtonBlue;
    QRadioButton *radioButtonMaxBGR;
    QRadioButton *radioButtonXYZ_X;
    QRadioButton *radioButtonXYZ_Y;
    QRadioButton *radioButtonXYZ_Z;
    QRadioButton *radioButtonHue;
    QRadioButton *radioButtonSaturation;
    QRadioButton *radioButtonValue;
    QRadioButton *radioButtonY;
    QRadioButton *radioButtonCr;
    QRadioButton *radioButtonCb;
    QGroupBox *channelBox;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButtonChColor;
    QRadioButton *radioButtonChGray;
    QGroupBox *hueBox;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioButtonMixHue;
    QRadioButton *radioButtonMixHueSat;
    QRadioButton *radioButtonMixHueVal;
    QVBoxLayout *processTimeLayout;
    QLabel *labelProcessTime;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelProcessTimeValue;
    QLabel *labelPM;
    QLabel *labelProcessTimeStd;
    QLabel *labelTimeUnit;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuSources;
    QMenu *menuVideo;
    QMenu *menuSize;
    QMenu *menuRender;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(650, 585);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        actionCamera_0 = new QAction(MainWindow);
        actionCamera_0->setObjectName(QStringLiteral("actionCamera_0"));
        actionCamera_1 = new QAction(MainWindow);
        actionCamera_1->setObjectName(QStringLiteral("actionCamera_1"));
        actionFile = new QAction(MainWindow);
        actionFile->setObjectName(QStringLiteral("actionFile"));
        actionFlip = new QAction(MainWindow);
        actionFlip->setObjectName(QStringLiteral("actionFlip"));
        actionFlip->setCheckable(true);
        actionOriginalSize = new QAction(MainWindow);
        actionOriginalSize->setObjectName(QStringLiteral("actionOriginalSize"));
        actionOriginalSize->setCheckable(true);
        actionConstrainedSize = new QAction(MainWindow);
        actionConstrainedSize->setObjectName(QStringLiteral("actionConstrainedSize"));
        actionConstrainedSize->setCheckable(true);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionRenderImage = new QAction(MainWindow);
        actionRenderImage->setObjectName(QStringLiteral("actionRenderImage"));
        actionRenderImage->setCheckable(true);
        actionRenderImage->setChecked(true);
        actionRenderPixmap = new QAction(MainWindow);
        actionRenderPixmap->setObjectName(QStringLiteral("actionRenderPixmap"));
        actionRenderPixmap->setCheckable(true);
        actionRenderOpenGL = new QAction(MainWindow);
        actionRenderOpenGL->setObjectName(QStringLiteral("actionRenderOpenGL"));
        actionRenderOpenGL->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 0, 6, 0);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        widgetImage = new QcvMatWidget();
        widgetImage->setObjectName(QStringLiteral("widgetImage"));
        widgetImage->setGeometry(QRect(0, 0, 463, 534));
        scrollArea->setWidget(widgetImage);

        horizontalLayout->addWidget(scrollArea);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setUsesScrollButtons(false);
        sizeTab = new QWidget();
        sizeTab->setObjectName(QStringLiteral("sizeTab"));
        verticalLayout = new QVBoxLayout(sizeTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(8, 8, 8, 8);
        radioButtonOrigSize = new QRadioButton(sizeTab);
        radioButtonOrigSize->setObjectName(QStringLiteral("radioButtonOrigSize"));
        radioButtonOrigSize->setChecked(true);

        verticalLayout->addWidget(radioButtonOrigSize);

        radioButtonCustomSize = new QRadioButton(sizeTab);
        radioButtonCustomSize->setObjectName(QStringLiteral("radioButtonCustomSize"));

        verticalLayout->addWidget(radioButtonCustomSize);

        labelWidth = new QLabel(sizeTab);
        labelWidth->setObjectName(QStringLiteral("labelWidth"));

        verticalLayout->addWidget(labelWidth);

        spinBoxWidth = new QSpinBox(sizeTab);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMaximum(1600);
        spinBoxWidth->setSingleStep(4);

        verticalLayout->addWidget(spinBoxWidth);

        labelHeight = new QLabel(sizeTab);
        labelHeight->setObjectName(QStringLiteral("labelHeight"));

        verticalLayout->addWidget(labelHeight);

        spinBoxHeight = new QSpinBox(sizeTab);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMaximum(1200);
        spinBoxHeight->setSingleStep(4);

        verticalLayout->addWidget(spinBoxHeight);

        checkBoxFlip = new QCheckBox(sizeTab);
        checkBoxFlip->setObjectName(QStringLiteral("checkBoxFlip"));

        verticalLayout->addWidget(checkBoxFlip);

        verticalSpacer = new QSpacerItem(20, 228, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(sizeTab, QString());
        colorTab = new QWidget();
        colorTab->setObjectName(QStringLiteral("colorTab"));
        verticalLayout_2 = new QVBoxLayout(colorTab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(8, 8, 8, 8);
        displayBox = new QGroupBox(colorTab);
        displayBox->setObjectName(QStringLiteral("displayBox"));
        verticalLayout_3 = new QVBoxLayout(displayBox);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(8, 8, 8, 8);
        radioButtonInput = new QRadioButton(displayBox);
        radioButtonInput->setObjectName(QStringLiteral("radioButtonInput"));
        radioButtonInput->setChecked(true);

        verticalLayout_3->addWidget(radioButtonInput);

        radioButtonGray = new QRadioButton(displayBox);
        radioButtonGray->setObjectName(QStringLiteral("radioButtonGray"));

        verticalLayout_3->addWidget(radioButtonGray);

        radioButtonRed = new QRadioButton(displayBox);
        radioButtonRed->setObjectName(QStringLiteral("radioButtonRed"));

        verticalLayout_3->addWidget(radioButtonRed);

        radioButtonGreen = new QRadioButton(displayBox);
        radioButtonGreen->setObjectName(QStringLiteral("radioButtonGreen"));

        verticalLayout_3->addWidget(radioButtonGreen);

        radioButtonBlue = new QRadioButton(displayBox);
        radioButtonBlue->setObjectName(QStringLiteral("radioButtonBlue"));

        verticalLayout_3->addWidget(radioButtonBlue);

        radioButtonMaxBGR = new QRadioButton(displayBox);
        radioButtonMaxBGR->setObjectName(QStringLiteral("radioButtonMaxBGR"));

        verticalLayout_3->addWidget(radioButtonMaxBGR);

        radioButtonXYZ_X = new QRadioButton(displayBox);
        radioButtonXYZ_X->setObjectName(QStringLiteral("radioButtonXYZ_X"));

        verticalLayout_3->addWidget(radioButtonXYZ_X);

        radioButtonXYZ_Y = new QRadioButton(displayBox);
        radioButtonXYZ_Y->setObjectName(QStringLiteral("radioButtonXYZ_Y"));

        verticalLayout_3->addWidget(radioButtonXYZ_Y);

        radioButtonXYZ_Z = new QRadioButton(displayBox);
        radioButtonXYZ_Z->setObjectName(QStringLiteral("radioButtonXYZ_Z"));

        verticalLayout_3->addWidget(radioButtonXYZ_Z);

        radioButtonHue = new QRadioButton(displayBox);
        radioButtonHue->setObjectName(QStringLiteral("radioButtonHue"));

        verticalLayout_3->addWidget(radioButtonHue);

        radioButtonSaturation = new QRadioButton(displayBox);
        radioButtonSaturation->setObjectName(QStringLiteral("radioButtonSaturation"));

        verticalLayout_3->addWidget(radioButtonSaturation);

        radioButtonValue = new QRadioButton(displayBox);
        radioButtonValue->setObjectName(QStringLiteral("radioButtonValue"));

        verticalLayout_3->addWidget(radioButtonValue);

        radioButtonY = new QRadioButton(displayBox);
        radioButtonY->setObjectName(QStringLiteral("radioButtonY"));

        verticalLayout_3->addWidget(radioButtonY);

        radioButtonCr = new QRadioButton(displayBox);
        radioButtonCr->setObjectName(QStringLiteral("radioButtonCr"));

        verticalLayout_3->addWidget(radioButtonCr);

        radioButtonCb = new QRadioButton(displayBox);
        radioButtonCb->setObjectName(QStringLiteral("radioButtonCb"));

        verticalLayout_3->addWidget(radioButtonCb);


        verticalLayout_2->addWidget(displayBox);

        channelBox = new QGroupBox(colorTab);
        channelBox->setObjectName(QStringLiteral("channelBox"));
        verticalLayout_4 = new QVBoxLayout(channelBox);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(8, 8, 8, 8);
        radioButtonChColor = new QRadioButton(channelBox);
        radioButtonChColor->setObjectName(QStringLiteral("radioButtonChColor"));
        radioButtonChColor->setChecked(true);

        verticalLayout_4->addWidget(radioButtonChColor);

        radioButtonChGray = new QRadioButton(channelBox);
        radioButtonChGray->setObjectName(QStringLiteral("radioButtonChGray"));

        verticalLayout_4->addWidget(radioButtonChGray);


        verticalLayout_2->addWidget(channelBox);

        hueBox = new QGroupBox(colorTab);
        hueBox->setObjectName(QStringLiteral("hueBox"));
        verticalLayout_5 = new QVBoxLayout(hueBox);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(8, 8, 8, 8);
        radioButtonMixHue = new QRadioButton(hueBox);
        radioButtonMixHue->setObjectName(QStringLiteral("radioButtonMixHue"));
        radioButtonMixHue->setChecked(true);

        verticalLayout_5->addWidget(radioButtonMixHue);

        radioButtonMixHueSat = new QRadioButton(hueBox);
        radioButtonMixHueSat->setObjectName(QStringLiteral("radioButtonMixHueSat"));

        verticalLayout_5->addWidget(radioButtonMixHueSat);

        radioButtonMixHueVal = new QRadioButton(hueBox);
        radioButtonMixHueVal->setObjectName(QStringLiteral("radioButtonMixHueVal"));

        verticalLayout_5->addWidget(radioButtonMixHueVal);


        verticalLayout_2->addWidget(hueBox);

        processTimeLayout = new QVBoxLayout();
        processTimeLayout->setSpacing(1);
        processTimeLayout->setObjectName(QStringLiteral("processTimeLayout"));
        labelProcessTime = new QLabel(colorTab);
        labelProcessTime->setObjectName(QStringLiteral("labelProcessTime"));
        QFont font;
        font.setPointSize(10);
        labelProcessTime->setFont(font);

        processTimeLayout->addWidget(labelProcessTime);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelProcessTimeValue = new QLabel(colorTab);
        labelProcessTimeValue->setObjectName(QStringLiteral("labelProcessTimeValue"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelProcessTimeValue->sizePolicy().hasHeightForWidth());
        labelProcessTimeValue->setSizePolicy(sizePolicy2);
        labelProcessTimeValue->setFont(font);
        labelProcessTimeValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(labelProcessTimeValue);

        labelPM = new QLabel(colorTab);
        labelPM->setObjectName(QStringLiteral("labelPM"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelPM->sizePolicy().hasHeightForWidth());
        labelPM->setSizePolicy(sizePolicy3);
        labelPM->setFont(font);
        labelPM->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labelPM);

        labelProcessTimeStd = new QLabel(colorTab);
        labelProcessTimeStd->setObjectName(QStringLiteral("labelProcessTimeStd"));
        sizePolicy2.setHeightForWidth(labelProcessTimeStd->sizePolicy().hasHeightForWidth());
        labelProcessTimeStd->setSizePolicy(sizePolicy2);
        labelProcessTimeStd->setFont(font);
        labelProcessTimeStd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(labelProcessTimeStd);

        labelTimeUnit = new QLabel(colorTab);
        labelTimeUnit->setObjectName(QStringLiteral("labelTimeUnit"));
        sizePolicy3.setHeightForWidth(labelTimeUnit->sizePolicy().hasHeightForWidth());
        labelTimeUnit->setSizePolicy(sizePolicy3);
        labelTimeUnit->setFont(font);
        labelTimeUnit->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labelTimeUnit);


        processTimeLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(processTimeLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        tabWidget->addTab(colorTab, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 22));
        menuSources = new QMenu(menuBar);
        menuSources->setObjectName(QStringLiteral("menuSources"));
        menuVideo = new QMenu(menuBar);
        menuVideo->setObjectName(QStringLiteral("menuVideo"));
        menuSize = new QMenu(menuVideo);
        menuSize->setObjectName(QStringLiteral("menuSize"));
        menuRender = new QMenu(menuBar);
        menuRender->setObjectName(QStringLiteral("menuRender"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSources->menuAction());
        menuBar->addAction(menuVideo->menuAction());
        menuBar->addAction(menuRender->menuAction());
        menuSources->addAction(actionCamera_0);
        menuSources->addAction(actionCamera_1);
        menuSources->addAction(actionFile);
        menuSources->addSeparator();
        menuSources->addAction(actionQuit);
        menuVideo->addAction(actionFlip);
        menuVideo->addSeparator();
        menuVideo->addAction(menuSize->menuAction());
        menuSize->addAction(actionOriginalSize);
        menuSize->addAction(actionConstrainedSize);
        menuRender->addAction(actionRenderImage);
        menuRender->addAction(actionRenderPixmap);
        menuRender->addAction(actionRenderOpenGL);

        retranslateUi(MainWindow);
        QObject::connect(radioButtonCustomSize, SIGNAL(clicked(bool)), actionConstrainedSize, SLOT(setChecked(bool)));
        QObject::connect(actionConstrainedSize, SIGNAL(triggered(bool)), radioButtonCustomSize, SLOT(setChecked(bool)));
        QObject::connect(radioButtonOrigSize, SIGNAL(clicked(bool)), actionOriginalSize, SLOT(setChecked(bool)));
        QObject::connect(actionOriginalSize, SIGNAL(triggered(bool)), radioButtonOrigSize, SLOT(setChecked(bool)));
        QObject::connect(checkBoxFlip, SIGNAL(clicked(bool)), actionFlip, SLOT(setChecked(bool)));
        QObject::connect(actionFlip, SIGNAL(triggered(bool)), checkBoxFlip, SLOT(setChecked(bool)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Color spaces", 0));
        actionCamera_0->setText(QApplication::translate("MainWindow", "Camera 0", 0));
#ifndef QT_NO_TOOLTIP
        actionCamera_0->setToolTip(QApplication::translate("MainWindow", "cam\303\251ra interne", 0));
#endif // QT_NO_TOOLTIP
        actionCamera_0->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+0", 0));
        actionCamera_1->setText(QApplication::translate("MainWindow", "Camera 1", 0));
#ifndef QT_NO_TOOLTIP
        actionCamera_1->setToolTip(QApplication::translate("MainWindow", "cam\303\251ra externe", 0));
#endif // QT_NO_TOOLTIP
        actionCamera_1->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+1", 0));
        actionFile->setText(QApplication::translate("MainWindow", "File", 0));
#ifndef QT_NO_TOOLTIP
        actionFile->setToolTip(QApplication::translate("MainWindow", "fichier video", 0));
#endif // QT_NO_TOOLTIP
        actionFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionFlip->setText(QApplication::translate("MainWindow", "flip", 0));
        actionOriginalSize->setText(QApplication::translate("MainWindow", "Originale", 0));
#ifndef QT_NO_TOOLTIP
        actionOriginalSize->setToolTip(QApplication::translate("MainWindow", "taille originale", 0));
#endif // QT_NO_TOOLTIP
        actionConstrainedSize->setText(QApplication::translate("MainWindow", "Custom", 0));
        actionConstrainedSize->setIconText(QApplication::translate("MainWindow", "contrainte", 0));
#ifndef QT_NO_TOOLTIP
        actionConstrainedSize->setToolTip(QApplication::translate("MainWindow", "taille impos\303\251e", 0));
#endif // QT_NO_TOOLTIP
        actionQuit->setText(QApplication::translate("MainWindow", "Quitter", 0));
#ifndef QT_NO_TOOLTIP
        actionQuit->setToolTip(QApplication::translate("MainWindow", "quitter", 0));
#endif // QT_NO_TOOLTIP
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionRenderImage->setText(QApplication::translate("MainWindow", "Image", 0));
        actionRenderPixmap->setText(QApplication::translate("MainWindow", "Pixmap", 0));
        actionRenderOpenGL->setText(QApplication::translate("MainWindow", "OpenGL", 0));
        radioButtonOrigSize->setText(QApplication::translate("MainWindow", "Originale", 0));
        radioButtonCustomSize->setText(QApplication::translate("MainWindow", "Custom", 0));
        labelWidth->setText(QApplication::translate("MainWindow", "Largeur", 0));
        labelHeight->setText(QApplication::translate("MainWindow", "Hauteur", 0));
        checkBoxFlip->setText(QApplication::translate("MainWindow", "Flip", 0));
        tabWidget->setTabText(tabWidget->indexOf(sizeTab), QApplication::translate("MainWindow", "Size", 0));
        displayBox->setTitle(QApplication::translate("MainWindow", "Display", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonInput->setToolTip(QApplication::translate("MainWindow", "Input Image (I)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonInput->setText(QApplication::translate("MainWindow", "Input", 0));
        radioButtonInput->setShortcut(QApplication::translate("MainWindow", "I", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonGray->setToolTip(QApplication::translate("MainWindow", "Grayscale Image (K)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonGray->setText(QApplication::translate("MainWindow", "Gray", 0));
        radioButtonGray->setShortcut(QApplication::translate("MainWindow", "K", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonRed->setToolTip(QApplication::translate("MainWindow", "Red Component (R)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonRed->setText(QApplication::translate("MainWindow", "RGB: Red", 0));
        radioButtonRed->setShortcut(QApplication::translate("MainWindow", "R", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonGreen->setToolTip(QApplication::translate("MainWindow", "Green Component (G)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonGreen->setText(QApplication::translate("MainWindow", "RGB: Green", 0));
        radioButtonGreen->setShortcut(QApplication::translate("MainWindow", "G", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonBlue->setToolTip(QApplication::translate("MainWindow", "Blue Component (B)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonBlue->setText(QApplication::translate("MainWindow", "RGB: Blue", 0));
        radioButtonBlue->setShortcut(QApplication::translate("MainWindow", "B", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonMaxBGR->setToolTip(QApplication::translate("MainWindow", "RGB Maximum Image", 0));
#endif // QT_NO_TOOLTIP
        radioButtonMaxBGR->setText(QApplication::translate("MainWindow", "RGB: Max", 0));
        radioButtonMaxBGR->setShortcut(QApplication::translate("MainWindow", "M", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonXYZ_X->setToolTip(QApplication::translate("MainWindow", "X Component (X)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonXYZ_X->setText(QApplication::translate("MainWindow", "XYZ: X", 0));
        radioButtonXYZ_X->setShortcut(QApplication::translate("MainWindow", "X", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonXYZ_Y->setToolTip(QApplication::translate("MainWindow", "Y component (W)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonXYZ_Y->setText(QApplication::translate("MainWindow", "XYZ: Y", 0));
        radioButtonXYZ_Y->setShortcut(QApplication::translate("MainWindow", "W", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonXYZ_Z->setToolTip(QApplication::translate("MainWindow", "Z Component (Z)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonXYZ_Z->setText(QApplication::translate("MainWindow", "XYZ: Z", 0));
        radioButtonXYZ_Z->setShortcut(QApplication::translate("MainWindow", "Z", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonHue->setToolTip(QApplication::translate("MainWindow", "Hue Component (H)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonHue->setText(QApplication::translate("MainWindow", "HSV: Hue", 0));
        radioButtonHue->setShortcut(QApplication::translate("MainWindow", "H", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonSaturation->setToolTip(QApplication::translate("MainWindow", "Saturation Component (S)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonSaturation->setText(QApplication::translate("MainWindow", "HSV: Saturation", 0));
        radioButtonSaturation->setShortcut(QApplication::translate("MainWindow", "S", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonValue->setToolTip(QApplication::translate("MainWindow", "Value Component (V)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonValue->setText(QApplication::translate("MainWindow", "HSV: Value", 0));
        radioButtonValue->setShortcut(QApplication::translate("MainWindow", "V", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonY->setToolTip(QApplication::translate("MainWindow", "Y Component (Y)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonY->setText(QApplication::translate("MainWindow", "YCbCr: Y", 0));
        radioButtonY->setShortcut(QApplication::translate("MainWindow", "Y", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonCr->setToolTip(QApplication::translate("MainWindow", "Green/Magenta Chrominance (U)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonCr->setText(QApplication::translate("MainWindow", "YCbCr: Cr", 0));
        radioButtonCr->setShortcut(QApplication::translate("MainWindow", "U", 0));
#ifndef QT_NO_TOOLTIP
        radioButtonCb->setToolTip(QApplication::translate("MainWindow", "Blue/Yellow Chrominance (T)", 0));
#endif // QT_NO_TOOLTIP
        radioButtonCb->setText(QApplication::translate("MainWindow", "YCbCr: Cb", 0));
        radioButtonCb->setShortcut(QApplication::translate("MainWindow", "T", 0));
        channelBox->setTitle(QApplication::translate("MainWindow", "Channel", 0));
        radioButtonChColor->setText(QApplication::translate("MainWindow", "Color", 0));
        radioButtonChGray->setText(QApplication::translate("MainWindow", "Gray", 0));
        hueBox->setTitle(QApplication::translate("MainWindow", "Hue mix", 0));
        radioButtonMixHue->setText(QApplication::translate("MainWindow", "Hue", 0));
        radioButtonMixHueSat->setText(QApplication::translate("MainWindow", "Hue x Sat", 0));
        radioButtonMixHueVal->setText(QApplication::translate("MainWindow", "Hue x Value", 0));
        labelProcessTime->setText(QApplication::translate("MainWindow", "process time:", 0));
        labelProcessTimeValue->setText(QApplication::translate("MainWindow", "0", 0));
        labelPM->setText(QApplication::translate("MainWindow", "\302\261", 0));
        labelProcessTimeStd->setText(QApplication::translate("MainWindow", "0", 0));
        labelTimeUnit->setText(QApplication::translate("MainWindow", "ms", 0));
        tabWidget->setTabText(tabWidget->indexOf(colorTab), QApplication::translate("MainWindow", "Color", 0));
        menuSources->setTitle(QApplication::translate("MainWindow", "Sources", 0));
        menuVideo->setTitle(QApplication::translate("MainWindow", "Video", 0));
        menuSize->setTitle(QApplication::translate("MainWindow", "taille", 0));
        menuRender->setTitle(QApplication::translate("MainWindow", "Render", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
