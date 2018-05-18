#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QFileDialog>
#include <QDebug>
#include <assert.h>

#include <opencv2/calib3d/calib3d.hpp>	// CV_ITERATIVE, CV_...

#include "QcvMatWidgetImage.h"
#include "QcvMatWidgetLabel.h"
#include "QcvMatWidgetGL.h"

#include "QcvAlgoParamConstWidget.h"
#include "QcvAlgoParamBooleanWidget.h"
#include "QcvAlgoParamIntWidget.h"
#include "QcvAlgoParamEnumWidget.h"
#include "QcvAlgosParamRealWidget.h"

/*
 * MainWindow constructor
 * @param capture the capture QObject to capture frames from devices
 * or video files
 * @param parent parent widget
 */
MainWindow::MainWindow(QcvVideoCapture * capture,
					   QcvDMR * processor,
					   QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	capture(capture),
	processor(processor),
	preferredWidth(640),
	preferredHeight(480),
	renderMode(RENDER_IMAGE)
{
	ui->setupUi(this);
	ui->scrollAreaModel->setBackgroundRole(QPalette::Mid);
	ui->scrollAreaScene->setBackgroundRole(QPalette::Mid);

	// ------------------------------------------------------------------------
	// Assertions
	// ------------------------------------------------------------------------
	assert(capture != NULL);

	assert(processor != NULL);

	// ------------------------------------------------------------------------
	// Setup Detector & Descriptor combobox according to CvDetector contents
	// ------------------------------------------------------------------------
	ui->comboBoxFeatures->blockSignals(true);
	ui->comboBoxFeatures->clear();
	for (size_t i = 0; i < (size_t)CvDetector::FEATURE_NUMBER; i++)
	{
		ui->comboBoxFeatures->addItem(QString::fromStdString(CvDetector::FeatureNames[i]),
									  QVariant::fromValue<size_t>(i));
	}
	ui->comboBoxFeatures->blockSignals(false);

	ui->comboBoxDescriptors->blockSignals(true);
	ui->comboBoxDescriptors->clear();
	for (size_t i = 0; i < (size_t)CvDetector::DESCRIPTOR_NUMBER; i++)
	{
		ui->comboBoxDescriptors->addItem(QString::fromStdString(CvDetector::DescriptorNames[i]),
										 QVariant::fromValue<size_t>(i));
	}
	ui->comboBoxDescriptors->blockSignals(false);

	// ------------------------------------------------------------------------
	// UI setup according to capture and processor options
	// ------------------------------------------------------------------------
	setupUIfromCapture();

	setupUIfromProcessor();

	// ------------------------------------------------------------------------
	// Signal/Slot connections
	// ------------------------------------------------------------------------
	// Replace QcvMatWidget instance with QcvMatWidgetImage instance and
	// sets widgetImage source for the first time
	setupImageWidgets();

	// Connects Mainwindow messages to status bar
	connect(this, SIGNAL(sendMessage(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	// Connects capture status messages to statusBar
	connect(capture, SIGNAL(messageChanged(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	// Connects processor status messages to statusBar
	connect(processor, SIGNAL(sendMessage(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	// When Processor source image changes, some attributes are reinitialised
	// So we have to set them up again according to current UI values
	connect(processor, SIGNAL(imageChanged()),
			this, SLOT(setupProcessorfromUI()));

	// Connects UI requests to capture
	connect(this, SIGNAL(sizeChanged(const QSize &)),
			capture, SLOT(setSize(const QSize &)), Qt::DirectConnection);
	connect(this, SIGNAL(deviceChanged(int,uint,uint)),
			capture, SLOT(open(int,uint,uint)), Qt::DirectConnection);
	connect(this, SIGNAL(fileChanged(QString,uint,uint)),
			capture, SLOT(open(QString,uint,uint)), Qt::DirectConnection);
	connect(this, SIGNAL(flipChanged(bool)),
			capture, SLOT(setFlipVideo(bool)), Qt::DirectConnection);
	connect(this, SIGNAL(grayChanged(bool)),
			capture, SLOT(setGray(bool)), Qt::DirectConnection);
}

/*
 * MainWindow destructor
 */
MainWindow::~MainWindow()
{
	delete ui;
}

/*
 * Changes widgetImage nature according to desired rendering mode.
 * Possible values for rendering mode are:
 * 	- IMAGE: widgetImage is assigned to a QcvMatWidgetImage instance
 * 	- PIXMAP: widgetImage is assigned to a QcvMatWidgetLabel instance
 * 	- GL: widgetImage is assigned to a QcvMatWidgetGL instance
 */
void MainWindow::setupImageWidgets()
{
	// Disconnect first
	disconnect(processor, SIGNAL(updated()),
			   ui->widgetImageScene, SLOT(update()));

	disconnect(processor, SIGNAL(modelUpdated()),
			   ui->widgetImageModel, SLOT(update()));

	disconnect(processor, SIGNAL(imageChanged(Mat*)),
			   ui->widgetImageScene, SLOT(setSourceImage(Mat*)));

	disconnect(processor, SIGNAL(modelImageChanged(Mat*)),
			   ui->widgetImageModel, SLOT(setSourceImage(Mat*)));

	QWindow * currentWindow = windowHandle();
	if (renderMode == RENDER_GL)
	{
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen *)),
				   ui->widgetImageModel,
				   SLOT(screenChanged()));
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen *)),
				   ui->widgetImageScene,
				   SLOT(screenChanged()));
	}

	// remove widget in scroll areas
	QWidget * wScene = ui->scrollAreaScene->takeWidget();
	QWidget * wModel = ui->scrollAreaModel->takeWidget();

	if ((wScene == ui->widgetImageScene) &&
		(wModel == ui->widgetImageModel))
	{
		// delete removed widget
		delete ui->widgetImageScene;
		delete ui->widgetImageModel;

		// create new widget
		Mat * sceneImage = processor->getDisplaySourceImagePtr();
		Mat * modelImage = processor->getDisplayModelImagePtr();

		switch (renderMode)
		{
			case RENDER_PIXMAP:
				ui->widgetImageScene =
						new QcvMatWidgetLabel(sceneImage,
											  ui->scrollAreaScene);
				ui->widgetImageModel =
						new QcvMatWidgetLabel(modelImage,
											  ui->scrollAreaModel);
				break;
			case RENDER_GL:
				ui->widgetImageScene =
						new QcvMatWidgetGL(sceneImage,
										   ui->scrollAreaScene);
				ui->widgetImageModel =
						new QcvMatWidgetGL(modelImage,
										   ui->scrollAreaModel);
				break;
			case RENDER_IMAGE:
			default:
				ui->widgetImageScene =
						new QcvMatWidgetImage(sceneImage,
											  ui->scrollAreaScene);
				ui->widgetImageModel =
						new QcvMatWidgetImage(modelImage,
											  ui->scrollAreaModel);
				break;
		}

		if ((ui->widgetImageScene != NULL) && (ui->widgetImageModel != NULL))
		{
			ui->widgetImageScene->setObjectName(QString::fromUtf8("widgetImageScene"));
			ui->widgetImageModel->setObjectName(QString::fromUtf8("widgetImageModel"));
			// add it to the scroll area
			ui->scrollAreaScene->setWidget(ui->widgetImageScene);
			ui->scrollAreaModel->setWidget(ui->widgetImageModel);

			/*
			 * Should these connections use direct connections in order to
			 * refresh promptly ???
			 * No because QGLImageRender introduces parent problems when
			 * RE-creating a QGLImageRender with a parent in an other thread
			 */
			connect(processor, SIGNAL(updated()),
					ui->widgetImageScene, SLOT(update()));

			connect(processor, SIGNAL(modelUpdated()),
					ui->widgetImageModel, SLOT(update()));

			connect(processor, SIGNAL(imageChanged(Mat*)),
					ui->widgetImageScene, SLOT(setSourceImage(Mat*)));

			connect(processor, SIGNAL(modelImageChanged(Mat*)),
					ui->widgetImageModel, SLOT(setSourceImage(Mat*)));

			if (renderMode == RENDER_GL)
			{
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->widgetImageModel,
						SLOT(screenChanged()));
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->widgetImageScene,
						SLOT(screenChanged()));
			}

			// Sends message to status bar and sets menu checks
			message.clear();
			message.append(tr("Render mode set to "));
			switch (renderMode)
			{
				case RENDER_IMAGE:
					ui->actionRenderPixmap->setChecked(false);
					ui->actionRenderOpenGL->setChecked(false);
					message.append(tr("QImage"));
					break;
				case RENDER_PIXMAP:
					ui->actionRenderImage->setChecked(false);
					ui->actionRenderOpenGL->setChecked(false);
					message.append(tr("QPixmap in QLabel"));
					break;
				case RENDER_GL:
					ui->actionRenderImage->setChecked(false);
					ui->actionRenderPixmap->setChecked(false);
					message.append("QGLWidget");
					break;
				default:
				break;
			}
			emit sendMessage(message, 5000);
		}
		else
		{
			qDebug("MainWindow::on_actionRenderXXX new widget is null");
		}
	}
	else
	{
		qDebug("MainWindow::on_actionRenderXXX removed widget is not imageWidget");
	}
}

/*
 * Setup UI according to capture settings when app launches
 */
void MainWindow::setupUIfromCapture()
{
	// ------------------------------------------------------------------------
	// UI setup according to capture options
	// ------------------------------------------------------------------------

	// Sets size radioButton states
	if (capture->isResized())
	{
		/*
		 * Initial Size radio buttons configuration
		 */
		ui->radioButtonOrigSize->setChecked(false);
		ui->radioButtonCustomSize->setChecked(true);
		/*
		 * Initial Size menu items configuration
		 */
		ui->actionOriginalSize->setChecked(false);
		ui->actionConstrainedSize->setChecked(true);

		QSize size = capture->getSize();
		qDebug("Capture->size is %dx%d", size.width(), size.height());
		preferredWidth = size.width();
		preferredHeight = size.height();

	}
	else
	{
		/*
		 * Initial Size radio buttons configuration
		 */
		ui->radioButtonCustomSize->setChecked(false);
		ui->radioButtonOrigSize->setChecked(true);

		/*
		 * Initial Size menu items configuration
		 */
		ui->actionConstrainedSize->setChecked(false);
		ui->actionOriginalSize->setChecked(true);
	}

	// Sets spinboxes preferred size
	ui->spinBoxWidth->setValue(preferredWidth);
	ui->spinBoxHeight->setValue(preferredHeight);

	// Sets flipCheckbox and menu item states
	bool flipped = capture->isFlipVideo();
	ui->actionFlip->setChecked(flipped);
	ui->checkBoxFlip->setChecked(flipped);

	// Sets gray checkbox and menu item states
	bool grayed = capture->isGray();
	ui->actionGray->setChecked(grayed);
	ui->checkBoxGray->setChecked(grayed);

}

/*
 * Setup UI according to processor settings when app launches
 */
void MainWindow::setupUIfromProcessor()
{
	// UI Settings ------------------------------------------------------------
	// Detector parameters

	qDebug("UI Current Feature is %d : %s", ui->comboBoxFeatures->currentIndex(), CvDetector::FeatureNames[ui->comboBoxFeatures->currentIndex()].c_str());
	qDebug("Processor current Feature is %d : %s", processor->getFeatureType(), CvDetector::FeatureNames[processor->getFeatureType()].c_str());
	ui->comboBoxFeatures->setEditable(true);
	ui->comboBoxFeatures->setCurrentIndex((int)processor->getFeatureType());
	ui->comboBoxFeatures->setEditable(false);

	qDebug("UI Current descriptors is %d : %s", ui->comboBoxDescriptors->currentIndex(), CvDetector::DescriptorNames[ui->comboBoxDescriptors->currentIndex()].c_str());
	qDebug("Processor current Feature is %d : %s", processor->getDescriptorExtractorType(), CvDetector::DescriptorNames[processor->getDescriptorExtractorType()].c_str());
	ui->comboBoxDescriptors->setCurrentIndex((int)processor->getDescriptorExtractorType());

	ui->groupBoxDetector->setChecked(processor->isDetecting());

	// Keypoints to show
	ui->comboBoxShowKPts->setCurrentIndex((int)processor->getKeyPointsMode());

	// Matcher parameters
	ui->comboBoxMatcherType->setCurrentIndex(processor->getMatcherType());
	ui->comboBoxMatcherMode->setCurrentIndex(processor->getMatcherMode());
	ui->spinBoxKnn->setValue(processor->getKnn());
	ui->doubleSpinBoxRadius->setValue(processor->getRadiusThreshold());
	ui->groupBoxMatcher->setChecked(processor->isMatching());
	// Controls possible matchers
	setupUIPossibleMatchers();

	// Registrar parameters
	ui->doubleSpinBoxPrintSize->setValue(processor->getPrintSize());
	ui->doubleSpinBoxReprojThres->setValue(processor->getReprojThreshold());
	bool registering  = processor->isRegistering();
	ui->groupBoxRegistrar->setChecked(registering);
	ui->checkBoxUsePreviousPose->setEnabled(registering);

	if (processor->isCameraSet())
	{
		ui->checkBoxCameraSet->setCheckable(true);
		ui->checkBoxCameraSet->setChecked(true);
//		ui->checkBoxCameraSet->setCheckable(false);
	}

	// Connect QcvDMR signals to ui labels ------------------------------------

	// Number of model keypoints
	connect(processor, SIGNAL(updateModelKeypointsNumberString(QString)),
			ui->labelModelKPts, SLOT(setText(QString)));
	// Number of scene keypoints
	connect(processor, SIGNAL(updateSceneKeypointsNumberString(QString)),
			ui->labelSceneKPts, SLOT(setText(QString)));
	// Scene feature points detection time
	connect(processor, SIGNAL(updateDetectionTimeString(QString)),
			ui->labelDetectorTimeMs, SLOT(setText(QString)));
	// Scene descriptors extraction time
	connect(processor, SIGNAL(updateExtractionTimeString(QString)),
			ui->labelDescriptorsTimeMs, SLOT(setText(QString)));
	// Number of matched keypoints
	connect(processor, SIGNAL(updateMatchedPointsNumberString(QString)),
			ui->labelMatchedNumber, SLOT(setText(QString)));
	// Descriptors matching time
	connect(processor, SIGNAL(updateMatchingTimeString(QString)),
			ui->labelMatcherTimeMs, SLOT(setText(QString)));
	// Mean match distance
	connect(processor, SIGNAL(updateMeanMatchDistanceString(QString)),
			ui->labelDistMeanNumber, SLOT(setText(QString)));
	// Min/max match distance
	connect(processor, SIGNAL(updateMinMaxMatchDistanceString(QString)),
			ui->labelDistMinNumber, SLOT(setText(QString)));
	// Number of inliers
	connect(processor, SIGNAL(updateInliersNumberString(QString)),
			ui->labelInliersNumber, SLOT(setText(QString)));
	// Mean reprojection error
	connect(processor, SIGNAL(updateReprojectionErrorString(QString)),
			ui->labelReprojErrorNumber, SLOT(setText(QString)));
	// Registration time
	connect(processor, SIGNAL(updateRegistrationTimeString(QString)),
			ui->labelRegTimeMS, SLOT(setText(QString)));

	// Setup parameters pane --------------------------------------------------
	cleanUpWidgets(ui->detectorParamBox);
	setupParametersWidgets(ui->detectorParamBox,
						   processor->getDetectorsParamSet(),
						   processor->getDetectorsAlgorithm());

	cleanUpWidgets(ui->extractorParamBox);
	if (processor->getExtractorsAlgorithm() !=
		processor->getDetectorsAlgorithm())
	{
		setupParametersWidgets(ui->extractorParamBox,
							   processor->getExtractorsParamSet(),
							   processor->getExtractorsAlgorithm());
	}
	else
	{
		ui->extractorParamBox->setTitle(
		 QString::fromStdString(processor->getExtractorsParamSet()->getName()) +
					QString(" parameters"));
		QWidget * widget = new QLabel(QString("Same as above"),
									  ui->extractorParamBox);
		ui->extractorParamBox->layout()->addWidget(widget);
	}

}

/*
 * Setup UI possible matchers according to processor's current
 * descriptor extractor
 */
void MainWindow::setupUIPossibleMatchers()
{
	// Undocumented hack from https://forum.qt.io/topic/27419/qcombobox-item-disable/2
	// disable item
	// ui->comboBox->setItemData(index, 0, Qt::UserRole - 1);
	// enable item
	// ui->comboBox->setItemData(index, 33, Qt::UserRole - 1);
	CvDetector::DescriptorTypes descriptorType = (CvDetector::DescriptorTypes)
			processor->getDescriptorType();
	QVariant value;
	switch (descriptorType)
	{
		case CvDetector::BINARY_DESCRIPTOR:
			for (int i = 0; i < ui->comboBoxMatcherType->count(); i++)
			{
				if (CvMatcher::MatcherBinary[i])
				{
					// enable
					value = 33;
				}
				else
				{
					// disable
					value = 0;
				}
				ui->comboBoxMatcherType->setItemData(i, value, Qt::UserRole - 1);
			}
			break;
		case CvDetector::VALUED_DESCRIPTOR:
			for (int i = 0; i < ui->comboBoxMatcherType->count(); i++)
			{
				if (CvMatcher::MatcherFloat[i])
				{
					// enable
					value = 33;
				}
				else
				{
					// disable
					value = 0;
				}
				ui->comboBoxMatcherType->setItemData(i, value, Qt::UserRole - 1);
			}
			break;
		default:
			qWarning() << "setupUIPossibleMatchers : unknown matcher type";
			break;
	}
}


/*
 * Setup processor from current UI settings when processor source image
 * changes
 */
void MainWindow::setupProcessorfromUI()
{
	// Detector
	processor->setFeatureType((CvDetector::FeatureType)ui->comboBoxFeatures->currentIndex());
	processor->setDescriptorExtractorType((CvDetector::DescriptorExtractorType)
								 ui->comboBoxDescriptors->currentIndex(), false);
	processor->setDetecting(ui->groupBoxDetector->isChecked());

	// Matcher
	processor->setMatcherType((CvMatcher::MatcherType)
							  ui->comboBoxMatcherType->currentIndex(), false);
	processor->setMatcherMode((CvMatcher::MatchType)
							  ui->comboBoxMatcherMode->currentIndex());
	processor->setKnn(ui->spinBoxKnn->value());
	processor->setRadiusThreshold(ui->doubleSpinBoxRadius->value());
	processor->setMatching(ui->groupBoxMatcher->isChecked());

	// Registrar
	processor->setPrintSize(ui->doubleSpinBoxPrintSize->value());
	processor->setReprojThreshold(ui->doubleSpinBoxReprojThres->value());
	processor->setShowModelFrame(ui->checkBoxShowFrame->isChecked());
	processor->setShowModelBox(ui->checkBoxShowModelBox->isChecked());
	processor->setComputePose(ui->checkBoxShowModelBox->isChecked());
	processor->setUsePreviousPose(ui->checkBoxUsePreviousPose->isChecked());
	processor->setRegistering(ui->groupBoxRegistrar->isChecked());
}

/*
 * Clears all widgets from ui->detectorParamBox or
 * ui->extractorParamBox
 */
void MainWindow::cleanUpWidgets(QWidget * parent)
{
	QList<QWidget *> Widgets = parent->findChildren<QWidget *>();
	QLayout * layout = parent->layout();
	foreach(QWidget * child, Widgets)
	{
		// qDebug("removing widget %s", child->objectName().toStdString().c_str());
		layout->removeWidget(child);
		if (child != NULL)
		{
			// qDebug("setting null parent");
			// child->setParent(NULL);
			// qDebug("deleting");
			child->deleteLater();
		}
	}
}

/*
 * Setup control widgets
 * @param parent Parent widget (ui->detectorParamBox or
 * ui->extractorParamBox)
 * @param paramSet the parameter set to represent by widgets
 * @param the algorithm represented by this parameter set (the algorithm
 * is supposed to be already associated with the parameters in the set
 * and is only used to list the parameters in the algorithm's favorite
 * order
 */
void MainWindow::setupParametersWidgets(QGroupBox * parent,
										CvAlgoParamSet * paramSet,
										const Ptr<Feature2D> & algorithm)
{
	if (paramSet != NULL && !algorithm.empty())
	{
		qDebug() << "Setting Parameters for " << *paramSet;

		parent->setTitle(QString::fromStdString(paramSet->getName()) +
						 QString(" parameters"));
		QLayout * layout = parent->layout();

		if (paramSet->matches(algorithm))
		{
			// We use sliders for INT & REAL parameters up to 5 (no more)
			bool sliderOn = (paramSet->nbParameters() <= 5);

			for (map<string, Ptr<CvAlgoParam> >::iterator pit = paramSet->begin();
				 pit != paramSet->end();
				 ++pit)
			{
				string name = pit->first;
				CvAlgoParam * parameter = pit->second.get();

				if (parameter != NULL)
				{
					QWidget * widget = NULL;

					if (parameter->isConstant())
					{
						widget = new QcvAlgoParamConstWidget(parameter, parent);
					}
					else
					{
						switch(parameter->getType())
						{
							case CvAlgoParam::BOOLEAN:
								// direct operations for boolean switch
								widget = new QcvAlgoParamBooleanWidget(parameter,
																	   false,
																	   parent);
								if (parameter->isSettable())
								{
									connect((QcvAlgoParamBooleanWidget *)widget,
											SIGNAL(parameterUpdated()),
											processor,
											SLOT(setModelDetectorUpdate()));
								}
								break;
							case CvAlgoParam::INT:
								if (parameter->isEnum())
								{
									// direct operation for enum changed
									widget = new QcvAlgoParamEnumWidget(parameter,
																		false,
																		parent);
									if (parameter->isSettable())
									{
										connect((QcvAlgoParamEnumWidget *)widget,
												SIGNAL(parameterUpdated()),
												processor,
												SLOT(setModelDetectorUpdate()));
									}
								}
								else
								{
									// signal/slot operations for int value
									widget = new QcvAlgoParamIntWidget(parameter,
																	   sliderOn,
																	   false,
																	   parent);
									if (parameter->isSettable())
									{
										connect((QcvAlgoParamIntWidget *)widget,
												SIGNAL(parameterUpdated()),
												processor,
												SLOT(setModelDetectorUpdate()));
									}
								}
								break;
							case CvAlgoParam::REAL:
								// signal/slot operations for real value
								widget = new QcvAlgosParamRealWidget(parameter,
																	 sliderOn,
																	 false,
																	 parent);
								if (parameter->isSettable())
								{
									connect((QcvAlgosParamRealWidget *)widget,
											SIGNAL(parameterUpdated()),
											processor,
											SLOT(setModelDetectorUpdate()));
								}
								break;
							default:
								break;
						}
					}
					if (widget != NULL)
					{
						widget->setObjectName(QString::fromStdString(name));
						layout->addWidget(widget);
					}
				}
				else
				{
					qWarning("Can not add NULL parameter to widgets");
				}
			}

		}
		else
		{
			const Feature2D * algoPtr = algorithm.get();
			qWarning("parameter set %s does not match algorithm %s",
					 paramSet->getName().c_str(),
					 typeid(*algoPtr).name());
		}
	}
	else
	{
		if (paramSet == NULL)
		{
			qWarning("setup parameters widgets : NULL paramset");
		}
		if (algorithm.empty())
		{
			qWarning("setup parameters widgets : empty algorithm");
		}
	}
}

/*
 * Menu action when Sources->camera 0 is selected
 * Sets capture to open device 0. If device is not available
 * menu item is set to inactive.
 */
void MainWindow::on_actionCamera_0_triggered()
{
	int width = 0;
	int height = 0;

	if (ui->radioButtonCustomSize->isChecked())
	{
		width = preferredWidth;
		height = preferredHeight;
	}

	qDebug("Opening device 0 ...");
//	if (!capture->open(0, width, height))
//	{
//		qWarning("Unable to open device 0");
//		// disable menu item if camera 0 does not exist
//		ui->actionCamera_0->setDisabled(true);
//	}
	emit deviceChanged(0, width, height);
}

/*
 * Menu action when Sources->camera 1 is selected
 * Sets capture to open device 0. If device is not available
 * menu item is set to inactive
 */
void MainWindow::on_actionCamera_1_triggered()
{
	int width = 0;
	int height = 0;

	if (ui->radioButtonCustomSize->isChecked())
	{
		width = preferredWidth;
		height = preferredHeight;
	}

	qDebug("Opening device 1 ...");
//	if (!capture->open(1, width, height))
//	{
//		qWarning("Unable to open device 1");
//		// disable menu item if camera 1 does not exist
//		ui->actionCamera_1->setDisabled(true);
//	}
	emit deviceChanged(1, width, height);
}

/*
 * Menu action when Sources->file is selected.
 * Opens file dialog and tries to open selected file (is not empty),
 * then sets capture to open the selected file
 */
void MainWindow::on_actionFile_triggered()
{
	int width = 0;
	int height = 0;

	if (ui->radioButtonCustomSize->isChecked())
	{
		width = preferredWidth;
		height = preferredHeight;
	}

	QString fileName = QFileDialog::getOpenFileName(this,
		 tr("Open Video"), "./", tr("Video Files (*.avi *.mkv *.mp4 *.m4v)"));

	qDebug("Opening file %s ...", fileName.toStdString().c_str());

	if (fileName.length() > 0)
	{
//		if (!capture->open(fileName, width, height))
//		{
//			qWarning("Unable to open device file : %s",
//					 fileName.toStdString().c_str());
//		}

		emit fileChanged(fileName, width, height);
	}
	else
	{
		qWarning("empty file name");
	}
}

void MainWindow::on_actionModel_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		 tr("Open Model Image"), "./", tr("Image Files (*.jpg *.png *.tif)"));

	qDebug("Opening Model Image file %s ...", fileName.toStdString().c_str());

	if (fileName.length() > 0)
	{
		processor->updateModelImage(fileName.toStdString());
	}
	else
	{
		qWarning("empty file name");
	}
}

void MainWindow::on_actionCalibData_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		 tr("Open Calibration Data"), "./", tr("Calibration Files (*.yaml)"));

	qDebug("Opening Calibration file %s ...", fileName.toStdString().c_str());

	if (fileName.length() > 0)
	{
		processor->setCameraParameters(fileName.toStdString());

		if (processor->isCameraSet())
		{
			ui->checkBoxCameraSet->setCheckable(true);
			ui->checkBoxCameraSet->setChecked(true);
//			ui->checkBoxCameraSet->setCheckable(false);
		}
	}
	else
	{
		qWarning("empty file name");
	}
}

/*
 * Menu action to qui application
 */
void MainWindow::on_actionQuit_triggered()
{
	this->close();
}

/*
 * Menu action when flip image is selected.
 * Sets capture to change flip status which leads to reverse
 * image horizontally
 */
void MainWindow::on_actionFlip_triggered()
{

	emit flipChanged(!capture->isFlipVideo());
	/*
	 * There is no need to update ui->checkBoxFlip since it is connected
	 * to ui->actionFlip through signals/slots
	 */
}

/*
 * Menu action when gray image is selected.
 * Sets capture to convert source image to gray
 */
void MainWindow::on_actionGray_triggered()
{
	emit grayChanged(!capture->isGray());
}

/*
 * Menu action when original image size is selected.
 * Sets capture not to resize image
 */
void MainWindow::on_actionOriginalSize_triggered()
{

	ui->actionConstrainedSize->setChecked(false);

	emit sizeChanged(QSize(0,0));
}

/*
 * Menu action when constrained image size is selected.
 * Sets capture resize to preferred width and height
 */
void MainWindow::on_actionConstrainedSize_triggered()
{
	ui->actionOriginalSize->setChecked(false);

	emit sizeChanged(QSize(preferredWidth, preferredHeight));
}

/*
 * Menu action to replace current image rendering widget by a
 * QcvMatWidgetImage instance.
 */
void MainWindow::on_actionRenderImage_triggered()
{
	renderMode = RENDER_IMAGE;
	setupImageWidgets();
}

/*
 * Menu action to replace current image rendering widget by a
 * QcvMatWidgetLabel with pixmap instance.
 */
void MainWindow::on_actionRenderPixmap_triggered()
{
	renderMode = RENDER_PIXMAP;
	setupImageWidgets();
}

/*
 * Menu action to replace current image rendering widget by a
 * QcvMatWidgetGL instance.
 */
void MainWindow::on_actionRenderOpenGL_triggered()
{
	renderMode = RENDER_GL;
	setupImageWidgets();
}

/*
 * Original size radioButton action.
 * Sets capture resize to off
 */
void MainWindow::on_radioButtonOrigSize_clicked()
{
	ui->actionConstrainedSize->setChecked(false);
	emit sizeChanged(QSize(0, 0));
}

/*
 * Custom size radioButton action.
 * Sets capture resize to preferred width and height
 */
void MainWindow::on_radioButtonCustomSize_clicked()
{
	ui->actionOriginalSize->setChecked(false);
	emit sizeChanged(QSize(preferredWidth, preferredHeight));
}

/*
 * Width spinbox value change.
 * Changes the preferred width and if custom size is selected apply
 * this custom width
 * @param value the desired width
 */
void MainWindow::on_spinBoxWidth_valueChanged(int value)
{
	preferredWidth = value;
	if (ui->radioButtonCustomSize->isChecked())
	{
		emit sizeChanged(QSize(preferredWidth, preferredHeight));
	}
}

/*
 * Height spinbox value change.
 * Changes the preferred height and if custom size is selected apply
 * this custom height
 * @param value the desired height
 */
void MainWindow::on_spinBoxHeight_valueChanged(int value)
{
	preferredHeight = value;
	if (ui->radioButtonCustomSize->isChecked())
	{
		emit sizeChanged(QSize(preferredWidth, preferredHeight));
	}
}

/*
 * Flip capture image horizontally.
 * changes capture flip status
 */
void MainWindow::on_checkBoxFlip_clicked()
{
	/*
	 * There is no need to update ui->actionFlip since it is connected
	 * to ui->checkBoxFlip through signals/slots
	 */
	emit flipChanged(ui->checkBoxFlip->isChecked());
}

/*
 * Convert capture image to gray
 */
void MainWindow::on_checkBoxGray_clicked()
{
	emit grayChanged(ui->checkBoxGray->isChecked());
}

/*
 * Check/Uncheck the detector group box which also triggers the
 * Feature points detectors
 * @param checked status
 */
void MainWindow::on_groupBoxDetector_clicked(bool checked)
{
	processor->setDetecting(checked);

	if (!checked)
	{
		ui->groupBoxMatcher->setChecked(false);
		ui->groupBoxRegistrar->setChecked(false);
	}

}

/*
 * Check/Uncheck the matcher group box which also triggers the matcher
 * @param checked status
 */
void MainWindow::on_groupBoxMatcher_clicked(bool checked)
{
	bool result = processor->setMatching(checked);

	if (!checked)
	{
		ui->groupBoxRegistrar->setChecked(false);
	}

	// setMatching might fail so recheck it according to results
	ui->groupBoxMatcher->setChecked(result);

}

/*
 * Check/Uncheck the registrar group box which also triggers the
 * regisrtar
 * @param checked status
 */
void MainWindow::on_groupBoxRegistrar_clicked(bool checked)
{
	bool result = processor->setRegistering(checked);

	if (!checked)
	{
		ui->checkBoxShowFrame->setChecked(processor->isShowModelFrame());
		ui->checkBoxShowModelBox->setChecked(processor->isComputePose());
		ui->checkBoxUsePreviousPose->setChecked(processor->isUsePreviousPose());
	}

	// setRegistering might fail so recheck is according to result
	ui->groupBoxRegistrar->setChecked(result);
}

/*
 * Select the Feature points to detect on images
 * @param index the selected mode
 */
void MainWindow::on_comboBoxFeatures_currentIndexChanged(int index)
{
	bool pairChanged = processor->getDetectorsAlgorithm() ==
					   processor->getExtractorsAlgorithm();

	processor->setFeatureType((CvDetector::FeatureType) index);
	// Set preferred descriptor extractor (could be changed later)
	processor->setDescriptorExtractorType((CvDetector::DescriptorExtractorType)
								 CvDetector::PreferredDescriptor[index]);

	cleanUpWidgets(ui->detectorParamBox);

	setupParametersWidgets(ui->detectorParamBox,
						   processor->getDetectorsParamSet(),
						   processor->getDetectorsAlgorithm());

	if (processor->getDetectorsAlgorithm() ==
		processor->getExtractorsAlgorithm())
	{
		cleanUpWidgets(ui->extractorParamBox);
		QWidget * widget = new QLabel(QString("Same as above"),
									  ui->extractorParamBox);
		ui->extractorParamBox->layout()->addWidget(widget);
	}
	else
	{
		if (pairChanged)
		{
			cleanUpWidgets(ui->extractorParamBox);
			setupParametersWidgets(ui->extractorParamBox,
								   processor->getExtractorsParamSet(),
								   processor->getExtractorsAlgorithm());
		}
	}

	// Update descriptor type in UI
	ui->comboBoxDescriptors->setCurrentIndex((int)CvDetector::PreferredDescriptor[index]);
}

/*
 * Select the descriptors to compute on detected keypoints
 * @param index the selected mode
 */
void MainWindow::on_comboBoxDescriptors_currentIndexChanged(int index)
{
	processor->setDescriptorExtractorType((CvDetector::DescriptorExtractorType)index);

	/*
	 * Checks if setting this descriptor has changed the matcher because
	 * CvDMR::setDescriptorExtractorType(...) evt changes the matcher type
	 * according to the kind of descriptors produced by the extractor
	 */
	int currentMatcherType = (int)processor->getMatcherType();
	if (ui->comboBoxMatcherType->currentIndex() != currentMatcherType)
	{
		ui->comboBoxMatcherType->setCurrentIndex(currentMatcherType);
	}

	setupUIPossibleMatchers();

	cleanUpWidgets(ui->extractorParamBox);

	CvAlgoParamSet * paramSet = processor->getExtractorsParamSet();

	if (processor->getExtractorsAlgorithm() !=
		processor->getDetectorsAlgorithm())
	{
		setupParametersWidgets(ui->extractorParamBox,
							   paramSet,
							   processor->getExtractorsAlgorithm());
	}
	else
	{
		QWidget * widget = new QLabel(QString("Same as above"),
									  ui->extractorParamBox);
		ui->extractorParamBox->layout()->addWidget(widget);
		ui->extractorParamBox->setTitle(
					QString::fromStdString(paramSet->getName()) +
					QString(" parameters"));
	}
}

/*
 * Select the keypoints to show (none, all, matched, inliers)
 * @param index the selected mode
 */
void MainWindow::on_comboBoxShowKPts_currentIndexChanged(int index)
{
	processor->setKeyPointsMode((KeyPointShow)index);
}

/*
 * Select the matcher type
 * @param index the selected mode
 */
void MainWindow::on_comboBoxMatcherType_currentIndexChanged(int index)
{
	processor->setMatcherType((CvMatcher::MatcherType)index, true);

	/*
	 * Checks if setting this matcher type has changed the current
	 * descriptors
	 */
	int currentDescriptorType((int)processor->getDescriptorExtractorType());

	if (ui->comboBoxDescriptors->currentIndex() != currentDescriptorType)
	{
		ui->comboBoxDescriptors->setCurrentIndex(currentDescriptorType);
	}
}

/*
 * Select the matcher mode
 * @param index the selected mode
 */
void MainWindow::on_comboBoxMatcherMode_currentIndexChanged(int index)
{
	processor->setMatcherMode((CvMatcher::MatchType)index);
}

/*
 * Set the Knn number of Flann Based matcher
 * @param value the Knn number
 */
void MainWindow::on_spinBoxKnn_valueChanged(int value)
{
	processor->setKnn(value);
}

/*
 * Set the radius threshold of radius match
 * @param value the radius value
 */
void MainWindow::on_doubleSpinBoxRadius_valueChanged(double value)
{
	processor->setRadiusThreshold(value);
}

/*
 * Set the model image print size.
 * @param value the new print size
 */
void MainWindow::on_doubleSpinBoxPrintSize_valueChanged(double value)
{
	bool result = processor->setPrintSize(value);

	if (result)
	{
		ui->checkBoxCameraSet->setCheckable(true);
		ui->checkBoxCameraSet->setChecked(true);
	}
}

/*
 * Set the reprojection threshold for inliers
 * @param value the new reprojection threshold
 */
void MainWindow::on_doubleSpinBoxReprojThres_valueChanged(double value)
{
	processor->setReprojThreshold(value);
}

/*
 * Show / hide the model image frame in the scene image
 * @param checked the show frame status
 */
void MainWindow::on_checkBoxShowFrame_clicked(bool checked)
{
	bool result = processor->setShowModelFrame(checked);

	// show Model frame might fail so recheck the current state
	ui->checkBoxShowFrame->setChecked(result);
}

/*
 * Show / hide the model image box in the scene image
 * @param checked the dhow box status
 */
void MainWindow::on_checkBoxShowModelBox_clicked(bool checked)
{
	bool pose = processor->setComputePose(checked);

	bool show = processor->setShowModelBox(checked);

	// show model box might fail so recheck the current state
	ui->checkBoxShowModelBox->setChecked(show && pose);

	ui->checkBoxUsePreviousPose->setEnabled(show && pose);

}

/*
 * Set the use of the previous pose to compute the next pose
 * @param checked the status of the use previous pose
 */
void MainWindow::on_checkBoxUsePreviousPose_clicked(bool checked)
{
	processor->setUsePreviousPose(checked);
}

/*
 * Set processing time display (absolute or per feature time)
 * @param index 0 means absolute time, other means per feature time
 */
void MainWindow::on_comboBoxTimeUnit_currentIndexChanged(int index)
{
	if (index == 0)
	{
		processor->setTimePerFeature(false);
	}
	else
	{
		processor->setTimePerFeature(true);
	}
}
