/*
 * CvRegistrar.cpp
 *
 *  Created on: 27 mars 2012
 *	  Author: davidroussel
 */

#include <cassert>

#include <opencv2/calib3d.hpp>	// solvePnP

#include "CvRegistrar.h"

/*
 * Maximum reprojection error threshold [10 pixels]
 */
const double CvRegistrar::reprojThresholdMax = 10.0;

/*
 * Registrar constructor
 * @param modelPoints model matched points from matcher
 * @param scenePoints scene matched points from matcher
 * @param reprojectionError maximum reprojection error to sort model
 * points reprojected in scene space as outliers or inliers
 * @param computePose should pose be computed.
 * In such case the three next parameters should be also set
 * @param printScale Print scale relating model image points to
 * printed model real scale points
 * @param cameraMatrix camera calibration intrinsic coefs matrix
 * @param distortionCoefs camera calibration distotion coefs matrix
 */
CvRegistrar::CvRegistrar(vector<Point2f> * modelPoints,
						 vector<Point2f> * scenePoints,
						 const double reprojectionError,
						 const bool computePose,
						 double printScale,
						 const Mat & cameraMatrix,
						 const Mat & distortionCoefs) :
	modelPoints(modelPoints),
	scenePoints(scenePoints),
	nbPoints(modelPoints == NULL ? 0 : modelPoints->size()),
	homography(Mat::eye(3,3,CV_32F)),
	homographyOk(false),
	reprojThreshold(reprojectionError > 0.0 ? reprojectionError : reprojThresholdMax),
	nbInliers(0),
	meanReprojectionError(0.0),
	computePose(computePose),
	printScale(printScale > 0.0 ? printScale : 0.0),
	cameraMatrix(cameraMatrix),
	distortionCoefs(distortionCoefs),
	cameraSet(false), // until we can test cameraMatrix content below
	rotationVec(1,3,CV_64FC1,Scalar(0.0)),
	translationVec(1,3,CV_64FC1,Scalar(0.0)),
	usePreviousPose(false),
	poseOk(false),
	verboseLevel(CvProcessor::VERBOSE_NONE),
	processTime((clock_t)0),
	meanProcessTime(),
	timePerFeature(false),
	registrationTime(0.0)
	// all vectors created with default constructor
{
	bool illegalHomographyState = false;
	bool illegalPoseState = false;

	// If we should compute homography, modelPoints and scenePoints should
	// be set and contains more than 4 points
	if ((this->modelPoints != NULL) && (this->scenePoints != NULL))
	{
		if (this->modelPoints->size() != this->scenePoints->size())
		{
			if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
			{
				cerr << "CvRegistrar::CvRegistrar: not the same number of"
					 << " model points" << this->modelPoints->size()
					 << " and scene points " << this->scenePoints->size()
					 << ": resetting to none." << endl;
			}

			illegalHomographyState = true;
		}
		else
		{
			if (nbPoints < 4)
			{
				if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
				{
					cerr << "CvRegistrar::CvRegistrar: not enough points to"
						 << " compute homography: " << nbPoints << endl;
				}
				illegalHomographyState = true;
			}
		}
	}
	else
	{
		if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
		{
			cerr << "CvRegistrar::CvRegistrar: scenePoints or modePoints"
				 << " are NULL: resetting to none." << endl;
		}
		illegalHomographyState = true;
	}

	// If we should also compute pose: printscale, cameraMatrix and evt
	// distortion sould be set correctly
	illegalPoseState = !isCameraSet();

	if (illegalPoseState)
	{
		this->computePose = false;
	}

	if (illegalHomographyState)
	{
		this->modelPoints = NULL;
		this->scenePoints = NULL;
		this->computePose = false;
	}

}

/*
 * Registrar destructor
 */
CvRegistrar::~CvRegistrar()
{
	translationVec.release();
	rotationVec.release();
	distortionCoefs.release();
	cameraMatrix.release();
	inliersModelPoints3D.clear();
	inliersIndex.clear();
	reprojModelPoints.clear();
	homography.release();
	scenePoints = NULL;
	modelPoints = NULL;
}

/*
 * Find homography and/or camera pose from 2D scene points and 3D
 * model points correspondances
 */
void CvRegistrar::update()
{
	// Update nbPoints and checks model & scene have the same
	// number of points

	size_t modelNbPoints = modelPoints->size();
	size_t sceneNbPoints = scenePoints->size();

	nbPoints = MIN(modelNbPoints, sceneNbPoints);

	if ((modelNbPoints != sceneNbPoints) &&
		(verboseLevel >= CvProcessor::VERBOSE_WARNINGS))
	{
		cerr << "CvRegistrar::update : incoherent point numbers : "
			 << modelNbPoints << "!=" << sceneNbPoints << endl;
	}

	// Clears previously computed values
	nbInliers = 0;

	clock_t start, end;
	start = clock();

	homographyComputing();

	// --------------------------------------------------------------------
	// Compute Camera Pose
	// --------------------------------------------------------------------
	if (computePose)
	{
		if (homographyOk)
		{
			poseComputing();
		}
	}
	end = clock();

	processTime = end - start;
	meanProcessTime += processTime;
}

/*
 * Conditional update.
 * launch #update only if condition is true
 * @param condition
 */
void CvRegistrar::update(const bool condition)
{
	if (condition)
	{
		update();
	}
	else
	{
		clock_t start, end;
		start = clock();

		// Set all variables modified by update to their fail value
		nbInliers = 0;
		homographyOk = false;
		poseOk = false;

		end = clock();
		processTime = end - start;
		meanProcessTime += processTime;
	}
}

/*
 * Compute homography.
 * Needs to be reimplemented in subclasses to send signal when done
 */
void CvRegistrar::homographyComputing()
{
	reprojModelPoints.clear();
	inliersIndex.clear();

	// -------------------------------------------------------------------
	// Compute Homography
	// -------------------------------------------------------------------
	if ((modelPoints != NULL) && (scenePoints != NULL) && (nbPoints >= 4))
	{
		// ----------------------------------------------------------------
		// TODO Find homography between *modelPoints and *scenePoints using
		// findHomography function with CV_RANSAC approach with reprojThreshold
		// ransac threshold.
		// threshold : points farther from each other than this threshold
		// won't be used in the homography computing
		// ----------------------------------------------------------------
        //clog << "Searching homography with " << nbPoints << " points" << endl;

		InputArray modelPointsArray = *modelPoints;
		InputArray scenePointsArray = *scenePoints;

		if (modelPointsArray.size() == scenePointsArray.size() &&
			modelPointsArray.type() == scenePointsArray.type())
		{
			// homography = ...
            homography = findHomography(*modelPoints,*scenePoints,CV_RANSAC);
		}
		else
		{
			if (verboseLevel >= CvProcessor::VERBOSE_ERRORS)
			{
				clog << "findHomography(...) failed because ";
				if (modelPointsArray.size() != scenePointsArray.size())
				{
					clog << "model has " << modelPointsArray.size()
						 << " points" << " and scene has "
						 << scenePointsArray.size() << " points";
				}

				if (modelPointsArray.type() != scenePointsArray.type())
				{
					clog << "model points and scene points have different types"
						 << endl;
				}
			}
		}

		// ----------------------------------------------------------------
		// Compare model matched reprojected points to scene matched points
		// and remove outliers :
		// ----------------------------------------------------------------

		// TODO Reproject matched model points (*modelPoints) into scene space
		// (reprojModelPoints) using reprojectPoints2D
        // reprojectPoints2D(...);
        reprojectPoints2D(*modelPoints,reprojModelPoints);

		// check distance between reprojected points and scene points to
		// eliminate outliers and keep only inliers reprojecting
		// as close as reprojThreshold from scene points
		for( size_t i = 0; i < nbPoints; i++ )
		{
			// TODO replace error phony initialisation to reprojThreshold by
			// computing the distance from each (*scenePoints)[i] point to each
			// reprojModelPoints[i] using norm function
            //double error = reprojThreshold;
            double error = norm((*scenePoints)[i]-reprojModelPoints[i]);

			// if distance < reprojThreshold then we found an inlier
			// So push current i index to inliersIndex
			if (error < reprojThreshold)
			{
				// TODO We found an inlier ==> increment nbInliers
                nbInliers++;
				// TODO Push this index i to inliersIndex
                inliersIndex.push_back(i);
				// Sum reproj error
				meanReprojectionError += error;
			}
		}

		// Mean reproj error
		meanReprojectionError /= MAX(1, (double)nbInliers);

		if (verboseLevel >= CvProcessor::VERBOSE_ACTIVITY)
		{
			clog << "Reprojection(" << nbPoints << " points)"
				 << " with reproj error " << reprojThreshold
				 << " : inliers = " << nbInliers
				 << ", Mean reprojection error = "
				 << meanReprojectionError << " pixels" << endl;
		}

		homographyOk = true;
	}
	else
	{
		homographyOk = false;
		if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
		{
			cerr << "CvRegistrar::update: homography not computed";

			if (modelPoints == NULL || scenePoints == NULL)
			{
				cerr << ", modelPoints or scenePoints are NULL";
			}

			if (nbPoints < 4)
			{
				cerr << ", not enough points(" << nbPoints << ") to compute"
					 << "homography";
			}

			cerr << endl;
		}
	}

	if (verboseLevel >= CvProcessor::VERBOSE_NOTIFICATIONS)
	{
		clog << "Homography reprojection procuded " << nbInliers
			 << " inliers with " << meanReprojectionError
			 << " pixels reprojection error" << endl;
	}
}

/*
 * Compute camera pose.
 * Needs to be reimplemented in subclasses to send signal when done
 */
void CvRegistrar::poseComputing()
{
	inliersModelPoints3D.clear();
	inliersModelPoints3D.reserve(nbInliers);
	inliersScenePoints2D.clear();
	inliersScenePoints2D.reserve(nbInliers);

	if (cameraSet) // camera parameters are set and prinScale is valid
	{
		if (nbInliers >= 6)	// number of inliers is good enough
		{
			// ----------------------------------------------------------------
			// Compute 3D model inliers points in real printed scale
			// and extract 2D scene inliers that will be used to solve
			// the camera pose
			// ----------------------------------------------------------------
			for (size_t i=0; i < (size_t)nbInliers; i++)
			{
				// TODO point = Current inlier: *modelPoints of index inliersIndex[i]
                Point2f point = (*modelPoints)[inliersIndex[i]];

				// TODO Create the corresponding printed model 3D point
                // Point3f p = ( x & y ) * printScale and z = 0.0
                Point3f p(point.x*printScale,point.y*printScale,0.0);
				// and push this 3D point to inliersModelPoints3D
                inliersModelPoints3D.push_back(p);

				// TODO Push current inlier *scenePoints of index inliersIndex[i] to
				// inliersScenePoints2D
                 inliersScenePoints2D.push_back((*scenePoints)[inliersIndex[i]]);
			}

			// ----------------------------------------------------------------
			// TODO Solve camera pose with solvePnP from
			//	- 3D model inliers points scaled from model inliers image points
			//		to real printed scale : inliersModelPoints3D
			//	- 2D Scene inliers points : inliersScenePoints2D
			//	- Camera intrinsic parameters cameraMatrix
			//	- Camera distortion coefficients distortionCoefs
			//	in order to obtain camera pose (rotationVec & translationVec)
			// Note: pose is defined as the transform that "brings points from
			// the model coordinate system to the camera coordinate system"
			// and therefore is inversed in order to express the camera pose
			// in the model coordinate system
			// ----------------------------------------------------------------
            solvePnP(inliersModelPoints3D,inliersScenePoints2D,cameraMatrix,distortionCoefs,rotationVec,translationVec);

			// TODO change poseOk to true
            poseOk = true;

			currentPose.update(translationVec, rotationVec);
		}
		else // nbInliers <= 6
		{
			poseOk = false;

			if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
			{
				cerr << "CvRegistrar::update: pose not computed";

				if (!homographyOk)
				{
					cerr << ", homography is not valid";
				}

				if (printScale <= 0.0)
				{
					cerr << ", printScale("<< printScale <<") is not valid";
				}

				if (!cameraSet)
				{
					cerr << ", camera parameters are not set";
				}

				if (nbInliers < 6)
				{
					cerr << ", not enough inliers in reprojected points: "
						 << nbInliers;
				}

				cerr << endl;
			}
		}
	}
}

/*
 * Get current pose
 * @return the current pose
 */
const Pose & CvRegistrar::getPose() const
{
	return currentPose;
}

/*
 * Reproject model points into scene points by applying an homography on them
 * @param points points vector to be reprojected (points.size() = N)
 * @param rPoints points transformed by homography
 */
void CvRegistrar::reprojectPoints2D(const vector<Point2f> & points,
									vector<Point2f> & rPoints)
{
	rPoints.clear();
	rPoints.reserve(points.size());

	if (homography.size() == Size(3,3))
	{
		// First convert points to Mat because perspectiveTransform is expecting Mat
		// points (Nx<Point2f> vector) --> pointsMat (Nx1<Point2f> matrix)
		Mat pointsMat = Mat(points);
		// transformed points matrix (Nx1<Point2f> matrix)
		Mat rPointsMat;

		// TODO Then apply homography on pointsMat to obtain rPointsMat with
		// perspectiveTransform function
        perspectiveTransform(pointsMat,rPointsMat,homography);

		// Then Convert rPointsMat back to vector of Point2f : rPoints
		for (int i=0; i < rPointsMat.rows; i++)
		{
			rPoints.push_back(rPointsMat.at<Point2f>(i,0));
		}

		pointsMat.release();
		rPointsMat.release();
	}
	else
	{
		cerr << "reprojectPoints error : wrong homography size ["
			 << homography.rows << "x" << homography.cols << "]" << endl;
	}

}

/*
 * Reproject 3D points from Model to 2D point in image using extrinsic
 * parameters matrix from pose evaluation and intrinsic parameters
 * matrix from calibration
 * @param points3D 3D points vector to project
 * @param the camera pose (position/orientation) to use to reproject
 * 3D points to 2D points
 * @param points2D 2D projected points vector
 */
void CvRegistrar::reprojectPoints3D(const vector<Point3f> & points3D,
									const Pose & pose,
									vector<Point2f> & points2D)
{
	points2D.clear();
	points2D.reserve(points3D.size());

	// TODO reprojects model 3D points to image 2D points with projectPoints
	// function:
	//	- 3D object points to project = points3D
	//	- rotationVec camera rotation vector obtained from pose.rotationVector()
	//	- translationVec camera translation vector obtained from pose.translationVector()
	// 	- camera intrinsic parameter matrix obtained from calibration (cameraMatrix)
	//	- camera distortion coefs obtained from calibration (distortionCoefs)
	// 	- 2D image reprojected points = points2D
    rotationVec = pose.rotationVector();
    translationVec = pose.translationVector();
    projectPoints(points3D,rotationVec,translationVec,cameraMatrix,distortionCoefs,points2D);


}

/*
 * Set model image points
 * @param modelPoints the new model image points
 */
void CvRegistrar::setModelPoints(vector<Point2f> *modelPoints)
{
	this->modelPoints = modelPoints;

	if (modelPoints != NULL)
	{
		nbPoints = (modelPoints->size() != nbPoints ?
					modelPoints->size() : nbPoints);

		clog << "Registrar::setModelPoints: " << modelPoints->size()
			 << " points to " << nbPoints << " points"<< endl;
	}
	else
	{
		nbPoints = 0;

		if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
		{
			cerr << "Registrar::setModelPoints: NULL model points" << endl;
		}
	}

}

/*
 * Set scene image points
 * @param scenePoints the new scene image points
 */
void CvRegistrar::setScenePoints(vector<Point2f> *scenePoints)
{
	this->scenePoints = scenePoints;

	if (scenePoints != NULL)
	{
		nbPoints = (scenePoints->size() != nbPoints ?
					scenePoints->size() : nbPoints);

		clog << "Registrar::setScenePoints: " << scenePoints->size()
			 << " points to " << nbPoints << " points"<< endl;

	}
	else
	{
		nbPoints = 0;

		if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
		{
			cerr << "Registrar::setScenePoints: NULL scene points" << endl;
		}
	}
}

/*
 * Gets the number of points in model and scene points
 * @return the number of points in model and scene points
 */
size_t CvRegistrar::getNbPoints() const
{
	return nbPoints;
}

/*
 * Get the current homography
 * @return the current homography
 * @note default homography might be identity if no bomography has
 * been computed yet
 */
const Mat & CvRegistrar::getHomography() const
{
	return homography;
}

/*
 * Get computed homography status
 * @return true if homography has been computed, false if homography
 * has not been computed yet or if there ise not enough points
 * to compute homography (we need at least 4 points to compute
 * homography)
 */
bool CvRegistrar::isHomographyOk() const
{
	return homographyOk;
}

/*
 * Gets model points reprojected in scene space by homography
 * @return the model points reprojected in scene space by homography
 */
const vector<Point2f> & CvRegistrar::getReprojModelPoints() const
{
	return reprojModelPoints;
}

/*
 * Get the current reprojection error threshold to sort oultliers from
 * inliers
 * @return the current reprojection error threshold
 */
double CvRegistrar::getReprojThreshold() const
{
	return reprojThreshold;
}

/*
 * Set a new reprojection error threshold to sort inliers from
 * outliers
 * @param reprojThreshold the new reprojection error threshold
 */
void CvRegistrar::setReprojThreshold(const double reprojThreshold)
{
	if ((reprojThreshold >= 0)  && (reprojThreshold <= reprojThresholdMax))
	{
		this->reprojThreshold = reprojThreshold;
	}
	else
	{
		if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
		{
			cerr << "registrar invalid reprojection threshold: "
				 << reprojThreshold << "[" << 0.0 << "..."
				 << reprojThresholdMax << "]" << endl;
		}
	}

	resetMeanProcessTime();
}

/*
 * Get the maximum reprojection error threshold to sort oultliers from
 * inliers
 * @return the maximum reprojection error threshold
 */
double CvRegistrar::getReprojThresholdMax()
{
	return reprojThresholdMax;
}

/*
 * Get the number of inliers after reprojecting model points to
 * scene space
 * @return the number of inliers
 */
int CvRegistrar::getNbInliers() const
{
	return nbInliers;
}

/*
 * Gets the indices of inliers points amongst model and scene points
 * in order to extract inliers points from these two sets
 * @return the indices of inliers points amongst model and scene points
 */
const vector<int> & CvRegistrar::getInliersIndexes() const
{
	return inliersIndex;
}

/*
 * Gets the current mean reprojection error when reprojecting model
 * points to scene space with homography
 * @return the current mean reprojection error
 */
double CvRegistrar::getMeanReprojectionError() const
{
	return meanReprojectionError;
}

/*
 * Gets model points converted to 3D Real space (with z = 0) using
 * printScale
 * @return the 3D model points in real space
 */
const vector<Point3f> & CvRegistrar::getInliersModelPoints3D() const
{
	return inliersModelPoints3D;
}

/*
 * Gets the current print scale. Scale factor between model image
 * points and model space points wich depends on the printed model image
 * size.
 * @return the current print scale.
 */
double CvRegistrar::getPrintScale() const
{
	return printScale;
}

/*
 * Set a new printscale for converting model image points to real space
 * points
 * @param printScale the new printscale
 * @return true if printScale have been set and all camera parameters
 * and printscale are correct (acccording to isCameraSet)
 */
bool CvRegistrar::setPrintScale(const double printScale)
{
	if (printScale > 0.0)
	{
		this->printScale = printScale;
	}
	else
	{
		if (verboseLevel > CvProcessor::VERBOSE_ERRORS)
		{
			cerr << "CvRegistrar::setPrintScale(" << printScale
				 << ") : invalid print scale" << endl;
		}
	}

	// Checks if all camera param and printScale are set
	return isCameraSet();
}

/*
 * Sets Camera matrix in order to compute camera pose
 * @param cameraMatrix the new camera matrix
 * @return true if printScale have been set and all camera parameters
 * and printscale are correct (acccording to isCameraSet)
 */
bool CvRegistrar::setCameraMatrix(const Mat & cameraMatrix)
{
	this->cameraMatrix = cameraMatrix;

	// Checks if all camera param and printScale are set
	bool valid = isCameraSet();

	if (!valid)
	{
		if (verboseLevel > CvProcessor::VERBOSE_ERRORS)
		{
			cerr << "CvRegistrar::setCameraMatrix(" << cameraMatrix
				 << ") : Camera is not set yet" << endl;
		}
	}

	return valid;
}

/*
 * Sets new Camera distorsions coefficients
 * @param distortionCoefs the new camera distorsions coefficients
 * @return true if printScale have been set and all camera parameters
 * and printscale are correct (acccording to isCameraSet)
 */
bool CvRegistrar::setDistortionCoefs(const Mat & distortionCoefs)
{
	this->distortionCoefs = distortionCoefs;

	// Checks if all camera param and printScale are set
	bool valid = isCameraSet();

	if (!valid)
	{
		if (verboseLevel > CvProcessor::VERBOSE_ERRORS)
		{
			cerr << "CvRegistrar::setDistortionCoefs(" << distortionCoefs
				 << ") : Camera is not set yet" << endl;
		}
	}

	return valid;
}

/*
 * Indicates whether cameera matrix and camera distorsions coefficients
 * have been set (in order to solve camera pose)
 * @return true if camera intrinsisc parameters matrix and distorsions
 * coefficients have been set, false otherwise
 */
bool CvRegistrar::isCameraSet()
{
	// if camera is not set yet then check it
	if (!cameraSet)
	{
		bool cameraOk = false;
		// Camera matrix should be 3x3 and first elt non zero
		if (!cameraMatrix.empty())
		{
			if (cameraMatrix.size() == Size(3,3))
			{
				if (cameraMatrix.at<float>(0,0) != 0.0)
				{
					cameraOk = true;
				}
			}
		}
		bool distortionOk = false;
		// Distortion coefs should be [4|5|8]x1 and first elt non zero
		// Or empty matrix
		if (distortionCoefs.empty())
		{
			distortionOk = true;
		}
		else
		{
			if ((distortionCoefs.size() == Size(1,4)) ||
				(distortionCoefs.size() == Size(1,5)) ||
				(distortionCoefs.size() == Size(1,8)))
			{
				if (distortionCoefs.at<float>(0,0) != 0.0)
				{
					distortionOk = true;
				}
			}
		}
		bool printScaleOk = false;
		if (printScale > 0.0)
		{
			printScaleOk = true;
		}

		cameraSet = cameraOk && distortionOk && printScaleOk;

	}

	return cameraSet;
}

/*
 * Get the compute camera pose status
 * @return the current camera pose status
 */
bool CvRegistrar::isComputePose() const
{
	return computePose;
}

/*
 * Set a new camera pose computing status
 * @param computePose the new camera pose computing status
 * @return if computePose is set to be true isCameraSet is called first
 * to check all camera parameters and printScale are set correctly
 * So the result might not be equal to computePose if all camera
 * parameters are not set porperly
 */
bool CvRegistrar::setComputePose(const bool computePose)
{
	if (computePose)
	{
		this->computePose = isCameraSet();

		if (!this->computePose)
		{
			if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
			{
				cerr << "Camera pose computation can't be set on without camera "
					 << "parameters and print scale" << endl;
			}
		}
	}
	else
	{
		this->computePose = computePose;
		poseOk = false;
	}

	if (verboseLevel >= CvProcessor::VERBOSE_NOTIFICATIONS)
	{
		clog << "Compute camera pose is " << (computePose ? "on" : "off")
			 << endl;
	}

	resetMeanProcessTime();

	return this->computePose;
}

/*
 * Get the current camera rotation vector computed by solving camera
 * pose
 * @return the current camera pose rotation vector
 */
const Mat & CvRegistrar::getRotationVec() const
{
	return rotationVec;
}

/*
 * Get the current camera translation vector computed by solving camera
 * pose
 * @return the current camera pose rotation vector
 */
const Mat & CvRegistrar::getTranslationVec() const
{
	return translationVec;
}

/*
 * Get the current use previous pose status in pose computing.
 * If usePreviousPose is true then pose computing is initialized
 * with current rotationVec et translationVec and further optimized
 * in pose computing
 * @return the current "use previous pose" status in pose computing
 */
bool CvRegistrar::isUsePreviousPose()
{
	return usePreviousPose;
}

/*
 * Set a new "use previous pose" status in pose computing
 * @param use the new "use previous pose" status
 */
void CvRegistrar::setUsePreviousPose(const bool use)
{
	usePreviousPose = use;

	if (verboseLevel >= CvProcessor::VERBOSE_NOTIFICATIONS)
	{
		clog << "Use previous pose is " << (use ? "on" : "off") << endl;
	}

	resetMeanProcessTime();
}

/*
 * Get computed pose status
 * @return true if number of inliers are greater than 6, camera
 * intrinsic matrix is set and camera pose has been computed, false
 * otherwise
 */
bool CvRegistrar::isPoseOk() const
{
	return poseOk;
}

/*
 * Get the current verbose level
 * @return the current verbose level
 */
CvProcessor::VerboseLevel CvRegistrar::getVerboseLevel() const
{
	return verboseLevel;
}

/*
 * Set new verbose level
 * @param level the new verobse level
 */
void CvRegistrar::setVerboseLevel(const CvProcessor::VerboseLevel level)
{
	if ((level >= CvProcessor::VERBOSE_NONE) &&
		(level < CvProcessor::NBVERBOSELEVEL))
	{
		verboseLevel = level;
	}
}

/*
 * Gets the matching time in ticks or ticks/scene point to match
 * depending on #timePerFeature attibute
 * @return number of ticks used to process current image in absolute
 * time or time per matched points depending on #timePerFeature attribute
 * @see #timePerFeature
 */
double CvRegistrar::getProcessTime() const
{
	if (timePerFeature)
	{
		return (double)processTime / (double)MAX(1,nbInliers);
	}
	else
	{
		return (double)processTime;
	}
}

/*
 * Gets the mean registration time in ticks or ticks/inliers points
 * depending on #timePerFeature attibute
 * @return mean number of ticks used to process current image in absolute
 * time or time per inliers points depending on #timePerFeature attribute
 * @see #timePerFeature
 */
double CvRegistrar::getMeanProcessTime() const
{
	if (timePerFeature)
	{
		return meanProcessTime.mean() / (double)MAX(1,nbInliers);
	}
	else
	{
		return meanProcessTime.mean();
	}
}

/*
 * Gets the registration time stddev in ticks or ticks/inliers points
 * depending on #timePerFeature attibute
 * @return number of ticks deviation from mean used to process current
 * image in absolute time or time per inliers points
 */
double CvRegistrar::getStdProcessTime() const
{
	if (timePerFeature)
	{
		return meanProcessTime.std() / (double)MAX(1,nbInliers);
	}
	else
	{
		return meanProcessTime.std();
	}
}

/*
 * Reset mean and std process time to 0
 */
void CvRegistrar::resetMeanProcessTime()
{
	meanProcessTime.reset();
}


/*
 * Indicates if matching time is per matched points in the current
 * image or absolute
 * @return
 */
bool CvRegistrar::isTimePerFeature() const
{
	return timePerFeature;
}

/*
 * Sets Time per matched point processing time unit
 * @param value the time per feature value (true or false)
 */
void CvRegistrar::setTimePerFeature(const bool value)
{
	timePerFeature = value;
}

