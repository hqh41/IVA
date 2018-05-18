#include "CvProcessorException.h"
#include <iostream>		// for cerr et endl;
#include <string>		// for string
#include <sstream>		// for ostringstream
using namespace std;

/*
 * CvProcessor exception constructor
 * @param e the chosen error case for this error
 * @see ExceptionCause
 */
CvProcessorException::CvProcessorException(
	const CvProcessorException::ExceptionCause e) :
	exception(),
	cause(e),
	message("")
{
}

/*
 * CvProcessor exception constructor with message descriptor
 * @param e the chosen error case for this error
 * @param descr character string describing the message
 * @see ExceptionCause
 */
CvProcessorException::CvProcessorException(
	const CvProcessorException::ExceptionCause e, const char * descr) :
	exception(),
	cause(e),
	message(descr)
{
}

/*
 * CvProcessor exception from regular (typically OpenCV) exception
 * @param e the exception to relay
 */
CvProcessorException::CvProcessorException(const exception & e, const char * descr) :
	exception(e),
	cause(OPENCV_EXCEPTION),
	message(descr)
{
}


/*
 * CvProcessor exception destructor
 * @post message cleared
 */
CvProcessorException::~CvProcessorException() throw ()
{
	message.clear();
}

/*
 * Explanation message of the exception
 * @return a C-style character string describing the general cause
 * of the current error.
 */
const char * CvProcessorException::what() const throw()
{
	const char * initialWhat = exception::what();

	ostringstream output;

	output << initialWhat << " : ";

	output << "CvProcessorException : ";

	if (message.length() > 0)
	{
		output << message << " : ";
	}

	switch (cause) {
		case CvProcessorException::NULL_IMAGE:
			output << "NULL image" << endl ;
			break;
		case CvProcessorException::NULL_DATA:
			output << "NULL image data" << endl ;
			break;
		case CvProcessorException::INVALID_NAME:
			output << "Invalid name" << endl ;
			break;
		case CvProcessorException::INVALID_IMAGE_TYPE:
			output << "Invalid image type" << endl;
			break;
		case CvProcessorException::ILLEGAL_ACCESS:
			output << "Illegal access" << endl;
			break;
		case CvProcessorException::ALLOC_FAILURE:
			output << "New element allocation failure" << endl;
			break;
		case CvProcessorException::FILE_READ_FAIL:
			output << "Unable to read file" << endl;
			break;
		case CvProcessorException::FILE_PARSE_FAIL:
			output << "File parse error" << endl;
			break;
		case CvProcessorException::FILE_WRITE_FAIL:
			output << "Unable to write file" << endl;
			break;
		default:
			output << "Unknown exception" << endl;
			break;
	}

	return output.str().c_str();
}


/*
 * CvProcessorException cause
 * @return the cause enum of the exception
 */
CvProcessorException::ExceptionCause CvProcessorException::getCause()
{
	return cause;
}

/*
 * Source message of the exception
 * @return the message string of the exception
 */
string CvProcessorException::getMessage()
{
	return message;
}
