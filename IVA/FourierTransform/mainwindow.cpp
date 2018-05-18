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
 * @param processor Fourier transform and filter processor
 * @param parent parent widget
 */
MainWindow::MainWindow(QcvVideoCapture * capture,
					   QcvDFT * processor,
					   QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	capture(capture),
	processor(processor),
	preferredWidth(341),
	preferredHeight(256)
{
	ui->setupUi(this);
	ui->scrollAreaSource->setBackgroundRole(QPalette::Mid);
	ui->scrollAreaSpectrum->setBackgroundRole(QPalette::Mid);
	ui->scrollAreaInverse->setBackgroundRole(QPalette::Mid);

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

	ui->labelFFTSizeValue->setText(QString::number(processor->getOptimalDftSize()));

	// Setup filter sizes according to image size
	setupFilterSizes();

	// Setup spin and sliders availability according to image colors
	setupFiltersAvailability();

	// ------------------------------------------------------------------------
	// rest of Signal/Slot connections
	// ------------------------------------------------------------------------
	// processor->sendText --> labelFFTSizeValue->setText when source image
	// changes, fft size might also change

	connect(processor, SIGNAL(sendText(QString)),
			ui->labelFFTSizeValue, SLOT(setText(QString)));

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

	// When processor images size changes we need to update filter sizes
	// (min, max & value)
	connect(processor, SIGNAL(imageSizeChanged()),
			this, SLOT(setupFilterSizes()));

	// When processor image color channels changes we need to update filters
	// available sliders and spin boxes
	connect(processor, SIGNAL(imageColorsChanged()),
			this, SLOT(setupFiltersAvailability()));

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

	// Sets grayCheckbox and menu item states
	bool gray = capture->isGray();
	ui->actionGray->setChecked(gray);
	ui->checkBoxGray->setChecked(gray);

	// ------------------------------------------------------------------------
	// UI setup according to DFTProcessor options
	// ------------------------------------------------------------------------
	// Setting up log scale spinbox value and boundaries
	ui->spinBoxMag->setValue((int)processor->getLogScaleFactor());
	ui->spinBoxMag->setMinimum((int)processor->minLogScaleFactor);
	ui->spinBoxMag->setMaximum((int)processor->maxLogScaleFactor);

	// Setting up filtering checkbox
	ui->checkBoxFiltering->setChecked(processor->isFiltering());

	// Setting up filtering type
	CvDFT::FilterType type = processor->getFilterType();
	switch (type)
	{
		case CvDFT::BOX_FILTER:
			ui->radioButtonFilterBox->setChecked(true);
			break;
		case CvDFT::GAUSS_FILTER:
			ui->radioButtonFilterGauss->setChecked(true);
			break;
		case CvDFT::SINC_FILTER:
			ui->radioButtonFilterSinc->setChecked(true);
			break;
		default:
			break;
	}
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
 * Sets capture to change gray status which leads convert captured image
 * to gray or not
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
	disconnect(processor, SIGNAL(updated()),
			   ui->spectrumImage, SLOT(update()));
	disconnect(processor, SIGNAL(updated()),
			   ui->inverseImage, SLOT(update()));

	disconnect(processor, SIGNAL(squareImageChanged(Mat*)),
			   ui->sourceImage, SLOT(setSourceImage(Mat*)));
	disconnect(processor, SIGNAL(spectrumImageChanged(Mat*)),
			   ui->spectrumImage, SLOT(setSourceImage(Mat*)));
	disconnect(processor, SIGNAL(inverseImageChanged(Mat*)),
			   ui->inverseImage, SLOT(setSourceImage(Mat*)));

	QWindow * currentWindow = windowHandle();
	if (mode == RENDER_GL)
	{
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen *)),
				   ui->sourceImage,
				   SLOT(screenChanged()));
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen*)),
				   ui->spectrumImage,
				   SLOT(screenChanged()));
		disconnect(currentWindow,
				   SIGNAL(screenChanged(QScreen*)),
				   ui->inverseImage,
				   SLOT(screenChanged()));
	}

	// remove widgets in scroll areas
	QWidget * wSource = ui->scrollAreaSource->takeWidget();
	QWidget * wSpectrum = ui->scrollAreaSpectrum->takeWidget();
	QWidget * wInverse = ui->scrollAreaInverse->takeWidget();

	if ((wSource == ui->sourceImage) &&
		(wSpectrum == ui->spectrumImage) &&
		(wInverse == ui->inverseImage))
	{
		// delete removed widgets
		delete ui->sourceImage;
		delete ui->spectrumImage;
		delete ui->inverseImage;

		// create new widget
		Mat * sourceMat = processor->getImagePtr("square");
		Mat * spectrumMat = processor->getImagePtr("spectrum");
		Mat * inverseMat = processor->getImagePtr("inverse");

		switch (mode)
		{
			case RENDER_PIXMAP:
				ui->sourceImage = new QcvMatWidgetLabel(sourceMat);
				ui->spectrumImage = new QcvMatWidgetLabel(spectrumMat);
				ui->inverseImage = new QcvMatWidgetLabel(inverseMat);
				break;
			case RENDER_GL:
				ui->sourceImage = new QcvMatWidgetGL(sourceMat);
				ui->spectrumImage = new QcvMatWidgetGL(spectrumMat);
				ui->inverseImage = new QcvMatWidgetGL(inverseMat);
				break;
			case RENDER_IMAGE:
			default:
				ui->sourceImage = new QcvMatWidgetImage(sourceMat);
				ui->spectrumImage = new QcvMatWidgetImage(spectrumMat);
				ui->inverseImage = new QcvMatWidgetImage(inverseMat);
				break;
		}

		if ((ui->sourceImage != NULL) &&
			(ui->spectrumImage != NULL) &&
			(ui->inverseImage != NULL))
		{
			// Name the new images widgets with same name as in UI files
			 ui->sourceImage->setObjectName(QString::fromUtf8("sourceImage"));
			 ui->spectrumImage->setObjectName(QString::fromUtf8("spectrumImage"));
			 ui->inverseImage->setObjectName(QString::fromUtf8("inverseImage"));

			// add to scroll areas
			ui->scrollAreaSource->setWidget(ui->sourceImage);
			ui->scrollAreaSpectrum->setWidget(ui->spectrumImage);
			ui->scrollAreaInverse->setWidget(ui->inverseImage);

			// Reconnect signals to slots
			connect(processor, SIGNAL(updated()),
					ui->sourceImage, SLOT(update()));
			connect(processor, SIGNAL(updated()),
					ui->spectrumImage, SLOT(update()));
			connect(processor, SIGNAL(updated()),
					ui->inverseImage, SLOT(update()));

			connect(processor, SIGNAL(squareImageChanged(Mat*)),
					ui->sourceImage, SLOT(setSourceImage(Mat*)));
			connect(processor, SIGNAL(spectrumImageChanged(Mat*)),
					ui->spectrumImage, SLOT(setSourceImage(Mat*)));
			connect(processor, SIGNAL(inverseImageChanged(Mat*)),
					ui->inverseImage, SLOT(setSourceImage(Mat*)));

			if (mode == RENDER_GL)
			{
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->sourceImage,
						SLOT(screenChanged()));
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->spectrumImage,
						SLOT(screenChanged()));
				connect(currentWindow,
						SIGNAL(screenChanged(QScreen *)),
						ui->inverseImage,
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
 * Re setup processor from UI settings when source changes
 */
void MainWindow::setupProcessorFromUI()
{
	processor->setLogScaleFactor((double)ui->spinBoxMag->value());

	if (ui->radioButtonFilterBox->isChecked())
	{
		processor->setFilterType(CvDFT::BOX_FILTER);
	}
	else if (ui->radioButtonFilterGauss->isChecked())
	{
		processor->setFilterType(CvDFT::GAUSS_FILTER);
	}
	else
	{
		processor->setFilterType(CvDFT::SINC_FILTER);
	}

	processor->setFiltering(ui->checkBoxFiltering->isChecked());

	processor->setLowPassFilterSize(CvDFT::BLUE, ui->spinBoxBlueLP->value());
	processor->setLowPassFilterSize(CvDFT::GREEN, ui->spinBoxGreenLP->value());
	processor->setLowPassFilterSize(CvDFT::RED, ui->spinBoxRedLP->value());

	processor->setHighPassFilterSize(CvDFT::BLUE, ui->spinBoxBlueHP->value());
	processor->setHighPassFilterSize(CvDFT::GREEN, ui->spinBoxGreenHP->value());
	processor->setHighPassFilterSize(CvDFT::RED, ui->spinBoxRedHP->value());
}

/*
 * Setup filter min/max and evt values according to source image size.
 * Filter max size is \$f\frac{FFTSize}{\sqrt{2}}\$f
 */
void MainWindow::setupFilterSizes()
{
	qDebug("Setting up filter sizes and values");

	int maxFilterValue = (int)processor->getMaxFilterSize();
	int minFilterValue = (int)processor->getMinFilterSize();
	int nbChannels = processor->getNbChannels();

	// spin boxes in same order as openCV components
	QSpinBox * lowPassSpinBoxes[3] =
	{
		ui->spinBoxBlueLP,
		ui->spinBoxGreenLP,
		ui->spinBoxRedLP,
	};

	// sliders in same order as openCV components
	QSlider * lowPassSliders[3] =
	{
		ui->horizontalSliderBLP,
		ui->horizontalSliderGLP,
		ui->horizontalSliderRLP
	};

	for (int i=0; i < 3; i++)
	{
		lowPassSpinBoxes[i]->setMaximum(maxFilterValue);
		lowPassSpinBoxes[i]->setMinimum(minFilterValue);
		lowPassSliders[i]->setMaximum(maxFilterValue);
		lowPassSliders[i]->setMinimum(minFilterValue);

		if (i < nbChannels)
		{
			lowPassSpinBoxes[i]->setValue(processor->getLowPassFilterSize(i));
		}
		else
		{
			lowPassSpinBoxes[i]->setValue(maxFilterValue);
		}
	}

	QSpinBox * highPassSpinBoxes[3] =
	{
		ui->spinBoxBlueHP,
		ui->spinBoxGreenHP,
		ui->spinBoxRedHP
	};

	QSlider * highPassSliders[3] =
	{
		ui->horizontalSliderBHP,
		ui->horizontalSliderGHP,
		ui->horizontalSliderRHP
	};

	for (int i=0; i < 3; i++)
	{
		highPassSpinBoxes[i]->setMaximum(maxFilterValue);
		highPassSpinBoxes[i]->setMinimum(minFilterValue);
		highPassSliders[i]->setMaximum(maxFilterValue);
		highPassSliders[i]->setMinimum(minFilterValue);

		if (i < nbChannels)
		{
			highPassSpinBoxes[i]->setValue(processor->getHighPassFilterSize(i));
		}
		else
		{
			highPassSpinBoxes[i]->setValue(minFilterValue);
		}
	}
}

/*
 * Setup filters sliders/spinboxes availability according to the number
 * of channels in the source image
 */
void MainWindow::setupFiltersAvailability()
{
	int nbChannels = processor->getNbChannels();

	qDebug("Setting up filters availability with %d channels", nbChannels);

	QSpinBox * lowPassSpinBoxes[3] =
	{
		ui->spinBoxBlueLP,
		ui->spinBoxGreenLP,
		ui->spinBoxRedLP
	};

	QSlider * lowPassSliders[3] =
	{
		ui->horizontalSliderBLP,
		ui->horizontalSliderGLP,
		ui->horizontalSliderRLP
	};

	for (int i=0; i < 3; i++)
	{
		if (i < nbChannels)
		{
			lowPassSpinBoxes[i]->setEnabled(true);
			lowPassSliders[i]->setEnabled(true);

			// Re set processor filter values
			processor->setLowPassFilterSize(i, lowPassSpinBoxes[i]->value());
		}
		else
		{
			lowPassSpinBoxes[i]->setEnabled(false);
			lowPassSliders[i]->setEnabled(false);
		}
	}

	QSpinBox * highPassSpinBoxes[3] =
	{
		ui->spinBoxBlueHP,
		ui->spinBoxGreenHP,
		ui->spinBoxRedHP
	};

	QSlider * highPassSliders[3] =
	{
		ui->horizontalSliderBHP,
		ui->horizontalSliderGHP,
		ui->horizontalSliderRHP
	};

	for (int i=0; i < 3; i++)
	{
		if (i < nbChannels)
		{
			highPassSpinBoxes[i]->setEnabled(true);
			highPassSliders[i]->setEnabled(true);

			// Re set processor filter values
			processor->setHighPassFilterSize(i, highPassSpinBoxes[i]->value());
		}
		else
		{
			highPassSpinBoxes[i]->setEnabled(false);
			highPassSliders[i]->setEnabled(false);
		}
	}

	if (nbChannels == 1)
	{
		setLinkedFilterSizes(false);
		ui->checkBoxLinkLP->setEnabled(false);
		ui->checkBoxLinkHP->setEnabled(false);

		ui->labelBlueLP->setText(tr("Gray"));
		ui->labelBlueHP->setText(tr("Gray"));
	}
	else
	{
		ui->checkBoxLinkLP->setEnabled(true);
		ui->checkBoxLinkHP->setEnabled(true);

		ui->labelBlueLP->setText(tr("Blue"));
		ui->labelBlueHP->setText(tr("Blue"));
	}
}


/*
 * Set filters spinBoxes and sliders link state
 * @param linked the link status
 * @post When link is on all sliders/spinboxes of low pass and high pass
 * filters are linked together, moving/changing one changes the others.
 * When link os off sliders/spinboxes are not linked together
 */
void MainWindow::setLinkedFilterSizes(bool linked)
{
	if (linked)
	{
		qDebug("Linking Sliders together");
		// check all link checkboxes since we don't know which one lead here
		ui->checkBoxLinkLP->setChecked(true);
		ui->checkBoxLinkHP->setChecked(true);

		// set blue/green values to red value
		int redLPValue = ui->spinBoxRedLP->value();
		ui->spinBoxGreenLP->setValue(redLPValue);
		ui->spinBoxBlueLP->setValue(redLPValue);
		int redHPValue = ui->spinBoxRedHP->value();
		ui->spinBoxGreenHP->setValue(redHPValue);
		ui->spinBoxBlueHP->setValue(redHPValue);

		// link all filter sizes sliders and spinboxes together
		// only spinboxes are affected since sliders and spinboxes
		// arer already connected together

		// red -> green
		connect(ui->spinBoxRedLP, SIGNAL(valueChanged(int)),
				ui->spinBoxGreenLP, SLOT(setValue(int)));
		connect(ui->spinBoxRedHP, SIGNAL(valueChanged(int)),
				ui->spinBoxGreenHP, SLOT(setValue(int)));

		// red -> blue
		connect(ui->spinBoxRedLP, SIGNAL(valueChanged(int)),
				ui->spinBoxBlueLP, SLOT(setValue(int)));
		connect(ui->spinBoxRedHP, SIGNAL(valueChanged(int)),
				ui->spinBoxBlueHP, SLOT(setValue(int)));

		// green -> red
		connect(ui->spinBoxGreenLP, SIGNAL(valueChanged(int)),
				ui->spinBoxRedLP, SLOT(setValue(int)));
		connect(ui->spinBoxGreenHP, SIGNAL(valueChanged(int)),
				ui->spinBoxRedHP, SLOT(setValue(int)));

		// green -> blue
		connect(ui->spinBoxGreenLP, SIGNAL(valueChanged(int)),
				ui->spinBoxBlueLP, SLOT(setValue(int)));
		connect(ui->spinBoxGreenHP, SIGNAL(valueChanged(int)),
				ui->spinBoxBlueHP, SLOT(setValue(int)));

		// blue -> red
		connect(ui->spinBoxBlueLP, SIGNAL(valueChanged(int)),
				ui->spinBoxRedLP, SLOT(setValue(int)));
		connect(ui->spinBoxBlueHP, SIGNAL(valueChanged(int)),
				ui->spinBoxRedHP, SLOT(setValue(int)));

		// blue -> green
		connect(ui->spinBoxBlueLP, SIGNAL(valueChanged(int)),
				ui->spinBoxGreenLP, SLOT(setValue(int)));
		connect(ui->spinBoxBlueHP, SIGNAL(valueChanged(int)),
				ui->spinBoxGreenHP, SLOT(setValue(int)));
	}
	else
	{
		qDebug("Unlink sliders from each other");
		// uncheck all link checkboxes since we don't know which one lead here
		ui->checkBoxLinkLP->setChecked(false);
		ui->checkBoxLinkHP->setChecked(false);

		// unlink all filter sizes sliders and spinboxes from each other
		// only spinboxes are affected since sliders and spinboxes
		// arer already connected together

		// red -> green
		disconnect(ui->spinBoxRedLP, SIGNAL(valueChanged(int)),
				   ui->spinBoxGreenLP, SLOT(setValue(int)));
		disconnect(ui->spinBoxRedHP, SIGNAL(valueChanged(int)),
				   ui->spinBoxGreenHP, SLOT(setValue(int)));

		// red -> blue
		disconnect(ui->spinBoxRedLP, SIGNAL(valueChanged(int)),
				   ui->spinBoxBlueLP, SLOT(setValue(int)));
		disconnect(ui->spinBoxRedHP, SIGNAL(valueChanged(int)),
				   ui->spinBoxBlueHP, SLOT(setValue(int)));

		// green -> red
		disconnect(ui->spinBoxGreenLP, SIGNAL(valueChanged(int)),
				   ui->spinBoxRedLP, SLOT(setValue(int)));
		disconnect(ui->spinBoxGreenHP, SIGNAL(valueChanged(int)),
				   ui->spinBoxRedHP, SLOT(setValue(int)));

		// green -> blue
		disconnect(ui->spinBoxGreenLP, SIGNAL(valueChanged(int)),
				   ui->spinBoxBlueLP, SLOT(setValue(int)));
		disconnect(ui->spinBoxGreenHP, SIGNAL(valueChanged(int)),
				   ui->spinBoxBlueHP, SLOT(setValue(int)));

		// blue -> red
		disconnect(ui->spinBoxBlueLP, SIGNAL(valueChanged(int)),
				   ui->spinBoxRedLP, SLOT(setValue(int)));
		disconnect(ui->spinBoxBlueHP, SIGNAL(valueChanged(int)),
				   ui->spinBoxRedHP, SLOT(setValue(int)));

		// blue -> green
		disconnect(ui->spinBoxBlueLP, SIGNAL(valueChanged(int)),
				   ui->spinBoxGreenLP, SLOT(setValue(int)));
		disconnect(ui->spinBoxBlueHP, SIGNAL(valueChanged(int)),
				   ui->spinBoxGreenHP, SLOT(setValue(int)));
	}
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
 * convert capture image to gray level.
 * changes cpature gray conversion status
 */
void MainWindow::on_checkBoxGray_clicked()
{
	bool isGray = ui->checkBoxGray->isChecked();
	emit grayChanged(isGray);
}

/*
 * Changes logscale factor for spectrum
 * @param value the new logscale factor
 */
void MainWindow::on_spinBoxMag_valueChanged(int value)
{
	processor->setLogScaleFactor((double)value);

	double realScale = processor->getLogScaleFactor();

	ui->spinBoxMag->setValue((int)realScale);
}

/*
 * Sets filtering on/off
 */
void MainWindow::on_checkBoxFiltering_clicked()
{
	processor->setFiltering(ui->checkBoxFiltering->isChecked());
}

/*
 * Sets Filter mode to box
 */
void MainWindow::on_radioButtonFilterBox_clicked()
{
	processor->setFilterType(CvDFT::BOX_FILTER);
}

/*
 * Sets filter mode to gaussian
 */
void MainWindow::on_radioButtonFilterGauss_clicked()
{
	processor->setFilterType(CvDFT::GAUSS_FILTER);
}

/*
 * Sets filter mode to sinus cardinal
 */
void MainWindow::on_radioButtonFilterSinc_clicked()
{
	processor->setFilterType(CvDFT::SINC_FILTER);
}

/*
 * Changes low pass filter size for red component
 * @param value the new low pass filter size for red component
 * @note low pass filters are lower bounded by their respective high
 * pass filters
 */
void MainWindow::on_spinBoxRedLP_valueChanged(int value)
{
	processor->setLowPassFilterSize(CvDFT::RED, value);
	// low pass filter might be lower bounded by high pass filter
	ui->spinBoxRedLP->setValue(processor->getLowPassFilterSize(CvDFT::RED));
}

/*
 * Changes low pass filter size for green component
 * @param value the new low pass filter size for green component
 * @note low pass filters are lower bounded by their respective high
 * pass filters
 */
void MainWindow::on_spinBoxGreenLP_valueChanged(int value)
{
	processor->setLowPassFilterSize(CvDFT::GREEN, value);
	// low pass filter might be lower bounded by high pass filter
	ui->spinBoxGreenLP->setValue(processor->getLowPassFilterSize(CvDFT::GREEN));
}

/*
 * Changes low pass filter size for blue component
 * @param value the new low pass filter size for blue component
 * @note low pass filters are lower bounded by their respective high
 * pass filters
 */
void MainWindow::on_spinBoxBlueLP_valueChanged(int value)
{
	processor->setLowPassFilterSize(CvDFT::BLUE, value);
	// low pass filter might be lower bounded by high pass filter
	ui->spinBoxBlueLP->setValue(processor->getLowPassFilterSize(CvDFT::BLUE));
}

/*
 * Changes high pass filter size for red component
 * @param value the new high pass filter size for red component
 * @note high pass filters are upper bounded by their respective low
 * pass filters
 */
void MainWindow::on_spinBoxRedHP_valueChanged(int value)
{
	processor->setHighPassFilterSize(CvDFT::RED, value);
	// high pass filter might be upper bounded by low pass filter
	ui->spinBoxRedHP->setValue(processor->getHighPassFilterSize(CvDFT::RED));
}

/*
 * Changes high pass filter size for green component
 * @param value the new high pass filter size for green component
 * @note high pass filters are upper bounded by their respective low
 * pass filters
 */
void MainWindow::on_spinBoxGreenHP_valueChanged(int value)
{
	processor->setHighPassFilterSize(CvDFT::GREEN, value);
	// high pass filter might be upper bounded by low pass filter
	ui->spinBoxGreenHP->setValue(processor->getHighPassFilterSize(CvDFT::GREEN));
}

/*
 * Changes high pass filter size for blue component
 * @param value the new high pass filter size for blue component
 * @note high pass filters are upper bounded by their respective low
 * pass filters
 */
void MainWindow::on_spinBoxBlueHP_valueChanged(int value)
{
	processor->setHighPassFilterSize(CvDFT::BLUE, value);
	// high pass filter might be upper bounded by low pass filter
	ui->spinBoxBlueHP->setValue(processor->getHighPassFilterSize(CvDFT::BLUE));
}

/*
 * Changes spinboxes/sliders link mode from low pass pane
 */
void MainWindow::on_checkBoxLinkLP_clicked()
{
	setLinkedFilterSizes(ui->checkBoxLinkLP->isChecked());
}

/*
 * Changes spinboxes/sliders link mode from low pass pane
 */
void MainWindow::on_checkBoxLinkHP_clicked()
{
	setLinkedFilterSizes(ui->checkBoxLinkHP->isChecked());
}
