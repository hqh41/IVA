/*
 * CvProcessor.cpp
 *
 *  Created on: 21 févr. 2012
 *	  Author: davidroussel
 */


#include "CvProcessor.h"

/*
 * OpenCV image processor constructor
 * @param sourceImage the source image
 * @pre source image is not NULL
 */
CvProcessor::CvProcessor(Mat *sourceImage, const VerboseLevel level) :
	sourceImage(sourceImage),
	nbChannels(sourceImage->channels()),
	size(sourceImage->size()),
	type(sourceImage->type()),
	verboseLevel(level),
	processTime(0),
	meanProcessTime(clock_t(0)),
	timePerFeature(false)
{
	// No dynamic links in constructors, so this setup will always be
	// CvProcessor::setup
	setup(sourceImage, false);
}

/*
 * OpenCV image Processor destructor
 */
CvProcessor::~CvProcessor()
{
	// No Dynamic link in destructors ?
	cleanup();

	map<string, Mat*>::const_iterator cit;
	for (cit = images.begin(); cit != images.end(); ++cit)
	{
		// Release handle to evt deallocate data
		/*
		 * Since this is a pointer it should be necessary to release data
		 */
		cit->second->release();
	}
	// Calls destructors on all elements
	images.clear();
}

/*
 * Setup internal attributes according to source image
 * @param sourceImage a new source image
 * @param fullSetup full setup is needed when source image is changed
 * @pre sourceimage is not NULL
 * @note this method should be reimplemented in sub classes
 */
void CvProcessor::setup(Mat *sourceImage, const bool fullSetup)
{
	if (verboseLevel >= VERBOSE_ACTIVITY)
	{
		clog << "CvProcessor::"<< (fullSetup ? "full " : "") <<"setup" << endl;
	}

	// Full setup starting point (==> previous cleanup)
	if (fullSetup)
	{
		this->sourceImage = sourceImage;
		nbChannels = sourceImage->channels();
		size = sourceImage->size();
		type = sourceImage->type();
	}

	// Partial setup starting point  (==> in any cases)
	processTime = (clock_t) 0;
	resetMeanProcessTime();
	addImage("source", this->sourceImage);
}

/*
 * Clean up internal atrtibutes before changing source image or
 * cleaning up class before destruction
 * @note this method should be reimplemented in sub classes
 */
void CvProcessor::cleanup()
{
	if (verboseLevel >= VERBOSE_ACTIVITY)
	{
		clog << "CvProcessor::cleanup()" << endl;
	}

	// remove source pointer
	map<string, Mat*>::iterator it;
	for (it = images.begin(); it != images.end(); ++it)
	{
		if (it->first == "source")
		{
			images.erase(it);
			break;
		}
	}
}

/*
 * Changes source image
 * @param sourceImage the new source image
 * @throw CvProcessorException#NULL_IMAGE when new source image is NULL
 */
void CvProcessor::setSourceImage(Mat *sourceImage)
	throw (CvProcessorException)
{
	if (verboseLevel >= VERBOSE_NOTIFICATIONS)
	{
		clog << "CvProcessor::setSourceImage(" << (unsigned long) sourceImage
			 << ")" << endl;
	}

	// clean up current attributes
	cleanup();

	if (sourceImage == NULL)
	{
		clog << "CvProcessor::setSourceImage NULL sourceImage" << endl;
		throw CvProcessorException(CvProcessorException::NULL_IMAGE);
	}

	// setup attributes again
	setup(sourceImage);
}

/*
 * Adds a named image to additionnal images
 * @param name the name of the image
 * @param image the image reference
 * @return true if image has been added to additionnal images map, false
 * if image key (the name) already exists in the addtitionnal images map.
 */
bool CvProcessor::addImage(const char *name, Mat * image)
{
	string sname(name);

	return addImage(sname, image);
}

/*
 * Adds a named image to additionnal images
 * @param name the name of the image
 * @param image the image reference
 * @return true if image has been added to additionnal images map, false
 * if image key (the name) already exists in the addtitionnal images map.
 */
bool CvProcessor::addImage(const string & name, Mat * image)
{
	if (verboseLevel >= VERBOSE_ACTIVITY)
	{
		clog << "Adding image " << name << "@[" << (long)(image) << "] in" << endl;
		// Show map content before adding image
		map<string, Mat*>::const_iterator cit;
		for (cit = images.begin(); cit != images.end(); ++cit)
		{
			clog  << "\t" << cit->first << "@["<< (long)(cit->second) << "]" << endl;
		}
	}

	pair<map<string,Mat*>::iterator,bool> ret;
	bool retValue;
	ret = images.insert(pair<string, Mat*>(name, image));

	if (ret.second == false)
	{
		if (verboseLevel >= VERBOSE_WARNINGS)
		{
			cerr << "CvProcessor::addImage(\"" << name
				<< "\",...) : already added" << endl;
		}

		retValue = false;
	}
	else
	{
		retValue = true;
	}

	return retValue;
}
/*
 * Update named image in additionnal images.
 * @param name the name of the image
 * @param image the image reference
 * @post the image located at key name is updated.
 */
//void CvProcessor::updateImage(const char * name, Mat * image)
//{
//	// Search for this name in the map
//	map<string, Mat*>::iterator it;
//	for (it = images.begin(); it != images.end(); ++it)
//	{
//		if (it->first == name)
//		{
//			(it->second->release();
//			images.erase(it);
//		}
//	}
//
//	string sname(name);
//
//	updateImage(sname, image);
//}

/*
 * Update named image in additionnal images.
 * @param name the name of the image
 * @param image the image reference
 * @post the image located at key name is updated.
 */
//void CvProcessor::updateImage(const string & name, const Mat & image)
//{
//	clog << "update image " << name << " with " << (long) &image << endl;
//	images.erase(name);
//
//	addImage(name, image);
//}

/*
 * Get image by name
 * @param name the name of the image we're looking for
 * @return the image registered by this name in the additionnal images
 * map
 * @throw CvProcessorException#INVALID_NAME is used name is not already
 * registerd in the images
 */
const Mat & CvProcessor::getImage(const char *name) const
	throw (CvProcessorException)
{
	string sname(name);

	return getImage(sname);
}

/*
 * Get image pointer by name
 * @param name the name of the image we're looking for
 * @return the image pointer registered by this name in the additionnal
 * images map
 * @throw CvProcessorException#INVALID_NAME is used name is not already
 * registerd in the images
 */
const Mat & CvProcessor::getImage(const string & name) const
	throw (CvProcessorException)
{
	// Search for this name
	map<string, Mat*>::const_iterator cit;
	for (cit = images.begin(); cit != images.end(); ++cit)
	{
		if (cit->first == name)
		{
			if (cit->second->data == NULL)
			{
				// image contains no data
				throw CvProcessorException(CvProcessorException::NULL_DATA,
										   name.c_str());
			}
			return *(cit->second);
		}
	}

	// not found : throw exception
	throw CvProcessorException(CvProcessorException::INVALID_NAME,
							   name.c_str());
}

/*
 * Get image pointer by name
 * @param name the name of the image we're looking for
 * @return the image pointer registered by this name in the additionnal
 * images map
 * @throw CvProcessorException#INVALID_NAME is used name is not already
 * registerd in the images
 */
Mat * CvProcessor::getImagePtr(const char *name)
	throw (CvProcessorException)
{
	string sname(name);

	return getImagePtr(sname);
}

/*
 * Get image pointer by name
 * @param name the name of the image we're looking for
 * @return the image registered by this name in the additionnal images
 * map
 * @throw CvProcessorException#INVALID_NAME is used name is not already
 * registerd in the images
 */
Mat * CvProcessor::getImagePtr(const string & name)
	throw (CvProcessorException)
{
	// Search for this name
	map<string, Mat*>::const_iterator cit;
	for (cit = images.begin(); cit != images.end(); ++cit)
	{
		if (cit->first == name)
		{
			if (verboseLevel >= VERBOSE_ACTIVITY)
			{
				clog << "getImagePtr(" << name << "): returning : "
					 << (long) (cit->second) << endl;
			}
			return cit->second;
		}
	}

	// not found : throw exception
	throw CvProcessorException(CvProcessorException::INVALID_NAME, name.c_str());
}

/*
 * Number of channels in source image
 * @return the number of channels of source image
 */
int CvProcessor::getNbChannels() const
{
	return nbChannels;
}

/*
 * Type of the source image
 * @return the openCV type of the source image
 */
int CvProcessor::getType() const
{
	return type;
}

/*
 * Get the current verbose level
 * @return the current verbose level
 */
CvProcessor::VerboseLevel CvProcessor::getVerboseLevel() const
{
	return verboseLevel;
}

/*
 * Set new verbose level
 * @param level the new verobse level
 */
void CvProcessor::setVerboseLevel(const VerboseLevel level)
{
	if ((level >= VERBOSE_NONE) && (level < NBVERBOSELEVEL))
	{
		verboseLevel = level;
	}

	cout << "Verbose level set to: ";
	switch (verboseLevel)
	{
		case VERBOSE_NONE:
			cout << "no messages";
			break;
		case VERBOSE_ERRORS:
			cout << "unrecoverable errors only";
			break;
		case VERBOSE_WARNINGS:
			cout << "errors and warnings";
			break;
		case VERBOSE_NOTIFICATIONS:
			cout << "errors, warnings and notifications";
			break;
		case VERBOSE_ACTIVITY:
			cout << "All messages";
			break;
		case NBVERBOSELEVEL:
		default:
			cout << "Unknown verobse mode (unchanged)";
			break;
	}
	cout << endl;
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
double CvProcessor::getProcessTime(const size_t) const
{
	return processTime;
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
double CvProcessor::getMeanProcessTime(const size_t) const
{
	return meanProcessTime.mean();
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
double CvProcessor::getStdProcessTime(const size_t) const
{
	return meanProcessTime.std();
}

/*
 * Return processor minimum processing time of step index [default
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
clock_t CvProcessor::getMinProcessTime(const size_t) const
{
	return meanProcessTime.min();
}

/*
 * Return processor maximum processing time of step index [default
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
clock_t CvProcessor::getMaxProcessTime(const size_t) const
{
	return meanProcessTime.max();
}

/*
 * Reset mean and std process time in order to re-start computing
 * new mean and std process time values.
 */
void CvProcessor::resetMeanProcessTime()
{
	meanProcessTime.reset();
}


/*
 * Indicates if processing time is per feature processed in the current
 * image or absolute
 * @return
 */
bool CvProcessor::isTimePerFeature() const
{
	return timePerFeature;
}

/*
 * Sets Time per feature processing time unit
 * @param value the time per feature value (true or false)
 */
void CvProcessor::setTimePerFeature(const bool value)
{
	timePerFeature = value;
}

/*
 * Send to stream (for showing processor attributes values)
 * @param out the stream to send to
 * @return a reference to the output stream
 */
ostream & CvProcessor::toStream(ostream & out) const
{
	return toStream_Impl<ostream>(out);
}

/*
 * Send to output stream operator
 * @param out the output stream to send to
 * @param proc the processor to send to the output stream
 * @return a reference to the output stream used
 */
ostream & operator <<(ostream & out, const CvProcessor & proc)
{
	return proc.toStream(out);
}

/*
 * Proto instantiation of CvProcessor template method
 * Stream & CvProcessor::toStream_Impl<Stream>(Stream &) const with concrete
 * type ostream
 */
template ostream & CvProcessor::toStream_Impl<ostream>(ostream &) const;
