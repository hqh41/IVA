/*
 * QcvGFilter.cpp
 *
 *  Created on: 27 févr. 2012
 *      Author: davidroussel
 */

#include "QcvGFilter.h"


/*
 * QcvGFilter constructor
 * @param image the source image
 * @param imageLock the mutex on source image
 * @param updateThread the thread in which this processor runs
 * @param parent parent QObject
 */
QcvGFilter::QcvGFilter(Mat *image,
					   QMutex * imageLock,
					   QThread * updateThread,
					   QObject *parent) :
	CvProcessor(image), // <-- virtual base class constructor first
	QcvProcessor(image, imageLock, updateThread, parent),
	CvGFilter(image),
	selfLock(updateThread != NULL ? new QMutex() :
									(imageLock != NULL ? imageLock : NULL))
{
}

/*
 * QcvGFilter destructor
 */
QcvGFilter::~QcvGFilter()
{
	message.clear();
	if (selfLock != NULL)
	{
		selfLock->lock();
		selfLock->unlock();
		delete selfLock;
	}
}

/*
 * Changes source image slot.
 * Attributes needs to be cleaned up then set up again
 * @param image the new source Image
 */
void QcvGFilter::setSourceImage(Mat *image)
	throw (CvProcessorException)
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

	// Force update
	// update();
}

/*
 * Sets the a new kernel size
 * @param kernelSize the new kernel size
 * @post if new size is in range [3..15]
 * with a step of 2;
 * 	- the new kernel size is set up, and remains unchanged otherwise.
 *	- gaussian kernels are eventually recomputed
 */
void QcvGFilter::setKernelSize(int kernelSize)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvGFilter::setKernelSize(kernelSize);

	if (hasLock)
	{
		selfLock->unlock();
	}
}

/*
 * Sets a new value for gaussian variance
 * @param sigma the new value of gaussian variance
 */
void QcvGFilter::setSigma(double sigma)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvGFilter::setSigma(sigma);

	if (hasLock)
	{
		selfLock->unlock();
	}
}

/*
 * Sets new threshold level for edge map
 * @param thresholdLevel the new threshold level
 */
void QcvGFilter::setThresholdLevel(int thresholdLevel)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvGFilter::setThresholdLevel(thresholdLevel);

	if (hasLock)
	{
		selfLock->unlock();
	}
}

/*
 * Sets new Harris parameter Kappa
 * @param harrisKappa the new parameter to set
 */
void QcvGFilter::setHarrisKappa(double harrisKappa)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvGFilter::setHarrisKappa(harrisKappa);

	if (hasLock)
	{
		selfLock->unlock();
	}
}


/*
 * Sets a new display mode and emit corresponding imageChanged(Mat*)
 * signal
 * @param displayMode the new display mode to set
 */
void QcvGFilter::setDisplayMode(ImageDisplay displayMode)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvGFilter::setDisplayMode(displayMode);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();

	switch (this->displayMode)
	{
		case INPUT_IM:
			message.append("Source image");
			emit imageChanged(getImagePtr("source"));
			break;
		case GRAY_IM:
			message.append("Gray converted image");
			emit imageChanged(getImagePtr("gray"));
			break;
		case BLURRED_IM:
			message.append("Gray converted image, blurred with gaussian kernel");
			emit imageChanged(getImagePtr("blurred"));
			break;
		case GRADIENT_X_IM:
			message.append("Horizontal gradient");
			emit imageChanged(getImagePtr("dx"));
			break;
		case GRADIENT_Y_IM:
			message.append("Vertical gradient");
			emit imageChanged(getImagePtr("dy"));
			break;
		case GRADIENT_MAG_IM:
			message.append("Gradient magnitude");
			emit imageChanged(getImagePtr("gradientmag"));
			break;
		case GRADIENT_ANGLE_IM:
			message.append("Gradient angle");
			emit imageChanged(getImagePtr("gradientangle"));
			break;
		case EDGE_MAP_IM:
			// Embeded setEdgeMode
			setEdgeMode(edgeMode, false);
			break;
		case LAPLACIAN_IM:
			message.append("Laplacian image");
			emit imageChanged(getImagePtr("laplacian"));
			break;
		case CORNERNESS_IM:
			message.append("Cornerness");
			emit imageChanged(getImagePtr("cornerness"));
			break;
		case HARRISCORNER_IM:
			message.append("Harris cornerness");
			emit imageChanged(getImagePtr("harris"));
			break;
		case NBDISPLAY_IM:
		default:
			break;
	}

	emit sendMessage(message, defaultTimeOut);
}

/*
 * Set a new edge didsplay mode and emit corresponding
 * imageChanged(Mat*) signal if needed
 * @param edgeMode the new edge mode
 */
void QcvGFilter::setEdgeMode(EdgeDisplay edgeMode, const bool standalone)
{
	if (standalone)
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvGFilter::setEdgeMode(edgeMode);

		if (hasLock)
		{
			selfLock->unlock();
		}
	}

	if (displayMode == EDGE_MAP_IM)
	{
		if (standalone)
		{
			message.clear();
		}

		switch (edgeMode)
		{
			case THRESHOLD:
				message.append("Egde map by thresholding gradient magnitude");
				emit imageChanged(getImagePtr("edgemap"));
				break;
			case CANNY:
				message.append("Canny edges");
				emit imageChanged(getImagePtr("canny"));
				break;
			case MERGED:
				message.append("Mixed edge image");
				emit imageChanged(getImagePtr("mixedges"));
				break;
			case NBEDGEDISPLAY:
			default:
				break;
		}

		if (standalone)
		{
			emit sendMessage(message, defaultTimeOut);
		}
	}
}


/*
 * Update computed images slot and sends updated signal
 * required
 */
void QcvGFilter::update()
{
	bool hasSourceLock = (sourceLock != NULL) && (sourceLock != selfLock);

	if (hasSourceLock)
	{
		sourceLock->lock();
		// qDebug() << "QcvColorSpaces::update : lock";
	}

	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	/*
	 * Update filtered images
	 */
	CvGFilter::update();

	if (hasSourceLock)
	{
		// qDebug() << "QcvColorSpaces::update : unlock";
		sourceLock->unlock();
	}

	if (hasLock)
	{
		selfLock->unlock();
	}

	/*
	 * emit updated signal
	 */
	QcvProcessor::update();
}
