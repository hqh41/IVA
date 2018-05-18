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
#include "QcvMatWidgetImage.h"

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
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QcvMatWidget *widgetImage;
    QGroupBox *groupBoxHistogram;
    QHBoxLayout *horizontalLayout;
    QcvMatWidgetImage *widgetHistogram;
    QGroupBox *groupBoxLUT;
    QHBoxLayout *horizontalLayout_2;
    QcvMatWidgetImage *widgetLUT;
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
    QWidget *histTab;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBoxHistChannels;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *checkBoxHistRed;
    QCheckBox *checkBoxHistGreen;
    QCheckBox *checkBoxHistBlue;
    QCheckBox *checkBoxHistGray;
    QGroupBox *groupBoxHistMode;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButtonHMNormal;
    QRadioButton *radioButtonHMCumulative;
    QRadioButton *radioButtonHMTime;
    QSpacerItem *verticalSpacer_3;
    QWidget *lutTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *lutBox;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButtonIdentity;
    QRadioButton *radioButtonInverse;
    QRadioButton *radioButtonGamma;
    QRadioButton *radioButtonThreshold;
    QRadioButton *radioButtonDynamic;
    QRadioButton *radioButtonEqualize;
    QGroupBox *channelBox;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButtonChColor;
    QRadioButton *radioButtonChGray;
    QGroupBox *percentBox;
    QVBoxLayout *verticalLayout_5;
    QSpinBox *spinBoxlutParam;
    QSlider *horizontalSlider;
    QSpacerItem *verticalSpacer_2;
    QWidget *timeTab;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBoxHistogram_2;
    QVBoxLayout *verticalLayout_10;
    QLabel *labelUH1;
    QLabel *labelUH1Time;
    QLabel *labelUH2;
    QLabel *labelUH2Time;
    QLabel *labelDH;
    QLabel *labelDHTime;
    QGroupBox *groupBoxLUT_2;
    QVBoxLayout *verticalLayout_11;
    QLabel *labelCL;
    QLabel *labelCLTime;
    QLabel *labelAL;
    QLabel *labelALTime;
    QLabel *labelDL;
    QLabel *labelDLTime;
    QGroupBox *groupBoxDL;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelAllTime;
    QSpacerItem *verticalSpacer_4;
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
        MainWindow->resize(714, 569);
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
        widgetImage->setGeometry(QRect(0, 0, 528, 398));
        scrollArea->setWidget(widgetImage);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        groupBoxHistogram = new QGroupBox(centralWidget);
        groupBoxHistogram->setObjectName(QStringLiteral("groupBoxHistogram"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBoxHistogram->sizePolicy().hasHeightForWidth());
        groupBoxHistogram->setSizePolicy(sizePolicy1);
        groupBoxHistogram->setMinimumSize(QSize(100, 100));
        horizontalLayout = new QHBoxLayout(groupBoxHistogram);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        widgetHistogram = new QcvMatWidgetImage(groupBoxHistogram);
        widgetHistogram->setObjectName(QStringLiteral("widgetHistogram"));
        sizePolicy.setHeightForWidth(widgetHistogram->sizePolicy().hasHeightForWidth());
        widgetHistogram->setSizePolicy(sizePolicy);
        widgetHistogram->setMinimumSize(QSize(512, 100));

        horizontalLayout->addWidget(widgetHistogram);


        gridLayout->addWidget(groupBoxHistogram, 1, 0, 1, 1);

        groupBoxLUT = new QGroupBox(centralWidget);
        groupBoxLUT->setObjectName(QStringLiteral("groupBoxLUT"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBoxLUT->sizePolicy().hasHeightForWidth());
        groupBoxLUT->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(groupBoxLUT);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, 3, 3, 3);
        widgetLUT = new QcvMatWidgetImage(groupBoxLUT);
        widgetLUT->setObjectName(QStringLiteral("widgetLUT"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widgetLUT->sizePolicy().hasHeightForWidth());
        widgetLUT->setSizePolicy(sizePolicy3);
        widgetLUT->setMinimumSize(QSize(100, 100));

        horizontalLayout_2->addWidget(widgetLUT);


        gridLayout->addWidget(groupBoxLUT, 1, 1, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy4);
        tabWidget->setStyleSheet(QStringLiteral("font: 10pt \"Lucida Grande\";"));
        tabWidget->setTabPosition(QTabWidget::West);
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
        histTab = new QWidget();
        histTab->setObjectName(QStringLiteral("histTab"));
        verticalLayout_7 = new QVBoxLayout(histTab);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(8, 8, 8, 8);
        groupBoxHistChannels = new QGroupBox(histTab);
        groupBoxHistChannels->setObjectName(QStringLiteral("groupBoxHistChannels"));
        verticalLayout_8 = new QVBoxLayout(groupBoxHistChannels);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        checkBoxHistRed = new QCheckBox(groupBoxHistChannels);
        checkBoxHistRed->setObjectName(QStringLiteral("checkBoxHistRed"));

        verticalLayout_8->addWidget(checkBoxHistRed);

        checkBoxHistGreen = new QCheckBox(groupBoxHistChannels);
        checkBoxHistGreen->setObjectName(QStringLiteral("checkBoxHistGreen"));

        verticalLayout_8->addWidget(checkBoxHistGreen);

        checkBoxHistBlue = new QCheckBox(groupBoxHistChannels);
        checkBoxHistBlue->setObjectName(QStringLiteral("checkBoxHistBlue"));

        verticalLayout_8->addWidget(checkBoxHistBlue);

        checkBoxHistGray = new QCheckBox(groupBoxHistChannels);
        checkBoxHistGray->setObjectName(QStringLiteral("checkBoxHistGray"));

        verticalLayout_8->addWidget(checkBoxHistGray);


        verticalLayout_7->addWidget(groupBoxHistChannels);

        groupBoxHistMode = new QGroupBox(histTab);
        groupBoxHistMode->setObjectName(QStringLiteral("groupBoxHistMode"));
        verticalLayout_6 = new QVBoxLayout(groupBoxHistMode);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        radioButtonHMNormal = new QRadioButton(groupBoxHistMode);
        radioButtonHMNormal->setObjectName(QStringLiteral("radioButtonHMNormal"));
        radioButtonHMNormal->setChecked(true);

        verticalLayout_6->addWidget(radioButtonHMNormal);

        radioButtonHMCumulative = new QRadioButton(groupBoxHistMode);
        radioButtonHMCumulative->setObjectName(QStringLiteral("radioButtonHMCumulative"));

        verticalLayout_6->addWidget(radioButtonHMCumulative);

        radioButtonHMTime = new QRadioButton(groupBoxHistMode);
        radioButtonHMTime->setObjectName(QStringLiteral("radioButtonHMTime"));

        verticalLayout_6->addWidget(radioButtonHMTime);


        verticalLayout_7->addWidget(groupBoxHistMode);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);

        tabWidget->addTab(histTab, QString());
        lutTab = new QWidget();
        lutTab->setObjectName(QStringLiteral("lutTab"));
        verticalLayout_2 = new QVBoxLayout(lutTab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(8, 8, 8, 8);
        lutBox = new QGroupBox(lutTab);
        lutBox->setObjectName(QStringLiteral("lutBox"));
        verticalLayout_3 = new QVBoxLayout(lutBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(8, 8, 8, 8);
        radioButtonIdentity = new QRadioButton(lutBox);
        radioButtonIdentity->setObjectName(QStringLiteral("radioButtonIdentity"));
        radioButtonIdentity->setChecked(true);

        verticalLayout_3->addWidget(radioButtonIdentity);

        radioButtonInverse = new QRadioButton(lutBox);
        radioButtonInverse->setObjectName(QStringLiteral("radioButtonInverse"));

        verticalLayout_3->addWidget(radioButtonInverse);

        radioButtonGamma = new QRadioButton(lutBox);
        radioButtonGamma->setObjectName(QStringLiteral("radioButtonGamma"));

        verticalLayout_3->addWidget(radioButtonGamma);

        radioButtonThreshold = new QRadioButton(lutBox);
        radioButtonThreshold->setObjectName(QStringLiteral("radioButtonThreshold"));

        verticalLayout_3->addWidget(radioButtonThreshold);

        radioButtonDynamic = new QRadioButton(lutBox);
        radioButtonDynamic->setObjectName(QStringLiteral("radioButtonDynamic"));

        verticalLayout_3->addWidget(radioButtonDynamic);

        radioButtonEqualize = new QRadioButton(lutBox);
        radioButtonEqualize->setObjectName(QStringLiteral("radioButtonEqualize"));

        verticalLayout_3->addWidget(radioButtonEqualize);


        verticalLayout_2->addWidget(lutBox);

        channelBox = new QGroupBox(lutTab);
        channelBox->setObjectName(QStringLiteral("channelBox"));
        verticalLayout_4 = new QVBoxLayout(channelBox);
        verticalLayout_4->setSpacing(6);
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

        percentBox = new QGroupBox(lutTab);
        percentBox->setObjectName(QStringLiteral("percentBox"));
        percentBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        verticalLayout_5 = new QVBoxLayout(percentBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        spinBoxlutParam = new QSpinBox(percentBox);
        spinBoxlutParam->setObjectName(QStringLiteral("spinBoxlutParam"));
        spinBoxlutParam->setMinimum(5);
        spinBoxlutParam->setMaximum(95);
        spinBoxlutParam->setValue(80);

        verticalLayout_5->addWidget(spinBoxlutParam);

        horizontalSlider = new QSlider(percentBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(5);
        horizontalSlider->setMaximum(95);
        horizontalSlider->setValue(80);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(horizontalSlider);


        verticalLayout_2->addWidget(percentBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        tabWidget->addTab(lutTab, QString());
        timeTab = new QWidget();
        timeTab->setObjectName(QStringLiteral("timeTab"));
        verticalLayout_9 = new QVBoxLayout(timeTab);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        groupBoxHistogram_2 = new QGroupBox(timeTab);
        groupBoxHistogram_2->setObjectName(QStringLiteral("groupBoxHistogram_2"));
        verticalLayout_10 = new QVBoxLayout(groupBoxHistogram_2);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(8, 8, 8, 8);
        labelUH1 = new QLabel(groupBoxHistogram_2);
        labelUH1->setObjectName(QStringLiteral("labelUH1"));

        verticalLayout_10->addWidget(labelUH1);

        labelUH1Time = new QLabel(groupBoxHistogram_2);
        labelUH1Time->setObjectName(QStringLiteral("labelUH1Time"));
        labelUH1Time->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(labelUH1Time);

        labelUH2 = new QLabel(groupBoxHistogram_2);
        labelUH2->setObjectName(QStringLiteral("labelUH2"));

        verticalLayout_10->addWidget(labelUH2);

        labelUH2Time = new QLabel(groupBoxHistogram_2);
        labelUH2Time->setObjectName(QStringLiteral("labelUH2Time"));
        labelUH2Time->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(labelUH2Time);

        labelDH = new QLabel(groupBoxHistogram_2);
        labelDH->setObjectName(QStringLiteral("labelDH"));

        verticalLayout_10->addWidget(labelDH);

        labelDHTime = new QLabel(groupBoxHistogram_2);
        labelDHTime->setObjectName(QStringLiteral("labelDHTime"));
        labelDHTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(labelDHTime);


        verticalLayout_9->addWidget(groupBoxHistogram_2);

        groupBoxLUT_2 = new QGroupBox(timeTab);
        groupBoxLUT_2->setObjectName(QStringLiteral("groupBoxLUT_2"));
        verticalLayout_11 = new QVBoxLayout(groupBoxLUT_2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        labelCL = new QLabel(groupBoxLUT_2);
        labelCL->setObjectName(QStringLiteral("labelCL"));

        verticalLayout_11->addWidget(labelCL);

        labelCLTime = new QLabel(groupBoxLUT_2);
        labelCLTime->setObjectName(QStringLiteral("labelCLTime"));
        labelCLTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_11->addWidget(labelCLTime);

        labelAL = new QLabel(groupBoxLUT_2);
        labelAL->setObjectName(QStringLiteral("labelAL"));

        verticalLayout_11->addWidget(labelAL);

        labelALTime = new QLabel(groupBoxLUT_2);
        labelALTime->setObjectName(QStringLiteral("labelALTime"));
        labelALTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_11->addWidget(labelALTime);

        labelDL = new QLabel(groupBoxLUT_2);
        labelDL->setObjectName(QStringLiteral("labelDL"));

        verticalLayout_11->addWidget(labelDL);

        labelDLTime = new QLabel(groupBoxLUT_2);
        labelDLTime->setObjectName(QStringLiteral("labelDLTime"));
        labelDLTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_11->addWidget(labelDLTime);


        verticalLayout_9->addWidget(groupBoxLUT_2);

        groupBoxDL = new QGroupBox(timeTab);
        groupBoxDL->setObjectName(QStringLiteral("groupBoxDL"));
        horizontalLayout_5 = new QHBoxLayout(groupBoxDL);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(8, 8, 8, 8);
        labelAllTime = new QLabel(groupBoxDL);
        labelAllTime->setObjectName(QStringLiteral("labelAllTime"));
        labelAllTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(labelAllTime);


        verticalLayout_9->addWidget(groupBoxDL);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_4);

        tabWidget->addTab(timeTab, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 714, 22));
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
        QWidget::setTabOrder(tabWidget, radioButtonOrigSize);
        QWidget::setTabOrder(radioButtonOrigSize, radioButtonCustomSize);
        QWidget::setTabOrder(radioButtonCustomSize, spinBoxWidth);
        QWidget::setTabOrder(spinBoxWidth, spinBoxHeight);
        QWidget::setTabOrder(spinBoxHeight, checkBoxFlip);
        QWidget::setTabOrder(checkBoxFlip, checkBoxHistRed);
        QWidget::setTabOrder(checkBoxHistRed, checkBoxHistGreen);
        QWidget::setTabOrder(checkBoxHistGreen, checkBoxHistBlue);
        QWidget::setTabOrder(checkBoxHistBlue, checkBoxHistGray);
        QWidget::setTabOrder(checkBoxHistGray, radioButtonHMNormal);
        QWidget::setTabOrder(radioButtonHMNormal, radioButtonHMCumulative);
        QWidget::setTabOrder(radioButtonHMCumulative, radioButtonHMTime);
        QWidget::setTabOrder(radioButtonHMTime, radioButtonIdentity);
        QWidget::setTabOrder(radioButtonIdentity, radioButtonInverse);
        QWidget::setTabOrder(radioButtonInverse, radioButtonGamma);
        QWidget::setTabOrder(radioButtonGamma, radioButtonThreshold);
        QWidget::setTabOrder(radioButtonThreshold, radioButtonDynamic);
        QWidget::setTabOrder(radioButtonDynamic, radioButtonEqualize);
        QWidget::setTabOrder(radioButtonEqualize, radioButtonChColor);
        QWidget::setTabOrder(radioButtonChColor, radioButtonChGray);
        QWidget::setTabOrder(radioButtonChGray, spinBoxlutParam);
        QWidget::setTabOrder(spinBoxlutParam, horizontalSlider);
        QWidget::setTabOrder(horizontalSlider, scrollArea);

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
        QObject::connect(spinBoxlutParam, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), spinBoxlutParam, SLOT(setValue(int)));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Histograms & LUTs", 0));
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
        groupBoxHistogram->setTitle(QApplication::translate("MainWindow", "Histogram", 0));
        groupBoxLUT->setTitle(QApplication::translate("MainWindow", "LUT", 0));
        radioButtonOrigSize->setText(QApplication::translate("MainWindow", "Originale", 0));
        radioButtonCustomSize->setText(QApplication::translate("MainWindow", "Custom", 0));
        labelWidth->setText(QApplication::translate("MainWindow", "Largeur", 0));
        labelHeight->setText(QApplication::translate("MainWindow", "Hauteur", 0));
        checkBoxFlip->setText(QApplication::translate("MainWindow", "Flip", 0));
        tabWidget->setTabText(tabWidget->indexOf(sizeTab), QApplication::translate("MainWindow", "Size", 0));
        groupBoxHistChannels->setTitle(QApplication::translate("MainWindow", "Channels", 0));
        checkBoxHistRed->setText(QApplication::translate("MainWindow", "Red", 0));
        checkBoxHistRed->setShortcut(QApplication::translate("MainWindow", "R", 0));
        checkBoxHistGreen->setText(QApplication::translate("MainWindow", "Green", 0));
        checkBoxHistGreen->setShortcut(QApplication::translate("MainWindow", "G", 0));
        checkBoxHistBlue->setText(QApplication::translate("MainWindow", "Blue", 0));
        checkBoxHistBlue->setShortcut(QApplication::translate("MainWindow", "B", 0));
        checkBoxHistGray->setText(QApplication::translate("MainWindow", "Gray", 0));
        checkBoxHistGray->setShortcut(QApplication::translate("MainWindow", "K", 0));
        groupBoxHistMode->setTitle(QApplication::translate("MainWindow", "Hist. mode", 0));
        radioButtonHMNormal->setText(QApplication::translate("MainWindow", "Normal", 0));
        radioButtonHMNormal->setShortcut(QApplication::translate("MainWindow", "V", 0));
        radioButtonHMCumulative->setText(QApplication::translate("MainWindow", "Cumulative", 0));
        radioButtonHMCumulative->setShortcut(QApplication::translate("MainWindow", "C", 0));
        radioButtonHMTime->setText(QApplication::translate("MainWindow", "Time Cumul.", 0));
        radioButtonHMTime->setShortcut(QApplication::translate("MainWindow", "T", 0));
        tabWidget->setTabText(tabWidget->indexOf(histTab), QApplication::translate("MainWindow", "Hist", 0));
        lutBox->setTitle(QApplication::translate("MainWindow", "Transfert", 0));
        radioButtonIdentity->setText(QApplication::translate("MainWindow", "Identity", 0));
        radioButtonIdentity->setShortcut(QApplication::translate("MainWindow", "I", 0));
        radioButtonInverse->setText(QApplication::translate("MainWindow", "Inverse", 0));
        radioButtonInverse->setShortcut(QApplication::translate("MainWindow", "N", 0));
        radioButtonGamma->setText(QApplication::translate("MainWindow", "Gamma", 0));
        radioButtonGamma->setShortcut(QApplication::translate("MainWindow", "M", 0));
        radioButtonThreshold->setText(QApplication::translate("MainWindow", "Threshold", 0));
        radioButtonThreshold->setShortcut(QApplication::translate("MainWindow", "H", 0));
        radioButtonDynamic->setText(QApplication::translate("MainWindow", "&Dynamic", 0));
        radioButtonDynamic->setShortcut(QApplication::translate("MainWindow", "D", 0));
        radioButtonEqualize->setText(QApplication::translate("MainWindow", "Equalize", 0));
        radioButtonEqualize->setShortcut(QApplication::translate("MainWindow", "E", 0));
        channelBox->setTitle(QApplication::translate("MainWindow", "Channels", 0));
        radioButtonChColor->setText(QApplication::translate("MainWindow", "Colors", 0));
        radioButtonChGray->setText(QApplication::translate("MainWindow", "Gray", 0));
        percentBox->setTitle(QApplication::translate("MainWindow", "Percent", 0));
        tabWidget->setTabText(tabWidget->indexOf(lutTab), QApplication::translate("MainWindow", "LUT", 0));
        groupBoxHistogram_2->setTitle(QApplication::translate("MainWindow", "Histogram", 0));
        labelUH1->setText(QApplication::translate("MainWindow", "Update 1", 0));
        labelUH1Time->setText(QApplication::translate("MainWindow", "0", 0));
        labelUH2->setText(QApplication::translate("MainWindow", "Update 2", 0));
        labelUH2Time->setText(QApplication::translate("MainWindow", "0", 0));
        labelDH->setText(QApplication::translate("MainWindow", "Draw", 0));
        labelDHTime->setText(QApplication::translate("MainWindow", "0", 0));
        groupBoxLUT_2->setTitle(QApplication::translate("MainWindow", "LUT", 0));
        labelCL->setText(QApplication::translate("MainWindow", "Compute", 0));
        labelCLTime->setText(QApplication::translate("MainWindow", "0", 0));
        labelAL->setText(QApplication::translate("MainWindow", "Apply", 0));
        labelALTime->setText(QApplication::translate("MainWindow", "0", 0));
        labelDL->setText(QApplication::translate("MainWindow", "Draw", 0));
        labelDLTime->setText(QApplication::translate("MainWindow", "0", 0));
        groupBoxDL->setTitle(QApplication::translate("MainWindow", "All", 0));
        labelAllTime->setText(QApplication::translate("MainWindow", "0", 0));
        tabWidget->setTabText(tabWidget->indexOf(timeTab), QApplication::translate("MainWindow", "Times", 0));
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
