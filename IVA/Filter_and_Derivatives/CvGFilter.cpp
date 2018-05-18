/*
 * CvGFilter.cpp
 *
 *  Created on: 26 févr. 2012
 *      Author: davidroussel
 */

#include <assert.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "CvGFilter.h"

/*
 * Minimum kernel size: 3
 */
const int CvGFilter::minKernelSize = 3;

/*
 * Maximum kernel size: 15
 */
const int CvGFilter::maxKernelSize = 15;

/*
 * gaussian variance steps
 */
const double CvGFilter::sigmaStep = 0.1;

/*
 * Minimum threshold value for edge map: 0
 */
const int CvGFilter::minThreshold = 0;

/*
 * Maximum threshold value for edge map: 255
 */
const int CvGFilter::maxThreshold = 255;

/*
 * Harris K constant mininal value: 0.04
 */
const double CvGFilter::harrisKappaMin = 0.04;

/*
 * Harris K constant maximal value: 0.15
 */
const double CvGFilter::harrisKappaMax = 0.15;

/*
 * Harris K constant steps: 0.01
 */
const double CvGFilter::harrisKappaStep = 0.01;

/*
 * Gaussian filtering class constructor
 * @param sourceImage
 */
CvGFilter::CvGFilter(Mat * sourceImage) :
	CvProcessor(sourceImage),
	dim(sourceImage->size()),
	procType(CV_64FC1),
	displayType(CV_8UC1),
	inFrameGray(dim, displayType, Scalar(0)),
	kernelSize(7),
	sigma((double) kernelSize/5.0),
	minSigma((double) kernelSize / 20.0),
	maxSigma((double) kernelSize / 2.0),
	sigmaChanged(true),
	thresholdLevel(128),
	harrisKappa(harrisKappaMin),
	gX(1, kernelSize, procType, Scalar(0)),
	gY(kernelSize, 1, procType, Scalar(0)),
	gDx(1, kernelSize, procType, Scalar(0)),
	gDy(kernelSize, 1, procType, Scalar(0)),
	gD2x(1, kernelSize, procType, Scalar(0)),
	gD2y(kernelSize, 1, procType, Scalar(0)),
	gDxy(kernelSize, 1, procType, Scalar(0)),
	g2D(kernelSize, kernelSize, procType, Scalar(0)),
	displayMode(INPUT_IM),
	edgeMode(THRESHOLD),
	blurred(dim, procType, Scalar(0)),
	dX(dim, procType, Scalar(0)),
	dY(dim, procType, Scalar(0)),
	gradientMag(dim, procType, Scalar(0)),
	gradientAngle(dim, procType, Scalar(0)),
	d2X(dim, procType, Scalar(0)),
	d2Y(dim, procType, Scalar(0)),
	laplacian(dim, procType, Scalar(0)),
	dXY(dim, procType, Scalar(0)),
	cornerness(dim, procType, Scalar(0)),
	harris(dim, procType, Scalar(0)),
	blurredDisplay(dim, displayType, Scalar(0)),
	dXDisplay(dim, displayType, Scalar(0)),
	dYDisplay(dim, displayType, Scalar(0)),
	gradientMagDisplay(dim, displayType, Scalar(0)),
	gradientAngleDisplay(dim, displayType, Scalar(0)),
	edgeMap(dim, displayType, Scalar(0)),
	laplacianDisplay(dim, displayType, Scalar(0)),
	cornernessDisplay(dim, displayType, Scalar(0)),
	cannyEdgeMap(dim, displayType, Scalar(0)),
	mixEdge(dim, CV_8UC3, Scalar(0, 0, 0)),
	harrisDisplay(dim, displayType, Scalar(0))

{
	setup(sourceImage, false);

	// Adds named image to additional images map
	addImage("gray", &inFrameGray);
	addImage("blurred", &blurredDisplay);
	addImage("dx", &dXDisplay);
	addImage("dy", &dYDisplay);
	addImage("gradientmag", &gradientMagDisplay);
	addImage("gradientangle", &gradientAngleDisplay);
	addImage("edgemap", &edgeMap);
	addImage("laplacian", &laplacianDisplay);
	addImage("cornerness", &cornernessDisplay);
	addImage("canny", &cannyEdgeMap);
	addImage("mixedges", &mixEdge);
	addImage("harris", &harrisDisplay);
}

/*
 * Gaussian filtering class destructor
 */
CvGFilter::~CvGFilter()
{
	cleanup();
}

/*
 * Setup attributes when source image is changed
 * @param image source Image
 * @param completeSetup is true when used to change source image,
 * and false when used in constructor
 */
void CvGFilter::setup(Mat *image, bool completeSetup)
{
	assert (image != NULL);

	CvProcessor::setup(image, completeSetup);

	if (completeSetup) // complete setup
	{
		dim = sourceImage->size();
		inFrameGray = Mat(dim, displayType, Scalar(0));
		CvGFilter::setKernelSize(7);
		thresholdLevel = 128;
		harrisKappa = harrisKappaMin;
		displayMode = INPUT_IM;
		edgeMode = THRESHOLD;
		blurred = Mat(dim, procType, Scalar(0));
		dX = Mat(dim, procType, Scalar(0));
		dY = Mat(dim, procType, Scalar(0));
		gradientMag = Mat(dim, procType, Scalar(0));
		gradientAngle = Mat(dim, procType, Scalar(0));
		d2X = Mat(dim, procType, Scalar(0));
		d2Y = Mat(dim, procType, Scalar(0));
		laplacian = Mat(dim, procType, Scalar(0));
		dXY = Mat(dim, procType, Scalar(0));
		cornerness = Mat(dim, procType, Scalar(0));
		harris = Mat(dim, procType, Scalar(0));
		blurredDisplay = Mat(dim, displayType, Scalar(0));
		dXDisplay = Mat(dim, displayType, Scalar(0));
		dYDisplay = Mat(dim, displayType, Scalar(0));
		gradientMagDisplay = Mat(dim, displayType, Scalar(0));
		gradientAngleDisplay = Mat(dim, displayType, Scalar(0));
		edgeMap = Mat(dim, displayType, Scalar(0));
		laplacianDisplay = Mat(dim, displayType, Scalar(0));
		cornernessDisplay = Mat(dim, displayType, Scalar(0));
		cannyEdgeMap = Mat(dim, displayType, Scalar(0));
		mixEdge = Mat(dim, CV_8UC3, Scalar(0, 0, 0));
		harrisDisplay = Mat(dim, displayType, Scalar(0));
	}
	else // during constructor only
	{

	}

	// in any cases
	edgeMapComponents.push_back(inFrameGray);
	edgeMapComponents.push_back(edgeMap);
	edgeMapComponents.push_back(cannyEdgeMap);

}

/*
 * Cleanup attributes before changing source image or cleaning class
 * before destruction
 */
void CvGFilter::cleanup()
{
	vector<Mat>::iterator it = edgeMapComponents.begin();
	for (; it != edgeMapComponents.end(); ++it)
	{
		(*it).release();
	}
	edgeMapComponents.clear();

	harrisDisplay.release();
	mixEdge.release();
	cannyEdgeMap.release();
	cornernessDisplay.release();
	laplacianDisplay.release();
	edgeMap.release();
	gradientAngleDisplay.release();
	gradientMagDisplay.release();
	dYDisplay.release();
	dXDisplay.release();
	blurredDisplay.release();
	harris.release();
	cornerness.release();
	dXY.release();
	laplacian.release();
	d2Y.release();
	d2X.release();
	gradientAngle.release();
	gradientMag.release();
	dY.release();
	dX.release();
	blurred.release();
	inFrameGray.release();
}

/*
 * Get current kernel size
 * @return the current kernel size
 */
int CvGFilter::getKernelSize() const
{
	return kernelSize;
}

/*
 * Sets the a new kernel size
 * @param kernelSize the new kernel size
 * @post if new size is in range [3..15]
 * with a step of 2;
 * 	- the new kernel size is set up, and remains unchanged otherwise.
 *	- gaussian kernels are eventually recomputed
 */
void CvGFilter::setKernelSize(int kernelSize)
{
	if (this->kernelSize != kernelSize)
	{
		g2D.release();
		gDxy.release();
		gD2y.release();
		gD2x.release();
		gDy.release();
		gDx.release();
		gY.release();
		gX.release();

		// Kernel size should be odd
		if (((kernelSize - 1)%2) != 0)
		{
			kernelSize++;
		}

		if (kernelSize > maxKernelSize)
		{
			this->kernelSize = maxKernelSize;
		}
		else if (kernelSize < minKernelSize)
		{
			this->kernelSize = minKernelSize;
		}
		else
		{
			this->kernelSize = kernelSize;
		}

		sigma = (double) kernelSize/5.0;
		minSigma = (double) kernelSize / 20.0;
		maxSigma = (double) kernelSize / 2.0;
		sigmaChanged = true;

		gX = Mat(1, this->kernelSize, procType, Scalar(0));
		gY = Mat(this->kernelSize, 1, procType, Scalar(0));
		gDx = Mat(1, this->kernelSize, procType, Scalar(0));
		gDy = Mat(this->kernelSize, 1, procType, Scalar(0));
		gD2x = Mat(1, this->kernelSize, procType, Scalar(0));
		gD2y = Mat(this->kernelSize, 1, procType, Scalar(0));
		gDxy = Mat(this->kernelSize, 1, procType, Scalar(0));
		g2D = Mat(this->kernelSize, this->kernelSize, procType, Scalar(0));

		sigmaChanged = true;
	}
}

/*
 * Gets maximum kernel size
 * @return the maximum kernel size
 */
int CvGFilter::getMaxKernelSize()
{
	return maxKernelSize;
}

/*
 * Gets minimum kernel size
 * @return the minimum kernel size
 */
int CvGFilter::getMinKernelSize()
{
	return minKernelSize;
}

/*
 * Gets the current value of gaussian variance
 * @return the current value of gaussian variance
 */
double CvGFilter::getSigma() const
{
	return sigma;
}

/*
 * Sets a new value for gaussian variance
 * @param sigma the new value of gaussian variance
 */
void CvGFilter::setSigma(double sigma)
{
	if (sigma < minSigma)
	{
		this->sigma = minSigma;
	}
	else if (sigma > maxSigma)
	{
		this->sigma = maxSigma;
	}
	else
	{
		this->sigma = sigma;
	}
	sigmaChanged = true;
}

/*
 * Gets the minimum possible value of gaussian variance
 * according to kernel size
 * @return the minimum gaussian variance
 */
double CvGFilter::getMinSigma() const
{
	return minSigma;
}

/*
 * Gets the maximum possible value of gaussian variance
 * according to kernel size
 * @return the maximum gaussian variance
 */
double CvGFilter::getMaxSigma() const
{
	return maxSigma;
}

/*
 * Gets the steps for sigma increments
 * @return steps for sigma increments
 */
double CvGFilter::getSigmaStep()
{
	return sigmaStep;
}

/*
 * Gets the sigma changed status, in order to recompute
 * gaussian kernels (if needed)
 * @return true if sigma is different from last update,
 * false otherwise
 */
bool CvGFilter::isSigmaChanged() const
{
	return sigmaChanged;
}

/*
 * Gets the current threshold level of edgemap
 * @return the current threshold level
 */
int CvGFilter::getThresholdLevel() const
{
	return thresholdLevel;
}

/*
 * Sets new threshold level for edge map
 * @param thresholdLevel the new threshold level
 */
void CvGFilter::setThresholdLevel(int thresholdLevel)
{
	if (thresholdLevel < minThreshold)
	{
		this->thresholdLevel = minThreshold;
	}
	else if (thresholdLevel > maxThreshold)
	{
		this->thresholdLevel = maxThreshold;
	}
	else
	{
		this->thresholdLevel = thresholdLevel;
	}
}

/*
 * Gets minimum threshold value for edgemap
 * @return the minimum threshold value for edgemap
 */
int CvGFilter::getMinThreshold()
{
	return minThreshold;
}

/*
 * Gets maximum threshold value for edgemap
 * @return the maximum threshold value for edgemap
 */
int CvGFilter::getMaxThreshold()
{
	return maxThreshold;
}

/*
 * Gets the current Harris parameter Kappa
 * @return the current value of Kappa
 */
double CvGFilter::getHarrisKappa() const
{
	return harrisKappa;
}

/*
 * Sets new Harris parameter Kappa
 * @param harrisKappa the new parameter to set
 */
void CvGFilter::setHarrisKappa(double harrisKappa)
{
	if (harrisKappa > harrisKappaMax)
	{
		this->harrisKappa = harrisKappaMax;
	}
	else if (harrisKappa < harrisKappaMin)
	{
		this->harrisKappa = harrisKappaMin;
	}
	else
	{
		this->harrisKappa = harrisKappa;
	}
}

/*
 * Gets maximum Harris parameter Kappa
 * @return the maximum Harris parameter Kappa
 */
double CvGFilter::getHarrisKappaMax()
{
	return harrisKappaMax;
}

/*
 * Gets minimum Harris parameter Kappa
 * @return the minimum Harris parameter Kappa
 */
double CvGFilter::getHarrisKappaMin()
{
	return harrisKappaMin;
}

/*
 * Gets Harris parameter Kappa increment
 * @return the Harris parameter Kappa increment
 */
double CvGFilter::getHarrisKappaStep()
{
	return harrisKappaStep;
}

/*
 * Get current display mode
 * @return the current display mode
 */
CvGFilter::ImageDisplay CvGFilter::getDisplayMode() const
{
	return displayMode;
}

void CvGFilter::setDisplayMode(const ImageDisplay displayMode)
{
	if ((displayMode >= INPUT_IM) && (displayMode < NBDISPLAY_IM))
	{
		this->displayMode = displayMode;
	}
	else
	{
		cerr << "display mode out of range: " << displayMode << endl;
	}
}

/*
 * Gets the current edge display mode
 * @return the current edge display mode
 */
CvGFilter::EdgeDisplay CvGFilter::getEdgeMode() const
{
	return edgeMode;
}

/*
 * Set a new edge didsplay mode
 * @param edgeMode the new edge mode
 */
void CvGFilter::setEdgeMode(const EdgeDisplay edgeMode)
{
	if ( (edgeMode >= THRESHOLD) && (edgeMode < NBEDGEDISPLAY))
	{
		this->edgeMode = edgeMode;
	}
	else
	{
		cerr << "edge mode out of range: " << edgeMode << endl;
	}
}

/*
 * Gets Image reference corresponding to the current displayMode and
 * edgeMode
 * @return Image reference corresponding to the current displayMode and
 * edgeMode
 */
const Mat & CvGFilter::getDisplayModeImage()
{
	switch (this->displayMode)
	{
		case INPUT_IM:
			return getImage("source");
			break;
		case GRAY_IM:
			return getImage("gray");
			break;
		case BLURRED_IM:
			return getImage("blurred");
			break;
		case GRADIENT_X_IM:
			return getImage("dx");
			break;
		case GRADIENT_Y_IM:
			return getImage("dy");
			break;
		case GRADIENT_MAG_IM:
			return getImage("gradientmag");
			break;
		case GRADIENT_ANGLE_IM:
			return getImage("gradientangle");
			break;
		case EDGE_MAP_IM:
			switch (edgeMode)
			{
				case THRESHOLD:
					return getImage("edgemap");
					break;
				case CANNY:
					return getImage("canny");
					break;
				case MERGED:
				case NBEDGEDISPLAY:
				default:
					return getImage("mixedges");
					break;
			}
			break;
		case LAPLACIAN_IM:
			return getImage("laplacian");
			break;
		case CORNERNESS_IM:
			return getImage("cornerness");
			break;
		case HARRISCORNER_IM:
			return getImage("harris");
			break;
		case NBDISPLAY_IM:
		default:
			break;
	}

	// by default return source
	return getImage("source");
}

/*
 * Gets Image pointer corresponding to the current displayMode and
 * edgeMode
 * @return Image reference corresponding to the current displayMode and
 * edgeMode
 */
Mat * CvGFilter::getDisplayModeImagePtr()
{
	switch (this->displayMode)
	{
		case INPUT_IM:
			return getImagePtr("source");
			break;
		case GRAY_IM:
			return getImagePtr("gray");
			break;
		case BLURRED_IM:
			return getImagePtr("blurred");
			break;
		case GRADIENT_X_IM:
			return getImagePtr("dx");
			break;
		case GRADIENT_Y_IM:
			return getImagePtr("dy");
			break;
		case GRADIENT_MAG_IM:
			return getImagePtr("gradientmag");
			break;
		case GRADIENT_ANGLE_IM:
			return getImagePtr("gradientangle");
			break;
		case EDGE_MAP_IM:
			switch (edgeMode)
			{
				case THRESHOLD:
					return getImagePtr("edgemap");
					break;
				case CANNY:
					return getImagePtr("canny");
					break;
				case MERGED:
				case NBEDGEDISPLAY:
				default:
					return getImagePtr("mixedges");
					break;
			}
			break;
		case LAPLACIAN_IM:
			return getImagePtr("laplacian");
			break;
		case CORNERNESS_IM:
			return getImagePtr("cornerness");
			break;
		case HARRISCORNER_IM:
			return getImagePtr("harris");
			break;
		case NBDISPLAY_IM:
		default:
			break;
	}
	// by default return source
	return getImagePtr("source");

}

/*
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
void CvGFilter::update()
{
	// --------------------------------------------------------------------
	// convert image to gray
	// --------------------------------------------------------------------
	cvtColor(*sourceImage, inFrameGray, CV_BGR2GRAY);

	// --------------------------------------------------------------------
	// recompute filters kernels if sigma has changed
	// --------------------------------------------------------------------
	if (sigmaChanged)
	{
		// Gaussian 1D horizontal filter
		// TODO gaussian<double> (gX, ...);
        gaussian<double> (gX,sigma,0,0);

		// Gaussian 1D vertical filter
		// TODO gaussian<double> (gY, ...);
        gaussian<double> (gY,sigma,0,0);

		// Gaussian horizontal 1st derivative filter: dx
		// TODO gaussian<double> (gDx, ...);
        gaussian<double> (gDx,sigma,1,0);

		// Gaussian vertical 1st derivative filter: dy
		// TODO gaussian<double> (gDy, sigma, 0, 1);
        gaussian<double> (gDy, sigma, 0, 1);

		// Gaussian horizontal and vertical 1st derivative filter: dxy
		// TODO gaussian<double> (gDxy, ...);
        gaussian<double> (gDxy,sigma,1,1);

		// 2D Gaussian kernel for Ixx,Iyy and Ixy smoothing in cornerness
		// with 2*sigma+1 sigma
		// TODO gaussian<double> (g2D, ...);
        //gaussian<double> (g2D,);

		sigmaChanged = false;
	}

	// ------------------------------------------------------------------------
	// Compute blurred image
	// ------------------------------------------------------------------------
	if (displayMode == BLURRED_IM ||
		displayMode == EDGE_MAP_IM ||
		displayMode == HARRISCORNER_IM)
	{
		// Compute gaussian blurred image inFrameGray --> blurred
		// TODO sepFilter2D(...);
        sepFilter2D(inFrameGray,blurred,blurred.depth(),gX,gY);

		// Convert blurred image for display or other purpose
		convertScaleAbs(blurred, blurredDisplay);
	}

	// ------------------------------------------------------------------------
	// Compute gradients
	// ------------------------------------------------------------------------
	if (displayMode >= GRADIENT_X_IM && displayMode <=LAPLACIAN_IM)
	{
		// Compute horizontal gradient: inFrameGray --> dX
		// TODO sepFilter2D(...);
        sepFilter2D(inFrameGray,dX,dX.depth(),gDx,gY);

		// Compute vertical gradient: inFrameGray --> dY
		// TODO sepFilter2D(...);
        sepFilter2D(inFrameGray,dY,dY.depth(),gX,gDy);
	}

	// ------------------------------------------------------------------------
	// Converts horizontal gradient for display
	// ------------------------------------------------------------------------
	if (displayMode == GRADIENT_X_IM)
	{
		// convert horizontal gradient for display
		dX.convertTo(dXDisplay,dXDisplay.type(),0.5,128);
	}

	// ------------------------------------------------------------------------
	// Converts vertical gradient for display
	// ------------------------------------------------------------------------
	if (displayMode == GRADIENT_Y_IM)
	{
		// convert vertical gradient for display
		dY.convertTo(dYDisplay,dYDisplay.type(),0.5,128);
	}

	// ------------------------------------------------------------------------
	// Compute gradient magnitude and angle
	// ------------------------------------------------------------------------
	if (displayMode == GRADIENT_MAG_IM ||
		displayMode == GRADIENT_ANGLE_IM ||
		(displayMode == EDGE_MAP_IM && edgeMode != CANNY))
	{
		// Compute gradient magnitude and angle with cartToPolar
		// dX, dY --> gradientMag, gradientAngle (angle in degrees)
		// TODO cartToPolar(...);
        cartToPolar(dX,dY,gradientMag,gradientAngle,true);
	}

	// ------------------------------------------------------------------------
	// Converts gradient magnitude for display
	// ------------------------------------------------------------------------
	if (displayMode == GRADIENT_MAG_IM ||
		(displayMode == EDGE_MAP_IM && edgeMode != CANNY))
	{
		// convert magnitude for display
		convertScaleAbs(gradientMag, gradientMagDisplay);
	}

	// ------------------------------------------------------------------------
	// Converts gradient angle for display
	// ------------------------------------------------------------------------
	if (displayMode == GRADIENT_ANGLE_IM)
	{
		// convert angle for display
		convertScaleAbs(gradientAngle, gradientAngleDisplay);
	}

	// ------------------------------------------------------------------------
	// Threshold display gradient magnitude to get edge map
	// ------------------------------------------------------------------------
	if (displayMode == EDGE_MAP_IM && edgeMode != CANNY)
	{
		// threshold gradient magnitude for edge map at thresholdLevel
		// gradientMagDisplay --> edgeMap
		// TODO threshold(...);
        threshold(gradientMagDisplay,edgeMap,thresholdLevel,maxThreshold,edgeMap.type());
	}

	// ------------------------------------------------------------------------
	// Compute canny edges from burred image
	// ------------------------------------------------------------------------
	if ( displayMode == EDGE_MAP_IM &&
		((edgeMode == CANNY) || (edgeMode == MERGED)) )
	{
		// Compute Canny Edges from blurred image
		// blurredDisplay --> cannyEdgeMap with 1st threshold= thresholdLevel
		// and second threshold = thresholdLevel / 2 or 3
		// Caution : sobel aperture should not be bigger than 7 so use
		// MIN(7, kernelSize) for sobel aperture
		// Use L2 norm rather than L1
		// TODO Canny(...,
		//      ...,
		//      ...,		// first threshold for histeresis
		//      ..., 	// second threshold for histeresis
		//      ..., 	// sobel aperture (1, 3, 5, 7)
		//      ...);				// slower L2 norm
        Canny(blurredDisplay,cannyEdgeMap,thresholdLevel,thresholdLevel/3,min(7, kernelSize),true);
	}

	// ------------------------------------------------------------------------
	// Compute :
	//	- Horizontal and vertical laplacian components
	//	- laplacian
	// ------------------------------------------------------------------------
	if (displayMode ==  LAPLACIAN_IM ||
		displayMode == CORNERNESS_IM)
	{
		// Compute Laplacian X component by computing x gradient on dX (already a gradient)
		// dX --> d2X
		// TODO à compléter ...
        sepFilter2D(dX,d2X,d2X.depth(),gDx,gY);


		// Compute Laplacian Y component by computing y gradient on dY (already a gradient)
		// dY -->d2Y
		// TODO à compléter ...
        sepFilter2D(dY,d2Y,d2Y.depth(),gX,gDy);

		// Compute Laplacian
		// d2X + d2Y --> laplacian;
		// TODO à compléter ...
        laplacian = d2X+d2Y;
	}

	// ------------------------------------------------------------------------
	// Converts laplacian for display
	// ------------------------------------------------------------------------
	if (displayMode == LAPLACIAN_IM)
	{
		// Convert laplacian for display
		laplacian.convertTo(laplacianDisplay, laplacianDisplay.type(), 0.5,
				128);
	}

	// ------------------------------------------------------------------------
	// Compute cornerness image and converts it for display
	// ------------------------------------------------------------------------
	if (displayMode == CORNERNESS_IM)
	{
		/*
		 * Compute Cornerness measure from Hessian matrix
		 *  H = | d2X dXY |
		 *      | dXY d2Y |
		 *  det(H) - k Trace(H) with k in [0.04 ... 0.15]
		 *   = d2X * d2Y - dXY^2 - k (d2X + d2Y)^2
		 */
		// Compute dXY: inFrameGray -> dXY cross derivative image
		// TODO sepFilter2D(...);
        sepFilter2D(inFrameGray,dXY,dXY.depth(),gDx,gDy);

		// compute cornerness measure
		// TODO Compléter la méthode computeCornerness
        computeCornerness<double>(d2X,d2Y,dXY,g2D,harrisKappa,cornerness);

		// Cornerness values are unknown yet so take a look:
        minMaxInfo(cornerness);

		// convert cornerness for display
		normalize(cornerness, cornernessDisplay, 0, 255, NORM_MINMAX,
				cornernessDisplay.type());
	}

	// ------------------------------------------------------------------------
	// merge edges map components into a color image
	// ------------------------------------------------------------------------
	if (displayMode == EDGE_MAP_IM && edgeMode == MERGED)
	{
		// merge edgeMap, cannyEdgeMap and gray component into mixEdge color image
		merge(edgeMapComponents, mixEdge);
	}


	// ------------------------------------------------------------------------
	// Compute Harris cornerness image with harris function and convert it
	// for display
	// ------------------------------------------------------------------------
	if (displayMode == HARRISCORNER_IM)
	{
		// Compute Harris corners from blurred image
		// blurredDisplay --> harris
		// with kernelSize neighborhood
		// use MIN(7,kernelSize) for sobel aperture
		// harrisKappa for kappa
		//TODO cornerHarris(...);
        cornerHarris(blurredDisplay,harris,kernelSize,min(7,kernelSize),harrisKappa);

		// Harris corner measures are unknown so take a look
        minMaxInfo(harris);

		// Convert harris measure for display
		normalize(harris, harrisDisplay, 0, 255, NORM_MINMAX, harrisDisplay.type());
	}
}

/*
 * Compute 1D or 2D normalized gaussian into kernel with sigma variance and
 * @param kernel matrix to store gaussian kernel:
 * 	- if kernel size is \f$ 1 \times N\f$ or \f$ N \times 1\f$ produces a 1D
 * 	line or column filter.
 * 	- if kernel size is \f$ M \times N\f$ produces a 2D gaussian filter.
 * @param sigma standard deviation \f$\sigma\f$ of the gauss curve (or surface)
 * expressed in pixels
 * @param derivOrderX horizontal derivative order. Should be 0, 1 or 2:
 * @param derivOrderY vertical derivative order. Should be 0, 1 or 2
 */
template <typename T>
void CvGFilter::gaussian(Mat & kernel,
						   const double sigma,
						   const unsigned int derivOrderX,
						   const unsigned int derivOrderY)
{
	// clog << "kernel to compute : [" << kernel.rows << "x" << kernel.cols
	//      << "] = " << kernel << endl;

	if ((kernel.rows > 0) && (kernel.cols > 0))
	{
		// x center point
		double x0 = floor(kernel.cols/2.0)+1.0;
		// y center point
		double y0 = floor(kernel.rows/2.0)+1.0;

		// clog << "kernel center is [" << y0 << ", " << x0 << "]" << endl;

		double sum = 0.0;

		if (sigma > 0.0)
		{
			double sigmaFactor = 2.0 * sigma * sigma;

			// clog << "Sigma factor = " << sigmaFactor << endl;

			// Compute gaussian values ----------------------------------------
			for (int i = 0; i < kernel.rows; i++)
			{
				// yterms = (y - y0)^2 / sigmaFactor
				double yterms = double(i+1) - y0;
				yterms *= yterms;
				yterms /= sigmaFactor;
				T yExp = (T) exp(-yterms);
				for (int j = 0; j < kernel.cols; j++)
				{
					// xterms = (x - x0)^2 / sigmaFactor
					double xterms = double(j+1) - x0;
					xterms *= xterms;
					xterms /= sigmaFactor;
					T xExp = (T) exp(-xterms);

					// FIXME kernel.at<T> (i, j) = (T)(exp(-(xterms + yterms)));
					kernel.at<T> (i, j) = xExp * yExp;

					// clog << "g(" << i << ", " << j << ") = "
					//      << kernel.at<T> (i, j) << " = " << " exp(-(" << xterms
					//      << " + " << yterms << "))" << endl;

				}
			}

			// clog << "gaussian[" << kernel.rows << "x" << kernel.cols << "] sum = "
			//      << sum << endl;

			// Compute derivatives if any -------------------------------------
			double sigma2 = sigma * sigma;
			double sigma4 = sigma2 * sigma2;

			if (derivOrderX > 0)
			{
				switch (derivOrderX)
				{
					case 1:
						for (int j = 0;  j < kernel.cols; j++)
						{
							/*
							 * dg(x,y)/dx = (-(x-x0) / sigma^2) * g(x,y)
							 */
							double dFactor = -((double)(j+1) - x0) / sigma2;

							for (int i=0; i < kernel.rows; i++)
							{
								kernel.at<T> (i, j) *= dFactor;
								// clog << "dg(" << i << ", " << j << ")/dj = "
								//      << kernel.at<T> (i, j) << endl;
							}
						}
						break;
					case 2:
						for (int j = 0;  j < kernel.cols; j++)
						{
							/*
							 * d^2g(x,y)/dx^2 = ((x-x0)^2 - sigma^2 / sigma^4)
							 *                  * g(x,y)
							 */
							double dFactor = (pow(((double) (j + 1) - x0), 2.0)
									- sigma2) / sigma4;

							for (int i=0; i < kernel.rows; i++)
							{
								kernel.at<T> (i, j) *= dFactor;
								// clog << "d^2g(" << i << ", " << j << ")/dj^2 = "
								//      << kernel.at<T> (i, j) << endl;
							}
						}
						break;
					default:
						cerr << "gaussian deriv order X should be 0, 1 or 2 : "
							 << derivOrderX << endl;
						break;
				}
			}

			if (derivOrderY > 0)
			{
				switch (derivOrderY)
				{
					case 1:
						for (int i = 0;  i < kernel.rows; i++)
						{
							/*
							 * dg(x,y)/dy = (-(y-y0) / sigma^2) * g(x,y)
							 */
							double dFactor = -((double)(i+1) - y0) / sigma2;

							for (int j=0; j < kernel.cols; j++)
							{
								kernel.at<T> (i, j) *= dFactor;
								// clog << "dg(" << i << ", " << j << ")/di = "
								//      << kernel.at<T> (i, j) << endl;
							}
						}
						break;
					case 2:
						for (int i = 0;  i < kernel.rows; i++)
						{
							/*
							 * d^2g(x,y)/dy^2 = ((y-y0)^2 - sigma^2 / sigma^4)
							 *                  * g(x,y)
							 */
							double dFactor = (pow(((double) (i + 1) - y0), 2.0)
									- sigma2) / sigma4;

							for (int j=0; j < kernel.cols; j++)
							{
								kernel.at<T> (i, j) *= dFactor;
								// clog << "d^2g(" << i << ", " << j << ")/di^2 = "
								//      << kernel.at<T> (i, j) << endl;
							}
						}
						break;
					default:
						cerr << "gaussian deriv order Y should be 0, 1 or 2 : "
							 << derivOrderY << endl;
						break;
				}
			}

			// Normalize values -----------------------------------------------
			// compute filter gain on first half (or quarter)
			sum = 0.0;
			double quarterSum = 0.0;
			double borderXSum = 0.0;
			double borderYSum = 0.0;
			int centerI = (int)y0;
			int centerJ = (int)x0;
			// quarter sum
			for (int i = 0; i < centerI-1; i++)
			{
				for (int j = 0; j < centerJ-1; j++)
				{
					quarterSum +=kernel.at<T> (i, j);
				}
			}
			// border X sum
			for (int j=0; j < centerJ-1; j++)
			{
				borderXSum+=kernel.at<T>(centerI-1,j);
			}
			// border Y sum
			for (int i = 0; i < centerI-1; ++i)
			{
				borderYSum+=kernel.at<T>(i,centerJ-1);
			}
			// Adds center Value
			sum += kernel.at<T>(centerI-1,centerJ-1);

			// The compute the whole sum =
			//	- quarterSum * 4 + borderXSum*2 + boderYSum*2
			//    + center (already added in sum)
			sum += borderXSum*2.0 + borderYSum*2.0 + quarterSum*4.0;

			// Normalize values
			for (int i = 0; i < kernel.rows; i++)
			{
				for (int j = 0; j < kernel.cols; j++)
				{
					kernel.at<T> (i, j) /= sum;
				}
			}
		}
		else
		{
			cerr << "gaussian sigma is <= 0 --> no output" << endl;
		}
	}
	else
	{
		cerr << "gaussian kernel rows or cols is 0 --> no output" << endl;
	}
}

/*
 * Harris corenerness measure
 * det(H) - kappa trace(H)^2
 * = IxxIyy - Ixy^2 - kappa (Ixx + Iyy)^2
 */
template <typename T>
void CvGFilter::computeCornerness(const Mat & Ixx,
								  const Mat & Iyy,
								  const Mat & Ixy,
								  const Mat & wKernel,
								  const double Kappa,
								  Mat & dst)
{
	// Local smoothed Ixx, Iyy and Iyy
	Mat IxxW(Ixx.size(), Ixx.type(), Scalar(0));
	Mat IyyW(Iyy.size(), Iyy.type(), Scalar(0));
	Mat IxyW(Ixy.size(), Ixy.type(), Scalar(0));

	// Smooth Ixx, Iyy and Ixy with wKernel using filter2D
	// Ixx --> IxxW with wKernel
	// TODO filter2D(...);
    filter2D(Ixx,IxxW,IxxW.depth(),wKernel);
	// Iyy --> IyyW with wKernel
	// TODO filter2D(...);
    filter2D(Iyy,IyyW,IyyW.depth(),wKernel);
	// Ixy --> IxyW with wKernel
	// TODO filter2D(...);
    filter2D(Ixy,IxyW,IxyW.depth(),wKernel);

	// initiate iterators on IxxW, IyyW, IxyW and dst
	MatConstIterator_<T> xxIt = IxxW.begin<T>();
	MatConstIterator_<T> xxItEnd = IxxW.end<T>();
	MatConstIterator_<T> yyIt = IyyW.begin<T>();
	MatConstIterator_<T> xyIt = IxyW.begin<T>();
	MatIterator_<T> destIt = dst.begin<T>();

	// intialize variables of the equation
	T IxxIyy = 0.0;
	T Ixy2 = 0.0;
	T IxxSumIyy = 0.0;

	// Compute cornerness value on each pixel
	for(; xxIt != xxItEnd; ++xxIt, ++yyIt, ++xyIt, ++destIt)
	{
		/*
		 *     / *xxIt  *xyIt \
		 * H = |              |
		 *     \ *xyIt  *yyIt /
		 *
		 * *destIt = det(H) - Kappa x trace(H)^2
		 */

		// TODO (*destIt) = ...
        IxxIyy = (*xxIt)*(*yyIt);
        Ixy2 = (*xyIt)*(*xyIt);
        IxxSumIyy = (*xxIt) + (*yyIt);
        (*destIt) = IxxIyy - Ixy2 - Kappa * IxxSumIyy*IxxSumIyy;
	}

	IxxW.release();
	IyyW.release();
	IxyW.release();
}

/*
 * Prints info about min and max value of this matrix
 * @param m the matrix to investigate
 */
void CvGFilter::minMaxInfo(const Mat & m)
{
	double minVal, maxVal;
	Point minLoc;
	Point maxLoc;
	minMaxLoc(m,&minVal, &maxVal, &minLoc, &maxLoc);
	clog << "values : min = " << minVal << " at (" << minLoc.x
		 << ", " << minLoc.y << ") max = " << maxVal << " at ("
		 << maxLoc.x << ", " << maxLoc.y << ")" << endl;
}
