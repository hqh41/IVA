#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QFileDialog>
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
					   QcvFloodFill * processor,
					   QWidget *parent) :
	QMainWindow(parent),
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

	connect(processor, SIGNAL(processTimeUpdated(QString)),
			ui->labelTime, SLOT(setText(QString)));

	// Connects UI requests to capture
	connect(this, SIGNAL(sizeChanged(const QSize &)),
			capture, SLOT(setSize(const QSize &)), Qt::DirectConnection);
	connect(this, SIGNAL(deviceChanged(int,uint,uint)),
			capture, SLOT(open(int,uint,uint)), Qt::DirectConnection);
	connect(this, SIGNAL(fileChanged(QString,uint,uint)),
			capture, SLOT(open(QString,uint,uint)), Qt::DirectConnection);
	connect(this, SIGNAL(flipChanged(bool)),
			capture, SLOT(setFlipVideo(bool)), Qt::DirectConnection);

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
	disconnect(processor, SIGNAL(updated()),
			   ui->widgetImage, SLOT(update()));

	disconnect(processor, SIGNAL(imageChanged(Mat*)),
			   ui->widgetImage, SLOT(setSourceImage(Mat*)));

	// Pressed mouse button in image widget clears current flood in processor
	disconnect(ui->widgetImage, SIGNAL(pressPoint(QPoint,Qt::MouseButton)),
			   processor, SLOT(clearFloodPoint(QPoint,Qt::MouseButton)));

	// Released left mouse button in image widget creates a new flood seed
	disconnect(ui->widgetImage, SIGNAL(releasePoint(QPoint,Qt::MouseButton)),
			   processor, SLOT(setSeedPoint(QPoint,Qt::MouseButton)));

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
				ui->widgetImage = new QcvMatWidgetLabel(image,
														ui->scrollArea,
														QcvMatWidget::MOUSE_CLICK);
				break;
			case RENDER_GL:
				ui->widgetImage = new QcvMatWidgetGL(image,
													 ui->scrollArea,
													 QcvMatWidget::MOUSE_CLICK);
				break;
			case RENDER_IMAGE:
			default:
				ui->widgetImage = new QcvMatWidgetImage(image,
														ui->scrollArea,
														QcvMatWidget::MOUSE_CLICK);
				break;
		}

		if (ui->widgetImage != NULL)
		{
			ui->widgetImage->setObjectName(QString::fromUtf8("widgetImage"));

			// add it to the scroll area
			ui->scrollArea->setWidget(ui->widgetImage);

			connect(processor, SIGNAL(updated()),
					ui->widgetImage, SLOT(update()));

			connect(processor, SIGNAL(imageChanged(Mat*)),
					ui->widgetImage, SLOT(setSourceImage(Mat*)));

			// Pressed mouse button in image widget clears current flood in processor
			connect(ui->widgetImage, SIGNAL(pressPoint(QPoint,Qt::MouseButton)),
					processor, SLOT(clearFloodPoint(QPoint,Qt::MouseButton)),
					Qt::DirectConnection);

			// Released left mouse button in image widget creates a new flood seed
			connect(ui->widgetImage, SIGNAL(releasePoint(QPoint,Qt::MouseButton)),
					processor, SLOT(setSeedPoint(QPoint,Qt::MouseButton)),
					Qt::DirectConnection);


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
	// Sets selected image for display
	switch (processor->getDisplayMode())
	{
		case CvFloodFill::INPUT_IM:
			ui->radioButtonInput->setChecked(true);
			break;
		case CvFloodFill::MASK_IM:
			ui->radioButtonMask->setChecked(true);
			break;
		case CvFloodFill::MERGED_IM:
			ui->radioButtonMerged->setChecked(true);
			break;
		case CvFloodFill::NBDISPLAY_IM:
		default:
			// Do nothing
			break;
	}

	// Sets flooding mode radio buttons
	switch (processor->getFfillMode())
	{
		case CvFloodFill::FIXED_RANGE:
			ui->radioButtonAbsThreshold->setChecked(true);
			break;
		case CvFloodFill::FLOATING_RANGE:
			ui->radioButtonRelThreshold->setChecked(true);
			break;
		default:
		break;
	}

	// Sets show Bounding box
	ui->checkBoxBBox->setChecked(processor->isShowBoundingBox());

	// Sets Show center
	ui->checkBoxCenter->setChecked(processor->isShowSeed());

	// Set pixel connectivity radio buttons
	if (processor->getConnectivity() == 4)
	{
		ui->radioButton4Connect->setChecked(true);
	}
	else
	{
		ui->radioButton8Connect->setChecked(true);
	}

	// Sets LoDiff slider and spinBox
	ui->spinBoxLoDiff->setValue(processor->getLoDiff());

	// Sets upDiff slider and spinBox
	ui->spinBoxUpDiff->setValue(processor->getUpDiff());

}

/*
 * Setup processor from current UI settings when processor source image
 * changes
 */
void MainWindow::setupProcessorfromUI()
{
	if (ui->radioButtonInput->isChecked())
	{
		processor->setDisplayMode(CvFloodFill::INPUT_IM);
	}

	if (ui->radioButtonMask->isChecked())
	{
		processor->setDisplayMode(CvFloodFill::MASK_IM);
	}

	if (ui->radioButtonMerged->isChecked())
	{
		processor->setDisplayMode(CvFloodFill::MERGED_IM);
	}

	if (ui->radioButtonAbsThreshold->isChecked())
	{
		processor->setFfillMode(CvFloodFill::FIXED_RANGE);
	}

	if (ui->radioButtonRelThreshold->isChecked())
	{
		processor->setFfillMode(CvFloodFill::FLOATING_RANGE);
	}

	processor->setShowBoundingBox(ui->checkBoxBBox->isChecked());
	processor->setShowSeed(ui->checkBoxCenter->isChecked());

	if (ui->radioButton4Connect->isChecked())
	{
		processor->setConnectivity(4);
	}

	if (ui->radioButton8Connect->isChecked())
	{
		processor->setConnectivity(8);
	}

	processor->setLoDiff(ui->spinBoxLoDiff->value());
	processor->setUpDiff(ui->spinBoxUpDiff->value());
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
//		if (!capture->open(fileName))
//		{
//			qWarning("Unable to open device file : %s",
//					 fileName.toStdString().c_str());
//		}
//		// setupProcessorFromUI(); // already done from connection
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
 * Menu action when gray image is selected.
 * Sets capture to convert source image to gray
 */
void MainWindow::on_actionGray_triggered()
{
	bool isGray = !capture->isGray();

	emit grayChanged(isGray);
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
 * Convert capture image to gray
 */
void MainWindow::on_checkBoxGray_clicked()
{
	bool isGray = ui->checkBoxGray->isChecked();
	emit grayChanged(isGray);
}

/*
 * Select input image for display
 */
void MainWindow::on_radioButtonInput_clicked()
{
	processor->setDisplayMode(CvFloodFill::INPUT_IM);
}

/*
 * Select mask image for display
 */
void MainWindow::on_radioButtonMask_clicked()
{
	processor->setDisplayMode(CvFloodFill::MASK_IM);
}

/*
 * Select merged image for display
 */
void MainWindow::on_radioButtonMerged_clicked()
{
	processor->setDisplayMode(CvFloodFill::MERGED_IM);
}

/*
 * Select absolute threshold mode for flood fill
 */
void MainWindow::on_radioButtonAbsThreshold_clicked()
{
	processor->setFfillMode(CvFloodFill::FIXED_RANGE);
}

/*
 * Select floating threshold mode for flood fill
 */
void MainWindow::on_radioButtonRelThreshold_clicked()
{
	processor->setFfillMode(CvFloodFill::FLOATING_RANGE);
}

/*
 * Clears current floor
 */
void MainWindow::on_pushButtonClearFlood_clicked()
{
	processor->clearFlood();
}

/*
 * Generate new color for flood
 */
void MainWindow::on_pushButtonNewColor_clicked()
{
	processor->newFloodColor();
}

/*
 * Show/hides flood bouding box in source image
 */
void MainWindow::on_checkBoxBBox_clicked()
{
	processor->setShowBoundingBox(ui->checkBoxBBox->isChecked());
}

/*
 * Show/hides flood center
 */
void MainWindow::on_checkBoxCenter_clicked()
{
	processor->setShowSeed(ui->checkBoxCenter->isChecked());
}

/*
 * Changes loDiff value
 * @param value the new loDiff value
 */
void MainWindow::on_spinBoxLoDiff_valueChanged(int value)
{
	processor->setLoDiff(value);
}

/*
 * Changes upDiff value
 * @param value the new upDiff value
 */
void MainWindow::on_spinBoxUpDiff_valueChanged(int value)
{
	processor->setUpDiff(value);
}

/*
 * Selects 4 pixels connectivity for flooding
 */
void MainWindow::on_radioButton4Connect_clicked()
{
	processor->setConnectivity(4);
}

/*
 * Selects 4 pixels connectivity for flooding
 */
void MainWindow::on_radioButton8Connect_clicked()
{
	processor->setConnectivity(8);
}

/*
 * Link the two Diff sliders and spinBox together
 * @param checked the new link state
 */
void MainWindow::on_checkBoxLink_clicked(bool checked)
{
	if(checked)
	{
		// connect spinner spinBoxLoDiff  to spinBoxUpDiff
		connect(ui->spinBoxLoDiff, SIGNAL(valueChanged(int)),
				ui->spinBoxUpDiff, SLOT(setValue(int)));
		// Disable spinBoxUpDiff & horizontalSliderUpDiff
		ui->spinBoxUpDiff->setEnabled(false);
		ui->horizontalSliderUpDiff->setEnabled(false);
	}
	else
	{
		// disconnect spinner spinBoxLoDiff  to spinBoxUpDiff
		disconnect(ui->spinBoxLoDiff, SIGNAL(valueChanged(int)),
				   ui->spinBoxUpDiff, SLOT(setValue(int)));
		// Enable spinBoxUpDiff & horizontalSliderUpDiff
		ui->spinBoxUpDiff->setEnabled(true);
		ui->horizontalSliderUpDiff->setEnabled(true);
	}
}
