#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QcvVideoCapture.h"
#include "QcvHistograms.h"

/**
 * Namespace for generated UI
 */
namespace Ui {
	class MainWindow;
}

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
 * OpenCV/Qt Histograms and LUT main window
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		/**
		 * MainWindow constructor.
		 * @param capture the capture QObject to capture frames from devices
		 * or video files
		 * @param processor processor and LUT processing class
		 * @param parent parent widget
		 */
		explicit MainWindow(QcvVideoCapture * capture,
							QcvHistograms * histograms,
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
		 * Signal to send when video size is changed
		 * @param size the new video size
		 */
		void sizeChanged(const QSize & size);

		/**
		 * Signal to send when requesting opening a device (camera)
		 * @param deviceId the device ID
		 * @param width the requested video width
		 * @param height the requested video height
		 */
		void openDevice(const int deviceId,
						const unsigned int width,
						const unsigned int height);
		/**
		 * Signal to send when requesting opening a file
		 * @param deviceId the device ID
		 * @param width the requested video width
		 * @param height the requested video height
		 */
		void openFile(const QString & fileName,
					  const unsigned int width,
					  const unsigned int height);

		/**
		 * Signal to send when requesting video flip
		 * @param flip video flip
		 */
		void flipVideo(const bool flip);

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
		 * The Hist and LUT object compute histograms and performs LUT
		 * on capture source image
		 */
		QcvHistograms * processor;

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
		void setupImageWidget(const RenderMode mode);

		/**
		 * Setup UI from capture settings when launching application
		 */
		void setupUIfromCapture();

		/**
		 * Setup UI from processor settings when launching application
		 */
		void setupUIfromProcessor();

	private slots:

		/**
		 * Re setup processor from UI settings when source image changes
		 */
		void setupProcessorFromUI();

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
		 * Set transfert function to identity
		 */
		void on_radioButtonIdentity_clicked();

		/**
		 * Set transfert function to inverse
		 */
		void on_radioButtonInverse_clicked();

		/**
		 * Set transfert function to gamma
		 */
		void on_radioButtonGamma_clicked();

		/**
		 * Set transfert function to threshold
		 */
		void on_radioButtonThreshold_clicked();

		/**
		 * Set transfert function to optimal dynamic
		 */
		void on_radioButtonDynamic_clicked();

		/**
		 * Set transfert function to equalization
		 */
		void on_radioButtonEqualize_clicked();

		/**
		 * Set transfert function depending on processor to use colors
		 * components of the histogram generating 1 transfert function per image
		 * channels
		 */
		void on_radioButtonChColor_clicked();

		/**
		 * Set transfert function depending on processor to use gray level
		 * histogram component generating 1 transfert function per image
		 * channels
		 */
		void on_radioButtonChGray_clicked();

		/**
		 * Modify lut parameter applied to transfert function depending on
		 * histogram
		 * @param value the new value of lutParam
		 */
		void on_spinBoxlutParam_valueChanged(int value);

		/**
		 * Set histogram mode to normal
		 */
		void on_radioButtonHMNormal_clicked();

		/**
		 * Set Histogram mode to cumulative
		 */
		void on_radioButtonHMCumulative_clicked();

		/**
		 * set Histogram mode to time cumulative
		 */
		void on_radioButtonHMTime_clicked();

		/**
		 * Show/Hides histogram red component
		 */
		void on_checkBoxHistRed_clicked();

		/**
		 * Show/Hides histogram green component
		 */
		void on_checkBoxHistGreen_clicked();

		/**
		 * Show/Hides histogram Blue component
		 */
		void on_checkBoxHistBlue_clicked();

		/**
		 * Show/Hides histogram gray component
		 */
		void on_checkBoxHistGray_clicked();
};

#endif // MAINWINDOW_H
