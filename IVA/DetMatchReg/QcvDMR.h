/*
 * QcvDMR.h
 *
 *  Created on: 31 mars 2012
 *	  Author: davidroussel
 */

#ifndef QCVDMR_H_
#define QCVDMR_H_

#include <QMutex>

#include "QcvAlgoParamSets.h"

#include "QcvProcessor.h"
#include "CvDMR.h"

/**
 * Qt oriented Detection / Matching / Registation processor
 * @author David Roussel
 * @date 2012/03/31
 */
class QcvDMR : public QcvProcessor, public CvDMR
{
	Q_OBJECT

	protected:

		/**
		 * the string containing the number of model keypoints
		 */
		QString modelKeypointsNumberString;

		/**
		 * the string containing the number of scene keypoints
		 */
		QString sceneKeypointsNumberString;

		/**
		 * the string containing feature detection time
		 */
		QString detectionTimeString;

		/**
		 * the string containing descriptors extraction time
		 */
		QString extractionTimeString;

		/**
		 * the string containing descriptors matching time
		 */
		QString matchingTimeString;

		/**
		 * the string containing registration time
		 */
		QString registrationTimeString;

		/**
		 * Number of scene keypoints in previous update
		 */
		int previousSceneKeypointsNumber;

		/**
		 * Variation of scene keypoints percentage compared to previous image
		 */
		float scenekeyPointsVariationPercent;

		/**
		 * the string containing the number of matched keypoints
		 */
		QString matchedKeypointsNumberString;

		/**
		 * the string containing the number of inliers keypoints
		 */
		QString inliersKeypointsNumberString;

		/**
		 * the string containing the match mean ± std distance
		 */
		QString meanMatchDistanceString;

		/**
		 * the string containing the match min max distance
		 */
		QString minMaxMatchDistanceString;

		/**
		 * the string containing mean reprojection error
		 */
		QString reprojectionErrorString;

		/**
		 * Self lock to modify self parameters from multiple threads without
		 * compromising the ongoing update.
		 * @note may be NULL if updateThread is also NULL (in ordre to avoid
		 * deadlocks)
		 */
		QMutex * selfLock;

	public:
		/**
		 * QcvDMR Detector / Matcher / Registrar constructor
		 * @param inFrame the source image from video capture [mandatory]
		 * @param modelImageFilename the model image file name [mandatory]
		 * @param cameraFilename the camera parameters file [default value is
		 * empty file name, in which case pose camera would not be computed]
		 * @param featureType the type of feature point to detect in images
		 * @param descriptorType the type of point descriptor to compute
		 * at feature points locations
		 * @param matcherType the kind of matcher touse when matching points
		 * descriptors
		 * @param matchType the kind of match to perform between points
		 * descriptors
		 * @param reprojectionError the maximum acceptable reprojection when
		 * reprojecting model points on scene points when reprojecting with
		 * homography
		 * @param printSize the print scale of the printed model image in order
		 * to convert model image points to model printed points at real scale
		 * @param paramSets Pool of parameters for all algorithms. If an update
		 * thread is available then this pool an all its parameters are moved
		 * to this update thread. This allow to have non blocking parameters
		 * setting from the UI using signals/slots.
		 * @param verboseLevel verbosity level for messages printing
		 * @param imageLock the mutex on source image
		 * @param updateThread the thread in which this processor runs
		 * @param parent parent object
		 * @throw CvProcessorException when
		 * 	- modelImage can't be opened
		 * 	- camera parameters file can't be opened
		 */
		QcvDMR(Mat * inFrame,
			   const string & modelImageFilename,
			   const string & cameraFilename = "",
			   const CvDetector::FeatureType featureType = CvDetector::SURF_FEATURE,
			   const CvDetector::DescriptorExtractorType descriptorType = CvDetector::SURF_DESCRIPTOR,
			   const CvMatcher::MatcherType matcherType = CvMatcher::FLANNBASED_MATCHER,
			   const CvMatcher::MatchType matchType = CvMatcher::KNN_MATCH,
			   const double reprojectionError = 3.0,
			   const double printSize = 0.0,
			   QcvAlgoParamSets * paramSets = NULL,
			   const VerboseLevel verboseLevel = VERBOSE_NONE,
			   QMutex * imageLock = NULL,
			   QThread * updateThread = NULL,
			   QObject * parent = NULL) throw (CvProcessorException);

		/**
		 * QcvDMR destructor
		 */
		virtual ~QcvDMR();

	private:

		/**
		 * Update Scene detector
		 */
		void updateDetector();

		/**
		 * update matcher and extract matched keypoints
		 */
		void updateMatcher();

		/**
		 * Convert matched keypoints to points, update registrar and extract
		 * inliers keypoints
		 */
		void updateRegistrar();

		/**
		 * Draw results in displaySceneImage and evt displayModelImage
		 * @param redrawModelImage model image redraw needed
		 * @return true if displayModelImage has also been updated
		 */
		bool drawResults(const bool redrawModelImage);

	public slots:
		/**
		 * Update computed images and sends displayImageChanged signal if
		 * required
		 */
		void update();

		/**
		 * Changes source image slot.
		 * Attributes needs to be cleaned up then set up again
		 * @param image the new source Image
		 * @throw CvProcessorException#NULL_IMAGE when new source image is NULL
		 * @post Various signals are emitted:
		 * 	- imageChanged(&displaySourceImage)
		 * 	- imageCchanged()
		 * 	- if image size changed then imageSizeChanged() is emitted
		 * 	- if image color space changed then imageColorsChanged() is emitted
		 */
		void setSourceImage(Mat * image) throw (CvProcessorException);

		/**
		 * Read model image from file with notifications
		 * @param filename the model image file name
		 * @post the model image is loaded in modelImage, grayModel and
		 * displayModelImage images are and modelDetector is instanciated with
		 * grayModelImage if it was not created otherwise it is just set to
		 * grayModelImage, and finally descriptors ptr is provided to the
		 * matcher
		 * @throw CvProcessorException when the faile can not be read
		 */
		void updateModelImage(const string & filename)
			throw (CvProcessorException);

		/**
		 * Read camera matrix from file after locking the registrar
		 * @param filename file containing camera matrix
		 * @post cameraMatrix is set in registrar
		 * @throw CvProcessorException when the faile can not be read
		 */
		void setCameraParameters(const string & filename)
			throw (CvProcessorException);

		/**
		 * Sets a new feature type after locking the detectors with message
		 * notification
		 * @param featureType the new feature type to set
		 * @post current Feature detector is released and a new one is created
		 * @throw CvProcessorException if feature detector is empty because it
		 * couldn't be created properly
		 */
		void setFeatureType(const CvDetector::FeatureType featureType)
			throw (CvProcessorException);

		/**
		 * Sets a new descriptor type with message notification after locking
		 * the detectors
		 * @param descriptorType the new descriptor type to set
		 * @param checkMatcher checks if the current matcher is compatible with
		 * the new descriptor type and if not change the current matcher.
		 * @post current Descriptor extractor is released and a new one is created
		 * @throw CvProcessorException if descriptor extractor is empty because it
		 * couldn't be created properly
		 * @note setting a descriptor with binary content such as ORB, BRISK or
		 * BRIEF may involve having to set up a matcher supporting binary
		 * descriptors. Conversely, setting a valued descriptor such as SIFT or
		 * SURF, may imply to change the matcher so it can support valued
		 * descriptors.
		 */
		void setDescriptorExtractorType(const CvDetector::DescriptorExtractorType descriptorType,
							   const bool checkMatcher = true)
			throw (CvProcessorException);

		/**
		 * Set #modelDetectorUpdateNeeded attribute after locking the detectors
		 * to true which should lead to a modelDetector update (which then will
		 * reset it to false
		 * when done)
		 */
		void setModelDetectorUpdate();

		/**
		 * Sets a new matcher type after locking the matcher
		 * @param matcherType the new matcher type to set
		 * @param checkDescriptors check if current descriptors are compatible
		 * with the new matcher and if not change the current descriptors.
		 * @post the old DescriptorMatcher has been released and a new one
		 * has been created
		 * @throw CvProcessorException if matcher is empty because it
		 * couldn't be created properly
		 * @note Setting a new matcher type may involve to change the current
		 * descriptors if the content of the current descriptors is not
		 * supported by the new matcher.
		 */
		void setMatcherType(const CvMatcher::MatcherType matcherType,
							const bool checkDescriptors = true)
			throw (CvProcessorException);

		/**
		 * Sets a new matcher mode after locking the matcher
		 * @param matcherMode the new matcher mode to set
		 */
		void setMatcherMode(const CvMatcher::MatchType matcherMode);

		/**
		 * Sets a new number of best matches to search for each descriptor
		 * when using knnMatch after locking the matcher
		 * @param knn the new number of best matches to search for each
		 * descriptor
		 */
		void setKnn(const int knn);

		/**
		 * Sets a new radius Threshold to search for each descriptor when using
		 * radiusMatch after locking the matcher
		 * @param radiusThreshold the new radius threshold to set.
		 * @post if the new threshold is contained within the bounds
		 * [radiusThresholdMin..radiusThresholdMax] the new threshold is set,
		 * otherwise min or max are set depending on the saturation side
		 */
		void setRadiusThreshold(const double radiusThreshold);

		/**
		 * Set a new reprojection error threshold to sort inliers from
		 * outliers after locking the registrar
		 * @param reprojThreshold the new reprojection error threshold
		 */
		void setReprojThreshold(const double reprojThreshold);

//		/**
//		 * Set a new printscale for converting model image points to real space
//		 * points after locking the registrar
//		 * @param printScale the new printscale
//		 * @return true if printScale have been set and all camera parameters
//		 * and printscale are correct (acccording to isCameraSet)
//		 */
//		bool setPrintScale(const double printScale);

		/**
		 * Set a new mode print size and modifies print scale after locking the
		 * registrar
		 * @param printSize the new print size of the image model
		 * @return true if printScale have been set and all camera parameters
		 * and printscale are correct (acccording to isCameraSet)
		 */
		bool setPrintSize(const double printSize);

		/**
		 * Set a new camera pose computing status after locking the registrar
		 * @param computePose the new camera pose computing status
		 * @return if computePose is set to be true isCameraSet is called first
		 * to check all camera parameters and printScale are set correctly
		 * So the result might not be equal to computePose if all camera
		 * parameters are not set porperly
		 */
		bool setComputePose(const bool computePose);

		/**
		 * Set a new "use previous pose" status in pose computing after locking
		 * the registrar
		 * @param use the new "use previous pose" status
		 */
		void setUsePreviousPose(const bool use);

		/**
		 * Sets a new feature points detecting status after locking the
		 * detectors
		 * @param detecting the new feature points detecting status
		 */
		void setDetecting(const bool detecting);

		/**
		 * Sets a new feature points matching status after locking the matcher
		 * @param matching the new feature points matching status
		 * @return true if matching is set or false is matching is unset or
		 * if matching can not be set because model image is not ready
		 * or detecting is off
		 * @note detecting should be on in order to turn matching on
		 */
		bool setMatching(const bool matching);

		/**
		 * Sets a new feature points registering status after locking the
		 * registrar
		 * @param registering the new feature points registering status
		 * @return true if registering is set or false if registering is unset
		 * or if matching is off
		 * @note matching should be on in order to turn registering on
		 */
		bool setRegistering(const bool registering);

		/**
		 * Set new verbose level after selflocking
		 * @param level the new verobse level
		 */
		void setVerboseLevel(const VerboseLevel level);

		/**
		 * Sets a new keypoints drawing mode after self locking
		 * @param mode the new keypoints drawing mode
		 */
		void setKeyPointsMode(const KeyPointShow mode);

		/**
		 * Sets a new drawing status for model box in scene image after self
		 * locking
		 * @param showModelFrame the new drawing status for model box in scene
		 * image
		 * @return true if show model box is set, false if it is unset or
		 * if it can't be set because registering is off
		 */
		bool setShowModelFrame(const bool showModelFrame);

		/**
		 * Sets a new drawing status for model frame in scene image after self
		 * locking
		 * @param showModelBox the new drawing status for model frame in scene
		 * image
		 * @return true if show model Frame is set, false if it is unset or
		 * if show model box could not be stated because registering is off
		 */
		bool setShowModelBox(const bool showModelBox);

		/**
		 * Sets a new model image box height in scene image after self locking
		 * @param height the new model image box height (in mm)
		 * @post the last 4 points of modelBoxPoints3D had their last (Z)
		 * coodinates changed to -height.
		 */
		void setBoxHeight(const double height);

		/**
		 * Sets Time per feature processing time unit slot after self locking
		 * @param value the time per feature value (true or false)
		 */
		void setTimePerFeature(const bool value);

		/**
		 * Reset mean and std process times in order to re-start computing
		 * new mean and std process time values.
		 */
		void resetMeanProcessTime();

	signals:
		/**
		 * Signal emitted when model image is updated
		 */
		void modelUpdated();

		/**
		 * Signal emitted when model image is reallocated
		 * @param image the new model image pointer or none if just
		 * image changed notification is required
		 */
		void modelImageChanged(Mat * image);

		/**
		 * Update String showing model keypoints number
		 * @param numberString the string containing the number of model
		 * keypoints
		 */
		void updateModelKeypointsNumberString(const QString & numberString);

		/**
		 * Update String showing scene keypoints number
		 * @param numberString the string containing the number of scene
		 * keypoints
		 */
		void updateSceneKeypointsNumberString(const QString & numberString);

		/**
		 * update String showing mean feature points detection time
		 * @param numberString the string containing the mean detection time
		 */
		void updateDetectionTimeString(const QString & numberString);

		/**
		 * update String showing mean descriptors extraction time
		 * @param numberString the string containing the mean extraction time
		 */
		void updateExtractionTimeString(const QString & numberString);

		/**
		 * update String showing descriptors matching time
		 * @param numberString the string containing the mean matching time
		 */
		void updateMatchingTimeString(const QString & numberString);

		/**
		 * update String showing mean registration time
		 * @param numberString the string containing the mean registration time
		 */
		void updateRegistrationTimeString(const QString & numberString);

		/**
		 * Update String showing matched keypoints number
		 * @param numberString the string containing the number of matched
		 * keypoints
		 */
		void updateMatchedPointsNumberString(const QString & numberString);

		/**
		 * Update String showing the match mean distance
		 * @param numberString the string containing the match mean distance
		 */
		void updateMeanMatchDistanceString(const QString & numberString);

		/**
		 * Update String showing the match min distance
		 * @param numberString the string containing the match min distance
		 */
		void updateMinMaxMatchDistanceString(const QString & numberString);

		/**
		 * Update String showing the match max distance
		 * @param numberString the string containing the match max distance
		 */
		void updateMaxMatchDistanceString(const QString & numberString);

		/**
		 * Update String showing the match standard deviation distance
		 * @param numberString the string containing the match max distance
		 */
		void updateStdMatchDistanceString(const QString & numberString);

		/**
		 * Update String showing the mean reprojection error
		 * @param numberString the string containing mean reprojection error
		 */
		void updateReprojectionErrorString(const QString & numberString);

		/**
		 * Update String showing inliers keypoints number
		 * @param numberString the string containing the number of inliers
		 * keypoints
		 */
		void updateInliersNumberString(const QString & numberString);

};

#endif /* QCVDMR_H_ */
