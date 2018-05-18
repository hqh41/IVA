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
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QScrollArea *scrollAreaSource;
    QcvMatWidget *sourceImage;
    QScrollArea *scrollAreaSpectrum;
    QcvMatWidget *spectrumImage;
    QScrollArea *scrollAreaInverse;
    QcvMatWidget *inverseImage;
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
    QCheckBox *checkBoxGray;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBoxFFT;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelMag;
    QSpinBox *spinBoxMag;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelFFTSizeTitle;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelFFTSizeValue;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBoxFiltering;
    QRadioButton *radioButtonFilterBox;
    QRadioButton *radioButtonFilterGauss;
    QRadioButton *radioButtonFilterSinc;
    QSpacerItem *horizontalSpacer;
    QWidget *tabLowPass;
    QGridLayout *gridLayout_2;
    QLabel *labelRedLP;
    QSlider *horizontalSliderRLP;
    QLabel *labelGreenLP;
    QSlider *horizontalSliderGLP;
    QLabel *labelBlueLP;
    QSlider *horizontalSliderBLP;
    QSpinBox *spinBoxRedLP;
    QSpinBox *spinBoxGreenLP;
    QSpinBox *spinBoxBlueLP;
    QCheckBox *checkBoxLinkLP;
    QWidget *tabHighPass;
    QGridLayout *gridLayout_3;
    QLabel *labelRedHP;
    QSlider *horizontalSliderRHP;
    QSpinBox *spinBoxRedHP;
    QLabel *labelGreenHP;
    QSlider *horizontalSliderGHP;
    QSpinBox *spinBoxGreenHP;
    QLabel *labelBlueHP;
    QSlider *horizontalSliderBHP;
    QSpinBox *spinBoxBlueHP;
    QCheckBox *checkBoxLinkHP;
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
        actionGray = new QAction(MainWindow);
        actionGray->setObjectName(QStringLiteral("actionGray"));
        actionGray->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(8, 8, 8, 8);
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setHandleWidth(7);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(7);
        scrollAreaSource = new QScrollArea(splitter);
        scrollAreaSource->setObjectName(QStringLiteral("scrollAreaSource"));
        sizePolicy.setHeightForWidth(scrollAreaSource->sizePolicy().hasHeightForWidth());
        scrollAreaSource->setSizePolicy(sizePolicy);
        scrollAreaSource->setWidgetResizable(true);
        scrollAreaSource->setAlignment(Qt::AlignCenter);
        sourceImage = new QcvMatWidget();
        sourceImage->setObjectName(QStringLiteral("sourceImage"));
        sourceImage->setGeometry(QRect(0, 0, 225, 335));
        scrollAreaSource->setWidget(sourceImage);
        splitter->addWidget(scrollAreaSource);
        scrollAreaSpectrum = new QScrollArea(splitter);
        scrollAreaSpectrum->setObjectName(QStringLiteral("scrollAreaSpectrum"));
        scrollAreaSpectrum->setWidgetResizable(true);
        scrollAreaSpectrum->setAlignment(Qt::AlignCenter);
        spectrumImage = new QcvMatWidget();
        spectrumImage->setObjectName(QStringLiteral("spectrumImage"));
        spectrumImage->setGeometry(QRect(0, 0, 225, 335));
        scrollAreaSpectrum->setWidget(spectrumImage);
        splitter->addWidget(scrollAreaSpectrum);
        splitter_2->addWidget(splitter);
        scrollAreaInverse = new QScrollArea(splitter_2);
        scrollAreaInverse->setObjectName(QStringLiteral("scrollAreaInverse"));
        scrollAreaInverse->setWidgetResizable(true);
        scrollAreaInverse->setAlignment(Qt::AlignCenter);
        inverseImage = new QcvMatWidget();
        inverseImage->setObjectName(QStringLiteral("inverseImage"));
        inverseImage->setGeometry(QRect(0, 0, 228, 335));
        scrollAreaInverse->setWidget(inverseImage);
        splitter_2->addWidget(scrollAreaInverse);

        verticalLayout->addWidget(splitter_2);

        tabWidgetFilters = new QTabWidget(centralWidget);
        tabWidgetFilters->setObjectName(QStringLiteral("tabWidgetFilters"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidgetFilters->sizePolicy().hasHeightForWidth());
        tabWidgetFilters->setSizePolicy(sizePolicy1);
        tabWidgetFilters->setStyleSheet(QStringLiteral("font: 10pt \"Lucida Grande\";"));
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

        checkBoxGray = new QCheckBox(groupBoxConv);
        checkBoxGray->setObjectName(QStringLiteral("checkBoxGray"));

        verticalLayout_2->addWidget(checkBoxGray);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(groupBoxConv);

        groupBoxFFT = new QGroupBox(tabImage);
        groupBoxFFT->setObjectName(QStringLiteral("groupBoxFFT"));
        verticalLayout_4 = new QVBoxLayout(groupBoxFFT);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(8, 8, 8, 8);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelMag = new QLabel(groupBoxFFT);
        labelMag->setObjectName(QStringLiteral("labelMag"));

        horizontalLayout_5->addWidget(labelMag);

        spinBoxMag = new QSpinBox(groupBoxFFT);
        spinBoxMag->setObjectName(QStringLiteral("spinBoxMag"));
        spinBoxMag->setMinimum(5);
        spinBoxMag->setMaximum(20);
        spinBoxMag->setValue(10);

        horizontalLayout_5->addWidget(spinBoxMag);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labelFFTSizeTitle = new QLabel(groupBoxFFT);
        labelFFTSizeTitle->setObjectName(QStringLiteral("labelFFTSizeTitle"));

        horizontalLayout_6->addWidget(labelFFTSizeTitle);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        labelFFTSizeValue = new QLabel(groupBoxFFT);
        labelFFTSizeValue->setObjectName(QStringLiteral("labelFFTSizeValue"));

        horizontalLayout_6->addWidget(labelFFTSizeValue);


        verticalLayout_4->addLayout(horizontalLayout_6);


        horizontalLayout->addWidget(groupBoxFFT);

        groupBox = new QGroupBox(tabImage);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(8, 8, 8, 8);
        checkBoxFiltering = new QCheckBox(groupBox);
        checkBoxFiltering->setObjectName(QStringLiteral("checkBoxFiltering"));

        verticalLayout_3->addWidget(checkBoxFiltering);

        radioButtonFilterBox = new QRadioButton(groupBox);
        radioButtonFilterBox->setObjectName(QStringLiteral("radioButtonFilterBox"));
        radioButtonFilterBox->setChecked(true);

        verticalLayout_3->addWidget(radioButtonFilterBox);

        radioButtonFilterGauss = new QRadioButton(groupBox);
        radioButtonFilterGauss->setObjectName(QStringLiteral("radioButtonFilterGauss"));

        verticalLayout_3->addWidget(radioButtonFilterGauss);

        radioButtonFilterSinc = new QRadioButton(groupBox);
        radioButtonFilterSinc->setObjectName(QStringLiteral("radioButtonFilterSinc"));

        verticalLayout_3->addWidget(radioButtonFilterSinc);


        horizontalLayout->addWidget(groupBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tabWidgetFilters->addTab(tabImage, QString());
        tabLowPass = new QWidget();
        tabLowPass->setObjectName(QStringLiteral("tabLowPass"));
        gridLayout_2 = new QGridLayout(tabLowPass);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(8, 8, 8, 8);
        labelRedLP = new QLabel(tabLowPass);
        labelRedLP->setObjectName(QStringLiteral("labelRedLP"));

        gridLayout_2->addWidget(labelRedLP, 1, 0, 1, 1);

        horizontalSliderRLP = new QSlider(tabLowPass);
        horizontalSliderRLP->setObjectName(QStringLiteral("horizontalSliderRLP"));
        horizontalSliderRLP->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSliderRLP, 1, 1, 1, 1);

        labelGreenLP = new QLabel(tabLowPass);
        labelGreenLP->setObjectName(QStringLiteral("labelGreenLP"));

        gridLayout_2->addWidget(labelGreenLP, 2, 0, 1, 1);

        horizontalSliderGLP = new QSlider(tabLowPass);
        horizontalSliderGLP->setObjectName(QStringLiteral("horizontalSliderGLP"));
        horizontalSliderGLP->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSliderGLP, 2, 1, 1, 1);

        labelBlueLP = new QLabel(tabLowPass);
        labelBlueLP->setObjectName(QStringLiteral("labelBlueLP"));

        gridLayout_2->addWidget(labelBlueLP, 3, 0, 1, 1);

        horizontalSliderBLP = new QSlider(tabLowPass);
        horizontalSliderBLP->setObjectName(QStringLiteral("horizontalSliderBLP"));
        horizontalSliderBLP->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSliderBLP, 3, 1, 1, 1);

        spinBoxRedLP = new QSpinBox(tabLowPass);
        spinBoxRedLP->setObjectName(QStringLiteral("spinBoxRedLP"));

        gridLayout_2->addWidget(spinBoxRedLP, 1, 2, 1, 1);

        spinBoxGreenLP = new QSpinBox(tabLowPass);
        spinBoxGreenLP->setObjectName(QStringLiteral("spinBoxGreenLP"));

        gridLayout_2->addWidget(spinBoxGreenLP, 2, 2, 1, 1);

        spinBoxBlueLP = new QSpinBox(tabLowPass);
        spinBoxBlueLP->setObjectName(QStringLiteral("spinBoxBlueLP"));

        gridLayout_2->addWidget(spinBoxBlueLP, 3, 2, 1, 1);

        checkBoxLinkLP = new QCheckBox(tabLowPass);
        checkBoxLinkLP->setObjectName(QStringLiteral("checkBoxLinkLP"));

        gridLayout_2->addWidget(checkBoxLinkLP, 0, 2, 1, 1);

        tabWidgetFilters->addTab(tabLowPass, QString());
        tabHighPass = new QWidget();
        tabHighPass->setObjectName(QStringLiteral("tabHighPass"));
        gridLayout_3 = new QGridLayout(tabHighPass);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(8, 8, 8, 8);
        labelRedHP = new QLabel(tabHighPass);
        labelRedHP->setObjectName(QStringLiteral("labelRedHP"));

        gridLayout_3->addWidget(labelRedHP, 1, 0, 1, 1);

        horizontalSliderRHP = new QSlider(tabHighPass);
        horizontalSliderRHP->setObjectName(QStringLiteral("horizontalSliderRHP"));
        horizontalSliderRHP->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(horizontalSliderRHP, 1, 1, 1, 1);

        spinBoxRedHP = new QSpinBox(tabHighPass);
        spinBoxRedHP->setObjectName(QStringLiteral("spinBoxRedHP"));

        gridLayout_3->addWidget(spinBoxRedHP, 1, 2, 1, 1);

        labelGreenHP = new QLabel(tabHighPass);
        labelGreenHP->setObjectName(QStringLiteral("labelGreenHP"));

        gridLayout_3->addWidget(labelGreenHP, 2, 0, 1, 1);

        horizontalSliderGHP = new QSlider(tabHighPass);
        horizontalSliderGHP->setObjectName(QStringLiteral("horizontalSliderGHP"));
        horizontalSliderGHP->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(horizontalSliderGHP, 2, 1, 1, 1);

        spinBoxGreenHP = new QSpinBox(tabHighPass);
        spinBoxGreenHP->setObjectName(QStringLiteral("spinBoxGreenHP"));

        gridLayout_3->addWidget(spinBoxGreenHP, 2, 2, 1, 1);

        labelBlueHP = new QLabel(tabHighPass);
        labelBlueHP->setObjectName(QStringLiteral("labelBlueHP"));

        gridLayout_3->addWidget(labelBlueHP, 3, 0, 1, 1);

        horizontalSliderBHP = new QSlider(tabHighPass);
        horizontalSliderBHP->setObjectName(QStringLiteral("horizontalSliderBHP"));
        horizontalSliderBHP->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(horizontalSliderBHP, 3, 1, 1, 1);

        spinBoxBlueHP = new QSpinBox(tabHighPass);
        spinBoxBlueHP->setObjectName(QStringLiteral("spinBoxBlueHP"));

        gridLayout_3->addWidget(spinBoxBlueHP, 3, 2, 1, 1);

        checkBoxLinkHP = new QCheckBox(tabHighPass);
        checkBoxLinkHP->setObjectName(QStringLiteral("checkBoxLinkHP"));

        gridLayout_3->addWidget(checkBoxLinkHP, 0, 2, 1, 1);

        tabWidgetFilters->addTab(tabHighPass, QString());

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
        QWidget::setTabOrder(checkBoxFlip, checkBoxGray);
        QWidget::setTabOrder(checkBoxGray, spinBoxMag);
        QWidget::setTabOrder(spinBoxMag, checkBoxFiltering);
        QWidget::setTabOrder(checkBoxFiltering, radioButtonFilterBox);
        QWidget::setTabOrder(radioButtonFilterBox, radioButtonFilterGauss);
        QWidget::setTabOrder(radioButtonFilterGauss, radioButtonFilterSinc);
        QWidget::setTabOrder(radioButtonFilterSinc, spinBoxRedLP);
        QWidget::setTabOrder(spinBoxRedLP, spinBoxGreenLP);
        QWidget::setTabOrder(spinBoxGreenLP, spinBoxBlueLP);
        QWidget::setTabOrder(spinBoxBlueLP, horizontalSliderRLP);
        QWidget::setTabOrder(horizontalSliderRLP, horizontalSliderGLP);
        QWidget::setTabOrder(horizontalSliderGLP, horizontalSliderBLP);
        QWidget::setTabOrder(horizontalSliderBLP, checkBoxLinkLP);
        QWidget::setTabOrder(checkBoxLinkLP, spinBoxRedHP);
        QWidget::setTabOrder(spinBoxRedHP, spinBoxGreenHP);
        QWidget::setTabOrder(spinBoxGreenHP, spinBoxBlueHP);
        QWidget::setTabOrder(spinBoxBlueHP, horizontalSliderRHP);
        QWidget::setTabOrder(horizontalSliderRHP, horizontalSliderGHP);
        QWidget::setTabOrder(horizontalSliderGHP, horizontalSliderBHP);
        QWidget::setTabOrder(horizontalSliderBHP, checkBoxLinkHP);
        QWidget::setTabOrder(checkBoxLinkHP, tabWidgetFilters);
        QWidget::setTabOrder(tabWidgetFilters, scrollAreaSource);
        QWidget::setTabOrder(scrollAreaSource, scrollAreaSpectrum);
        QWidget::setTabOrder(scrollAreaSpectrum, scrollAreaInverse);

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
        QObject::connect(horizontalSliderRLP, SIGNAL(valueChanged(int)), spinBoxRedLP, SLOT(setValue(int)));
        QObject::connect(horizontalSliderGLP, SIGNAL(valueChanged(int)), spinBoxGreenLP, SLOT(setValue(int)));
        QObject::connect(horizontalSliderBLP, SIGNAL(valueChanged(int)), spinBoxBlueLP, SLOT(setValue(int)));
        QObject::connect(spinBoxRedLP, SIGNAL(valueChanged(int)), horizontalSliderRLP, SLOT(setValue(int)));
        QObject::connect(spinBoxGreenLP, SIGNAL(valueChanged(int)), horizontalSliderGLP, SLOT(setValue(int)));
        QObject::connect(spinBoxBlueLP, SIGNAL(valueChanged(int)), horizontalSliderBLP, SLOT(setValue(int)));
        QObject::connect(horizontalSliderRHP, SIGNAL(valueChanged(int)), spinBoxRedHP, SLOT(setValue(int)));
        QObject::connect(horizontalSliderGHP, SIGNAL(valueChanged(int)), spinBoxGreenHP, SLOT(setValue(int)));
        QObject::connect(horizontalSliderBHP, SIGNAL(valueChanged(int)), spinBoxBlueHP, SLOT(setValue(int)));
        QObject::connect(spinBoxRedHP, SIGNAL(valueChanged(int)), horizontalSliderRHP, SLOT(setValue(int)));
        QObject::connect(spinBoxGreenHP, SIGNAL(valueChanged(int)), horizontalSliderGHP, SLOT(setValue(int)));
        QObject::connect(spinBoxBlueHP, SIGNAL(valueChanged(int)), horizontalSliderBHP, SLOT(setValue(int)));
        QObject::connect(checkBoxGray, SIGNAL(clicked(bool)), actionGray, SLOT(setChecked(bool)));
        QObject::connect(actionGray, SIGNAL(triggered(bool)), checkBoxGray, SLOT(setChecked(bool)));

        tabWidgetFilters->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Frequency Filtering", 0));
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
        groupBoxSize->setTitle(QApplication::translate("MainWindow", "Size", 0));
        radioButtonOrigSize->setText(QApplication::translate("MainWindow", "Original", 0));
        radioButtonCustomSize->setText(QApplication::translate("MainWindow", "Custom", 0));
        labelWidth->setText(QApplication::translate("MainWindow", "Width", 0));
        labelHeight->setText(QApplication::translate("MainWindow", "Height", 0));
        groupBoxConv->setTitle(QApplication::translate("MainWindow", "Conversions", 0));
        checkBoxFlip->setText(QApplication::translate("MainWindow", "Flip", 0));
        checkBoxGray->setText(QApplication::translate("MainWindow", "Convert to gray", 0));
        groupBoxFFT->setTitle(QApplication::translate("MainWindow", "FFT", 0));
        labelMag->setText(QApplication::translate("MainWindow", "Mag.", 0));
        labelFFTSizeTitle->setText(QApplication::translate("MainWindow", "FFT Size", 0));
        labelFFTSizeValue->setText(QApplication::translate("MainWindow", "0", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Filter", 0));
        checkBoxFiltering->setText(QApplication::translate("MainWindow", "Filtering", 0));
        radioButtonFilterBox->setText(QApplication::translate("MainWindow", "Box", 0));
        radioButtonFilterGauss->setText(QApplication::translate("MainWindow", "Gaussian", 0));
        radioButtonFilterSinc->setText(QApplication::translate("MainWindow", "Sinc", 0));
        tabWidgetFilters->setTabText(tabWidgetFilters->indexOf(tabImage), QApplication::translate("MainWindow", "Image", 0));
        labelRedLP->setText(QApplication::translate("MainWindow", "Red", 0));
        labelGreenLP->setText(QApplication::translate("MainWindow", "Green", 0));
        labelBlueLP->setText(QApplication::translate("MainWindow", "Blue", 0));
        checkBoxLinkLP->setText(QApplication::translate("MainWindow", "Link", 0));
        tabWidgetFilters->setTabText(tabWidgetFilters->indexOf(tabLowPass), QApplication::translate("MainWindow", "Low Pass", 0));
        labelRedHP->setText(QApplication::translate("MainWindow", "Red", 0));
        labelGreenHP->setText(QApplication::translate("MainWindow", "Green", 0));
        labelBlueHP->setText(QApplication::translate("MainWindow", "Blue", 0));
        checkBoxLinkHP->setText(QApplication::translate("MainWindow", "Link", 0));
        tabWidgetFilters->setTabText(tabWidgetFilters->indexOf(tabHighPass), QApplication::translate("MainWindow", "High Pass", 0));
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
