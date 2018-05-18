/*
 * CvFloodFill.h
 *
 *  Created on: 22 mars 2012
 *      Author: davidroussel
 */

#ifndef CVGFLOODFILL_H_
#define CVGFLOODFILL_H_

#include "CvProcessor.h"

/**
 * Class to process source image with gaussian filters
 */
class CvFloodFill: virtual public CvProcessor
{
	public:
		/**
		 * Image Display type
		 */
		typedef enum
		{
			INPUT_IM = 0, //!< Input image
			MASK_IM, //!< Flood fill mask
			MERGED_IM, //!< Mixes Input dans flood fill image
			NBDISPLAY_IM //!< Number of elements in this enum
		} ImageDisplay;

		/**
		 * Flood Fill mode
		 */
		typedef enum
		{
			/**
			 * Fixed range, lower and upper threshold for pixel aggregation criteria
			 * are absolute
			 */
			FIXED_RANGE = 1,
			/**
			 * Floating range, lower and upper threshold of pixel aggregation criteria
			 * are floating (absolute compared to the value of the current pixel to
			 * aggregate neighbors with).
			 */
			FLOATING_RANGE = 2,
			NBFILLING_MODES
		} FloodFillMode;

	protected:
		// --------------------------------------------------------------------
		// image parameters
		// --------------------------------------------------------------------
		/**
		 * Size of all processed images: sourceImage->size()
		 */
		Size dim;

		/**
		 * Image displayed
		 */
		Mat displayImage;

		/**
		 * True when display image changed since last update
		 */
		bool displayImageChanged;

		/**
		 * Mask image
		 */
		Mat mask;

		/**
		 * Merged Source and flood fill image
		 */
		Mat merged;

		/**
		 * Image display mode.
		 */
		ImageDisplay displayMode;

		// -------------------------------------------------------------------
		// Flood parameters
		// -------------------------------------------------------------------
		/**
		 * indicates a manual seed has been provided and initialSeed can be
		 * used to flood the image.
		 * seeded can be reset to false in order to cancel current flood.
		 * @warning reset seeded to false should also cause flooded to be
		 * reset to false.
		 * [initial value is false]
		 */
		bool seeded;

		/**
		 * Indicates image has been flooded at least once and barycenter
		 * of the flooded area (centerSeed) can be used to seed the flood of
		 * the next image.
		 * flooded is reset when a new manual seed is provided
		 * [initial value is false]
		 */
		bool flooded;

		/**
		 * flooding fill mode [default value is 1]
		 * 	- 1: Fixed range flood fill mode
		 * 	- 2: Gradient (floating range) floodfill mode
		 */
		FloodFillMode ffillMode;

		/**
		 * Lower difference for pixel aggregation [default value is 20]
		 */
		int loDiff;

		/**
		 * upper difference for pixel aggregation [default value is 20]
		 */
		int upDiff;

		/**
		 * pixel connectivity for flood fill [default value is 4]
		 */
		int connectivity;

		/**
		 * Is source image color ?  [default value is true]
		 */
		bool isColor;

		/**
		 * New mask value (old mask values are thresholded to 128)
		 *  [default value is 255]
		 */
		int newMaskVal;

		/**
		 * Flood flags computed from conenctivity, newMaskVal and ffillMode such
		 * that
		 * @code
		 * 	flags = connectivity + (newMaskVal << 8) +
		 * 	(ffillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
		 * @endcode
		 */
		int floodFlags;

		/**
		 * Number of pixels in the flooded area
		 */
		int floodArea;

		/**
		 * The initial seed for flood fill obtained from user click
		 *  [default value is (-1, -1) when initial seed is not set]
		 */
		Point initialSeed;

		/**
		 * The seed for next image obtained from flooded area barycenter
		 * [default value is (-1, -1) when initial seed is not set]
		 */
		Point centerSeed;

		/**
		 * Show/Hides seed point in source image and merged image
		 */
		bool showSeed;

		/**
		 * Flood color to use in the merged image
		 */
		Scalar floodColor;

		/**
		 * Flooded area bounding box
		 */
		Rect floodBoundingBox;

		/**
		 * Show/Hides flooded area bounding box in source image
		 */
		bool showBoundingBox;

		// --------------------------------------------------------------------
		// Utility methods
		// --------------------------------------------------------------------
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

		/**
		 * Compute barycenter of last flooded mask
		 * @param mask the mask image where mask pixels are set to newMaskVal
		 * @param center the barycenter point computed here
		 * @param threshold the value to use as threshold to find flooded area
		 * pixels in the mask image
		 * @note One can also use the OpenCV function moments(...) to compute
		 * all moments up to the third order but we only need m00 (number of
		 * pixels of the flooded area) and m01 & m10 to compute flooded area
		 * center = (m10/m00, m01/m00).
		 * @return true if there is some flooded pixels in the mask to compute
		 * a barycenter, false otherwise.
		 * @note we need to know if flooding has failed as we should reset
		 * seeded and flooded variables accordingly
		 */
		template<typename T>
		bool computeFloodCenter(const Mat & mask,
								Point & center,
								const T threshold = numeric_limits<T>::max());
	public:
		/**
		 * Flood fill class constructor
		 * @param sourceImage
		 */
		CvFloodFill(Mat *sourceImage);

		/**
		 * Flood fill class destructor
		 */
		virtual ~CvFloodFill();

		/**
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
		virtual void update();

		// --------------------------------------------------------------------
		// ImageDisplay image related methods
		// --------------------------------------------------------------------
//		/**
//		 * Gets displayImageChanged current status when display image is changed
//		 * @return the current displayImageChanged value
//		 */
//		bool isDisplayImageChanged();

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
		 * Gets Image reference corresponding to the current displayMode and
		 * edgeMode
		 * @return Image reference corresponding to the current displayMode and
		 * edgeMode
		 */
		const Mat & getDisplayImage() const;

		/**
		 * Gets Image pointer corresponding to the current displayMode and
		 * edgeMode
		 * @return Image reference corresponding to the current displayMode and
		 * edgeMode
		 */
		Mat * getDisplayImagePtr();

		// --------------------------------------------------------------------
		// Flood related methods
		// --------------------------------------------------------------------
		/**
		 * Clears flood and reset seede and flooded values to false;
		 */
		void clearFlood();

		/**
		 * Gets the seeded status of the image
		 * @return true if there is a seed, false otherwise
		 */
		bool isSeeded() const;

		/**
		 * Gets the flooded status of the image
		 * @return true if image has been flooded, false otherwise
		 */
		bool isFlooded() const;

		/**
		 * Gets the current flooding mode (absolute or relative)
		 * @return the current floodin mode
		 */
		FloodFillMode getFfillMode() const;

		/**
		 * Sets a new flooding mode (absolute or relative
		 * @param ffillMode the new flooding mode
		 */
		virtual void setFfillMode(const FloodFillMode ffillMode);

		/**
		 * Gets the lower difference in pixel values for flooding
		 * @return the current lower difference for flooding
		 */
		int getLoDiff() const;

		/**
		 * Sets a new lower difference in pixels values for flooding
		 * @param loDiff the new lower difference for flooding
		 */
		virtual void setLoDiff(const int loDiff);

		/**
		 * Gets loDiff pointer.
		 * OpenCV trackbars require direct access to values
		 * @return the address of loDiff attribute
		 */
		int * getLoDiffPtr();

		/**
		 * Gets the upper difference in pixel values for flooding
		 * @return the current upper difference for flooding
		 */
		int getUpDiff() const;

		/**
		 * Sets a new upper difference in pixels values for flooding
		 * @param upDiff the new upper difference for flooding
		 */
		virtual void setUpDiff(const int upDiff);

		/**
		 * Gets upDiff pointer.
		 * OpenCV trackbars require direct access to values
		 * @return the address of upDiff attribute
		 */
		int * getUpDiffPtr();

		/**
		 * Gets the current connectivity for pixels neighbors for flooding
		 * @return the current connectivity for pixels neighbors for flooding
		 */
		int getConnectivity() const;

		/**
		 * Sets a new connectivity for pixels neighbors for flooding
		 * @param connectivity the new connectivity for pixels neighbors
		 * for flooding
		 */
		virtual void setConnectivity(const int connectivity);

		/**
		 * Gets the current color status of the source image
		 * @return the current color status of the source image
		 */
		bool getIsColor() const;

		/**
		 * Gets the current initial seed
		 * @return the current initial seed
		 * @note use isSeeded to check if there is an initial seed
		 */
		const Point & getInitialSeed() const;

		/**
		 * Sets an new initial seed
		 * @param initialSeed the new initial seed
		 */
		virtual void setInitialSeed(const Point & initialSeed);

		/**
		 * Gets the current flooded area center for future seed
		 * @return the current flooded area center
		 * @note use isFlooded to check image has been flooded
		 */
		const Point & getCenterSeed() const;

		/**
		 * Gets current show/hide seed point status
		 * @return the current show/hide seed point status
		 */
		bool isShowSeed() const;

		/**
		 * Sets new show/hide seed point status
		 * @param showSeed the new show/hide seed point status
		 */
		virtual void setShowSeed(const bool showSeed);

		/**
		 * Generates a new random color for floodColor
		 */
		void newFloodColor();

		/**
		 * Gets the current flooded area bounding box
		 * @return the current flooded area bounding box
		 * @note use isFlooded to check image has been flooded
		 */
		const Rect & getFloodBoundingBox() const;

		/**
		 * Gets the current show/hide bounding box status
		 * @return the current show/hide bounding box status
		 */
		bool isShowBoundingBox() const;

		/**
		 * Set the show/hide bounding box status
		 * @param showBoundingBox the new show/hide bounding box status
		 */
		virtual void setShowBoundingBox(const bool showBoundingBox);
};

#endif /* CVGFLOODFILL_H_ */
