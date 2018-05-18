/*
 * CvHistograms.h
 *
 *  Created on: 22 févr. 2012
 *      Author: David Roussel
 */

#ifndef CVHISTOGRAMS_H_
#define CVHISTOGRAMS_H_

#include <vector>
using namespace std;

#include "CvProcessor.h"

/*
 * Forward declaration of Histograms output operator
 */
template <typename T, size_t channels> class CvHistograms;
template <typename T, size_t channels>
ostream & operator << (ostream & out, const CvHistograms<T, channels> & h);

/**
 * OpenCV Multiple histograms of an image.
 * @param T the data type in the image. Usually, unsigned char (default is uchar)
 * @param channels the number of channels in the image (default is 1)
 * If image has only one channel, no other histogram are computed.
 * But if image has several channels, each layer has an histogram and an
 * additional histogram corresponding to gray level equivalent image is
 * computed by linear combination of the previously computed histograms.
 * Eventually, linear combination coefficients are used :
 * 	- for RGB images linear combination coefficients are
 * 		- C_red = 0.30
 * 		- C_green = 0.59
 * 		- C_blue = 0.11
 *	- for YUV images linear combination coefficients are not necessary since
 *	the V component is already a grayscale component
 */
template <typename T = uchar, size_t channels = 1>
class CvHistograms : virtual public CvProcessor
{
	public:
		/**
		 * Color Histogram indices
		 */
		typedef enum
		{
			HIST_BLUE = 0,		//!< HIST_BLUE
			HIST_GREEN = 1,		//!< HIST_GREEN
			HIST_RED = 2,		//!< HIST_RED
			HIST_GRAY = 3		//!< HIST_GRAY
		} ColorHistIndex;

		/**
		 * Transfert function to apply on the image.
		 * Transfert function (also called LUT : standing for Look Up Table)
		 * are applied on the image with OpenCV function :
		 * @code
		 * void LUT(const Mat& src, const Mat& lut, Mat& dst)
		 * @endcode
		 * with
		 * 	- src - Source array of 8-bit elements
		 * 	- lut - Look-up table of 256 elements. In the case of multi-channel
		 * 	source array, the table should either have a single channel
		 * 	(in this case the same table is used for all channels) or the same
		 * 	number of channels as in the source array
		 * 	- dst - Destination array; will have the same size and the same number
		 * 	of channels as src , and the same depth as lut
		 */
		typedef enum
		{
			/**
			 * No transfert function should be applied on the image
			 */
			NONE=0,
			/**
			 * Image threshold on all channels should be applied on the image
			 * @see CvHistograms<T,channels>::computeGrayThresholdLUT
			 */
			THRESHOLD_GRAY,
			/**
			 * Optimal image dynamic should be applied on the image
			 * @see CvHistograms<T,channels>::computeGrayOptimalLUT
			 */
			DYNAMIC_GRAY,
			/**
			 * Levels equalization should be applied on the images
			 * @see CvHistograms<T,channels>::computeGrayEqualizeLUT
			 */
			EQUALIZE_GRAY,
			/**
			 * Image threshold with different threshold on each channel should be
			 * applied on the image
			 * @see CvHistograms<T,channels>::computeColorThresholdLUT
			 */
			THRESHOLD_COLOR,
			/**
			 * Optimal image dynamic should be applied on the image using
			 * different dynamic on each channel
			 * @see CvHistograms<T,channels>::computeColorOptimalLUT
			 */
			DYNAMIC_COLOR,
			/**
			 * Levels equalization should be applied on the images using different
			 * equalization on each channel
			 * @see CvHistograms<T,channels>::computeColorEqualizeLUT
			 */
			EQUALIZE_COLOR,
			/**
			 * Gamma transfert function
			 * @see CvHistograms<T,channels>::computeGammaLUT
			 */
			GAMMA,
			/**
			 * Negative transfert function
			 * @see CvHistograms<T,channels>::computeNegativeLUT
			 */
			NEGATIVE,
			/**
			 * Defines the number of available transfert functions.
			 * Used to toggle between LUTs to apply by using
			 * @code currentTransfertFunc % NBTRANS @endcode
			 */
			NBTRANS
		} TransfertType;

		/**
		 * Processing indices for getProcessTime method
		 * @see #getProcessTime
		 */
		typedef enum
		{
			ALL = 0,                    //!< ALL
			UPDATE_HISTOGRAM,           //!< UPDATE_HISTOGRAM
			COMPUTE_LUT,                //!< COMPUTE_LUT
			DRAW_LUT,                   //!< DRAW_LUT
			APPLY_LUT,                  //!< APPLY_LUT
			UPDATE_HISTOGRAM_AFTER_LUT, //!< UPDATE_HISTOGRAM_AFTER_LUT
			DRAW_HISTOGRAM,             //!< DRAW_HISTOGRAM
			NB_PROC_INDEX               //!< Number of processing time indices
		} ProcessTimeIndex;

	protected:
		// --------------------------------------------------------------------
		// Histograms attributes
		// --------------------------------------------------------------------
		/**
		 * 3 coefficients for additionnal grayscale histogram from RGB image :
		 * 	- \f$Coef_{red} = 0.30\f$
		 * 	- \f$Coef_{green} = 0.59\f$
		 * 	- \f$Coef_{blue} = 0.11\f$
		 * @note Be aware that OpenCV Color images are ususally encoded in BGR
		 * format instead of RGB.
		 */
		static const float BGR2Gray[];

		/**
		 * Number of bins in the histogram.
		 * All histogram populations ranges from 0 to bins-1
		 */
		static const size_t bins;

		/**
		 * Checks whether to compute additionnal gray level histogram
		 * from RGB components.
		 * @note has no impact if number of channels in the image is not 3
		 */
		bool computeGray;

		/**
		 * Number of computed histograms.
		 * @note could be bigger than the number of channels in the image
		 * if an additional gray level histogram is computed.
		 */
		size_t nbHistograms;

		/**
		 * The histogram values (an array containing "bins" elements).
		 * if image has 3 channels (BGR), a fourth histogram is computed
		 * according to the computeGray attribute in order to compute the
		 * equivalent gray level histogram.
		 * @see #BGR2Gray
		 */
		vector<float *> histograms;

		/**
		 * Maximum value found in all histograms
		 */
		float maxValue;

		/**
		 * The cumulative histogram computed by cumulatively sum "hist".
		 * (an array containing "bins" elements)
		 */
		vector<float *> cumulHistograms;

		/**
		 * Maximum value found in all cumulative histogram.
		 * @note cumulative maximum should be the number of pixels
		 * in the image but when histogram is time cumulative it is
		 * a multiple of number of pixels.
		 */
		float cMaxValue;

		/**
		 * checks whether histograms are time cumulative or not.
		 * if time cumulative histogram value are not cleared before
		 * updating the histogram values.
		 */
		bool timeCumulative;

		// --------------------------------------------------------------------
		// LUT attributes
		// --------------------------------------------------------------------
		/**
		 * Gray level transfert function
		 */
		Mat monoTransfertFunc;

		/**
		 * Colors transfert functions
		 */
		Mat colorTransferFunc;

		/**
		 * Current LUT to apply.
		 * Alternatively receives monoTransfertFunc or colorTransferFunc address
		 * depending on the transfert function to apply
		 */
		Mat * lut;

		/**
		 * Current LUT type
		 */
		TransfertType lutType;

		/**
		 * Previous LUT type. Used to avoid recomputing LUTs that does not
		 * depend on image histogram such as NONE, GAMMA and NEGATIVE
		 */
		TransfertType previousLutType;

		/**
		 * Current percentage for LUTs that requires such a parameter
		 */
		float lutParam;

		/**
		 * previous percentage for LUTs that requires such a parameter.
		 * Needed to know if LUT not depending on image histogram should be
		 * refreshed when param changes, such as Gamma
		 */
		float previousLutParam;

		/**
		 * Maximum percentage for LUTs that requires such a parameter
		 */
		static const float maxParam;

		/**
		 * Minimum percentage for LUTs that requires such a parameter
		 */
		static const float minParam;

		/**
		 * Indicates if LUT has been updated
		 */
		bool lutUpdated;

		// --------------------------------------------------------------------
		// Drawing attributes
		// --------------------------------------------------------------------
		/**
		 * checks whether to show cumulative histograms in the drawing or
		 * regular histograms
		 */
		bool showCumulative;

		/**
		 * components to show in the drawing
		 */
		vector<bool> showComponent;

		/**
		 * image width of the histogram drawing frame
		 */
		size_t histWidth;

		/**
		 * image height of the histogram drawing frame
		 */
		size_t histHeight;

		/**
		 * image width of the LUT drawing frame
		 */
		size_t lutWidth;

		/**
		 * image height of the LUT drawing frame
		 */
		size_t lutHeight;

		/**
		 * drawing color for the histograms
		 */
		vector<Scalar> displayColors;

		/**
		 * The color Matrices to draw each histogram
		 */
		vector<Mat> histComponents;

		/**
		 * The Frame to draw all histograms in
		 */
		Mat histDisplayFrame;

		/**
		 * The color Matrices to draw each LUT
		 */
		vector<Mat> lutComponents;

		/**
		 * The Frame to draw all LUTs in
		 */
		Mat lutDisplayFrame;

		/**
		 * The frame to draw transformed image when LUT is applied
		 */
		Mat outDisplayFrame;

		// --------------------------------------------------------------------
		// Time measurement attributes
		// --------------------------------------------------------------------

		/**
		 * Update histogram time when new frames appends
		 */
		clock_t updateHistogramTime1;

		/**
		 * Mean update histogram time when new frames appends
		 */
		ProcessTime meanUpdateHistogramTime1;

		/**
		 * LUT computing time
		 */
		clock_t computeLUTTime;

		/**
		 * Mean LUT computing time
		 */
		ProcessTime meanComputeLUTTime;

		/**
		 * LUT drawing time
		 */
		clock_t drawLUTTime;

		/**
		 * LUT drawing time
		 */
		ProcessTime meanDrawLUTTime;

		/**
		 * LUT apply time on image
		 */
		clock_t applyLUTTime;

		/**
		 * mean LUT apply time on image
		 */
		ProcessTime meanApplyLUTTime;

		/**
		 * Update histogram time after LUT is applied (when needed)
		 */
		clock_t updateHistogramTime2;

		/**
		 * mean update histogram time after LUT is applied (when needed)
		 */
		ProcessTime meanUpdateHistogramTime2;

		/**
		 * Histogram drawing time
		 */
		clock_t drawHistogramTime;

		/**
		 * Mean histogram drawing time
		 */
		ProcessTime meanDrawHistogramTime;

	public:

		/**
		 * Histogram constructor
		 * @param image the image to use for computing histograms
		 * @param drawColors the drawing colors of the histogram
		 * @param computeGray checks whether to compute 4th gray level
		 * histogram on BGR image or not
		 * @param drawHeight the drawing height of the histogram window
		 * @param drawWidth the drawing width of the histogram window
		 * @param timeCumulation checks whether to compute time cumulative
		 * histograms or not.
		 */
		CvHistograms(Mat * image,
					 const bool computeGray = true,
					 const size_t drawHeight = 256,
					 const size_t drawWidth = 512,
					 const bool timeCumulation = false);

		/**
		 * Histogram destructor.
		 * clears histogram values and release display frame
		 */
		virtual ~CvHistograms();

		/**
		 * Update histogram, LUT and resulting images
		 */
		virtual void update();

		/**
		 * Update histograms values.
		 */
		virtual void updateHistogram();

		/**
		 * Value reading access operator
		 * @param i the ith histogram to access. if i is invalid, 0 is returned
		 * @param j the jth bin value of the ith histogram to access. if j is
		 * invalid, 0 is returned.
		 * @param cumulative checks whether to return regular histogram value
		 * or cumulative histogram value
		 * @return the value in the jth bin of the ith histogram
		 * @par usage :
		 * @code
		 * 	float jthValue = myHist(i,j);
		 *  float jthCumulativeValue = myHist(i,j,true);
		 * @endcode
		 */
		float operator()(const size_t i,
						 const size_t j,
						 const bool cumulative = false) const;

		/**
		 * Value reading/writing access operator
		 * @param i the ith histogram to access. if i is invalid, 0 is returned
		 * @param j the jth bin value of the ith histogram to access. if j is
		 * invalid, 0 is returned.
		 * @param cumulative checks whether to return regular histogram value
		 * or cumulative histogram value
		 * @return the value in the jth bin of the ith histogram
		 * @par usage :
		 * @code
		 * 	float myHist(i,j) = jthValue;
		 *  float myHist(i,j,true) = jthCumulativeValue;
		 * @endcode
		 */
		float & operator()(const size_t i,
						   const size_t j,
						   const bool cumulative = false);

		/**
		 * Number of bins in all histograms
		 * @return the Number of bins in all histograms
		 */
		static size_t getBins();

		/**
		 * Get the number of histograms computed
		 * @return the current number of histograms computed by this class
		 */
		size_t getNbHistograms() const;

		/**
		 * Gets the additionnal gray histogram status
		 * @return true if additional gray level histogram is computed,
		 * false otherwise
		 */
		bool isComputeGray() const;

		/**
		 * Maximum histograms value;
		 * @return the maximum value in all histograms
		 */
		float getMaxValue() const;

		/**
		 * Maximum cumulative histograms value;
		 * @return the maximum value in all histograms
		 * @note regular cumulative maximum value is the number of pixels in
		 * the image, but when timecumulative is activated it can be bigger.
		 */
		float getCMaxValue() const;

		/**
		 * Time cumulative histogram status read access
		 * @return the time cumulative histogram status
		 */
		bool isTimeCumulative() const;

		/**
		 * Time cumulative histogram status read access
		 * @param value the value to set for time cumulative status
		 */
		virtual void setTimeCumulative(const bool value);

		/**
		 * Cumulative histogram status read access
		 * @return the cumulative histogram status
		 */
		bool isCumulative() const;

		/**
		 * Cumulative histogram status read access
		 * @param value the value to set for cumulative status
		 */
		virtual void setCumulative(const bool value);

		/**
		 * Ith histogram component shown status read access
		 * @param i the ith histogram component
		 * @return true if this component show status is true
		 */
		bool isShowComponent(const size_t i) const;

		/**
		 * Ith histogram component shown status write access
		 * @param i the ith histogram component
		 * @param value the value to set for this component show status
		 */
		virtual void setShowComponent(const size_t i,
									  const bool value);

		/**
		 * Indicates if LUT has been updated or if it has not changed
		 * @return true if LUT has been updated
		 */
		bool isLUTUpdated() const;

		/**
		 * Gets the current LUT type
		 * @return the current LUT type
		 */
		TransfertType getLutType() const;

		/**
		 * Sets the current LUT type
		 * @param lutType the new LUT type
		 */
		virtual void setLutType(const TransfertType lutType);

		/**
		 * Gets the current parameter value for LUTs using a percentage parameter
		 * @return the current LUT parameter
		 */
		float getLUTParam() const;

		/**
		 * Sets the current LUT % parameter
		 * @param lutParam the new LUT parameter
		 */
		virtual void setLUTParam(const float currentParam);

		/**
		 * Return processor processing time of step index [default implementation
		 * returning only processTime, should be reimplemented in subclasses]
		 * @param index index of the step which processing time is required,
		 * 0 indicates all steps, and values above 0 indicates step #. If
		 * required index is bigger than number of steps than all steps value
		 * should be returned.
		 * @return the processing time of step index.
		 * @note should be reimplemented in subclasses in order to define
		 * time/feature behaviour
		 */
		virtual double getProcessTime(const size_t index) const;

		/**
		 * Return processor mean processing time of step index [default
		 * implementation returning only processTime, should be reimplemented
		 * in subclasses]
		 * @param index index of the step which processing time is required,
		 * 0 indicates all steps, and values above 0 indicates step #. If
		 * required index is bigger than number of steps than all steps value
		 * should be returned.
		 * @return the mean processing time of step index.
		 * @note should be reimplemented in subclasses in order to define
		 * time/feature behaviour
		 * @param index
		 */
		virtual double getMeanProcessTime(const size_t index = 0) const;

		/**
		 * Return processor processing time std of step index [default
		 * implementation returning only processTime, should be reimplemented
		 * in subclasses]
		 * @param index index of the step which processing time is required,
		 * 0 indicates all steps, and values above 0 indicates step #. If
		 * required index is bigger than number of steps than all steps value
		 * should be returned.
		 * @return the mean processing time of step index.
		 * @note should be reimplemented in subclasses in order to define
		 * time/feature behaviour
		 * @param index
		 */
		virtual double getStdProcessTime(const size_t index = 0) const;

		/**
		 * Reset mean and std process time in order to re-start computing
		 * new mean and std process time values.
		 */
		virtual void resetMeanProcessTime();

		/**
		 * output operator for Histograms
		 * @param out the output stream
		 * @param h the histograms to print on the stream
		 * @return a reference to the output stream so it can be cumulated
		 */
		friend ostream & operator <<<> (ostream & out,
										const CvHistograms<T,channels> & h);
	protected:
		/**
		 * Setup attributes when source image is changed
		 * @param image source Image
		 * @param completeSetup
		 * @param computeGray checks if additionnal gray level histogram should
		 * be computed
		 * @param drawHeight histogram draw height
		 * @param drawWidth histogram draw width
		 * @param timeCumulation cheks time cumulation status
		 */
		virtual void setup(Mat * image,
						   const bool completeSetup = false);
		/**
		 * Cleanup attributes before changing source image or cleaning class
		 * before destruction
		 */
		virtual void cleanup();

		/**
		 * Draws selected histogram(s) in drawing frame and returns the drawing
		 * frame
		 * @return the updated drawing frame.
		 * @post depending on several attributes one or several histograms
		 * have been drawn in the drawing frame wich is returned
		 * 	- if #showCumulative is true then cumulative histograms are drawn
		 * 	otherwise regular histograms are drawn
		 * 	- each histogram is drawn only if its showComponent[i] is true.
		 */
		virtual void drawHistograms();

		/**
		 * Draws selected transfert function in drawing frame and returns the
		 * drawing frame
		 * @param lut the LUT to draw : the LUT may contains 1 or several
		 * channels
		 * @return the updated drawing frame
		 */
		virtual void drawTransfertFunc(const Mat * lut);

		/**
		 * Compute linear transfert function (LUT) : no change in image levels
		 * @return the LUT containing the corresponding transfert function,
		 * the returned matrix contains only one channel corresponding to
		 * the graylevel LUT which should be applied to all color channels of
		 * the image
		 * @post the result is stored in monoTransfertFunc
		 * @note It's useless to compute a color Linear LUT since all channels
		 * would contain the exact same values.
		 */
		Mat * computeLinearGrayLUT();

		/**
		 * Compute linear transfert function (LUT) : no change in image levels
		 * @return the LUT containing the corresponding transfert function,
		 * the returned matrix contains 3 channels corresponding to
		 * the color LUT which should be applied to all color channels of
		 * the image
		 * @post the result is stored in colorTransfertFunc
		 * @note It's useless to compute a color Linear LUT since all channels
		 * would contain the exact same values.
		 */
		Mat * computeLinearColorLUT();

		/**
		 * Compute the optimal dynamic LUT for preserving "percentDynamic"
		 * percent of the whole image ligthness range.
		 * @param percentDynamic the gray level percentage to spread on the
		 * whole (100%) gray level range in the image
		 * @return the LUT containing the corresponding transfert function,
		 * the returned matrix contains only one channel corresponding to
		 * the graylevel LUT which should be applied to all color channels of
		 * the image
		 * @post the result is stored in monoTransfertFunc
		 */
		Mat * computeGrayOptimalLUT(const unsigned int percentDynamic);

		/**
		 * Compute the optimal dynamic LUTs (one for each channel) for preserving
		 * "percentDynamic" percent of the whole image color ranges.
		 * @param percentDynamic the colors level percentage to spread on the
		 * whole (100%) colors level range in the image
		 * @return the LUT containing the corresponding transfert functions,
		 * the returned matrix contains as much channels as the image and
		 * corresponding to the color level LUT which should be applied to
		 * each color channels of the image
		 * @post the result is stored in colorTransfertFunc
		 */
		Mat * computeColorOptimalLUT(const unsigned int percentDynamic);

		/**
		 * Computes the transfert function corresponding to gray level
		 * equalization
		 * @return the matrix containing the gray level equalization LUT to
		 * apply on the image
		 * @post the result is stored in monoTransfertFunc
		 */
		Mat * computeGrayEqualizeLUT();

		/**
		 * Computes the transfert functions corresponding to each channel
		 * level equalization
		 * @return the matrix contaning each channel level equalization LUT to
		 * apply on the image
		 * @post the result is stored in colorTransferFunc
		 */
		Mat * computeColorEqualizeLUT();

		/**
		 * Compute the LUT corresponding to thresholded image with tPercent
		 * of the pixel population on each side of the threshold according
		 * to the cumulative gray level histogram
		 * @param tPercent percent of the population on each side of the
		 * threshold
		 * @return the LUT containing the corresponding transfert function,
		 * the returned matrix contains only one channel corresponding to
		 * the graylevel LUT which should be applied to all color channels of
		 * the image
		 * @post the result is stored in monoTransfertFunc
		 */
		Mat * computeGrayThresholdLUT(const float tPercent);

		/**
		 * Compute the LUT corresponding to thresholded image with tPercent
		 * of the pixel components population on each side of the
		 * thresholds according to the cumulative color histograms
		 * @param tPercent percent of the population on each side of the
		 * thresholds
		 * @return the matrix containing each channel level equalization LUT to
		 * apply on the image
		 * @post the result is stored in colorTransferFunc
		 */
		Mat * computeColorThresholdLUT(const float tPercent);

		/**
		 * Compute gamma LUT.
		 * \f$y(k) = x(k)^{\gamma}\f$
		 * @param tPercent
		 * @return the matrix containing the gamma LUT (mono)
		 */
		Mat * computeGammaLUT(const float tPercent);

		/**
		 * Compute the LUT corresponding to negative image
		 * @return the matrix containing the negative LUT (mono)
		 */
		Mat * computeNegativeLUT();

		/**
		 * Compute and returns the current transfert function to be applied
		 * on the image, eventually with the current LUT parameter
		 * @return the mono or color LUT matrix to apply on the image depending
		 * on the lutType
		 * @see TransfertType
		 */
		Mat * computeLUT();

		/**
		 * Apply current LUT (if != NULL) to the source image to produce the
		 * outFrame
		 * @return true if LUT has been applied, false if lut is NULL or
		 * lutType is NONE
		 */
		virtual bool drawTransformedImage();
};

#endif /* CVHISTOGRAMS_H_ */
