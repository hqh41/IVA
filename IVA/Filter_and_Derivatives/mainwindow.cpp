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
 * MainWindow constructor.
 * @param capture the capture QObject to capture frames from devices
 * or video files
 * @param processor the openCV image processor
 * @param parent parent widget
 */
MainWindow::MainWindow(QcvVideoCapture * capture,
					   QcvGFilter * processor,
					   QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	capture(capture),
	processor(processor),
	preferredWidth(320),
	preferredHeight(240)
{
	ui->setupUi(this);
	ui->scrollAreaSource->setBackgroundRole(QPalette::Mid);

	// ------------------------------------------------------------------------
	// Assertions
	// ------------------------------------------------------------------------
	assert(capture != NULL);

	assert(processor != NULL);

	// ------------------------------------------------------------------------
	// Special widgets initialisation
	// ------------------------------------------------------------------------
	// Replace QcvMatWidget instances with QcvMatWidgetImage instances
	// sets image widget sources for the first time
	// connects processor->update to image Widgets->updated
	// connects processor->image changed to image widgets->setSourceImage
	setRenderingMode(RENDER_IMAGE);

	// ------------------------------------------------------------------------
	// rest of Signal/Slot connections
	// ------------------------------------------------------------------------

	// Capture, processor and this messages to status bar
	connect(capture, SIGNAL(messageChanged(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	connect(processor, SIGNAL(sendMessage(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	connect(this, SIGNAL(sendMessage(QString,int)),
			ui->statusBar, SLOT(showMessage(QString,int)));

	// When Processor source image changes, some attributes are reinitialised
	// So we have to set them up again according to current UI values
	connect(processor, SIGNAL(imageChanged()),
			this, SLOT(setupProcessorFromUI()));

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

	// ------------------------------------------------------------------------
	// UI setup according to capture and processor options
	// ------------------------------------------------------------------------
	setupUIfromCatpure();
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
void MainWindow::setRenderingMode(const RenderMode mode)
{
	// Disconnect signals from slots first
	disconnect(processor, SIGNAL(updated()),
			   ui->sourceImage, SLOT(update()));

	disconnect(processor, SIGNAL(imageChanged(Mat*)),
			   ui->sourceImage, SLOT(setSourceImage(Mat*)));

	QWindow * currentWindow = windowHandle();
	if (mode == RENDER_GL)
	{
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen *)),
				   ui->sourceImage,
				   SLOT(screenChanged()));
	}

	// remove widgets in scroll areas
	QWidget * wSource = ui->scrollAreaSource->takeWidget();

	if (wSource == ui->sourceImage)
	{
		// delete removed widgets
		delete ui->sourceImage;

		// create new widget
		Mat * sourceMat = processor->getImagePtr("source");

		switch (mode)
		{
			case RENDER_PIXMAP:
				ui->sourceImage = new QcvMatWidgetLabel(sourceMat);
				break;
			case RENDER_GL:
				ui->sourceImage = new QcvMatWidgetGL(sourceMat);
				break;
			case RENDER_IMAGE:
			default:
				ui->sourceImage = new QcvMatWidgetImage(sourceMat);
				break;
		}

		if (ui->sourceImage != NULL)
		{
			// Name the new images widgets with same name as in UI files
			 ui->sourceImage->setObjectName(QString::fromUtf8("sourceImage"));

			// add to scroll areas
			ui->scrollAreaSource->setWidget(ui->sourceImage);

			// Reconnect signals to slots
			connect(processor, SIGNAL(updated()),
					ui->sourceImage, SLOT(update()));

			connect(processor, SIGNAL(imageChanged(Mat*)),
					ui->sourceImage, SLOT(setSourceImage(Mat*)));

			if (mode == RENDER_GL)
			{
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->sourceImage,
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
					message.append(tr("QGLWidget"));
					break;
				default:
				break;
			}
			emit sendMessage(message, 5000);
		}
		else
		{
			qDebug("MainWindow::on_actionRenderXXX some new widget is null");
		}
	}
	else
	{
		qDebug("MainWindow::on_actionRenderXXX removed widget is not in ui->");
	}
}

/*
 * Setup UI values from capture settings
 */
void MainWindow::setupUIfromCatpure()
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
 * Setup UI values from processor attributes
 */
void MainWindow::setupUIfromProcessor()
{
	ui->comboBoxImages->setCurrentIndex((int)processor->getDisplayMode());
	ui->comboBoxEdges->setCurrentIndex((int)processor->getEdgeMode());

	// Kernel
	ui->labelKernelMin->setText(QString::number(processor->getMinKernelSize()));
	ui->labelKernelMax->setText(QString::number(processor->getMaxKernelSize()));
	ui->spinBoxKernel->setValue(processor->getKernelSize());

	// Sigma
	setupSigma();

	// Threshold
	ui->horizontalSliderThreshold->setMinimum(processor->getMinThreshold());
	ui->horizontalSliderThreshold->setMaximum(processor->getMaxThreshold());
	ui->horizontalSliderThreshold->setSingleStep(1);
	ui->horizontalSliderThreshold->setValue(processor->getThresholdLevel());

	// Kappa
	double kappaMin = QcvGFilter::getHarrisKappaMin();
	double kappaMax = QcvGFilter::getHarrisKappaMax();
	double kappaStep = QcvGFilter::getHarrisKappaStep();
	double kappa = processor->getHarrisKappa();
//	qDebug("Kappa : %f [%f:%f:%f]",kappa, kappaMin, kappaStep, kappaMax);

	ui->labelKappaMin->setText(QString::number(kappaMin,'f',2));
	ui->labelKappaMax->setText(QString::number(kappaMax,'f',2));

	ui->doubleSpinBoxKappa->setMinimum(kappaMin);
	ui->doubleSpinBoxKappa->setMaximum(kappaMax);
	ui->doubleSpinBoxKappa->setSingleStep(kappaStep);
	ui->doubleSpinBoxKappa->setValue(kappa);

	ui->horizontalSliderKappa->setMinimum(0);
	ui->horizontalSliderKappa->setMaximum(
		double2intValue(kappaMin,
						kappaStep,
						kappaMax));
	ui->horizontalSliderKappa->setSingleStep(1);
	ui->horizontalSliderKappa->setValue(
		double2intValue(kappaMin,
						kappaStep,
						kappa));

}

/*
 * Setup Sigma slider and double spinbox according to processor
 * values
 */
void MainWindow::setupSigma()
{
	double sigmaMin = processor->getMinSigma();
	double sigmaMax = processor->getMaxSigma();
	double sigmaStep = QcvGFilter::getSigmaStep();
	double sigma = processor->getSigma();

//	qDebug("Sigma : %f [%f:%f:%f]",sigma, sigmaMin, sigmaStep, sigmaMax);

	ui->labelSigmaMin->setText(QString::number(sigmaMin,'f',2));
	ui->labelSigmaMax->setText(QString::number(sigmaMax,'f',2));

	ui->doubleSpinBoxSigma->setMinimum(sigmaMin);
	ui->doubleSpinBoxSigma->setMaximum(sigmaMax);
	ui->doubleSpinBoxSigma->setSingleStep(sigmaStep);
	ui->doubleSpinBoxSigma->setValue(sigma);

	ui->horizontalSliderSigma->setMinimum(0);
	ui->horizontalSliderSigma->setMaximum(
		double2intValue(sigmaMin,
						sigmaStep,
						sigmaMax));
	ui->horizontalSliderSigma->setSingleStep(1);
	ui->horizontalSliderSigma->setValue(
		double2intValue(sigmaMin,
						sigmaStep,
						sigma));
}

/*
 * Re setup processor from UI settings when source changes
 */
void MainWindow::setupProcessorFromUI()
{
	processor->setDisplayMode((CvGFilter::ImageDisplay)ui->comboBoxImages->currentIndex());
	processor->setEdgeMode((CvGFilter::EdgeDisplay)ui->comboBoxEdges->currentIndex());
	processor->setKernelSize(ui->spinBoxKernel->value());
	setupSigma();
	processor->setThresholdLevel(ui->spinBoxThreshold->value());
	processor->setHarrisKappa(ui->doubleSpinBoxKappa->value());
}

/*
 * Convert value of double spin box to integer slider
 * @param min minimum value of the double spin box
 * @param step step value of the double spin box
 * @param value current value of the double spin box or max value to obtain
 * integer slider max value
 * @return the integer value to set on the integer slider
 */
int MainWindow::double2intValue(const double min,
								const double step,
								const double value)
{
	return (int)((value - min)/step)+1;
}

/*
 * Convert integer value from slider to double value of double spin box
 * @param dmin the minimum double value of the spin box
 * @param dstep the step value of the double spin box
 * @param ivalue the integer value of the integer slider
 * @return the value of the double spin box
 */
double MainWindow::int2doubleValue(const double dmin,
								   const double dstep,
								   const int ivalue)
{
	return (dmin + ((double)ivalue * dstep));
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
	qDebug("Setting image rendering to: images");
	setRenderingMode(RENDER_IMAGE);
}

/*
 * Menu action to replace current image rendering widget by a
 * QcvMatWidgetLabel with pixmap instance.
 */
void MainWindow::on_actionRenderPixmap_triggered()
{
	qDebug("Setting image rendering to: pixmaps");
	setRenderingMode(RENDER_PIXMAP);
}

/*
 * Menu action to replace current image rendering widget by a
 * QcvMatWidgetGL instance.
 */
void MainWindow::on_actionRenderOpenGL_triggered()
{
	qDebug("Setting image rendering to: opengl");
	setRenderingMode(RENDER_GL);
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
 * Kernel size changed in spin box
 * @param value the new kernel size
 */
void MainWindow::on_spinBoxKernel_valueChanged(int value)
{
	processor->setKernelSize(value);

	setupSigma();
}

/*
 * Sigma gaussian variance changed in double spin box
 * @param dvalue the new sigma value
 * @post the corresponding integer value is computed and applied
 * to the integer sigma slider
 */
void MainWindow::on_doubleSpinBoxSigma_valueChanged(double dvalue)
{
	processor->setSigma(dvalue);

	int ivalue = double2intValue(ui->doubleSpinBoxSigma->minimum(),
								 ui->doubleSpinBoxSigma->singleStep(),
								 dvalue);

//	qDebug("Sigma Spinbox->Slider : convert %f [%f:%f:%f] to integer value %d [%d:%d:%d]",
//		   dvalue,
//		   ui->doubleSpinBoxSigma->minimum(),
//		   ui->doubleSpinBoxSigma->singleStep(),
//		   ui->doubleSpinBoxSigma->maximum(),
//		   ivalue,
//		   ui->horizontalSliderSigma->minimum(),
//		   ui->horizontalSliderSigma->singleStep(),
//		   ui->horizontalSliderSigma->maximum());

	ui->horizontalSliderSigma->blockSignals(true);
	ui->horizontalSliderSigma->setValue(ivalue);
	ui->horizontalSliderSigma->blockSignals(false);
}

void MainWindow::on_spinBoxThreshold_valueChanged(int value)
{
	processor->setThresholdLevel(value);
}

/*
 * Kappa harris parameter changed in double spinbox
 * @param dvalue the new kappa value
 * @post the corresponding integer value is computed and applied
 * to the integer kappa slider
 */
void MainWindow::on_doubleSpinBoxKappa_valueChanged(double dvalue)
{
	processor->setHarrisKappa(dvalue);

	int ivalue = double2intValue(ui->doubleSpinBoxKappa->minimum(),
								 ui->doubleSpinBoxKappa->singleStep(),
								 dvalue);

//	qDebug("Kappa Spinbox->Slider : convert %f [%f:%f:%f] to integer value %d [%d:%d:%d]",
//		   dvalue,
//		   ui->doubleSpinBoxKappa->minimum(),
//		   ui->doubleSpinBoxKappa->singleStep(),
//		   ui->doubleSpinBoxKappa->maximum(),
//		   ivalue,
//		   ui->horizontalSliderKappa->minimum(),
//		   ui->horizontalSliderKappa->singleStep(),
//		   ui->horizontalSliderKappa->maximum());

	ui->horizontalSliderKappa->blockSignals(true);
	ui->horizontalSliderKappa->setValue(ivalue);
	ui->horizontalSliderKappa->blockSignals(false);
}

void MainWindow::on_horizontalSliderSigma_valueChanged(int ivalue)
{
	double dvalue = int2doubleValue(ui->doubleSpinBoxSigma->minimum(),
									ui->doubleSpinBoxSigma->singleStep(),
									ivalue);

//	qDebug("Sigma Slider->spinbox : convert %d [%d:%d:%d] to double value = %f [%f:%f:%f]",
//		   ivalue,
//		   ui->horizontalSliderSigma->minimum(),
//		   ui->horizontalSliderSigma->singleStep(),
//		   ui->horizontalSliderSigma->maximum(),
//		   dvalue,
//		   ui->doubleSpinBoxSigma->minimum(),
//		   ui->doubleSpinBoxSigma->singleStep(),
//		   ui->doubleSpinBoxSigma->maximum());

	ui->doubleSpinBoxSigma->setValue(dvalue);
}

void MainWindow::on_horizontalSliderKappa_valueChanged(int ivalue)
{
	double dvalue = int2doubleValue(ui->doubleSpinBoxKappa->minimum(),
									ui->doubleSpinBoxKappa->singleStep(),
									ivalue);

//	qDebug("Kappa Slider->spinbox : convert %d [%d:%d:%d] to double value = %f [%f:%f:%f]",
//		   ivalue,
//		   ui->horizontalSliderKappa->minimum(),
//		   ui->horizontalSliderKappa->singleStep(),
//		   ui->horizontalSliderKappa->maximum(),
//		   dvalue,
//		   ui->doubleSpinBoxKappa->minimum(),
//		   ui->doubleSpinBoxKappa->singleStep(),
//		   ui->doubleSpinBoxKappa->maximum());

	ui->doubleSpinBoxKappa->setValue(dvalue);
}

/*
 * Display image selection
 * @param index the new selected image index
 */
void MainWindow::on_comboBoxImages_currentIndexChanged(int index)
{
	processor->setDisplayMode((CvGFilter::ImageDisplay)index);
}

/*
 * Edge mode selection
 * @param index the new edge mode index
 */
void MainWindow::on_comboBoxEdges_currentIndexChanged(int index)
{
	processor->setEdgeMode((CvGFilter::EdgeDisplay)index);
}
