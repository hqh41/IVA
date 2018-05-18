#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QcvVideoCapture.h"
#include "QcvDFT.h"

/**
 * Namespace for generated UI
 */
namespace Ui {
	class MainWindow;
}

/**
 * Channels index 2 Widget index conversion
 */
static const CvProcessor::Channels RGB[3] = {
	CvProcessor::RED,
	CvProcessor::GREEN,
	CvProcessor::BLUE
};

/**
 * OpenCV/Qt Histograms and LUT main window
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		/**
		 * Rendering mode for main image
		 */
		typedef enum
		{
			RENDER_IMAGE = 0,//!< QImage rendering mode
			RENDER_PIXMAP,   //!< QPixmap in a QLabel rendering mode
			RENDER_GL        //!< OpenGL in a QGLWidget rendering mode
		} RenderMode;

		/**
		 * MainWindow constructor.
		 * @param capture the capture QObject to capture frames from devices
		 * or video files
		 * @param processor Fourier transform and filter processor
		 * @param parent parent widget
		 */
		explicit MainWindow(QcvVideoCapture * capture,
							QcvDFT * processor,
							QWidget *parent = NULL);

		/**
		 * MainWindow destructor
		 */
		virtual ~MainWindow();

	signals:
		/**
		 * Signal to send update message when something changes
		 * @param message the message
		 * @param timeout number of ms the message should be displayed
		 */
		void sendMessage(const QString & message, int timeout = 0);

		/**
		 * Signal to send when video size change is requested
		 * @param size the new video size
		 */
		void sizeChanged(const QSize & size);

		/**
		 * Signal to send for opening a device (camera) with the capture
		 * @param deviceId device number to open
		 * @param width desired width or 0 to keep capture width
		 * @param height desired height or 0 to keep capture height
		 * @return true if device has been opened and checked and timer launched
		 */
		void deviceChanged(const int deviceId,
						   const unsigned int width,
						   const unsigned int height);

		/**
		 * Signal to send for opening a video file in the capture
		 * @param fileName video file to open
		 * @param width desired width or 0 to keep capture width
		 * @param height desired height or 0 to keep capture height
		 * @return true if video has been opened and timer launched
		 */
		void fileChanged(const QString & fileName,
						 const unsigned int width,
						 const unsigned int height);

		/**
		 * Signal to send when requesting video flip
		 * @param flip the video flip status
		 */
		void flipChanged(const bool flip);

		/**
		 * Signal to send when requesting gray changed
		 * @param gray the gray status
		 */
		void grayChanged(const bool gray);

	private:
		/**
		 * The UI built in QtDesigner or QtCreator
		 */
		Ui::MainWindow *ui;

		/**
		 * The Capture object grabs frame using OpenCV HiGui
		 */
		QcvVideoCapture * capture;

		/**
		 * The Fourier Transform and filter processor
		 */
		QcvDFT * processor;

		/**
		 * Image preferred width
		 */
		int preferredWidth;

		/**
		 * Image preferred height
		 */
		int preferredHeight;

		/**
		 * Message to send to statusBar
		 */
		QString message;

		/**
		 * Changes widgetImage nature according to desired rendering mode.
		 * Possible values for mode are:
		 * 	- IMAGE: widgetImage is assigned to a QcvMatWidgetImage instance
		 * 	- PIXMAP: widgetImage is assigned to a QcvMatWidgetLabel instance
		 * 	- GL: widgetImage is assigned to a QcvMatWidgetGL instance
		 * @param mode
		 */
		void setRenderingMode(const RenderMode mode);

		/**
		 * Set filters spinBoxes and sliders link state
		 * @param linked the link status
		 * @post When link is on all sliders/spinboxes of low pass and high pass
		 * filters are linked together, moving/changing one changes the others.
		 * When link os off sliders/spinboxes are not linked together
		 */
		void setLinkedFilterSizes(bool linked);

	private slots:

		/**
		 * Re setup processor from UI settings when source image changes
		 */
		void setupProcessorFromUI();

		/**
		 * Setup filter min/max and evt values according to source image size.
		 * Filter max size is \f$\frac{FFTSize}{\sqrt{2}}\f$
		 */
		void setupFilterSizes();

		/**
		 * Setup filters sliders/spinboxes availability according to the number
		 * of channels in the source image
		 */
		void setupFiltersAvailability();

		/**
		 * Menu action when Sources->camera 0 is selected
		 * Sets capture to open device 0. If device is not available
		 * menu item is set to inactive.
		 */
		void on_actionCamera_0_triggered();

		/**
		 * Menu action when Sources->camera 1 is selected
		 * Sets capture to open device 0. If device is not available
		 * menu item is set to inactive
		 */
		void on_actionCamera_1_triggered();

		/**
		 * Menu action when Sources->file is selected.
		 * Opens file dialog and tries to open selected file (is not empty),
		 * then sets capture to open the selected file
		 */
		void on_actionFile_triggered();

		/**
		 * Menu action to quit application.
		 */
		void on_actionQuit_triggered();

		/**
		 * Menu action when flip image is selected.
		 * Sets capture to change flip status which leads to reverse
		 * image horizontally
		 */
		void on_actionFlip_triggered();

		/**
		 * Menu action when gray image is selected.
		 * Sets capture to change gray status which leads convert captured image
		 * to gray or not
		 */
		void on_actionGray_triggered();

		/**
		 * Menu action when original image size is selected.
		 * Sets capture not to resize image
		 */
		void on_actionOriginalSize_triggered();

		/**
		 * Menu action when constrained image size is selected.
		 * Sets capture resize to preferred width and height
		 */
		void on_actionConstrainedSize_triggered();

		/**
		 * Menu action to replace current image rendering widget by a
		 * QcvMatWidgetImage instance.
		 */
		void on_actionRenderImage_triggered();

		/**
		 * Menu action to replace current image rendering widget by a
		 * QcvMatWidgetLabel with pixmap instance.
		 */
		void on_actionRenderPixmap_triggered();

		/**
		 * Menu action to replace current image rendering widget by a
		 * QcvMatWidgetGL instance.
		 */
		void on_actionRenderOpenGL_triggered();

		/**
		 * Original size radioButton action.
		 * Sets capture resize to off
		 */
		void on_radioButtonOrigSize_clicked();

		/**
		 * Custom size radioButton action.
		 * Sets capture resize to preferred width and height
		 */
		void on_radioButtonCustomSize_clicked();

		/**
		 * Width spinbox value change.
		 * Changes the preferred width and if custom size is selected apply
		 * this custom width
		 * @param value the desired width
		 */
		void on_spinBoxWidth_valueChanged(int value);

		/**
		 * Height spinbox value change.
		 * Changes the preferred height and if custom size is selected apply
		 * this custom height
		 * @param value the desired height
		 */
		void on_spinBoxHeight_valueChanged(int value);

		/**
		 * Flip capture image horizontally.
		 * changes capture flip status
		 */
		void on_checkBoxFlip_clicked();

		/**
		 * convert capture image to gray level.
		 * changes cpature gray conversion status
		 */
		void on_checkBoxGray_clicked();

		/**
		 * Changes logscale factor for spectrum
		 * @param value the new logscale factor
		 */
		void on_spinBoxMag_valueChanged(int value);

		/**
		 * Sets filtering on/off
		 */
		void on_checkBoxFiltering_clicked();

		/**
		 * Sets Filter mode to box
		 */
		void on_radioButtonFilterBox_clicked();

		/**
		 * Sets filter mode to gaussian
		 */
		void on_radioButtonFilterGauss_clicked();

		/**
		 * Sets filter mode to sinus cardinal
		 */
		void on_radioButtonFilterSinc_clicked();

		/**
		 * Changes low pass filter size for red component
		 * @param value the new low pass filter size for red component
		 * @note low pass filters are lower bounded by their respective high
		 * pass filters
		 */
		void on_spinBoxRedLP_valueChanged(int value);

		/**
		 * Changes low pass filter size for green component
		 * @param value the new low pass filter size for green component
		 * @note low pass filters are lower bounded by their respective high
		 * pass filters
		 */
		void on_spinBoxGreenLP_valueChanged(int value);

		/**
		 * Changes low pass filter size for blue component
		 * @param value the new low pass filter size for blue component
		 * @note low pass filters are lower bounded by their respective high
		 * pass filters
		 */
		void on_spinBoxBlueLP_valueChanged(int value);

		/**
		 * Changes high pass filter size for red component
		 * @param value the new high pass filter size for red component
		 * @note high pass filters are upper bounded by their respective low
		 * pass filters
		 */
		void on_spinBoxRedHP_valueChanged(int value);

		/**
		 * Changes high pass filter size for green component
		 * @param value the new high pass filter size for green component
		 * @note high pass filters are upper bounded by their respective low
		 * pass filters
		 */
		void on_spinBoxGreenHP_valueChanged(int value);

		/**
		 * Changes high pass filter size for blue component
		 * @param value the new high pass filter size for blue component
		 * @note high pass filters are upper bounded by their respective low
		 * pass filters
		 */
		void on_spinBoxBlueHP_valueChanged(int value);

		/**
		 * Changes spinboxes/sliders link mode from low pass pane
		 */
		void on_checkBoxLinkLP_clicked();

		/**
		 * Changes spinboxes/sliders link mode from high pass pane
		 */
		void on_checkBoxLinkHP_clicked();
};

#endif // MAINWINDOW_H
