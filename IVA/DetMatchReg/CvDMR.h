/*
 * CvDMR.h
 *
 *  Created on: 28 mars 2012
 *	  Author: davidroussel
 */

#ifndef CVDMR_H_
#define CVDMR_H_

#include "CvProcessor.h"

#include "CvDetector.h"
#include "CvMatcher.h"
#include "CvRegistrar.h"

#include "CvAlgoParamSets.h"
#include "CvAlgoParamSet.h"

/**
 * Drawing Mode for Keypoints
 */
typedef enum
{
	NO_POINTS = 0, //!< NO_POINTS: no points are displayed
	ALL_POINTS, //!< ALL_POINTS: All keypoints
	MATCHED_POINTS, //!< MATCHED_POINTS : only matched keypoints
	INLIERS_POINTS, //!< INLIERS_POINTS : only matched keypoints which are not outliers
	POINTMODES_NUMBER //!< Number of drawing modes
} KeyPointShow;

/**
 * OpenCV Detector / Matcher / Registrar.
 * The Goal is to extract feature points from a model image and find these very
 * same points in a video stream where a printed model image may appear.
 * Onces points are matched between the model image and the "scene" image from
 * the video stream, several operations can be performed.
 * DMR consists in 3 linked elements:
 * 	- Detector detects feature points in a model image and in the
 * 	current video stream (the scene image).
 * 		- Then descriptors are computed on every feature points
 * 	- Once descriptors are computed, they are matched by the matcher in order
 * 	to create a set of matched feature points between the model image and the
 * 	current scene image
 * 	- Then matched points are the supplied to the Registrar which will
 * 	try to compute the homography between matched scene points and matched model
 * 	points. Once homography is computed the model points are reprojected on
 * 	the scene points using the computed homography to eliminate outliers that
 * 	are reprojected too far away from the scene points. The remaining matches
 * 	are then called inliers and are used to compute the camera pose (rotation
 * 	and translation) with the help of printed model scale and camera parameters
 * 	(intrinsic parameters and distortion coefficients) obtained from
 * 	a calibration procedure.
 * @author David Roussel
 * @date 2012/03/28
 */
class CvDMR: virtual public CvProcessor
{
	public:
		/**
		 * Index to processing time
		 */
		typedef enum
		{
			ALL = 0, ///!< All processing
			DETECTION, ///!< sceneDetector feature points detection
			EXTRACTION, ///!< sceneDetector descriptors extraction
			MATCHING, ///!< matcher matching time
			REGISTRATION ///!< registrar registration time
		} ProcessTimeIndex;

	protected:
		// --------------------------------------------------------------------
		// Additionnal images
		// --------------------------------------------------------------------
		// Source image inherited from CvProcessor contains scene image

		/**
		 * Indicates if source / scene image is grayscale
		 */
		bool graySource;

		/**
		 * Color source image in witch we could draw colored keypoints.
		 * Contains either gray or color source image.
		 */
		Mat displaySourceImage;

		/**
		 * Model image (gray or color)
		 */
		Mat modelImage;

		/**
		 * size (width) in mm of the printed model.
		 * Used to compute scale between model image pixels and
		 * printed model mm in the scene
		 */
		double modelPrintSize;

		/**
		 * Indicates if model image is grayscale
		 */
		bool grayModel;

		/**
		 * Color model image in witch we could draw colored keypoints.
		 * Contains either gray or color source image.
		 */
		Mat displayModelImage;

		/**
		 * Indicates if model image have been loaded.
		 * If not, matching and registration can't be performed
		 */
		bool modelImageReady;

		/**
		 * Indicates that model image has changed and needs to be redrawn.
		 */
		bool updatedModelImage;

		// --------------------------------------------------------------------
		// Detection attributes
		// --------------------------------------------------------------------
		/**
		 * Model image feature point detector
		 */
		CvDetector *modelDetector;

		/**
		 * Scene image feature point detector
		 */
		CvDetector *sceneDetector;

		/**
		 * Matched model Keypoints extracted from modelDetector (if needed)
		 */
		vector<KeyPoint> matchedModelKeypoints;

		/**
		 * Matched scene Keypoints extracted from sceneDetector (if needed)
		 */
		vector<KeyPoint> matchedSceneKeypoints;

		/**
		 * Inliers model Keypoints extracted from modelDetector (if needed)
		 */
		vector<KeyPoint> inliersModelKeyPoints;

		/**
		 * Inliers scene Keypoints extracted from sceneDetector (if needed)
		 */
		vector<KeyPoint> inliersSceneKeyPoints;

		/**
		 * Algorithm parameters pool for all algorithms (detectors and
		 * extractors)
		 */
		CvAlgoParamSets * paramSets;

		/**
		 * Algorithm parameters set for the feature points detectors
		 * (the modelDetector and the sceneDetector)
		 */
		CvAlgoParamSet * detectorsParamSet;

		/**
		 * Algorithm parameters set for the feature points detectors
		 * (the modelDetector and the sceneDetector)
		 */
		CvAlgoParamSet * extractorsParamSet;

		/**
		 * Indicate the model detector needs an update when:
		 *	- model image changes
		 *	- feature point type changes
		 *	- descriptor type changes
		 *	- parameters of feature points detectors or descriptors extractors
		 *	changes
		 * This attribute might be set to true in
		 *	- #updateModelImage
		 *	- #setFeatureType
		 *	- #setDescriptorType
		 *	- #setDetecting
		 *	- #setModelDetectorUpdate
		 * And is set to false in
		 *	- #updateDetector
		 */
		bool modelDetectorUpdate;

		// --------------------------------------------------------------------
		// Matching attributes
		// --------------------------------------------------------------------
		/**
		 * Feature points descriptors matcher
		 */
		CvMatcher *matcher;

		// --------------------------------------------------------------------
		// Registration attributes
		// --------------------------------------------------------------------
		/**
		 * Camera calibration matrix
		 */
		Mat cameraMatrix;

		/**
		 * Camera distortion coefficients
		 */
		Mat distortionCoefs;

		/**
		 * Model matched points.
		 * Obtained from converting modelDetector matched KeyPoints to points
		 */
		vector<Point2f> modelMatchedPoints;

		/**
		 * Scene matched points.
		 * Obtained from converting sceneDetector matched KeyPoints to points
		 */
		vector<Point2f> sceneMatchePoints;

		/**
		 * Points registrar
		 */
		CvRegistrar *registrar;

		// --------------------------------------------------------------------
		// Processing attibutes
		// --------------------------------------------------------------------
		/**
		 * Indicates detection status.
		 * Feature points are detected in model an scene image
		 */
		bool detecting;

		/**
		 * Indicates matching status.
		 * Feature points between model and scene are matched
		 */
		bool matching;

		/**
		 * Indicates registration status.
		 * Matched points between model and scene are registered
		 * in order to find inliers and evt find camera pose in order
		 * to project model frame or box on the scene
		 */
		bool registering;

		// --------------------------------------------------------------------
		// Display results attributes
		// --------------------------------------------------------------------
		/**
		 * Keypoints to show in model and scene images
		 *  - None
		 * 	- All keypoints
		 * 	- Only matched keypoints
		 * 	- Only matched inliers keypoints
		 * @see KeyPointShow
		 */
		KeyPointShow keyPointsMode;

		/**
		 * previous Keypoints drawing mode used during last update.
		 * Used to refresh model display image if needed.
		 */
		KeyPointShow previousKeyPointsMode;

		/**
		 * Shows/hides model frame in scene image if homography is available
		 */
		bool showModelFrame;

		/**
		 * Model points representing image frame corners.
		 * model frame points can be reprojected on scene image
		 * when homography is computed
		 */
		vector<Point2f> modelFramePoints2D;

		/**
		 * Model frame points reprojected on scene image
		 */
		vector<Point2f> modelFramePointsReprojected2D;

		/**
		 * Shows/hides model box if camera pose is available
		 */
		bool showModelBox;

		/**
		 * Height (in mm) of the box to draw on top of image model in
		 * scene image when reprojecting 3D box points
		 */
		double boxHeight;

		/**
		 * Model points representing a box on the model image
		 */
		vector<Point3f> modelBoxPoints3D;

		/**
		 * Model box points reprojected on scene image using camera
		 * intrinsic parameters (projection rules) and estimated extrinsic
		 * parameters (pose).
		 */
		vector<Point2f> modelBoxPointsReprojected2D;

		/**
		 * Color to use when drawing feature points
		 */
		static const Scalar PointsColor;

		/**
		 * Color to use when drawing matched points
		 */
		static const Scalar MatchedPointsColor;

		/**
		 * Color to use when drawing matched inliers points
		 */
		static const Scalar InliersPointsColor;

		/**
		 * Color to use when drawing model image frame on scene image
		 */
		static const Scalar FrameColor;

		/**
		 * Color to use when drawing model image box on scene image using
		 * current pose : Light Blue
		 */
		static const Scalar BoxColorCurrent;

		// --------------------------------------------------------------------
		// Utility methods
		// --------------------------------------------------------------------
		/**
		 * Setup attributes when source image is changed
		 * @param image source Image
		 * @param completeSetup is true when used to change source image,
		 * and false when used in constructor
		 */
		virtual void setup(Mat *image, const bool completeSetup);

		/**
		 * Cleanup attributes before changing source image or cleaning class
		 * before destruction
		 */
		virtual void cleanup();

	public:

		/**
		 * Cv Detector / Matcher / Registrar constructor
		 * @param sourceImage the source image from video capture [mandatory]
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
		 * @param paramSets Pool of parameters for all algorithms
		 * @param verboseLevel verbosity level for messages printing
		 * @throw CvProcessorException when
		 * 	- modelImage can't be opened
		 * 	- camera parameters file can't be opened
		 * 	- when detectors can't be created
		 */
		CvDMR(Mat *sourceImage,
			  const string & modelImageFilename,
			  const string & cameraFilename = "",
			  const CvDetector::FeatureType featureType = CvDetector::SURF_FEATURE,
			  const CvDetector::DescriptorExtractorType descriptorType = CvDetector::SURF_DESCRIPTOR,
			  const CvMatcher::MatcherType matcherType = CvMatcher::FLANNBASED_MATCHER,
			  const CvMatcher::MatchType matchType = CvMatcher::KNN_MATCH,
			  const double reprojectionError = 3.0,
			  const double printSize = 0.0,
			  CvAlgoParamSets * paramSets = NULL,
			  const VerboseLevel verboseLevel = VERBOSE_NONE)
			throw (CvProcessorException);

		/**
		 * CvDMR destructor
		 */
		virtual ~CvDMR();

		/**
		 * Gets the display image for model image
		 * @return the display image for model image
		 */
		const Mat & getDisplayModelImage() const;

		/**
		 * Gets the display image pointer for model image
		 * @return the display image pointer for model image
		 */
		Mat * getDisplayModelImagePtr();

		/**
		 * Gets the display image for scene image
		 * @return the display image for scene image
		 */
		const Mat & getDisplaySourceImage() const;

		/**
		 * Gets the display image pointer for scene image
		 * @return the display image pointer for scene image
		 */
		Mat * getDisplaySourceImagePtr();

		/**
		 * CvDMR update
		 * 	- compute feature points in scene image (feature points in model
		 * 		image have been computed in setModelImage)
		 * 	- compute matching between scene descriptors and model descriptors
		 * 	- estimate homography between model image matched points and scene
		 * 		image matched points
		 * 	- reproject matched model points in scen image with homography and
		 * 		reject the points reprojecting far away from matched scene
		 * 		points to keep only inliers
		 * 	- compute camera pose between 2D scene points and 3D model points
		 * 		scaled to printed model
		 * 	- draws feature points (all | matched | inliers)
		 * 	- draws model image frame in scene image if homography is available
		 * 	- draws model image frame box scene image if camera pose
		 * 		is available
		 */
		virtual void update();

		/**
		 * Read model image from file, setup detector and update it
		 * @param filename the model image file name
		 * @post the model image is loaded in modelImage, grayModel and
		 * displayModelImage images are created and modelDetector is
		 * instanciated with grayModelImage if it was not created otherwise
		 * it is just set to grayModelImage, then modelDetector is updated and
		 * finally descriptors ptr is provided to the matcher
		 * @throw CvProcessorException when the file can not be read
		 */
		virtual void updateModelImage(const string & filename)
			throw (CvProcessorException);

		/**
		 * Gets the current modelImageReady state
		 * @return true if model image is loaded and ready, false otherwise
		 */
		bool isModelImageready() const;

		/**
		 * Read camera matrix from file
		 * @param filename file containing camera matrix
		 * @post cameraMatrix is set in registrar
		 * \f[
		 * \left(
		 * \begin{array}{ccc}
		 * 	f_x & 0 & c_x \\
		 * 	0 & f_y & c_y \\
		 *	0 & 0 & 1
		 * \end{array}
		 * \right)
		 * \f]
		 * @post distortionCoefs is set in registrar
		 * \f[
		 * \left(
		 * \begin{array}{ccccc}
		 * 	k_1 & k_2 & p_1 & p_2 & k_3
		 * \end{array}
		 * \right)
		 * \f]
		 * @throw CvProcessorException when the faile can not be read
		 */
		virtual void setCameraParameters(const string & filename)
			throw (CvProcessorException);

		// --------------------------------------------------------------------
		// Detectors methods
		// --------------------------------------------------------------------
		/**
		 * Gets the current feature type
		 * @return the current feature type
		 */
		CvDetector::FeatureType getFeatureType() const;

		/**
		 * Sets a new feature type
		 * @param featureType the new feature type to set
		 * @post current Feature detector is released and a new one is created
		 * @throw CvProcessorException if feature detector is empty because it
		 * couldn't be created properly
		 */
		virtual void setFeatureType(const CvDetector::FeatureType featureType)
			throw (CvProcessorException);

		/**
		 * Gets the current descriptor type
		 * @return the current descriptor type
		 */
		CvDetector::DescriptorExtractorType getDescriptorExtractorType() const;

		/**
		 * Sets a new descriptor type
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
		virtual void setDescriptorExtractorType(const CvDetector::DescriptorExtractorType descriptorType,
									   const bool checkMatcher = true)
			throw (CvProcessorException);

		/**
		 * Gets the descriptor type used bye the descriptor extractor, should be
		 *	- DescriptorTypes::BINARY_DESCRIPTOR (0) for binary descriptors
		 *	- DescriptorTypes::VALUED_DESCRIPTOR (5) for valued descriptors
		 * @return the descriptor type used by the descriptor extractor or -1
		 * if there is no descriptor extractor
		 */
		int getDescriptorType() const;

		/**
		 * Get the current detectors parameters set (detectors algorithms
		 * have already been associated with each parameter).
		 * @return a pointer to the detectors parameters set
		 */
		CvAlgoParamSet * getDetectorsParamSet() const;

		/**
		 * Get the current extractors parameters set (extractors algorithms
		 * have already been associated with each parameter).
		 * @return a pointer to the extractors parameters set
		 */
		CvAlgoParamSet * getExtractorsParamSet() const;

		/**
		 * Get Feature detector algorithm (featureDetector)
		 * @return a smart pointer to the featureDetector
		 * @note don't forget to release this pointer when you're done in order
		 * for this smart pointer to automatically destroye its content
		 */
		Ptr<Feature2D> getDetectorsAlgorithm() const;

		/**
		 * Get Descriptor extractor algorithm (descriptorExtractor)
		 * @return a smart pointer to the descriptorExtractor
		 * @note don't forget to release this pointer when you're done in order
		 * for this smart pointer to automatically destroye its content
		 */
		Ptr<Feature2D> getExtractorsAlgorithm() const;

		/**
		 * Access to #modelDetectorUpdate attribute
		 * @return the #modelDetectorUpdate attribute
		 */
		bool isModelDetectorUpdate() const;

		/**
		 * Set #modelDetectorUpdate attribute to true which should
		 * lead to a modelDetector update (which then will reset it to false
		 * when done)
		 */
		virtual void setModelDetectorUpdate();

		// --------------------------------------------------------------------
		// Matcher methods
		// --------------------------------------------------------------------
		/**
		 * Gets the current Matcher type
		 * @return the current Matcher type
		 */
		CvMatcher::MatcherType getMatcherType() const;

		/**
		 * Sets a new matcher type
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
		virtual void setMatcherType(const CvMatcher::MatcherType matcherType,
									const bool checkDescriptors = true)
			throw (CvProcessorException);

		/**
		 * Gets the current match mode
		 * @return the current match mode
		 */
		CvMatcher::MatchType getMatcherMode() const;

		/**
		 * Sets a new matcher mode
		 * @param matcherMode the new matcher mode to set
		 */
		virtual void setMatcherMode(const CvMatcher::MatchType matcherMode);

		/**
		 * Indicates if the current matcher can match binary descriptors
		 * @return true if the current matcher can match binary descriptors
		 * and false otherwiser
		 */
		bool matchBinary() const;

		/**
		 * Indicates if the current matcher can match valued descriptors
		 * @return true if the current matcher can match valued descriptors
		 * and false otherwise
		 */
		bool matchFloat() const;

		/**
		 * Gets the number of matches
		 * @return the current number of matches
		 */
		int getNbMatches() const;

		/**
		 * Gets the minimum match distance
		 * @return the minimum match distance
		 */
		double getMinMatchError() const;

		/**
		 * Gets the maximum match distance
		 * @return the maximum match distance
		 */
		double getMaxMatchError() const;

		/**
		 * Gets the mean match distance
		 * @return the mean match distance
		 */
		double getMeanMatchError() const;

		/**
		 * Gets the current number of best matches to search for each descriptor
		 * when using knnMatch
		 * @return the current number of best matches to search for each
		 * descriptor
		 */
		int getKnn() const;

		/**
		 * Sets a new number of best matches to search for each descriptor
		 * when using knnMatch
		 * @param knn the new number of best matches to search for each
		 * descriptor
		 */
		virtual void setKnn(const int knn);

		/**
		 * Gets the current radius threshold to search for each descriptor when
		 * using radiusMatch
		 * @return the current radius thresold to search for each descriptor
		 */
		double getRadiusThreshold() const;

		/**
		 * Sets a new radius Threshold to search for each descriptor when using
		 * radiusMatch
		 * @param radiusThreshold the new radius threshold to set.
		 * @post if the new threshold is contained within the bounds
		 * [radiusThresholdMin..radiusThresholdMax] the new threshold is set,
		 * otherwise min or max are set depending on the saturation side
		 */
		virtual void setRadiusThreshold(const double radiusThreshold);

		// --------------------------------------------------------------------
		// Registrar methods
		// --------------------------------------------------------------------
		/**
		 * Get the current reprojection error threshold to sort oultliers from
		 * inliers
		 * @return the current reprojection error threshold
		 */
		double getReprojThreshold() const;

		/**
		 * Set a new reprojection error threshold to sort inliers from
		 * outliers
		 * @param reprojThreshold the new reprojection error threshold
		 */
		virtual void setReprojThreshold(const double reprojThreshold);

		/**
		 * Get the number of inliers after reprojecting model points to
		 * scene space
		 * @return the number of inliers
		 */
		int getNbInliers() const;

		/**
		 * Gets the current mean reprojection error when reprojecting model
		 * points to scene space with homography
		 * @return the current mean reprojection error
		 */
		double getMeanReprojectionError() const;

		/**
		 * Gets the current print scale. Scale factor between model image
		 * points and model space points wich depends on the printed model image
		 * size.
		 * @return the current print scale.
		 */
		double getPrintScale() const;

		/**
		 * Set a new printscale for converting model image points to real space
		 * points
		 * @param printScale the new printscale
		 * @return true if printScale have been set and all camera parameters
		 * and printscale are correct (acccording to isCameraSet)
		 */
		virtual bool setPrintScale(const double printScale);

		/**
		 * Gets the current model print size according to print scale.
		 * @return the current print size according to model image width
		 * and printscale.
		 */
		double getPrintSize() const;

		/**
		 * Set a new mode print size and modifies print scale
		 * @param printSize the new print size of the image model
		 * @return true if printScale have been set and all camera parameters
		 * and printscale are correct (acccording to isCameraSet)
		 */
		virtual bool setPrintSize(const double printSize);

		/**
		 * Indicates whether cameera matrix and camera distorsions coefficients
		 * have been set (in order to solve camera pose)
		 * @return true if camera intrinsisc parameters matrix and distorsions
		 * coefficients have been set, false otherwise
		 */
		bool isCameraSet();

		/**
		 * Get the compute camera pose status
		 * @return the current camera pose status
		 */
		bool isComputePose() const;

		/**
		 * Set a new camera pose computing status
		 * @param computePose the new camera pose computing status
		 * @return if computePose is set to be true isCameraSet is called first
		 * to check all camera parameters and printScale are set correctly
		 * So the result might not be equal to computePose if all camera
		 * parameters are not set porperly
		 */
		virtual bool setComputePose(const bool computePose);

		/**
		 * Get the current use previous pose status in pose computing.
		 * If usePreviousPose is true then pose computing is initialized
		 * with current rotationVec et translationVec and further optimized
		 * in pose computing
		 * @return the current "use previous pose" status in pose computing
		 */
		bool isUsePreviousPose();

		/**
		 * Set a new "use previous pose" status in pose computing
		 * @param use the new "use previous pose" status
		 */
		virtual void setUsePreviousPose(const bool use);

		// --------------------------------------------------------------------
		// Processing control methods
		// --------------------------------------------------------------------
		/**
		 * Get current feature points detection status
		 * @return the current feature points detection status
		 * @note Note that is detecting status is false matching and
		 * registering should also be false.
		 */
		bool isDetecting() const;

		/**
		 * Sets a new feature points detecting status
		 * @param detecting the new feature points detecting status
		 */
		virtual void setDetecting(const bool detecting);

		/**
		 * Get current feature points matching status
		 * @return the current feature points matching status
		 * @note Note that is matching status is false registering should also
		 * be false.
		 */
		bool isMatching() const;

		/**
		 * Sets a new feature points matching status
		 * @param matching the new feature points matching status
		 * @return true if matching is set or false is matching is unset or
		 * if matching can not be set because model image is not ready
		 * or detecting is off
		 * @note detecting should be on in order to turn matching on
		 */
		virtual bool setMatching(const bool matching);

		/**
		 * Get current feature points registering status
		 * @return the current points registering status
		 * @note Note that is matching status is false registering should also
		 * be false.
		 */
		bool isRegistering() const;

		/**
		 * Sets a new feature points registering status
		 * @param registering the new feature points registering status
		 * @return true if registering is set or false if registering is unset
		 * or if matching is off
		 * @note matching should be on in order to turn registering on
		 */
		virtual bool setRegistering(const bool registering);

		/**
		 * Set new verbose level
		 * @param level the new verobse level
		 */
		virtual void setVerboseLevel(const VerboseLevel level);


		// --------------------------------------------------------------------
		// Drawing control methods
		// --------------------------------------------------------------------
		/**
		 * Gets the current keypoints drawing mode
		 * @return the current keypoints drawing mode
		 */
		KeyPointShow getKeyPointsMode() const;

		/**
		 * Sets a new keypoints drawing mode
		 * @param mode the new keypoints drawing mode
		 */
		virtual void setKeyPointsMode(const KeyPointShow mode);

		/**
		 * Indicates if model box is drawn on scene image
		 * @return true if model box is drawn on scene image, false otherwise
		 */
		bool isShowModelFrame() const;

		/**
		 * Sets a new drawing status for model box in scene image
		 * @param showModelFrame the new drawing status for model box in scene
		 * image
		 * @return true if show model box is set, false if it is unset or
		 * if it can't be set because registering is off
		 */
		virtual bool setShowModelFrame(const bool showModelFrame);

		/**
		 * Indicates if model frame is drawn on scene image
		 * @return true if model frame is drawn on scene image, false otherwise
		 */
		bool isShowModelBox() const;

		/**
		 * Sets a new drawing status for model frame in scene image
		 * @param showModelBox the new drawing status for model frame in scene
		 * image
		 * @return true if show model Frame is set, false if it is unset or
		 * if show model box could not be stated because registering is off
		 */
		virtual bool setShowModelBox(const bool showModelBox);

		/**
		 * Get current model image box height (in mm)
		 * @return the current model image box height
		 */
		double getBoxHeight() const;

		/**
		 * Sets a new model image box height in scene image
		 * @param height the new model image box height (in mm)
		 * @post the last 4 points of modelBoxPoints3D had their last (Z)
		 * coodinates changed to -height.
		 */
		virtual void setBoxHeight(const double height);

		/**
		 * Return processor processing time of step index
		 * @param index index of the step which processing time is required,
		 * 	- 0 indicates all steps,
		 * 	- 1 indicates feature detection time
		 * 	- 2 indicates descriptors extraction time
		 * 	- 3 indicates matching time between descriptors
		 * 	- 4 indicates registration time
		 * @return the processing time of step index.
		 */
		double getProcessTime(const size_t index = 0) const;

		/**
		 * Return processor mean processing time of step index
		 * @param index index of the step which processing time is required,
		 * 	- 0 indicates all steps,
		 * 	- 1 indicates feature detection time
		 * 	- 2 indicates descriptors extraction time
		 * 	- 3 indicates matching time between descriptors
		 * 	- 4 indicates registration time
		 * @return the processing time of step index.
		 */
		double getMeanProcessTime(const size_t index = 0) const;

		/**
		 * Return processor processing time std of step index
		 * @param index index of the step which processing time is required,
		 * 	- 0 indicates all steps,
		 * 	- 1 indicates feature detection time
		 * 	- 2 indicates descriptors extraction time
		 * 	- 3 indicates matching time between descriptors
		 * 	- 4 indicates registration time
		 * @return the processing time of step index.
		 */
		double getStdProcessTime(const size_t index = 0) const;

		/**
		 * Reset mean and std process times in order to re-start computing
		 * new mean and std process time values.
		 */
		void resetMeanProcessTime();

		/**
		 * Sets Time per feature processing time unit
		 * @param value the time per feature value (true or false)
		 */
		virtual void setTimePerFeature(const bool value);

	protected:
		// --------------------------------------------------------------------
		// Utility drawing methods
		// --------------------------------------------------------------------

		/**
		 * Update Scene detector
		 */
		virtual void updateDetector();

		/**
		 * update matcher and extract matched keypoints
		 */
		virtual void updateMatcher();

		/**
		 * Convert matched keypoints to points, update registrar and extract
		 * inliers keypoints
		 */
		virtual void updateRegistrar();

		/**
		 * Draw results in displaySceneImage and evt displayModelImage
		 * @param redrawModelImage model image redraw needed
		 * @return true if displayModelImage has also been updated
		 */
		virtual bool drawResults(const bool redrawModelImage);

		/**
		 * Construct model frame 2D points from modelImage
		 * @param modelImage model image
		 * @post modelFramePoints2D have been filled with 4 model image corner
		 * points
		 */
		void createFramePoints(const Mat & modelImage);

		/**
		 * Construct model box 3D points from modelImage, print scale and
		 * box height
		 * @param modelImage model image
		 * @param printScale scale between image and printed image
		 * (printedWidth (in mm) / imageWidth (in pixels)
		 * @param height box height in mm
		 * @post modelBoxPoints3D have been filled with 8 model box corners
		 */
		void createBoxPoints(const Mat & modelImage,
							 const double printScale,
							 const double height);

		/**
		 * Convert KeyPoint(s) from detector to Point2f(s) used in registrar
		 * @param kp KeyPoint vector
		 * @param p Point2f vector
		 * @param indexes indexes to choose in Keypoints (when converting only
		 * matched keypoints to points) [default value is empty vector so convert
		 * all keypoints to points]
		 */
		void convertKeyPoints2Points(const vector<KeyPoint> & kp,
									 vector<Point2f> & p,
									 const vector<int> indexes = vector<int>(0));

		/**
		 * Draw points in outImg with color and marker size
		 * @param outImg image to draw in
		 * @param points points to draw
		 * @param color color
		 * @param markerSize point size
		 */
		void plotPoints(Mat & outImg,
						const vector<Point2f> points,
						const Scalar & color,
						size_t markerSize);

		/**
		 * Draw polyline connectig  points in outImg with color and marker size
		 * @param outImg image to draw in
		 * @param points points to draw
		 * @param color color
		 * @param thickness Line thickness
		 * @param isClosed closed curve
		 */
		void plotPolyLine(Mat & outImg,
						  const vector<Point2f> points,
						  const Scalar & color,
						  const int thickness,
						  const bool isClosed = true);

		/**
		 * Plot 3D box 2D points.
		 * First plot base 4 points, then top 4 points and then the 4 studs
		 * @param outImg image to draw in
		 * @param points the 8 points of the box
		 * @param color color
		 * @param thickness Line thickness
		 */
		void plotBox(Mat & outImg,
					 const vector<Point2f> points,
					 const Scalar & color,
					 const int thickness);
};

#endif /* CVDMR_H_ */
