/*
 * CvDMR.cpp
 *
 *  Created on: 28 mars 2012
 *	  Author: davidroussel
 */

#include <iostream>		// for output streams
#include <algorithm>	// for replace algo
using namespace std;

#include <opencv2/highgui.hpp>	// for imread
#include <opencv2/imgproc.hpp>	// for cvtColor
using namespace cv;

#include "CvDMR.h"

/*
 * Color to use when drawing feature points: blue
 */
const Scalar CvDMR::PointsColor = CV_RGB(0, 0, 255);

/*
 * Color to use when drawing matched points: cyan
 */
const Scalar CvDMR::MatchedPointsColor = CV_RGB(0, 255, 255);

/*
 * Color to use when drawing matched inliers points: green
 */
const Scalar CvDMR::InliersPointsColor = CV_RGB(0, 255, 0);

/*
 * Color to use when drawing model image frame on scene image: orange
 */
const Scalar CvDMR::FrameColor = CV_RGB(255,128,64);

/*
 * Color to use when drawing model image box on scene image using
 * current pose : Light Blue
 */
const Scalar CvDMR::BoxColorCurrent = CV_RGB(64,128,255);

/*
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
CvDMR::CvDMR(Mat * sourceImage,
			 const string & modelImageFilename,
			 const string & cameraFilename,
			 const CvDetector::FeatureType featureType,
			 const CvDetector::DescriptorExtractorType descriptorType,
			 const CvMatcher::MatcherType matcherType,
			 const CvMatcher::MatchType matchType,
			 const double reprojectionError,
			 const double printSize,
			 CvAlgoParamSets * paramSets,
			 const VerboseLevel verboseLevel) throw (CvProcessorException) :
	CvProcessor(sourceImage, verboseLevel),
	graySource(nbChannels == 1),
	displaySourceImage(size, CV_8UC3),
	modelPrintSize(printSize),
	modelImageReady(false),
	updatedModelImage(true),
	modelDetector(NULL),
	sceneDetector(new CvDetector(sourceImage,
								 featureType,
								 descriptorType,
								 verboseLevel)),
	paramSets(paramSets),
	detectorsParamSet(paramSets->getParamSet(CvDetector::FeatureNames[featureType])),
	extractorsParamSet(paramSets->getParamSet(CvDetector::DescriptorNames[descriptorType])),
	modelDetectorUpdate(true),
	matcher(new CvMatcher(matcherType, matchType, verboseLevel)),
	cameraMatrix(Mat()),
	distortionCoefs(Mat()),
	registrar(NULL),
	detecting(false),
	matching(false),
	registering(false),
	keyPointsMode(NO_POINTS),
	previousKeyPointsMode(POINTMODES_NUMBER), // to force all images update
	showModelFrame(false),
	showModelBox(false),
	boxHeight(40.0)
	// All other attributes are instanciated with their default constructors
{
	// setup CvProcessor stuff (sourceImage mainly)
	setup(sourceImage, false);

	// setup scene descriptors
	matcher->setSceneDescriptors(sceneDetector->getDescriptorsPtr());

	double printScale = 0.0;

	// Setup model related stuff
	//	- reads model image
	//	- setup model detector based on scene detector (or just
	//	changes the source image if it already exists
	//	- updates model detector
	//	- ...
	if (!modelImageFilename.empty())
	{
		updateModelImage(modelImageFilename);
		// once model image is loaded we can compute printScale
		printScale = printSize / (double)modelImage.cols;
	}

	// Associates detector and extractor algorithms to param sets
	if (detectorsParamSet != NULL)
	{
		detectorsParamSet->addAlgorithm(sceneDetector->getDetectorAlgorithm());
		detectorsParamSet->addAlgorithm(modelDetector->getDetectorAlgorithm());
//		clog << "Detectors parameter set" << endl << *detectorsParamSet << endl;
	}
	else
	{
		cerr << "CvDMR::CvDMR(...) : Null detector param set" << endl;
	}

	if (extractorsParamSet != NULL)
	{
		extractorsParamSet->addAlgorithm(sceneDetector->getExtractorAlgorithm());
		extractorsParamSet->addAlgorithm(modelDetector->getExtractorAlgorithm());
//		clog << "Extractors parameter set" << endl << *extractorsParamSet << endl;
	}
	else
	{
		cerr << "CvDMR::CvDMR(...) : Null extractor param set" << endl;
	}

	// Setup camera parameters if any
	if (!cameraFilename.empty())
	{
		setCameraParameters(cameraFilename);
	}

	// Setup registrar
	registrar = new CvRegistrar(&modelMatchedPoints, 	// model points ptr (updated later)
								&sceneMatchePoints, 	// scene points ptr (updated later)
								reprojectionError,	// reprojection error
								false,	// compute pose
								printScale, 	// print scale
								cameraMatrix,	// camera matrix
								distortionCoefs);

	// Set the local matched points as registrar points
	registrar->setModelPoints(&modelMatchedPoints);
	registrar->setScenePoints(&sceneMatchePoints);

	addImage("scene", &displaySourceImage);
	addImage("model", &displayModelImage);

//	clog << "CvDMR::CvDMR(FeatureType = "<< FeatureNames[featureType]
//		 << " DescriptorType = "<< DescriptorNames[descriptorType]
//		 << ")" << endl;
//	clog << "SceneDetector feature point algo  = "
//		 << sceneDetector->getDetectorAlgorithm() << endl
//		 << "ModelDetector feature points algo = "
//		 << modelDetector->getDetectorAlgorithm() << endl;
//	clog << "SceneDetector descriptors algo  = "
//		 << sceneDetector->getExtractorAlgorithm() << endl
//		 << "ModelDetector descriptors algo  = "
//		 << modelDetector->getExtractorAlgorithm() << endl;
}

/*
 * CvDMR destructor
 */
CvDMR::~CvDMR()
{
	cleanup(); // clean up source related images and sceneDetector
	delete registrar;
	distortionCoefs.release();
	cameraMatrix.release();
	delete matcher;
	delete modelDetector;
	displayModelImage.release();
}

/*
 * Setup attributes when source image is changed
 * @param image source Image
 * @param completeSetup is true when used to change source image,
 * and false when used in constructor
 */
void CvDMR::setup(Mat *image, const bool completeSetup)
{
	assert (image != NULL);

	// super setup
	CvProcessor::setup(image, completeSetup);

	if (completeSetup) // complete setup
	{
		graySource = (image->channels() == 1);
		displaySourceImage.create(size, CV_8UC3);
		sceneDetector = new CvDetector(sourceImage, *modelDetector);
		matcher->setSceneDescriptors(sceneDetector->getDescriptorsPtr());
	}
	else // during constructor only
	{

	}

	// in any cases
}

/*
 * Cleanup attributes before changing source image or cleaning class
 * before destruction
 */
void CvDMR::cleanup()
{
	delete sceneDetector;
	displaySourceImage.release();

	// super cleanup
	CvProcessor::cleanup();
}

/*
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
void CvDMR::update()
{
	// We need to know if model image drawing should be updated
	//	- when model detector has to be updated
	//	- when keypoints drawing mode changes
	//	- when keypoints drawing is set to draw only
	//		- matched keypoints or
	//		- inliers keypoints
	//		because they are always changing
	bool redrawModelImage = (previousKeyPointsMode != keyPointsMode) ||
							(modelDetectorUpdate && detecting) ||
							(keyPointsMode > ALL_POINTS);

	processTime = 0;

	// Update detectors
	if (detecting)
	{
		updateDetector();

		// Update matcher
		if (matching)
		{

			updateMatcher();

			// Update registrar
			if (registering)
			{
				updateRegistrar();
			}
		}
	}

	meanProcessTime += processTime;

	// Draw resutlts in displayImages
	drawResults(redrawModelImage);

	updatedModelImage = false;

	previousKeyPointsMode = keyPointsMode;
}

/*
 * Update Scene detector
 */
void CvDMR::updateDetector()
{
	if (modelDetectorUpdate && modelDetector != NULL)
	{
		modelDetector->update();
		modelDetectorUpdate = false;
	}

	sceneDetector->update();

	processTime += sceneDetector->getProcessTime();
}

/*
 * update matcher and extract matched keypoints
 */
void CvDMR::updateMatcher()
{
	matcher->update();

	processTime += matcher->getProcessTime();

	// If drawing mode shows matched keypoints we should extract them from
	// matched indexes of keyPoints into matchedXXXKeyPoints
	if (keyPointsMode == MATCHED_POINTS)
	{
		// extract ModelMatchedIndexes from matcher into matchedModelKeypoints
		modelDetector->extractSelectedKeypoints(matchedModelKeypoints,
											 matcher->getModelMatchedIndexes());
		// extract SceneMatchedIndexes from matcher into matchedSceneKeypoints
		sceneDetector->extractSelectedKeypoints(matchedSceneKeypoints,
											 matcher->getSceneMatchedIndexes());
	}
}

/*
 * Convert matched keypoints to points, update registrar and extract
 * inliers keypoints
 */
void CvDMR::updateRegistrar()
{
	// ------------------------------------------------------------------------
	// Convert model & scene MATCHED Keypoints to points for
	// registrar
	// ------------------------------------------------------------------------
	modelMatchedPoints.clear();
	sceneMatchePoints.clear();

	convertKeyPoints2Points(modelDetector->getKeyPoints(),
							modelMatchedPoints,
							matcher->getModelMatchedIndexes());

	convertKeyPoints2Points(sceneDetector->getKeyPoints(),
							sceneMatchePoints,
							matcher->getSceneMatchedIndexes());

	// ------------------------------------------------------------------------
	// Update registrar
	// ------------------------------------------------------------------------

	registrar->update();

	processTime += registrar->getProcessTime();

	// If drawing mode shows inliers keypoints we should extract them
	// from inliers indexes of matched indexes of keyPoints into inliersXXXKeyPoints
	if (keyPointsMode == INLIERS_POINTS &&
		registrar->getNbInliers() > 0)
	{
		// TODO extract inliersModelKeyPoints from modelDetector with
		// matcher's modelMatchedIndexes and registrar's inliersIndexes
		// with extractSelectedKeypoints
        modelDetector->extractSelectedKeypoints(inliersModelKeyPoints,matcher->getModelMatchedIndexes(),registrar->getInliersIndexes());

		// TODO extract inliersSceneKeyPoints from sceneDetector with
		// matcher's sceneMatchedIndexes and registrar's inliersIndexes
		// with extractSelectedKeypoints
        sceneDetector->extractSelectedKeypoints(inliersSceneKeyPoints,matcher->getModelMatchedIndexes(),registrar->getInliersIndexes());
	}
	else
	{
		inliersModelKeyPoints.clear();
		inliersSceneKeyPoints.clear();
	}
}

/*
 * Draw results in displaySceneImage and evt displayModelImage
 * @param redrawModelImage model image redraw needed
 * @return true if displayModelImage has also been updated
 */
bool CvDMR::drawResults(const bool redrawModelImage)
{
	// ---------------------------------------------------------
	// Update display images
	// ---------------------------------------------------------

	updatedModelImage  = (redrawModelImage || updatedModelImage) &&
						 modelImageReady;

	// evt update model display image if drawings mode have changed
	if (updatedModelImage)
	{
		if (grayModel)
		{
			cvtColor(modelImage, displayModelImage, CV_GRAY2BGR);
		}
		else
		{
			modelImage.copyTo(displayModelImage);
		}
	}

	// update scene display image
	if (graySource)
	{
		cvtColor(*sourceImage, displaySourceImage, CV_GRAY2BGR);
	}
	else
	{
		sourceImage->copyTo(displaySourceImage);
	}

	// draw keypoints (or not)
	switch (keyPointsMode)
	{
		case NO_POINTS:
			// Do nothing
			break;
		case ALL_POINTS:
			// Draw all keypoints with PointsColor
			if (updatedModelImage)
			{
				// TODO Draw model image keypoints using drawKeypoints with
				// source image = modelImage
				// Keypoints from modelDetector
				// dest image = displayModelImage
				// color = PointsColor
				// flags = DrawMatchesFlags::DRAW_RICH_KEYPOINTS |
				//         DrawMatchesFlags::DRAW_OVER_OUTIMG
				// drawKeypoints(...);
                drawKeypoints(modelImage,modelDetector->getKeyPoints(),displayModelImage,PointsColor,DrawMatchesFlags::DRAW_RICH_KEYPOINTS | DrawMatchesFlags::DRAW_OVER_OUTIMG);
			}
			// TODO Draw scene image keypoints using drawKeypoints with
			// source image = *sourceImage
			// Keypoints from sceneDetector
			// dest image = displaySourceImage
			// color = PointsColor
			// flags = DrawMatchesFlags::DRAW_RICH_KEYPOINTS |
			//         DrawMatchesFlags::DRAW_OVER_OUTIMG
			// drawKeypoints(...);
            drawKeypoints(*sourceImage,sceneDetector->getKeyPoints(),displaySourceImage,PointsColor,DrawMatchesFlags::DRAW_RICH_KEYPOINTS | DrawMatchesFlags::DRAW_OVER_OUTIMG);
			break;
		case MATCHED_POINTS:
			// Draw matched keypoints with MatchedPointsColor
			// Draw model image keypoints
			if (modelImageReady)
			{
				// TODO Draw model image MATCHED keypoints using drawKeypoints
				// source image = modelImage
				// Keypoints  = matchedModelKeypoints
				// dest image = displayModelImage
				// color = MatchedPointsColor
				// flags = DrawMatchesFlags::DRAW_RICH_KEYPOINTS |
				//         DrawMatchesFlags::DRAW_OVER_OUTIMG
				// drawKeypoints(...);
                drawKeypoints(modelImage,matchedModelKeypoints,displayModelImage,MatchedPointsColor,DrawMatchesFlags::DRAW_RICH_KEYPOINTS | DrawMatchesFlags::DRAW_OVER_OUTIMG);
			}
			// TODO Draw scene image MATCHED keypoints using drawKeypoints with
			// source image = *sourceImage
			// Keypoints  = matchedSceneKeypoints
			// dest image = displaySourceImage
			// color = MatchedPointsColor
			// flags = DrawMatchesFlags::DRAW_RICH_KEYPOINTS |
			//         DrawMatchesFlags::DRAW_OVER_OUTIMG
			// drawKeypoints(...);
            drawKeypoints(*sourceImage,matchedSceneKeypoints,displaySourceImage,MatchedPointsColor,DrawMatchesFlags::DRAW_RICH_KEYPOINTS | DrawMatchesFlags::DRAW_OVER_OUTIMG);
			break;
		case INLIERS_POINTS:
			if (modelImageReady)
			{
				// TODO Draw model image MATCHED INLIERS keypoints using drawKeypoints
				// source image = modelImage
				// Keypoints  = inliersModelKeyPoints
				// dest image = displayModelImage
				// color = InliersPointsColor
				// flags = DrawMatchesFlags::DRAW_RICH_KEYPOINTS |
				//         DrawMatchesFlags::DRAW_OVER_OUTIMG
				// drawKeypoints(...);
                drawKeypoints(modelImage,inliersModelKeyPoints,displayModelImage,InliersPointsColor,DrawMatchesFlags::DRAW_RICH_KEYPOINTS | DrawMatchesFlags::DRAW_OVER_OUTIMG);
			}
			// TODO Draw scene image MATCHED INLIERS keypoints using drawKeypoints
			// source image = *sourceImage
			// Keypoints  = inliersSceneKeyPoints
			// dest image = displaySourceImage
			// color = InliersPointsColor
			// flags = DrawMatchesFlags::DRAW_RICH_KEYPOINTS |
			//         DrawMatchesFlags::DRAW_OVER_OUTIMG
			// drawKeypoints();
            drawKeypoints(*sourceImage,inliersSceneKeyPoints,displaySourceImage,InliersPointsColor,DrawMatchesFlags::DRAW_RICH_KEYPOINTS | DrawMatchesFlags::DRAW_OVER_OUTIMG);
			break;
		default:
			// do nothing
		break;
	}

	// draw model frame/box in scene image
	if (registrar != NULL)
	{
		// draw model image frame reprojected in scene image by homography
		if (registering && showModelFrame && registrar->isHomographyOk())
		{
			// TODO Reproject frame model modelFramePoints2D points to scene
			// modelFramePointsReprojected2D with registrar->reprojectPoints2D
			// registrar->...
            registrar->reprojectPoints2D(modelFramePoints2D,modelFramePointsReprojected2D);

			// TODO Uncomment the following
            plotPolyLine(displaySourceImage,
                         modelFramePointsReprojected2D,
                         FrameColor,
                         2,
                         true);
		}

		// draw model box points reprojected in scene image by camera projection
		if (registering && showModelBox)
		{
			if (registrar->isPoseOk())
			{
				// TODO reproject frame box 3D points modelBoxPoints3D to scene 2D
				// points modelBoxPointsReprojected2D with registrar->reprojectPoints3D
				// and using Pose from registrar
				// registrar->...
                registrar->reprojectPoints3D(modelBoxPoints3D,registrar->getPose(),modelBoxPointsReprojected2D);

				// TODO Uncomment the following
                plotBox(displaySourceImage,
                        modelBoxPointsReprojected2D,
                        BoxColorCurrent,
                        2);
			}
		}
	}

	return updatedModelImage;
}

/*
 * Gets the display image for model image
 * @return the display image for model image
 */
const Mat & CvDMR::getDisplayModelImage() const
{
	return displayModelImage;
}

/*
 * Gets the display image pointer for model image
 * @return the display image pointer for model image
 */
Mat * CvDMR::getDisplayModelImagePtr()
{
	return &displayModelImage;
}

/*
 * Gets the display image for scene image
 * @return the display image for scene image
 */
const Mat & CvDMR::getDisplaySourceImage() const
{
	return displaySourceImage;
}

/*
 * Gets the display image pointer for scene image
 * @return the display image pointer for scene image
 */
Mat * CvDMR::getDisplaySourceImagePtr()
{
	return &displaySourceImage;
}

/*
 * Read model image from file, setup detector and update it
 * @param filename the model image file name
 * @post the model image is loaded in modelImage, grayModel and
 * displayModelImage images are created and modelDetector is
 * instanciated with grayModelImage if it was not created otherwise
 * it is just set to grayModelImage, then modelDetector is updated and
 * finally descriptors ptr is provided to the matcher
 * @throw CvProcessorException when the file can not be read
 */
void CvDMR::updateModelImage(const string & filename)
	throw (CvProcessorException)
{
	modelImage.release();
	displayModelImage.release();

	if (verboseLevel >= VERBOSE_ACTIVITY)
	{
		cout << "opening model image " << filename << endl;
	}

	modelImage = imread(filename, CV_LOAD_IMAGE_ANYCOLOR);

	if (!modelImage.empty())
	{
		grayModel = (modelImage.channels() == 1);

		displayModelImage.create(modelImage.size(), CV_8UC3);

		if (grayModel)
		{
			cvtColor(modelImage, displayModelImage, CV_GRAY2BGR);
		}
		else
		{
			modelImage.copyTo(displayModelImage);
		}

		// instanciate detector on gray converted image
		if (modelDetector == NULL)
		{
			// Copy detector from scene detector
			modelDetector = new CvDetector(&modelImage, *sceneDetector);
		}
		else
		{
			modelDetector->setSourceImage(&modelImage);
		}

		// Set model image to ready
		modelImageReady = true;

		// force modelDetector update
		modelDetectorUpdate = true;

		// Setup model descriptors address in the matcher
		matcher->setModelDescriptors(modelDetector->getDescriptorsPtr());

		// Creates model 2D frame points to reproject on scene image with
		// homography
		createFramePoints(modelImage);

		double printScale = modelPrintSize / (double)modelImage.cols;

		if (registrar != NULL)
		{
			// Sets print scale in registrar
			registrar->setPrintScale(printScale);
		}

		// Creates model 3D box points to reproject on scene image with
		// camera pose
		createBoxPoints(modelImage, printScale, boxHeight);

		updatedModelImage = true;
	}
	else // model image empty
	{
		ostringstream oss;
		oss << "CvDMR::loadModelImage(" << filename << ") unable to open file";
		throw CvProcessorException(CvProcessorException::FILE_READ_FAIL,
								   oss.str().c_str());
	}
}

/*
 * Gets the current modelImageReady state
 * @return true if model image is loaded and ready, false otherwise
 */
bool CvDMR::isModelImageready() const
{
	return modelImageReady;
}


/*
 * Read camera matrix from file
 * @param filename file containing camera matrix
 * @post cameraMatrix is set in registrar
 * @post distortionCoefs is set in registrar
 * @throw CvProcessorException when the faile can not be read
 */
void CvDMR::setCameraParameters(const string & filename)
	throw (CvProcessorException)
{
	if (verboseLevel >= VERBOSE_ACTIVITY)
	{
		cout << "Opening Camera model file " << filename << endl;
	}

	FileStorage fs(filename, FileStorage::READ);
	if (fs.isOpened())
	{
		Mat cam64;
		// reads camera matrix from file
		fs["camera_matrix"] >> cam64;

		if (cam64.size() != Size(3,3))
		{
			ostringstream oss;
			oss << "CvDMR::readCameraParameters : error parsing camera matrix : "
				<< cam64;
			throw CvProcessorException(CvProcessorException::FILE_PARSE_FAIL,
									   oss.str().c_str());
		}

		// converts to 32 bits floats
		cam64.convertTo(cameraMatrix,CV_32FC1);

		if (registrar != NULL)
		{
			// When loading another camera matrix
			registrar->setCameraMatrix(cameraMatrix);
		}

		if (verboseLevel >= VERBOSE_NOTIFICATIONS)
		{
			cout << "Camera matrix = " << cameraMatrix << endl;
		}

		Mat coefs64;

		fs["distortion_coefficients"] >> coefs64;

		if (!coefs64.empty())
		{
			if ((coefs64.size() == Size(1,4)) ||
				(coefs64.size() == Size(1,5)) ||
				(coefs64.size() == Size(1,8))) // caution : Size is (width, height)
			{
				coefs64.convertTo(distortionCoefs, CV_32FC1);
			}
			else
			{
				ostringstream oss;
				oss << "CvDMR::readCameraParameters : "
					<< "error parsing camera distorsion : "
					<< coefs64;
				throw CvProcessorException(CvProcessorException::FILE_PARSE_FAIL,
										   oss.str().c_str());
			}
		}
		else // empty distorsion
		{
			/*
			 * Caution : old openCV version tolerates no distorsions in
			 * projectPoints function, but since OpenCV 2.1+ distorsions
			 * coefficients are mandatory
			 */
			ostringstream oss;
			oss << "CvDMR::readCameraParameters : "
				<< "empty camera distorsion : "
				<< coefs64;
			throw CvProcessorException(CvProcessorException::FILE_PARSE_FAIL,
									   oss.str().c_str());
		}


		if (registrar != NULL)
		{
			// When loading another camera matrix
			registrar->setDistortionCoefs(distortionCoefs);
		}

		if (verboseLevel >= VERBOSE_NOTIFICATIONS)
		{
			cout << "distortion coefficients = " << distortionCoefs << endl;
		}
	}
	else
	{
		ostringstream oss;
		oss << "CvDMR::readCameraParameters(" << filename
			<< ") unable to open file";
		throw CvProcessorException(CvProcessorException::FILE_READ_FAIL,
								   oss.str().c_str());
	}
}

// ----------------------------------------------------------------------------
// Detectors methods
// ----------------------------------------------------------------------------

/*
 * Gets the current feature type
 * @return the current feature type
 */
CvDetector::FeatureType CvDMR::getFeatureType() const
{
	return sceneDetector->getFeatureType();
}

/*
 * Sets a new feature type
 * @param featureType the new feature type to set
 * @post current Feature detector is released and a new one is created
 * @throw CvProcessorException if feature detector is empty because it
 * couldn't be created properly
 */
void CvDMR::setFeatureType(const CvDetector::FeatureType featureType)
	throw (CvProcessorException)
{
	sceneDetector->setFeatureType(featureType);

	if (modelDetector != NULL)
	{
		modelDetector->setFeatureType(featureType, sceneDetector);
		// update modeldetector
		modelDetectorUpdate = true;
	}

	if (detectorsParamSet != NULL)
	{
		// clean up parameter set from its associated algorithms
		detectorsParamSet->removeAllAlgorithms();

		// get a new paramSet
		detectorsParamSet = paramSets->getParamSet(CvDetector::FeatureNames[featureType]);
		if (detectorsParamSet != NULL)
		{
			// fill up this parameter set with detectors algorithms
			detectorsParamSet->addAlgorithm(sceneDetector->getDetectorAlgorithm());
			detectorsParamSet->addAlgorithm(modelDetector->getDetectorAlgorithm());
			clog << "New detectors parameter set" << endl << *detectorsParamSet
				 << endl;
		}
		else
		{
			cerr << "CvDMR::setFeatureType(" << CvDetector::FeatureNames[featureType]
				 << ") NULL parameter set" << endl;
		}
	}

//	clog << "CvDMR::setFeatureType("<< FeatureNames[featureType] << ")" << endl;
//	clog << "SceneDetector feature point algo  = "
//		 << sceneDetector->getDetectorAlgorithm() << endl
//		 << "ModelDetector feature points algo = "
//		 << modelDetector->getDetectorAlgorithm() << endl;

	CvDMR::resetMeanProcessTime();
}

/*
 * Gets the current descriptor type
 * @return the current descriptor type
 */
CvDetector::DescriptorExtractorType CvDMR::getDescriptorExtractorType() const
{
	return sceneDetector->getDescriptorExtractorType();
}

/*
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
void CvDMR::setDescriptorExtractorType(const CvDetector::DescriptorExtractorType descriptorType,
							  const bool checkMatcher)
	throw (CvProcessorException)
{
	sceneDetector->setDescriptorExtractorType(descriptorType);

	if (modelDetector != NULL)
	{
		modelDetector->setDescriptorExtractorType(descriptorType, sceneDetector);
		modelDetectorUpdate = true;
	}

	/*
	 * Checks if the current matcher supports this type of descriptors.
	 * If not, then find one who does.
	 */
	if (matcher != NULL && checkMatcher)
	{
		int currentMatcherIndex((int)matcher->getMatcherType());
		bool newMatcherRequired(false);

		while (CvMatcher::MatcherBinary[currentMatcherIndex] !=
			   CvDetector::DescriptorBinary[descriptorType])
		{
			// we need to find another matcher
			currentMatcherIndex = (currentMatcherIndex + 1) % CvMatcher::MATCHER_NUMBER;
			newMatcherRequired = true;
		}

		if (newMatcherRequired)
		{
			// setMatcherType((CvMatcher::MatcherType)currentMatcherIndex, false);
			matcher->setMatcherType((CvMatcher::MatcherType)currentMatcherIndex);
		}
	}

	if (extractorsParamSet != NULL)
	{
		// clean up parameter set from its associated algorithms
		extractorsParamSet->removeAllAlgorithms();

		// get a new paramSet
		extractorsParamSet = paramSets->getParamSet(CvDetector::DescriptorNames[descriptorType]);
		if (extractorsParamSet != NULL)
		{
			// fill up this parameter set with detectors algorithms
			extractorsParamSet->addAlgorithm(sceneDetector->getExtractorAlgorithm());
			extractorsParamSet->addAlgorithm(modelDetector->getExtractorAlgorithm());
			clog << "New extractors parameter set" << endl << *extractorsParamSet
				 << endl;
		}
		else
		{
			cerr << "CvDMR::setDescriptorType(" << CvDetector::DescriptorNames[descriptorType]
				 << ") NULL parameter set" << endl;
		}
	}

//	clog << "CvDMR::setDescriptorType("<< DescriptorNames[descriptorType] << ")" << endl;
//	clog << "SceneDetector descriptors algo  = "
//		 << sceneDetector->getExtractorAlgorithm() << endl
//		 << "ModelDetector descriptors algo  = "
//		 << modelDetector->getExtractorAlgorithm() << endl;

	CvDMR::resetMeanProcessTime();
}

/*
 * Gets the descriptor type used bye the descriptor extractor, should be
 *	- DescriptorTypes::BINARY_DESCRIPTOR (0) for binary descriptors
 *	- DescriptorTypes::VALUED_DESCRIPTOR (5) for valued descriptors
 * @return the descriptor type used by the descriptor extractor or -1
 * if there is no descriptor extractor
 */
int CvDMR::getDescriptorType() const
{
	return sceneDetector->getDescriptorType();
}


// ----------------------------------------------------------------------------
// Matcher methods
// ----------------------------------------------------------------------------

/*
 * Gets the current Matcher type
 * @return the current Matcher type
 */
CvMatcher::MatcherType CvDMR::getMatcherType() const
{
	return matcher->getMatcherType();
}

/*
 * Sets a new matcher type
 * @param matcherType the new matcher type to set
 * @param checkDescriptors check if current descriptors are compatible
 * with the new matcher and if not change the current descriptors.
 * @post the old DescriptorMatcher has been released and a new one
 * has been created
 * @note Setting a new matcher type may involve to change the current
 * descriptors if the content of the current descriptors is not
 * supported by the new matcher.
 * @throw CvProcessorException if matcher is empty because it
 * couldn't be created properly
 */
void CvDMR::setMatcherType(const CvMatcher::MatcherType matcherType,
						   const bool checkDescriptors)
	throw (CvProcessorException)
{
	matcher->setMatcherType(matcherType);

	if (sceneDetector != NULL && checkDescriptors)
	{
		int currentDescriptorIndex((int)getDescriptorExtractorType());
		bool newDescriptorRequired(false);

		if (CvMatcher::MatcherBinary[matcherType] &&
			!CvMatcher::MatcherFloat[matcherType])
		{
			while(!CvDetector::DescriptorBinary[currentDescriptorIndex])
			{
				// searching for the next binary descriptor type
				currentDescriptorIndex = (currentDescriptorIndex + 1) %
										 CvDetector::DESCRIPTOR_NUMBER;
				newDescriptorRequired = true;
			}
		}
		else // !MatcherBinary[matcherType] || MatcherFloat[matcherType]
		{
			if (!CvMatcher::MatcherBinary[matcherType] &&
				CvMatcher::MatcherFloat[matcherType])
			{
				while (CvDetector::DescriptorBinary[currentDescriptorIndex])
				{
					// searching for the previous valued descriptor type
					currentDescriptorIndex--;
					newDescriptorRequired = true;
				}
			}
		}

		if (newDescriptorRequired)
		{
			// setDescriptorType((CvDetector::DescriptorExtractorType)currentDescriptorIndex,
			// 				  false);
			sceneDetector->setDescriptorExtractorType((CvDetector::DescriptorExtractorType)
											 currentDescriptorIndex);
			modelDetector->setDescriptorExtractorType((CvDetector::DescriptorExtractorType)
											 currentDescriptorIndex);
		}
	}

	CvDMR::resetMeanProcessTime();
}

/*
 * Gets the current match mode
 * @return the current match mode
 */
CvMatcher::MatchType CvDMR::getMatcherMode() const
{
	return matcher->getMatcherMode();
}

/*
 * Sets a new matcher mode
 * @param matcherMode the new matcher mode to set
 */
void CvDMR::setMatcherMode(const CvMatcher::MatchType matcherMode)
{
	matcher->setMatcherMode(matcherMode);

	CvDMR::resetMeanProcessTime();
}

/*
 * Indicates if the current matcher can match binary descriptors
 * @return true if the current matcher can match binary descriptors
 * and false otherwiser
 */
bool CvDMR::matchBinary() const
{
	return matcher->matchBinary();
}

/*
 * Indicates if the current matcher can match valued descriptors
 * @return true if the current matcher can match valued descriptors
 * and false otherwise
 */
bool CvDMR::matchFloat() const
{
	return matcher->matchFloat();
}

/*
 * Gets the number of matches
 * @return the current number of matches
 */
int CvDMR::getNbMatches() const
{
	return matcher->getNbMatches();
}

/*
 * Gets the minimum match distance
 * @return the minimum match distance
 */
double CvDMR::getMinMatchError() const
{
	return matcher->getMinMatchError();
}

/*
 * Gets the maximum match distance
 * @return the maximum match distance
 */
double CvDMR::getMaxMatchError() const
{
	return matcher->getMaxMatchError();
}

/*
 * Gets the mean match distance
 * @return the mean match distance
 */
double CvDMR::getMeanMatchError() const
{
	return matcher->getMeanMatchError();
}

/*
 * Gets the current number of best matches to search for each descriptor
 * when using knnMatch
 * @return the current number of best matches to search for each
 * descriptor
 */
int CvDMR::getKnn() const
{
	return matcher->getKnn();
}

/*
 * Sets a new number of best matches to search for each descriptor
 * when using knnMatch
 * @param knn the new number of best matches to search for each
 * descriptor
 */
void CvDMR::setKnn(const int knn)
{
	matcher->setKnn(knn);

	CvDMR::resetMeanProcessTime();
}

/*
 * Gets the current radius threshold to search for each descriptor when
 * using radiusMatch
 * @return the current radius thresold to search for each descriptor
 */
double CvDMR::getRadiusThreshold() const
{
	return matcher->getRadiusThreshold();
}

/*
 * Sets a new radius Threshold to search for each descriptor when using
 * radiusMatch
 * @param radiusThreshold the new radius threshold to set.
 * @post if the new threshold is contained within the bounds
 * [radiusThresholdMin..radiusThresholdMax] the new threshold is set,
 * otherwise min or max are set depending on the saturation side
 */
void CvDMR::setRadiusThreshold(const double radiusThreshold)
{
	matcher->setRadiusThreshold(radiusThreshold);

	CvDMR::resetMeanProcessTime();
}

// ----------------------------------------------------------------------------
// Registrar methods
// ----------------------------------------------------------------------------

/*
 * Get the current reprojection error threshold to sort oultliers from
 * inliers
 * @return the current reprojection error threshold
 */
double CvDMR::getReprojThreshold() const
{
	return registrar->getReprojThreshold();
}

/*
 * Set a new reprojection error threshold to sort inliers from
 * outliers
 * @param reprojThreshold the new reprojection error threshold
 */
void CvDMR::setReprojThreshold(const double reprojThreshold)
{
	registrar->setReprojThreshold(reprojThreshold);

	CvDMR::resetMeanProcessTime();
}

/*
 * Get the number of inliers after reprojecting model points to
 * scene space
 * @return the number of inliers
 */
int CvDMR::getNbInliers() const
{
	return registrar->getNbInliers();
}

/*
 * Gets the current mean reprojection error when reprojecting model
 * points to scene space with homography
 * @return the current mean reprojection error
 */
double CvDMR::getMeanReprojectionError() const
{
	return registrar->getMeanReprojectionError();
}

/*
 * Gets the current print scale. Scale factor between model image
 * points and model space points wich depends on the printed model image
 * size.
 * @return the current print scale.
 */
double CvDMR::getPrintScale() const
{
	return registrar->getPrintScale();
}

/*
 * Set a new printscale for converting model image points to real space
 * points
 * @param printScale the new printscale
 * @return true if printScale have been set and all camera parameters
 * and printscale are correct (acccording to isCameraSet)
 */
bool CvDMR::setPrintScale(const double printScale)
{
	return registrar->setPrintScale(printScale);
}

/*
 * Gets the current model print size according to print scale.
 * @return the current print size according to model image witdh and printscale.
 */
double CvDMR::getPrintSize() const
{
	if (!modelImage.empty())
	{
		return (double)modelImage.cols * registrar->getPrintScale();
	}
	else
	{
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "can't get print size with no model image" << endl;
		}
		return 0.0;
	}
}

/*
 * Set a new mode print size and modifies print scale
 * @param printSize the new print size of the image model
 * @return true if printScale have been set and all camera parameters
 * and printscale are correct (acccording to isCameraSet)
 */
bool CvDMR::setPrintSize(const double printSize)
{
	if (!modelImage.empty())
	{
		return registrar->setPrintScale(printSize / (double)modelImage.cols);
	}
	else
	{
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "can't set print size with no model image" << endl;
		}

		// if there is no model image there is no printScale
		return false;
	}
}

/*
 * Indicates whether cameera matrix and camera distorsions coefficients
 * have been set (in order to solve camera pose)
 * @return true if camera intrinsisc parameters matrix and distorsions
 * coefficients have been set, false otherwise
 */
bool CvDMR::isCameraSet()
{
	return registrar->isCameraSet();
}

/*
 * Get the compute camera pose status
 * @return the current camera pose status
 */
bool CvDMR::isComputePose() const
{
	return registrar->isComputePose();
}

/*
 * Set a new camera pose computing status
 * @param computePose the new camera pose computing status
 * @return if computePose is set to be true isCameraSet is called first
 * to check all camera parameters and printScale are set correctly
 * So the result might not be equal to computePose if all camera
 * parameters are not set porperly
 */
bool CvDMR::setComputePose(const bool computePose)
{
	bool valid = registrar->setComputePose(computePose);

	if (!computePose)
	{
		if (showModelBox)
		{
			CvDMR::setShowModelBox(false);
		}
	}

	CvDMR::resetMeanProcessTime();

	return valid;
}

/*
 * Get the current use previous pose status in pose computing.
 * If usePreviousPose is true then pose computing is initialized
 * with current rotationVec et translationVec and further optimized
 * in pose computing
 * @return the current "use previous pose" status in pose computing
 */
bool CvDMR::isUsePreviousPose()
{
	return registrar->isUsePreviousPose();
}

/*
 * Set a new "use previous pose" status in pose computing
 * @param use the new "use previous pose" status
 */
void CvDMR::setUsePreviousPose(const bool use)
{
	registrar->setUsePreviousPose(use);

	CvDMR::resetMeanProcessTime();
}

// ----------------------------------------------------------------------------
// Processing control methods
// ----------------------------------------------------------------------------

/*
 * Get current feature points detection status
 * @return the current feature points detection status
 * @note Note that is detecting status is false matching and
 * registering should also be false.
 */
bool CvDMR::isDetecting() const
{
	return detecting;
}

/*
 * Sets a new feature points detecting status
 * @param detecting the new feature points detecting status
 */
void CvDMR::setDetecting(bool detecting)
{
	if (!detecting)
	{
		modelDetector->clear();
		sceneDetector->clear();
		if (registering)
		{
			CvDMR::setRegistering(false);
		}
		if (matching)
		{
			CvDMR::setMatching(false);
		}
	}
	else
	{
		modelDetectorUpdate = true;
	}

	this->detecting = detecting;

	if (verboseLevel >= VERBOSE_NOTIFICATIONS)
	{
		cout << "Feature Points detection is " << (detecting ? "on" : "off")
			 << endl;
	}

	CvDMR::resetMeanProcessTime();
}

/*
 * Get current feature points matching status
 * @return the current feature points matching status
 * @note Note that is matching status is false registering should also
 * be false.
 */
bool CvDMR::isMatching() const
{
	return matching;
}

/*
 * Sets a new feature points matching status
 * @param matching the new feature points matching status
 * @return true if matching is set or false is matching is unset or
 * if matching can not be set because model image is not ready
 * or detecting is off
 * @note detecting should be on in order to turn matching on
 */
bool CvDMR::setMatching(bool matching)
{
	if (detecting)
	{
		if (matching)
		{
			this->matching = modelImageReady;
			if (!modelImageReady)
			{
				if (verboseLevel >= VERBOSE_WARNINGS)
				{
					cerr << "Matching can't be set on when model image is "
						 << "not set" << endl;
				}
			}
		}
		else
		{
			this->matching = matching;
			CvDMR::setRegistering(false);
			matchedModelKeypoints.clear();
			matchedSceneKeypoints.clear();
		}

		if (verboseLevel >= VERBOSE_NOTIFICATIONS)
		{
			cout << "Point matching is " << (this->matching ? "on" : "off")
				 << endl;
		}
	}
	else
	{
		this->matching = false;
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "Matching can not be set when detecting is off" << endl;
		}
	}

	CvDMR::resetMeanProcessTime();

	return this->matching;
}

/*
 * Get current feature points registering status
 * @return the current points registering status
 * @note Note that is matching status is false registering should also
 * be false.
 */
bool CvDMR::isRegistering() const
{
	return registering;
}

/*
 * Sets a new feature points registering status
 * @param registering the new feature points registering status
 * @return true if registering is set or false if registering is unset
 * or if matching is off
 * @note matching should be on in order to turn registering on
 */
bool CvDMR::setRegistering(bool registering)
{
	if (matching)
	{
		if (!registering)
		{
			// setShowModelFrame(false);
			showModelFrame = false;
			modelFramePointsReprojected2D.clear();
			if (verboseLevel >= VERBOSE_NOTIFICATIONS)
			{
				cout << "Show model frame is " << (showModelFrame ? "on" : "off")
					 << endl;
			}

			// setComputePose(false);
			registrar->setComputePose(false);
			showModelBox = false;
			modelBoxPointsReprojected2D.clear();
			if (verboseLevel >= VERBOSE_NOTIFICATIONS)
			{
				cout << "Show model box is " << (showModelBox ? "on" : "off")
					 << endl;
			}

			registrar->setUsePreviousPose(false);
		}

		this->registering = registering;

		if (verboseLevel >= VERBOSE_NOTIFICATIONS)
		{
			cout << "Registering is " <<  (this->registering ? "on" : "off")
				 << endl;
		}
	}
	else
	{
		this->registering = false;
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "Registering can not be set when matching is off" << endl;
		}
	}

	CvDMR::resetMeanProcessTime();

	return this->registering;
}

/*
 * Set new verbose level
 * @param level the new verobse level
 */
void CvDMR::setVerboseLevel(const VerboseLevel level)
{
	CvProcessor::setVerboseLevel(level);
	modelDetector->setVerboseLevel(level);
	sceneDetector->setVerboseLevel(level);
	matcher->setVerboseLevel(level);
	registrar->setVerboseLevel(level);
}


// ----------------------------------------------------------------------------
// Drawing control methods
// ----------------------------------------------------------------------------

/*
 * Gets the current keypoints drawing mode
 * @return the current keypoints drawing mode
 */
KeyPointShow CvDMR::getKeyPointsMode() const
{
	return keyPointsMode;
}

/*
 * Sets a new keypoints drawing mode
 * @param mode the new keypoints drawing mode
 */
void CvDMR::setKeyPointsMode(const KeyPointShow mode)
{
	if ((mode >= NO_POINTS) && (mode < POINTMODES_NUMBER))
	{
		keyPointsMode = mode;

		if (verboseLevel >= VERBOSE_ACTIVITY)
		{
			cout << "Keypoints mode is ";
			switch (mode)
			{
				case NO_POINTS:
					cout << "No points";
					break;
				case ALL_POINTS:
					cout << "All ";
					break;
				case MATCHED_POINTS:
					cout << "Matched ";
					break;
				case INLIERS_POINTS:
					cout << "Inliers ";
					break;
				case POINTMODES_NUMBER:
				default:
					cout << "Unknown ";
					break;
			}
			cout << endl;
		}

		updatedModelImage = true;
	}
	else
	{
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "CvDMR::setKeyPointsMode: unknown mode" << endl;
		}
	}
}

/*
 * Indicates if model frame is drawn on scene image
 * @return true if model frame is drawn on scene image, false otherwise
 */
bool CvDMR::isShowModelFrame() const
{
	return showModelFrame;
}

/*
 * Sets a new drawing status for model frame in scene image
 * @param the new drawing status for model frame in scene image
 * @return true if show model box is set, false if it is unset or
 * if it can't be set because registering is off
 */
bool CvDMR::setShowModelFrame(bool showModelFrame)
{
	if (registering)
	{
		this->showModelFrame = showModelFrame;

		if (!showModelFrame)
		{
			modelFramePointsReprojected2D.clear();
		}

		if (verboseLevel >= VERBOSE_NOTIFICATIONS)
		{
			cout << "Show model frame is " << (showModelFrame ? "on" : "off")
				 << endl;
		}
	}
	else
	{
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "Show model frame can't be set without registering" << endl;
		}
	}

	return this->showModelFrame;
}

/*
 * Indicates if model box is drawn on scene image
 * @return true if model box is drawn on scene image, false otherwise
 */
bool CvDMR::isShowModelBox() const
{
	return showModelBox;
}

bool CvDMR::setShowModelBox(bool showModelBox)
{
	if (registering)
	{
		this->showModelBox = showModelBox;

		if (!showModelBox)
		{
			modelBoxPointsReprojected2D.clear();
		}

		if (verboseLevel >= VERBOSE_NOTIFICATIONS)
		{
			cout << "Show model box is " << (showModelBox ? "on" : "off")
				 << endl;
		}
	}
	else
	{
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "Show model box can't be set without registering" << endl;
		}
	}

	return this->showModelBox;
}

/*
 * Get current model image box height
 * @return the current model image box height
 */
double CvDMR::getBoxHeight() const
{
	return boxHeight;
}

/*
 * Sets a new model image box height in scene image
 * @param height the new model image box height (in mm)
 * @post the last 4 points of modelBoxPoints3D had their last (Z)
 * coodinates changed to -height.
 */
void CvDMR::setBoxHeight(const double height)
{
	if (height > 0.0)
	{
		// Sets new box height
		boxHeight = height;

		// modify modelBoxPoints3D
		if (modelBoxPoints3D.size() == 8)
		{
			for (size_t i = 4; i < 8; i++)
			{
				modelBoxPoints3D[i].z = -height;
			}
		}
		else
		{
			if (verboseLevel >= VERBOSE_WARNINGS)
			{
				cerr << "CvDMR::setBoxHeight(" << height
					 << "): unable to modify modelBoxPoints3D" << endl;
			}
		}
	}
	else
	{
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "CvDMR::setBoxHeight(" << height
				 << "): height should be positive" << endl;
		}
	}
}

/*
 * Return processor processing time of step index
 * @param index index of the step which processing time is required,
 * 	- 0 indicates all steps,
 * 	- 1 indicates feature detection time
 * 	- 2 indicates descriptors extraction time
 * 	- 3 indicates matching time between descriptors
 * 	- 4 indicates registration time
 * @return the processing time of step index.
 */
double CvDMR::getProcessTime(const size_t index) const
{
	double lProcessTime = 0.0;
	switch(index)
	{
		case CvDMR::DETECTION:
			if (sceneDetector != NULL)
			{
				lProcessTime = sceneDetector->getProcessTime(CvDetector::DETECTION);
			}
			break;
		case CvDMR::EXTRACTION:
			if (sceneDetector != NULL)
			{
				lProcessTime = sceneDetector->getProcessTime(CvDetector::EXTRACTION);
			}
			break;
		case CvDMR::MATCHING:
			if (matcher != NULL)
			{
				lProcessTime = matcher->getProcessTime();
			}
			break;
		case CvDMR::REGISTRATION:
			if (registrar != NULL)
			{
				lProcessTime = registrar->getProcessTime();
			}
			break;
		case CvDMR::ALL:
		default:
			lProcessTime = (double) processTime;
			break;
	}

	return lProcessTime;
}

/*
 * Return processor mean processing time of step index
 * @param index index of the step which processing time is required,
 * 	- 0 indicates all steps,
 * 	- 1 indicates feature detection time
 * 	- 2 indicates descriptors extraction time
 * 	- 3 indicates matching time between descriptors
 * 	- 4 indicates registration time
 * @return the processing time of step index.
 */
double CvDMR::getMeanProcessTime(const size_t index) const
{
	double lProcessTime = 0.0;
	switch(index)
	{
		case CvDMR::DETECTION:
			if (sceneDetector != NULL)
			{
				lProcessTime = sceneDetector->getMeanProcessTime(CvDetector::DETECTION);
			}
			break;
		case CvDMR::EXTRACTION:
			if (sceneDetector != NULL)
			{
				lProcessTime = sceneDetector->getMeanProcessTime(CvDetector::EXTRACTION);
			}
			break;
		case CvDMR::MATCHING:
			if (matcher != NULL)
			{
				lProcessTime = matcher->getMeanProcessTime();
			}
			break;
		case CvDMR::REGISTRATION:
			if (registrar != NULL)
			{
				lProcessTime = registrar->getMeanProcessTime();
			}
			break;
		case CvDMR::ALL:
		default:
			lProcessTime = meanProcessTime.mean();
			break;
	}

	return lProcessTime;
}

/*
 * Return processor processing time std of step index
 * @param index index of the step which processing time is required,
 * 	- 0 indicates all steps,
 * 	- 1 indicates feature detection time
 * 	- 2 indicates descriptors extraction time
 * 	- 3 indicates matching time between descriptors
 * 	- 4 indicates registration time
 * @return the processing time of step index.
 */
double CvDMR::getStdProcessTime(const size_t index) const
{
	double lProcessTimeStd = 0.0;
	switch(index)
	{
		case CvDMR::DETECTION:
			if (sceneDetector != NULL)
			{
				lProcessTimeStd = sceneDetector->getStdProcessTime(CvDetector::DETECTION);
			}
			break;
		case CvDMR::EXTRACTION:
			if (sceneDetector != NULL)
			{
				lProcessTimeStd = sceneDetector->getStdProcessTime(CvDetector::EXTRACTION);
			}
			break;
		case CvDMR::MATCHING:
			if (matcher != NULL)
			{
				lProcessTimeStd = matcher->getStdProcessTime();
			}
			break;
		case CvDMR::REGISTRATION:
			if (registrar != NULL)
			{
				lProcessTimeStd = registrar->getStdProcessTime();
			}
			break;
		case CvDMR::ALL:
		default:
			lProcessTimeStd = meanProcessTime.std();
			break;
	}

	return lProcessTimeStd;

}

/*
 * Reset mean and std process times in order to re-start computing
 * new mean and std process time values.
 */
void CvDMR::resetMeanProcessTime()
{
	if (sceneDetector != NULL)
	{
		sceneDetector->resetMeanProcessTime();
	}
	if (matcher != NULL)
	{
		matcher->resetMeanProcessTime();
	}
	if (registrar != NULL)
	{
		registrar->resetMeanProcessTime();
	}
}

/*
 * Sets Time per feature processing time unit
 * @param value the time per feature value (true or false)
 */
void CvDMR::setTimePerFeature(const bool value)
{
	timePerFeature = value;
	if (sceneDetector != NULL)
	{
		sceneDetector->setTimePerFeature(value);
	}
	if (modelDetector != NULL)
	{
		modelDetector->setTimePerFeature(value);
	}
	if (matcher != NULL)
	{
		matcher->setTimePerFeature(value);
	}
	if (registrar != NULL)
	{
		registrar->setTimePerFeature(value);
	}
}

/*
 * Get the current detectors parameters set (detectors algorithms
 * have already been associated with each parameter).
 * @return a pointer to the detectors parameters set
 */
CvAlgoParamSet * CvDMR::getDetectorsParamSet() const
{
	return detectorsParamSet;
}

/*
 * Get the current extractors parameters set (extractors algorithms
 * have already been associated with each parameter).
 * @return a pointer to the extractors parameters set
 */
CvAlgoParamSet * CvDMR::getExtractorsParamSet() const
{
	return extractorsParamSet;
}

/*
 * Get Feature detector algorithm (featureDetector)
 * @return a smart pointer to the featureDetector
 */
Ptr<Feature2D> CvDMR::getDetectorsAlgorithm() const
{
	if (sceneDetector != NULL)
	{
		return sceneDetector->getDetectorAlgorithm();
	}
	else
	{
		return Ptr<Feature2D>();
	}
}

/*
 * Get Descriptor extractor algorithm (descriptorExtractor)
 * @return a smart pointer to the descriptorExtractor
 */
Ptr<Feature2D> CvDMR::getExtractorsAlgorithm() const
{
	if (sceneDetector != NULL)
	{
		return sceneDetector->getExtractorAlgorithm();
	}
	else
	{
		return Ptr<Feature2D>();
	}
}

/*
 * Access to #modelDetectorUpdate attribute
 * @return the #modelDetectorUpdate attribute
 */
bool CvDMR::isModelDetectorUpdate() const
{
	return modelDetectorUpdate;
}

/*
 * Set #modelDetectorUpdate attribute to true which should
 * lead to a modelDetector update (which then will reset it to false
 * when done)
 */
void CvDMR::setModelDetectorUpdate()
{
	modelDetectorUpdate = true;

	// This method is also called when an algorithm parameter has changed so
	// we must update meanTimeProcess
	CvDMR::resetMeanProcessTime();
}

// ----------------------------------------------------------------------------
// Utility drawing methods
// ----------------------------------------------------------------------------
/*
 * Construct model frame 2D points from modelImage
 * @param modelImage model image
 * @post modelFramePoints2D hav been filled with 4 mode image corner points
 */
void CvDMR::createFramePoints(const Mat & modelImage)
{
	modelFramePoints2D.clear();

	// build the image frame points so we can project them on scene image later
	// with reprojectPoints2D
	float imageWidth = modelImage.cols - 1;
	float imageHeight = modelImage.rows - 1;
	// top left
	modelFramePoints2D.push_back(Point2f(0, 0));
	// top right
	modelFramePoints2D.push_back(Point2f(imageWidth, 0));
	// botom right
	modelFramePoints2D.push_back(Point2f(imageWidth, imageHeight));
	// bottom left
	modelFramePoints2D.push_back(Point2f(0, imageHeight));

}

/*
 * Construct model box 3D points from modelImage, print scale and
 * box height
 * @param modelImage model image
 * @param printScale scale between image and printed image
 * (printedWidth (in mm) / imageWidth (in pixels)
 * @param height box height in mm
 * @post modelBoxPoints3D have been filled with 8 model box corners
 */
void CvDMR::createBoxPoints(const Mat & modelImage,
							const double printScale,
							const double height)
{
	float imageWidth = modelImage.cols;
	float imageHeight = modelImage.rows;
	float boxRear = 0.0;
	float boxFront = -height; // mm top of image is in -z direction

	// Points du modèle centrés sur le coin (l'arête) supérieur(e) gauche
	 float boxLeft = 0.0;
	 float boxRight = imageWidth * printScale;
	 float boxTop = 0.0;
	 float boxBottom = imageHeight * printScale;

	// Points 3D du modèle centrés sur le centre de l'image
//	float boxRight = (imageWidth/2.0) * printScale;
//	float boxLeft = -boxRight;
//	float boxBottom = (imageHeight/2.0) * printScale;
//	float boxTop = -boxBottom;

	// Image Box 3D points
	// Box edges
	modelBoxPoints3D.clear();
	modelBoxPoints3D.push_back(Point3f(boxLeft,  boxTop,	boxRear));
	modelBoxPoints3D.push_back(Point3f(boxRight, boxTop,	boxRear));
	modelBoxPoints3D.push_back(Point3f(boxRight, boxBottom, boxRear));
	modelBoxPoints3D.push_back(Point3f(boxLeft,  boxBottom, boxRear));
	modelBoxPoints3D.push_back(Point3f(boxLeft,  boxTop,	boxFront));
	modelBoxPoints3D.push_back(Point3f(boxRight, boxTop,	boxFront));
	modelBoxPoints3D.push_back(Point3f(boxRight, boxBottom, boxFront));
	modelBoxPoints3D.push_back(Point3f(boxLeft,  boxBottom, boxFront));
}

/*
 * Convert KeyPoints from detector to Point2fs from the registrar
 * @param kp KeyPoint vector
 * @param p Point2f vector
 * @param indexes indexes to choose in Keypoints (when converting only
 * matched keypoints to points)
 */
void CvDMR::convertKeyPoints2Points(const vector<KeyPoint> & kp,
									vector<Point2f> & p,
									const vector<int> indexes)
{
	if (indexes.size() > 0)
	{
//		clog << "Converting subset " << indexes.size() << " Keypoints out of "
//			 << kp.size() << " to points ... ";
		KeyPoint::convert(kp, p, indexes);
	}
	else
	{
//		clog << "Converting all " << kp.size() << " Keypoints to points ... ";
		KeyPoint::convert(kp, p);
	}

//	clog << "Converted " << p.size() << " points" << endl;
}

/*
 * Draw points in outImg with color and marker size
 * @param outImg image to draw in
 * @param points points to draw
 * @param color color
 * @param markerSize point size
 */
void CvDMR::plotPoints(Mat & outImg,
					   const vector<Point2f> points,
					   const Scalar& color,
					   size_t markerSize)
{
	for (vector<Point2f>::const_iterator pointIt = points.begin();
		 pointIt != points.end(); ++pointIt)
	{
		float mSize = markerSize/2.0;
		Point2f point = *pointIt;
		Point2f p1(point.x - mSize, point.y);
		Point2f p2(point.x + mSize, point.y);
		Point2f p3(point.x, point.y + mSize);
		Point2f p4(point.x, point.y - mSize);

		line(outImg,p1, p2,color,1,CV_AA);
		line(outImg,p3, p4,color,1,CV_AA);
	}
}

/*
 * Draw polyline connectig  points in outImg with color and marker size
 * @param outImg image to draw in
 * @param points points to draw
 * @param color color
 * @param thickness Line thickness
 * @param isClosed closed curve
 */
void CvDMR::plotPolyLine(Mat & outImg,
						 const vector<Point2f> points,
						 const Scalar& color,
						 const int thickness,
						 const bool isClosed)
{
	int nbPoints = points.size();
	if (nbPoints > 1)
	{
		vector<Point2f>::const_iterator pointIt = points.begin();
//		Point2f first = *pointIt;
		Point2f prev = *pointIt;
		++pointIt; // advance one before cycling
		for (; pointIt != points.end(); ++pointIt)
		{
			line(outImg, prev, (*pointIt), color, thickness, CV_AA);
			prev = *pointIt;
		}
		if (isClosed)
		{
			line(outImg, points[nbPoints-1], points[0], color, thickness, CV_AA);
		}
	}
}

/*
 * Plot 3D box 2D points.
 * First plot base 4 points, then top 4 points and then the 4 studs
 * @param outImg image to draw in
 * @param points the 8 points of the box
 * @param color color
 * @param thickness Line thickness
 */
void CvDMR::plotBox(Mat & outImg,
					const vector<Point2f> points,
					const Scalar& color,
					const int thickness)
{
	vector<Point2f>::const_iterator pointIt = points.begin();
	Point2f base0 = *pointIt;
	++pointIt;
	Point2f base1 = *pointIt;
	++pointIt;
	Point2f base2 = *pointIt;
	++pointIt;
	Point2f base3 = *pointIt;
	++pointIt;
	Point2f top0 = *pointIt;
	++pointIt;
	Point2f top1 = *pointIt;
	++pointIt;
	Point2f top2 = *pointIt;
	++pointIt;
	Point2f top3 = *pointIt;

	// Plots box
	line(outImg, base0, base1, color, thickness, CV_AA);
	line(outImg, base1, base2, color, thickness, CV_AA);
	line(outImg, base2, base3, color, thickness, CV_AA);
	line(outImg, base3, base0, color, thickness, CV_AA);
	line(outImg, top0, top1, color, thickness, CV_AA);
	line(outImg, top1, top2, color, thickness, CV_AA);
	line(outImg, top2, top3, color, thickness, CV_AA);
	line(outImg, top3, top0, color, thickness, CV_AA);
	line(outImg, base0, top0, color, thickness, CV_AA);
	line(outImg, base1, top1, color, thickness, CV_AA);
	line(outImg, base2, top2, color, thickness, CV_AA);
	line(outImg, base3, top3, color, thickness, CV_AA);
}

