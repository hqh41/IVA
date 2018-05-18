/*
 * CvDetector.cpp
 *
 *  Created on: 29 févr. 2012
 *	  Author: davidroussel
 */
#include <iostream>	// for cout, cerr, clog
#include <sstream>	// for ostringstream
#include <ctime>	// for clock (time measurement)
using namespace std;

#include <opencv2/imgproc.hpp>

#include "CvDetector.h"

/*
 * Feature names to compare with arguments
 */
const string CvDetector::FeatureNames[FEATURE_NUMBER] =
{
	"FAST",
	"STAR",
	"SIFT",
	"SURF",
	"ORB",
	"BRISK",
	"MSER",
	"GFTT",
	"KAZE",
	"AKAZE"
};

/*
 * Descriptors extractors names to compare with arguments
 */
const string CvDetector::DescriptorNames[DESCRIPTOR_NUMBER] =
{
	"SIFT",
	"SURF",
	"ORB",
	"BRISK",
	"BRIEF",
	"FREAK",
	"KAZE",
	"AKAZE"
};

/*
 * Preferred descriptor for a feature.
 * @note We're using BRIEF descriptor as a fallback for every feature
 * which doesn't have a dedicated descriptor (FAST, STAR, MSER, GFTT)
 */
const CvDetector::DescriptorExtractorType
CvDetector::PreferredDescriptor[FEATURE_NUMBER] =
{
	CvDetector::BRIEF_DESCRIPTOR,	// FAST Feature --> Brief Descriptor
	CvDetector::BRIEF_DESCRIPTOR,	// STAR Feature --> Brief Descriptor
	CvDetector::SIFT_DESCRIPTOR,	// SIFT Feature --> SIFT Descriptor
	CvDetector::SURF_DESCRIPTOR,	// SURF Feature --> SURF Descriptor
	CvDetector::ORB_DESCRIPTOR,		// ORB Feature --> ORB Descriptor
	CvDetector::BRISK_DESCRIPTOR,	// BRISK Feature --> BRISK Descriptor
	CvDetector::BRIEF_DESCRIPTOR,	// MSER Feature --> Brief Descriptor
	CvDetector::BRIEF_DESCRIPTOR,	// GFTT Feature --> Brief Descriptor
	CvDetector::KAZE_DESCRIPTOR,	// KAZE Feature --> KAZE Descriptor
	CvDetector::AKAZE_DESCRIPTOR	// AKAZE Feature --> AKAZE Descriptor
};

/*
 * Nature of the descriptor content.
 * Useful to know what kind of mathcher can be used with these descriptors
 */
const bool CvDetector::DescriptorBinary[DESCRIPTOR_NUMBER] =
{
	false,	// SIFT descriptors contains numbers
	false,	// SURF descriptors contains numbers
	true,	// ORB descriptors contains booleans
	true,	// BRISK descriptors contains booleans
	true,	// BRIEF descriptors contains booleans
	true,	// FREAK descriptors contains booleans
	false,	// KAZE descriptors contains numbers
	true	// AKAZE descriptors contains booleans
};

/*
 * Cv feature point detector creator
 * @param sourceImage the source image
 * @param feature the type of feature points to detect
 * @param descriptor
 * @throw CvProcessorException if feature detector or descriptor
 * extractor are empty because they couldn't be created properly
 */
CvDetector::CvDetector(Mat *sourceImage,
					   const FeatureType feature,
					   const DescriptorExtractorType descriptor,
					   const VerboseLevel level)
	throw (CvProcessorException) :
	CvProcessor(sourceImage, level),
	grayInput(nbChannels == 1),
	grayImage(size, CV_8UC1),
	featureType(FEATURE_NUMBER), // souhld be != feature at first
	descriptorType(DESCRIPTOR_NUMBER), // should be != descriptor at first
	detectionTime(0.0),
	meanDetectionTime(),
	extractionTime(0.0),
	meanExtractionTime()
{
	// Set Feature type
	setFeatureType(feature, NULL, false);
	// Set Descriptor extractor type
	setDescriptorExtractorType(descriptor, NULL, false);
	// Set source image (without setting up gray image, feat. type & descr. type)
	setup(sourceImage, false);

	addImage("gray", &grayImage);

	// all set! so update at least once, this should be enough for static images
	if (sourceImage != NULL)
	{
		update();
	}
}

/*
 * Cv Feature point detector copy constructor.
 * Allow to share an already instanciated FeatureDetector:
 * 	- source image is specific to this detector
 * 	- but the FeatureDetector inside comes from the other detector
 * @param sourceImage the new source image
 * @param det the detector to copy the FeatureDetector and DescriptorExtractor
 * from
 */
CvDetector::CvDetector(Mat *sourceImage,
					   const CvDetector & det) :
	CvProcessor(sourceImage, det.verboseLevel),
	grayInput(nbChannels == 1),
	grayImage(size, CV_8UC1),
	featureType(det.featureType),
	descriptorType(det.descriptorType),
	featureName(det.featureName),
	descriptorName(det.descriptorName),
	featureDetector(det.featureDetector),
	descriptorExtractor(det.descriptorExtractor),
	detectionTime(det.detectionTime),
	meanDetectionTime(det.meanDetectionTime),
	extractionTime(det.extractionTime),
	meanExtractionTime(det.meanExtractionTime)
{
	addImage("gray", &grayImage);

	if (sourceImage != NULL)
	{
		// all set! so update at least once, this should be enough
		// for static images
		update();
	}
}

/*
 * Cv Feature points detector destructor
 */
CvDetector::~CvDetector()
{
	cleanup();
}

/*
 * Setup internal attributes according to source image
 * @param sourceImage a new source image
 * @param fullSetup full setup is needed when source image is changed
 * @pre sourceimage is not NULL
 * @post only calls CvProcessor::setup and checks source image has only
 * one channel otherwise the detector might fail
 * @throw CvProcessorException if sourceImage is neither gray level or
 * BGR image
 */
void CvDetector::setup(Mat *sourceImage, const bool fullSetup)
	throw (CvProcessorException)
{
	// Super setup
	CvProcessor::setup(sourceImage, fullSetup);

	if (fullSetup)
	{
		grayImage.create(size, CV_8UC1);
		setFeatureType(featureType);
		setDescriptorExtractorType(descriptorType);
	}

	// Checks this image has only one channel otherwise the detector might fail
	grayInput = sourceImage->channels() == 1;

	if (grayInput)
	{
		grayImage = *sourceImage;
	}
	else
	{
		if (nbChannels != 3)
		{
			throw CvProcessorException(CvProcessorException::INVALID_IMAGE_TYPE);
		}
		// else color image will be converted in update method before processing
	}
}

/*
 * Cleanup attributes before changing source image or cleaning class
 * before destruction
 */
void CvDetector::cleanup()
{
	keyPoints.clear();
	descriptorExtractor.release();
	featureDetector.release();
	grayImage.release();

	// super cleanup
	CvProcessor::cleanup();
}

/*
 * Gets the current feature type
 * @return the current feature type
 */
CvDetector::FeatureType CvDetector::getFeatureType() const
{
	return featureType;
}

/*
 * Sets a new feature type
 * @param featureType the new feature type to set
 * @param detector pointer to another detector : If this pointer is non
 * NULL then copy its feature detector rather than creating a new one
 * @param full full set previously cleanup keyPoints, featureName and
 * featureDetector
 * @post current Feature detector is released and a new one is created
 * IFF the descriptorExtractor is different, otherwise copy the
 * descriptorExtractor algorithm into the feature detector algoritm
 * @throw CvProcessorException if feature detector is empty because it
 * couldn't be created properly
 */
void CvDetector::setFeatureType(const FeatureType featureType,
								const CvDetector * otherDetector,
								const bool full)
	throw (CvProcessorException)
{
	// in any case clears keypoints
	keyPoints.clear();

	if (full)
	{
		featureDetector.release();
		featureName.clear();
	}

	this->featureType = featureType;
	featureName = FeatureNames[featureType];
	bool featureDetectorPaired = false;

	/*
	 * We need to check if descriptorExtractor is non empty and evt
	 * contains an already instanciated instance of the detector we're looking
	 * for (because they might be the same algorithm).
	 * In such a case we will only copy the smart pointer of descriptorExtractor
	 * into featureDetector
	 */
	if (otherDetector != NULL)
	{
		if (featureName == otherDetector->featureName)
		{
			// Just copy the feature detector from another CvDetector
			featureDetector = otherDetector->featureDetector;
			featureDetectorPaired = true;
		}
	}
	else
	{
		if (featureName == descriptorName && !descriptorExtractor.empty())
		{
			// Copy the feature detector from descriptor extractor if they match
			featureDetector = static_cast<Ptr<Feature2D> >(descriptorExtractor);
			featureDetectorPaired = true;
		}
		else
		{
			// Creates new feature detector (algorithm) from featureType
			// TODO Créez le featureDetector
			// see http://docs.opencv.org/3.1.0/d0/d13/classcv_1_1Feature2D.html
			switch (featureType)
			{
				case FAST_FEATURE:
					// see http://docs.opencv.org/3.1.0/df/d74/classcv_1_1FastFeatureDetector.html
					// TODO featureDetector =
                    featureDetector = FastFeatureDetector::create();
					break;
				case STAR_FEATURE:
					// see http://docs.opencv.org/3.1.0/dd/d39/classcv_1_1xfeatures2d_1_1StarDetector.html
                    // featureDetector =
                    featureDetector = StarDetector::create();
					break;
				case SIFT_FEATURE:
					// see http://docs.opencv.org/3.1.0/d5/d3c/classcv_1_1xfeatures2d_1_1SIFT.html
					// TODO featureDetector =
                    featureDetector = SIFT::create();
					break;
				case SURF_FEATURE:
					// see http://docs.opencv.org/3.1.0/d5/df7/classcv_1_1xfeatures2d_1_1SURF.html
					// TODO featureDetector =
                    featureDetector = SURF::create();
					break;
				case ORB_FEATURE:
					// see http://docs.opencv.org/3.1.0/db/d95/classcv_1_1ORB.html
					// TODO featureDetector =
                    featureDetector = ORB::create();
					break;
				case BRISK_FEATURE:
					// see http://docs.opencv.org/3.1.0/de/dbf/classcv_1_1BRISK.html
					// TODO featureDetector =
                    featureDetector = BRISK::create();
					break;
				case MSER_FEATURE:
					// see http://docs.opencv.org/3.1.0/d3/d28/classcv_1_1MSER.html
					// TODO featureDetector =
                    featureDetector = MSER::create();
					break;
				case GFTT_FEATURE:
					// see http://docs.opencv.org/3.1.0/df/d21/classcv_1_1GFTTDetector.html
					// TODO featureDetector =
                    featureDetector = GFTTDetector::create();
					break;
				case KAZE_FEATURE:
					// see http://docs.opencv.org/3.1.0/d3/d61/classcv_1_1KAZE.html
					// TODO featureDetector =
                    featureDetector = KAZE::create();
					break;
				case AKAZE_FEATURE:
					// see http://docs.opencv.org/3.1.0/d8/d30/classcv_1_1AKAZE.html
					// TODO featureDetector =
                    featureDetector = AKAZE::create();
					break;
				default:
					if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
					{
						cerr << "Unknown Feature type " << featureType << endl;
					}
					featureDetector = ORB::create();
					break;
			}
			featureDetectorPaired = false;
		}
	}

	if (!featureDetector.empty())
	{
		if (verboseLevel >= VERBOSE_NOTIFICATIONS)
		{
			clog << (featureDetectorPaired ? "Paired " : "Created ")
				 << FeatureNames[featureType] << " detector" << endl;
		}

		// Prints detector algorithm info
		// detectorInfo(featureDetector, featureType);
	}
	else
	{
		// TODO décommentez les lignes suivantes après avoir créé le
		// featureDetector
        ostringstream msg;
        msg <<  "Can't create detector [" << FeatureNames[featureType] << "]";

        throw CvProcessorException(CvProcessorException::ALLOC_FAILURE,
                                   msg.str().c_str());
	}

	resetMeanProcessTime();
}

/*
 * Get the currently detected keypoints
 * @return the currently detected keypoints
 */
const vector<KeyPoint> & CvDetector::getKeyPoints() const
{
	return keyPoints;
}

/*
 * Get the currently detected keypoints
 * @return the currently detected keypoints
 */
const vector<KeyPoint> * CvDetector::getKeyPointsPtr() const
{
	return &keyPoints;
}

/*
 * Get the current keypoints number
 * @return the current keypoints number
 */
size_t CvDetector::getNbKeypoints() const
{
	return keyPoints.size();
}

/*
 * Extract selected keypoints into another keypoint set.
 * This method is used to extract matched keypoints or inliers
 * keypoints in order to draw them.
 * @param extracted the other keypoints set to store extrated keypoints
 * @param indexes the indices of keypoints to extract
 * @param subindexes the subset of the previous indexes to extract
 * [default value is empty subset so all indexes are extracted]
 * @post extracted is filled with extracted keypoints
 */
void CvDetector::extractSelectedKeypoints(vector<KeyPoint> & extracted,
										  const vector<int> & indexes,
										  const vector<int> & subindexes)
{
	extracted.clear();

//	clog << "extract selected Keypoints" << endl
//		 << "extracted = " << extracted.size() << endl
//		 << "indexes = " << indexes.size() << endl
//		 << "subindexes = " << subindexes.size() << endl;

	if (subindexes.size() == 0) // extract all indexes
	{
//		clog << "single extracting " << indexes.size() << " out of "
//			 << keyPoints.size() << " keypoints" << endl;

		extracted.reserve(indexes.size());

		for (size_t i = 0; i < indexes.size(); i++)
		{
			extracted.push_back(keyPoints[indexes[i]]);
		}
	}
	else // extract only subindexes from indexes
	{
//		clog << "double extracting " << subindexes.size() << " out of "
//			 << indexes.size() << " indexes out of "<< keyPoints.size()
//			 << " keypoints" << endl;

		extracted.reserve(subindexes.size());

		for (size_t i= 0; i < subindexes.size(); i++)
		{
			extracted.push_back(keyPoints[indexes[subindexes[i]]]);
		}
	}

//	clog << "extracted " << extracted.size() << " keypoints" << endl;
}


/*
 * Gets the current descriptor type
 * @return the current descriptor type
 */
CvDetector::DescriptorExtractorType CvDetector::getDescriptorExtractorType() const
{
	return descriptorType;
}

/*
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
void CvDetector::setDescriptorExtractorType(const DescriptorExtractorType descriptorType,
											const CvDetector * detector,
											const bool full)
	throw (CvProcessorException)
{
	if (full)
	{
		descriptors.release();
		descriptorName.clear();
		descriptorExtractor.release();
	}

	this->descriptorType = descriptorType;
	descriptorName = DescriptorNames[descriptorType];
	bool descriptorExtractorPaired = false;

	/*
	 * We need to check if featureDetector is non empty and evt
	 * contains an already instanciated instance of the extractor we're looking
	 * for (Because the algorithm might be the same).
	 * In such a case we will only copy the pointer of featureDetector
	 * into descriptorExtractor
	 */
	if (detector != NULL)
	{
		// just copy the descriptorExtractor from another CvDetector
		descriptorExtractor = detector->descriptorExtractor;
		descriptorExtractorPaired = true;
	}
	else
	{
		if (descriptorName == featureName && !featureDetector.empty())
		{
			// copy the descriptorExtractor algorithm from an already
			// instanciated featureDetector if their names matches
			descriptorExtractor = static_cast<Ptr<Feature2D> >(featureDetector);
			descriptorExtractorPaired = true;
		}
		else
		{
			// TODO Creates new descriptor extractor
			switch (descriptorType)
			{
				case SIFT_DESCRIPTOR:
					// see see http://docs.opencv.org/3.1.0/d5/d3c/classcv_1_1xfeatures2d_1_1SIFT.html
					// TODO descriptorExtractor =
                    descriptorExtractor = SIFT::create();
					break;
				case SURF_DESCRIPTOR:
					// see http://docs.opencv.org/3.1.0/d5/df7/classcv_1_1xfeatures2d_1_1SURF.html
					// TODO descriptorExtractor =
                    descriptorExtractor = SURF::create();
					break;
				case ORB_DESCRIPTOR:
					// see http://docs.opencv.org/3.1.0/db/d95/classcv_1_1ORB.html
					// TODO descriptorExtractor =
                    descriptorExtractor = ORB::create();
					break;
				case BRISK_DESCRIPTOR:
					// see http://docs.opencv.org/3.1.0/de/dbf/classcv_1_1BRISK.html
					// TODO descriptorExtractor =
                    descriptorExtractor = BRISK::create();
					break;
				case BRIEF_DESCRIPTOR:
					// see http://docs.opencv.org/3.1.0/d1/d93/classcv_1_1xfeatures2d_1_1BriefDescriptorExtractor.html
					// TODO descriptorExtractor =
                    descriptorExtractor = BriefDescriptorExtractor::create();
					break;
				case FREAK_DESCRIPTOR:
					// see http://docs.opencv.org/3.1.0/df/db4/classcv_1_1xfeatures2d_1_1FREAK.html
					// TODO descriptorExtractor =
                    descriptorExtractor = FREAK::create();
					break;
				case KAZE_DESCRIPTOR:
					// see http://docs.opencv.org/3.1.0/d3/d61/classcv_1_1KAZE.html
					// TODO descriptorExtractor =
                    descriptorExtractor = KAZE::create();
					break;
				case AKAZE_DESCRIPTOR:
					// see http://docs.opencv.org/3.1.0/d8/d30/classcv_1_1AKAZE.html
					// TODO descriptorExtractor =
                    descriptorExtractor = AKAZE::create();
					break;
				default:
					if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
					{
						cerr << "Unknown Descriptor type " << featureType << endl;
					}
					descriptorExtractor = ORB::create();
					break;
			}
			descriptorExtractorPaired = false;
		}
	}

	if (!descriptorExtractor.empty())
	{
		if (verboseLevel >= VERBOSE_NOTIFICATIONS)
		{
			clog << (descriptorExtractorPaired ? "Paired " : "Created ")
				 << DescriptorNames[descriptorType]
				 << " descriptor extractor with type : "
				 << (descriptorExtractor->descriptorType() == CV_8U ?
					 "Binary" : "Floating point")
				 << ", size : " << descriptorExtractor->descriptorSize() << endl;
			/*
			 * Descriptor type is either
			 * 	- CV_8U = 0 for binary valued descriptors
			 * 	- CV_32F = 5 for 32 bit floating points valued descriptors
			 */
		}

		// Prints descriptors algorithm info
		// extractorInfo(descriptorExtractor, descriptorType);
	}
	else
	{
		// TODO Décommentez les lignes suivantes lorsque le descriptorExtractor
		// est créé
        ostringstream msg;
        msg << "Can't create descriptor extractor ["
            << DescriptorNames[descriptorType] << "]";

        throw CvProcessorException(CvProcessorException::ALLOC_FAILURE,
                                   msg.str().c_str());
	}

	resetMeanProcessTime();
}

/*
 * Gets the preferred descriptor norm (should be NormTypes::NORM_HAMMING (6)
 * for HAMMING distance type suitable for binary descriptors or
 * NormTypes::NORM_L2 (4) L2 distances suitable for valued descriptors.
 * @return the descriptor size used by the descriptor extractor or -1
 * if there is no descriptor extractor
 */
int CvDetector::getDescriptorNorm() const
{
	if (!descriptorExtractor.empty())
	{
		return descriptorExtractor->defaultNorm();
	}
	else
	{
		return -1;
	}
}

/*
 * Gets the preferred descriptor size
 * @return the descriptor size used by the descriptor extractor or 0
 * if there is no descriptor extractor
 */
int CvDetector::getDescriptorSize() const
{
	if (!descriptorExtractor.empty())
	{
		return descriptorExtractor->descriptorSize();
	}
	else
	{
		return 0;
	}
}

/*
 * Gets the preferred descriptor type (should be
 * DescriptorTypes::BINARY_DESCRIPTOR (0) for binary
 * descriptors or DescriptorTypes::VALUED_DESCRIPTOR (5) for valued
 * descriptors.)
 * @return the descriptor type used by the descriptor extractor or -1
 * if there is no descriptor extractor
 */
int CvDetector::getDescriptorType() const
{
	if (!descriptorExtractor.empty())
	{
		return descriptorExtractor->descriptorType();
	}
	else
	{
		return -1;
	}
}


/*
 * Gets the current descriptors computed on keyPoints
 * @return the current descriptors computed on keyPoints
 */
const Mat & CvDetector::getDescriptors() const
{
	return descriptors;
}

/*
 * Gets the current descriptors computed on keyPoints
 * @return the current descriptors computed on keyPoints
 */
Mat * CvDetector::getDescriptorsPtr()
{
	return &descriptors;
}

/*
 * Return processor processing time of step index
 * @param index index of the step which processing time is required,
 * 0 indicates all steps, 1 indicates points detection time and
 * 2 indicates descriptors extraction time.
 * @return the processing time of step index.
 * @see #ProcessTimeIndex
 */
double CvDetector::getProcessTime(const size_t index) const
{
	clock_t lProcessTime;
	switch(index)
	{
		case CvDetector::DETECTION:
			lProcessTime = detectionTime;
			break;
		case CvDetector::EXTRACTION:
			lProcessTime = extractionTime;
			break;
		case CvDetector::ALL:
		default:
			lProcessTime = processTime;
			break;
	}

	if (timePerFeature)
	{
		return (double) lProcessTime / (double) MAX(1, keyPoints.size());
	}
	else
	{
		return (double) lProcessTime;
	}
}


/*
 * Return processor mean processing time of step index
 * @param index index of the step which processing time is required,
 * 0 indicates all steps, 1 indicates points detection time and
 * 2 indicates descriptors extraction time.
 * @return the processing time of step index.
 * @see #ProcessTimeIndex
 */
double CvDetector::getMeanProcessTime(const size_t index) const
{
	MeanValue<clock_t, double> mProcessTime;
	switch(index)
	{
		case CvDetector::DETECTION:
			mProcessTime = meanDetectionTime;
			break;
		case CvDetector::EXTRACTION:
			mProcessTime = meanExtractionTime;
			break;
		case CvDetector::ALL:
		default:
			mProcessTime = meanProcessTime;
			break;
	}

	if (timePerFeature)
	{
		return mProcessTime.mean() / (float) MAX(1, keyPoints.size());
	}
	else
	{
		return mProcessTime.mean();
	}
}

/*
 * Return processor processing time standard deviation of step index
 * @param index index of the step which processing time is required,
 * 0 indicates all steps, 1 indicates points detection time and
 * 2 indicates descriptors extraction time.
 * @return the processing time of step index.
 * @see #ProcessTimeIndex
 */
double CvDetector::getStdProcessTime(const size_t index) const
{
	MeanValue<clock_t, double> mProcessTime;
	switch(index)
	{
		case CvDetector::DETECTION:
			mProcessTime = meanDetectionTime;
			break;
		case CvDetector::EXTRACTION:
			mProcessTime = meanExtractionTime;
			break;
		case CvDetector::ALL:
		default:
			mProcessTime = meanProcessTime;
			break;
	}

	if (timePerFeature)
	{
		return mProcessTime.std() / (float) MAX(1, keyPoints.size());
	}
	else
	{
		return mProcessTime.std();
	}
}

/*
 * Reset mean and std process time in order to re-start computing
 * new mean and std process time values.
 * @note this reimplementation takes into account detectionTime and
 * extractionTime.
 */
void CvDetector::resetMeanProcessTime()
{
	CvProcessor::resetMeanProcessTime();

	meanDetectionTime.reset();
	meanExtractionTime.reset();
}

/*
 * Feature points detector update.
 * Detects keyPoints in source image and compute descriptors on these
 * points
 */
void CvDetector::update()
{
//	clog << "Detector update" << endl;

	clock_t dstart, dend, estart, eend;

	if (sourceImage != NULL)
	{
		// --------------------------------------------------------------------
		// convert source image to gray (if needed)
		// --------------------------------------------------------------------
		if (!grayInput)
		{
			cvtColor(*sourceImage, grayImage, CV_BGR2GRAY);
		}
		else
		{
			grayImage = *sourceImage;
		}

		// --------------------------------------------------------------------
		// Update keypoints and descriptors
		// --------------------------------------------------------------------
		if (!featureDetector.empty())
		{
			dstart = clock();
			// Detect feature points in the grayImage to produce keyPoints
			// TODO déclenchez la détection des keyPoints dans la grayImage
			// en utilisant le featureDetector
			// see http://docs.opencv.org/3.1.0/d0/d13/classcv_1_1Feature2D.html#aa4e9a7082ec61ebc108806704fbd7887
			// featureDetector->...
            featureDetector->detect(grayImage,keyPoints);
			dend = clock();
			detectionTime = dend - dstart;
			meanDetectionTime += detectionTime;
		}
		else
		{
			detectionTime = 0;
		}

		if (!descriptorExtractor.empty())
		{
			estart = clock();
			// Compute descriptors on each detected points on grayImage with
			// keyPoints to produce descriptors
			// TODO calculez les descriptors à partir des keyPoints précédemment
			// détectés dans la grayImage avec le descriptorExtractor
			// see http://docs.opencv.org/3.1.0/d0/d13/classcv_1_1Feature2D.html#ab3cce8d56f4fc5e1d530b5931e1e8dc0
			// descriptorExtractor->...
            descriptorExtractor->compute(grayImage,keyPoints,descriptors);
			eend = clock();
			extractionTime = eend - estart;
			meanExtractionTime += extractionTime;
		}
		else
		{
			extractionTime = 0;
		}

		processTime = detectionTime + extractionTime;
		meanProcessTime += processTime;
	}
}

/*
 * Clears currenlty detected KeyPoints
 * @post keyPoints have been cleared
 */
void CvDetector::clear()
{
	keyPoints.clear();
}

/*
 * Get Feature detector algorithm (featureDetector)
 * @return a smart pointer to the featureDetector
 */
Ptr<Feature2D> CvDetector::getDetectorAlgorithm()
{
	return static_cast<Ptr<Feature2D> >(featureDetector);
}

/*
 * Get Descriptor extractor algorithm (descriptorExtractor)
 * @return a smart pointer to the descriptorExtractor
 */
Ptr<Feature2D> CvDetector::getExtractorAlgorithm()
{
	return static_cast<Ptr<Feature2D> >(descriptorExtractor);
}


/*
 * Prints info on the detector
 * @param ptr smart pointer to the detector
 * @param  type of detector to recast the detector in the correct type
 * in order to explore its members
 */
void CvDetector::detectorInfo(const Ptr<Feature2D> & ptr,
							  const FeatureType type)
{
	if (!ptr.empty())
	{
		cout << "Detector: ";
		switch(type)
		{
			case FAST_FEATURE:
				cout << "FAST Corner detection";
				break;
			case STAR_FEATURE:
				cout << "STAR: STAR feature";
				break;
			case SIFT_FEATURE:
				cout << "SIFT: Scale Invariant Feature Transform";
				break;
			case SURF_FEATURE:
				cout << "SURF : Speeded Up Robust Features";
				break;
			case ORB_FEATURE:
				cout << "ORB : Oriented BRIEF Features";
				break;
			case BRISK_FEATURE:
				cout << "BRISK : Binary Robust Invariant Scalable Keypoints";
				break;
			case MSER_FEATURE:
				cout << "MSER : Maximally Stable Extremal Regions";
				break;
			case GFTT_FEATURE:
				cout << "GFTT : Good Features To Track";
				break;
			case KAZE_FEATURE:
				cout << "KAZE";
				break;
			case AKAZE_FEATURE:
				cout << "Accelerated KAZE";
				break;
			default:
				break;
		}
		cout << endl;

//		algorithmInfo(ptr);
	}
	else
	{
		cerr << "CvDetector::detectorInfo : empy detector" << endl;
	}
}

/*
 * Prints info on the feature points extractor
 * @param ptr smart pointer to the feature points extractor
 * @param  type of extractor
 */
void CvDetector::extractorInfo(const Ptr<Feature2D> & ptr,
							   const DescriptorExtractorType type)
{
	if (!ptr.empty())
	{
		cout << "Descriptor Extractor: ";
		switch(type)
		{
			case SIFT_DESCRIPTOR:
				cout << "SIFT Descriptor: Scale Invariant Feature Transform";
				break;
			case SURF_DESCRIPTOR:
				cout << "SURF Descriptor: Speeded Up Robust Features";
				break;
			case ORB_DESCRIPTOR:
				cout << "ORB descriptor : Oriented BRIEF";
				break;
			case BRISK_DESCRIPTOR:
				cout << "BRISK Descriptor : Binary Robust Invariant Scalable Keypoints";
				break;
			case BRIEF_DESCRIPTOR:
				cout << "BRIEF Descriptor: Binary Robust Independent Elementary Features";
				break;
			case FREAK_DESCRIPTOR:
				cout << "FREAK Descriptor: Fast Retina Keypoint";
				break;
			case KAZE_DESCRIPTOR:
				cout << "KAZE Descriptor: M-SURF adapted to non-linear Scale Space";
				break;
			case AKAZE_DESCRIPTOR:
				cout << "AKAZE Descriptor: Modified-Local Difference Binary (M-LDB) descriptor";
				break;
			default:
				break;
		}
		cout << " (default norm = " << ptr->defaultNorm()
			 << ", descriptor size = " << ptr->descriptorSize()
			 << ", descriptor type = " << ptr->descriptorType() << ")"
			 << endl;
	}
	else
	{
		cerr << "CvDetector::exctractorInfo : empy detector" << endl;
	}
}

/*
 * Prints info on any algorithm (Detector or extractor)
 * @param ptr smart pointer to the algorithm
 */
//void CvDetector::algorithmInfo(const Ptr<Algorithm> & ptr)
//{
//	if (!ptr.empty())
//	{
//		cout << ptr->name() << " Parameters = " << endl;
//		AlgorithmInfo * infoPtr = ptr->info();
//		vector<string> params;
//		infoPtr->getParams(params);

//		for (vector<string>::const_iterator it = params.begin(); it != params.end(); ++it)
//		{
//			string paramName = *it;
//			cout << "\t" << paramName << " = ";
//			int paramType = infoPtr->paramType(paramName.c_str());
//			vector<Mat> mats;
//			switch(paramType)
//			{
//				case Param::INT:
//					cout << ptr->getInt(paramName) << " [integer]";
//					break;
//				case Param::SHORT:
//					cout << ptr->getInt(paramName) << " [short]";
//					break;
//				case Param::BOOLEAN:
//					cout << (ptr->getBool(paramName) ? "true" : "false") << " [boolean]";
//					break;
//				case Param::REAL:
//					cout << ptr->getDouble(paramName) << " [double]";
//					break;
//				case Param::STRING:
//					cout << ptr->getString(paramName) << " [string]";
//					break;
//				case Param::MAT:
//					cout << ptr->getMat(paramName) << " [Mat]";
//					break;
//				case Param::MAT_VECTOR:
//					mats = ptr->getMatVector(paramName);
//					for (vector<Mat>::const_iterator it = mats.begin();
//						 it != mats.end(); ++it)
//					{
//						cout << "(" << *it << ") ";
//					}
//					cout << "[vector<Mat>]";
//					break;
//				case Param::ALGORITHM:
//					cout << ptr->getAlgorithm(paramName) << " [algorithm]";
//					break;
//				case Param::FLOAT:
//					cout << ptr->getDouble(paramName) << " [float]";
//					break;
//				case Param::UNSIGNED_INT:
//					cout << ptr->getInt(paramName) << " [unsigned int]";
//					break;
//				case Param::UINT64:
//					cout << ptr->getInt(paramName) << " [unsigned int64]";
//					break;
//				case Param::UCHAR:
//					cout << ptr->getInt(paramName) << " [unsigned char]";
//					break;
//				default:
//					cout << "[unkown type]";
//					break;
//			}
//			cout << " (" << ptr->paramHelp(paramName) << ")" << endl;
//		}
//	}
//}

