/*
 * CvDFT.h
 *
 *  Created on: 21 févr. 2012
 *      Author: davidroussel
 */

#ifndef CVDFT_H_
#define CVDFT_H_

#include <vector>
using namespace std;

#include <cv.h>
using namespace cv;

#include "CvProcessor.h"

/**
 * Class to compute DFT on input image, then apply filters on the resulting
 * FFT and then process spectrum with inverse FFT to obtain filtered image.
 * input image can have single or multiple channels
 */
class CvDFT : virtual public CvProcessor
{
	public:

		/**
		 * Frenquency filter type
		 */
		typedef enum
		{
			/**
			 * Frequency Box filter.
			 * Inverse box filter is sinus cardinal
			 */
			BOX_FILTER = 0,
			/**
			 * Frequency gaussian filter.
			 * Inverse gaussian filter is gaussian
			 */
			GAUSS_FILTER,
			/**
			 * frequency sinus cardinal filter.
			 * Inverse sinus cardinal is box
			 */
			SINC_FILTER,
			/**
			 * Number of available filters
			 */
			NB_FILTERS
		} FilterType;

		/**
		 * Minimum log scale factor.
		 * Default value is 5.
		 */
		static const double minLogScaleFactor;

		/**
		 * Maximum log scale factor.
		 * Default value is 20 or 30.
		 */
		static const double maxLogScaleFactor;

	protected:
		/**
		 * Minimum of source image rows & cols for cropping source
		 */
		int minSize;

		/**
		 * Maximum of source image rows & cols for cropping source
		 */
		int maxSize;

		/**
		 * Border size to crop on source image
		 */
		int borderSize;

		/**
		 * DFT optimal size
		 */
		int optimalDFTSize;

		/**
		 * Frequency filtering status
		 */
		bool filtering;

		/**
		 * Type of frequency filter to apply
		 */
		FilterType filterType;

		/**
		 * Optimal Fourier size
		 */
		Size dftSize;

		/**
		 * Input frame cropped to square size for FFT: CV_8UC<nbChannels>
		 */
		Mat inFrameSquare;

		/**
		 * Input frame cropped color channels: CV_8UC1 x <nbChannels>
		 */
		vector<Mat> channels;

		/**
		 * Input frame square channels converted to doubles: CV_64FC1 x <nbChannels>
		 */
		vector<Mat> channelsDouble;

		/**
		 * Input frame square channels complex channels:
		 * CV_64FC1 x 2 x <nbChannels>
		 */
		vector<vector<Mat> > channelsDoubleComplexComponents;

		/**
		 * Input frame square complex image: CV_64FC2 x <nbChannels>
		 */
		vector<Mat> channelsComplexImages;

		/**
		 * Complex spectrum images: CV_64FC2 x <nbChannels>
		 */
		vector<Mat> channelsComplexSpectrums;

		/**
		 * Complex spectrum channels: CV_64FC1 x 2 x <nbChannels>
		 */
		vector<vector<Mat> > channelsComplexSpectrumComponents;

		/**
		 * Spectrum magnitude: CV_64FC1 x <nbChannels>
		 */
		vector<Mat> channelsSpectrumMagnitude;

		/**
		 * LogScale factor.
		 * Log scale factor
		 */
		double logScaleFactor;

		/**
		 * log spectrum magnitude: CV_64FC1 x <nbChannels>
		 */
		vector<Mat> channelsSpectrumLogMagnitude;

		/**
		 * [Log] spectrum magnitude channels converted for display:
		 * CV_8UC1 x <nbChannels>
		 */
		vector<Mat> channelsSpectrumLogMagnitudeDisplay;

		/**
		 * [Log] spectrum magnitude image converted for display:
		 * CV_8UC<nbChannels>
		 */
		Mat spectrumMagnitudeImage;

		/**
		 * Mask for lowpass filtering of each channel
		 * (white door/gaussian on black):
		 * CV_64FC1 x <nbChannels>
		 */
		vector<Mat> channelsLowPassMask;

		/**
		 * Mask for hipass filtering (black door/gaussian on white):
		 * CV_64FC1 x <nbChannels>
		 */
		vector<Mat> channelsHighPassMask;

		/**
		 * Mask for reverse hipass when Hipass needs to be reversed:
		 * CV_64F1 x <nbChannels>
		 */
		vector<Mat> channelsHighPassMaskReverse;

		/**
		 * Complete channel spectrum mask = channelsLowPassMask x channelsHighPassMask:
		 * CV_64FC1 x <nbChannels>
		 */
		vector<Mat> channelsSpectrumMask;

		/**
		 * Channel spectrum mask converted for display :
		 * CV_8UC1 x <nbChannels>
		 */
		vector<Mat> channelsSpectrumMaskDisplay;

		/**
		 * Spectrum mask image : CV_8UC<nbChannels>
		 */
		Mat spectrumMaskImage;

		/**
		 * Complex spectrum masked: CV_64FC2 x <nbChannels>
		 */
		vector<Mat> channelsComplexSpectrumsMasked;

		/**
		 * Complex channels resulting from inverse Fourier transform
		 * of the masked complex spectrums: CV_64FC2 x <nbChannels>
		 */
		vector<Mat> channelsComplexInverseImages;

		/**
		 * Complex inverse image channels: CV_64FC1 x 2 x <nbChannels>
		 */
		vector<vector<Mat> > channelsComplexInverseComponents;

		/**
		 * Real part of FFT inverse channels (with fft shift):
		 * CV_64FC1 x <nbChannels>
		 */
		vector<Mat> channelsRealInverse;

		/**
		 * Real part of FFT inverse channels converted for display:
		 * CV_8UC1 x <nbChannels>
		 */
		vector<Mat> channelsRealInverseDisplay;

		/**
		 * Image composed with display real parts: CV_8UC<nbChannels>
		 */
		Mat inverseImage;

		/**
		 * Maximum size of the filters (dftSize / sqrt(2.0))
		 */
		int filterMaxSize;

		/**
		 * Minimum size of the filters
		 */
		int filterMinSize;

		/**
		 * Low pass filter size for each channel (initialised to filterMaxSize
		 * for no filtering)
		 */
		vector<int> lowPassFilterSize;

		/**
		 * High pass filter size for each channel (initialised to 0)
		 */
		vector<int> highPassFilterSize;

	public:
		/**
		 * DFT processor constructor
		 * @param sourceImage the source image
		 * @pre source image is not NULL
		 */
		CvDFT(Mat * sourceImage);

		/**
		 * DFT Processor destructor
		 */
		virtual ~CvDFT();

		/**
		 * DFT Update.
		 * Steps in update
		 * 	- crop source image to a square according to optima FFT size
		 * 	- split in frame square into color channels
		 *	- converts these color channels to double
		 *	- apply frequency shift on double channels to
		 *		- produce the shifted real component of source channels
		 *		- produce later a spectrum with low frequencies at image center
		 *	- merge real/image channels into complex image per channel
		 *	- compute dft on each channel
		 *	- split channels complex spectrum in to real/imag components
		 *	- compute channels spectrum magnitude from real/imag components
		 *	- log scale channels spectrum magnitude
		 *	- if filtering
		 *		- fill lowpass channel masks with 0
		 *		- fill highpass channel masks with 1
		 *		- draw white low pass filter in lowpass channels
		 *		- draw white high pass filters in revrse highpass channels
		 *		- reverse highpass reverse channels to produce high pass
		 *		channels
		 *		- multiply lowpass & highpass channels into channel spectrum
		 *		masks
		 *		- multiply log magnitude spectrum channels by masks
		 *	- if not filtering then fill channels spectum masks with ones
		 *	- converts channels spectum masks for display
		 *	- converts channels log magnitude for display
		 *	- multiply channels complex spectrum components by masks
		 *	- perform inverse dft on masked spectrum channel complex to produce
		 *	inverse complex channels
		 *	- split inverse channels complex image into real/imag components
		 *	- perform frequency shift on real part o channels inverse component
		 *	- convert channels real inverse part for display
		 *	- merge channels spectrum log magnidude channels to displayable
		 *	image
		 *	- merge channels spectrum masks into a displayable image
		 *	- merge real channels of inverse dft into displayable image
		 */
		virtual void update();

		// --------------------------------------------------------------------
		// Options settings and gettings
		// --------------------------------------------------------------------

		/**
		 * Filter type read access
		 * @return the current filter type
		 */
		FilterType getFilterType() const;

		/**
		 * Filter type setting
		 * @param filterType ne new filter type
		 */
		virtual void setFilterType(const FilterType filterType);

		/**
		 * Optimal dft size for current source image
		 * @return the current optimal dft size
		 */
		int getOptimalDftSize() const;

		/**
		 * Filtering status
		 * @return the filtering status. true if filtering is on, false
		 * otherwise
		 */
		bool isFiltering() const;

		/**
		 * Setting filtering status
		 * @param filtering ne new filtering status
		 */
		virtual void setFiltering(bool filtering);

		/**
		 * Get current log scale factor
		 * @return the current log scale factor
		 */
		double getLogScaleFactor() const;

		/**
		 * Setting the log scale factor
		 * @param logScaleFactor the new log scale factor
		 */
		virtual void setLogScaleFactor(double logScaleFactor);

		/**
		 * Returns min filter size for current image (generally 0)
		 * @return the minimum filter size
		 */
		int getMinFilterSize() const;

		/**
		 * Returns max filter size for current image
		 * @return the maximum filter size
		 */
		int getMaxFilterSize() const;

		/**
		 * Low pass filter size read access
		 * @param channel channel index
		 * @return the current low pass filter size or -1 if channel is invalid
		 */
		int getLowPassFilterSize(const int channel = 0) const;

		/**
		 * Low pass filter size setting
		 * @param channel channel index. If channel index == number of channels
		 * then set value for all channels
		 * @param filterSize the new value of low pass filter size.
		 * @note filterSize is limited to range
		 * [highPassFilterSize...filterMaxSize]
		 */
		virtual void setLowPassFilterSize(const int channel,
										  const int filterSize);

		/**
		 * High pass filter size read access
		 * @param channel channel index
		 * @return the current high pass filter size or -1 if channel is invalid
		 */
		int getHighPassFilterSize(const int channel = 0) const;

		/**
		 * High pass filter size setting
		 * @param channel channel index. If channel index == number of channels
		 * then set value for all channels
		 * @param filterSize the new value of high pass filter size.
		 * @note filterSize is limited to range
		 * [filterMinSize...lowPassFilterSize]
		 */
		virtual void setHighPassFilterSize(const int channel,
										   const int filterSize);

	protected:

		// --------------------------------------------------------------------
		// Setup and cleanup attributes
		// --------------------------------------------------------------------

		/**
		 * Setup internal attributes according to source image
		 * @param sourceImage a new source image
		 * @param fullSetup full setup is needed when source image is changed
		 */
		void setup(Mat * sourceImage, bool fullSetup = true);

		/**
		 * Clean up internal atrtibutes before changing source image or
		 * cleaning up class before destruction
		 */
		void cleanup();

		// --------------------------------------------------------------------
		// Utility methods
		// --------------------------------------------------------------------
		/**
		 * Modify image to obtain reverse frequencies on the Fourier transform
		 * (low frequencies at the center of the image and high frequencies on
		 * the border), or modify image obtained from reverse Fourier transform
		 * with reversed frequencies.
		 * @param imgIn source image
		 * @param imgOut destination image
		 * @par Algorithm:
		 * This is based on the following property of the Z transform :
		 * \f[
		 * 	TZ\left\{a^{k} x_{k}\right\} = X\left(\frac{z}{a}\right)
		 * \f]
		 * if \f$y_{k} = (-1)^{k} x_{k}\f$ then \f$Y(z) = X(-z)\f$
		 * which can be explained in Fourier space by replacing
		 * \f$z\f$ by \f$e^{j 2 \pi F}\f$:
		 * \f[
		 * Y\left[e^{j 2 \pi F}\right] = X\left[-e^{j2\pi F}\right] =
		 * X\left[e^{j\pi}e^{j2\pi F}\right] =
		 * X\left[e^{j2\pi\left(F + \frac{1}{2}\right)}\right]
		 * \f]
		 * hence
		 * \f[
		 * Y(F) = X\left(F + \frac{1}{2}\right)
		 * \f]
		 * or
		 * \f[
		 * Y(f) = X\left(f + \frac{f_{e}}{2}\right)
		 * \f]
		 * where \f$f_{e}\f$ is the sampling frequency, which means the
		 * resulting Fourier transform will present an \f$\frac{f_{e}}{2}\f$
		 * frequency offset. And since the sampling frequency lies in the middle
		 * of the spectrum in the DFT. Low frequencies will appear centered
		 * around the middle of the spectrum.
		 *
		 * In 2D the algorithm is the following:
		 * \f[
		 * imgOut(i,j) = (-1)^{i+j} \cdot imgIn(i,j)
		 * \f]
		 * \f$f_{e}\f$ is at the center of the spectrum image in 2D, which
		 * means, low frequencies will be located at the center of the image.
		 */
		template <typename T>
		void frequencyShift(Mat & imgIn, Mat & imgOut);

		/**
		 * Computes a 2D gaussian on image
		 * @param image output (and/or input) image
		 * @param x0 x center
		 * @param y0 y center
		 * @param sigma gaussian width (at half height). If sigma <= 0 no
		 * output is performed
		 * @param amp amplitude
		 * @post Compute a 2D gaussian in image:
		 * \f[
		 * g(x,y) = amp \cdot exp^{-
		 * \left(
		 * 	\frac{(x - x_{0})^{2} + (y - y_{0})^{2}}{2 \sigma^{2}}
		 * 	\right)
		 * 	}
		 * \f]
		 */
		template <typename T>
		void gaussian2D(Mat & image, double x0, double y0, double sigma,
			double amp);
		/**
		 * Computes a 2D sinc on image
		 * @param image output (and/or input) image
		 * @param x0 x center
		 * @param y0 y center
		 * @param sigma width (at half height). If sigma <= 0 no
		 * output is performed
		 * @param amp amplitude
		 */
		template <typename T>
		void sinc2D(Mat & image, double x0, double y0, double sigma,
			double amp);

		/**
		 * Log scale T valued image
		 * @param imgIn input image
		 * @param imgOut output image
		 * @param scaleFactor such as
		 * \f$ imgOut = scaleFactor \times \log(1 + imgIn)\f$
		 */
		template <typename T>
		void logScaleImg(const Mat & imgIn, Mat & imgOut, const T scaleFactor);

		/**
		 * Negate image
		 * @param imgIn input image
		 * @param imgOut reversed output image
		 * @param value value to reverse from
		 * @code
		 * imageOut(i,j) = value - imageIn(i,j)
		 * @endcode
		 */
		template <typename T>
		void reverseValues(const Mat & imgIn, Mat & imgOut,
						   const T value = numeric_limits<T>::max());
};

#endif /* CVDFT_H_ */
