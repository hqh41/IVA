/*
 * CvRegistrar.h
 *
 *  Created on: 27 mars 2012
 *	  Author: davidroussel
 */

#ifndef CVREGISTRAR_H_
#define CVREGISTRAR_H_

#include <vector>
#include <ctime>	// for clock_t
using namespace std;

#include <opencv2/core/core.hpp>	// Mat, Point2f
using namespace cv;

#include "CvProcessor.h"	// for verboseLevel
#include "Pose.h"

/**
 * OpenCV class to register points detected in a model image against
 * coplanar points detected in a scene image:
 * 	- We suppose these two sets of points have already been matched together
 * 	with a matcher such as CvMatcher.
 * 	- If the number of points is greater than 4 we can compute an homography
 * 	between these two sets of points and then appluy this homography on model
 * 	points to see where they project on the scene image.
 * 	We can the compare reprojected model points and scene points to remove
 * 	outliers model reprojected points that projects too far away from scene
 * 	points. Hence getting a subset of inliers points that project correctly
 * 	on the scene image with homography.
 * 	- If we know the size of the printed model in the scene space then we can
 * 	convert model points to real scale 3D points lying on a z=0 plane.
 * 	- If the number of points is greater than 6 AND if camera intrinsic
 * 	parameters are available (from camera calibration), then we can compute
 * 	the camera extrinsic parameters (pose and orientation of the camera
 * 	relative to the printed model)
 * @author David Roussel
 * @date 2012/03/27
 */
class CvRegistrar
{
	protected:
		/**
		 * Model image points to register on scene points
		 */
		vector<Point2f> * modelPoints;

		/**
		 * Scene image points to register with model points
		 */
		vector<Point2f> * scenePoints;

		/**
		 * Number of points in model and scene points
		 */
		size_t nbPoints;

		/**
		 * Homography to compute.
		 * Homography contains the transformation to apply on model points
		 * to find them in scene points.
		 */
		Mat homography;

		/**
		 * Indicates homography has been succesfully computed.
		 * So 2D Model points can be reprojected to Scene space
		 */
		bool homographyOk;

		/**
		 * Model points reprojected on scene space with homography
		 */
		vector<Point2f> reprojModelPoints;

		/**
		 * Reprojection threshold error distance to consider inliers
		 * from outliers
		 */
		double reprojThreshold;

		/**
		 * Maximum reprojection error threshold [10 pixels]
		 */
		static const double reprojThresholdMax;

		/**
		 * Number of inliers when reprojectin model points on scene space
		 * with homography.
		 * Inliers are reprojected points closer than reprojThreshold.
		 */
		int nbInliers;

		/**
		 * Indices of inliers points based on scene points reprojected on
		 * scene image.
		 */
		vector<int> inliersIndex;

		/**
		 * Mean reprojection error when reprojecting model points on scene
		 * space whith computed homography
		 */
		double meanReprojectionError;

		/**
		 * Inliers Model points converted to scene space by scaling model inliers
		 * image points with printScale.
		 * Used to solve camera pose by using 3D/2D correspondences between
		 * these points and inliers scene points (2D)
		 */
		vector<Point3f> inliersModelPoints3D;

		/**
		 * Inliers scene points.
		 * Used to solve camera pose by using 2D/3D correspondences between
		 * these points and inliers mode points scaled to printed model (3D)
		 */
		vector<Point2f> inliersScenePoints2D;

		/**
		 * Indicates if camera pose should be computed or not.
		 * if computePose is true then printScale, cameraMatrix and
		 * distortionCoefs must be set in order to compute camera pose
		 */
		bool computePose;

		/**
		 * PrintScale : the ratio to apply on model points pixel values
		 * to obtain model points paper scale values in order to transform
		 * model image points to real scale mode points and solve camera pose
		 * with 2D scene images points / 3D model points correspondances.
		 */
		double printScale;

		/**
		 * Camera Matrix (if any)
		 */
		Mat cameraMatrix;

		/**
		 * Distortion coefs (if any)
		 */
		Mat distortionCoefs;

		/**
		 * Indicates Camera matrix is set and print scale is valid so
		 * pose can be estimated
		 */
		bool cameraSet;

		/**
		 * Extrinsic rotation vector obtained from estimating pose
		 */
		Mat rotationVec;

		/**
		 * Extrinsic translation vector obtained from estimating pose
		 */
		Mat translationVec;

		/**
		 * If true the previous computed pose (rotationVec and translationVec)
		 * is used to initialize pose computing and further optimized by
		 * pose computing
		 */
		bool usePreviousPose;

		/**
		 * Indicates camera pose has been successfully computed.
		 * So 3D points can be reprojected to Scene space
		 */
		bool poseOk;

		/**
		 * Current pose as obtained by solvePNP
		 */
		Pose currentPose;

		/**
		 * Verbose level to show messages
		 */
		CvProcessor::VerboseLevel verboseLevel;

		/**
		 * Time in ticks/scene point used to:
		 *	- compute homography between model points and scene points
		 *	- compute camera pose from 3D/2D inliers points correspondances
		 */
		clock_t processTime;

		/**
		 * Mean/std Time in ticks/scene point used to:
		 *	- compute homography between model points and scene points
		 *	- compute camera pose from 3D/2D inliers points correspondances
		 */
		MeanValue<clock_t, double> meanProcessTime;

		/**
		 * Indicates if time should be measured per matched point or in absolute
		 * time.
		 */
		bool timePerFeature;

		/**
		 * Registration time in ticks/inlier point.
		 * registration time includes computing the homography between
		 * model and scene + evt solving camera pose.
		 */
		double registrationTime;

	public:
		/**
		 * Registrar constructor
		 * @param modelPoints model matched points from matcher
		 * @param scenePoints scene matched points from matcher
		 * @param reprojectionError maximum reprojection error to sort model
		 * points reprojected in scene space as outliers or inliers
		 * @param computePose should pose be computed.
		 * In such case the three next parameters should be also set
		 * @param printSize Print scale relating model image points to
		 * printed model real scale points
		 * @param cameraMatrix camera calibration intrinsic coefs matrix
		 * @param distortionCoefs camera calibration distotion coefs matrix
		 */
		CvRegistrar(vector<Point2f> * modelPoints = NULL,
					vector<Point2f> * scenePoints = NULL,
					const double reprojectionError = 3.0,
					const bool computePose = false,
					double printSize = 0.0,
					const Mat & cameraMatrix = Mat(),
					const Mat & distortionCoefs = Mat());

		/**
		 * Registrar destructor
		 */
		virtual ~CvRegistrar();

		/**
		 * Find homography and/or camera pose from 2D scene points and 3D
		 * model points correspondances
		 */
		virtual void update();

		/**
		 * Conditional update.
		 * launch #update only if condition is true
		 * @param condition
		 */
		virtual void update(const bool condition);

		/**
		 * Compute homography.
		 * Needs to be reimplemented in subclasses to send signal when done
		 */
		virtual void homographyComputing();

		/**
		 * Compute camera pose.
		 * Needs to be reimplemented in subclasses to send signal when done
		 */
		virtual void poseComputing();

		/**
		 * Get current pose
		 * @return the current pose
		 */
		const Pose & getPose() const;

		/**
		 * Reproject model points into scene points by applying an homography
		 * on them
		 * @param points points vector to be reprojected (points.size() = N)
		 * @param rPoints points transformed by homography
		 */
		void reprojectPoints2D(const vector<Point2f> & points,
							   vector<Point2f> & rPoints);

		/**
		 * Reproject 3D points from Model to 2D point in image using extrinsic
		 * parameters matrix from pose evaluation and intrinsic parameters
		 * matrix from calibration
		 * @param points3D 3D points vector to project
		 * @param pose the camera pose (position/orientation) to use to reproject
		 * 3D points to 2D points
		 * @param points2D 2D projected points vector
		 */
		void reprojectPoints3D(const vector<Point3f> & points3D,
							   const Pose & pose,
							   vector<Point2f> & points2D);

		/**
		 * Set model image poinst
		 * @param modelPoints the new model image points
		 */
		virtual void setModelPoints(vector<Point2f> *modelPoints);

		/**
		 * Set scene image points
		 * @param scenePoints the new scene image points
		 */
		virtual void setScenePoints(vector<Point2f> *scenePoints);

		/**
		 * Gets the number of points in model and scene points
		 * @return the number of points in model and scene points
		 */
		size_t getNbPoints() const;

		/**
		 * Get the current homography
		 * @return the current homography
		 * @note default homography might be identity if no bomography has
		 * been computed yet
		 */
		const Mat & getHomography() const;

		/**
		 * Get computed homography status
		 * @return true if homography has been computed, false if homography
		 * has not been computed yet or if there ise not enough points
		 * to compute homography (we need at least 4 points to compute
		 * homography)
		 */
		bool isHomographyOk() const;

		/**
		 * Gets model points reprojected in scene space by homography
		 * @return the model points reprojected in scene space by homography
		 */
		const vector<Point2f> & getReprojModelPoints() const;

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
		 * Get the maximum reprojection error threshold to sort oultliers from
		 * inliers
		 * @return the maximum reprojection error threshold
		 */
		static double getReprojThresholdMax();

		/**
		 * Get the number of inliers after reprojecting model points to
		 * scene space
		 * @return the number of inliers
		 */
		int getNbInliers() const;

		/**
		 * Gets the indices of inliers points amongst model and scene points
		 * in order to extract inliers points from these two sets
		 * @return the indices of inliers points amongst model and scene points
		 */
		const vector<int> & getInliersIndexes() const;

		/**
		 * Gets the current mean reprojection error when reprojecting model
		 * points to scene space with homography
		 * @return the current mean reprojection error
		 */
		double getMeanReprojectionError() const;

		/**
		 * Gets model points converted to 3D Real space (with z = 0) using
		 * printScale
		 * @return the 3D model points in real space
		 */
		const vector<Point3f> & getInliersModelPoints3D() const;

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
		 * Sets Camera matrix in order to compute camera pose
		 * @param cameraMatrix the new camera matrix
		 * @return true if camera matrix have been set and all camera parameters
		 * and printscale are correct (acccording to isCameraSet)
		 */
		virtual bool setCameraMatrix(const Mat & cameraMatrix);

		/**
		 * Sets new Camera distorsions coefficients
		 * @param distortionCoefs the new camera distorsions coefficients
		 * @return true if distortions have been set and all camera parameters
		 * and printscale are correct (acccording to isCameraSet)
		 */
		virtual bool setDistortionCoefs(const Mat & distortionCoefs);

//		/**
//		 * Checks camera matrix is set (along with distortion coefs) and
//		 * printScale is valid so pose computation could be computed
//		 * @return true if camera matrix (and evt distortion coefs) is set
//		 * and printScale is valie
//		 * @post set cameraSet attribute
//		 */
//		bool checkCameraSet();

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
		 * Get the current camera rotation vector computed by solving camera
		 * pose
		 * @return the current camera pose rotation vector
		 */
		const Mat & getRotationVec() const;

		/**
		 * Get the current camera translation vector computed by solving camera
		 * pose
		 * @return the current camera pose rotation vector
		 */
		const Mat & getTranslationVec() const;

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

		/**
		 * Get computed pose status
		 * @return true if number of inliers are greater than 6, camera
		 * intrinsic matrix is set and camera pose has been computed, false
		 * otherwise
		 */
		bool isPoseOk() const;

		/**
		 * Get the current verbose level
		 * @return the current verbose level
		 */
		CvProcessor::VerboseLevel getVerboseLevel() const;

		/**
		 * Set new verbose level
		 * @param level the new verobse level
		 */
		virtual void setVerboseLevel(const CvProcessor::VerboseLevel level);

		/**
		 * Gets the registration time in ticks or ticks/inliers points
		 * depending on #timePerFeature attibute
		 * @return number of ticks used to process current image in absolute
		 * time or time per inliers points depending on #timePerFeature attribute
		 * @see #timePerFeature
		 */
		double getProcessTime() const;

		/**
		 * Gets the mean registration time in ticks or ticks/inliers points
		 * depending on #timePerFeature attibute
		 * @return mean number of ticks used to process current image in absolute
		 * time or time per inliers points depending on #timePerFeature attribute
		 * @see #timePerFeature
		 */
		double getMeanProcessTime() const;

		/**
		 * Gets the registration time stddev in ticks or ticks/inliers points
		 * depending on #timePerFeature attibute
		 * @return number of ticks deviation from mean used to process current
		 * image in absolute time or time per inliers points
		 */
		double getStdProcessTime() const;

		/**
		 * Reset mean and std process time to 0
		 */
		void resetMeanProcessTime();

		/**
		 * Indicates if matching time is per matched points in the current
		 * image or absolute
		 * @return
		 */
		bool isTimePerFeature() const;

		/**
		 * Sets Time per matched point processing time unit
		 * @param value the time per feature value (true or false)
		 */
		virtual void setTimePerFeature(const bool value);
};

#endif /* CVREGISTRAR_H_ */
