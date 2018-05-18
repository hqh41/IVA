/*
 * QcvFloodFill.cpp
 *
 *  Created on: 25 févr. 2012
 *      Author: davidroussel
 */

#include "QcvFloodFill.h"

/*
 * QcvFloodFill constructor
 * @param inFrame the input frame from capture
 * @param imageLock the mutex for concurrent access to the source image.
 * In order to avoid concurrent access to the same image
 * @param updateThread the thread in which this processor should run
 * @param parent parent QObject
 */
QcvFloodFill::QcvFloodFill(Mat * inFrame,
						   QMutex * imageLock,
						   QThread * updateThread,
						   QObject * parent) :
	CvProcessor(inFrame), // <-- virtual base class constructor first
	QcvProcessor(inFrame, imageLock, updateThread, parent),
	CvFloodFill(inFrame),
	selfLock(updateThread != NULL ? new QMutex() :
									(imageLock != NULL ? imageLock : NULL))

{
	numberFormat = QString::fromUtf8("%5.0f");
	meanStdFormat = numberFormat + QString::fromUtf8(" ± %4.0f µs");
	minMaxFormat = numberFormat + QString::fromUtf8(" / ") + numberFormat +
				   QString::fromUtf8(" µs");
}

/*
 * QcvFloodFill destructor
 */
QcvFloodFill::~QcvFloodFill()
{
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
void QcvFloodFill::update()
{
	bool hasSourceLock = (sourceLock != NULL) && (sourceLock != selfLock);
	if (hasSourceLock)
	{
		sourceLock->lock();
		// qDebug() << "QcvFloodFill::update : lock";
	}

	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::update();

	if (hasLock)
	{
		selfLock->unlock();
	}

	if (hasSourceLock)
	{
		// qDebug() << "QcvFloodFill::update : unlock";
		sourceLock->unlock();
	}

	// at the end of update, if displayImageChanged is true then display
	// image has changed
	if (displayImageChanged)
	{
		emit imageChanged(&displayImage);
	}

	/*
	 * emit updated signal
	 */
	QcvProcessor::update();
}

/*
 * Select image to set in displayImage and sends notification message
 * @param select the index to select display image
 */
void QcvFloodFill::setDisplayMode(const ImageDisplay index)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::setDisplayMode(index);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();
	message.append(tr("Display Image set to: "));
	switch (index)
	{
		case INPUT_IM:
			message.append(tr("Input"));
			break;
		case MASK_IM:
			message.append(tr("Mask"));
			break;
		case MERGED_IM:
			message.append(tr("Merged Mask/Input"));
			break;
		case NBDISPLAY_IM:
		default:
			message.append(tr("Unknown"));
			break;
	}

	emit sendMessage(message, defaultTimeOut);
}

/*
 * Sets a new flooding mode (absolute or relative) with notification
 * @param ffillMode the new flooding mode
 */
void QcvFloodFill::setFfillMode(const FloodFillMode ffillMode)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::setFfillMode(ffillMode);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();
	message.append(tr("Flood type set to "));
	switch (getFfillMode())
	{
		case FIXED_RANGE:
			message.append(tr("Fixed"));
			break;
		case FLOATING_RANGE:
			message.append(tr("Floating"));
			break;
		default:
			message.append(tr("Unknown"));
			break;
	}

	message.append(tr(" range threshold"));

	emit sendMessage(message, defaultTimeOut);
}

/*
 * Sets a new lower difference in pixels values for flooding
 * @param loDiff the new lower difference for flooding
 */
void QcvFloodFill::setLoDiff(const int loDiff)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::setLoDiff(loDiff);

	if (hasLock)
	{
		selfLock->unlock();
	}

}

/*
 * Sets a new upper difference in pixels values for flooding
 * @param upDiff the new upper difference for flooding
 */
void QcvFloodFill::setUpDiff(const int upDiff)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::setUpDiff(upDiff);

	if (hasLock)
	{
		selfLock->unlock();
	}

}

/*
 * Sets a new connectivity for pixels neighbors for flooding with
 * notification
 * @param connectivity the new connectivity for pixels neighbors
 * for flooding
 */
void QcvFloodFill::setConnectivity(const int connectivity)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::setConnectivity(connectivity);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();

	message.append(tr("Pixel connectivity set to "));
	message.append(QString::number(getConnectivity()));
	message.append(tr(" neighbors"));

	emit sendMessage(message, defaultTimeOut);
}

/*
 * Sets an new initial seed
 * @param initialSeed the new initial seed
 */
void QcvFloodFill::setInitialSeed(const Point & initialSeed)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::setInitialSeed(initialSeed);

	if (hasLock)
	{
		selfLock->unlock();
	}
}

/*
 * Sets new show/hide seed point status with notification
 * @param showSeed the new show/hide seed point status
 */
void QcvFloodFill::setShowSeed(const bool showSeed)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::setShowSeed(showSeed);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();

	message.append(tr("Show seed point is "));
	if(isShowSeed())
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
 * Set the show/hide bounding box status with notification
 * @param showBoundingBox the new show/hide bounding box status
 */
void QcvFloodFill::setShowBoundingBox(const bool showBoundingBox)
{
	bool hasLock = selfLock != NULL;
	if (hasLock)
	{
		selfLock->lock();
	}

	CvFloodFill::setShowBoundingBox(showBoundingBox);

	if (hasLock)
	{
		selfLock->unlock();
	}

	message.clear();

	message.append(tr("Show bouding box is "));
	if(isShowBoundingBox())
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
 * Slot to clear current flood when left or right mouse button is
 * pressed (should be connected to QcvMatWigdet::pressPoint signal)
 * Later relase event will evt trigger new seed for flood
 * @param p the point the event occured
 * @param button the pressed button
 */
void QcvFloodFill::clearFloodPoint(const QPoint &, const Qt::MouseButton & button)
{
	// if button is left or right
	if ((button == Qt::LeftButton) || (button == Qt::RightButton))
	{
		bool hasLock = selfLock != NULL;
		if (hasLock)
		{
			selfLock->lock();
		}

		CvFloodFill::clearFlood();

		if (hasLock)
		{
			selfLock->unlock();
		}
	}
}

/*
 * Slot to set intialSeed point
 * @param p the initial seed point
 * @param button the button pressed
 */
void QcvFloodFill::setSeedPoint(const QPoint & p, const Qt::MouseButton & button)
{
	// if button left initiate new seed
	if (button == Qt::LeftButton)
	{
		int px = (p.x() > 0 ? p.x() : 0);
		int py = (p.y() > 0 ? p.y() : 0);
		setInitialSeed(Point(px, py));
	}
}
