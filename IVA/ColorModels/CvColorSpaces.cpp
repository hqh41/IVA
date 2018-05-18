/*
 * CvColorSpaces.cpp
 *
 *  Created on: 8 févr. 2012
 *      Author: davidroussel
 */
#include <cassert>	// for assert
#include <iostream>	// for cerr
using namespace std;

#include <opencv2/imgproc/imgproc.hpp> // for cvtColor

#include "mapRed.h"
#include "mapGreen.h"
#include "mapBlue.h"
#include "mapHSV.h"
#include "mapCb.h"
#include "mapCr.h"

#include "CvColorSpaces.h"

/*
 * Color spaces constructor
 * @param sourceImage input image
 */
CvColorSpaces::CvColorSpaces(Mat * sourceImage) :
	CvProcessor(sourceImage),
	inFrameGray(sourceImage->size(), CV_8UC1),
	maxBGChannels(sourceImage->size(), CV_8UC1),
	maxBGRChannels(sourceImage->size(), CV_8UC1),
	maxBGChannelsColor(sourceImage->size(), CV_8UC3),
	maxBGRChannelsColor(sourceImage->size(), CV_8UC3),
	inFrameXYZ(sourceImage->size(), CV_64FC3),
	inFrameHSV(sourceImage->size(), CV_8UC3),
	hueColorImage(sourceImage->size(), CV_8UC3),
	hueMixImage(sourceImage->size(), CV_8UC3),
	hueMixedColorImage(sourceImage->size(), CV_8UC3),
	hueDisplay(HUECOLOR),
	inFrameYCrCb(sourceImage->size(), CV_8UC3),
	crColoredImage(sourceImage->size(), CV_8UC3),
	cbColoredImage(sourceImage->size(), CV_8UC3),
	redMap(mapRed),
	greenMap(mapGreen),
	blueMap(mapBlue),
	hMap(mapHSV),
	cbMap(mapCb),
	crMap(mapCr),
	imageDisplayIndex(INPUT),
	displayImageChanged(false)
{
	setup(sourceImage, false);
	addImage("display", &displayImage);
}

/*
 * Color spaces destructor
 */
CvColorSpaces::~CvColorSpaces()
{
	cleanup();
}

/*
 * Setup internal attributes according to source image
 * @param sourceImage a new source image
 * @param fullSetup full setup is needed when source image is changed
 * @pre sourceimage is not NULL
 * @note this method should be reimplemented in sub classes
 */
void CvColorSpaces::setup(Mat * sourceImage, bool fullSetup)
{
//	clog << "CvColorSpaces::"<< (fullSetup ? "full " : "") <<"setup" << endl;

	assert(sourceImage != NULL);

	CvProcessor::setup(sourceImage, fullSetup);

	// Full setup starting point
	if (fullSetup) // only when sourceImage changes
	{
		inFrameGray.create(sourceImage->size(), CV_8UC1);
		maxBGChannels.create(sourceImage->size(), CV_8UC1);
		maxBGRChannels.create(sourceImage->size(), CV_8UC1);
		maxBGChannelsColor.create(sourceImage->size(), CV_8UC3);
		maxBGRChannelsColor.create(sourceImage->size(), CV_8UC3);
		inFrameXYZ.create(sourceImage->size(), CV_64FC3),
		inFrameHSV.create(sourceImage->size(), CV_8UC3);
		hueColorImage.create(sourceImage->size(), CV_8UC3);
		hueMixImage.create(sourceImage->size(), CV_8UC3);
		hueMixedColorImage.create(sourceImage->size(), CV_8UC3);
		inFrameYCrCb.create(sourceImage->size(), CV_8UC3);
		crColoredImage.create(sourceImage->size(), CV_8UC3);
		cbColoredImage.create(sourceImage->size(), CV_8UC3);
		processTime = 0;
	}
	else // only at construction
	{
		bgrMap[0] = &blueMap;
		bgrMap[1] = &greenMap;
		bgrMap[2] = &redMap;

		for (size_t i = 0; i < (size_t) NbShows; i++)
		{
			showColorChannel[i] = true;
		}
	}

	// Partial setup starting point (in both cases)
	for (int i=0; i < 3; i++)
	{
		bgrChannels.push_back(Mat(sourceImage->size(), CV_8UC1));
		bgrColoredChannels[i].create(sourceImage->size(), CV_8UC3);
		xyzGrayChannels[i].create(sourceImage->size(), CV_64FC1);
		xyzDisplayChannels[i].create(sourceImage->size(), CV_8UC1);
		hsvChannels.push_back(Mat(sourceImage->size(), CV_8UC1));
		hueMixChannels[i].create(sourceImage->size(), CV_8UC1);
		yCrCbChannels.push_back(Mat(sourceImage->size(), CV_8UC1));
	}
}

/*
 * Clean up images before changing source image or terminating
 * CvColorSpaces
 */
void CvColorSpaces::cleanup()
{
//	clog << "CvColorSpaces::cleanup()" << endl;

	cbColoredImage.release();
	crColoredImage.release();
	for (size_t i = 0; i < yCrCbChannels.size(); i++)
	{
		yCrCbChannels[i].release();
	}
	yCrCbChannels.clear();
	inFrameYCrCb.release();

	hueMixedColorImage.release();
	hueMixImage.release();
	for (size_t i = 0; i < 3; i++)
	{
		hueMixChannels[i].release();
	}
	hueColorImage.release();
	for (size_t i = 0; i < hsvChannels.size(); i++)
	{
		hsvChannels[i].release();
	}
	hsvChannels.clear();
	inFrameHSV.release();

	for (size_t i = 0; i < bgrChannels.size(); i++)
	{
		bgrChannels[i].release();
		bgrColoredChannels[i].release();
		xyzGrayChannels[i].release();
		xyzDisplayChannels[i].release();
	}
	bgrChannels.clear();

	inFrameXYZ.release();

	maxBGRChannelsColor.release();

	maxBGChannelsColor.release();

	maxBGRChannels.release();

	maxBGChannels.release();

	inFrameGray.release();

	displayImage.release();

	CvProcessor::cleanup();
}


/*
 * Update compute selected image for display according to
 * selected parameters such as imageDisplayIndex, showColorChannel,
 * and eventually hueDisplay
 * @return true if display image has changed, false otherwise
 */
void CvColorSpaces::update()
{
	clock_t start, end;
	start = clock();
	// ------------------------------------------------------------------------
	// Compute needed images
	// ------------------------------------------------------------------------
	switch (imageDisplayIndex)
	{
		case INPUT:
			// Ain't got nothin to do here : input image doesn't need to be processed
			break;

		// --------------------------------------------------------------------
		// Gray level conversion
		// --------------------------------------------------------------------
		case GRAY:
			// Converts to gray
			// sourceImage -> inFramegray
			// TODO Compléter ...
            cvtColor(*sourceImage,inFrameGray,CV_BGR2GRAY);
			break;

		// --------------------------------------------------------------------
		// RGB Decomposition
		// --------------------------------------------------------------------
		case RED:
		case GREEN:
		case BLUE:
		case MAX_BGR:
			// Split BGR channels : sourceImage -> bgrChannels
			// TODO Compléter ...
            split(*sourceImage, bgrChannels);

			// TODO Build colored image from channels : red channel leads to a
			// red colored image, and so on ...
			// by applying bgrMap[x] on bgrChannels[x] to produce
			// bgrColoredChannels[x]
			// bgrChannels[i] -> bgrColoredChannels[i]
			for (size_t i = 0; i < bgrChannels.size(); i++)
			{
				// TODO Compléter ...
                bgrMap[i]->applyPalette(bgrChannels[i],bgrColoredChannels[i]);
			}

			if (imageDisplayIndex == MAX_BGR)
			{
				if (!showColorChannel[MAXINDEX])
				{
					// Compute maximum of BGR channels using cv::max
					// bgrChannels[0 & 1] -> maxBGChannels
					// bgrChannels[2] & maxBGChannels -> maxBGRChannels
					// TODO à compléter ...
                    max(bgrChannels[0],bgrChannels[1],maxBGChannels);
                    max(maxBGChannels,bgrChannels[2],maxBGRChannels);
				}
				else
				{
					// Compute colored maximum of BGR channels using normMax
					// bgrColoredChannels[0 & 1] -> maxBGChannelsColor
					// bgrColoredChannels[2] & maxBGChannelsColor -> maxBGRChannelsColor
					// TODO à compléter normMax puis utiliser normMax ...
                    normMax(bgrColoredChannels[0],bgrColoredChannels[1],maxBGChannelsColor);
                    normMax(maxBGChannelsColor, bgrColoredChannels[2], maxBGRChannelsColor);
				}
			}

			/*
			 * TODO What are the characteristics of blue component vs
			 * green or red ?
			 * Tip: use gray images instead of colored images to compare
			 * Answer below:
			 *
			 */

			break;

		// --------------------------------------------------------------------
		// XYZ conversion
		// --------------------------------------------------------------------
		case XYZ_X:
		case XYZ_Y:
		case XYZ_Z:
			// Converts to XYZ : sourceImage -> inFrameXYZ
			// TODO à compléter ...
            cvtColor(*sourceImage,inFrameXYZ,CV_BGR2XYZ);
            convertScaleAbs(inFrameXYZ,inFrameXYZ);

			// Splits inFrameXYZ to channels xyzGrayChannels
			// TODO à compléter ...
            split(inFrameXYZ, xyzGrayChannels);

			// Converts floating point channels to display channels
			// xyzGrayChannels[...] -> xyzDisplayChannels[...]
			for( size_t i=0; i < 3; i++)
			{
				// TODO à compléter ...
                convertScaleAbs( xyzGrayChannels[i],xyzDisplayChannels[i]);
			}

			/*
			 * TODO What component X, Y or Z looks more like luminance to you ?
			 * Answer below:
             * Y
			 */

			break;
		// --------------------------------------------------------------------
		// HSV conversion
		// --------------------------------------------------------------------
		case HUE:
		case SATURATION:
		case VALUE:
			// Converts to HSV : sourceImage -> inFrameHSV
			// TODO à compléter ...

			// Split HSV channels : inFrameHSV -> hsvChannels
			// TODO à compléter ...

			// evt show min/max of H component : should be [0...179]°
			// showMinMaxLoc(hsvChannels[0]);

			// Normalize hue from 0 to 255 because hsv colormap (hMap)
			// applied below expects value within 0 to 255 range
			// hsvChannels[0] -> hsvChannels[0]
			// TODO à compléter ...

			// Build colored Hue image : hsvChannels[0] -> hueColorImage
			// TODO à compléter ...

			// Build Mixed Hue Color and (Saturation or Value) image
			if ((hueDisplay > HUECOLOR) && (hueDisplay < HUEGRAY))
			{
				// Creates a 3 channel image from saturation or value channel
				// depending on huDisplay value
				// hsvChannels -> hueMixChannels
				// TODO à compléter ...

				// merge mix channels into color image
				// hueMixChannels --> hueMixImage
				// TODO à compléter ...

				// Build colored Hue image \times Saturation or Value
				// hueColorImage x hueMixImage -> hueMixedColorImage
				// TODO à compléter ...
			}
			break;

			/*
			 * TODO To what other component the V component of HSV space looks
			 * like ?
			 * Tip: Use gray images instead of colored images to compare.
			 * Answer below:
			 *
			 */

		// --------------------------------------------------------------------
		// YCbCr conversion
		// --------------------------------------------------------------------
		case Y:
		case Cr:
		case Cb:
			// Converts to YCrCb : sourceImage -> inFrameYCrCb
			// TODO à compléter ...

			// Split YCrCb channels : inFrameYCrCb -> yCrCbChannels
			// TODO à compléter ...

			// Apply palette on cr & cb components
			// crmap, yCrCbChannels[1] -> crColoredImage
			// TODO à compléter ...
			// cbmap, yCrCbChannels[2] -> cbColoredImage
			// TODO à compléter ...
			break;
		default:
			cerr << "unknown image display index" << imageDisplayIndex << endl;
			break;
		/*
		 * TODO How does the Y component compares to the gray component ?
		 * Answer below :
		 */

		/*
		 * TODO What can you tell about the details in Cr or Cb components vs
		 * the details in the Y component ?
		 * Answer below :
		 */
	}

	// ------------------------------------------------------------------------
	// select image to display ...
	// ------------------------------------------------------------------------

	uchar * previousImageData = displayImage.data;

	switch (imageDisplayIndex)
	{
		case INPUT:
			displayImage = *sourceImage;
			break;
		case GRAY:
			displayImage = inFrameGray;
			break;
		case RED:
			if (showColorChannel[RINDEX])
			{
				displayImage = bgrColoredChannels[RINDEX];
			}
			else
			{
				displayImage = bgrChannels[RINDEX];
			}
			break;
		case GREEN:
			if (showColorChannel[GINDEX])
			{
				displayImage = bgrColoredChannels[GINDEX];
			}
			else
			{
				displayImage = bgrChannels[GINDEX];
			}
			break;
		case BLUE:
			if (showColorChannel[BINDEX])
			{
				displayImage = bgrColoredChannels[BINDEX];
			}
			else
			{
				displayImage = bgrChannels[BINDEX];
			}
			break;
		case MAX_BGR:
			if (showColorChannel[MAXINDEX])
			{
				displayImage = maxBGRChannelsColor;
			}
			else
			{
				displayImage = maxBGRChannels;
			}
			break;
		case XYZ_X:
			displayImage = xyzDisplayChannels[0];
			break;
		case XYZ_Y:
			displayImage = xyzDisplayChannels[1];
			break;
		case XYZ_Z:
			displayImage = xyzDisplayChannels[2];
			break;
		case HUE:
			switch (hueDisplay)
			{
				case HUECOLOR:
					displayImage = hueColorImage;
					break;
				case HUESATURATE:
				case HUEVALUE:
					displayImage = hueMixedColorImage;
					break;
				case HUEGRAY:
					displayImage = hsvChannels[0];
					break;
				case NBHUES:
				default:
					cerr << "unknown Hue display mode "<< hueDisplay
						 << endl;
					break;
			}
			break;
		case SATURATION:
			displayImage = hsvChannels[1];
			break;
		case VALUE:
			displayImage = hsvChannels[2];
			break;
		case Y:
			displayImage = yCrCbChannels[0];
			break;
		case Cr:
			if (showColorChannel[CrINDEX])
			{
				displayImage = crColoredImage;
			}
			else
			{
				displayImage = yCrCbChannels[1];
			}
			break;
		case Cb:
			if (showColorChannel[CbINDEX])
			{
				displayImage = cbColoredImage;
			}
			else
			{
				displayImage = yCrCbChannels[2];
			}
			break;
		default:
			cerr << "unknown display image index " << imageDisplayIndex << endl;
			displayImage = *sourceImage;
			break;
	}

	displayImageChanged = previousImageData != displayImage.data;

	end = clock();
	processTime = (end - start);
	meanProcessTime += processTime;
	if (displayImageChanged)
	{
		resetMeanProcessTime();
	}
}

/*
 * Gets the image selected for display
 * @return the display image
 */
Mat & CvColorSpaces::getDisplayImage()
{
	return displayImage;
}

/*
 * Get currently selected image index
 * @return the currently selected image for display index
 */
CvColorSpaces::Display CvColorSpaces::getDisplayImageIndex()
{
	return imageDisplayIndex;
}

/*
 * Select image to set in displayImage :
 * 	- INPUT selects input image for display
 * 	- GRAY selects gray converted input image for display
 * 	- RED selects BGR red component image for display
 * 	- GREEN selects BGR green component image for display
 * 	- BLUE selects BGR blue component image for display
 * 	- HUE selects HSV hue component image for display
 * 	- SATURATION selects HSV saturation component image for display
 * 	- VALUE selects HSV value component image for display
 * 	- Y selects YCrCb Y component image for display
 * 	- Cr selects YCrCb Cr component image for display
 * 	- Cb selects YCrCb Cb component image for display
 * @param select the index to select display image
 */
void CvColorSpaces::setDisplayImageIndex(const Display index)
{
	if (index < NbSelected)
	{
		imageDisplayIndex = index;
		processTime = 0;
	}
	else
	{
		cerr << "CvColorSpaces::setDisplayImageIndex : index " << index
			 << " out of bounds" << endl;
	}
}

/*
 * Get the color display status for specific channels (such as red,
 * green, blue, hue ...)
 * @param c the channel to get color display status:
 * 	- BINDEX color display status for blue component
 * 	- GINDEX color display status for green component
 * 	- RINDEX color display status for red component
 * 	- MAXINDEX color display for max of RGB
 * 	- HINDEX color display status for hue component
 * 	- CbNDEX color display status for Cb component
 * 	- CrNDEX color display status for Cr component
 * @return the color display status of selected component
 */
bool CvColorSpaces::getColorChannel(const ShowColor c)
{
	return showColorChannel[c];
}

/*
 * Sets the color display status of selected component
 * @param c the selected component:
 * 	- BINDEX color display status for blue component
 * 	- GINDEX color display status for green component
 * 	- RINDEX color display status for red component
 * 	- MAXINDEX color display for max of RGB
 * 	- HINDEX color display status for hue component
 * 	- CbNDEX color display status for Cb component
 * 	- CrNDEX color display status for Cr component
 * @param value the value to set on the selected component
 */
void CvColorSpaces::setColorChannel(const ShowColor c, const bool value)
{
	if ( c < NbShows)
	{
		showColorChannel[c] = value;
		processTime = 0;
	}
	else
	{
		cerr << "CvColorSpaces::setColorChannel : index " << c
			 << " out of bounds" << endl;
	}
}

/*
 * Get currently selected hue display mode
 * @return the currenlty selected hue display mode
 */
CvColorSpaces::HueDisplay CvColorSpaces::getHueDisplaymode()
{
	return hueDisplay;
}

/*
 * Select hue display mode :
 *	- HUECOLOR Normal Hue mode
 *	- HUESATURATE Hue*Saturatin mode
 *	- HUEVALUE Hue*Value mode
 *	- HUEGRAY Gray mode
 * @param mode the mode so select
 */
void CvColorSpaces::setHueDisplayMode(const HueDisplay mode)
{
	if (mode < NBHUES)
	{
		hueDisplay = mode;
		processTime = 0;
	}
	else
	{
		cerr << "CvColorSpaces::setHueDisplayMode : index " << mode
			 << " out of bounds" << endl;
	}
}

/*
 * Show Min and Max values and locations for a matrix
 * @param m the matrix to consider
 */
void CvColorSpaces::showMinMaxLoc(const Mat & m)
{
	// search for min & max value locations
	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(m,&minVal, &maxVal, &minLoc, &maxLoc);
	clog << "sat values : min = " << minVal << " at (" << minLoc.x
		 << ", " << minLoc.y << ") max = " << maxVal << " at ("
		 << maxLoc.x << ", " << maxLoc.y << ")" << endl;
}

/*
 * Compute Maximum of color images by computing a channel wide norm
 * to find which is the greatest rather than mixing channels
 * @param src1 the first color (or gray) image
 * @param src2 the second color (or gray) image
 * @param dst the color (or gray) destination
 */
void CvColorSpaces::normMax(const Mat& src1, const Mat& src2, Mat& dst)
{
	// first check if src1, src2 && dst have the same sizes and type
	if ( (src1.rows == src2.rows) &&
		 (src1.rows == dst.rows) &&
		 (src1.cols == src2.cols) &&
		 (src1.cols == dst.cols) &&
		 (src1.type() == src2.type()) &&
		 (src1.type() == dst.type()) )
	{
		if (src1.type() == CV_8UC3)
		{
			// Compute max by pixel norm rather than mixing pixels
			for(int i = 0; i < src1.rows; ++i)
			{
				for (int j = 0; j < src1.cols; ++j)
				{
					/*
					 * TODO compute pixel norms from src1 & src2 using
					 * ddot (scalar product) on each pixel
					 * the result (dst) is the pixel with the greatest norm
					 */
                    Vec3b p1 = src1.at<Vec3b>(i,j);
                    Vec3b p2 = src2.at<Vec3b>(i,j);
                    if(p1.ddot(p1) > p2.ddot(p2)){
                        dst.at<Vec3b>(i,j) = p1;
                    }
                    else{
                        dst.at<Vec3b>(i,j) = p2;
                    }


				}
			}
		}
		else
		{
			// compute max the regular way with max function
			cv::max(src1, src2, dst);
		}
	}
	else
	{
		// Do nothing
		cerr << "CvColorSpaces::normMax : incompatible images" << endl;
	}
}


