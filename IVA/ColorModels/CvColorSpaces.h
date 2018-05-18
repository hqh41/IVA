/*
 * CvColorSpaces.h
 *
 *  Created on: 25 févr. 2012
 *      Author: davidroussel
 */

#ifndef CVCOLORSPACES_H_
#define CVCOLORSPACES_H_

#include <vector>
using namespace std;

#include "CvProcessor.h"
#include "Palette.h"

/**
 * Class to process source image into several color spaces such as RGB, HSV and
 * YCbCr
 */
class CvColorSpaces : public virtual CvProcessor
{
	public:
		/**
		 * Indices of colors to show in color components
		 */
		typedef enum
		{
			BINDEX = 0,	//!< index for blue
			GINDEX,		//!< index for green
			RINDEX,		//!< index for red
			MAXINDEX,	//!< index for maximum of RGB (or BGR)
			HINDEX,		//!< index for hue
			CbINDEX,	//!< index for cb
			CrINDEX,	//!< index for cr
			NbShows		//!< NbShows
		} ShowColor;

		/**
		 * Image type selected for display
		 */
		typedef enum
		{
			INPUT = 0,	//!< color input image is selected for display
			GRAY,		//!< gray input image is selected for display
			RED,		//!< red component from BGR is selected for display
			GREEN,		//!< green component from BGR is selected for display
			BLUE,		//!< blue component from BGR is selected for display
			MAX_BGR,	//!< Maximum of R, G and B components
			XYZ_X,		//!< X component of XYZ space
			XYZ_Y,		//!< Y component of XYZ space
			XYZ_Z,		//!< Z component of XYZ space
			HUE,		//!< Hue component from HSV is selected for display
			SATURATION,	//!< Saturation component from HSV is selected for display
			VALUE,		//!< Lightness component from HSV is selected for display
			Y,			//!< Lightness component from YCrCb is selected for display
			Cr,			//!< Green/Magenta Cr component from YCrCb is selected for display
			Cb,			//!< Yellow/Blue Cb component from YCrCb is selected for display
			NbSelected
		} Display;

		/**
		 * Hue image display mode
		 */
		typedef enum
		{
			HUECOLOR=0,		//!< Normal Hue mode
			HUESATURATE,	//!< Hue*Saturation mode
			HUEVALUE,		//!< Hue*Value mode
			HUEGRAY,		//!< Gray mode
			NBHUES			//!< Number of Hue display modes
		} HueDisplay;

	protected :

		/**
		 * Image displayed
		 */
		Mat displayImage;

		/**
		 * Gray converted image
		 */
		Mat inFrameGray;

		/**
		 * BGR individual channels
		 */
		vector<Mat> bgrChannels;

		/**
		 * BGR colored images built from individual channels and palettes
		 */
		Mat bgrColoredChannels[3];

		/**
		 * Maximum of B & G channels
		 */
		Mat maxBGChannels;

		/**
		 * Maximum of maxBGChannels and R channel
		 */
		Mat maxBGRChannels;

		/**
		 * Colored maximum of B & G channels
		 */
		Mat maxBGChannelsColor;

		/**
		 * Colored Maximum of maxBGChannels and R channel
		 */
		Mat maxBGRChannelsColor;

		/**
		 * XYZ floating point converted image
		 */
		Mat inFrameXYZ;

		/**
		 * XYZ floating point channels
		 */
		Mat xyzGrayChannels[3];

		/**
		 * XYZ channels normalized to 0..255
		 */
		Mat xyzDisplayChannels[3];

		/**
		 * HSV converted image
		 */
		Mat inFrameHSV;

		/**
		 * HSV individual channels
		 */
		vector<Mat> hsvChannels;

		/**
		 * Hue colored image built from hue component and hsv palette
		 */
		Mat hueColorImage;

		/**
		 * Hue Mix channels to build hue colored display image
		 */
		Mat hueMixChannels[3];

		/**
		 * Hue image built from hueMixChannels
		 */
		Mat hueMixImage;

		/**
		 * Hue colored mixed image normalized from hueMixImage
		 */
		Mat hueMixedColorImage;

		/**
		 * Mix mode to create hue colored image
		 */
		HueDisplay hueDisplay;

		/**
		 * YCbCr converted image
		 */
		Mat inFrameYCrCb;

		/**
		 * YCbCr channels
		 */
		vector<Mat> yCrCbChannels;

		/**
		 * Cr colored image
		 */
		Mat crColoredImage;

		/**
		 * Cb colored image
		 */
		Mat cbColoredImage;

		/**
		 * Palette to build colored red component image
		 */
		Palette redMap;

		/**
		 * Palette to build colored green component image
		 */
		Palette greenMap;

		/**
		 * Palette to build colored blue component image
		 */
		Palette blueMap;

		/**
		 * Pointers to RGB palettes
		 * pointing respectively to
		 *	- blueMap
		 *	- greenMap
		 *	- redMap
		 */
		Palette * bgrMap[3];

		/**
		 * Palette for hue component
		 */
		Palette hMap;

		/**
		 * Palette for Cb component
		 */
		Palette cbMap;

		/**
		 * Palette for Cr component
		 */
		Palette crMap;

		/**
		 * Booleans to choose to display channels as grayscale
		 * or colored images
		 */
		bool showColorChannel[NbShows];

		/**
		 * Selected image type to display
		 */
		Display imageDisplayIndex;

		/**
		 * True when display image changed since last update
		 */
		bool displayImageChanged;

	public :
		/**
		 * Color spaces constructor
		 * @param inFrame input image
		 */
		CvColorSpaces(Mat * inFrame);

		/**
		 * Color spaces destructor
		 */
		virtual ~CvColorSpaces();

		/**
		 * Update compute selected image for display according to
		 * selected parameters such as imageDisplayIndex, showColorChannel,
		 * and eventually hueDisplay
		 */
		virtual void update();

		/**
		 * Get currently selected image index
		 * @return the currently selected image for display index
		 */
		Display getDisplayImageIndex();

		/**
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
		 * @param index select the index to select display image
		 */
		virtual void setDisplayImageIndex(const Display index);

		/**
		 * Get the color display status for specific channels (such as red,
		 * green, blue, hue ...)
		 * @param c the channel to get color display status:
		 * 	- BINDEX color display status for blue component
		 * 	- GINDEX color display status for green component
		 * 	- RINDEX color display status for red component
		 * 	- HINDEX color display status for hue component
		 * 	- CbNDEX color display status for Cb component
		 * 	- CrNDEX color display status for Cr component
		 * @return the color display status of selected component
		 */
		bool getColorChannel(const ShowColor c);

		/**
		 * Sets the color display status of selected component
		 * @param c the selected component:
		 * 	- BINDEX color display status for blue component
		 * 	- GINDEX color display status for green component
		 * 	- RINDEX color display status for red component
		 * 	- HINDEX color display status for hue component
		 * 	- CbNDEX color display status for Cb component
		 * 	- CrNDEX color display status for Cr component
		 * @param value the value to set on the selected component
		 */
		virtual void setColorChannel(const ShowColor c, const bool value);

		/**
		 * Get currently selected hue display mode
		 * @return the currenlty selected hue display mode
		 */
		HueDisplay getHueDisplaymode();

		/**
		 * Select hue display mode :
		 *	- HUECOLOR Normal Hue mode
		 *	- HUESATURATE Hue*Saturatin mode
		 *	- HUEVALUE Hue*Value mode
		 *	- HUEGRAY Gray mode
		 * @param mode the mode so select
		 */
		virtual void setHueDisplayMode(const HueDisplay mode);

		/**
		 * Gets the image selected for display
		 * @return the display image
		 */
		Mat & getDisplayImage();

	protected:
		// --------------------------------------------------------------------
		// Setup and cleanup attributes
		// --------------------------------------------------------------------
		/**
		 * Setup internal attributes according to source image
		 * @param sourceImage a new source image
		 * @param fullSetup full setup is needed when source image is changed
		 * @pre sourceimage is not NULL
		 * @note this method should be reimplemented in sub classes
		 */
		virtual void setup(Mat * sourceImage, bool fullSetup = true);

		/**
		 * Clean up internal attributes before changing source image or
		 * cleaning up class before destruction
		 * @note this method should be reimplemented in sub classes
		 */
		virtual void cleanup();

		/**
		 * Show Min and Max values and locations for a matrix
		 * @param m the matrix to consider
		 */
		static void showMinMaxLoc(const Mat & m);

		/**
		 * Compute Maximum of color images by comparing pixel norm
		 * rather than a per channel max like the openCV max function
		 * @param src1 the first color (or gray) image
		 * @param src2 the second color (or gray) image
		 * @param dst the color (or gray) destination
		 * @pre the norm max is only computed if arguments are of type CV_8UC3,
		 * otherwise ordinary max is performed
		 */
		static void normMax(const Mat& src1, const Mat& src2, Mat& dst);
};

#endif /* CVCOLORSPACES_H_ */
