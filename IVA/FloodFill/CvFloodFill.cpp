/*
 * CvFloodFill.cpp
 *
 *  Created on: 26 févr. 2012
 *      Author: davidroussel
 */

#include <ctime>		// for clock
#include <iostream>		// for cerr
using namespace std;

#include <opencv2/imgproc/imgproc.hpp>

#include <assert.h>

#include "CvFloodFill.h"

/*
 * Flood fill class constructor
 * @param sourceImage
 */
CvFloodFill::CvFloodFill(Mat * sourceImage) :
	CvProcessor(sourceImage),
	dim(sourceImage->size()),
	// mask is 2 pixel wider and taller
	mask(Size(sourceImage->cols + 2, sourceImage->rows + 2), CV_8UC1),
	merged(dim, type),
	displayMode(INPUT_IM),
	seeded(false),
	flooded(false),
	ffillMode(FIXED_RANGE),
	loDiff(20),
	upDiff(20),
	connectivity(4),
	isColor(sourceImage->channels() > 1 ? true : false),
	newMaskVal(255),
	floodFlags(connectivity + (newMaskVal << 8) +
			   (ffillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0)),
	floodArea(0),
	initialSeed(-1, -1),
	centerSeed(-1, -1),
	floodBoundingBox(0,0,0,0),
	showBoundingBox(false)

{
	setup(sourceImage, false);

	newFloodColor();

	// Adds named image to additional images map
	addImage("display", &displayImage);
}

/*
 * Gaussian filtering class destructor
 */
CvFloodFill::~CvFloodFill()
{
	cleanup();
}

/*
 * Setup attributes when source image is changed
 * @param image source Image
 * @param completeSetup is true when used to change source image,
 * and false when used in constructor
 */
void CvFloodFill::setup(Mat *image, bool completeSetup)
{
	assert (image != NULL);

	CvProcessor::setup(image, completeSetup);

	if (completeSetup) // complete setup
	{
		dim = sourceImage->size();
		seeded = false;
		flooded = false;
		isColor = (sourceImage->channels() > 1 ? true : false);
		floodArea = 0;
		initialSeed = Point(-1,-1);
		centerSeed = Point(-1,-1);
		floodBoundingBox = Rect(0,0,0,0);
		showBoundingBox = false;
		mask.create(Size(image->cols + 2, image->rows + 2), CV_8UC1);
		merged.create(dim, type);
		displayMode = INPUT_IM;
	}
	else // setup during constructor only
	{

	}

	// in any cases
}

/*
 * Cleanup attributes before changing source image or cleaning class
 * before destruction
 */
void CvFloodFill::cleanup()
{
	merged.release();
	mask.release();
	displayImage.release();

	// super cleanup
	CvProcessor::cleanup();
}

/*
 * Gets displayImageChanged current status when display image is changed
 * @return the current displayImageChanged value
 */
//bool CvFloodFill::isDisplayImageChanged()
//{
//	return displayImageChanged;
//}

/*
 * Get current display mode
 * @return the current display mode
 */
CvFloodFill::ImageDisplay CvFloodFill::getDisplayMode() const
{
	return displayMode;
}

/*
 * Sets a new display mode
 * @param displayMode the new display mode to set
 */
void CvFloodFill::setDisplayMode(const ImageDisplay displayMode)
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
 * Gets Image reference corresponding to the current displayMode and
 * edgeMode
 * @return Image reference corresponding to the current displayMode and
 * edgeMode
 */
const Mat & CvFloodFill::getDisplayImage() const
{
	return displayImage;
}

/*
 * Gets Image pointer corresponding to the current displayMode and
 * edgeMode
 * @return Image reference corresponding to the current displayMode and
 * edgeMode
 */
Mat * CvFloodFill::getDisplayImagePtr()
{
	return &displayImage;
}

/*
 * Gets the seeded status of the image
 * @return true if there is a seed, false otherwise
 */
bool CvFloodFill::isSeeded() const
{
	return seeded;
}

/*
 * Gets the flooded status of the image
 * @return true if image has been flooded, false otherwise
 */
bool CvFloodFill::isFlooded() const
{
	return flooded;
}

/*
 * Gets the current flooding mode (absolute or relative)
 * @return the current floodin mode
 */
CvFloodFill::FloodFillMode CvFloodFill::getFfillMode() const
{
	return ffillMode;
}

/*
 * Sets a new flooding mode (absolute or relative
 * @param ffillMode the new flooding mode
 */
void CvFloodFill::setFfillMode(const FloodFillMode ffillMode)
{
	if(ffillMode < NBFILLING_MODES)
	{
		this->ffillMode = ffillMode;
		floodFlags = connectivity + (newMaskVal << 8) +
					 (ffillMode == FIXED_RANGE ? CV_FLOODFILL_FIXED_RANGE : 0);

	}

	resetMeanProcessTime();
}

/*
 * Gets the lower difference in pixel values for flooding
 * @return the current lower difference for flooding
 */
int CvFloodFill::getLoDiff() const
{
	return loDiff;
}

/*
 * Sets a new lower difference in pixels values for flooding
 * @param loDiff the new lower difference for flooding
 */
void CvFloodFill::setLoDiff(const int loDiff)
{
	if((loDiff >= 0) && (loDiff <= 255))
	{
		this->loDiff = loDiff;
	}

	resetMeanProcessTime();
}

/*
 * Gets loDiff pointer.
 * OpenCV trackbars require direct access to values
 * @return
 */
int * CvFloodFill::getLoDiffPtr()
{
	return &loDiff;
}

/*
 * Gets the upper difference in pixel values for flooding
 * @return the current upper difference for flooding
 */
int CvFloodFill::getUpDiff() const
{
	return upDiff;
}

/*
 * Sets a new upper difference in pixels values for flooding
 * @param upDiff the new upper difference for flooding
 */
void CvFloodFill::setUpDiff(const int upDiff)
{
	if((upDiff >= 0) && (upDiff <= 255))
	{
		this->upDiff = upDiff;
	}

	resetMeanProcessTime();
}

/*
 * Gets upDiff pointer.
 * OpenCV trackbars require direct access to values
 * @return the address of upDiff attribute
 */
int * CvFloodFill::getUpDiffPtr()
{
	return &upDiff;
}

/*
 * Gets the current connectivity for pixels neighbors for flooding
 * @return the current connectivity for pixels neighbors for flooding
 */
int CvFloodFill::getConnectivity() const
{
	return connectivity;
}

/*
 * Sets a new connectivity for pixels neighbors for flooding
 * @param connectivity the new connectivity for pixels neighbors
 * for flooding
 */
void CvFloodFill::setConnectivity(const int connectivity)
{
	if ((connectivity == 4) || (connectivity == 8))
	{
		this->connectivity = connectivity;
		floodFlags = connectivity + (newMaskVal << 8) +
					 (ffillMode == FIXED_RANGE ? CV_FLOODFILL_FIXED_RANGE : 0);
	}

	resetMeanProcessTime();
}

/*
 * Gets the current color status of the source image
 * @return the current color status of the source image
 */
bool CvFloodFill::getIsColor() const
{
	return isColor;
}

/*
 * Gets the current initial seed
 * @return the current initial seed
 * @note use isSeeded to check if there is an initial seed
 */
const Point &CvFloodFill::getInitialSeed() const
{
	return initialSeed;
}

/*
 * Sets an new initial seed
 * @param initialSeed the new initial seed
 */
void CvFloodFill::setInitialSeed(const Point & initialSeed)
{
	this->initialSeed = initialSeed;
	seeded = true;
}

/*
 * Gets the current flooded area center for future seed
 * @return the current flooded area center
 * @note use isFlooded to check image has been flooded
 */
const Point & CvFloodFill::getCenterSeed() const
{
	return centerSeed;
}

/*
 * Gets current show/hide seed point status
 * @return the current show/hide seed point status
 */
bool CvFloodFill::isShowSeed() const
{
	return showSeed;
}

/*
 * Sets new show/hide seed point status
 * @param showSeed the new show/hide seed point status
 */
void CvFloodFill::setShowSeed(const bool showSeed)
{
	this->showSeed = showSeed;
}

/*
 * Generates a new random color for floodColor
 */
void CvFloodFill::newFloodColor()
{
	// random numbers for new seed color
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	floodColor = isColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
}

/*
 * Gets the current flooded area bounding box
 * @return the current flooded area bounding box
 * @note use isFlooded to check image has been flooded
 */
const Rect & CvFloodFill::getFloodBoundingBox() const
{
	return floodBoundingBox;
}

/*
 * Gets the current show/hide bounding box status
 * @return the current show/hide bounding box status
 */
bool CvFloodFill::isShowBoundingBox() const
{
	return showBoundingBox;
}

/*
 * Set the show/hide bounding box status
 * @param showBoundingBox the new show/hide bounding box status
 */
void CvFloodFill::setShowBoundingBox(const bool showBoundingBox)
{
	this->showBoundingBox = showBoundingBox;
}

/*
 * Flood fill update:
 * 	- Copy source image to merged image
 * 	- if image has already been flooded compute Flood barycenter
 * 		- if flood has succeded set seed as the barycenter
 * 		- else reset seeded and flooded states
 * 	- else
 * 		- if image has been seed manually then use this seed
 * 	- clears mask with zeros
 * 	- if there is a seed
 * 		- flood fill the image
 * 		- if flood area counts some pixels then sets flooded state
 * 		- if flooded
 * 			- if show bounding box is on then draw bouding box rectangle
 * 				in source image
 * 			- if show seed is on then draw seed in source image and
 * 				merged image
 *	- according to displayMode set displayImage
 *
 */
void CvFloodFill::update()
{
	// copy source image to merged image
	sourceImage->copyTo(merged);

	clock_t start, end;

	start = clock();

	// if image has been flooded once, then compute flood barycenter as the
	// seed for next flood
	Point seed;
	if (flooded)
	{
		// TODO Compléter la méthode computeFloodCenter pour calculer
		// le barycentre centre de la zone inondée (flooded) à partir de l'image
		// du masque qui contient des valeurs à 255 dans cette zone et 0 ailleurs
		bool res = computeFloodCenter<uchar>(mask, centerSeed, (uchar)newMaskVal);
		if (res)
		{
			// set seed for flooding
			seed = centerSeed;
		}
		else
		{
			seeded = false;
			flooded = false;
		}
	}
	else
	{
		if (seeded)
		{
			seed = initialSeed;
		}
	}

	// update mask with zeros : clears mask
	mask = Scalar(0);

	// flood
	if (seeded) // We can flood the image
	{
		// Check seed is inside image otherwise floodFill will crash
		seed.x >= 0 ? seed.x : seed.x = 0;
		seed.x < dim.width ? seed.x : seed.x = dim.width - 1;
		seed.y >= 0 ? seed.y : seed.y = 0;
		seed.y < dim.height ? seed.y : seed.y = dim.height - 1;

		// Flood image from seed point
		// merged --> mask
		// with seed point : seed
		// with flood color : floodColor
		// update flood bounding box : floodBoundingBox
		// Lo diff set as Scalar(loDiff, loDiff, loDiff)
		// Up diff set as Scalar(upDiff, upDiff, upDiff)
		// use already computed floodFlags
		// TODO floodArea = floodFill(...);
        floodArea = floodFill(merged,mask,seed,floodColor,&floodBoundingBox,Scalar(loDiff, loDiff, loDiff),Scalar(upDiff, upDiff, upDiff),floodFlags);

		// if floodArea contains some pixels then flooded is true now
		flooded = (floodArea > 0 ? true : false);

		// if image has been flooded and showBoundingBox is true then
		// draw flooded area bounding box in source image
		if (flooded)
		{
			if (showBoundingBox) // Draws bounding box in source image with flood color
			{
				int topLeftX = floodBoundingBox.x;
				int topleftY = floodBoundingBox.y;
				int boxWidth = floodBoundingBox.width;
				int boxHeight = floodBoundingBox.height;
				Point p1 = Point(topLeftX, topleftY);
				Point p2 = Point(topLeftX + boxWidth,
								 topleftY + boxHeight);
				rectangle(*sourceImage, // image to draw in (sourceImage)
						  p1, // top left point
						  p2, // bottom right point
						  floodColor, // draw color : flood color
						  3, // line width
						  CV_AA); // Line Type (better with AA)
			}
		}

		// if showSeed is true then Shows seed point in source image
		// and merged image as a small circle with red color
		if (showSeed)
		{
			circle(*sourceImage, // image to draw in
				   seed, // center : seed points
				   3, // radius
				   Scalar(0, 0, 255), // draw color
				   2, // Line width
				   CV_AA); // Line type (better with AA)
			circle(merged, seed, 3, Scalar(0, 0, 255), 2, CV_AA);
		}
	}

	end = clock();
	processTime = end - start;
	meanProcessTime += processTime;

	// ------------------------------------------------------------------------
	// select image to display ...
	// ------------------------------------------------------------------------
	uchar * previousImageData = displayImage.data;

	switch (displayMode)
	{
		case INPUT_IM:
			displayImage = *sourceImage;
			break;
		case MASK_IM:
			displayImage = mask;
			break;
		case MERGED_IM:
			displayImage = merged;
			break;
		default:
			if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
			{
				cerr << "unknown display image index " << displayMode << endl;
			}
			displayImage = *sourceImage;
			break;
	}

	// Sets display image changed  status
	// This status will be used in the QcvProcessor descendant
	if (previousImageData != displayImage.data)
	{
		displayImageChanged = true;
	}
	else
	{
		displayImageChanged = false;
	}
}

/*
 * Clears flood and reset seed and flooded values to false;
 */
void CvFloodFill::clearFlood()
{
	flooded = false;
	seeded = false;
	floodArea = 0;
	initialSeed = Point(-1,-1);
	centerSeed = Point(-1,-1);
	floodBoundingBox = Rect(0,0,0,0);

	resetMeanProcessTime();
}

/*
 * Compute barycenter of last computed flood
 * @param mask the mask image where mask pixels are set to newMaskVal
 * @param center the barycenter point computed here
 * @param threshold the value to use as threshold to find flooded area
 * pixels in the mask image
 * @note One can also use the OpenCV function moments(...) to compute
 * all moments up to the third order but we only need m00 (number of
 * pixels of the flooded area) and m01 & m10 to compute flooded area
 * center = (m10/m00, m01/m00).
 * @return true if some pixels have been flooded, false otherwise.
 * @note we need to know if flooding has failed as we should reset
 * seeded and flooded variables accordingly
 */
template<typename T>
bool CvFloodFill::computeFloodCenter(const Mat & mask,
									 Point & center,
									 const T threshold)
{
	// first check mask is single channel
	if (mask.channels() == 1)
	{
		long pixelCount = 0;	// m00
		long lineCount = 0;		// m01
		long colCount = 0;		// m10

		for (int i = 0; i < mask.rows; i++)
		{
			for (int j = 0; j < mask.cols; j++)
			{
				if (mask.at<T>(i,j) >= threshold)
				{
					// TODO Compléter ...
					// update pixelCount : +1
					// update lineCount : +i
					// update colCount : +j
                    pixelCount++;
                    lineCount+=i;
                    colCount+=j;
				}
			}
		}

		if (pixelCount > 0)
		{
			lineCount/=pixelCount;	// m01 / m00
			colCount/=pixelCount;	// m10 / m00

			center.x = (int)colCount;
			center.y = (int)lineCount;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cerr << "CvFloodFill::computeFloodCenter : mask image has "
			 << mask.channels() << " channels, flood center computation aborted"
			 << endl;
		return false;
	}
}

