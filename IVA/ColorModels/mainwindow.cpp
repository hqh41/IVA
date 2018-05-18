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
					   QcvColorSpaces * processor,
					   QWidget * parent)
	: QMainWindow(parent),
	  ui(new Ui::MainWindow),
	  capture(capture),
	  processor(processor),
	  preferredWidth(640),
	  preferredHeight(480)
{
	ui->setupUi(this);
	ui->scrollArea->setBackgroundRole(QPalette::Mid);

	// ------------------------------------------------------------------------
	// Assertions
	// ------------------------------------------------------------------------
	assert(capture != NULL);

	assert(processor != NULL);

	// ------------------------------------------------------------------------
	// Signal/Slot connections
	// ------------------------------------------------------------------------
	// Replace QcvMatWidget instance with QcvMatWidgetImage instance and
	// sets widgetImage source for the first time
	setupImageWidget(RENDER_IMAGE);

	// Connects Mainwindow messages to status bar
	connect(this,
			SIGNAL(sendMessage(QString, int) ),
			ui->statusBar,
			SLOT(showMessage(QString, int) ));

	// Connects capture status messages to statusBar
	connect(capture,
			SIGNAL(messageChanged(QString, int) ),
			ui->statusBar,
			SLOT(showMessage(QString, int) ));

	// Connects processor status messages to statusBar
	connect(processor,
			SIGNAL(sendMessage(QString, int) ),
			ui->statusBar,
			SLOT(showMessage(QString, int) ));

	// When Processor source image changes, some attributes are reinitialised
	// So we have to set them up again according to current UI values
	connect(processor,
			SIGNAL(imageChanged()),
			this,
			SLOT(setupProcessorfromUI()));

	// Connects processor time to UI time label
	//	connect(processor, SIGNAL(processTimeUpdated(QString)),
	//			ui->labelProcessTimeValue, SLOT(setText(QString)));
	connect(processor,
			SIGNAL(processTimeUpdated(const CvProcessor::ProcessTime*)),
			this,
			SLOT(on_processTimeupdated(const CvProcessor::ProcessTime*)));

	// Connects UI requests to capture
	connect(this,
			SIGNAL(sizeChanged(const QSize &) ),
			capture,
			SLOT(setSize(const QSize &) ),
			Qt::DirectConnection);
	connect(this,
			SIGNAL(deviceChanged(int, uint, uint)),
			capture,
			SLOT(open(int, uint, uint)),
			Qt::DirectConnection);
	connect(this,
			SIGNAL(fileChanged(QString, uint, uint)),
			capture,
			SLOT(open(QString, uint, uint)),
			Qt::DirectConnection);
	connect(this,
			SIGNAL(flipChanged(bool) ),
			capture,
			SLOT(setFlipVideo(bool) ),
			Qt::DirectConnection);
	// ------------------------------------------------------------------------
	// UI setup according to capture and processor options
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
	disconnect(processor, SIGNAL(updated()), ui->widgetImage, SLOT(update()));

	disconnect(processor,
			   SIGNAL(imageChanged(Mat *) ),
			   ui->widgetImage,
			   SLOT(setSourceImage(Mat *) ));

	QWindow * currentWindow = windowHandle();
	if (mode == RENDER_GL)
	{
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen *)),
				   ui->widgetImage,
				   SLOT(screenChanged()));
	}

	// remove widget in scroll area
	QWidget * w = ui->scrollArea->takeWidget();

	if (w == ui->widgetImage)
	{
		// delete removed widget
		delete ui->widgetImage;

		// create new widget
		Mat * image = processor->getImagePtr("display");
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

			connect(
				processor, SIGNAL(updated()), ui->widgetImage, SLOT(update()));

			connect(processor,
					SIGNAL(imageChanged(Mat *) ),
					ui->widgetImage,
					SLOT(setSourceImage(Mat *) ));

			if (mode == RENDER_GL)
			{
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->widgetImage,
						SLOT(screenChanged()));
			}

			// Sends message to status bar and sets menu checks
			message.clear();
			message.append(tr("Render mode set to "));
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
		qDebug(
			"MainWindow::on_actionRenderXXX removed widget is not imageWidget");
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
}

/*
 * Setup UI according to processor settings when app launches
 */
void MainWindow::setupUIfromProcessor()
{
	// Sets selected image for display
	switch (processor->getDisplayImageIndex())
	{
		case CvColorSpaces::INPUT:
			ui->radioButtonInput->setChecked(true);
			break;
		case CvColorSpaces::GRAY:
			ui->radioButtonGray->setChecked(true);
			break;
		case CvColorSpaces::RED:
			ui->radioButtonRed->setChecked(true);
			break;
		case CvColorSpaces::GREEN:
			ui->radioButtonGreen->setChecked(true);
			break;
		case CvColorSpaces::BLUE:
			ui->radioButtonBlue->setChecked(true);
			break;
		case CvColorSpaces::HUE:
			ui->radioButtonHue->setChecked(true);
			break;
		case CvColorSpaces::SATURATION:
			ui->radioButtonSaturation->setChecked(true);
			break;
		case CvColorSpaces::VALUE:
			ui->radioButtonValue->setChecked(true);
			break;
		case CvColorSpaces::Y:
			ui->radioButtonY->setChecked(true);
			break;
		case CvColorSpaces::Cr:
			ui->radioButtonCr->setChecked(true);
			break;
		case CvColorSpaces::Cb:
			ui->radioButtonCb->setChecked(true);
			break;
		case CvColorSpaces::NbSelected:
		default:
			// Do nothing
			break;
	}

	// By default set radio button gray channel to checked
	ui->radioButtonChGray->setChecked(true);

	// if at least one showColor index is true then set radiobutton color
	// channel to true
	for (size_t i = 0; i < CvColorSpaces::NbShows; i++)
	{
		if (processor->getColorChannel((CvColorSpaces::ShowColor) i))
		{
			ui->radioButtonChColor->setChecked(true);
			break;
		}
	}

	// Sets Hue mix mode
	switch (processor->getHueDisplaymode())
	{
		case CvColorSpaces::HUECOLOR:
			ui->radioButtonMixHue->setChecked(true);
			break;
		case CvColorSpaces::HUESATURATE:
			ui->radioButtonMixHueSat->setChecked(true);
			break;
		case CvColorSpaces::HUEVALUE:
			ui->radioButtonMixHueVal->setChecked(true);
			break;
		case CvColorSpaces::HUEGRAY:
			ui->radioButtonChGray->setChecked(true);
			break;
		default:
			break;
	}
}

/*
 * Setup processor from current UI settings when processor source image
 * changes
 */
void MainWindow::setupProcessorfromUI()
{
	if (ui->radioButtonInput->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::INPUT);
	}

	if (ui->radioButtonGray->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::GRAY);
	}

	if (ui->radioButtonRed->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::RED);
	}

	if (ui->radioButtonGreen->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::GREEN);
	}

	if (ui->radioButtonBlue->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::BLUE);
	}

	if (ui->radioButtonHue->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::HUE);
	}

	if (ui->radioButtonSaturation->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::SATURATION);
	}

	if (ui->radioButtonValue->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::VALUE);
	}

	if (ui->radioButtonY->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::Y);
	}

	if (ui->radioButtonCr->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::Cr);
	}

	if (ui->radioButtonCb->isChecked())
	{
		processor->setDisplayImageIndex(CvColorSpaces::Cb);
	}

	if (ui->radioButtonChColor->isChecked())
	{
		for (size_t i = 0; i < CvColorSpaces::NbShows; i++)
		{
			processor->setColorChannel((CvColorSpaces::ShowColor) i, true);
		}
		if (ui->radioButtonMixHue->isChecked())
		{
			processor->setHueDisplayMode(CvColorSpaces::HUECOLOR);
		}
		else if (ui->radioButtonMixHueSat->isChecked())
		{
			processor->setHueDisplayMode(CvColorSpaces::HUESATURATE);
		}
		else
		{
			processor->setHueDisplayMode(CvColorSpaces::HUEVALUE);
		}
	}

	if (ui->radioButtonChGray->isChecked())
	{
		for (size_t i = 0; i < CvColorSpaces::NbShows; i++)
		{
			processor->setColorChannel((CvColorSpaces::ShowColor) i, false);
		}
		processor->setHueDisplayMode(CvColorSpaces::HUEGRAY);
	}
}

/*
 * Updates mean and std of process time
 * @param The updated process time (MeanValue<clock_t, double>)
 */
void MainWindow::on_processTimeupdated(const CvProcessor::ProcessTime * pt)
{
	meanTimeString.sprintf("%6.0f", pt->mean() / 1000.0);
	stdTimeString.sprintf("%5.0f", pt->std() / 1000.0);
	ui->labelProcessTimeValue->setText(meanTimeString);
	ui->labelProcessTimeStd->setText(stdTimeString);
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
	emit(deviceChanged(0, width, height));
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

	QString fileName = QFileDialog::getOpenFileName(
		this,
		tr("Open Video"),
		"./",
		tr("Video Files (*.avi *.m4v *.mkv *.mp4)"),
		NULL,
		QFileDialog::ReadOnly);

	// qDebug("Opening file %s ...", fileName.toStdString().c_str());

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
	emit flipChanged(ui->checkBoxFlip->isChecked());
}

/*
 * Select input image for display
 */
void MainWindow::on_radioButtonInput_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::INPUT);
}

/*
 * Select Gray image for display
 */
void MainWindow::on_radioButtonGray_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::GRAY);
}

/*
 * Select red component of RGB space for display
 */
void MainWindow::on_radioButtonRed_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::RED);
}

/*
 * Select green component of RGB space for display
 */
void MainWindow::on_radioButtonGreen_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::GREEN);
}

/*
 * Select blue component of RGB space for display
 */
void MainWindow::on_radioButtonBlue_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::BLUE);
}

/*
 * Select hue component of HSV space for display
 */
void MainWindow::on_radioButtonHue_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::HUE);
}

/*
 * Select saturation component of HSV space for display
 */
void MainWindow::on_radioButtonSaturation_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::SATURATION);
}

/*
 * Select value component of HSV space for display
 */
void MainWindow::on_radioButtonValue_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::VALUE);
}

/*
 * Select Y component of YCbCr space for display
 */
void MainWindow::on_radioButtonY_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::Y);
}

/*
 * Select Cr component of YCbCr space for display
 */
void MainWindow::on_radioButtonCr_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::Cr);
}

/*
 * Select Cb component of YCbCr space for display
 */
void MainWindow::on_radioButtonCb_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::Cb);
}

/*
 * Select component display as colored image
 */
void MainWindow::on_radioButtonChColor_clicked()
{
	for (size_t i = 0; i < CvColorSpaces::NbShows; i++)
	{
		processor->setColorChannel((CvColorSpaces::ShowColor) i, true);
	}
	if (ui->radioButtonMixHue->isChecked())
	{
		processor->setHueDisplayMode(CvColorSpaces::HUECOLOR);
	}
	else if (ui->radioButtonMixHueSat->isChecked())
	{
		processor->setHueDisplayMode(CvColorSpaces::HUESATURATE);
	}
	else
	{
		processor->setHueDisplayMode(CvColorSpaces::HUEVALUE);
	}
}

/*
 * Select componet display as gray image
 */
void MainWindow::on_radioButtonChGray_clicked()
{
	for (size_t i = 0; i < CvColorSpaces::NbShows; i++)
	{
		processor->setColorChannel((CvColorSpaces::ShowColor) i, false);
	}
	processor->setHueDisplayMode(CvColorSpaces::HUEGRAY);
}

/*
 * Select hue component display as hue alone
 */
void MainWindow::on_radioButtonMixHue_clicked()
{
	processor->setHueDisplayMode(CvColorSpaces::HUECOLOR);
}

/*
 * Select hue component display as hue x saturation value
 */
void MainWindow::on_radioButtonMixHueSat_clicked()
{
	processor->setHueDisplayMode(CvColorSpaces::HUESATURATE);
}

/*
 * Select hue component display as hue x value value
 */
void MainWindow::on_radioButtonMixHueVal_clicked()
{
	processor->setHueDisplayMode(CvColorSpaces::HUEVALUE);
}

void MainWindow::on_radioButtonXYZ_X_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::XYZ_X);
}

void MainWindow::on_radioButtonXYZ_Y_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::XYZ_Y);
}

void MainWindow::on_radioButtonXYZ_Z_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::XYZ_Z);
}

void MainWindow::on_radioButtonMaxBGR_clicked()
{
	processor->setDisplayImageIndex(CvColorSpaces::MAX_BGR);
}
