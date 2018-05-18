#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QFileDialog>
#include <QWindow>
#include <QDebug>
#include <assert.h>

#include "QcvMatWidgetImage.h"
#include "QcvMatWidgetLabel.h"
#include "QcvMatWidgetGL.h"

/*
 * MainWindow constructor
 * @param capture the capture QObject to capture frames from devices
 * or video files
 * @param parent parent widget
 */
MainWindow::MainWindow(QcvVideoCapture * capture,
					   QcvHistograms * processor,
					   QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	capture(capture),
	processor(processor),
	preferredWidth(320),
	preferredHeight(240)
{
	ui->setupUi(this);
	ui->scrollArea->setBackgroundRole(QPalette::Mid);

	// ------------------------------------------------------------------------
	// Assertions
	// ------------------------------------------------------------------------
	assert(capture != NULL);

	assert(processor != NULL);

	// ------------------------------------------------------------------------
	// Special widgets initialisation
	// ------------------------------------------------------------------------
	ui->widgetImage->setSourceImage(processor->getImagePtr("out"));
	ui->widgetHistogram->setSourceImage(processor->getImagePtr("histogram"));
	ui->widgetLUT->setSourceImage(processor->getImagePtr("lut"));

	// Replace widgetImage QcvMatWidget instance with QcvMatWidgetImage
	// Sets Source image for widgetImage
	// Connects processor->updated to widgetImage->update
	// Connects processor->outImageChanged to widgetImage->setSourceImage
	setupImageWidget(RENDER_IMAGE);

	// ------------------------------------------------------------------------
	// Signal/Slot connections
	// ------------------------------------------------------------------------

	// Histogram updates to various image widget updates
	connect(processor, SIGNAL(histogramImageUpdated()),
			ui->widgetHistogram, SLOT(update()));

	connect(processor, SIGNAL(lutImageUpdated()),
			ui->widgetLUT, SLOT(update()));

	// Histogram source image changed to various image widget set sources

	connect(processor, SIGNAL(histogramImageChanged(Mat*)),
			ui->widgetHistogram, SLOT(setSourceImage(Mat*)));

	connect(processor, SIGNAL(lutImageChanged(Mat*)),
			ui->widgetLUT, SLOT(setSourceImage(Mat*)));

	// Capture, histogram and this messages to status bar
	connect(capture, SIGNAL(messageChanged(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	connect(processor, SIGNAL(sendMessage(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	connect(this, SIGNAL(sendMessage(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	// Connect UI signals to Capture slots
	connect(this, SIGNAL(sizeChanged(const QSize &)),
			capture, SLOT(setSize(const QSize &))); //, Qt::DirectConnection);
	connect(this, SIGNAL(openDevice(int,uint,uint)),
			capture, SLOT(open(int,uint,uint))); //, Qt::DirectConnection);
	connect(this, SIGNAL(openFile(QString,uint,uint)),
			capture, SLOT(open(QString,uint,uint))); //, Qt::DirectConnection);
	connect(this, SIGNAL(flipVideo(bool)),
			capture, SLOT(setFlipVideo(bool))); //, Qt::DirectConnection);

	// When Processor source image changes, some attributes are reinitialised
	// So we have to set them up again according to current UI values
	connect(processor, SIGNAL(imageChanged()),
			this, SLOT(setupProcessorFromUI()));

	// Time measurement strings connections
	connect(processor, SIGNAL(processTimeUpdated(QString)),
			ui->labelAllTime, SLOT(setText(QString)));
	connect(processor, SIGNAL(histogramTime1Updated(QString)),
			ui->labelUH1Time, SLOT(setText(QString)));
	connect(processor, SIGNAL(histogramTime2Updated(QString)),
			ui->labelUH2Time, SLOT(setText(QString)));
	connect(processor, SIGNAL(drawHistogramTimeUpdated(QString)),
			ui->labelDHTime, SLOT(setText(QString)));
	connect(processor, SIGNAL(computeLUTTimeUpdated(QString)),
			ui->labelCLTime, SLOT(setText(QString)));
	connect(processor, SIGNAL(drawLUTTimeUpdated(QString)),
			ui->labelDLTime, SLOT(setText(QString)));
	connect(processor, SIGNAL(applyLUTTimeUpdated(QString)),
			ui->labelALTime, SLOT(setText(QString)));

	// ------------------------------------------------------------------------
	// UI setup accroding to capture ahd histogram settings
	// ------------------------------------------------------------------------
	setupUIfromCapture();

	setupUIfromProcessor();
}

/*
 * MainWindow destructor
 */
MainWindow::~MainWindow()
{
	delete ui;
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

	emit openDevice(0, width, height);
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

	emit openDevice(1, width, height);
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

	QString fileName =
	QFileDialog::getOpenFileName(this,
								 tr("Open Video"),
								 "./",
								 tr("Video Files (*.avi *.mkv *.mp4 *.m4v)"),
								 NULL,
								 QFileDialog::ReadOnly);

	qDebug("Opening file %s ...", fileName.toStdString().c_str());

	if (fileName.length() > 0)
	{
//		if (!capture->open(fileName, width, height))
//		{
//			qWarning("Unable to open device file : %s",
//					 fileName.toStdString().c_str());
//		}
		emit openFile(fileName, width, height);
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
	// capture->setFlipVideo(!capture->isFlipVideo());
	emit flipVideo(!capture->isFlipVideo());
	/*
	 * There is no need to update ui->checkBoxFlip since it is connected
	 * to ui->actionFlip through signals/slots
	 */
}

/*
 * Menu action when original image size is selected.
 * Sets capture not to resize image
 */
void MainWindow::on_actionOriginalSize_triggered()
{
	ui->actionConstrainedSize->setChecked(false);

	emit sizeChanged(QSize(0, 0));
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
 * Changes widgetImage nature according to desired rendering mode.
 * Possible values for mode are:
 * 	- IMAGE: widgetImage is assigned to a QcvMatWidgetImage instance
 * 	- PIXMAP: widgetImage is assigned to a QcvMatWidgetLabel instance
 * 	- GL: widgetImage is assigned to a QcvMatWidgetGL instance
 * @param mode
 */
void MainWindow::setupImageWidget(const RenderMode mode)
{
	// Disconnect first
	disconnect(processor, SIGNAL(outImageUpdated()),
			   ui->widgetImage, SLOT(update()));

	disconnect(processor, SIGNAL(outImageChanged(Mat*)),
			   ui->widgetImage, SLOT(setSourceImage(Mat*)));

	QWindow * currentWindow = windowHandle();
	if (mode == RENDER_GL)
	{
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen *)),
				   ui->widgetImage,
				   SLOT(screenChanged()));
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen*)),
				   ui->widgetHistogram,
				   SLOT(screenChanged()));
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen*)),
				   ui->widgetLUT,
				   SLOT(screenChanged()));
	}

	// remove widget in scroll area
	QWidget * w = ui->scrollArea->takeWidget();

	if (w == ui->widgetImage)
	{
		// delete removed widget
		delete ui->widgetImage;

		// create new widget
		Mat * image = processor->getImagePtr("out");
		if (image == NULL)
		{
			qFatal("Null image out");
		}
		if (image->data == NULL)
		{
			qFatal("image out NULL data");
		}
		switch (mode)
		{
			case RENDER_PIXMAP:
				ui->widgetImage = new QcvMatWidgetLabel(image);
				break;
			case RENDER_GL:
				ui->widgetImage = new QcvMatWidgetGL(image);
				break;
			case RENDER_IMAGE:
			default:
				ui->widgetImage = new QcvMatWidgetImage(image);
				break;
		}

		if (ui->widgetImage != NULL)
		{
			ui->widgetImage->setObjectName(QString::fromUtf8("widgetImage"));

			// add it to the scroll area
			ui->scrollArea->setWidget(ui->widgetImage);

			connect(processor, SIGNAL(outImageUpdated()),
					ui->widgetImage, SLOT(update()));

			connect(processor, SIGNAL(outImageChanged(Mat*)),
					ui->widgetImage, SLOT(setSourceImage(Mat*)));

			if (mode == RENDER_GL)
			{
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->widgetImage,
						SLOT(screenChanged()));
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->widgetHistogram,
						SLOT(screenChanged()));
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->widgetLUT,
						SLOT(screenChanged()));
			}

			// Sends message to status bar and sets menu checks
			message.clear();
			message.append(tr("Render more set to "));
			switch (mode)
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

/**
 * Setup UI from capture settings when launching application
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
}


/**
 * Setup UI from processor settings when launching application
 */
void MainWindow::setupUIfromProcessor()
{
	qDebug("Setting up UI from processor");


	// ------------------------------------------------------------------------
	// UI setup according to Histograms options
	// ------------------------------------------------------------------------
	// Histogram channel visibility
	QCheckBox * checkBoxesChannels[4] =
	{
		ui->checkBoxHistRed,
		ui->checkBoxHistGreen,
		ui->checkBoxHistBlue,
		ui->checkBoxHistGray
	};

	size_t nbHistograms = processor->getNbHistograms();

	for (size_t i = 0; i < nbHistograms; i++)
	{
		checkBoxesChannels[i]->setChecked(processor->isShowComponent(i));
	}

	if (nbHistograms < 4)
	{
		for (size_t i = nbHistograms; i < 4; i++)
		{
			checkBoxesChannels[i]->setEnabled(false);
		}
	}

	// Histogram mode
	if (processor->isCumulative())
	{
		ui->radioButtonHMCumulative->setChecked(true);
	}
	else
	{
		ui->radioButtonHMNormal->setChecked(true);
	}

	if (processor->isTimeCumulative())
	{
		ui->radioButtonHMTime->setChecked(true);
	}
	else
	{
		ui->radioButtonHMNormal->setChecked(true);
	}

	// Current LUT
	CvHistograms8UC3::TransfertType lutMode = processor->getLutType();

	switch (lutMode)
	{
		case CvHistograms8UC3::THRESHOLD_GRAY:
		case CvHistograms8UC3::THRESHOLD_COLOR:
			ui->radioButtonThreshold->setChecked(true);
			break;
		case CvHistograms8UC3::DYNAMIC_GRAY:
		case CvHistograms8UC3::DYNAMIC_COLOR:
			ui->radioButtonDynamic->setChecked(true);
			break;
		case CvHistograms8UC3::EQUALIZE_GRAY:
		case CvHistograms8UC3::EQUALIZE_COLOR:
			ui->radioButtonEqualize->setChecked(true);
			break;
		case CvHistograms8UC3::GAMMA:
			ui->radioButtonGamma->setChecked(true);
			break;
		case CvHistograms8UC3::NEGATIVE:
			ui->radioButtonInverse->setChecked(true);
			break;
		case CvHistograms8UC3::NONE:
		default:
			ui->radioButtonIdentity->setChecked(true);
			break;
	}

	// LUT mode : color/gray
	switch (lutMode)
	{
		case CvHistograms8UC3::THRESHOLD_COLOR:
		case CvHistograms8UC3::DYNAMIC_COLOR:
		case CvHistograms8UC3::EQUALIZE_COLOR:
			ui->radioButtonChColor->setChecked(true);
			break;
		case CvHistograms8UC3::THRESHOLD_GRAY:
		case CvHistograms8UC3::DYNAMIC_GRAY:
		case CvHistograms8UC3::EQUALIZE_GRAY:
		case CvHistograms8UC3::GAMMA:
		case CvHistograms8UC3::NEGATIVE:
		case CvHistograms8UC3::NONE:
		default:
			ui->radioButtonChGray->setChecked(true);
			break;
	}

	// If there is no additionnal gray level histogram we might change
	// the channels radio buttons accordingly
	if (!processor->isComputeGray())
	{
//		ui->radioButtonChGray->setChecked(false);
		ui->radioButtonChColor->setChecked(true);
		ui->radioButtonChGray->setEnabled(false);
	}

	// LUT param
	ui->spinBoxlutParam->setValue((int)processor->getLUTParam());
}


/**
 * Re setup processor from UI settings when source image changes
 */
void MainWindow::setupProcessorFromUI()
{
//	qDebug("Setting up processor from UI");

	// Sets histogram channel visibility
	processor->setShowComponent(CvHistograms8UC3::HIST_RED,
								ui->checkBoxHistRed->isChecked());
	processor->setShowComponent(CvHistograms8UC3::HIST_GREEN,
								ui->checkBoxHistGreen->isChecked());
	processor->setShowComponent(CvHistograms8UC3::HIST_BLUE,
								ui->checkBoxHistBlue->isChecked());
	if (processor->getNbHistograms() >= CvHistograms8UC3::HIST_GRAY)
	{
		processor->setShowComponent(CvHistograms8UC3::HIST_GRAY,
									ui->checkBoxHistGray->isChecked());
	}

	// Sets Histogram mode
	if (ui->radioButtonHMNormal->isChecked())
	{
		processor->setCumulative(false);
		processor->setTimeCumulative(false);
	}
	else if (ui->radioButtonHMCumulative->isChecked())
	{
		processor->setCumulative(true);
		processor->setTimeCumulative(false);
	}
	else
	{
		processor->setCumulative(false);
		processor->setTimeCumulative(true);
	}

	processor->setLUTParam((float)ui->spinBoxlutParam->value());

	if (ui->radioButtonIdentity->isChecked())
	{
		processor->setLutType(CvHistograms8UC3::NONE);
	}
	if (ui->radioButtonInverse->isChecked())
	{
		processor->setLutType(CvHistograms8UC3::NEGATIVE);
	}
	if (ui->radioButtonGamma->isChecked())
	{
		processor->setLutType(CvHistograms8UC3::GAMMA);
	}
	if (ui->radioButtonThreshold->isChecked())
	{
		if (ui->radioButtonChGray->isChecked())
		{
			processor->setLutType(CvHistograms8UC3::THRESHOLD_GRAY);
		}
		else
		{
			processor->setLutType(CvHistograms8UC3::THRESHOLD_COLOR);
		}
	}
	if (ui->radioButtonDynamic->isChecked())
	{
		if (ui->radioButtonChGray->isChecked())
		{
			processor->setLutType(CvHistograms8UC3::DYNAMIC_GRAY);
		}
		else
		{
			processor->setLutType(CvHistograms8UC3::DYNAMIC_COLOR);
		}
	}
	if (ui->radioButtonEqualize->isChecked())
	{
		if (ui->radioButtonChGray->isChecked())
		{
			processor->setLutType(CvHistograms8UC3::EQUALIZE_GRAY);
		}
		else
		{
			processor->setLutType(CvHistograms8UC3::EQUALIZE_COLOR);
		}
	}
}


/*
 * Menu action to replace current image rendering widget by a
 * QcvMatWidgetImage instance.
 */
void MainWindow::on_actionRenderImage_triggered()
{
	setupImageWidget(RENDER_IMAGE);
}

/*
 * Menu action to replace current image rendering widget by a
 * QcvMatWidgetLabel with pixmap instance.
 */
void MainWindow::on_actionRenderPixmap_triggered()
{
	setupImageWidget(RENDER_PIXMAP);
}

/*
 * Menu action to replace current image rendering widget by a
 * QcvMatWidgetGL instance.
 */
void MainWindow::on_actionRenderOpenGL_triggered()
{
	setupImageWidget(RENDER_GL);
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
	// capture->setFlipVideo(ui->checkBoxFlip->isChecked());
	emit flipVideo(ui->checkBoxFlip->isChecked());
}

/*
 * Set transfert function to identity
 */
void MainWindow::on_radioButtonIdentity_clicked()
{
	processor->setLutType(CvHistograms8UC3::NONE);
}

/*
 * Set transfert function to inverse
 */
void MainWindow::on_radioButtonInverse_clicked()
{
	processor->setLutType(CvHistograms8UC3::NEGATIVE);
}

/*
 * Set transfert function to gamma
 */
void MainWindow::on_radioButtonGamma_clicked()
{
	processor->setLutType(CvHistograms8UC3::GAMMA);
}

/*
 * Set transfert function to threshold
 */
void MainWindow::on_radioButtonThreshold_clicked()
{
	if (ui->radioButtonChGray->isChecked())
	{
		processor->setLutType(CvHistograms8UC3::THRESHOLD_GRAY);
	}
	else
	{
		processor->setLutType(CvHistograms8UC3::THRESHOLD_COLOR);
	}
}

/*
 * Set transfert function to optimal dynamic
 */
void MainWindow::on_radioButtonDynamic_clicked()
{
	if (ui->radioButtonChGray->isChecked())
	{
		processor->setLutType(CvHistograms8UC3::DYNAMIC_GRAY);
	}
	else
	{
		processor->setLutType(CvHistograms8UC3::DYNAMIC_COLOR);
	}
}

/*
 * Set transfert function to equalization
 */
void MainWindow::on_radioButtonEqualize_clicked()
{
	if (ui->radioButtonChGray->isChecked())
	{
		processor->setLutType(CvHistograms8UC3::EQUALIZE_GRAY);
	}
	else
	{
		processor->setLutType(CvHistograms8UC3::EQUALIZE_COLOR);
	}
}

/*
 * Set transfert function depending on processor to use colors
 * components of the histogram generating 1 transfert function per image
 * channels
 */
void MainWindow::on_radioButtonChColor_clicked()
{
	CvHistograms8UC3::TransfertType type = processor->getLutType();
	switch (type)
	{
		case CvHistograms8UC3::THRESHOLD_GRAY:
			processor->setLutType(CvHistograms8UC3::THRESHOLD_COLOR);
			break;
		case CvHistograms8UC3::DYNAMIC_GRAY:
			processor->setLutType(CvHistograms8UC3::DYNAMIC_COLOR);
			break;
		case CvHistograms8UC3::EQUALIZE_GRAY:
			processor->setLutType(CvHistograms8UC3::EQUALIZE_COLOR);
			break;
		// in all other cases do nothing
		case CvHistograms8UC3::NONE:
		case CvHistograms8UC3::GAMMA:
		case CvHistograms8UC3::NEGATIVE:
		default:
			// Nothing
			break;
	}
}

/*
 * Set transfert function depending on processor to use gray level
 * histogram component generating 1 transfert function per image
 * channels
 */
void MainWindow::on_radioButtonChGray_clicked()
{
	CvHistograms8UC3::TransfertType type = processor->getLutType();
	switch (type)
	{
		case CvHistograms8UC3::THRESHOLD_COLOR:
			processor->setLutType(CvHistograms8UC3::THRESHOLD_GRAY);
			break;
		case CvHistograms8UC3::DYNAMIC_COLOR:
			processor->setLutType(CvHistograms8UC3::DYNAMIC_GRAY);
			break;
		case CvHistograms8UC3::EQUALIZE_COLOR:
			processor->setLutType(CvHistograms8UC3::EQUALIZE_GRAY);
			break;
		// in all other cases do nothing
		case CvHistograms8UC3::NONE:
		case CvHistograms8UC3::GAMMA:
		case CvHistograms8UC3::NEGATIVE:
		default:
			// Nothing
			break;
	}
}

/*
 * Modify lut parameter applied to transfert function depending on
 * histogram
 * @param value the new value of lutParam
 */
void MainWindow::on_spinBoxlutParam_valueChanged(int value)
{
	processor->setLUTParam((float)value);
}

/*
 * Set histogram mode to normal
 */
void MainWindow::on_radioButtonHMNormal_clicked()
{
	processor->setTimeCumulative(false);
	processor->setCumulative(false);
}

/*
 * Set Histogram mode to cumulative
 */
void MainWindow::on_radioButtonHMCumulative_clicked()
{
	processor->setTimeCumulative(false);
	processor->setCumulative(true);
}

/*
 * set Histogram mode to time cumulative
 */
void MainWindow::on_radioButtonHMTime_clicked()
{
	processor->setCumulative(false);
	processor->setTimeCumulative(true);
}

/*
 * Show/Hides histogram red component
 */
void MainWindow::on_checkBoxHistRed_clicked()
{
	processor->setShowComponent((size_t)CvHistograms8UC3::HIST_RED,
								 ui->checkBoxHistRed->isChecked());
}

/*
 * Show/Hides histogram green component
 */
void MainWindow::on_checkBoxHistGreen_clicked()
{
	processor->setShowComponent((size_t)CvHistograms8UC3::HIST_GREEN,
								 ui->checkBoxHistGreen->isChecked());
}

/*
 * Show/Hides histogram blue component
 */
void MainWindow::on_checkBoxHistBlue_clicked()
{
	processor->setShowComponent((size_t)CvHistograms8UC3::HIST_BLUE,
								 ui->checkBoxHistBlue->isChecked());
}

/*
 * Show/Hides histogram gray component
 */
void MainWindow::on_checkBoxHistGray_clicked()
{
	processor->setShowComponent((size_t)CvHistograms8UC3::HIST_GRAY,
								 ui->checkBoxHistGray->isChecked());
}
