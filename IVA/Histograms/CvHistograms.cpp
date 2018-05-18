/*
 * CvHistograms.cpp
 *
 *  Created on: 22 févr. 2012
 *      Author: David Roussel
 */
#include <cmath>	// for powf function
#include <iostream> // for input / output streams
#include <limits>   // for numeric limits (max value of type T)
using namespace std;

#include <opencv2/imgproc/imgproc.hpp>

#include "CvHistograms.h"

/*
 * Number of bins in the histogram.
 * All histogram populations ranges from 0 to bins-1
 */
template <typename T, size_t channels>
const size_t CvHistograms<T, channels>::bins = (size_t) powf(2, sizeof(T) * 8);

/*
 * 3 coefficients for additionnal grayscale histogram from RGB image :
 * 	- \f$Coef_{red} = 0.30\f$
 * 	- \f$Coef_{green} = 0.59\f$
 * 	- \f$Coef_{blue} = 0.11\f$
 * @note Be aware that OpenCV Color images are ususally encoded in BGR
 * format instead of RGB.
 */
template <typename T, size_t channels>
const float CvHistograms<T, channels>::BGR2Gray[] = {0.11, 0.59, 0.30};

/*
 * Maximum percentage for LUTs that requires such a parameter
 */
template <typename T, size_t channels>
const float CvHistograms<T, channels>::maxParam = 100.0;

/*
 * Minimum percentage for LUTs that requires such a parameter
 */
template <typename T, size_t channels>
const float CvHistograms<T, channels>::minParam = 0.0;

/*
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
template <typename T, size_t channels>
CvHistograms<T, channels>::CvHistograms(Mat * image,
										const bool computeGray,
										const size_t drawHeight,
										const size_t drawWidth,
										const bool timeCumulation)
	: CvProcessor(image),
	  computeGray(computeGray),
	  timeCumulative(timeCumulation),
	  monoTransfertFunc(1, bins, CV_8UC1),
	  colorTransferFunc(1, bins, CV_8UC(channels)),
	  lut(NULL),
	  lutType(NONE),
	  previousLutType(NBTRANS),
	  lutParam(80.0),
	  previousLutParam(80.0),
	  showCumulative(false),
	  histWidth(drawWidth),
	  histHeight(drawHeight),
	  lutWidth(bins),
	  lutHeight(bins),
	  histDisplayFrame(drawHeight, drawWidth, CV_8UC(channels)),
	  lutDisplayFrame(bins, bins, CV_8UC(channels)),
	  outDisplayFrame(image->size(), image->type())

{
	// Partial setup since lots has been done in initialisation list above
	setup(image, false);

	addImage("histogram", &histDisplayFrame);
	addImage("lut", &lutDisplayFrame);
	addImage("out", &outDisplayFrame);
}

/*
 * Setup attributes when source image is changed
 * @param image source Image
 * @param computeGray checks if additionnal gray level histogram should
 * be computed
 * @param drawHeight histogram draw height
 * @param drawWidth histogram draw width
 * @param timeCumulation cheks time cumulation status
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::setup(Mat * image, const bool completeSetup)
{
	CvProcessor::setup(image, completeSetup);

	// Complete setup starting point (==> previous cleanup)
	if (completeSetup)
	{
		monoTransfertFunc = Mat(1, bins, CV_8UC1);
		colorTransferFunc = Mat(1, bins, CV_8UC(channels));
		lut = NULL;
		lutType = NONE;
		previousLutType = NBTRANS;
		lutParam = 80.0;
		showCumulative = false;
		lutWidth = bins;
		lutHeight = bins;
		histDisplayFrame = Mat(histHeight, histWidth, CV_8UC(channels));
		lutDisplayFrame = Mat(bins, bins, CV_8UC(channels));
		outDisplayFrame = Mat(image->size(), image->type());
	}
	else //
	{
		// Creates colors to draw histogram components
		displayColors.push_back(Scalar(0xFF, 0x00, 0x00)); // Blue
		displayColors.push_back(Scalar(0x00, 0xFF, 0x00)); // Green
		displayColors.push_back(Scalar(0x00, 0x00, 0xFF)); // Red
		displayColors.push_back(Scalar(0xCC, 0xCC, 0xCC)); // Gray
	}

	// Partial setup starting point (==> no previous cleanup but contructor)

	if (sourceImage->data != NULL)
	{
		maxValue = 0.0;
		cMaxValue = 0.0;

		nbHistograms = channels;
		if (this->computeGray && (nbHistograms == 3))
		{
			nbHistograms++;
		}

		for (size_t i = 0; i < nbHistograms; i++)
		{
			// creates ith histogram
			histograms.push_back(new float[bins]);
			// creates ith cumulative histogram
			cumulHistograms.push_back(new float[bins]);
			// defines if ith component should be drawn
			showComponent.push_back(true);
			// creates ith drawing color histogram frame
			histComponents.push_back(Mat(histHeight, histWidth, CV_8UC3));
			lutComponents.push_back(Mat(lutHeight, lutWidth, CV_8UC3));

			/*
			 * Initialize Histogram and cumiulative histograms values to 0.0
			 * Avoid calling [] on vectors multiple times by using local
			 * variables to store vector content (in this case float arrays)
			 */
			float * h = histograms[i];
			float * ch = cumulHistograms[i];
			// initialize histograms values
			for (size_t j = 0; j < bins; j++)
			{
				h[j] = 0.0;
				ch[j] = 0.0;
			}
		}

		if (this->computeGray && (nbHistograms == 4))
		{
			showComponent[HIST_GRAY] = false; // don't show gray hist. yet
		}
	}
	else // sourceImage->data is NULL
	{
		cerr << "CvHistograms::Setup : NULL source image" << endl;
		exit(EXIT_FAILURE);
	}
}

/*
 * Histogram destructor.
 * clears histogram values and release display frame
 */
template <typename T, size_t channels>
CvHistograms<T, channels>::~CvHistograms()
{
	cleanup();
}

/*
 * Cleanup attributes before changing source image or cleaning class
 * before destruction
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::cleanup()
{
	for (size_t i = 0; i < histograms.size(); i++)
	{
		delete (histograms[i]);
		delete (cumulHistograms[i]);
		histComponents[i].release();
		lutComponents[i].release();
	}

	outDisplayFrame.release();
	lutDisplayFrame.release();
	lutComponents.clear();
	histDisplayFrame.release();
	histComponents.clear();
	displayColors.clear();
	showComponent.clear();
	colorTransferFunc.release();
	monoTransfertFunc.release();
	cumulHistograms.clear();
	histograms.clear();

	// Super cleanup
	CvProcessor::cleanup();
}

/*
 * Number of bins in all histograms
 * @return the Number of bins in all histograms
 */
template <typename T, size_t channels>
size_t CvHistograms<T, channels>::getBins()
{
	return bins;
}

/*
 * Get the number of histograms computed
 * @return the current number of histograms computed by this class
 */
template <typename T, size_t channels>
size_t CvHistograms<T, channels>::getNbHistograms() const
{
	return nbHistograms;
}

/*
 * Gets the additionnal gray histogram status
 * @return true if additional gray level histogram is computed,
 * false otherwise
 */
template <typename T, size_t channels>
bool CvHistograms<T, channels>::isComputeGray() const
{
	return computeGray;
}

/*
 * Maximum histograms value;
 * @return the maximum value in all histograms
 */
template <typename T, size_t channels>
float CvHistograms<T, channels>::getMaxValue() const
{
	return maxValue;
}

/*
 * Maximum cumulative histograms value;
 * @return the maximum value in all histograms
 * @note regular cumulative maximum value is the number of pixels in
 * the image, but when timecumulative is activated it can be bigger.
 */
template <typename T, size_t channels>
float CvHistograms<T, channels>::getCMaxValue() const
{
	return cMaxValue;
}

/*
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
template <typename T, size_t channels>
float CvHistograms<T, channels>::operator()(const size_t i,
											const size_t j,
											const bool cumulative) const
{
	if (i < nbHistograms)
	{
		if (j < bins)
		{
			if (!cumulative)
			{
				return (const float) histograms[i][j];
			}
			else
			{
				return (const float) cumulHistograms[i][j];
			}
		}
		else
		{
			cerr << "CvHistograms::operator() const invalid second index "
				 << "j = " << j << endl;
			return operator()(i, bins - 1);
		}
	}
	else
	{
		cerr << "CvHistograms::operator() const invalid first index i = " << i
			 << endl;
		return operator()(nbHistograms - 1, j);
	}
}

/*
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
template <typename T, size_t channels>
float & CvHistograms<T, channels>::operator()(const size_t i,
											  const size_t j,
											  const bool cumulative)
{
	if (i < nbHistograms)
	{
		if (j < bins)
		{
			if (!cumulative)
			{
				return histograms[i][j];
			}
			else
			{
				return cumulHistograms[i][j];
			}
		}
		else
		{
			cerr << "CvHistograms::operator() invalid second index j = " << j
				 << endl;
			return operator()(i, bins - 1);
		}
	}
	else
	{
		cerr << "CvHistograms::operator() invalid first index i = " << i
			 << endl;
		return operator()(nbHistograms - 1, j);
	}
}

/*
 * Time cumulative histogram status read access
 * @return the time cumulative histogram status
 */
template <typename T, size_t channels>
bool CvHistograms<T, channels>::isTimeCumulative() const
{
	return timeCumulative;
}

/*
 * Time cumulative histogram status read access
 * @param value the value to set for time cumulative status
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::setTimeCumulative(const bool value)
{
	timeCumulative = value;
}

/*
 * Cumulative histogram status read access
 * @return the cumulative histogram status
 */
template <typename T, size_t channels>
bool CvHistograms<T, channels>::isCumulative() const
{
	return showCumulative;
}

/*
 * Cumulative histogram status read access
 * @param value the value to set for cumulative status
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::setCumulative(const bool value)
{
	showCumulative = value;
}

/*
 * Ith histogram component shown status read access
 * @param i the ith histogram component
 * @return true if this component show status is true
 */
template <typename T, size_t channels>
bool CvHistograms<T, channels>::isShowComponent(const size_t i) const
{
	if (i < nbHistograms)
	{
		return showComponent[i];
	}
	else
	{
		return false;
	}
}

/*
 * Ith histogram component shown status write access
 * @param i the ith histogram component
 * @param value the value to set for this component show status
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::setShowComponent(const size_t i,
												 const bool value)
{
	//	clog << "Set Showcomponent n° " << i << (value ? "true" : "false") <<
	//endl;
	if (i < nbHistograms)
	{
		showComponent[i] = value;
	}
}

/**
 * Update histogram, LUT and resulting images
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::update()
{
	clock_t start;
	processTime = 0;

	// Compute histogram
	start = clock();

	updateHistogram();

	updateHistogramTime1 = clock() - start;
	processTime += updateHistogramTime1;
	meanUpdateHistogramTime1 += updateHistogramTime1;

	// Compute requested LUT
	start = clock();

	lut = computeLUT();

	computeLUTTime = clock() - start;
	processTime += computeLUTTime;
	meanComputeLUTTime += computeLUTTime;

	if (isLUTUpdated())
	{
		// draw TransfertFunction to lutDisplayFrame
		start = clock();

		drawTransfertFunc(lut);

		drawLUTTime = clock() - start;
		processTime += drawLUTTime;
		meanDrawLUTTime += drawLUTTime;
	}

	// Try to apply LUT
	start = clock();

	bool lutApplied = drawTransformedImage();

	applyLUTTime = clock() - start;
	processTime += applyLUTTime;
	meanApplyLUTTime += applyLUTTime;

	if (lutApplied)
	{
		// if LUT has been applied histogram should be updated
		start = clock();

		updateHistogram();

		updateHistogramTime2 = clock() - start;
		processTime += updateHistogramTime2;
		meanUpdateHistogramTime2 += updateHistogramTime2;
	}
	else
	{
		updateHistogramTime2 = 0;
	}

	// Finally draw Histogram
	start = clock();

	drawHistograms();

	drawHistogramTime = clock() - start;
	processTime += drawHistogramTime;
	meanDrawHistogramTime += drawHistogramTime;
	meanProcessTime += processTime;
}

/*
 * Update histograms values.
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::updateHistogram()
{
	maxValue = 0.0;
	cMaxValue = 0.0;

	// reset histograms values if necessary
	if (!timeCumulative)
	{
		// reset histograms values (including evt gray level histogram)
		for (size_t i = 0; i < nbHistograms; i++)
		{
			float * h = histograms[i];
			for (size_t j = 0; j < bins; j++)
			{
				h[j] = 0.0;
			}
		}
	}

	// creating iterators over image
	MatConstIterator_<Vec<T, channels> > iterator =
		sourceImage->begin<Vec<T, channels> >();
	MatConstIterator_<Vec<T, channels> > end =
		sourceImage->end<Vec<T, channels> >();

	// updateHistogram histograms values
	for (; iterator != end; ++iterator)
	{
		Vec<T, channels> pixel = *iterator;

		for (size_t i = 0; i < channels; i++)
		{
			// updateHistogram corresponding histogram bin
			float histValue = ++histograms[i][(size_t) pixel[i]];

			// updateHistogram max value if needed
			if (histValue > maxValue)
			{
				maxValue = histValue;
			}
		}
	}

	// eventually updates gray level histogram
	if (computeGray && (channels == 3))
	{
		for (size_t l = 0; l < channels; l++)
		{
			for (size_t i = 0; i < bins; i++)
			{
				histograms[HIST_GRAY][i] += BGR2Gray[l] * histograms[l][i];
			}
		}
	}

	// update cumulative histograms
	for (size_t h = 0; h < nbHistograms; h++)
	{
		float * regularHistogram = histograms[h];
		float * cumulativeHistogram = cumulHistograms[h];

		size_t b;
		cumulativeHistogram[0] = regularHistogram[0];
		for (b = 1; b < bins; b++)
		{
			cumulativeHistogram[b] =
				cumulativeHistogram[b - 1] + regularHistogram[b];
		}

		// b == bins now, so checks if last is greater than max value
		if (cumulativeHistogram[b - 1] > cMaxValue)
		{
			cMaxValue = cumulativeHistogram[b - 1];
		}
	}
}

/*
 * Draws selected histogram(s) in drawing frame and returns the drawing
 * frame
 * @return the updated drawing frame.
 * @post depending on several attributes one or several histograms
 * have bee drawn in the drawing frame wich is returned
 * 	- if #showCumulative is true then cumulative histograms are drawn
 * 	otherwise regular histograms are drawn
 * 	- each histogram is drawn only if its showComponent[i] is true.
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::drawHistograms()
{
	float curveStep = (float) histWidth / (float) bins;
	vector<float *> * valuesPtr;
	float max;
	if (showCumulative)
	{
		valuesPtr = &cumulHistograms;
		max = cMaxValue;
	}
	else
	{
		valuesPtr = &histograms;
		max = maxValue;
	}

	// Fill the drawing frame with black
	rectangle(histDisplayFrame,
			  Point(0, 0),
			  Point(histWidth - 1, histHeight - 1),
			  Scalar(0x00, 0x00, 0x00, 0x00),
			  CV_FILLED);

	// Draw the bins (reversed)
	for (size_t h = 0; h < nbHistograms; h++)
	{
		// fills this color histogram frame with black
		rectangle(histComponents[h],
				  Point(0, 0),
				  Point(histWidth - 1, histHeight - 1),
				  Scalar(0x00, 0x00, 0x00, 0x00),
				  CV_FILLED);

		// if this color histogram should be drawn
		if (showComponent[h])
		{
			for (size_t i = 0; i < bins; i++)
			{
				// draws each bin (reversed) in this color hist. frame
				rectangle(
					histComponents[h], // the image to draw in
					Point(i * curveStep,
						  histHeight - 1),	 // first corner of this bin
					Point((i + 1) * curveStep, // second corner of this bin
						  histHeight - 1 -
							  cvRound(((*valuesPtr)[h][i] / max) * histHeight)),
					displayColors[h], // current color
					CV_FILLED,		  // filled rectangle
					CV_AA);			  // antialiased line
			}
			// adds this color histogram frame to the drawing frame
			add(histDisplayFrame, histComponents[h], histDisplayFrame);
		}
	}
}

/*
 * Draws selected transfert function in drawing frame and returns the
 * drawing frame
 * @param lut the LUT to draw : the LUT may contains 1 or several
 * channels
 * @return the updated drawing frame
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::drawTransfertFunc(const Mat * lut)
{
	float curveStep = (float) lutWidth / (float) bins;

	const Mat * currentLUT;

	if (lut != NULL)
	{
		currentLUT = lut;
	}
	else // identity LUT should be computed
	{
		currentLUT = computeLinearGrayLUT();
	}

	size_t lutChannels = (size_t) currentLUT->channels();

	// Fill the drawing frame with black
	rectangle(lutDisplayFrame,
			  Point(0, 0),
			  Point(lutWidth - 1, lutHeight - 1),
			  Scalar(0x00, 0x00, 0x00, 0x00),
			  CV_FILLED);

	// Draw the bins (reversed)
	if (lutChannels == 1)
	{
		// draws directly in histDisplayFrame with white color
		for (size_t i = 0; i < bins; i++)
		{
			rectangle(
				lutDisplayFrame,					 // the image to draw in
				Point(i * curveStep, lutHeight - 1), // first corner of this bin
				Point((i + 1) * curveStep, // second corner of this bin
					  lutHeight - 1 -
						  cvRound(((float) currentLUT->at<T>(0, i) / bins) *
								  lutHeight)),
				displayColors[3], // current color
				CV_FILLED,		  // filled rectangle
				CV_AA);			  // antialiased line
		}
	}
	else // lutChannels == 3 or others
	{
		// draws in each colorLUTFrams and adds it to histDisplayFrame
		for (size_t c = 0; c < lutChannels; c++)
		{
			if (showComponent[c])
			{
				// Fill the color drawing frame with black
				rectangle(lutComponents[c],
						  Point(0, 0),
						  Point(lutWidth - 1, lutHeight - 1),
						  Scalar(0x00, 0x00, 0x00, 0x00),
						  CV_FILLED);

				for (size_t i = 0; i < bins; i++)
				{
					rectangle(lutComponents[c], // the image to draw in
						Point(i * curveStep,
							  lutHeight - 1), // first corner of this bin
						Point((i + 1) * curveStep, // second corner of this bin
							  lutHeight - 1 -
							  cvRound(((float)
									   currentLUT->at<Vec<T, channels> >(0, i)[c] / bins) *
									lutHeight)),
						displayColors[c], // current color
						CV_FILLED,		  // filled rectangle
						CV_AA);			  // antialiased line
				}
				add(lutDisplayFrame, lutComponents[c], lutDisplayFrame);
			}
		}
	}
}

/*
 * Indicates if LUT has been updated or if it has not changed
 * @return true if LUT has been updated
 */
template <typename T, size_t channels>
bool CvHistograms<T, channels>::isLUTUpdated() const
{
	return lutUpdated;
}

/*
 * Gets the current LUT type
 * @return the current LUT type
 */
template <typename T, size_t channels>
typename CvHistograms<T, channels>::TransfertType
CvHistograms<T, channels>::getLutType() const
{
	return lutType;
}

/*
 * Sets the current LUT type
 * @param lutType the new LUT type
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::setLutType(const TransfertType lutType)
{
	previousLutType = this->lutType;

	computeLUTTime = 0;
	drawLUTTime = 0;
	applyLUTTime = 0;
	updateHistogramTime2 = 0;

	if (lutType < NBTRANS)
	{
		this->lutType = lutType;
	}
	else
	{
		this->lutType = NONE;
	}
}

/*
 * Gets the current parameter value for LUTs using a percentage parameter
 * @return the current LUT parameter
 */
template <typename T, size_t channels>
float CvHistograms<T, channels>::getLUTParam() const
{
	return lutParam;
}

/*
 * Sets the current LUT % parameter
 * @param lutParam the new LUT parameter
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::setLUTParam(const float currentParam)
{
	previousLutParam = lutParam;

	if (currentParam > maxParam)
	{
		this->lutParam = maxParam;
	}
	else if (currentParam < minParam)
	{
		this->lutParam = minParam;
	}
	else
	{
		this->lutParam = currentParam;
	}
}

/*
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
template <typename T, size_t channels>
double CvHistograms<T, channels>::getProcessTime(const size_t index) const
{
	switch (index)
	{
		case (CvHistograms<T, channels>::UPDATE_HISTOGRAM):
			return (double) updateHistogramTime1;
		case (CvHistograms<T, channels>::COMPUTE_LUT):
			return (double) computeLUTTime;
		case (CvHistograms<T, channels>::DRAW_LUT):
			return (double) drawLUTTime;
		case (CvHistograms<T, channels>::APPLY_LUT):
			return (double) applyLUTTime;
		case (CvHistograms<T, channels>::UPDATE_HISTOGRAM_AFTER_LUT):
			return (double) updateHistogramTime2;
		case (CvHistograms<T, channels>::DRAW_HISTOGRAM):
			return (double) drawHistogramTime;
		default:
			return (double) processTime;
	}
}

/*
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
template <typename T, size_t channels>
double CvHistograms<T, channels>::getMeanProcessTime(const size_t index) const
{
	switch (index)
	{
		case (CvHistograms<T, channels>::UPDATE_HISTOGRAM):
			return (double) meanUpdateHistogramTime1.mean();
		case (CvHistograms<T, channels>::COMPUTE_LUT):
			return (double) meanComputeLUTTime.mean();
		case (CvHistograms<T, channels>::DRAW_LUT):
			return (double) meanDrawLUTTime.mean();
		case (CvHistograms<T, channels>::APPLY_LUT):
			return (double) meanApplyLUTTime.mean();
		case (CvHistograms<T, channels>::UPDATE_HISTOGRAM_AFTER_LUT):
			return (double) meanUpdateHistogramTime2.mean();
		case (CvHistograms<T, channels>::DRAW_HISTOGRAM):
			return (double) meanDrawHistogramTime.mean();
		default:
			return (double) meanProcessTime.mean();
	}
}

/*
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
template <typename T, size_t channels>
double CvHistograms<T, channels>::getStdProcessTime(const size_t index) const
{
	switch (index)
	{
		case (CvHistograms<T, channels>::UPDATE_HISTOGRAM):
			return (double) meanUpdateHistogramTime1.std();
		case (CvHistograms<T, channels>::COMPUTE_LUT):
			return (double) meanComputeLUTTime.std();
		case (CvHistograms<T, channels>::DRAW_LUT):
			return (double) meanDrawLUTTime.std();
		case (CvHistograms<T, channels>::APPLY_LUT):
			return (double) meanApplyLUTTime.std();
		case (CvHistograms<T, channels>::UPDATE_HISTOGRAM_AFTER_LUT):
			return (double) meanUpdateHistogramTime2.std();
		case (CvHistograms<T, channels>::DRAW_HISTOGRAM):
			return (double) meanDrawHistogramTime.std();
		default:
			return (double) meanProcessTime.std();
	}
}

/*
 * Reset mean and std process time in order to re-start computing
 * new mean and std process time values.
 */
template <typename T, size_t channels>
void CvHistograms<T, channels>::resetMeanProcessTime()
{
	CvProcessor::resetMeanProcessTime();
	meanUpdateHistogramTime1.reset();
	meanComputeLUTTime.reset();
	meanDrawLUTTime.reset();
	meanApplyLUTTime.reset();
	meanUpdateHistogramTime2.reset();
	meanDrawHistogramTime.reset();
}

/*
 * Compute linear transfert function (LUT) : no change in image levels
 * @return the LUT containing the corresponding transfert function,
 * the returned matrix contains only one channel corresponding to
 * the graylevel LUT which should be applied to all color channels of
 * the image
 * @post the result is stored in monoTransfertFunc
 * @note It's useless to compute a color Linear LUT since all channels
 * would contain the exact same values.
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeLinearGrayLUT()
{
	for (size_t i = 0; i < bins; i++)
	{
		monoTransfertFunc.at<T>(0, i) = i;
	}

	return &monoTransfertFunc;
}

/*
 * Compute linear transfert function (LUT) : no change in image levels
 * @return the LUT containing the corresponding transfert function,
 * the returned matrix contains 3 channels corresponding to
 * the color LUT which should be applied to all color channels of
 * the image
 * @post the result is stored in colorTransfertFunc
 * @note It's useless to compute a color Linear LUT since all channels
 * would contain the exact same values.
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeLinearColorLUT()
{
	for (size_t c = 0; c < channels; c++)
	{
		for (size_t i = 0; i < bins; i++)
		{
			colorTransferFunc.at<Vec<T, channels> >(0, i)[c] = i;
		}
	}

	return &colorTransferFunc;
}

/*
 * Compute the optimal dynamic LUT for preserving "percentDynamic"
 * percent of the whole image ligthness range.
 * @param percentDynamic the gray level percentage to spread on the
 * whole (100%) gray level range in the image
 * @return the LUT containing the corresponding transfert function,
 * the returned matrix contains only one channel corresponding to
 * the graylevel LUT which should be applied to all color channels of
 * the image
 * @post the result is stored in monoTransfertFunc
 * 			^
 * maxVal	|           ________
 * 			|          /
 * 			|         /
 * 			|        /         dy/dx = (maxVal-minVal) / (maxThresIndex - minthresIndex - 1)
 * 			|       /
 * 			|      /
 * minVal	|_____/     maxThresIndex
 * 			+----+------+------------->
 * 	 minThresIndex
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeGrayOptimalLUT(const unsigned int percentDynamic)
{
	if (computeGray && nbHistograms == 4)
	{
		float threshold = (100 - percentDynamic) / 200.0;
		float imageSize = sourceImage->rows * sourceImage->cols;
		float minThres = imageSize * threshold;
		float maxThres = imageSize - minThres;

		size_t minThresIndex = 0;
		size_t maxThresIndex = bins;

		T minVal = 0;
		T maxVal = numeric_limits<T>::max(); // 255 for uchar
        size_t i;
		// finds minThresIndex in cumulHistograms[HIST_GRAY][i=0..bins]
		// TODO à compléter ...
        for(i=0; i<bins; i++){
            if(cumulHistograms[HIST_GRAY][i]>minThres){
                minThresIndex = i;
                break;
            }
        }

		// finds maxThresIndex in cumulHistograms[HIST_GRAY][i=0..bins]
		// TODO à compléter ...
        for(i=0; i<bins; i++){
            if(cumulHistograms[HIST_GRAY][i]>maxThres){
                maxThresIndex = i;
                break;
            }
        }

		// fill monoTransfertFunc before minThresIndex with minVal
		// TODO à compléter ...
        for(size_t j=0; j<minThresIndex; j++){
            monoTransfertFunc.at<T>(0,j) = minVal;
        }

		// fill monoTransfertFunc between minThresIndex and maxThesIndex with Dy/Dx Values
		float slope = (float)(maxVal - minVal) /
					  (float)(maxThresIndex-1-minThresIndex);

		// TODO à compléter ...
        for(size_t s=minThresIndex; s<maxThresIndex; s++){
            monoTransfertFunc.at<T>(0,s) = (s-minThresIndex)*slope;
        }

		// fill monoTransfertFunc after maxThresIndex with maxVal
		// TODO à compléter ...
        for(size_t k=maxThresIndex; k<bins; k++){
            monoTransfertFunc.at<T>(0,k) = maxVal;
        }

	}
	else
	{
		cerr << "CvHistograms<T,channels>::computeGrayOptimalLUT : "
			 << "There is no gray histogram !" << endl;
	}

	return &monoTransfertFunc;
}

/*
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
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeColorOptimalLUT(const unsigned int percentDynamic)
{
	float threshold = (1 - (percentDynamic / 100.0)) / 2.0;
	float imageSize = sourceImage->rows * sourceImage->cols;
	float minThres = imageSize * threshold;
	float maxThres = imageSize - minThres;

	size_t minThresIndex[channels];
	size_t maxThresIndex[channels];
	T minVal = 0;
	T maxVal = numeric_limits<T>::max(); // 255 for uchar;
	float slope[channels];

	for (size_t c = 0; c < channels; c++)
	{
		minThresIndex[c] = 0;
		maxThresIndex[c] = bins;

        size_t i;
		// finds minThresIndex in cumulHistograms[c][...] for this channel
		// TODO à compléter ...
        for(i=0; i<bins; i++){
            if(cumulHistograms[c][i]>minThres){
                minThresIndex[c] = i;
                break;
            }
        }

		// finds maxThresIndex in cumulHistograms[c][...] for this channel
		// TODO à compléter ...
        for(i=0; i<bins; i++){
            if(cumulHistograms[c][i]>maxThres){
                maxThresIndex[c] = i;
                break;
            }
        }

		// fill colorTransferFunc before minThresIndex with minVal
		// TODO à compléter ...

            for (size_t i = 0; i < minThresIndex[c]; i++)
            {
                colorTransferFunc.at<Vec<T, channels> >(0, i)[c] = minVal;
            }



		// ramp slope for this channel = Dy/Dx
		slope[c] = (float)(maxVal - minVal) /
				   (float)(maxThresIndex[c]-1-minThresIndex[c]);

		// fill colorTransferFunc between minThresIndex and maxThesIndex with regular ramp
		// TODO à compléter ...

            for (size_t i = minThresIndex[c]; i < maxThresIndex[c]; i++)
            {
                colorTransferFunc.at<Vec<T, channels> >(0, i)[c] = (i-minThresIndex[c])*slope[c];
            }


		// fill colorTransferFunc after maxThresIndex with maxVal
		// TODO à compléter ...

            for (size_t i = maxThresIndex[c]; i < bins; i++)
            {
                colorTransferFunc.at<Vec<T, channels> >(0, i)[c] = maxVal;
            }

	}

	return &colorTransferFunc;
}

/*
 * Computes the transfert function corresponding to gray level
 * equalization
 * @return the matrix containing the gray level equalization LUT to
 * apply on the image
 * @post the result is stored in monoTransfertFunc
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeGrayEqualizeLUT()
{
	T maxVal = numeric_limits<T>::max();
	if (computeGray && nbHistograms == 4)
	{
		/*
		 * Equalisation consists in applying the corresponding cumulative
		 * histogram (cumulHistograms[HIST_GRAY][i=0..bins] normalized to
		 * maxVal)
		 * as a mono transfert function
		 */
		// TODO à compléter ...
        for(i=0; i<bins; i++){
            normalize(cumulHistograms[HIST_GRAY][i],cumulHistograms[HIST_GREY][i], 0, maxVal, CV_BGR2GREY);
        }

	}
	else
	{
		cerr << "CvHistograms<T,channels>::computeGrayEqualizeLUT : "
			 << "There is no gray level histogram" << endl;
	}

	return &monoTransfertFunc;
}

/*
 * Computes the transfert functions corresponding to each channel
 * level equalization
 * @return the matrix contaning each channel level equalization LUT to
 * apply on the image
 * @post the result is stored in colorTransferFunc
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeColorEqualizeLUT()
{
	// 255 for uchar;
	T maxVal = numeric_limits<T>::max();
	/*
	 * Color equalisation consists in applying the corresponding cumulative
	 * histogram (cumulHistograms[c=0..channels][i=0..bins] normalized to
	 * maxVal)
	 * as a color transfert function
	 */
	for (size_t c = 0; c < channels; c++)
	{
		// TODO à compléter ...
	}

	return &colorTransferFunc;
}

/*
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
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeGrayThresholdLUT(const float tPercent)
{
	T minVal = 0;
	T maxVal = numeric_limits<T>::max(); // 255 for uchar;

	if (computeGray && nbHistograms == 4)
	{
		if (tPercent > 0.0 && tPercent < 100.0)
		{
			// determine threshold population count
			float thresLevel = (float) cMaxValue * (tPercent / 100);

			// initialize thresIndex at any possible value;
			size_t thresIndex = bins / 2;

			// search for thresLevel in cumulHistograms[HIST_GRAY][i=0..bins]
			// TODO à compléter ...
            for(size_t i=0; i<=bins; i++){
                if(cumulHistograms[HIST_GRAY][i]>thresLevel){
                    thresIndex = i;
                    break;
                }
            }

			// apply minVal in monoTransfertFunc to population below threshold index
			// TODO à compléter ...
            for(size_t j=0; j<thresIndex; j++){
                monoTransfertFunc.at<T>(0,j) = minVal;
            }

			// apply maxVal in monoTransfertFunc to population above threshold index
			// TODO à compléter ...
            for(size_t k=thresIndex; k<=bins; k++){
                monoTransfertFunc.at<T>(0,k) = maxVal;
            }

		}
		else
		{
			cerr << "CvHistograms<T,channels>::computeGrayThresholdLUT : "
				 << "percentage should be between 0 and 100 : " << tPercent
				 << endl;
		}
	}
	else
	{
		cerr << "CvHistograms<T,channels>::computeGrayThresholdLUT : "
			 << "There is no gray level histogram" << endl;
	}

	return &monoTransfertFunc;
}

/*
 * Compute the LUT corresponding to thresholded image with tPercent
 * of the pixel components population on each side of the
 * thresholds according to the cumulative color histograms
 * @param tPercent percent of the population on each side of the
 * thresholds
 * @return the matrix contaning each channel level equalization LUT to
 * apply on the image
 * @post the result is stored in colorTransferFunc
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeColorThresholdLUT(const float tPercent)
{
	T minVal = 0;
	T maxVal = numeric_limits<T>::max(); // 255 for uchar;
	size_t mThresIndex[channels];

	if (tPercent > 0.0 && tPercent < 100.0)
	{

		// determine threshold population count
		float thresLevel = (float) cMaxValue * (tPercent / 100);

        for (size_t c = 0; c < channels; c++)
		{
			// initialize thresIndex at any possible value;
			size_t thresIndex = bins / 2;

			// search for thresLevel in cumulHistograms[c][i=0..bins]
			// TODO à compléter ...
            for(size_t i=0; i<=bins; i++){
                if(cumulHistograms[c][i]>thresLevel){
                    thresIndex = i;
                    break;
                }
            }

			mThresIndex[c] = thresIndex;

			// apply minVal in colorTransferFunc to population below threshold index
			// TODO à compléter ...

                for (size_t i = 0; i < mThresIndex[c]; i++)
                {
                    colorTransferFunc.at<Vec<T, channels> >(0, i)[c] = minVal;
                }


			// apply maxVal in colorTransferFunc to population above threshold index
			// TODO à compléter ...

                for (size_t i = mThresIndex[c]; i < bins; i++)
                {
                    colorTransferFunc.at<Vec<T, channels> >(0, i)[c] = maxVal;
                }

		}
	}
	else
	{
		cerr << "CvHistograms<T,channels>::computeGrayThresholdLUT : "
			 << "percentage should be between 0 and 100 : " << tPercent << endl;
	}

	return &colorTransferFunc;
}

/*
 * Compute gamma LUT.
 * \f$y(k) = x(k)^{\gamma}\f$
 * @param tPercent
 * @return the matrix containing the gamma LUT
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeGammaLUT(const float tPercent)
{
	/*
	 * Gamma varies approximately from
	 * 0.25 when tPercent==0% to 4 when tPercent ==100%
	 */
	double gamma = 0.4101 * exp(2.3186 * ((double) tPercent / 100.0)) - 0.2506;

	// Apply (x^gamma)*bins where x=i/bins in monoTransfertFunc
	// TODO à compléter ...

	return &monoTransfertFunc;
}

/*
 * Compute the LUT corresponding to negative image
 * @return the matrix containing the negative LUT (mono)
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeNegativeLUT()
{
	// Apply (bins - 1 -i) in  monoTransfertFunc
	// TODO à compléter ...
    for(size_t i=0; i<bins; i++){
        monoTransfertFunc.at<T>(0, i) = bins-i-1;
    }
	return &monoTransfertFunc;
}

/*
 * Compute and returns the current transfert function to be applied
 * on the image, eventually with the current LUT parameter
 * @return the mono or color LUT matrix to apply on the image depending
 * on the lutType
 * @see TransfertType
 */
template <typename T, size_t channels>
Mat * CvHistograms<T, channels>::computeLUT()
{
	Mat * lut = NULL;

	lutUpdated = true;

	switch (lutType)
	{
		case NONE:
			/*
			 * Identity LUT
			 * Linear LUT does not depend on histogram so if previous
			 * LUT was already Linear then don't compute it again, just
			 * return the last LUT
			 */
			if (previousLutType != lutType)
			{
				lut = computeLinearGrayLUT();
			}
			else
			{
				lut = &monoTransfertFunc;
				lutUpdated = false;
			}
			break;
		case THRESHOLD_GRAY:
			/*
			 * LUT to split pixels below param % to black and pixels over
			 * param % to white based on graylevel cumulative histogram
			 */
			lut = computeGrayThresholdLUT(lutParam);
			break;
		case THRESHOLD_COLOR:
			/*
			 * LUT to split param% of the pixel components to black and
			 * 100-param% to full B, G or R based on cumulative histograms
			 * components
			 */
			lut = computeColorThresholdLUT(lutParam);
			break;
		case DYNAMIC_GRAY:
			/*
			 * LUT to spread param% of the pixel levels over 100% of the dynamic
			 * based on cumulative gray level histogram
			 */
			lut = computeGrayOptimalLUT(lutParam);
			break;
		case DYNAMIC_COLOR:
			/*
			 * LUT to spread param% of the pixel components levels over 100% of
			 * the dynamic based on cumulative color histograms
			 */
			lut = computeColorOptimalLUT(lutParam);
			break;
		case EQUALIZE_GRAY:
			/*
			 * Gray level histogram equalization LUT
			 */
			lut = computeGrayEqualizeLUT();
			break;
		case EQUALIZE_COLOR:
			/*
			 * Color components histograms equalization LUTs
			 */
			lut = computeColorEqualizeLUT();
			break;
		case GAMMA:
			/*
			 * Gamma LUT does not depend on histogram so if previous
			 * LUT was already Gamma then don't compute it again, just
			 * return the last LUT
			 */
			if ((previousLutType != lutType) || (previousLutParam != lutParam))
			{
				lut = computeGammaLUT(lutParam);
			}
			else
			{
				lut = &monoTransfertFunc;
				lutUpdated = false;
			}
			break;
		case NEGATIVE:
			/*
			 * Negative LUT does not depend on histogram so if previous
			 * LUT was already Negative then don't compute it again, just
			 * return the last LUT
			 */
			if (previousLutType != lutType)
			{
				lut = computeNegativeLUT();
			}
			else
			{
				lut = &monoTransfertFunc;
				lutUpdated = false;
			}
			break;
		default:
			cerr << "CvHistograms<T,channels>::applyLUT : unknown LUT" << endl;
			break;
	}

	if ((previousLutType != lutType) || (previousLutParam != lutParam))
	{
		resetMeanProcessTime();
	}

	previousLutType = lutType;
	previousLutParam = lutParam;

	return lut;
}

/*
 * Apply current LUT (if != NULL) to the source image to produce the
 * outFrame
 * @return true if LUT has been applied, false if lut is NULL or
 * lutType is NONE
 */
template <typename T, size_t channels>
bool CvHistograms<T, channels>::drawTransformedImage()
{
	if ((lut != NULL) && (lutType != NONE))
	{
		LUT(*sourceImage, *lut, outDisplayFrame);
		return true;
	}
	else
	{
		outDisplayFrame = *sourceImage;
		return false;
	}
}

/*
 * output operator for Histograms
 * @param out the output stream
 * @param h the histograms to print on the stream
 * @return a reference to the output stream so it can be cumulated
 */
template <typename T, size_t channels>
ostream & operator<<(ostream & out, const CvHistograms<T, channels> & h)
{
	for (size_t i = 0; i < h.bins; i++)
	{
		out << i << " : ";

		for (size_t j = 0; j < h.nbHistograms; j++)
		{
			out << h.histograms[i][j] << " ";
		}

		out << endl;
	}

	return out;
}

// =============================================================================
// Templates proto instanciations
// =============================================================================

// template class instanciation
// for gray level images
template class CvHistograms<uchar, 1>;
template ostream & operator<<(ostream &, const CvHistograms<uchar, 1> &);

// for BGR or YUV images
template class CvHistograms<uchar, 3>;
template ostream & operator<<(ostream &, const CvHistograms<uchar, 3> &);
