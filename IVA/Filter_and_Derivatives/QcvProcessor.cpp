/*
 * QCvProcessor.cpp
 *
 *  Created on: 19 févr. 2012
 *	  Author: davidroussel
 */

#include <QRegExpValidator>
#include <QMetaType>
#include <QDebug>
#include "QcvProcessor.h"

/*
 * Proto instantiation of CvProcessor template method
 * Stream & CvProcessor::toStream_Impl<Stream>(Stream &) const with concrete
 * type Qdebug
 */
template QDebug & CvProcessor::toStream_Impl<QDebug>(QDebug &) const;

/*
 * Default timeout to show messages
 */
int QcvProcessor::defaultTimeOut = 5000;

/*
 * Number format used to format numbers into QStrings
 */
QString QcvProcessor::numberFormat = QString::fromUtf8("%7.0f");

/*
 * The regular expression used to validate new number formats
 * @see #setNumberFormat
 */
QRegExp QcvProcessor::numberRegExp("%[+- 0#]*[0-9]*([.][0-9]+)?[efEF]");

/*
 * format used to format Mean/Std time values : <mean> ± <std>
 */
QString QcvProcessor::meanStdFormat = numberFormat + QString::fromUtf8(" ± %5.0f");

/*
 * format used to format Min/Max time values : <min> / <max>
 */
QString QcvProcessor::minMaxFormat = numberFormat +  QString::fromUtf8(" / ") +
									 numberFormat;

/*
 * QcvProcessor constructor
 * @param image the source image
 * @param imageLock the mutex for concurrent access to the source image
 * In order to avoid concurrent access to the same image
 * @param updateThread the thread in which this processor should run
 * @param parent parent QObject
 */
QcvProcessor::QcvProcessor(Mat * image,
						   QMutex * imageLock,
						   QThread * updateThread,
						   QObject * parent) :
	CvProcessor(image),	// <-- virtual base class constructor first
	QObject(parent),
	sourceLock(imageLock),
	updateThread(updateThread),
	message(),
	processTimeString()
{
	if (updateThread != NULL)
	{
		this->moveToThread(updateThread);

		connect(this, SIGNAL(finished()), updateThread, SLOT(quit()),
				Qt::DirectConnection);

		updateThread->start();
	}
}

/*
 * QcvProcessor destructor
 */
QcvProcessor::~QcvProcessor()
{
	// Lock might be already destroyed in source object so don't try to unlock

	message.clear();
	processTimeString.clear();

	emit finished();

	if (updateThread != NULL)
	{
		// Wait until update thread has received the "finished" signal through
		// "quit" slot
		updateThread->wait();
	}
}

/*
 * Sets new number format
 * @param format the new number format
 */
void QcvProcessor::setNumberFormat(const char * format)
{
	/*
	 * The format string should validate the following regex
	 * %[+- 0#]*[0-9]*([.][0-9]+)?[efEF]
	 */
	QRegExpValidator validator(numberRegExp, NULL);

	QString qFormat(format);
	int pos = 0;
	if (validator.validate(qFormat,pos) == QValidator::Acceptable)
	{
		numberFormat = format;
		meanStdFormat = format + QString::fromUtf8(" ± ") + format;
		minMaxFormat = format + QString::fromUtf8(" / ") + format;
	}
	else
	{
		qWarning("QcvProcessor::setNumberFormat(%s) : invalid format", format);
	}
}

/*
 * Send to stream (for showing processor attributes values)
 * @param dbg the debug stream to send to
 * @return a reference to the output stream
 */
QDebug & QcvProcessor::toDBStream(QDebug & dbg) const
{
	return toStream_Impl<QDebug>(dbg);
}

/*
 * Friend QDebug output operator
 * @param dbg the debug stream
 * @param proc the Qcvprocessor to send to debug stream
 * @return the debug stream
 */
QDebug & operator << (QDebug & dbg, const QcvProcessor & proc)
{
	proc.toDBStream(dbg.nospace());
	return dbg.space();
}

/*
 * Update computed images slot and sends updated signal
 * required
 */
void QcvProcessor::update()
{
	/*
	 * Important note : CvProcessor::update() should NOT be called here
	 * since it should be called in QcvXXXprocessor subclasses such that
	 * QcvXXXProcessor::update method should contain :
	 *	- call to CvXXXProcessor::update() (not QCvXXXProcessor)
	 *	- emit signals from QcvXXXProcessor
	 *	- call to QcvProcessor::update() (this method) to
	 *		- emit updated signal
	 *		- emit standard process time strings signals
	 *	- or
	 *		- emit updated signal in QcvXXXProcessor
	 *		- customize your processtimes and emit time strings signals
	 */
	emit updated();
	processTimeString.sprintf(meanStdFormat.toStdString().c_str(),
							  getMeanProcessTime(0), getStdProcessTime(0));
//	processMinMaxTimeString.sprintf(minMaxFormat.toStdString().c_str(),
//									getMinProcessTime(0), getMaxProcessTime(0));
	emit processTimeUpdated(processTimeString);
//	emit processTimeMinMaxUpdated(processMinMaxTimeString);
	emit processTimeUpdated(&meanProcessTime);
}

/*
 * Changes source image slot.
 * Attributes needs to be cleaned up then set up again
 * @param image the new source Image
 * @post Various signals are emitted:
 * 	- imageChanged(sourceImage)
 * 	- imageCchanged()
 * 	- if image size changed then imageSizeChanged() is emitted
 * 	- if image color space changed then imageColorsChanged() is emitted
 */
void QcvProcessor::setSourceImage(Mat *image)
	throw (CvProcessorException)
{
	Size previousSize(sourceImage->size());
	int previousNbChannels(nbChannels);

	if (sourceLock != NULL)
	{
		sourceLock->lock();
		// qDebug() << "QcvProcessor::setSourceImage: lock";
	}

	CvProcessor::setSourceImage(image);

	if (sourceLock != NULL)
	{
		// qDebug() << "QcvProcessor::setSourceImage: unlock";
		sourceLock->unlock();
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
	update();
}

/*
 * Sets Time per feature processing time unit (reimplemented as a slot).
 * @param value the time per feature value (true or false)
 */
void QcvProcessor::setTimePerFeature(const bool value)
{
	CvProcessor::setTimePerFeature(value);
}

/*
 * Reset mean and std process time in order to re-start computing
 * (reimplemented as a slot)
 * new mean and std process time values.
 */
void QcvProcessor::resetMeanProcessTime()
{
	CvProcessor::resetMeanProcessTime();
}


/*
 * Get the format c-string for numbers
 * @return the format string for numbers (e.g.: "%5.2f")
 */
const char * QcvProcessor::getNumberFormat()
{
	return numberFormat.toStdString().c_str();
}

/*
 * Get the format c-string for std dev of numbers
 * @return the format string for numbers (e.g.: " ± %4.2f")
 */
const char * QcvProcessor::getStdFormat()
{
	return meanStdFormat.toLocal8Bit().data();
}

/*
 * Get the format c-string for min / max of numbers
 * @return the format string for numbers (e.g.: "%5.2f / %5.2f")
 */
const char * QcvProcessor::getMinMaxFormat()
{
	return minMaxFormat.toLocal8Bit().data();
}
