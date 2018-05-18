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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
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
    QAction *actionCalibData;
    QAction *actionModel;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QScrollArea *scrollAreaModel;
    QcvMatWidget *widgetImageModel;
    QScrollArea *scrollAreaScene;
    QcvMatWidget *widgetImageScene;
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
    QGridLayout *gridLayout_4;
    QGroupBox *groupBoxMatcher;
    QGridLayout *gridLayout_2;
    QLabel *labelMatcherType;
    QLabel *labelMatcherMode;
    QLabel *labelKnn;
    QComboBox *comboBoxMatcherType;
    QComboBox *comboBoxMatcherMode;
    QLabel *labelRadius;
    QDoubleSpinBox *doubleSpinBoxRadius;
    QLabel *labelMached;
    QLabel *labelMatchedNumber;
    QGroupBox *groupBoxMatchDistances;
    QGridLayout *gridLayout_3;
    QLabel *labelDistMean;
    QLabel *labelDistMeanNumber;
    QLabel *labelDistMin;
    QLabel *labelDistMinNumber;
    QSpinBox *spinBoxKnn;
    QLabel *labelMatcherTime;
    QLabel *labelMatcherTimeMs;
    QGroupBox *groupBoxRegistrar;
    QGridLayout *gridLayout_5;
    QLabel *labelReprojError;
    QLabel *labelReprojThres;
    QDoubleSpinBox *doubleSpinBoxReprojThres;
    QLabel *labelReprojErrorNumber;
    QLabel *labelInliers;
    QLabel *labelInliersNumber;
    QLabel *labelPrintSize;
    QDoubleSpinBox *doubleSpinBoxPrintSize;
    QCheckBox *checkBoxCameraSet;
    QCheckBox *checkBoxShowFrame;
    QCheckBox *checkBoxUsePreviousPose;
    QLabel *labelRegTime;
    QLabel *labelRegTimeMS;
    QCheckBox *checkBoxShowModelBox;
    QLabel *labelShowKP;
    QComboBox *comboBoxShowKPts;
    QSpacerItem *verticalSpacer_2;
    QComboBox *comboBoxTimeUnit;
    QLabel *labelTimeUnit;
    QGroupBox *groupBoxDetector;
    QGridLayout *gridLayout;
    QLabel *labelDetectorTimeMs;
    QLabel *labelDescriptors;
    QLabel *labelModel;
    QComboBox *comboBoxFeatures;
    QComboBox *comboBoxDescriptors;
    QLabel *labelModelKPts;
    QLabel *labelScene;
    QLabel *labelSceneKPts;
    QLabel *labelDescriptorsTime;
    QLabel *labelFeatures;
    QLabel *labelDescriptorsTimeMs;
    QLabel *labelDetectorTime;
    QWidget *parameterTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *detectorParamBox;
    QVBoxLayout *detectorBoxVerticalLayout;
    QLabel *detectorParam1Label;
    QLabel *detectorParam2Label;
    QGroupBox *extractorParamBox;
    QVBoxLayout *exctractorBoxVerticalLayout;
    QLabel *extractorParam1Label;
    QSpacerItem *verticalSpacer_3;
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
        MainWindow->resize(1006, 788);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
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
        actionCalibData = new QAction(MainWindow);
        actionCalibData->setObjectName(QStringLiteral("actionCalibData"));
        actionModel = new QAction(MainWindow);
        actionModel->setObjectName(QStringLiteral("actionModel"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        scrollAreaModel = new QScrollArea(splitter);
        scrollAreaModel->setObjectName(QStringLiteral("scrollAreaModel"));
        scrollAreaModel->setWidgetResizable(true);
        widgetImageModel = new QcvMatWidget();
        widgetImageModel->setObjectName(QStringLiteral("widgetImageModel"));
        widgetImageModel->setGeometry(QRect(0, 0, 356, 719));
        scrollAreaModel->setWidget(widgetImageModel);
        splitter->addWidget(scrollAreaModel);
        scrollAreaScene = new QScrollArea(splitter);
        scrollAreaScene->setObjectName(QStringLiteral("scrollAreaScene"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollAreaScene->sizePolicy().hasHeightForWidth());
        scrollAreaScene->setSizePolicy(sizePolicy1);
        scrollAreaScene->setWidgetResizable(true);
        scrollAreaScene->setAlignment(Qt::AlignCenter);
        widgetImageScene = new QcvMatWidget();
        widgetImageScene->setObjectName(QStringLiteral("widgetImageScene"));
        widgetImageScene->setGeometry(QRect(0, 0, 355, 719));
        scrollAreaScene->setWidget(widgetImageScene);
        splitter->addWidget(scrollAreaScene);

        horizontalLayout->addWidget(splitter);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setMaximumSize(QSize(250, 16777215));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setUsesScrollButtons(false);
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
        gridLayout_4 = new QGridLayout(processTab);
        gridLayout_4->setSpacing(3);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        groupBoxMatcher = new QGroupBox(processTab);
        groupBoxMatcher->setObjectName(QStringLiteral("groupBoxMatcher"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBoxMatcher->sizePolicy().hasHeightForWidth());
        groupBoxMatcher->setSizePolicy(sizePolicy3);
        groupBoxMatcher->setFlat(false);
        groupBoxMatcher->setCheckable(true);
        groupBoxMatcher->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBoxMatcher);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(-1);
        gridLayout_2->setVerticalSpacing(3);
        gridLayout_2->setContentsMargins(4, 4, 4, 4);
        labelMatcherType = new QLabel(groupBoxMatcher);
        labelMatcherType->setObjectName(QStringLiteral("labelMatcherType"));
        QFont font;
        font.setPointSize(10);
        labelMatcherType->setFont(font);
        labelMatcherType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelMatcherType, 0, 0, 1, 1);

        labelMatcherMode = new QLabel(groupBoxMatcher);
        labelMatcherMode->setObjectName(QStringLiteral("labelMatcherMode"));
        labelMatcherMode->setFont(font);
        labelMatcherMode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelMatcherMode, 2, 0, 1, 1);

        labelKnn = new QLabel(groupBoxMatcher);
        labelKnn->setObjectName(QStringLiteral("labelKnn"));
        labelKnn->setFont(font);
        labelKnn->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelKnn, 4, 0, 1, 1);

        comboBoxMatcherType = new QComboBox(groupBoxMatcher);
        comboBoxMatcherType->setObjectName(QStringLiteral("comboBoxMatcherType"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboBoxMatcherType->sizePolicy().hasHeightForWidth());
        comboBoxMatcherType->setSizePolicy(sizePolicy4);
        comboBoxMatcherType->setFont(font);

        gridLayout_2->addWidget(comboBoxMatcherType, 0, 1, 1, 1);

        comboBoxMatcherMode = new QComboBox(groupBoxMatcher);
        comboBoxMatcherMode->setObjectName(QStringLiteral("comboBoxMatcherMode"));
        sizePolicy4.setHeightForWidth(comboBoxMatcherMode->sizePolicy().hasHeightForWidth());
        comboBoxMatcherMode->setSizePolicy(sizePolicy4);
        comboBoxMatcherMode->setFont(font);

        gridLayout_2->addWidget(comboBoxMatcherMode, 2, 1, 1, 1);

        labelRadius = new QLabel(groupBoxMatcher);
        labelRadius->setObjectName(QStringLiteral("labelRadius"));
        labelRadius->setFont(font);
        labelRadius->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelRadius, 5, 0, 1, 1);

        doubleSpinBoxRadius = new QDoubleSpinBox(groupBoxMatcher);
        doubleSpinBoxRadius->setObjectName(QStringLiteral("doubleSpinBoxRadius"));
        sizePolicy4.setHeightForWidth(doubleSpinBoxRadius->sizePolicy().hasHeightForWidth());
        doubleSpinBoxRadius->setSizePolicy(sizePolicy4);
        doubleSpinBoxRadius->setDecimals(2);
        doubleSpinBoxRadius->setMaximum(1);
        doubleSpinBoxRadius->setSingleStep(0.01);
        doubleSpinBoxRadius->setValue(0.1);

        gridLayout_2->addWidget(doubleSpinBoxRadius, 5, 1, 1, 1);

        labelMached = new QLabel(groupBoxMatcher);
        labelMached->setObjectName(QStringLiteral("labelMached"));
        labelMached->setFont(font);
        labelMached->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelMached, 6, 0, 1, 1);

        labelMatchedNumber = new QLabel(groupBoxMatcher);
        labelMatchedNumber->setObjectName(QStringLiteral("labelMatchedNumber"));
        labelMatchedNumber->setFont(font);

        gridLayout_2->addWidget(labelMatchedNumber, 6, 1, 1, 1);

        groupBoxMatchDistances = new QGroupBox(groupBoxMatcher);
        groupBoxMatchDistances->setObjectName(QStringLiteral("groupBoxMatchDistances"));
        gridLayout_3 = new QGridLayout(groupBoxMatchDistances);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(4, 4, 4, 4);
        labelDistMean = new QLabel(groupBoxMatchDistances);
        labelDistMean->setObjectName(QStringLiteral("labelDistMean"));
        labelDistMean->setFont(font);

        gridLayout_3->addWidget(labelDistMean, 0, 0, 1, 1);

        labelDistMeanNumber = new QLabel(groupBoxMatchDistances);
        labelDistMeanNumber->setObjectName(QStringLiteral("labelDistMeanNumber"));
        labelDistMeanNumber->setFont(font);

        gridLayout_3->addWidget(labelDistMeanNumber, 0, 1, 1, 1);

        labelDistMin = new QLabel(groupBoxMatchDistances);
        labelDistMin->setObjectName(QStringLiteral("labelDistMin"));
        labelDistMin->setFont(font);

        gridLayout_3->addWidget(labelDistMin, 1, 0, 1, 1);

        labelDistMinNumber = new QLabel(groupBoxMatchDistances);
        labelDistMinNumber->setObjectName(QStringLiteral("labelDistMinNumber"));
        labelDistMinNumber->setFont(font);

        gridLayout_3->addWidget(labelDistMinNumber, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBoxMatchDistances, 7, 0, 1, 2);

        spinBoxKnn = new QSpinBox(groupBoxMatcher);
        spinBoxKnn->setObjectName(QStringLiteral("spinBoxKnn"));
        sizePolicy4.setHeightForWidth(spinBoxKnn->sizePolicy().hasHeightForWidth());
        spinBoxKnn->setSizePolicy(sizePolicy4);
        spinBoxKnn->setMaximum(5);
        spinBoxKnn->setValue(1);

        gridLayout_2->addWidget(spinBoxKnn, 4, 1, 1, 1);

        labelMatcherTime = new QLabel(groupBoxMatcher);
        labelMatcherTime->setObjectName(QStringLiteral("labelMatcherTime"));
        labelMatcherTime->setFont(font);
        labelMatcherTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelMatcherTime, 8, 0, 1, 1);

        labelMatcherTimeMs = new QLabel(groupBoxMatcher);
        labelMatcherTimeMs->setObjectName(QStringLiteral("labelMatcherTimeMs"));
        sizePolicy3.setHeightForWidth(labelMatcherTimeMs->sizePolicy().hasHeightForWidth());
        labelMatcherTimeMs->setSizePolicy(sizePolicy3);
        labelMatcherTimeMs->setFont(font);
        labelMatcherTimeMs->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelMatcherTimeMs, 8, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);

        gridLayout_4->addWidget(groupBoxMatcher, 5, 0, 1, 2);

        groupBoxRegistrar = new QGroupBox(processTab);
        groupBoxRegistrar->setObjectName(QStringLiteral("groupBoxRegistrar"));
        sizePolicy3.setHeightForWidth(groupBoxRegistrar->sizePolicy().hasHeightForWidth());
        groupBoxRegistrar->setSizePolicy(sizePolicy3);
        groupBoxRegistrar->setCheckable(true);
        groupBoxRegistrar->setChecked(false);
        gridLayout_5 = new QGridLayout(groupBoxRegistrar);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setVerticalSpacing(3);
        gridLayout_5->setContentsMargins(4, 4, 4, 4);
        labelReprojError = new QLabel(groupBoxRegistrar);
        labelReprojError->setObjectName(QStringLiteral("labelReprojError"));
        labelReprojError->setFont(font);
        labelReprojError->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(labelReprojError, 2, 0, 1, 1);

        labelReprojThres = new QLabel(groupBoxRegistrar);
        labelReprojThres->setObjectName(QStringLiteral("labelReprojThres"));
        labelReprojThres->setFont(font);
        labelReprojThres->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(labelReprojThres, 1, 0, 1, 1);

        doubleSpinBoxReprojThres = new QDoubleSpinBox(groupBoxRegistrar);
        doubleSpinBoxReprojThres->setObjectName(QStringLiteral("doubleSpinBoxReprojThres"));
        doubleSpinBoxReprojThres->setDecimals(1);
        doubleSpinBoxReprojThres->setMaximum(20);
        doubleSpinBoxReprojThres->setSingleStep(0.1);
        doubleSpinBoxReprojThres->setValue(3);

        gridLayout_5->addWidget(doubleSpinBoxReprojThres, 1, 1, 1, 1);

        labelReprojErrorNumber = new QLabel(groupBoxRegistrar);
        labelReprojErrorNumber->setObjectName(QStringLiteral("labelReprojErrorNumber"));
        labelReprojErrorNumber->setFont(font);

        gridLayout_5->addWidget(labelReprojErrorNumber, 2, 1, 1, 1);

        labelInliers = new QLabel(groupBoxRegistrar);
        labelInliers->setObjectName(QStringLiteral("labelInliers"));
        labelInliers->setFont(font);
        labelInliers->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(labelInliers, 3, 0, 1, 1);

        labelInliersNumber = new QLabel(groupBoxRegistrar);
        labelInliersNumber->setObjectName(QStringLiteral("labelInliersNumber"));
        labelInliersNumber->setFont(font);

        gridLayout_5->addWidget(labelInliersNumber, 3, 1, 1, 1);

        labelPrintSize = new QLabel(groupBoxRegistrar);
        labelPrintSize->setObjectName(QStringLiteral("labelPrintSize"));
        labelPrintSize->setFont(font);
        labelPrintSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(labelPrintSize, 0, 0, 1, 1);

        doubleSpinBoxPrintSize = new QDoubleSpinBox(groupBoxRegistrar);
        doubleSpinBoxPrintSize->setObjectName(QStringLiteral("doubleSpinBoxPrintSize"));
        doubleSpinBoxPrintSize->setDecimals(1);
        doubleSpinBoxPrintSize->setMinimum(10);
        doubleSpinBoxPrintSize->setMaximum(300);
        doubleSpinBoxPrintSize->setSingleStep(0.1);
        doubleSpinBoxPrintSize->setValue(178.1);

        gridLayout_5->addWidget(doubleSpinBoxPrintSize, 0, 1, 1, 1);

        checkBoxCameraSet = new QCheckBox(groupBoxRegistrar);
        checkBoxCameraSet->setObjectName(QStringLiteral("checkBoxCameraSet"));
        checkBoxCameraSet->setFont(font);
        checkBoxCameraSet->setLayoutDirection(Qt::RightToLeft);
        checkBoxCameraSet->setCheckable(false);

        gridLayout_5->addWidget(checkBoxCameraSet, 4, 0, 1, 2);

        checkBoxShowFrame = new QCheckBox(groupBoxRegistrar);
        checkBoxShowFrame->setObjectName(QStringLiteral("checkBoxShowFrame"));
        checkBoxShowFrame->setFont(font);

        gridLayout_5->addWidget(checkBoxShowFrame, 5, 0, 1, 2);

        checkBoxUsePreviousPose = new QCheckBox(groupBoxRegistrar);
        checkBoxUsePreviousPose->setObjectName(QStringLiteral("checkBoxUsePreviousPose"));
        checkBoxUsePreviousPose->setFont(font);

        gridLayout_5->addWidget(checkBoxUsePreviousPose, 7, 0, 1, 2);

        labelRegTime = new QLabel(groupBoxRegistrar);
        labelRegTime->setObjectName(QStringLiteral("labelRegTime"));
        labelRegTime->setFont(font);
        labelRegTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(labelRegTime, 8, 0, 1, 1);

        labelRegTimeMS = new QLabel(groupBoxRegistrar);
        labelRegTimeMS->setObjectName(QStringLiteral("labelRegTimeMS"));
        labelRegTimeMS->setFont(font);
        labelRegTimeMS->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(labelRegTimeMS, 8, 1, 1, 1);

        checkBoxShowModelBox = new QCheckBox(groupBoxRegistrar);
        checkBoxShowModelBox->setObjectName(QStringLiteral("checkBoxShowModelBox"));
        checkBoxShowModelBox->setFont(font);

        gridLayout_5->addWidget(checkBoxShowModelBox, 6, 0, 1, 1);


        gridLayout_4->addWidget(groupBoxRegistrar, 6, 0, 1, 2);

        labelShowKP = new QLabel(processTab);
        labelShowKP->setObjectName(QStringLiteral("labelShowKP"));
        sizePolicy3.setHeightForWidth(labelShowKP->sizePolicy().hasHeightForWidth());
        labelShowKP->setSizePolicy(sizePolicy3);
        labelShowKP->setFont(font);

        gridLayout_4->addWidget(labelShowKP, 2, 0, 1, 1);

        comboBoxShowKPts = new QComboBox(processTab);
        comboBoxShowKPts->setObjectName(QStringLiteral("comboBoxShowKPts"));
        sizePolicy4.setHeightForWidth(comboBoxShowKPts->sizePolicy().hasHeightForWidth());
        comboBoxShowKPts->setSizePolicy(sizePolicy4);
        comboBoxShowKPts->setFont(font);

        gridLayout_4->addWidget(comboBoxShowKPts, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 7, 0, 1, 2);

        comboBoxTimeUnit = new QComboBox(processTab);
        comboBoxTimeUnit->setObjectName(QStringLiteral("comboBoxTimeUnit"));
        sizePolicy4.setHeightForWidth(comboBoxTimeUnit->sizePolicy().hasHeightForWidth());
        comboBoxTimeUnit->setSizePolicy(sizePolicy4);
        comboBoxTimeUnit->setFont(font);

        gridLayout_4->addWidget(comboBoxTimeUnit, 1, 1, 1, 1);

        labelTimeUnit = new QLabel(processTab);
        labelTimeUnit->setObjectName(QStringLiteral("labelTimeUnit"));
        labelTimeUnit->setFont(font);
        labelTimeUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(labelTimeUnit, 1, 0, 1, 1);

        groupBoxDetector = new QGroupBox(processTab);
        groupBoxDetector->setObjectName(QStringLiteral("groupBoxDetector"));
        sizePolicy3.setHeightForWidth(groupBoxDetector->sizePolicy().hasHeightForWidth());
        groupBoxDetector->setSizePolicy(sizePolicy3);
        groupBoxDetector->setCheckable(true);
        groupBoxDetector->setChecked(false);
        gridLayout = new QGridLayout(groupBoxDetector);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setHorizontalSpacing(-1);
        gridLayout->setVerticalSpacing(3);
        gridLayout->setContentsMargins(4, 4, 4, 4);
        labelDetectorTimeMs = new QLabel(groupBoxDetector);
        labelDetectorTimeMs->setObjectName(QStringLiteral("labelDetectorTimeMs"));
        sizePolicy3.setHeightForWidth(labelDetectorTimeMs->sizePolicy().hasHeightForWidth());
        labelDetectorTimeMs->setSizePolicy(sizePolicy3);
        labelDetectorTimeMs->setFont(font);
        labelDetectorTimeMs->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelDetectorTimeMs, 10, 2, 1, 1);

        labelDescriptors = new QLabel(groupBoxDetector);
        labelDescriptors->setObjectName(QStringLiteral("labelDescriptors"));
        labelDescriptors->setFont(font);

        gridLayout->addWidget(labelDescriptors, 2, 0, 1, 2);

        labelModel = new QLabel(groupBoxDetector);
        labelModel->setObjectName(QStringLiteral("labelModel"));
        labelModel->setFont(font);
        labelModel->setTextFormat(Qt::AutoText);
        labelModel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelModel, 4, 0, 1, 2);

        comboBoxFeatures = new QComboBox(groupBoxDetector);
        comboBoxFeatures->setObjectName(QStringLiteral("comboBoxFeatures"));
        sizePolicy4.setHeightForWidth(comboBoxFeatures->sizePolicy().hasHeightForWidth());
        comboBoxFeatures->setSizePolicy(sizePolicy4);
        comboBoxFeatures->setFont(font);

        gridLayout->addWidget(comboBoxFeatures, 0, 2, 1, 1);

        comboBoxDescriptors = new QComboBox(groupBoxDetector);
        comboBoxDescriptors->setObjectName(QStringLiteral("comboBoxDescriptors"));
        sizePolicy4.setHeightForWidth(comboBoxDescriptors->sizePolicy().hasHeightForWidth());
        comboBoxDescriptors->setSizePolicy(sizePolicy4);
        comboBoxDescriptors->setFont(font);

        gridLayout->addWidget(comboBoxDescriptors, 2, 2, 1, 1);

        labelModelKPts = new QLabel(groupBoxDetector);
        labelModelKPts->setObjectName(QStringLiteral("labelModelKPts"));
        sizePolicy3.setHeightForWidth(labelModelKPts->sizePolicy().hasHeightForWidth());
        labelModelKPts->setSizePolicy(sizePolicy3);
        labelModelKPts->setFont(font);
        labelModelKPts->setTextFormat(Qt::AutoText);

        gridLayout->addWidget(labelModelKPts, 4, 2, 1, 1);

        labelScene = new QLabel(groupBoxDetector);
        labelScene->setObjectName(QStringLiteral("labelScene"));
        labelScene->setFont(font);
        labelScene->setTextFormat(Qt::AutoText);
        labelScene->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelScene, 6, 0, 1, 2);

        labelSceneKPts = new QLabel(groupBoxDetector);
        labelSceneKPts->setObjectName(QStringLiteral("labelSceneKPts"));
        sizePolicy3.setHeightForWidth(labelSceneKPts->sizePolicy().hasHeightForWidth());
        labelSceneKPts->setSizePolicy(sizePolicy3);
        labelSceneKPts->setFont(font);
        labelSceneKPts->setTextFormat(Qt::AutoText);

        gridLayout->addWidget(labelSceneKPts, 6, 2, 1, 1);

        labelDescriptorsTime = new QLabel(groupBoxDetector);
        labelDescriptorsTime->setObjectName(QStringLiteral("labelDescriptorsTime"));
        labelDescriptorsTime->setFont(font);
        labelDescriptorsTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelDescriptorsTime, 13, 0, 1, 2);

        labelFeatures = new QLabel(groupBoxDetector);
        labelFeatures->setObjectName(QStringLiteral("labelFeatures"));
        labelFeatures->setFont(font);

        gridLayout->addWidget(labelFeatures, 0, 0, 1, 2);

        labelDescriptorsTimeMs = new QLabel(groupBoxDetector);
        labelDescriptorsTimeMs->setObjectName(QStringLiteral("labelDescriptorsTimeMs"));
        sizePolicy3.setHeightForWidth(labelDescriptorsTimeMs->sizePolicy().hasHeightForWidth());
        labelDescriptorsTimeMs->setSizePolicy(sizePolicy3);
        labelDescriptorsTimeMs->setFont(font);
        labelDescriptorsTimeMs->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelDescriptorsTimeMs, 13, 2, 1, 1);

        labelDetectorTime = new QLabel(groupBoxDetector);
        labelDetectorTime->setObjectName(QStringLiteral("labelDetectorTime"));
        labelDetectorTime->setFont(font);
        labelDetectorTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelDetectorTime, 10, 0, 1, 2);


        gridLayout_4->addWidget(groupBoxDetector, 3, 0, 1, 2);

        tabWidget->addTab(processTab, QString());
        parameterTab = new QWidget();
        parameterTab->setObjectName(QStringLiteral("parameterTab"));
        verticalLayout_2 = new QVBoxLayout(parameterTab);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 0, 2, 0);
        detectorParamBox = new QGroupBox(parameterTab);
        detectorParamBox->setObjectName(QStringLiteral("detectorParamBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(detectorParamBox->sizePolicy().hasHeightForWidth());
        detectorParamBox->setSizePolicy(sizePolicy5);
        detectorParamBox->setFont(font);
        detectorBoxVerticalLayout = new QVBoxLayout(detectorParamBox);
        detectorBoxVerticalLayout->setSpacing(6);
        detectorBoxVerticalLayout->setContentsMargins(11, 11, 11, 11);
        detectorBoxVerticalLayout->setObjectName(QStringLiteral("detectorBoxVerticalLayout"));
        detectorBoxVerticalLayout->setContentsMargins(2, 2, 2, 2);
        detectorParam1Label = new QLabel(detectorParamBox);
        detectorParam1Label->setObjectName(QStringLiteral("detectorParam1Label"));

        detectorBoxVerticalLayout->addWidget(detectorParam1Label);

        detectorParam2Label = new QLabel(detectorParamBox);
        detectorParam2Label->setObjectName(QStringLiteral("detectorParam2Label"));

        detectorBoxVerticalLayout->addWidget(detectorParam2Label);


        verticalLayout_2->addWidget(detectorParamBox);

        extractorParamBox = new QGroupBox(parameterTab);
        extractorParamBox->setObjectName(QStringLiteral("extractorParamBox"));
        sizePolicy5.setHeightForWidth(extractorParamBox->sizePolicy().hasHeightForWidth());
        extractorParamBox->setSizePolicy(sizePolicy5);
        extractorParamBox->setFont(font);
        exctractorBoxVerticalLayout = new QVBoxLayout(extractorParamBox);
        exctractorBoxVerticalLayout->setSpacing(6);
        exctractorBoxVerticalLayout->setContentsMargins(11, 11, 11, 11);
        exctractorBoxVerticalLayout->setObjectName(QStringLiteral("exctractorBoxVerticalLayout"));
        exctractorBoxVerticalLayout->setContentsMargins(2, 2, 2, 2);
        extractorParam1Label = new QLabel(extractorParamBox);
        extractorParam1Label->setObjectName(QStringLiteral("extractorParam1Label"));

        exctractorBoxVerticalLayout->addWidget(extractorParam1Label);


        verticalLayout_2->addWidget(extractorParamBox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        tabWidget->addTab(parameterTab, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1006, 22));
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
        menuSources->addAction(actionModel);
        menuSources->addAction(actionCalibData);
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

        tabWidget->setCurrentIndex(1);
        comboBoxMatcherType->setCurrentIndex(0);
        comboBoxMatcherMode->setCurrentIndex(0);
        comboBoxShowKPts->setCurrentIndex(0);
        comboBoxFeatures->setCurrentIndex(3);
        comboBoxDescriptors->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Detection / Matching / Registration", 0));
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
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionRenderImage->setText(QApplication::translate("MainWindow", "Image", 0));
        actionRenderPixmap->setText(QApplication::translate("MainWindow", "Pixmap", 0));
        actionRenderOpenGL->setText(QApplication::translate("MainWindow", "OpenGL", 0));
        actionGray->setText(QApplication::translate("MainWindow", "gray", 0));
        actionCalibData->setText(QApplication::translate("MainWindow", "Camera parameters", 0));
        actionModel->setText(QApplication::translate("MainWindow", "Model image", 0));
        radioButtonOrigSize->setText(QApplication::translate("MainWindow", "Originale", 0));
        radioButtonCustomSize->setText(QApplication::translate("MainWindow", "Custom", 0));
        labelWidth->setText(QApplication::translate("MainWindow", "Largeur", 0));
        labelHeight->setText(QApplication::translate("MainWindow", "Hauteur", 0));
        checkBoxFlip->setText(QApplication::translate("MainWindow", "Flip", 0));
        checkBoxGray->setText(QApplication::translate("MainWindow", "Gray", 0));
        tabWidget->setTabText(tabWidget->indexOf(captureTab), QApplication::translate("MainWindow", "Size", 0));
        groupBoxMatcher->setTitle(QApplication::translate("MainWindow", "Matcher", 0));
        labelMatcherType->setText(QApplication::translate("MainWindow", "Type", 0));
        labelMatcherMode->setText(QApplication::translate("MainWindow", "Match Mode", 0));
        labelKnn->setText(QApplication::translate("MainWindow", "Knn", 0));
        comboBoxMatcherType->clear();
        comboBoxMatcherType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Brute Force", 0)
         << QApplication::translate("MainWindow", "Brute Force L1", 0)
         << QApplication::translate("MainWindow", "Brute Force Hamming", 0)
         << QApplication::translate("MainWindow", "Brute Force Hamming (2)", 0)
         << QApplication::translate("MainWindow", "Flann Based", 0)
        );
        comboBoxMatcherMode->clear();
        comboBoxMatcherMode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Simple", 0)
         << QApplication::translate("MainWindow", "Cross Best Knn", 0)
         << QApplication::translate("MainWindow", "Cross Radius", 0)
        );
        labelRadius->setText(QApplication::translate("MainWindow", "Radius", 0));
        labelMached->setText(QApplication::translate("MainWindow", "Matched:", 0));
        labelMatchedNumber->setText(QApplication::translate("MainWindow", "0", 0));
        groupBoxMatchDistances->setTitle(QApplication::translate("MainWindow", "Match distances", 0));
        labelDistMean->setText(QApplication::translate("MainWindow", "Mean", 0));
        labelDistMeanNumber->setText(QApplication::translate("MainWindow", "0.00", 0));
        labelDistMin->setText(QApplication::translate("MainWindow", "Min/Max", 0));
        labelDistMinNumber->setText(QApplication::translate("MainWindow", "0.00", 0));
        labelMatcherTime->setText(QApplication::translate("MainWindow", "Matching time :", 0));
        labelMatcherTimeMs->setText(QApplication::translate("MainWindow", "0", 0));
        groupBoxRegistrar->setTitle(QApplication::translate("MainWindow", "Registrar", 0));
        labelReprojError->setText(QApplication::translate("MainWindow", "Reproj. Error", 0));
        labelReprojThres->setText(QApplication::translate("MainWindow", "Reproj. Thres.", 0));
        labelReprojErrorNumber->setText(QApplication::translate("MainWindow", "0.00", 0));
        labelInliers->setText(QApplication::translate("MainWindow", "Inliers:", 0));
        labelInliersNumber->setText(QApplication::translate("MainWindow", "0", 0));
        labelPrintSize->setText(QApplication::translate("MainWindow", "Print Size", 0));
        checkBoxCameraSet->setText(QApplication::translate("MainWindow", "Camera parameters set", 0));
        checkBoxShowFrame->setText(QApplication::translate("MainWindow", "Show Model Frame", 0));
        checkBoxUsePreviousPose->setText(QApplication::translate("MainWindow", "Use Previous Pose", 0));
        labelRegTime->setText(QApplication::translate("MainWindow", "Registration time:", 0));
        labelRegTimeMS->setText(QApplication::translate("MainWindow", "0", 0));
        checkBoxShowModelBox->setText(QApplication::translate("MainWindow", "Compute Pose", 0));
        labelShowKP->setText(QApplication::translate("MainWindow", "Show Keypoints", 0));
        comboBoxShowKPts->clear();
        comboBoxShowKPts->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", 0)
         << QApplication::translate("MainWindow", "All", 0)
         << QApplication::translate("MainWindow", "Matched", 0)
         << QApplication::translate("MainWindow", "Inliers", 0)
        );
        comboBoxTimeUnit->clear();
        comboBoxTimeUnit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\316\274s", 0)
         << QApplication::translate("MainWindow", "\316\274s/pt", 0)
        );
        labelTimeUnit->setText(QApplication::translate("MainWindow", "Time unit", 0));
        groupBoxDetector->setTitle(QApplication::translate("MainWindow", "Detector", 0));
        labelDetectorTimeMs->setText(QApplication::translate("MainWindow", "0", 0));
        labelDescriptors->setText(QApplication::translate("MainWindow", "Descriptors", 0));
        labelModel->setText(QApplication::translate("MainWindow", "Model:", 0));
        comboBoxFeatures->clear();
        comboBoxFeatures->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "FAST", 0)
         << QApplication::translate("MainWindow", "STAR", 0)
         << QApplication::translate("MainWindow", "SIFT", 0)
         << QApplication::translate("MainWindow", "SURF", 0)
         << QApplication::translate("MainWindow", "ORB", 0)
         << QApplication::translate("MainWindow", "BRISK", 0)
         << QApplication::translate("MainWindow", "MSER", 0)
         << QApplication::translate("MainWindow", "GFTT", 0)
         << QApplication::translate("MainWindow", "HARRIS", 0)
        );
        comboBoxDescriptors->clear();
        comboBoxDescriptors->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "SIFT", 0)
         << QApplication::translate("MainWindow", "SURF", 0)
         << QApplication::translate("MainWindow", "ORB", 0)
         << QApplication::translate("MainWindow", "BRISK", 0)
         << QApplication::translate("MainWindow", "BRIEF", 0)
         << QApplication::translate("MainWindow", "FREAK", 0)
        );
        labelModelKPts->setText(QApplication::translate("MainWindow", "0", 0));
        labelScene->setText(QApplication::translate("MainWindow", "Scene:", 0));
        labelSceneKPts->setText(QApplication::translate("MainWindow", "0", 0));
        labelDescriptorsTime->setText(QApplication::translate("MainWindow", "Descriptors time :", 0));
        labelFeatures->setText(QApplication::translate("MainWindow", "Features", 0));
        labelDescriptorsTimeMs->setText(QApplication::translate("MainWindow", "0", 0));
        labelDetectorTime->setText(QApplication::translate("MainWindow", "Detection time :", 0));
        tabWidget->setTabText(tabWidget->indexOf(processTab), QApplication::translate("MainWindow", "Process", 0));
        detectorParamBox->setTitle(QApplication::translate("MainWindow", "Detector parameters", 0));
        detectorParam1Label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        detectorParam2Label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        extractorParamBox->setTitle(QApplication::translate("MainWindow", "Extractor Parameters", 0));
        extractorParam1Label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(parameterTab), QApplication::translate("MainWindow", "Parameters", 0));
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
