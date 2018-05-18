/*
 * CvDetector.h
 *
 *  Created on: 29 févr. 2012
 *	  Author: davidroussel
 */

#ifndef CVDETECTOR_H_
#define CVDETECTOR_H_

#include <string>
using namespace std;

#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
using namespace cv::xfeatures2d;

#include "CvProcessor.h"
#include "MeanValue.h"

/**
 * OpenCV Feature points detector processor.
 * Detects feature points in (evt gray converted) source image and compute
 * descriptors on these keyPoints.
 * This detector dose not provide any display image (except the ones provided
 * by the CvProcessor class).
 * Which means another class will have to get the detected keyPoints and
 * eventually draw them on another image.
 * @note Please note that all virtual methods may be reimplemented in
 * CvDetector progeny such as QcvDetector which will reimplement these
 * methods with added Qt capabilities (such as signals and slots)
 * @author David Roussel
 * @date 2012/02/29
 */
class CvDetector : virtual public CvProcessor
{
	public:
		/**
		 * Feature type to detect
		 */
		typedef enum
		{
			FAST_FEATURE = 0, //!< FAST: FAST Corner detection
			STAR_FEATURE = 1, //!< STAR: STAR feature
			SIFT_FEATURE = 2, //!< SIFT: Scale Invariant Feature Transform
			SURF_FEATURE = 3, //!< SURF : Speeded Up Robust Features
			ORB_FEATURE = 4,  //!< ORB : Oriented BRIEF Features
			BRISK_FEATURE = 5, //!< BRISK : Binary Robust Invariant Scalable Keypoints
			MSER_FEATURE = 6,   //!< MSER : Maximally Stable Extremal Regions
			GFTT_FEATURE = 7,   //!< GFTT : Good Features To Track
			KAZE_FEATURE = 8,   //!< KAZE Features
			AKAZE_FEATURE = 9,  //!< Accelerated KAZE Features
			FEATURE_NUMBER = 10 //!< Number of Feature types
		} FeatureType;

		/**
		 * Feature names to compare with arguments
		 *	- "FAST",
		 *	- "STAR",
		 *	- "SIFT",
		 *	- "SURF",
		 *	- "ORB",
		 *	- "BRISK",
		 *	- "MSER",
		 *	- "GFTT",
		 *	- "KAZE"
		 *	- "AKAZE"
		 */
		static const string FeatureNames[FEATURE_NUMBER];

		/**
		 * Descriptor extractor types
		 */
		typedef enum
		{
			SIFT_DESCRIPTOR = 0, //!< SIFT Descriptor: Scale Invariant Feature Transform
			SURF_DESCRIPTOR = 1,  //!< SURF Descriptor: Speeded Up Robust Features
			ORB_DESCRIPTOR = 2,   //!< ORB descriptor : Oriented BRIEF
			BRISK_DESCRIPTOR = 3, //!< BRISK Descriptor : Binary Robust Invariant
								  //!Scalable Keypoints
			BRIEF_DESCRIPTOR = 4, //!< BRIEF Descriptor: Binary Robust Independent
								  //!Elementary Features
			FREAK_DESCRIPTOR = 5, //!< FREAK Descriptor: Fast Retina Keypoint
			KAZE_DESCRIPTOR = 6,  //!< KAZE Descriptor
			AKAZE_DESCRIPTOR = 7, //!< Accelerated KAZE Descriptor
			DESCRIPTOR_NUMBER = 8 //!< Number of descriptors
		} DescriptorExtractorType;

		/**
		 * Descriptor types (as provided by Feature2D->descriptorType())
		 */
		enum DescriptorTypes
		{
			/**
			 * Unknown descriptor type
			 */
			UNKOWN_DESCRIPTOR = -1,
			/**
			 * Binary descriptor type used by AKAZE, BRIEF, BRISK, FREAK & ORB
			 */
			BINARY_DESCRIPTOR = 0,
			/**
			 * Valued descriptor type used by KAZE, SIFT & SURF
			 */
			VALUED_DESCRIPTOR = 5
		};

		/**
		 * Descriptors extractors names to compare with arguments
		 *	- "SIFT",
		 *	- "SURF",
		 *	- "ORB",
		 *	- "BRISK",
		 *	- "BRIEF",
		 *	- "FREAK"
		 *	- "KAZE"
		 *	- "AKAZE"
		 */
		static const string DescriptorNames[DESCRIPTOR_NUMBER];

		/**
		 * Preferred descriptor for a feature.
		 * @note We're using BRIEF descriptor as a fallback for every feature
		 * which doesn't have a dedicated descriptor (FAST, STAR, MSER, GFTT)
		 */
		static const DescriptorExtractorType PreferredDescriptor[FEATURE_NUMBER];

		/**
		 * Nature of the descriptor content.
		 * Useful to know what kind of mathcher can be used with these descriptors
		 *	- SIFT: false, SIFT descriptors contains numbers
		 *	- SURF: false, SURF descriptors contains numbers
		 *	- ORB: true, ORB descriptors contains booleans
		 *	- BRISK: true, BRISK descriptors contains booleans
		 *	- BRIEF: true, BRIEF descriptors contains booleans
		 *	- FREAK: true, FREAK descriptors contains booleans
		 *	- KAZE: false, KAZE descriptors contains numbers
		 *	- AKAZE: true, KAZE descriptors contains booleans
		 */
		static const bool DescriptorBinary[DESCRIPTOR_NUMBER];

		/**
		 * Index of processing time
		 */
		typedef enum
		{
			ALL = 0, //!< All processing (points detection + descriptors extraction)
			DETECTION, //!< Feature points detection time index
			EXTRACTION //!< Descriptors extraction time index
		} ProcessTimeIndex;

	protected:
		/**
		 * Indicates sourceimage is already gray image
		 */
		bool grayInput;

		/**
		 * Gray converted image to perform detection on;
		 */
		Mat grayImage;

		/**
		 * The type of features this detector should detect
		 */
		FeatureType featureType;

		/**
		 * The kind of descriptors to compute on keyPoints
		 */
		DescriptorExtractorType descriptorType;

		/**
		 * the name of the corresponding feature to provide to the Feature
		 * detector create method
		 */
		string featureName;

		/**
		 * the name of the corresponding descriptor to provide to the Descriptor
		 * Extractor create method
		 */
		string descriptorName;

		/**
		 * Feature detector.
		 */
		Ptr<Feature2D> featureDetector;

		/**
		 * Descriptor extractor to extract descriptors from keypoints.
		 * featureDetector and descriptorExtractor are differents which allow
		 * to extract SIFT descriptors on SURF points for instance
		 */
		Ptr<Feature2D> descriptorExtractor;

		/**
		 * Keypoints detected by the detector
		 */
		vector<KeyPoint> keyPoints;

		/**
		 * Descriptors matrix computed on the keypoints.
		 * Row i contains the descriptor of ith key point
		 * This matrix is constantly modified by DescriptorExtractor#compute
		 * so we don't initialize it
		 */
		Mat descriptors;

		/**
		 * feature points detection time in ticks
		 */
		clock_t detectionTime;

		/**
		 * feature points mean detection time and std in ticks
		 */
		MeanValue<clock_t, double> meanDetectionTime;

		/**
		 * descriptors extraction time in ticks
		 */
		clock_t extractionTime;

		/**
		 * descriptors mean extraction time and std in ticks
		 */
		MeanValue<clock_t, double> meanExtractionTime;

		/**
		 * Setup internal attributes according to source image
		 * @param sourceImage a new source image
		 * @param fullSetup full setup is needed when source image is changed
		 * @pre sourceimage is not NULL
		 * @post only calls CvProcessor::setup and checks source image has only
		 * one channel otherwise the detector might fail
		 * @throw CvProcessorException if sourceImage is neither gray level or
		 * BGR image
		 */
		virtual void setup(Mat * sourceImage,
						   const bool fullSetup = true) throw(CvProcessorException);

		/**
		 * Cleanup attributes before changing source image or cleaning class
		 * before destruction
		 */
		virtual void cleanup();

	public:
		/**
		 * Cv feature point detector creator
		 * @param sourceImage the source image
		 * @param feature the type of feature points to detect [default value is
		 * SURF Feature]
		 * @param descriptor the type of descriptor to compute on detected
		 * points [default value is SURF Descriptor]
		 * @param level Verbose level
		 * @throw CvProcessorException if feature detector or descriptor
		 * extractor are empty because they couldn't be created properly
		 */
		CvDetector(Mat * sourceImage,
				   const FeatureType feature = SURF_FEATURE,
				   const DescriptorExtractorType descriptor = SURF_DESCRIPTOR,
				   const VerboseLevel level = VERBOSE_NONE)
			throw(CvProcessorException);

		/**
		 * Cv Feature point detector copy constructor.
		 * Allow to share an already instanciated FeatureDetector and
		 * DescriptorExtractor:
		 * 	- source image, keyPoints and descriptors are specific to this
		 * 	detector
		 * 	- but the FeatureDetector and DescriptorExtractor inside comes
		 * 	from the other detector
		 * @param sourceImage the new source image
		 * @param det the detector to copy the FeatureDetector and
		 * DescriptorExtractor from
		 */
		CvDetector(Mat * sourceImage, const CvDetector & det);

		/**
		 * Cv Feature points detector destructor
		 */
		virtual ~CvDetector();

		/**
		 * Feature points detector update.
		 * Detects keyPoints in source image and compute descriptors on these
		 * points
		 */
		virtual void update();

		/**
		 * Clears currenlty detected KeyPoints
		 * @post keyPoints have been cleared
		 */
		virtual void clear();

		/**
		 * Gets the current feature type
		 * @return the current feature type
		 */
		FeatureType getFeatureType() const;

		/**
		 * Sets a new feature type
		 * @param featureType the new feature type to set
		 * @param otherDetector pointer to another detector : If this pointer
		 * is non NULL then copy its feature detector rather than creating a
		 * new one
		 * @param full full set previously cleanup keyPoints, featureName and
		 * featureDetector
		 * @post current Feature detector is released and a new one is created
		 * IFF the descriptorExtractor is different, otherwise copy the
		 * descriptorExtractor algorithm into the feature detector algoritm
		 * @post All mean process times have been rest with
		 * #resetMeanProcessTime
		 * @throw CvProcessorException if feature detector is empty because it
		 * couldn't be created properly
		 */
		void setFeatureType(const FeatureType featureType,
							const CvDetector * otherDetector = NULL,
							const bool full = true) throw(CvProcessorException);

		/**
		 * Get the currently detected keypoints
		 * @return the currently detected keypoints
		 */
		const vector<KeyPoint> & getKeyPoints() const;

		/**
		 * Get the currently detected keypoints pointer
		 * @return the currently detected keypoints
		 */
		const vector<KeyPoint> * getKeyPointsPtr() const;

		/**
		 * Get the current keypoints number
		 * @return the current keypoints number
		 */
		size_t getNbKeypoints() const;

		/**
		 * Extract selected keypoints into another keypoint set.
		 * This method is used to extract matched keypoints or inliers
		 * keypoints in order to draw them.
		 * @param extracted the other keypoints set to store extrated keypoints
		 * @param indexes the indices of keypoints to extract
		 * @param subindexes the subset of the previous indexes to extract
		 * [default value is empty subset so all indexes are extracted]
		 * @post extracted is filled with extracted keypoints
		 */
		void extractSelectedKeypoints(vector<KeyPoint> & extracted,
									  const vector<int> & indexes,
									  const vector<int> & subindexes = vector<int>(0));

		/**
		 * Gets the current descriptor type
		 * @return the current descriptor type
		 */
		DescriptorExtractorType getDescriptorExtractorType() const;

		/**
		 * Sets a new descriptor type
		 * @param descriptorType the new descriptor type to set
		 * @param detector pointer to another detector : If this pointer is non
		 * NULL then copy its descriptor extractor rather than creating a new
		 * one
		 * @param full full set previously cleanup descriptors, descriptorName
		 * and descriptorExtractor
		 * @post current Descriptor extractor is released and a new one is created
		 * @throw CvProcessorException if descriptor extractor is empty because it
		 * couldn't be created properly
		 */
		void setDescriptorExtractorType(const DescriptorExtractorType descriptorType,
										const CvDetector * detector = NULL,
										const bool full = true) throw(CvProcessorException);

		/**
		 * Gets the preferred descriptor norm (should be NormTypes::NORM_HAMMING (6)
		 * for HAMMING distance type suitable for binary descriptors or
		 * NormTypes::NORM_L2 (4) L2 distances suitable for valued descriptors.
		 * @return the descriptor size used by the descriptor extractor or -1
		 * if there is no descriptor extractor
		 */
		int getDescriptorNorm() const;

		/**
		 * Gets the preferred descriptor size
		 * @return the descriptor size used by the descriptor extractor or 0
		 * if there is no descriptor extractor or if the algorithm does not
		 * provide descriptors
		 */
		int getDescriptorSize() const;

		/**
		 * Gets the preferred descriptor type (should be
		 * DescriptorTypes::BINARY_DESCRIPTOR (0) for binary
		 * descriptors or DescriptorTypes::VALUED_DESCRIPTOR (5) for valued
		 * descriptors.)
		 * @return the descriptor type used by the descriptor extractor or -1
		 * if there is no descriptor extractor
		 */
		int getDescriptorType() const;

		/**
		 * Gets keypoints descriptors Matrix
		 * @return the current descriptors computed on keyPoints
		 */
		const Mat & getDescriptors() const;

		/**
		 * Gets keypoints descriptors Matrix pointer
		 * @return the current descriptors computed on keyPoints
		 */
		Mat * getDescriptorsPtr();

		/**
		 * Return processor processing time of step index
		 * @param index index of the step which processing time is required,
		 * 0 indicates all steps, 1 indicates points detection time and
		 * 2 indicates descriptors extraction time.
		 * @return the processing time of step index.
		 * @see #ProcessTimeIndex
		 */
		double getProcessTime(const size_t index = 0) const;

		/**
		 * Return processor mean processing time of step index
		 * @param index index of the step which processing time is required,
		 * 0 indicates all steps, 1 indicates points detection time and
		 * 2 indicates descriptors extraction time.
		 * @return the processing time of step index.
		 * @see #ProcessTimeIndex
		 */
		double getMeanProcessTime(const size_t index = 0) const;

		/**
		 * Return processor processing time standard deviation of step index
		 * @param index index of the step which processing time is required,
		 * 0 indicates all steps, 1 indicates points detection time and
		 * 2 indicates descriptors extraction time.
		 * @return the processing time of step index.
		 * @see #ProcessTimeIndex
		 */
		double getStdProcessTime(const size_t index = 0) const;

		/**
		 * Reset mean and std process time in order to re-start computing
		 * new mean and std process time values.
		 * @note this reimplementation takes into account detectionTime and
		 * extractionTime.
		 */
		void resetMeanProcessTime();

		/**
		 * Get Feature detector algorithm (featureDetector)
		 * @return a smart pointer to the featureDetector
		 * @note don't forget to release this pointer when you're done in order
		 * for this smart pointer to automatically destroye its content
		 */
		Ptr<Feature2D> getDetectorAlgorithm();

		/**
		 * Get Descriptor extractor algorithm (descriptorExtractor)
		 * @return a smart pointer to the descriptorExtractor
		 * @note don't forget to release this pointer when you're done in order
		 * for this smart pointer to automatically destroye its content
		 */
		Ptr<Feature2D> getExtractorAlgorithm();

	private:
		/**
		 * Prints info on the detector
		 * @param ptr smart pointer to the detector
		 * @param  type of detector
		 */
		void detectorInfo(const Ptr<Feature2D> & ptr, const FeatureType type);
		/**
		 * Prints info on the feature points extractor
		 * @param ptr smart pointer to the feature points extractor
		 * @param  type of extractor
		 */
		void extractorInfo(const Ptr<Feature2D> & ptr,
						   const DescriptorExtractorType type);

		/*
		 * OpenCV 3.x Algorithm does not feature introscpection anymore so
		 * remove the algorithmInfo method
		 */
		//		/**
		//		 * Prints info on any algorithm (Detector or extractor)
		//		 * @param ptr smart pointer to the algorithm
		//		 */
		//		void algorithmInfo(const Ptr<Algorithm> & ptr);
};

#endif /* CVDETECTOR_H_ */
