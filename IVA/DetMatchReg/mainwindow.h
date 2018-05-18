#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QString>
#include <QPixmap>
#include <QWindow>

#include "QcvVideoCapture.h"
#include "QcvDMR.h"

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
	RENDER_GL		//!< OpenGL in a QGLWidget rendering mode
} RenderMode;

/**
 * OpenCV/Qt capture input main window
 * @author David Roussel
 * @date 2012/02
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
							QcvDMR * processor,
							QWidget *parent = NULL);

		/**
		 * MainWindow destructor
		 */
		virtual ~MainWindow();

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
		 * The Vision processor to:
		 * 	- extract keypoints from model(image) and scene(camera)
		 * 	- match these keypoints
		 * 	- according to matched keypoints
		 * 		- compute homography between 3D model points and 2D scene points
		 * 		- according to this homography
		 * 			- compute inliers keypoints (those which are correctly
		 * 			reprojected on the scene points)
		 * 			- according to inliers points
		 * 				- compute camera pose in the scene
		 *
		 */
		QcvDMR * processor;

		/**
		 * Image preferred width
		 */
		int preferredWidth;

		/**
		 * Image preferred height
		 */
		int preferredHeight;

		/**
		 * Images rendering mode (Pixmap, Image or OpenGL)
		 */
		RenderMode renderMode;

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
		 */
		void setupImageWidgets();

		/**
		 * Setup UI according to capture settings when app launches
		 */
		void setupUIfromCapture();

		/**
		 * Setup UI according to processor settings when app launches
		 */
		void setupUIfromProcessor();

		/**
		 * Setup UI possible matchers according to processor's current
		 * descriptor extractor
		 */
		void setupUIPossibleMatchers();

		/**
		 * Clears all widgets from ui->detectorParamBox or
		 * ui->extractorParamBox
		 */
		void cleanUpWidgets(QWidget * parent);

		/**
		 * Setup control widgets
		 * @param parent Parent widget (ui->detectorParamBox or
		 * ui->extractorParamBox)
		 * @param paramSet the parameter set to represent by widgets
		 * @param algorithm the algorithm represented by this parameter set
		 * (the algorithm is supposed to be already associated with the
		 * parameters in the set and is only used to list the parameters in
		 * the algorithm's favorite order)
		 */
		void setupParametersWidgets(QGroupBox * parent,
									CvAlgoParamSet * paramSet,
									const Ptr<Feature2D> & algorithm);

	private slots:

		/**
		 * Setup processor from current UI settings when processor source image
		 * changes
		 */
		void setupProcessorfromUI();

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
		 * Menu action when Source->Model image is selected.
		 * Opens file dialog and tries to open selected file (is not empty),
		 * then loads a model image
		 */
		void on_actionModel_triggered();

		/**
		 * Menu action when Source->Camera paeameters is selected.
		 * Opens file dialog and tries to open selected file (is not empty),
		 * then loads the camera parameters (cameraMatrix & distortionCoefs)
		 * and if all parameters for pose computation are set, checks the
		 * camera parameters checkbox.
		 */
		void on_actionCalibData_triggered();

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
		 * Sets capture to convert source image to gray
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
		 * Convert capture image to gray
		 */
		void on_checkBoxGray_clicked();

		/**
		 * Check/Uncheck the detector group box which also triggers the
		 * Feature points detectors
		 * @param checked status
		 */
		void on_groupBoxDetector_clicked(bool checked);

		/**
		 * Check/Uncheck the matcher group box which also triggers the matcher
		 * @param checked status
		 */
		void on_groupBoxMatcher_clicked(bool checked);

		/**
		 * Check/Uncheck the registrar group box which also triggers the
		 * regisrtar
		 * @param checked status
		 */
		void on_groupBoxRegistrar_clicked(bool checked);

		/**
		 * Select the Feature points to detect on images
		 * @param index the selected mode
		 */
		void on_comboBoxFeatures_currentIndexChanged(int index);

		/**
		 * Select the descriptors to compute on detected keypoints
		 * @param index the selected mode
		 */
		void on_comboBoxDescriptors_currentIndexChanged(int index);

		/**
		 * Select the keypoints to show (none, all, matched, inliers)
		 * @param index the selected mode
		 */
		void on_comboBoxShowKPts_currentIndexChanged(int index);

		/**
		 * Select the matcher type
		 * @param index the selected mode
		 */
		void on_comboBoxMatcherType_currentIndexChanged(int index);

		/**
		 * Select the matcher mode
		 * @param index the selected mode
		 */
		void on_comboBoxMatcherMode_currentIndexChanged(int index);

		/**
		 * Set the Knn number of Flann Based matcher
		 * @param value the Knn number
		 */
		void on_spinBoxKnn_valueChanged(int value);

		/**
		 * Set the radius threshold of radius match
		 * @param value the radius value
		 */
		void on_doubleSpinBoxRadius_valueChanged(double value);

		/**
		 * Set the model image print size.
		 * @param value the new print size
		 */
		void on_doubleSpinBoxPrintSize_valueChanged(double value);

		/**
		 * Set the reprojection threshold for inliers
		 * @param value the new reprojection threshold
		 */
		void on_doubleSpinBoxReprojThres_valueChanged(double value);

		/**
		 * Show / hide the model image frame in the scene image
		 * @param checked the show frame status
		 */
		void on_checkBoxShowFrame_clicked(bool checked);

		/**
		 * Show / hide the model image box in the scene image
		 * @param checked the dhow box status
		 */
		void on_checkBoxShowModelBox_clicked(bool checked);

		/**
		 * Set the use of the previous pose to compute the next pose
		 * @param checked the status of the use previous pose
		 */
		void on_checkBoxUsePreviousPose_clicked(bool checked);

		/**
		 * Set processing time display (absolute or per feature time)
		 * @param index 0 means absolute time, other means per feature time
		 */
		void on_comboBoxTimeUnit_currentIndexChanged(int index);

	public slots:

	signals:
		/**
		 * Signal to send update message when something changes
		 * @param message the message
		 * @param timeout number of ms the message should be displayed
		 */
		void sendMessage(const QString & message, int timeout = 0);

		// ---------------------------------------------------------------------
		// Signals for capture
		// ---------------------------------------------------------------------
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

		// ---------------------------------------------------------------------
		// Signals for processor
		// ---------------------------------------------------------------------

		/**
		 * Signal sent to the processor to change the time/feature timing state
		 * @param state the new time/feature timing state
		 * @note this signal should be emitted after locking the processor
		 * itself in order to ensure no timing operation is performed when this
		 * change occurs.
		 * @note this signal should be preferred over
		 * processor->setTimePerFeature direct call
		 */
		void timePerFeatureStateChanged(const bool state);

		/**
		 * Signal send to processor to change detecting state.
		 * @param state the new detecting state
		 * @note this signal should be emitted after locking detectors in order
		 * to ensure detectors are not updating when this
		 * change occurs.
		 * @note this signal should be preferred over processor->setDetecting
		 * direct call
		 */
		void detectingStateChanged(const bool state);

		/**
		 * Signal send to processor to change feature type.
		 * @param type the new feature type
		 * @note this signal should be emitted after locking detectors in order
		 * to ensure detectors are not detecting new feature points when this
		 * change occurs.
		 * @note this signal should be preferred over processor->setFeatureType
		 * direct call
		 */
		void featureTypeChanged(const CvDetector::FeatureType type);

		/**
		 * Signal send to processor to change descriptor type.
		 * @param type the new descriptor type
		 * @param checkMatcher checks if the current matcher is compatible with
		 * the new descriptor type and if not change the current matcher.
		 * @note this signal should be emitted after locking detectors in order
		 * to ensure detectors are not computing descriptors when this
		 * change occurs.
		 * @note this signal should be preferred over processor->setDescriptorType
		 * direct call
		 */
		void descriptorTypeChanged(const CvDetector::DescriptorExtractorType type,
								   const bool checkMatcher);

		/**
		 * Signal sent to the processor to change matching state
		 * @param state the new matching state
		 * @note this signal should be emitted after locking matcher in order
		 * to ensure matcher is not matching when this change occurs.
		 * @note this signal should be preferred over processor->setMatching
		 * direct call
		 */
		void matchingStateChanged(const bool state);

		/**
		 * Signal send to processor to change matcher type.
		 * @param type the new descriptor type
		 * @param checkDescriptors check if current descriptors are compatible
		 * with the new matcher and if not change the current descriptors.
		 * @note this signal should be emitted after locking matcher in order
		 * to ensure matcher is not matching when this change occurs.
		 * @note this signal should be preferred over processor->setMatcherType
		 * direct call
		 */
		void matcherTypeChanged(const CvMatcher::MatcherType type,
								const bool checkDescriptors);

		/**
		 * Signal send to processor to change matcher type.
		 * @param mode the new matching mode
		 * @note this signal should be emitted after locking matcher in order
		 * to ensure matcher is not matching when this change occurs.
		 * @note this signal should be emitted after locking matcher in order
		 * to ensure matcher is not matching when this change occurs.
		 */
		void matcherModeChanged(const CvMatcher::MatchType mode);

		/**
		 * Signal sent to the processor to change the number of candidates in
		 * cross best match.
		 * @param value the new candidates number
		 * @note this signal should be emitted after locking matcher in order
		 * to ensure matcher is not matching when this change occurs.
		 * @note this signal should be preferred over processor->setKnn direct
		 * call
		 */
		void knnChanged(const int value);

		/**
		 * Signal sent to the processor to change the radius threshold in radius
		 * match
		 * @param value the radius threshold
		 * @note this signal should be emitted after locking matcher in order
		 * to ensure matcher is not matching when this change occurs.
		 * @note this signal should be preferred over
		 * processor->setRadiusThreshold direct call
		 */
		void radiusThresholdChanged(const double value);

		/**
		 * Signal sent to the processor to change the registering state.
		 * @param state the new registering state
		 * @note this signal should be emitted after locking registrar in order
		 * to ensure registrar is not registering when this change occurs.
		 * @note this signal shopuld be preferred over processor->setRegistering
		 * direct call
		 */
		void registeringStateChanged(const bool state);

		/**
		 * Signal sent to the processor to change the pose computing state.
		 * @param state the new pose computing state
		 * @note this signal should be emitted after locking registrar in order
		 * to ensure registrar is not registering when this change occurs.
		 * @note this signal should be preferred over
		 * processor->setComputePose direct call
		 */
		void poseComputingStateChanged(const bool state);

		/**
		 * Signal sent to the processor to change the target print size.
		 * @param value the new print size value
		 * @note this signal should be emitted after locking registrar in order
		 * to ensure registrar is not registering when this change occurs.
		 * @note this signal shopuld be preferred over processor->setPrintSize
		 * direct call
		 */
		void printSizeChanged(const double value);

		/**
		 * Signal sent to the processor to change the reprojection threshold.
		 * @param value the new reprojection threshold
		 * @note this signal should be emitted after locking registrar in order
		 * to ensure registrar is not registering when this change occurs.
		 * @note this signal shopuld be preferred over
		 * processor->setReprojThreshold direct call
		 */
		void reprojThresholdChanged(const double value);

		/**
		 * Signal sent to the processor to change the show frame state.
		 * @param state the new show model frame state
		 * @note this signal should be emitted after locking registrar in order
		 * to ensure registrar is not registering when this change occurs.
		 * @note this signal shopuld be preferred over
		 * processor->setShowModelFrame direct call
		 */
		void showModelFrameChanged(const bool state);

		/**
		 * Signal sent to the processor to change the show box state.
		 * @param state the new show model box state
		 * @note this signal should be emitted after locking registrar in order
		 * to ensure registrar is not registering when this change occurs.
		 * @note this signal shopuld be preferred over
		 * processor->setShowModelBox direct call
		 */
		void showModelBoxChanged(const bool state);

		/**
		 * Signal sent to the processor to change the previous pose used state.
		 * @param state the new previous pose used state
		 * @note this signal should be emitted after locking registrar in order
		 * to ensure registrar is not registering when this change occurs.
		 * @note this signal shopuld be preferred over
		 * processor->setUsePreviousPose direct call
		 */
		void usePreviousPoseStateChanged(const bool state);


		/**
		 * Signal sent to the processor to change the camera configuration file.
		 * @param state the new camera configuration file
		 * @note this signal should be emitted after locking registrar in order
		 * to ensure registrar is not registering when this change occurs.
		 * @note this signal shopuld be preferred over
		 * processor->setCameraParameters direct call
		 */
		void cameraParametersChanged(const QString & filename);
};

#endif // MAINWINDOW_H
