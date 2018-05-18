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
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollAreaSource;
    QcvMatWidget *sourceImage;
    QTabWidget *tabWidgetFilters;
    QWidget *tabImage;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxSize;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButtonOrigSize;
    QRadioButton *radioButtonCustomSize;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelWidth;
    QSpinBox *spinBoxWidth;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelHeight;
    QSpinBox *spinBoxHeight;
    QGroupBox *groupBoxConv;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBoxFlip;
    QComboBox *comboBoxImages;
    QComboBox *comboBoxEdges;
    QSpacerItem *horizontalSpacer;
    QWidget *tabVariables;
    QGridLayout *gridLayout_2;
    QLabel *labelSigma;
    QLabel *labelSigmaMin;
    QSlider *horizontalSliderSigma;
    QLabel *labelSigmaMax;
    QDoubleSpinBox *doubleSpinBoxSigma;
    QLabel *labelKernel;
    QLabel *labelKernelMin;
    QSlider *horizontalSliderKernel;
    QLabel *labelKernelMax;
    QSpinBox *spinBoxKernel;
    QLabel *labelThreshold;
    QLabel *labelThresholdMin;
    QSlider *horizontalSliderThreshold;
    QLabel *labelThresholdMax;
    QSpinBox *spinBoxThreshold;
    QLabel *labelKappa;
    QLabel *labelKappaMin;
    QSlider *horizontalSliderKappa;
    QLabel *labelKappaMax;
    QDoubleSpinBox *doubleSpinBoxKappa;
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
        MainWindow->resize(714, 561);
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
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollAreaSource = new QScrollArea(centralWidget);
        scrollAreaSource->setObjectName(QStringLiteral("scrollAreaSource"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaSource->sizePolicy().hasHeightForWidth());
        scrollAreaSource->setSizePolicy(sizePolicy);
        scrollAreaSource->setWidgetResizable(true);
        scrollAreaSource->setAlignment(Qt::AlignCenter);
        sourceImage = new QcvMatWidget();
        sourceImage->setObjectName(QStringLiteral("sourceImage"));
        sourceImage->setGeometry(QRect(0, 0, 688, 309));
        scrollAreaSource->setWidget(sourceImage);

        verticalLayout->addWidget(scrollAreaSource);

        tabWidgetFilters = new QTabWidget(centralWidget);
        tabWidgetFilters->setObjectName(QStringLiteral("tabWidgetFilters"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidgetFilters->sizePolicy().hasHeightForWidth());
        tabWidgetFilters->setSizePolicy(sizePolicy1);
        tabImage = new QWidget();
        tabImage->setObjectName(QStringLiteral("tabImage"));
        horizontalLayout = new QHBoxLayout(tabImage);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(8, 8, 8, 8);
        groupBoxSize = new QGroupBox(tabImage);
        groupBoxSize->setObjectName(QStringLiteral("groupBoxSize"));
        horizontalLayout_4 = new QHBoxLayout(groupBoxSize);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(8, 8, 8, 8);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        radioButtonOrigSize = new QRadioButton(groupBoxSize);
        radioButtonOrigSize->setObjectName(QStringLiteral("radioButtonOrigSize"));
        radioButtonOrigSize->setChecked(true);

        verticalLayout_6->addWidget(radioButtonOrigSize);

        radioButtonCustomSize = new QRadioButton(groupBoxSize);
        radioButtonCustomSize->setObjectName(QStringLiteral("radioButtonCustomSize"));

        verticalLayout_6->addWidget(radioButtonCustomSize);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelWidth = new QLabel(groupBoxSize);
        labelWidth->setObjectName(QStringLiteral("labelWidth"));

        horizontalLayout_2->addWidget(labelWidth);

        spinBoxWidth = new QSpinBox(groupBoxSize);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMaximum(1600);
        spinBoxWidth->setSingleStep(4);

        horizontalLayout_2->addWidget(spinBoxWidth);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelHeight = new QLabel(groupBoxSize);
        labelHeight->setObjectName(QStringLiteral("labelHeight"));

        horizontalLayout_3->addWidget(labelHeight);

        spinBoxHeight = new QSpinBox(groupBoxSize);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMaximum(1200);
        spinBoxHeight->setSingleStep(4);

        horizontalLayout_3->addWidget(spinBoxHeight);


        verticalLayout_5->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_5);


        horizontalLayout->addWidget(groupBoxSize);

        groupBoxConv = new QGroupBox(tabImage);
        groupBoxConv->setObjectName(QStringLiteral("groupBoxConv"));
        verticalLayout_2 = new QVBoxLayout(groupBoxConv);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(8, 8, 8, 8);
        checkBoxFlip = new QCheckBox(groupBoxConv);
        checkBoxFlip->setObjectName(QStringLiteral("checkBoxFlip"));

        verticalLayout_2->addWidget(checkBoxFlip);

        comboBoxImages = new QComboBox(groupBoxConv);
        comboBoxImages->setObjectName(QStringLiteral("comboBoxImages"));

        verticalLayout_2->addWidget(comboBoxImages);

        comboBoxEdges = new QComboBox(groupBoxConv);
        comboBoxEdges->setObjectName(QStringLiteral("comboBoxEdges"));

        verticalLayout_2->addWidget(comboBoxEdges);


        horizontalLayout->addWidget(groupBoxConv);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tabWidgetFilters->addTab(tabImage, QString());
        tabVariables = new QWidget();
        tabVariables->setObjectName(QStringLiteral("tabVariables"));
        gridLayout_2 = new QGridLayout(tabVariables);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(8, 8, 8, 8);
        labelSigma = new QLabel(tabVariables);
        labelSigma->setObjectName(QStringLiteral("labelSigma"));

        gridLayout_2->addWidget(labelSigma, 1, 0, 1, 1);

        labelSigmaMin = new QLabel(tabVariables);
        labelSigmaMin->setObjectName(QStringLiteral("labelSigmaMin"));
        labelSigmaMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelSigmaMin, 1, 1, 1, 1);

        horizontalSliderSigma = new QSlider(tabVariables);
        horizontalSliderSigma->setObjectName(QStringLiteral("horizontalSliderSigma"));
        horizontalSliderSigma->setMaximum(315);
        horizontalSliderSigma->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSliderSigma, 1, 2, 1, 1);

        labelSigmaMax = new QLabel(tabVariables);
        labelSigmaMax->setObjectName(QStringLiteral("labelSigmaMax"));

        gridLayout_2->addWidget(labelSigmaMax, 1, 3, 1, 1);

        doubleSpinBoxSigma = new QDoubleSpinBox(tabVariables);
        doubleSpinBoxSigma->setObjectName(QStringLiteral("doubleSpinBoxSigma"));
        doubleSpinBoxSigma->setMinimum(0.35);
        doubleSpinBoxSigma->setMaximum(3.5);
        doubleSpinBoxSigma->setSingleStep(0.01);

        gridLayout_2->addWidget(doubleSpinBoxSigma, 1, 4, 1, 1);

        labelKernel = new QLabel(tabVariables);
        labelKernel->setObjectName(QStringLiteral("labelKernel"));

        gridLayout_2->addWidget(labelKernel, 0, 0, 1, 1);

        labelKernelMin = new QLabel(tabVariables);
        labelKernelMin->setObjectName(QStringLiteral("labelKernelMin"));
        labelKernelMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelKernelMin, 0, 1, 1, 1);

        horizontalSliderKernel = new QSlider(tabVariables);
        horizontalSliderKernel->setObjectName(QStringLiteral("horizontalSliderKernel"));
        horizontalSliderKernel->setMinimum(3);
        horizontalSliderKernel->setMaximum(15);
        horizontalSliderKernel->setSingleStep(2);
        horizontalSliderKernel->setPageStep(2);
        horizontalSliderKernel->setValue(3);
        horizontalSliderKernel->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSliderKernel, 0, 2, 1, 1);

        labelKernelMax = new QLabel(tabVariables);
        labelKernelMax->setObjectName(QStringLiteral("labelKernelMax"));

        gridLayout_2->addWidget(labelKernelMax, 0, 3, 1, 1);

        spinBoxKernel = new QSpinBox(tabVariables);
        spinBoxKernel->setObjectName(QStringLiteral("spinBoxKernel"));
        spinBoxKernel->setMinimum(3);
        spinBoxKernel->setMaximum(15);
        spinBoxKernel->setSingleStep(2);

        gridLayout_2->addWidget(spinBoxKernel, 0, 4, 1, 1);

        labelThreshold = new QLabel(tabVariables);
        labelThreshold->setObjectName(QStringLiteral("labelThreshold"));

        gridLayout_2->addWidget(labelThreshold, 2, 0, 1, 1);

        labelThresholdMin = new QLabel(tabVariables);
        labelThresholdMin->setObjectName(QStringLiteral("labelThresholdMin"));
        labelThresholdMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelThresholdMin, 2, 1, 1, 1);

        horizontalSliderThreshold = new QSlider(tabVariables);
        horizontalSliderThreshold->setObjectName(QStringLiteral("horizontalSliderThreshold"));
        horizontalSliderThreshold->setMaximum(255);
        horizontalSliderThreshold->setValue(127);
        horizontalSliderThreshold->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSliderThreshold, 2, 2, 1, 1);

        labelThresholdMax = new QLabel(tabVariables);
        labelThresholdMax->setObjectName(QStringLiteral("labelThresholdMax"));

        gridLayout_2->addWidget(labelThresholdMax, 2, 3, 1, 1);

        spinBoxThreshold = new QSpinBox(tabVariables);
        spinBoxThreshold->setObjectName(QStringLiteral("spinBoxThreshold"));
        spinBoxThreshold->setMaximum(255);
        spinBoxThreshold->setValue(127);

        gridLayout_2->addWidget(spinBoxThreshold, 2, 4, 1, 1);

        labelKappa = new QLabel(tabVariables);
        labelKappa->setObjectName(QStringLiteral("labelKappa"));

        gridLayout_2->addWidget(labelKappa, 3, 0, 1, 1);

        labelKappaMin = new QLabel(tabVariables);
        labelKappaMin->setObjectName(QStringLiteral("labelKappaMin"));
        labelKappaMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelKappaMin, 3, 1, 1, 1);

        horizontalSliderKappa = new QSlider(tabVariables);
        horizontalSliderKappa->setObjectName(QStringLiteral("horizontalSliderKappa"));
        horizontalSliderKappa->setMaximum(11);
        horizontalSliderKappa->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSliderKappa, 3, 2, 1, 1);

        labelKappaMax = new QLabel(tabVariables);
        labelKappaMax->setObjectName(QStringLiteral("labelKappaMax"));

        gridLayout_2->addWidget(labelKappaMax, 3, 3, 1, 1);

        doubleSpinBoxKappa = new QDoubleSpinBox(tabVariables);
        doubleSpinBoxKappa->setObjectName(QStringLiteral("doubleSpinBoxKappa"));
        doubleSpinBoxKappa->setMinimum(0.04);
        doubleSpinBoxKappa->setMaximum(0.15);
        doubleSpinBoxKappa->setSingleStep(0.01);

        gridLayout_2->addWidget(doubleSpinBoxKappa, 3, 4, 1, 1);

        tabWidgetFilters->addTab(tabVariables, QString());

        verticalLayout->addWidget(tabWidgetFilters);

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
        QWidget::setTabOrder(radioButtonOrigSize, radioButtonCustomSize);
        QWidget::setTabOrder(radioButtonCustomSize, spinBoxWidth);
        QWidget::setTabOrder(spinBoxWidth, spinBoxHeight);
        QWidget::setTabOrder(spinBoxHeight, checkBoxFlip);
        QWidget::setTabOrder(checkBoxFlip, comboBoxImages);
        QWidget::setTabOrder(comboBoxImages, comboBoxEdges);
        QWidget::setTabOrder(comboBoxEdges, spinBoxKernel);
        QWidget::setTabOrder(spinBoxKernel, doubleSpinBoxSigma);
        QWidget::setTabOrder(doubleSpinBoxSigma, spinBoxThreshold);
        QWidget::setTabOrder(spinBoxThreshold, doubleSpinBoxKappa);
        QWidget::setTabOrder(doubleSpinBoxKappa, horizontalSliderKernel);
        QWidget::setTabOrder(horizontalSliderKernel, horizontalSliderSigma);
        QWidget::setTabOrder(horizontalSliderSigma, horizontalSliderThreshold);
        QWidget::setTabOrder(horizontalSliderThreshold, horizontalSliderKappa);
        QWidget::setTabOrder(horizontalSliderKappa, tabWidgetFilters);
        QWidget::setTabOrder(tabWidgetFilters, scrollAreaSource);

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
        QObject::connect(spinBoxKernel, SIGNAL(valueChanged(int)), horizontalSliderKernel, SLOT(setValue(int)));
        QObject::connect(horizontalSliderKernel, SIGNAL(valueChanged(int)), spinBoxKernel, SLOT(setValue(int)));
        QObject::connect(spinBoxThreshold, SIGNAL(valueChanged(int)), horizontalSliderThreshold, SLOT(setValue(int)));
        QObject::connect(horizontalSliderThreshold, SIGNAL(valueChanged(int)), spinBoxThreshold, SLOT(setValue(int)));

        tabWidgetFilters->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Filter and Derivatives", 0));
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
        groupBoxSize->setTitle(QApplication::translate("MainWindow", "Size", 0));
        radioButtonOrigSize->setText(QApplication::translate("MainWindow", "Original", 0));
        radioButtonCustomSize->setText(QApplication::translate("MainWindow", "Custom", 0));
        labelWidth->setText(QApplication::translate("MainWindow", "Width", 0));
        labelHeight->setText(QApplication::translate("MainWindow", "Height", 0));
        groupBoxConv->setTitle(QApplication::translate("MainWindow", "Conversions", 0));
        checkBoxFlip->setText(QApplication::translate("MainWindow", "Flip", 0));
        comboBoxImages->clear();
        comboBoxImages->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Input", 0)
         << QApplication::translate("MainWindow", "Gray", 0)
         << QApplication::translate("MainWindow", "Blurred", 0)
         << QApplication::translate("MainWindow", "X Gradient", 0)
         << QApplication::translate("MainWindow", "Y Gradient", 0)
         << QApplication::translate("MainWindow", "Gradient Magnitude", 0)
         << QApplication::translate("MainWindow", "Gradient Angle", 0)
         << QApplication::translate("MainWindow", "Edge Map", 0)
         << QApplication::translate("MainWindow", "Laplacian", 0)
         << QApplication::translate("MainWindow", "Cornerness", 0)
         << QApplication::translate("MainWindow", "Harris Cornerness", 0)
        );
        comboBoxEdges->clear();
        comboBoxEdges->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Threshold", 0)
         << QApplication::translate("MainWindow", "Canny", 0)
         << QApplication::translate("MainWindow", "Merged", 0)
        );
        tabWidgetFilters->setTabText(tabWidgetFilters->indexOf(tabImage), QApplication::translate("MainWindow", "Image", 0));
        labelSigma->setText(QApplication::translate("MainWindow", "Sigma", 0));
        labelSigmaMin->setText(QApplication::translate("MainWindow", "0.0", 0));
        labelSigmaMax->setText(QApplication::translate("MainWindow", "1.0", 0));
        labelKernel->setText(QApplication::translate("MainWindow", "Kernel", 0));
        labelKernelMin->setText(QApplication::translate("MainWindow", "3", 0));
        labelKernelMax->setText(QApplication::translate("MainWindow", "15", 0));
        labelThreshold->setText(QApplication::translate("MainWindow", "Threshold", 0));
        labelThresholdMin->setText(QApplication::translate("MainWindow", "0", 0));
        labelThresholdMax->setText(QApplication::translate("MainWindow", "255", 0));
        labelKappa->setText(QApplication::translate("MainWindow", "Kappa", 0));
        labelKappaMin->setText(QApplication::translate("MainWindow", "0.04", 0));
        labelKappaMax->setText(QApplication::translate("MainWindow", "0.15", 0));
        tabWidgetFilters->setTabText(tabWidgetFilters->indexOf(tabVariables), QApplication::translate("MainWindow", "Variables", 0));
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
