/*
 * QcvHistograms.cpp
 *
 *  Created on: 14 févr. 2012
 *      Author: davidroussel
 */

#include <QDebug>
#include "QcvHistograms.h"

/*
 * QcvHistograms constructor
 * @param image the source image
 * @param computeGray indicates if an aditionnal gray level histogram
 * should be computed
 * @param drawHeight histogram drawing height
 * @param drawWidth histogram drawing width
 * @param timeCumulation indicates if timecumulation is on for histogram
 * @param imageLock the mutex for concurrent access to the source image.
 * In order to avoid concurrent access to the same image
 * @param updateThread the thread in which this processor should run
 * @param parent parent QObject
 */
QcvHistograms::QcvHistograms(Mat * image,
							 QMutex * imageLock,
							 QThread * updateThread,
							 const bool computeGray,
							 const size_t drawHeight,
							 const size_t drawWidth,
							 const bool timeCumulation,
							 QObject * parent) :
	CvProcessor(image),
	QcvProcessor(image, imageLock, updateThread, parent),
	CvHistograms8UC3(image, computeGray, drawHeight, drawWidth, timeCumulation),
	selfLock(updateThread != NULL ? new QMutex() :
									(imageLock != NULL ? imageLock : NULL))
{
	QcvProcessor::setNumberFormat("%7.0f");
}

/*
 * QImageHistogram destructor
 */
QcvHistograms::~QcvHistograms()
{
	updateHistogramTime1String.clear();
	computeLUTTimeString.clear();
	drawLUTTimeString.clear();
	applyLUTTimeString.clear();
	updateHistogramTime2String.clear();
	drawHistogramTimeString.clear();

	if (selfLock != NULL)
	{
		selfLock->lock();
		selfLock->unlock();
		delete selfLock;
	}
}

/*
 * Update computed images and sends displayImageChanged signal if
 * required
 */
void QcvHistograms::update()
{
	bool hasSourceLock = (sourceLock != NULL) && (sourceLock != selfLock);
	if (hasSourceLock)
	{
		sourceLock->lock();
	}

	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	/*
	 * Update Histogram images
	 */
	CvHistograms8UC3::update();

	if (hasLock)
	{
		selfLock->unlock();
	}

	if (hasSourceLock)
	{
		sourceLock->unlock();
	}

	/*
	 * emit time measurement signals
	 */
	const char * format = meanStdFormat.toStdString().c_str();
	updateHistogramTime1String.sprintf(format,
									   getMeanProcessTime(UPDATE_HISTOGRAM) / 1000.0,
									   getStdProcessTime(UPDATE_HISTOGRAM) / 1000.0);
	emit(histogramTime1Updated(updateHistogramTime1String));

	computeLUTTimeString.sprintf(format,
								 getMeanProcessTime(COMPUTE_LUT) / 1000.0,
								 getStdProcessTime(COMPUTE_LUT) / 1000.0);
	emit(computeLUTTimeUpdated(computeLUTTimeString));
	if (isLUTUpdated())
	{
		drawLUTTimeString.sprintf(format,
								  getMeanProcessTime(DRAW_LUT) / 1000.0,
								  getStdProcessTime(DRAW_LUT) / 1000.0);
		emit(drawLUTTimeUpdated(drawLUTTimeString));
	}

	applyLUTTimeString.sprintf(format,
							   getMeanProcessTime(APPLY_LUT) / 1000.0,
							   getStdProcessTime(APPLY_LUT) / 1000.0);
	emit(applyLUTTimeUpdated(applyLUTTimeString));

	if ((lut != NULL) && (lutType != NONE))
	{
		updateHistogramTime2String.sprintf(format,
										   getMeanProcessTime(UPDATE_HISTOGRAM_AFTER_LUT) / 1000.0,
										   getStdProcessTime(UPDATE_HISTOGRAM_AFTER_LUT) / 1000.0);
		emit(histogramTime2Updated(updateHistogramTime2String));
	}

	drawHistogramTimeString.sprintf(format,
									getMeanProcessTime(DRAW_HISTOGRAM) / 1000.0,
									getStdProcessTime(DRAW_HISTOGRAM) / 1000.0);
	emit(drawHistogramTimeUpdated(drawHistogramTimeString));

	/*
	 * emit updated signal
	 */
	QcvProcessor::update(); // emits updated signal
}

/*
 * Changes source image slot.
 * Attributes needs to be cleaned up then set up again
 * @param image the new source Image
 */
void QcvHistograms::setSourceImage(Mat * image) throw (CvProcessorException)
{
	Size previousSize(sourceImage->size());
	int previousNbChannels(nbChannels);
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvProcessor::setSourceImage(image);

	if (hasLock)
	{
		selfLock->unlock();
	}

	emit imageChanged(sourceImage);

	emit imageChanged();

	if ((previousSize.width != image->cols) ||
		(previousSize.height != image->rows))
	{
		emit imageSizeChanged();
	}

	if (previousNbChannels != nbChannels)
	{
		emit imageColorsChanged();
	}

	// notifies any connected component to change source images
	emit outImageChanged(&outDisplayFrame);
	emit histogramImageChanged(&histDisplayFrame);
	emit lutImageChanged(&lutDisplayFrame);
}


/*
 * Time cumulative histogram status read access
 * @param value the value to set for time cumulative status
 */
void QcvHistograms::setTimeCumulative(const bool value)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvHistograms8UC3::setTimeCumulative(value);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();
	message.append(tr("Time Cumulative Histogram is "));
	if (value)
	{
		message.append(tr("on"));
	}
	else
	{
		message.append(tr("off"));
	}
	emit sendMessage(message, defaultTimeOut);
}

/*
 * Cumulative histogram status read access
 * @param value the value to set for cumulative status
 */
void QcvHistograms::setCumulative(const bool value)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvHistograms8UC3::setCumulative(value);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();
	message.append(tr("Cumulative Histogram is "));
	if (value)
	{
		message.append(tr("on"));
	}
	else
	{
		message.append(tr("off"));
	}

	emit sendMessage(message, defaultTimeOut);
}

/*
 * Ith histogram component shown status write access
 * @param i the ith histogram component
 * @param value the value to set for this component show status
 */
void QcvHistograms::setShowComponent(const size_t i, const bool value)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvHistograms8UC3::setShowComponent(i, value);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();
	switch (i)
	{
		case 0:
			message.append(tr("Red"));
			break;
		case 1:
			message.append(tr("Green"));
			break;
		case 2:
			message.append(tr("Blue"));
			break;
		case 3:
			message.append(tr("Gray"));
			break;
		default:
			message.append(tr("Unkown"));
			break;
	}
	message.append(tr(" histogram Component is "));

	if (value)
	{
		message.append(tr("on"));
	}
	else
	{
		message.append(tr("off"));
	}

	emit sendMessage(message, defaultTimeOut);
}

/*
 * Sets the current LUT type
 * @param lutType the new LUT type
 */
void QcvHistograms::setLutType(const TransfertType lutType)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvHistograms8UC3::setLutType(lutType);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();
	message.append(tr("Current transfert function is "));
	switch (lutType)
	{
		case NONE:
			message.append(tr("Identity"));
			break;
		case THRESHOLD_GRAY:
			message.append(tr("Threshold based on gray histogram"));
			break;
		case DYNAMIC_GRAY:
			message.append(tr("Optimal dynamic based on gray histogram"));
			break;
		case EQUALIZE_GRAY:
			message.append(tr("Equalize based on gray histogram"));
			break;
		case THRESHOLD_COLOR:
			message.append(tr("Threshold based on color histograms"));
			break;
		case DYNAMIC_COLOR:
			message.append(tr("Optimal dynamic based on color histograms"));
			break;
		case EQUALIZE_COLOR:
			message.append(tr("Equalize based on color histograms"));
			break;
		case GAMMA:
			message.append(tr("Gamma"));
			break;
		case NEGATIVE:
			message.append(tr("Inverse"));
			break;
		default:
			message.append(tr("unknown"));
			break;
	}

	emit sendMessage(message, defaultTimeOut);
}

/*
 * Reset mean and std process time in order to re-start computing
 * new mean and std process time values.
 */
void QcvHistograms::resetMeanProcessTime()
{
	CvHistograms8UC3::resetMeanProcessTime();
}

/*
 * Draws selected histogram(s) in drawing frame and returns the drawing
 * frame
 * @return the updated drawing frame.
 */
void QcvHistograms::drawHistograms()
{
	CvHistograms8UC3::drawHistograms();
	emit histogramImageUpdated();
}

/*
 * Draws selected transfert function in drawing frame and returns the
 * drawing frame
 * @param lut the LUT to draw : the LUT may contains 1 or several
 * channels
 * @return the updated drawing frame
 */
void QcvHistograms::drawTransfertFunc(const Mat *lut)
{
	CvHistograms8UC3::drawTransfertFunc(lut);
	emit lutImageUpdated();
}

/*
 * Apply current LUT (if != NULL) to the source image to produce the
 * outFrame
 * @return true if LUT has been applied, false if lut is NULL or
 * lutType is NONE
 */
bool QcvHistograms::drawTransformedImage()
{
	bool result = CvHistograms8UC3::drawTransformedImage();
	emit outImageUpdated();
	return result;
}
