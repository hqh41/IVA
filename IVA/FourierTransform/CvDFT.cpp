/*
 * CvDFT.cpp
 *
 *  Created on: 21 févr. 2012
 *      Author: davidroussel
 */

#include <limits>
#include <cmath>

//#include <iostream>
//using namespace std;

#include <opencv2/imgproc/imgproc.hpp>

#include "CvDFT.h"

/*
 * Minimum log scale factor.
 * Default value is 5.
 */
const double CvDFT::minLogScaleFactor = 5.0;

/*
 * Maximum log scale factor.
 * Default value is 20.
 */
const double CvDFT::maxLogScaleFactor = 30.0;

/*
 * DFT processor constructor
 * @param sourceImage the source image
 */
CvDFT::CvDFT(Mat * sourceImage) :
	CvProcessor(sourceImage),
	minSize(MIN(sourceImage->rows, sourceImage->cols)),
	maxSize(MAX(sourceImage->rows, sourceImage->cols)),
	borderSize((maxSize-minSize)/2),
	optimalDFTSize(getOptimalDFTSize(minSize)),
	filtering(false),
	filterType(BOX_FILTER),
	dftSize(optimalDFTSize, optimalDFTSize),
	inFrameSquare(dftSize, type),
	logScaleFactor(10.0),
	spectrumMagnitudeImage(dftSize, type),
	spectrumMaskImage(dftSize, type),
	inverseImage(dftSize, type),
	filterMaxSize((int)((double)optimalDFTSize / sqrt(2.0))),
	filterMinSize(0)
{
	setup(sourceImage, false);

	addImage("square", &inFrameSquare);
	addImage("mask", &spectrumMaskImage);
	addImage("spectrum", &spectrumMagnitudeImage);
	addImage("inverse", &inverseImage);
}

/*
 * DFT Processor destructor
 */
CvDFT::~CvDFT()
{
	cleanup();
}

/*
 * Setup internal attributes according to source image
 * @param sourceImage a new source image
 * @param fullSetup full setup is needed when source image is changed
 */
void CvDFT::setup(Mat *sourceImage, bool fullSetup)
{
	// Full setup starting point (already performed in constructor)
	if (fullSetup)
	{
		CvProcessor::setup(sourceImage, fullSetup);
		minSize = MIN(sourceImage->rows, sourceImage->cols);
		maxSize = MAX(sourceImage->rows, sourceImage->cols);
		borderSize = (maxSize-minSize)/2;
		optimalDFTSize = getOptimalDFTSize(minSize);
		dftSize.height = optimalDFTSize;
		dftSize.width = optimalDFTSize;
		inFrameSquare = Mat(dftSize, type);
//		logScaleFactor = 10.0;
		spectrumMagnitudeImage = Mat(dftSize, type);
		spectrumMaskImage = Mat(dftSize, type);
		inverseImage = Mat(dftSize, type);
		filterMaxSize = (int)((double)optimalDFTSize / sqrt(2.0));
		filterMinSize = 0;
	}

	// Partial setup starting point
	for (int i=0; i < nbChannels; i++)
	{
		channels.push_back(Mat(dftSize, CV_8UC1));
		channelsDouble.push_back(Mat(dftSize, CV_64FC1));
		channelsDoubleComplexComponents.push_back(vector<Mat>());
		channelsComplexImages.push_back(Mat(dftSize, CV_64FC2));
		channelsComplexSpectrums.push_back(Mat(dftSize, CV_64FC2));
		channelsComplexSpectrumComponents.push_back(vector<Mat>());
		channelsSpectrumMagnitude.push_back(Mat(dftSize, CV_64FC1));
		channelsSpectrumLogMagnitude.push_back(Mat(dftSize, CV_64FC1));
		channelsSpectrumLogMagnitudeDisplay.push_back(Mat(dftSize, CV_8UC1));
		channelsLowPassMask.push_back(Mat(dftSize, CV_64FC1));
		channelsHighPassMask.push_back(Mat(dftSize, CV_64FC1));
		channelsHighPassMaskReverse.push_back(Mat(dftSize, CV_64FC1));
		channelsSpectrumMask.push_back(Mat(dftSize, CV_64FC1));
		channelsSpectrumMaskDisplay.push_back(Mat(dftSize, CV_8UC1));
		channelsComplexSpectrumsMasked.push_back(Mat(dftSize, CV_64FC2));
		channelsComplexInverseImages.push_back(Mat(dftSize, CV_64FC2));
		channelsComplexInverseComponents.push_back(vector<Mat>());
		channelsRealInverse.push_back(Mat(dftSize, CV_64FC1));
		channelsRealInverseDisplay.push_back(Mat(dftSize, CV_8UC1));

		// complex channels
		for (int j=0; j < 2; j++)
		{
			channelsDoubleComplexComponents[i].push_back(Mat(dftSize, CV_64FC1));
			channelsComplexSpectrumComponents[i].push_back(Mat(dftSize, CV_64FC1));
			channelsComplexInverseComponents[i].push_back(Mat(dftSize, CV_64FC1));
		}

		lowPassFilterSize.push_back(filterMaxSize);
		highPassFilterSize.push_back(filterMinSize);

		// fill complex channels of channelsDoubleComplexComponents with 0
		channelsDoubleComplexComponents[i][1] = Scalar(0.0);
	}
}

void CvDFT::cleanup()
{
	for (int i=0; i < nbChannels; i++)
	{
		// complex channels
		for (int j=0; j < 2; j++)
		{
			channelsComplexInverseComponents[i][j].release();
			channelsComplexSpectrumComponents[i][j].release();
			channelsDoubleComplexComponents[i][j].release();
		}

		channelsRealInverseDisplay[i].release();
		channelsRealInverse[i].release();
		channelsComplexInverseComponents[i].clear();
		channelsComplexInverseImages[i].release();
		channelsComplexSpectrumsMasked[i].release();
		channelsSpectrumMaskDisplay[i].release();
		channelsSpectrumMask[i].release();
		channelsHighPassMask[i].release();
		channelsHighPassMaskReverse[i].release();
		channelsLowPassMask[i].release();
		channelsSpectrumLogMagnitudeDisplay[i].release();
		channelsSpectrumLogMagnitude[i].release();
		channelsSpectrumMagnitude[i].release();
		channelsComplexSpectrumComponents[i].clear();
		channelsComplexSpectrums[i].release();
		channelsComplexImages[i].release();
		channelsDoubleComplexComponents[i].clear();
		channelsDouble[i].release();
		channels[i].release();
	}

	highPassFilterSize.clear();
	lowPassFilterSize.clear();
	channelsRealInverseDisplay.clear();
	channelsRealInverse.clear();
	channelsComplexInverseComponents.clear();
	channelsComplexInverseImages.clear();
	channelsComplexSpectrumsMasked.clear();
	channelsSpectrumMaskDisplay.clear();
	channelsSpectrumMask.clear();
	channelsHighPassMask.clear();
	channelsHighPassMaskReverse.clear();
	channelsLowPassMask.clear();
	channelsSpectrumLogMagnitudeDisplay.clear();
	channelsSpectrumLogMagnitude.clear();
	channelsSpectrumMagnitude.clear();
	channelsComplexSpectrumComponents.clear();
	channelsComplexSpectrums.clear();
	channelsComplexImages.clear();
	channelsDoubleComplexComponents.clear();
	channelsDouble.clear();
	channels.clear();

	inverseImage.release();
	spectrumMaskImage.release();
	spectrumMagnitudeImage.release();
	inFrameSquare.release();

	// super cleanup
	CvProcessor::cleanup();
}

/*
 * Update
 */
void CvDFT::update()
{
//	clog << "CvDFT::update()" << endl;

	Scalar one(1.0);
	Scalar zero(0.0);
	/*
	 * Crop source image to center square and resize it to nearest
	 * DFT optimal size
	 */
	if (sourceImage->cols > sourceImage->rows)
	{
		resize(sourceImage->colRange(borderSize, borderSize + minSize),
			   inFrameSquare,
			   dftSize,
			   0,
			   0,
			   INTER_AREA);
	}
	else
	{
		resize(sourceImage->rowRange(borderSize, borderSize + minSize),
			   inFrameSquare,
			   dftSize,
			   0,
			   0,
			   INTER_AREA);
	}

	/*
	 * Split input frame square to individual channels
	 */
	split(inFrameSquare, channels);

	// Process each component
	for (int i=0; i < nbChannels; i++)
	{
		/*
		 * Fourier transform processing
		 * 	- Convert uchar center square image to CV_64F real component
		 * 	- perform frequency shift on real image to obtain low frequencies
		 * 		in the middle of the DFT image rather than in the corners
		 * 	- merge real & imag component to complexImage before DFT
		 * 		imag component could be filled with 0
		 * 	- compute DFT
		 * 	- split DFT channels
		 * 	- compute DFT magnitude from DFT channels
		 * 	- logScale magnitude with factor (5 to 20)
		 * 	- convertScaleAbs logMagnitude to CV_8UC1 to display image
		 *
		 */

		// convert component to float
		channels[i].convertTo(channelsDouble[i], CV_64FC1);

		// Frequency shift channelsDouble to real complex component
		// Frequency shift allow to prepare spatial image components to
		// produce frequency image later with low frequencies in the center
		// of frequency image
		frequencyShift<double>(channelsDouble[i],
							   channelsDoubleComplexComponents[i][0]);
		// channelsDoubleComplexComponents[i][1] is already filled with 0

		// Merge Real and Imaginary into a complex component image
		merge(channelsDoubleComplexComponents[i],
			  channelsComplexImages[i]);

		// Perform Fourier transform on Complex component image
		dft(channelsComplexImages[i],
			channelsComplexSpectrums[i],
			DFT_COMPLEX_OUTPUT);

		// Split component Complex spectrum to real/imag channels
		split(channelsComplexSpectrums[i],
			  channelsComplexSpectrumComponents[i]);

		// Compute component spectrum magnitude
		magnitude(channelsComplexSpectrumComponents[i][0],
				  channelsComplexSpectrumComponents[i][1],
				  channelsSpectrumMagnitude[i]);

		// Log scale magnitude
		logScaleImg<double>(channelsSpectrumMagnitude[i],
							channelsSpectrumLogMagnitude[i],
							logScaleFactor);

		if (filtering)
		{
			// Clear lowpass mask with black
			channelsLowPassMask[i] = zero;
			// Clear highpass mask with white
			channelsHighPassMask[i] = one;

			// Compute lowpass and highpass masks
			// Mask center
			double gsize = (double) (optimalDFTSize-1) / 2.0;
			// filter amplitude
			double amplitude = 1.0;
			switch (filterType)
			{
				case BOX_FILTER:
					// Draw white filled circle on mask
					if (lowPassFilterSize[i] < filterMaxSize+1)
					{
						// Draws a white circle in channelsLowPassMask[i]
						// - point : (optimalDFTSize/2, optimalDFTSize/2)
						// - color : one (see above)
						// - filled circle
						// - with size from lowPassFilterSize[]
						// - use CV_AA as lineType
						// - no shift
						// TODO Compléter ...
						// circle(...);
                        circle(channelsLowPassMask[i],Point(optimalDFTSize/2, optimalDFTSize/2),lowPassFilterSize[i],one,-1,CV_AA);
					}

					// Draw black circle inside white filled circle
					if (highPassFilterSize[i] > 0)
					{
						// Draws a black circle in channelsHighPassMask[i]
						// - point : (optimalDFTSize/2, optimalDFTSize/2)
						// - color : zero (see above)
						// - filled circle
						// - with size from highPassFilterSize[]
						// - use CV_AA as lineType
						// - no shift
						// TODO Compléter ...
						// circle(...);
                        circle(channelsLowPassMask[i],Point(optimalDFTSize/2, optimalDFTSize/2),highPassFilterSize[i],zero,-1,CV_AA);
					}
					break;
				case GAUSS_FILTER:
					// TODO Compléter la méthode gaussian2D<T>(...) en fin de fichier

					// positive gaussian for low pass freq filter
					if (lowPassFilterSize[i] < filterMaxSize+1)
					{
						gaussian2D<double> (channelsLowPassMask[i],
											gsize,
											gsize,
											(double) lowPassFilterSize[i],
											amplitude);
					}

					// negative gaussian for high pass freq filter
					if (highPassFilterSize[i] > filterMinSize)
					{
						gaussian2D<double> (channelsHighPassMaskReverse[i],
											gsize,
											gsize,
											(double) highPassFilterSize[i],
											amplitude);

						reverseValues<double>(channelsHighPassMaskReverse[i],
											  channelsHighPassMask[i],
											  1.0);
					}
					break;
				case SINC_FILTER:

					// TODO Compléter la méthode sinc2D<T>(...) en fin de fichier

					// positive sinc
					if (lowPassFilterSize[i] < filterMaxSize+1)
					{
						sinc2D<double> (channelsLowPassMask[i],
										gsize,
										gsize,
										(double) lowPassFilterSize[i],
										amplitude);
					}

					// negative sinc
					if (highPassFilterSize[i] > filterMinSize)
					{
						sinc2D<double> (channelsHighPassMaskReverse[i],
										gsize,
										gsize,
										(double) highPassFilterSize[i],
										amplitude);

						reverseValues<double>(channelsHighPassMaskReverse[i],
											  channelsHighPassMask[i],
											  1.0);
					}
					break;
				default:
					break;
			} // end switch (filterType)

			// multiply lowpass and highpass
			multiply(channelsLowPassMask[i],
					 channelsHighPassMask[i],
					 channelsSpectrumMask[i]);

			// multiply spectrum LogMagnitude by Spectrum mask when filtering
			multiply(channelsSpectrumLogMagnitude[i],
					 channelsSpectrumMask[i],
					 channelsSpectrumLogMagnitude[i]);

		} // end if (filtering)
		else // No filtering: spectrum mask is completely white
		{
			channelsSpectrumMask[i] = one;
		}

		// Converts Spectrum mask for display
		convertScaleAbs(channelsSpectrumMask[i],
						channelsSpectrumMaskDisplay[i]);

		// Convert Log scale channels Spectrum to display channels
		convertScaleAbs(channelsSpectrumLogMagnitude[i],
						channelsSpectrumLogMagnitudeDisplay[i]);

		/*
		 * Inverse Fourier transform processing
		 * Principle : Multiply spectrum by a mask and then compute inverse
		 * transform which is equivalent convolve input image with the
		 * inverse transform of the mask
		 * - Creates a uchar mask same size as the DFT
		 * 	- Draw white filled circle on the mask to represent frequencies to filter
		 * - Creates a complex floating point mask with the original mask
		 * - Multiply complex spectrum with complex mask to procude the filtered spectrum
		 * - Inverse filtered spectrum
		 * 	- split inverse Fourier complex image to channels
		 * 	- convert real channel to CV_8UC1 to display filtered image
		 */

		// multiply spectrum real and imaginary channels with mask
		for (int j = 0; j < 2; j++)
		{
			multiply(channelsComplexSpectrumComponents[i][j],
					 channelsSpectrumMask[i],
					 channelsComplexSpectrumComponents[i][j]);
		}

		// remerge filtered component Spectrum Components to complex image
		merge(channelsComplexSpectrumComponents[i],
			  channelsComplexSpectrumsMasked[i]);

		// perform inverse Fourier Transform
		// with specific flags : DFT_REAL_OUTPUT + DFT_SCALE
		idft(channelsComplexSpectrumsMasked[i],
			 channelsComplexInverseImages[i],
			 DFT_REAL_OUTPUT + DFT_SCALE);

		// split inverse FFT to real/imag channels
		split(channelsComplexInverseImages[i],
			  channelsComplexInverseComponents[i]);

		// Reperform frequency shift on resulting real component
		frequencyShift<double>(channelsComplexInverseComponents[i][0],
							   channelsRealInverse[i]);

		// Convert real channel to display component
		convertScaleAbs(channelsRealInverse[i],
						channelsRealInverseDisplay[i]);
	} // end for (int i=0; i < nbChannels; i++)

	// Merge channels spectrum Log magnitude to color spectrum image
	merge(channelsSpectrumLogMagnitudeDisplay,
		  spectrumMagnitudeImage);

	// Merge channels spectrum masks to color mask image
	merge(channelsSpectrumMaskDisplay,
		  spectrumMaskImage);

	// Merge channels inverse real parts into inverse image
	merge(channelsRealInverseDisplay, inverseImage);

}

/*
 * Filter type read access
 * @return the current filter type
 */
CvDFT::FilterType CvDFT::getFilterType() const
{
	return filterType;
}

/*
 * Filter type setting
 * @param filterType ne new filter type
 */
void CvDFT::setFilterType(const FilterType filterType)
{
	if (filterType < NB_FILTERS)
	{
		this->filterType = filterType;
	}
	else
	{
		cerr << "unknown filter type " << filterType;
	}
}

/*
 * Filtering status
 * @return the filtering status. true if filtering is on, false
 * otherwise
 */
bool CvDFT::isFiltering() const
{
	return filtering;
}

/*
 * Setting filtering status
 * @param filtering ne new filtering status
 */
void CvDFT::setFiltering(bool filtering)
{
	this->filtering = filtering;
}

/*
 * Optimal dft size for current source image
 * @return the current optimal dft size
 */
int CvDFT::getOptimalDftSize() const
{
	return optimalDFTSize;
}

/*
 * Get current log scale factor
 * @return the current log scale factor
 */
double CvDFT::getLogScaleFactor() const
{
	return logScaleFactor;
}

/*
 * Setting the log scale factor
 * @param logScaleFactor the new log scale factor
 */
void CvDFT::setLogScaleFactor(double logScaleFactor)
{
	if (logScaleFactor > maxLogScaleFactor)
	{
		this->logScaleFactor = maxLogScaleFactor;
	}
	else if (logScaleFactor < minLogScaleFactor)
	{
		this->logScaleFactor = minLogScaleFactor;
	}
	else
	{
		this->logScaleFactor = logScaleFactor;
	}
}

/*
 * Returns min filter size for current image (generally 0)
 * @return the minimum filter size
 */
int CvDFT::getMinFilterSize() const
{
	return filterMinSize;
}

/*
 * Returns max filter size for current image
 * @return the maximum filter size
 */
int CvDFT::getMaxFilterSize() const
{
	return filterMaxSize;
}

/*
 * Low pass filter size read access
 * @param channel channel index
 * @return the current low pass filter size or -1 if channel is invalid
 */
int CvDFT::getLowPassFilterSize(const int channel) const
{
	if ((channel >= 0) && (channel < nbChannels))
	{
		return lowPassFilterSize[channel];
	}
	else
	{
		return -1;
	}
}

/*
 * High pass filter size read access
 * @param channel channel index
 * @return the current high pass filter size or -1 if channel is invalid
 */
int CvDFT::getHighPassFilterSize(const int channel) const
{
	if ((channel >= 0) && (channel < nbChannels))
	{
		return highPassFilterSize[channel];
	}
	else
	{
		return -1;
	}
}

/*
 * Low pass filter size setting
 * @param channel channel index. If channel index == number of channels
 * then set value for all channels
 * @param filterSize the new value of low pass filter size.
 * @note filterSize is limited to range
 * [highPassFilterSize...filterMaxSize]
 */
void CvDFT::setLowPassFilterSize(const int channel, const int filterSize)
{
	if ((channel >= 0) && (channel < nbChannels))
	{
		if (filterSize < highPassFilterSize[channel])
		{
			lowPassFilterSize[channel] = highPassFilterSize[channel];
		}
		else if (filterSize > filterMaxSize)
		{
			lowPassFilterSize[channel] = filterMaxSize;
		}
		else
		{
			lowPassFilterSize[channel] = filterSize;
		}
	}
}

/*
 * High pass filter size setting
 * @param channel channel index. If channel index == number of channels
 * then set value for all channels
 * @param filterSize the new value of high pass filter size.
 * @note filterSize is limited to range
 * [filterMinSize...lowPassFilterSize]
 */
void CvDFT::setHighPassFilterSize(const int channel, const int filterSize)
{
	if ((channel >= 0) && (channel < nbChannels))
	{
		if (filterSize > lowPassFilterSize[channel])
		{
			highPassFilterSize[channel] = lowPassFilterSize[channel];
		}
		else if (filterSize < filterMinSize)
		{
			highPassFilterSize[channel] = filterMinSize;
		}
		else
		{
			highPassFilterSize[channel] = filterSize;
		}
	}
}

// --------------------------------------------------------------------
// Utility methods
// --------------------------------------------------------------------
/*
 * Modify image to obtain reverse frequencies on the Fourier transform
 * (low frequencies at the center of the image and high frequencies on
 * the border), or modify image obtained from reverse Fourier transform
 * with reversed frequencies.
 * @param imgIn source image
 * @param imgOut destination image
 */
template <typename T>
void CvDFT::frequencyShift(Mat & imgIn, Mat & imgOut)
{
	int i, j;

	for (i = 0; i < imgIn.rows; i++)
	{
		for (j = 0; j < imgIn.cols; j++)
		{
			/*
			 * Performance issue : using pow(-1.0, i + j) makes frequencyShift
			 * use up to 42.6 % of CPU time of update loop whereas using
			 * ((i+j)%2 == 0 ? 1.0 : -1.0) reduces this to 5.8 % of CPU time.
			 */
			// imgOut.at<T> (i, j) = imgIn.at<T> (i, j) * (T)pow(-1.0, i + j);
			imgOut.at<T>(i, j) = imgIn.at<T>(i, j) * (T) ((i + j) % 2 == 0 ? 1.0 : -1.0);
		}
	}
}

/*
 * Computes a 2D gaussian on image
 * @param image output (and/or input) image
 * @param x0 x center
 * @param y0 y center
 * @param sigma gaussian width (at half height). If sigma <= 0 no
 * output is performed
 * @param amp amplitude
 */
template <typename T>
void CvDFT::gaussian2D(Mat & image, double x0, double y0, double sigma,
	double amp)
{
	if (sigma > 0.0)
	{
		// 2 * sigma^2
		// TODO compléter
        double sigmaFactor = 2*sigma*sigma;

		for (int i = 0; i < image.rows; i++)
		{
			// yterms in the gaussian (y - y0)^2 / (2 * sigma^2)
			// TODO compléter
			// double yterms = ...
            double yterms = (i - y0)*(i-y0) / sigmaFactor;

			for (int j = 0; j < image.cols; j++)
			{
				// xterms in the gaussian (x - x0)^2 / (2 * sigma^2)
				// TODO compléter
				// double xterms = ...
                double xterms = (j - x0)*(j - x0) / sigmaFactor;

				// Gaussian = (T) (amp * exp(-(xterms + yterms))
				// TODO remplacer
                image.at<T> (i, j) = (T)(amp*exp(-(xterms + yterms)));
				// TODO par
				// image.at<T> (i, j) = (T)(amp * exp(...));
			}
		}
	}
//	else
//	{
//		clog << "gaussian2D no output" << endl;
//	}
}

/*
 * Computes a 2D sinc on image
 * @param image output (and/or input) image
 * @param x0 x center
 * @param y0 y center
 * @param sigma width (at half height). If sigma <= 0 no
 * output is performed
 * @param amp amplitude
 */
template <typename T>
void CvDFT::sinc2D(Mat & image, double x0, double y0, double sigma,
	double amp)
{
	// h : mid height width
	double h = 0.6033 * M_PI / sigma;
	double espilon = 1e-9;
	double xterms, yterms, valTerm;

	if (sigma > 0.0)
	{
		for (int i = 0; i < image.rows; i++)
		{
			// yterms in sinc (y-y0)^2
			// TODO Compléter ...
            double yterms = (i-y0)*(i-y0);

			for (int j = 0; j < image.cols; j++)
			{
				// xterms in sinc (x-x0)^2
				// TODO Compléter ...
                double xterms = (j-x0)*(j-x0);

				// TODO Remplacer ...
                //double valTerm = 0;
				// TODO par value term in sin(value)/value : h * (xterms + yterms)^(1/2)
                double valTerm = h*sqrt((xterms + yterms));

				if (abs(valTerm) > espilon)
				{
					// TODO Remplacer ...
                    image.at<T> (i, j) = (T)(amp*sin(valTerm)/valTerm);
					// TODO Par amp * sin(...)/...
					// image.at<T> (i, j) = (T)(...);
				}
				else
				{
					// Sinc for 0 value is amp (avoid divide by 0)
					image.at<T> (i, j) = (T)amp;
				}
			}
		}
	}
//	else
//	{
//		clog << "sinc2D no output" << endl;
//	}
}


/*
 * Log scale T valued image
 * @param imgIn input image
 * @param imgOut output image
 * @param scaleFactor such as
 * \f$ imgOut = scaleFactor \times \log(1 + imgIn)\f$
 */
template <typename T>
void CvDFT::logScaleImg(const Mat & imgIn, Mat & imgOut,
	const T scaleFactor)
{
	MatConstIterator_<T> inIt = imgIn.begin<T>();
	MatConstIterator_<T> inItEnd = imgIn.end<T>();
	MatIterator_<T> outIt = imgOut.begin<T>();
	for (; inIt != inItEnd; ++inIt, ++outIt)
	{
		(*outIt) = scaleFactor * (T)log(1.0 + (*inIt));
	}
}

template <typename T>
void CvDFT::reverseValues(const Mat & imgIn, Mat & imgOut, const T value)
{
	// input image iterators
	MatConstIterator_<T> inIt = imgIn.begin<T>();
	MatConstIterator_<T> inItEnd = imgIn.end<T>();
	// output image iterators
	MatIterator_<T> outIt = imgOut.begin<T>();
	MatIterator_<T> outItEnd = imgOut.end<T>();
	for (; (inIt != inItEnd) && (outIt != outItEnd); ++inIt, ++outIt)
	{
		(*outIt) = value - (*inIt);
	}
}
