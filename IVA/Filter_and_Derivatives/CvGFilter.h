/*
 * CvGFilter.h
 *
 *  Created on: 26 févr. 2012
 *      Author: davidroussel
 */

#ifndef CVGFILTER_H_
#define CVGFILTER_H_

#include "CvProcessor.h"

/**
 * Class to process source image with gaussian filters
 */
class CvGFilter: virtual public CvProcessor
{
	public:

		/**
		 * Image Display type
		 */
		typedef enum
		{
			INPUT_IM = 0, //!< Input image
			GRAY_IM, //!< Input gray image
			BLURRED_IM, //!< Gaussian Blurred gray image
			GRADIENT_X_IM, //!< Horizontal gradient component
			GRADIENT_Y_IM, //!< Vertical gradient component
			GRADIENT_MAG_IM, //!< Gradient Magnitude
			GRADIENT_ANGLE_IM, //!< Gradient angle
			EDGE_MAP_IM, //!< Edge Map from mag thresholding
			LAPLACIAN_IM, //!< Laplacian
			CORNERNESS_IM, //!< Cornerness measure
			HARRISCORNER_IM, //!< OpenCV Harris Cornerness measure
			NBDISPLAY_IM //!< Number of elements in this enum
		} ImageDisplay;

		typedef enum
		{
			THRESHOLD = 0, //!< Show only edge map from gradient magnitude threshold
			CANNY, //!< Show only Canny's edge map
			MERGED, //!< Show merged edge maps
			NBEDGEDISPLAY //!< Number of elements in this enum
		} EdgeDisplay;

	protected:
		/**
		 * Size of all processed images: sourceImage->size()
		 */
		Size dim;

		/**
		 * image processing result type: CV_32FC1 or CV_64FC1
		 */
		int procType;

		/**
		 * image processing result type for display images: CV_8UC1
		 */
		int displayType;

		/**
		 * Source image converted to gray
		 */
		Mat inFrameGray;
		// -------------------------------------------------------------------
		// Gaussian kernels parameters
		// -------------------------------------------------------------------
		/**
		 * Gaussian kernel size (3, 5, 7..., 15): 7.
		 * size is \f$(2n+1)\f$ with \f$n \in [1..7]\f$
		 */
		int kernelSize;

		/**
		 * Minimum kernel size: 3
		 */
		static const int minKernelSize;

		/**
		 * Maximum kernel size: 15
		 */
		static const int maxKernelSize;

		/**
		 * Gaussian Variance to apply on gaussian kernel: kernelSize/5.0
		 */
		double sigma;

		/**
		 * Minimum gaussian variance: kernelSize / 20.0
		 */
		double minSigma;

		/**
		 * Maximum gaussian variance : kernelSize / 2.0
		 */
		double maxSigma;

		/**
		 * gaussian variance steps
		 */
		static const double sigmaStep;

		/**
		 * Indicates sigma has changed so gaussian kernels should be
		 * recomputed: true
		 */
		bool sigmaChanged;

		// -------------------------------------------------------------------
		// Threshold for edge map
		// -------------------------------------------------------------------
		/**
		 * Threshold value for edge map: 128
		 */
		int thresholdLevel;

		/**
		 * Minimum threshold value for edge map: 0
		 */
		static const int minThreshold;

		/**
		 * Maximum threshold value for edge map: 255
		 */
		static const int maxThreshold;

		// -------------------------------------------------------------------
		// Harris K constant for cornerness measure
		// -------------------------------------------------------------------
		/**
		 * Harris K constant.
		 * initial value is 0.04
		 */
		double harrisKappa;

		/**
		 * Harris K constant mininal value: 0.04
		 */
		static const double harrisKappaMin;

		/**
		 * Harris K constant maximal value: 0.15
		 */
		static const double harrisKappaMax;

		/**
		 * Harris K constant steps: 0.01
		 */
		static const double harrisKappaStep;

		// -------------------------------------------------------------------
		// Gaussian filters kernels (all kernels are procType)
		// -------------------------------------------------------------------
		/**
		 * Gaussian 1D horizontal filter
		 */
		Mat gX;

		/**
		 * Gaussian 1D vertical filter
		 */
		Mat gY;

		/**
		 * Gaussian horizontal 1st derivative filter: dx
		 */
		Mat gDx;

		/**
		 * Gaussian vertical 1st derivative filter: dy
		 */
		Mat gDy;

		/**
		 * Gaussian horizontal 2nd derivative filter: d2x
		 */
		Mat gD2x;

		/**
		 * Gaussian vertical 2nd derivative filter: d2y
		 */
		Mat gD2y;

		/**
		 * Gaussian horizontal and vertical 1st derivative filter: dxy
		 */
		Mat gDxy;

		/**
		 * 2D Gaussian kernel for Ixx,Iyy and Ixy smoothing in cornerness
		 */
		Mat g2D;

		// -------------------------------------------------------------------
		// Processing images results (all images are procType)
		// -------------------------------------------------------------------
		/**
		 * Image display mode.
		 */
		ImageDisplay displayMode;

		/**
		 * Edge display mode.
		 */
		EdgeDisplay edgeMode;

		/**
		 * Blurred image processed with gaussian vertical and horizontal
		 * kernels
		 */
		Mat blurred;

		/**
		 * Image processed with 1st derivative horizontal gaussian kernel
		 * and vertical gaussian kernel.
		 * Horizontal gradient: \f$ I_{x} \f$
		 */
		Mat dX;

		/**
		 * Image processed with 1st derivative vertical gaussian kernel and
		 * horizontal gaussian kernel.
		 * Vertical gradient: \f$ I_{y} \f$
		 */
		Mat dY;

		/**
		 * Gradient magnitude: \f$ \sqrt{I_{x}^{2} + I_{y}^{2}} \f$
		 */
		Mat gradientMag;

		/**
		 * Gradient angle: \f$ atan(\frac{I_{y}}{I_{x}}) \f$
		 */
		Mat gradientAngle;

		/**
		 * Image processed with horizontal 2nd derivative gaussian kernel and
		 * vertical gaussian kernel. Or eventually Horizontal gradient
		 * processed with 1st derivative horizontal gaussian kernel.
		 * Horizontal laplacian: \f$ I_{x^{2}} \f$
		 */
		Mat d2X;

		/**
		 * Image processed with vertical 2nd derivative gaussian kernel and
		 * horizontal gaussian kernel. Or eventually Vertical gradient
		 * processed with 1st derivative vertical gaussian kernel.
		 * Vertical laplacian: \f$ I_{y^{2}} \f$
		 */
		Mat d2Y;

		/**
		 * Laplacian image: sum of horizontal and vertical laplacian components.
		 * laplacian: \f$ I_{x^{2}} + I_{y^{2}} \f$
		 */
		Mat laplacian;

		/**
		 * dXY component needed by Hessian matrix (in cornerness computing):
		 * \f$ I_{xy} \f$
		 */
		Mat dXY;

		/**
		 * Cornerness image computed according to Harris Measure.
		 * Such as the Hessian matrix : \f[
		 * H =
		 * 	\left(
		 *		\begin{array}{cc}
		 *			I_{x^{2}}	& I_{xy}\\
		 *			I_{yx}	& I_{y^{2}}\\
		 *		\end{array}
		 *	\right)
		 * \f]
		 * Harris measure is \f[
		 * det(H) - k trace(H) = I_{x}^{2} I_{y}^{2} - I_{xy}^{2} - k
		 * \left( I_{x}^{2} + I_{y}^{2} \right)^{2}
		 * \f]
		 */
		Mat cornerness;

		/**
		 * Cornerness image computed directly with OpenCV harris function
		 */
		Mat harris;

		// -------------------------------------------------------------------
		// Processing images results (all images are procType)
		// -------------------------------------------------------------------
		/**
		 * Blurred image converted for display
		 */
		Mat blurredDisplay;

		/**
		 * Horizontal gradient image converted for display
		 */
		Mat dXDisplay;

		/**
		 * Vertical gradient image converted for display
		 */
		Mat dYDisplay;

		/**
		 * Gradient magnitude image converted for display
		 */
		Mat gradientMagDisplay;

		/**
		 * Gradient angle image converted for display
		 */
		Mat gradientAngleDisplay;

		/**
		 * Gradient magnitude display thresholded to show edges
		 */
		Mat edgeMap;

		/**
		 * Laplacian image converted for display
		 */
		Mat laplacianDisplay;

		/**
		 * Cornerness image converted for display
		 */
		Mat cornernessDisplay;

		/**
		 * Canny edges image
		 */
		Mat cannyEdgeMap;

		/**
		 * Edge maps components.
		 * allow to mix inFrameGray, edgeMap and cannyEdge to produce a mmixed
		 * edge image
		 */
		vector<Mat> edgeMapComponents;

		/**
		 * Mixed edges image
		 */
		Mat mixEdge;

		/**
		 * Harris cornerness image converted for display
		 */
		Mat harrisDisplay;

		/**
		 * Setup attributes when source image is changed
		 * @param image source Image
		 * @param completeSetup is true when used to change source image,
		 * and false when used in constructor
		 */
		virtual void setup(Mat *image, bool completeSetup);

		/**
		 * Cleanup attributes before changing source image or cleaning class
		 * before destruction
		 */
		virtual void cleanup();

	public:
		/**
		 * Gaussian filtering class constructor
		 * @param sourceImage
		 */
		CvGFilter(Mat *sourceImage);

		/**
		 * Gaussian filtering class destructor
		 */
		virtual ~CvGFilter();

		/**
		 * Gaussian filtering update
		 * 	- convert source image to gray
		 * 	- if sigma changed recompute gaussian kernels
		 * 	- compute blurred image and convert it for display
		 * 	- compute horizontal and vertical gradients and convert them
		 * 	for display
		 * 	- compute gradient magnitude and angle and convert them for display
		 * 	- threshold gradient magintude to edgeMap
		 * 	- compute horizontal and vertical laplacian components and
		 * 	laplacian image
		 * 	- compute dXY to prepare cornerness measure
		 */
		virtual void update();

		/**
		 * Get current kernel size
		 * @return the current kernel size
		 */
		int getKernelSize() const;

		/**
		 * Sets the a new kernel size
		 * @param kernelSize the new kernel size
		 * @post if new size is in range [3..15]
		 * with a step of 2;
		 * 	- the new kernel size is set up, and remains unchanged otherwise.
		 *	- gaussian kernels are eventually recomputed
		 */
		virtual void setKernelSize(int kernelSize);

		/**
		 * Gets maximum kernel size
		 * @return the maximum kernel size
		 */
		static int getMaxKernelSize();

		/**
		 * Gets minimum kernel size
		 * @return the minimum kernel size
		 */
		static int getMinKernelSize();

		/**
		 * Gets the current value of gaussian variance
		 * @return the current value of gaussian variance
		 */
		double getSigma() const;

		/**
		 * Sets a new value for gaussian variance
		 * @param sigma the new value of gaussian variance
		 */
		virtual void setSigma(double sigma);

		/**
		 * Gets the minimum possible value of gaussian variance
		 * according to kernel size
		 * @return the minimum gaussian variance
		 */
		double getMinSigma() const;

		/**
		 * Gets the maximum possible value of gaussian variance
		 * according to kernel size
		 * @return the maximum gaussian variance
		 */
		double getMaxSigma() const;

		/**
		 * Gets the steps for sigma increments
		 * @return steps for sigma increments
		 */
		static double getSigmaStep();

		/**
		 * Gets the sigma changed status, in order to recompute
		 * gaussian kernels (if needed)
		 * @return true if sigma is different from last update,
		 * false otherwise
		 */
		bool isSigmaChanged() const;

		/**
		 * Gets the current threshold level of edgemap
		 * @return the current threshold level
		 */
		int getThresholdLevel() const;

		/**
		 * Sets new threshold level for edge map
		 * @param thresholdLevel the new threshold level
		 */
		virtual void setThresholdLevel(int thresholdLevel);

		/**
		 * Gets minimum threshold value for edgemap
		 * @return the minimum threshold value for edgemap
		 */
		static int getMinThreshold();

		/**
		 * Gets maximum threshold value for edgemap
		 * @return the maximum threshold value for edgemap
		 */
		static int getMaxThreshold();

		/**
		 * Gets the current Harris parameter Kappa
		 * @return the current value of Kappa
		 */
		double getHarrisKappa() const;

		/**
		 * Sets new Harris parameter Kappa
		 * @param harrisKappa the new parameter to set
		 */
		virtual void setHarrisKappa(double harrisKappa);

		/**
		 * Gets maximum Harris parameter Kappa
		 * @return the maximum Harris parameter Kappa
		 */
		static double getHarrisKappaMax();

		/**
		 * Gets minimum Harris parameter Kappa
		 * @return the minimum Harris parameter Kappa
		 */
		static double getHarrisKappaMin();

		/**
		 * Gets Harris parameter Kappa increment
		 * @return the Harris parameter Kappa increment
		 */
		static double getHarrisKappaStep();

		/**
		 * Get current display mode
		 * @return the current display mode
		 */
		ImageDisplay getDisplayMode() const;

		/**
		 * Sets a new display mode
		 * @param displayMode the new display mode to set
		 */
		virtual void setDisplayMode(const ImageDisplay displayMode);

		/**
		 * Gets the current edge display mode
		 * @return the current edge display mode
		 */
		EdgeDisplay getEdgeMode() const;

		/**
		 * Set a new edge didsplay mode
		 * @param edgeMode the new edge mode
		 */
		void setEdgeMode(const EdgeDisplay edgeMode);

		/**
		 * Gets Image reference corresponding to the current displayMode and
		 * edgeMode
		 * @return Image reference corresponding to the current displayMode and
		 * edgeMode
		 */
		const Mat & getDisplayModeImage();

		/**
		 * Gets Image pointer corresponding to the current displayMode and
		 * edgeMode
		 * @return Image reference corresponding to the current displayMode and
		 * edgeMode
		 */
		Mat * getDisplayModeImagePtr();

	protected:
		// --------------------------------------------------------------------
		// Utility methods
		// --------------------------------------------------------------------
		/**
		 * Compute 1D or 2D normalized gaussian into kernel with sigma variance and
		 * amp amplitude.
		 * \f[
		 * g(x,y) = A \cdot e^{-\left(\frac{\left(x - x_0\right)^2+\left(y - y_0\right)^2}
		 * {2\sigma^2}\right)}
		 * \f]
		 * where \f$ A = \frac{1}{\sum_{y}\sum_{x}g(x,y)}\f$ and
		 * \f$x_0 = floor(\frac{kernel.cols}{2}) + 1\f$ and
		 * \f$y_0 = floor(\frac{kernel.rows}{2}) + 1\f$.
		 * @param kernel matrix to store gaussian kernel:
		 * 	- if kernel size is \f$ 1 \times N\f$ or \f$ N \times 1\f$ produces a 1D
		 * 	line or column filter.
		 * 	- if kernel size is \f$ M \times N\f$ produces a 2D gaussian filter.
		 * @param sigma standard deviation \f$\sigma\f$ of the gauss curve (or surface)
		 * expressed in pixels
		 * @param derivOrderX horizontal derivative order. Should be 0, 1 or 2:
		 * 	- derivOrderX = 1: \f$\frac{\delta g(x,y)}{\delta x}=
		 * 	                      \frac{-(x - x_0)}{\sigma^2}\cdot g(x,y)\f$
		 * 	- derivOrderX = 2: \f$\frac{\delta^2 g(x,y)}{\delta x^2}=
		 * 	                      \frac{(x - x_0)^2 - \sigma^2}{\sigma^4}\cdot g(x,y)\f$
		 * @param derivOrderY vertical derivative order. Should be 0, 1 or 2
		 * 	- derivOrderY = 1: \f$\frac{\delta g(x,y)}{\delta y}=
		 * 	                      \frac{-(y - y_0)}{\sigma^2}\cdot g(x,y)\f$
		 * 	- derivOrderY = 2: \f$\frac{\delta^2 g(x,y)}{\delta y^2}=
		 * 	                      \frac{(y - y_0)^2 - \sigma^2}{\sigma^4}\cdot g(x,y)\f$
		 * @warning kernel size should be odd (2n+1) in order to have an application
		 * point at the center odf the matrix
		 * The type parameter T applied to gaussian2D depends on the type of
		 * the kernel matrix:
		 * 	- if kernel type is CV_64FC1, then you should use
		 * 	gaussian<double>(kernel...)
		 * 	- if kernel type is CV_32FC1, then you should use
		 * 	gaussian<float>(kernel...)
		 * 	- Other kernels Mat types haven't been tested
		 */
		template<typename T>
		void gaussian(Mat & kernel,
					  const double sigma,
					  const unsigned int derivOrderX = 0,
					  const unsigned int derivOrderY = 0);

		/**
		 * Compute Cornerness measure based on Harris criteria.
		 * This criteria is based on the Hessian matrix build upon
		 * 2nd order horizontal and vertical \f$I_{xx} \& I_{xx}\f$ derivatives and
		 * also 1st order cross derivatives \f$I_{xy}\f$.
		 * \f[
		 * H =
		 * \left(
		 * 	\begin{array}{cc}
		 * 		I_{xx} & I_{xy} \\
		 * 		I_{xy} & I_{yy}
		 * 	\end{array}
		 * \right)
		 * \f]
		 * each component of the hessian matrix is fisrt weighted (filtered) by
		 * a weighting kernel (such as gaussian kernel)
		 * \f[
		 * A = \sum_{x} \sum_{y} w(x,y)
		 * \left(
		 * 	\begin{array}{cc}
		 * 		I_{xx} & I_{xy} \\
		 * 		I_{xy} & I_{yy}
		 * 	\end{array}
		 * \right)
		 * =
		 * \left(
		 * 	\begin{array}{cc}
		 * 		\langle I_{xx}\rangle & \langle I_{xy}\rangle \\
		 * 		\langle I_{xy}\rangle & \langle I_{yy}\rangle
		 * 	\end{array}
		 * \right)
		 * \f]
		 * The Harris cornerness measure is then computed by :
		 * \f$det(A) - \kappa \cdot trace(A)^2\f$ with \f$\kappa \in
		 * \left[0.04 \cdots 0.15\right]\f$
		 * which is equivalent to \f$I_{xx}I_{yy} - I_{xy}^{2} + \kappa
		 * \left(I_{xx} + I_{xy}\right)^2\f$
		 *
		 *
		 * An approximate version can be obtained with
		 * \f$det(H) - \kappa \cdot trace(H)^2\f$
		 * @param Ixx Horizontal laplacian
		 * @param Iyy Vertical laplacian
		 * @param Ixy Cross derivatives
		 * @param wKernel weighting kernel (typically a gaussian)
		 * @param Kappa trace Factor
		 * @param dst destination matrix
		 * @note if matrices are CV_64FC1 we should use computeCornerness<double>
		 * @note if matrices are CV_32FC1 we should use computeCornerness<float>
		 */
		template<typename T>
		void computeCornerness(const Mat & Ixx,
							   const Mat & Iyy,
							   const Mat & Ixy,
							   const Mat & wKernel,
							   const double Kappa,
							   Mat & dst);

		/**
		 * Prints info about min and max value of this matrix
		 * @param m the matrix to investigate
		 */
		void minMaxInfo(const Mat & m);
};

#endif /* CVGFILTER_H_ */
