/*
 * Palette.h
 *
 *  Created on: 13 sept. 2010
 *      Author: David Roussel
 */

#ifndef PALETTE_H_
#define PALETTE_H_

#include <opencv2/core/core.hpp>	// for Mat
using namespace cv;

#include <vector>
using namespace std;

/**
 * Palette loads colormap from files or static arrays and apply it to a single
 * channel image (8 bits single channel image : CV_8UC1) in order to rebuild a
 * BGR image featuring the colors in the palette.
 * A Colormap is composed of 256 RGB values that should be applied for each
 * level (from 0 to 255) of the single channel image.
 * colormap is applied
 * @warning colormap are stored in RGB order, but OpenCV images are stored in
 * BGR order.
 */
class Palette
{
	protected:
		/**
		 * RGB colormap
		 * 	- Red colormap is first component
		 * 	- Green colormap is second component
		 * 	- Blue colormap is third component
		 */
		vector<Mat> colormap;

		/**
		 * Minimum value in the palette.
		 * In order to check invalid values in the palette
		 */
		int minValue;

		/**
		 * Maximum value in the palette.
		 * In order to check invalid values in the palette
		 */
		int maxValue;

		/**
		 * BGR BGRChannels of the resulting image
		 */
		vector<Mat> BGRChannels;

		/**
		 * Checks if channels have been allocated yet.
		 * Channels may be allocated only when they are not or when they
		 * does not fit the image dimension provided in applyPalette methods.
		 * In this case, if BGRChannels have been allocated they are released and
		 * recreated.
		 */
		bool channelsAllocated;

		/**
		 * Number of elements in the colormap : 256
		 */
		static const size_t CMAPSIZE;

		/**
		 * Number of components in the color image
		 */
		static const size_t COMPSIZE;

	public:
		/**
		 * Constructor from bidimensional array
		 * @param map bidimensional array containing palette values
		 * @param min  minimum value in the palette (default is 0)
		 * @param max maximum value in the palette (default is 255)
		 */
		Palette(uchar map[][3], int min = 0, int max = 255);

		/**
		 * Constructor from file name.
		 * List of operations :
		 * 	- opens the file
		 * 	- if file is correctly opened, then reads each line (ignoring lines
		 * 	starting with a "#" which indicates a comment line)
		 * 	- each line should contain 3 bytes : e.g. 127 0 255
		 * @param filename the name of the file to read
		 * @param min minimum value in the palette (default is 0)
		 * @param max maximum value in the palette (default is 255)
		 */
		Palette(const char * const filename, int min=0, int max = 255);

		/**
		 * Palette destructor.
		 * Relese all images and clear vectors
		 */
		virtual ~Palette();

		/**
		 * Apply the colormap on the single channel source image to build
		 * a destination 3 channels color image.
		 * @param src source mono-channel image
		 * @param dst destination BGR-BGRChannels image
		 */
		void applyPalette(const Mat & src, Mat & dst);
};

#endif /* PALETTE_H_ */
