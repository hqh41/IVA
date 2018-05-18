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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
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
    QAction *actionGray;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QcvMatWidget *widgetImage;
    QTabWidget *tabWidget;
    QWidget *captureTab;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonOrigSize;
    QRadioButton *radioButtonCustomSize;
    QLabel *labelWidth;
    QSpinBox *spinBoxWidth;
    QLabel *labelHeight;
    QSpinBox *spinBoxHeight;
    QCheckBox *checkBoxFlip;
    QCheckBox *checkBoxGray;
    QSpacerItem *verticalSpacer;
    QWidget *processTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxDisplay;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButtonInput;
    QRadioButton *radioButtonMask;
    QRadioButton *radioButtonMerged;
    QGroupBox *groupBoxShow;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *checkBoxBBox;
    QCheckBox *checkBoxCenter;
    QGroupBox *groupBoxConnectivity;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButton4Connect;
    QRadioButton *radioButton8Connect;
    QGroupBox *groupBoxFloodFill;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioButtonAbsThreshold;
    QRadioButton *radioButtonRelThreshold;
    QPushButton *pushButtonClearFlood;
    QPushButton *pushButtonNewColor;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelTTime;
    QLabel *labelTime;
    QGroupBox *groupBoxThreshold;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelLoDiff;
    QLabel *labelUpDiff;
    QVBoxLayout *verticalLayout_7;
    QSlider *horizontalSliderLoDiff;
    QSlider *horizontalSliderUpDiff;
    QVBoxLayout *verticalLayout_8;
    QSpinBox *spinBoxLoDiff;
    QSpinBox *spinBoxUpDiff;
    QCheckBox *checkBoxLink;
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
        MainWindow->resize(800, 660);
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
        actionGray = new QAction(MainWindow);
        actionGray->setObjectName(QStringLiteral("actionGray"));
        actionGray->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(6, 0, 6, 0);
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
        widgetImage->setGeometry(QRect(0, 0, 626, 509));
        scrollArea->setWidget(widgetImage);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(150, 0));
        tabWidget->setMaximumSize(QSize(150, 16777215));
        captureTab = new QWidget();
        captureTab->setObjectName(QStringLiteral("captureTab"));
        verticalLayout = new QVBoxLayout(captureTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(8, 8, 8, 8);
        radioButtonOrigSize = new QRadioButton(captureTab);
        radioButtonOrigSize->setObjectName(QStringLiteral("radioButtonOrigSize"));
        radioButtonOrigSize->setChecked(true);

        verticalLayout->addWidget(radioButtonOrigSize);

        radioButtonCustomSize = new QRadioButton(captureTab);
        radioButtonCustomSize->setObjectName(QStringLiteral("radioButtonCustomSize"));

        verticalLayout->addWidget(radioButtonCustomSize);

        labelWidth = new QLabel(captureTab);
        labelWidth->setObjectName(QStringLiteral("labelWidth"));

        verticalLayout->addWidget(labelWidth);

        spinBoxWidth = new QSpinBox(captureTab);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMaximum(1600);
        spinBoxWidth->setSingleStep(4);

        verticalLayout->addWidget(spinBoxWidth);

        labelHeight = new QLabel(captureTab);
        labelHeight->setObjectName(QStringLiteral("labelHeight"));

        verticalLayout->addWidget(labelHeight);

        spinBoxHeight = new QSpinBox(captureTab);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMaximum(1200);
        spinBoxHeight->setSingleStep(4);

        verticalLayout->addWidget(spinBoxHeight);

        checkBoxFlip = new QCheckBox(captureTab);
        checkBoxFlip->setObjectName(QStringLiteral("checkBoxFlip"));

        verticalLayout->addWidget(checkBoxFlip);

        checkBoxGray = new QCheckBox(captureTab);
        checkBoxGray->setObjectName(QStringLiteral("checkBoxGray"));

        verticalLayout->addWidget(checkBoxGray);

        verticalSpacer = new QSpacerItem(20, 228, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(captureTab, QString());
        processTab = new QWidget();
        processTab->setObjectName(QStringLiteral("processTab"));
        verticalLayout_2 = new QVBoxLayout(processTab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(8, 8, 8, 8);
        groupBoxDisplay = new QGroupBox(processTab);
        groupBoxDisplay->setObjectName(QStringLiteral("groupBoxDisplay"));
        verticalLayout_3 = new QVBoxLayout(groupBoxDisplay);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(8, 8, 8, 8);
        radioButtonInput = new QRadioButton(groupBoxDisplay);
        radioButtonInput->setObjectName(QStringLiteral("radioButtonInput"));
        radioButtonInput->setChecked(true);

        verticalLayout_3->addWidget(radioButtonInput);

        radioButtonMask = new QRadioButton(groupBoxDisplay);
        radioButtonMask->setObjectName(QStringLiteral("radioButtonMask"));

        verticalLayout_3->addWidget(radioButtonMask);

        radioButtonMerged = new QRadioButton(groupBoxDisplay);
        radioButtonMerged->setObjectName(QStringLiteral("radioButtonMerged"));

        verticalLayout_3->addWidget(radioButtonMerged);


        verticalLayout_2->addWidget(groupBoxDisplay);

        groupBoxShow = new QGroupBox(processTab);
        groupBoxShow->setObjectName(QStringLiteral("groupBoxShow"));
        verticalLayout_9 = new QVBoxLayout(groupBoxShow);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(2, 2, 2, 2);
        checkBoxBBox = new QCheckBox(groupBoxShow);
        checkBoxBBox->setObjectName(QStringLiteral("checkBoxBBox"));

        verticalLayout_9->addWidget(checkBoxBBox);

        checkBoxCenter = new QCheckBox(groupBoxShow);
        checkBoxCenter->setObjectName(QStringLiteral("checkBoxCenter"));

        verticalLayout_9->addWidget(checkBoxCenter);


        verticalLayout_2->addWidget(groupBoxShow);

        groupBoxConnectivity = new QGroupBox(processTab);
        groupBoxConnectivity->setObjectName(QStringLiteral("groupBoxConnectivity"));
        verticalLayout_4 = new QVBoxLayout(groupBoxConnectivity);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        radioButton4Connect = new QRadioButton(groupBoxConnectivity);
        radioButton4Connect->setObjectName(QStringLiteral("radioButton4Connect"));

        verticalLayout_4->addWidget(radioButton4Connect);

        radioButton8Connect = new QRadioButton(groupBoxConnectivity);
        radioButton8Connect->setObjectName(QStringLiteral("radioButton8Connect"));

        verticalLayout_4->addWidget(radioButton8Connect);


        verticalLayout_2->addWidget(groupBoxConnectivity);

        groupBoxFloodFill = new QGroupBox(processTab);
        groupBoxFloodFill->setObjectName(QStringLiteral("groupBoxFloodFill"));
        verticalLayout_5 = new QVBoxLayout(groupBoxFloodFill);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        radioButtonAbsThreshold = new QRadioButton(groupBoxFloodFill);
        radioButtonAbsThreshold->setObjectName(QStringLiteral("radioButtonAbsThreshold"));
        radioButtonAbsThreshold->setChecked(true);

        verticalLayout_5->addWidget(radioButtonAbsThreshold);

        radioButtonRelThreshold = new QRadioButton(groupBoxFloodFill);
        radioButtonRelThreshold->setObjectName(QStringLiteral("radioButtonRelThreshold"));

        verticalLayout_5->addWidget(radioButtonRelThreshold);


        verticalLayout_2->addWidget(groupBoxFloodFill);

        pushButtonClearFlood = new QPushButton(processTab);
        pushButtonClearFlood->setObjectName(QStringLiteral("pushButtonClearFlood"));

        verticalLayout_2->addWidget(pushButtonClearFlood);

        pushButtonNewColor = new QPushButton(processTab);
        pushButtonNewColor->setObjectName(QStringLiteral("pushButtonNewColor"));

        verticalLayout_2->addWidget(pushButtonNewColor);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelTTime = new QLabel(processTab);
        labelTTime->setObjectName(QStringLiteral("labelTTime"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelTTime->sizePolicy().hasHeightForWidth());
        labelTTime->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(10);
        labelTTime->setFont(font);

        horizontalLayout_2->addWidget(labelTTime);

        labelTime = new QLabel(processTab);
        labelTime->setObjectName(QStringLiteral("labelTime"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelTime->sizePolicy().hasHeightForWidth());
        labelTime->setSizePolicy(sizePolicy3);
        labelTime->setFont(font);

        horizontalLayout_2->addWidget(labelTime);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget->addTab(processTab, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        groupBoxThreshold = new QGroupBox(centralWidget);
        groupBoxThreshold->setObjectName(QStringLiteral("groupBoxThreshold"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBoxThreshold->sizePolicy().hasHeightForWidth());
        groupBoxThreshold->setSizePolicy(sizePolicy4);
        horizontalLayout = new QHBoxLayout(groupBoxThreshold);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(8, -1, 8, 8);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        labelLoDiff = new QLabel(groupBoxThreshold);
        labelLoDiff->setObjectName(QStringLiteral("labelLoDiff"));

        verticalLayout_6->addWidget(labelLoDiff);

        labelUpDiff = new QLabel(groupBoxThreshold);
        labelUpDiff->setObjectName(QStringLiteral("labelUpDiff"));

        verticalLayout_6->addWidget(labelUpDiff);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalSliderLoDiff = new QSlider(groupBoxThreshold);
        horizontalSliderLoDiff->setObjectName(QStringLiteral("horizontalSliderLoDiff"));
        horizontalSliderLoDiff->setMaximum(255);
        horizontalSliderLoDiff->setValue(20);
        horizontalSliderLoDiff->setOrientation(Qt::Horizontal);

        verticalLayout_7->addWidget(horizontalSliderLoDiff);

        horizontalSliderUpDiff = new QSlider(groupBoxThreshold);
        horizontalSliderUpDiff->setObjectName(QStringLiteral("horizontalSliderUpDiff"));
        horizontalSliderUpDiff->setMaximum(255);
        horizontalSliderUpDiff->setValue(20);
        horizontalSliderUpDiff->setOrientation(Qt::Horizontal);

        verticalLayout_7->addWidget(horizontalSliderUpDiff);


        horizontalLayout->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        spinBoxLoDiff = new QSpinBox(groupBoxThreshold);
        spinBoxLoDiff->setObjectName(QStringLiteral("spinBoxLoDiff"));
        spinBoxLoDiff->setMaximum(255);
        spinBoxLoDiff->setValue(20);

        verticalLayout_8->addWidget(spinBoxLoDiff);

        spinBoxUpDiff = new QSpinBox(groupBoxThreshold);
        spinBoxUpDiff->setObjectName(QStringLiteral("spinBoxUpDiff"));
        spinBoxUpDiff->setMaximum(255);
        spinBoxUpDiff->setValue(20);

        verticalLayout_8->addWidget(spinBoxUpDiff);


        horizontalLayout->addLayout(verticalLayout_8);

        checkBoxLink = new QCheckBox(groupBoxThreshold);
        checkBoxLink->setObjectName(QStringLiteral("checkBoxLink"));

        horizontalLayout->addWidget(checkBoxLink);


        gridLayout->addWidget(groupBoxThreshold, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
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
        menuVideo->addAction(actionGray);
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
        QObject::connect(checkBoxGray, SIGNAL(clicked(bool)), actionGray, SLOT(setChecked(bool)));
        QObject::connect(actionGray, SIGNAL(triggered(bool)), checkBoxGray, SLOT(setChecked(bool)));
        QObject::connect(spinBoxLoDiff, SIGNAL(valueChanged(int)), horizontalSliderLoDiff, SLOT(setValue(int)));
        QObject::connect(horizontalSliderLoDiff, SIGNAL(valueChanged(int)), spinBoxLoDiff, SLOT(setValue(int)));
        QObject::connect(spinBoxUpDiff, SIGNAL(valueChanged(int)), horizontalSliderUpDiff, SLOT(setValue(int)));
        QObject::connect(horizontalSliderUpDiff, SIGNAL(valueChanged(int)), spinBoxUpDiff, SLOT(setValue(int)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Flood Fill", 0));
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
        actionRenderImage->setText(QApplication::translate("MainWindow", "Image", 0));
        actionRenderPixmap->setText(QApplication::translate("MainWindow", "Pixmap", 0));
        actionRenderOpenGL->setText(QApplication::translate("MainWindow", "OpenGL", 0));
        actionGray->setText(QApplication::translate("MainWindow", "gray", 0));
        radioButtonOrigSize->setText(QApplication::translate("MainWindow", "Originale", 0));
        radioButtonCustomSize->setText(QApplication::translate("MainWindow", "Custom", 0));
        labelWidth->setText(QApplication::translate("MainWindow", "Largeur", 0));
        labelHeight->setText(QApplication::translate("MainWindow", "Hauteur", 0));
        checkBoxFlip->setText(QApplication::translate("MainWindow", "Flip", 0));
        checkBoxGray->setText(QApplication::translate("MainWindow", "Gray", 0));
        tabWidget->setTabText(tabWidget->indexOf(captureTab), QApplication::translate("MainWindow", "Size", 0));
        groupBoxDisplay->setTitle(QApplication::translate("MainWindow", "Display", 0));
        radioButtonInput->setText(QApplication::translate("MainWindow", "Input", 0));
        radioButtonInput->setShortcut(QApplication::translate("MainWindow", "I", 0));
        radioButtonMask->setText(QApplication::translate("MainWindow", "Mask", 0));
        radioButtonMask->setShortcut(QApplication::translate("MainWindow", "M", 0));
        radioButtonMerged->setText(QApplication::translate("MainWindow", "Merged", 0));
        radioButtonMerged->setShortcut(QApplication::translate("MainWindow", "E", 0));
        groupBoxShow->setTitle(QApplication::translate("MainWindow", "Show", 0));
        checkBoxBBox->setText(QApplication::translate("MainWindow", "Bbox", 0));
        checkBoxBBox->setShortcut(QApplication::translate("MainWindow", "B", 0));
        checkBoxCenter->setText(QApplication::translate("MainWindow", "Center", 0));
        checkBoxCenter->setShortcut(QApplication::translate("MainWindow", "S", 0));
        groupBoxConnectivity->setTitle(QApplication::translate("MainWindow", "Connectivity", 0));
        radioButton4Connect->setText(QApplication::translate("MainWindow", "4 Pixels", 0));
        radioButton8Connect->setText(QApplication::translate("MainWindow", "8 Pixels", 0));
        groupBoxFloodFill->setTitle(QApplication::translate("MainWindow", "Flood Threshold", 0));
        radioButtonAbsThreshold->setText(QApplication::translate("MainWindow", "Absolute", 0));
        radioButtonRelThreshold->setText(QApplication::translate("MainWindow", "Relative", 0));
        pushButtonClearFlood->setText(QApplication::translate("MainWindow", "Clear", 0));
        pushButtonClearFlood->setShortcut(QApplication::translate("MainWindow", "X", 0));
        pushButtonNewColor->setText(QApplication::translate("MainWindow", "New Color", 0));
        pushButtonNewColor->setShortcut(QApplication::translate("MainWindow", "N, Space", 0));
        labelTTime->setText(QApplication::translate("MainWindow", "Time", 0));
        labelTime->setText(QApplication::translate("MainWindow", "0", 0));
        tabWidget->setTabText(tabWidget->indexOf(processTab), QApplication::translate("MainWindow", "Process", 0));
        groupBoxThreshold->setTitle(QApplication::translate("MainWindow", "Flood Thresholds", 0));
        labelLoDiff->setText(QApplication::translate("MainWindow", "Low difference", 0));
        labelUpDiff->setText(QApplication::translate("MainWindow", "Up difference", 0));
        checkBoxLink->setText(QApplication::translate("MainWindow", "Link", 0));
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
