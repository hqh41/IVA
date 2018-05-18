#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QcvVideoCapture.h"
#include "QcvGFilter.h"

/**
 * Namespace for generated UI
 */
namespace Ui {
	class MainWindow;
}

/**
 * Channels index 2 Widget index conversion
 */
static const CvGFilter::Channels RGB[3] = {CvGFilter::RED,
										   CvGFilter::GREEN,
										   CvGFilter::BLUE};

/**
 * OpenCV/Qt Application Main window
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
		 * @param processor the openCV image processor
		 * @param parent parent widget
		 */
		explicit MainWindow(QcvVideoCapture * capture,
							QcvGFilter * processor,
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
		 * The filter processor
		 */
		QcvGFilter * processor;

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
		 * Setup UI values from capture settings
		 */
		void setupUIfromCatpure();

		/**
		 * Setup UI values from processor settings
		 */
		void setupUIfromProcessor();

		/**
		 * Setup Sigma slider and double spinbox according to processor
		 * values
		 */
		void setupSigma();

		/**
		 * Convert value of double spin box to integer slider
		 * @param min minimum value of the double spin box
		 * @param step step value of the double spin box
		 * @param value current value of the double spin box or max value to
		 * obtain integer slider max value
		 * @return the integer value to set on the integer slider
		 */
		static int double2intValue(const double min,
								   const double step,
								   const double value);

		/**
		 * Convert integer value from slider to double value of double spin box
		 * @param dmin the minimum double value of the spin box
		 * @param dstep the step value of the double spin box
		 * @param ivalue the integer value of the integer slider
		 * @return the value of the double spin box
		 */
		static double int2doubleValue(const double dmin,
									  const double dstep,
									  const int ivalue);

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
		 * Kernel size changed in spin box
		 * @param value the new kernel size
		 */
		void on_spinBoxKernel_valueChanged(int value);

		/**
		 * Sigma gaussian variance changed in double spin box
		 * @param dvalue the new sigma value
		 * @post the corresponding integer value is computed and applied
		 * to the integer sigma slider
		 */
		void on_doubleSpinBoxSigma_valueChanged(double dvalue);

		/**
		 * Threshold value changed in Threshold spinbox
		 * @param value the new threshold value
		 */
		void on_spinBoxThreshold_valueChanged(int value);

		/**
		 * Kappa harris parameter changed in double spinbox
		 * @param dvalue the new kappa value
		 * @post the corresponding integer value is computed and applied
		 * to the integer kappa slider
		 */
		void on_doubleSpinBoxKappa_valueChanged(double dvalue);

		/**
		 * Sigma slider value changed
		 * @param ivalue the new Sigma integer value
		 * @post the corresponding double value is computed and applied
		 * to the Sigma double spinbox
		 */
		void on_horizontalSliderSigma_valueChanged(int ivalue);

		/**
		 * Sigma slider value changed
		 * @param ivalue the new Sigma integer value
		 * @post the corresponding double value is computed and applied
		 * to the Sigma double spinbox
		 */
		void on_horizontalSliderKappa_valueChanged(int ivalue);

		/**
		 * Display image selection
		 * @param index the new selected image index
		 */
		void on_comboBoxImages_currentIndexChanged(int index);

		/**
		 * Edge mode selection
		 * @param index the new edge mode index
		 */
		void on_comboBoxEdges_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
