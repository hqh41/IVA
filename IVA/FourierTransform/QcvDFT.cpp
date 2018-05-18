/*
 * QcvDFT.cpp
 *
 *  Created on: 22 févr. 2012
 *      Author: davidroussel
 */

#include "QcvDFT.h"


/*
 * QcvDFT constructor
 * @param image the source image
 * @param imageLock the mutex for concurrent access to the source image.
 * In order to avoid concurrent access to the same image
 * @param updateThread the thread in which this processor should run
 * @param parent parent QObject
 */
QcvDFT::QcvDFT(Mat *image,
			   QMutex * imageLock,
			   QThread * updateThread,
			   QObject *parent) :
	CvProcessor(image), // <-- virtual base class constructor first
	QcvProcessor(image, imageLock, updateThread, parent),
	CvDFT(image),
	selfLock(updateThread != NULL ? new QMutex() :
									(imageLock != NULL ? imageLock : NULL))
{
}

/*
 * QcvDFT destructor
 */
QcvDFT::~QcvDFT()
{
	message.clear();
	if (selfLock != NULL)
	{
		// wait for update completion
		selfLock->lock();
		selfLock->unlock();
		delete selfLock;
	}
}

/*
 * Update computed images slot and sends updated signal
 * required
 */
void QcvDFT::update()
{
	bool hasSourceLock = (sourceLock != NULL) && (sourceLock != selfLock);
	if (hasSourceLock)
	{
		sourceLock->lock();
		// qDebug() << "QcvDFT::update : lock";
	}
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}
	/*
	 * Update DFT images
	 */
	CvDFT::update();

	if (hasLock)
	{
		selfLock->unlock();
	}
	if (hasSourceLock)
	{
		// qDebug() << "QcvDFT::update : unlock";
		sourceLock->unlock();
	}

	/*
	 * emit updated signal
	 */
	QcvProcessor::update();
}

/*
 * Changes source image slot.
 * Attributes needs to be cleaned up then set up again
 * @param image the new source Image
 */
void QcvDFT::setSourceImage(Mat *image)
	throw (CvProcessorException)
{
	Size previousSize(sourceImage->size());
	int previousNbChannels(nbChannels);
	Size previousDftSize(dftSize);
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

	emit squareImageChanged(&inFrameSquare);

	emit spectrumImageChanged(&spectrumMagnitudeImage);

	emit inverseImageChanged(&inverseImage);

	if ((previousDftSize.width != dftSize.width) ||
		(previousDftSize.height != dftSize.height))
	{
		emit imageSizeChanged();
		emit sendText(QString::number(optimalDFTSize));
	}

	// Force update
	// update();
}

/*
 * Filter type setting with notification
 * @param filterType ne new filter type
 */
void QcvDFT::setFilterType(FilterType filterType)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDFT::setFilterType(filterType);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();
	message.append(tr("Filter type set to "));
	switch (filterType)
	{
		case BOX_FILTER:
			message.append(tr("Box"));
			break;
		case GAUSS_FILTER:
			message.append(tr("Gaussian"));
			break;
		case SINC_FILTER:
			message.append(tr("Sinus Cardinal"));
			break;
		default:
			message.append(tr("Unknown"));
			break;
	}

	emit sendMessage(message, defaultTimeOut);
}

/*
 * Setting filtering status with notification
 * @param filtering ne new filtering status
 */
void QcvDFT::setFiltering(bool filtering)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDFT::setFiltering(filtering);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();

	message.append(tr("frequency filtering is "));

	if (filtering)
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
 * Setting the log scale factor
 * @param logScaleFactor the new log scale factor
 */
void QcvDFT::setLogScaleFactor(double logScaleFactor)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDFT::setLogScaleFactor(logScaleFactor);

	if (hasLock)
	{
		selfLock->unlock();
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
void QcvDFT::setLowPassFilterSize(const int channel, const int filterSize)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDFT::setLowPassFilterSize(channel, filterSize);

	if (hasLock)
	{
		selfLock->unlock();
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
void QcvDFT::setHighPassFilterSize(const int channel,const int filterSize)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvDFT::setHighPassFilterSize(channel, filterSize);

	if (hasLock)
	{
		selfLock->unlock();
	}
}
