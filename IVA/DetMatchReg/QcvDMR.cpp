/*
 * QcvDMR.cpp
 *
 *  Created on: 31 mars 2012
 *	  Author: davidroussel
 */

#include <QDebug>

#include "QcvDMR.h"

/*
 * QcvDMR Detector / Matcher / Registrar constructor
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
 * @param printScale the print scale of the printed model image in order
 * to convert model image points to model printed points at real scale
 * @param paramSets Pool of parameters for all algorithms
 * @param verboseLevel verbosity level for messages printing
 * @param imageLock the mutex on source image
 * @param updateThread the thread in which this processor runs
 * @param parent object
 * @throw CvProcessorException when
 * 	- modelImage can't be opened
 * 	- camera parameters file can't be opened
 */
QcvDMR::QcvDMR(Mat * inFrame,
			   const string & modelImageFilename,
			   const string & cameraFilename,
			   const CvDetector::FeatureType featureType,
			   const CvDetector::DescriptorExtractorType descriptorType,
			   const CvMatcher::MatcherType matcherType,
			   const CvMatcher::MatchType matchType,
			   const double reprojectionError,
			   const double printSize,
			   QcvAlgoParamSets * paramSets,
			   const VerboseLevel verboseLevel,
			   QMutex * imageLock,
			   QThread * updateThread,
			   QObject * parent) throw (CvProcessorException) :
	CvProcessor(inFrame), // <-- virtual base class constructor first
	QcvProcessor(inFrame, imageLock, updateThread, parent),
	CvDMR(inFrame,
		  modelImageFilename,
		  cameraFilename,
		  featureType,
		  descriptorType,
		  matcherType,
		  matchType,
		  reprojectionError,
		  printSize,
		  paramSets,
		  verboseLevel),
	previousSceneKeypointsNumber(0),
	scenekeyPointsVariationPercent(0.0f),
	selfLock(updateThread != NULL ? new QMutex() :
									(imageLock != NULL ? imageLock : NULL))
{
	if (updateThread != NULL)
	{
		paramSets->setParent(NULL);
		paramSets->moveToThread(updateThread);
	}
	// QcvProcessor::setNumberFormat("%7.0f");
	paramSets->setLock(selfLock);
}

/*
 * QcvDMR destructor
 */
QcvDMR::~QcvDMR()
{
	reprojectionErrorString.clear();
	minMaxMatchDistanceString.clear();
	meanMatchDistanceString.clear();
	inliersKeypointsNumberString.clear();
	matchedKeypointsNumberString.clear();
	sceneKeypointsNumberString.clear();
	modelKeypointsNumberString.clear();
	detectionTimeString.clear();
	extractionTimeString.clear();
	matchingTimeString.clear();
	registrationTimeString.clear();

	if (selfLock != NULL)
	{
		selfLock->lock();
		selfLock->unlock();
		delete selfLock;
		selfLock = NULL;
	}
}

/*
 * Update computed images and sends displayImageChanged signal if
 * required
 */
void QcvDMR::update()
{
//	qDebug("QcvDMR::update");

	bool updateModelDetectorKeypointsLabel = (modelDetectorUpdate && detecting);

	bool hasSourceLock = (sourceLock != NULL) && (sourceLock != selfLock);
	if (hasSourceLock)
	{
		sourceLock->lock();
	}

	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDMR::update();

	if (hasLock)
	{
		selfLock->unlock();
	}

	if (hasSourceLock)
	{
		sourceLock->unlock();
	}

	if (updateModelDetectorKeypointsLabel)
	{
		// update model detector keypoints number label
		modelKeypointsNumberString =
				QString::number(modelDetector->getNbKeypoints());
		emit(updateModelKeypointsNumberString(modelKeypointsNumberString));
	}

	QcvProcessor::update(); // emits updated signal
}

/*
 * Update Scene detector
 */
void QcvDMR::updateDetector()
{
	CvDMR::updateDetector();

	int sceneKeypointsNumber = sceneDetector->getNbKeypoints();

	// build scene keypoints number string
	if (sceneKeypointsNumber != previousSceneKeypointsNumber)
	{
		scenekeyPointsVariationPercent = (float)(sceneKeypointsNumber - previousSceneKeypointsNumber) / (float)sceneKeypointsNumber;
	}
	else
	{
		scenekeyPointsVariationPercent = 0.0f;
	}

	sceneKeypointsNumberString.sprintf("%4d %+3d%%",
									   sceneKeypointsNumber,
									   (int)round(scenekeyPointsVariationPercent*100));

	emit(updateSceneKeypointsNumberString(sceneKeypointsNumberString));

	detectionTimeString.sprintf(numberFormat.toStdString().c_str(),
								CvDMR::getMeanProcessTime(CvDMR::DETECTION),
								CvDMR::getStdProcessTime(CvDMR::DETECTION));
	emit(updateDetectionTimeString(detectionTimeString));

	extractionTimeString.sprintf(numberFormat.toStdString().c_str(),
								 CvDMR::getMeanProcessTime(CvDMR::EXTRACTION),
								 CvDMR::getStdProcessTime(CvDMR::EXTRACTION));
	emit(updateExtractionTimeString(extractionTimeString));

	previousSceneKeypointsNumber = sceneKeypointsNumber;
}

/*
 * update matcher and extract matched keypoints
 */
void QcvDMR::updateMatcher()
{
	CvDMR::updateMatcher();

	matchedKeypointsNumberString =
		QString::number(matcher->getNbMatches());
	meanMatchDistanceString = QString::number(matcher->getMeanMatchError(), 'f', 2) +
							  QString::fromUtf8(" ± ") +
							  QString::number(matcher->getStdMatchError(), 'f', 2);

	minMaxMatchDistanceString = QString::number(matcher->getMinMatchError(), 'f', 2) +
							 QString::fromUtf8(" / ") +
							 QString::number(matcher->getMaxMatchError(), 'f', 2);


	matchingTimeString.sprintf(numberFormat.toStdString().c_str(),
							   getMeanProcessTime(CvDMR::MATCHING),
							   getStdProcessTime(CvDMR::MATCHING));

	emit (updateMatchedPointsNumberString(matchedKeypointsNumberString));
	emit (updateMeanMatchDistanceString(meanMatchDistanceString));
	emit (updateMinMaxMatchDistanceString(minMaxMatchDistanceString));
	emit (updateMatchingTimeString(matchingTimeString));
}

/*
 * Convert matched keypoints to points, update registrar and extract
 * inliers keypoints
 */
void QcvDMR::updateRegistrar()
{
	CvDMR::updateRegistrar();

	inliersKeypointsNumberString = QString::number(registrar->getNbInliers());
	reprojectionErrorString = QString::number(registrar->getMeanReprojectionError(), 'f', 2);
	registrationTimeString.sprintf(numberFormat.toStdString().c_str(),
								   getMeanProcessTime(CvDMR::REGISTRATION),
								   getStdProcessTime(CvDMR::REGISTRATION));

	emit(updateInliersNumberString(inliersKeypointsNumberString));
	emit(updateReprojectionErrorString(reprojectionErrorString));
	emit(updateRegistrationTimeString(registrationTimeString));
}

/*
 * Read model image from file with notifications
 * @param filename the model image file name
 * @post the model image is loaded in modelImage, grayModel and
 * displayModelImage images are and modelDetector is instanciated with
 * grayModelImage if it was not created otherwise it is just set to
 * grayModelImage, and finally descriptors ptr is provided to the
 * matcher
 * @throw CvProcessorException when the file can not be read
 */
void QcvDMR::updateModelImage(const string & filename) throw (CvProcessorException)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDMR::updateModelImage(filename);

	if (hasLock)
	{
		selfLock->unlock();
	}

	// update model image
	emit(modelImageChanged(getDisplayModelImagePtr()));

	// update model detector keypoints number label
//	modelKeypointsNumberString = QString::number(modelDetector->getNbKeypoints());
	modelKeypointsNumberString.sprintf("%4d", (int)modelDetector->getNbKeypoints());

	emit(updateModelKeypointsNumberString(modelKeypointsNumberString));

	// send feature type to task bar
	message.clear();
	message.append(filename.c_str());
	message.append(tr(" Opened"));
	sendMessage(message, defaultTimeOut);
}

/*
 * Changes source image slot.
 * Attributes needs to be cleaned up then set up again
 * @param image the new source Image
 * @post Various signals are emitted:
 * 	- imageChanged(&displaySourceImage)
 * 	- imageCchanged()
 * 	- if image size changed then imageSizeChanged() is emitted
 * 	- if image color space changed then imageColorsChanged() is emitted
 */
void QcvDMR::setSourceImage(Mat *image)
	throw (CvProcessorException)
{
	Size previousSize(sourceImage->size());
	int previousNbChannels(nbChannels);

	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvProcessor::setSourceImage(image);

	if (hasLock)
	{
		selfLock->unlock();
	}

	/*
	 * displaySourceImage is emitted instead of sourceImage 'cause
	 * displaySourceImage is used to draw results in
	 */
	emit imageChanged(&displaySourceImage);

	emit imageChanged();

	if ((previousSize.width != image->cols) ||
		(previousSize.height != image->rows))
	{
		emit imageSizeChanged();
	}

	if (previousNbChannels != nbChannels)
	{
		emit imageColorsChanged();
	}

	// Force update
	// update();
}

/*
 * Read camera matrix from file
 * @param filename file containing camera matrix
 * @post cameraMatrix is set in registrar
 * @throw CvProcessorException when the faile can not be read
 */
void QcvDMR::setCameraParameters(const string & filename)
	throw (CvProcessorException)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDMR::setCameraParameters(filename);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();
	message.append(tr("Camera parameters are set"));

	sendMessage(message, defaultTimeOut);
}

/*
 * Sets a new feature type with message notification
 * @param featureType the new feature type to set
 * @post current Feature detector is released and a new one is created
 * @throw CvProcessorException if feature detector is empty because it
 * couldn't be created properly
 */
void QcvDMR::setFeatureType(const CvDetector::FeatureType featureType)
	throw (CvProcessorException)
{
	if (featureType != sceneDetector->getFeatureType())
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setFeatureType(featureType);

		if (hasLock)
		{
			selfLock->unlock();
		}

		// update model detector keypoints number label
		modelKeypointsNumberString = QString::number(modelDetector->getNbKeypoints());
		emit(updateModelKeypointsNumberString(modelKeypointsNumberString));

		message.clear();
		message.append(tr("Feature point type set to: "));
		switch (featureType)
		{
			case CvDetector::FAST_FEATURE:
				message.append("FAST: Fast Corner Detection");
				break;
			case CvDetector::STAR_FEATURE:
				message.append("STAR feature");
				break;
			case CvDetector::SIFT_FEATURE:
				message.append("SIFT: Scale Invariant Feature Transform");
				break;
			case CvDetector::SURF_FEATURE:
				message.append("SURF: Speeded Up Robust Features");
				break;
			case CvDetector::ORB_FEATURE:
				message.append("ORB: Oriented BRIEF Features");
				break;
			case CvDetector::BRISK_FEATURE:
				message.append("BRISK: Binary Robust Invariant Scalable Keypoints");
				break;
			case CvDetector::MSER_FEATURE:
				message.append("MSER: Maximally Stable Extremal Regions");
				break;
			case CvDetector::GFTT_FEATURE:
				message.append("GFTT: Good Features To Track");
				break;
			case CvDetector::KAZE_FEATURE:
				message.append("KAZE: KAZE Features");
				break;
			case CvDetector::AKAZE_FEATURE:
				message.append("AKAZE: Accelerated KAZE Features");
				break;
			default:
				message.append(tr("unknown feature"));
				break;
		}

		sendMessage(message, defaultTimeOut);
	}
}

/*
 * Sets a new descriptor type with message notification
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
void QcvDMR::setDescriptorExtractorType(const CvDetector::DescriptorExtractorType descriptorType,
							   const bool checkMatcher)
	throw (CvProcessorException)
{
	if (descriptorType != sceneDetector->getDescriptorExtractorType())
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setDescriptorExtractorType(descriptorType, checkMatcher);

		if (hasLock)
		{
			selfLock->unlock();
		}

		message.clear();
		message.append(tr("Desctiptor exctractor type set to: "));
		switch (descriptorType)
		{
			case CvDetector::SIFT_DESCRIPTOR:
				message.append("SIFT Descriptor: Scale Invariant Feature Transform");
				break;
			case CvDetector::SURF_DESCRIPTOR:
				message.append("SURF Descriptor: Speeded Up Robust Features");
				break;
			case CvDetector::ORB_DESCRIPTOR:
				message.append("ORB descriptor : Oriented BRIEF");
				break;
			case CvDetector::BRISK_DESCRIPTOR:
				message.append("BRISK Descriptor : Binary Robust Invariant Scalable Keypoints");
				break;
			case CvDetector::BRIEF_DESCRIPTOR:
				message.append("BRIEF Descriptor: Binary Robust Independent Elementary Features");
				break;
			case CvDetector::FREAK_DESCRIPTOR:
				message.append("FREAK Descriptor: Fast Retina Keypoint");
				break;
			default:
				message.append(tr("unknown descriptor"));
				break;
		}

		sendMessage(message, defaultTimeOut);
	}
}

/*
 * Set #modelDetectorUpdateNeeded attribute after locking the detectors
 * to true which should lead to a modelDetector update (which then will
 * reset it to false
 * when done)
 */
void QcvDMR::setModelDetectorUpdate()
{
//	qDebug() << "Model detector update required";

	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDMR::setModelDetectorUpdate();

	if (hasLock)
	{
		selfLock->unlock();
	}
}

/*
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
void QcvDMR::setMatcherType(const CvMatcher::MatcherType matcherType,
							const bool checkDescriptors)
	throw (CvProcessorException)
{
	if (matcherType != matcher->getMatcherType())
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setMatcherType(matcherType, checkDescriptors);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Sets a new matcher mode after locking the matcher
 * @param matcherMode the new matcher mode to set
 */
void QcvDMR::setMatcherMode(const CvMatcher::MatchType matcherMode)
{
	if (matcherMode != matcher->getMatcherMode())
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setMatcherMode(matcherMode);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Sets a new number of best matches to search for each descriptor
 * when using knnMatch after locking the matcher
 * @param knn the new number of best matches to search for each
 * descriptor
 */
void QcvDMR::setKnn(const int knn)
{
	if (knn != matcher->getKnn())
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setKnn(knn);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Sets a new radius Threshold to search for each descriptor when using
 * radiusMatch after locking the matcher
 * @param radiusThreshold the new radius threshold to set.
 * @post if the new threshold is contained within the bounds
 * [radiusThresholdMin..radiusThresholdMax] the new threshold is set,
 * otherwise min or max are set depending on the saturation side
 */
void QcvDMR::setRadiusThreshold(const double radiusThreshold)
{
	if (radiusThreshold != matcher->getRadiusThreshold())
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setRadiusThreshold(radiusThreshold);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Set a new reprojection error threshold to sort inliers from
 * outliers after locking the registrar
 * @param reprojThreshold the new reprojection error threshold
 */
void QcvDMR::setReprojThreshold(const double reprojThreshold)
{
	if (reprojThreshold != registrar->getReprojThreshold())
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setReprojThreshold(reprojThreshold);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Set a new mode print size and modifies print scale after locking the
 * registrar
 * @param printSize the new print size of the image model
 * @return true if printScale have been set and all camera parameters
 * and printscale are correct (acccording to isCameraSet)
 */
bool QcvDMR::setPrintSize(const double printSize)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	bool result = CvDMR::setPrintSize(printSize);

	if (hasLock)
	{
		selfLock->unlock();
	}

	return result;
}

/*
 * Set a new camera pose computing status after locking the registrar
 * @param computePose the new camera pose computing status
 * @return if computePose is set to be true isCameraSet is called first
 * to check all camera parameters and printScale are set correctly
 * So the result might not be equal to computePose if all camera
 * parameters are not set porperly
 */
bool QcvDMR::setComputePose(const bool computePose)
{
	bool currentValue = registrar->isComputePose();
	if (computePose != currentValue)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		bool result = CvDMR::setComputePose(computePose);

		if (hasLock)
		{
			selfLock->unlock();
		}

		return result;
	}

	return currentValue;
}

/*
 * Set a new "use previous pose" status in pose computing after locking
 * the registrar
 * @param use the new "use previous pose" status
 */
void QcvDMR::setUsePreviousPose(const bool use)
{
	if (use != registrar->isUsePreviousPose())
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setUsePreviousPose(use);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Sets a new feature points detecting status after locking the
 * detectors
 * @param detecting the new feature points detecting status
 */
void QcvDMR::setDetecting(const bool detecting)
{
	if (detecting != this->detecting)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setDetecting(detecting);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Sets a new feature points matching status after locking the matcher
 * @param matching the new feature points matching status
 * @return true if matching is set or false is matching is unset or
 * if matching can not be set because model image is not ready
 * or detecting is off
 * @note detecting should be on in order to turn matching on
 */
bool QcvDMR::setMatching(const bool matching)
{
	if (matching != this->matching)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		bool result = CvDMR::setMatching(matching);

		if (hasLock)
		{
			selfLock->unlock();
		}

		return result;
	}

	return this->matching;
}

/*
 * Sets a new feature points registering status after locking the
 * registrar
 * @param registering the new feature points registering status
 * @return true if registering is set or false if registering is unset
 * or if matching is off
 * @note matching should be on in order to turn registering on
 */
bool QcvDMR::setRegistering(const bool registering)
{
	if (registering != this->registering)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		bool result = CvDMR::setRegistering(registering);

		if (hasLock)
		{
			selfLock->unlock();
		}

		return result;
	}

	return this->registering;
}

/*
 * Set new verbose level after selflocking
 * @param level the new verobse level
 */
void QcvDMR::setVerboseLevel(const VerboseLevel level)
{
	if (level != this->verboseLevel)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setVerboseLevel(level);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Sets a new keypoints drawing mode after self locking
 * @param mode the new keypoints drawing mode
 */
void QcvDMR::setKeyPointsMode(const KeyPointShow mode)
{
	if (mode != this->keyPointsMode)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setKeyPointsMode(mode);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Sets a new drawing status for model box in scene image after self
 * locking
 * @param showModelFrame the new drawing status for model box in scene
 * image
 * @return true if show model box is set, false if it is unset or
 * if it can't be set because registering is off
 */
bool QcvDMR::setShowModelFrame(const bool showModelFrame)
{
	if (showModelFrame != this->showModelFrame)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		bool result = CvDMR::setShowModelFrame(showModelFrame);

		if (hasLock)
		{
			selfLock->unlock();
		}

		return result;
	}

	return this->showModelFrame;
}

/*
 * Sets a new drawing status for model frame in scene image after self
 * locking
 * @param showModelBox the new drawing status for model frame in scene
 * image
 * @return true if show model Frame is set, false if it is unset or
 * if show model box could not be stated because registering is off
 */
bool QcvDMR::setShowModelBox(const bool showModelBox)
{
	if (showModelBox != this->showModelBox)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		bool result = CvDMR::setShowModelBox(showModelBox);

		if (hasLock)
		{
			selfLock->unlock();
		}

		return result;
	}

	return this->showModelBox;
}

/*
 * Sets a new model image box height in scene image after self locking
 * @param height the new model image box height (in mm)
 * @post the last 4 points of modelBoxPoints3D had their last (Z)
 * coodinates changed to -height.
 */
void QcvDMR::setBoxHeight(const double height)
{
	if (height != this->boxHeight)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setBoxHeight(height);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Sets Time per feature processing time unit slot after self locking
 * @param value the time per feature value (true or false)
 */
void QcvDMR::setTimePerFeature(const bool value)
{
	if (value != this->timePerFeature)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvDMR::setTimePerFeature(value);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Reset mean and std process times in order to re-start computing
 * new mean and std process time values.
 */
void QcvDMR::resetMeanProcessTime()
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDMR::resetMeanProcessTime();

	if (hasLock)
	{
		selfLock->unlock();
	}
}

/*
 * Draw results in displaySceneImage and evt displayModelImage
 * @param redrawModelImage model image redraw needed
 * @return true if displayModelImage has also been updated
 */
bool QcvDMR::drawResults(const bool redrawModelImage)
{
	bool updated = CvDMR::drawResults(redrawModelImage);

	if (updated)
	{
		emit(modelUpdated());
	}

	return updated;
}
