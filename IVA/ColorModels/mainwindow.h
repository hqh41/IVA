#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QcvVideoCapture.h"
#include "QcvColorSpaces.h"

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
 * OpenCV/Qt capture input main window
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		/**
		 * MainWindow constructor.
		 * @param capture the capture QObject to capture frames from devices
		 * or video files
		 * @param processor the colorspace class to compute various components
		 * on various color spaces
		 * @param parent parent widget
		 */
		explicit MainWindow(QcvVideoCapture * capture,
							QcvColorSpaces * processor,
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
		 * @param flip video flip
		 */
		void flipChanged(const bool flip);

		/**
		 * Signal to send when gray source image request changes
		 * @param gray gray status
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
		 * The Color space object to compute color components
		 */
		QcvColorSpaces * processor;

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
		 * Mean process time string
		 */
		QString meanTimeString;

		/**
		 * Std process time string
		 */
		QString stdTimeString;

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
		 * Setup UI according to capture settings when app launches
		 */
		void setupUIfromCapture();

		/**
		 * Setup UI according to processor settings when app launches
		 */
		void setupUIfromProcessor();

	private slots:

		/**
		 * Setup processor from current UI settings when processor source image
		 * changes
		 */
		void setupProcessorfromUI();

		/**
		 * Updates mean and std of process time
		 * @param The updated process time (MeanValue<clock_t, double>)
		 */
		void on_processTimeupdated(const CvProcessor::ProcessTime * pt);

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
		 * Select input image for display
		 */
		void on_radioButtonInput_clicked();

		/**
		 * Select Gray image for display
		 */
		void on_radioButtonGray_clicked();

		/**
		 * Select red component of RGB space for display
		 */
		void on_radioButtonRed_clicked();

		/**
		 * Select green component of RGB space for display
		 */
		void on_radioButtonGreen_clicked();

		/**
		 * Select blue component of RGB space for display
		 */
		void on_radioButtonBlue_clicked();

		/**
		 * Select hue component of HSV space for display
		 */
		void on_radioButtonHue_clicked();

		/**
		 * Select saturation component of HSV space for display
		 */
		void on_radioButtonSaturation_clicked();

		/**
		 * Select value component of HSV space for display
		 */
		void on_radioButtonValue_clicked();

		/**
		 * Select Y component of YCbCr space for display
		 */
		void on_radioButtonY_clicked();

		/**
		 * Select Cr component of YCbCr space for display
		 */
		void on_radioButtonCr_clicked();

		/**
		 * Select Cb component of YCbCr space for display
		 */
		void on_radioButtonCb_clicked();

		/**
		 * Select component display as colored image
		 */
		void on_radioButtonChColor_clicked();

		/**
		 * Select componet display as gray image
		 */
		void on_radioButtonChGray_clicked();

		/**
		 * Select hue component display as hue alone
		 */
		void on_radioButtonMixHue_clicked();

		/**
		 * Select hue component display as hue x saturation value
		 */
		void on_radioButtonMixHueSat_clicked();

		/**
		 * Select hue component display as hue x value value
		 */
		void on_radioButtonMixHueVal_clicked();

		/**
		 * Select X component for display
		 */
		void on_radioButtonXYZ_X_clicked();

		/**
		 * Select Y component for display
		 */
		void on_radioButtonXYZ_Y_clicked();

		/**
		 * Select Z component for display
		 */
		void on_radioButtonXYZ_Z_clicked();

		/**
		 * Select Maximum of RGB as display
		 */
		void on_radioButtonMaxBGR_clicked();
};

#endif // MAINWINDOW_H
