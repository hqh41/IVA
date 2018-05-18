#ifndef CVPROCESSOREXCEPTION_H_
#define CVPROCESSOREXCEPTION_H_

#include <iostream>		// for ostream
#include <string>		// for string
#include <exception>	// for std::exception base class
using namespace std;

/**
 * Exception class for CvProcessor.
 * Contains mainly exception reasons why an CvProcessor operation could not be
 * performed.
 */
class CvProcessorException : public exception
{
	public:
		/**
		 * Matrices operation exception cases
		 */
		typedef enum
		{
			/**
			 * Null image.
			 * Used when trying to add null image as source image of the
			 * processor
			 */
			NULL_IMAGE,
			/**
			 * Null image data.
			 * Used when trying to use image with NULL data
			 */
			NULL_DATA,
			/**
			 * Invalid name in image acces by name.
			 * Used when searching for images by name which is not contained
			 * in the already registered names
			 */
			INVALID_NAME,
			/**
			 * Invalid image type.
			 * Some Processors needs specific images types
			 */
			INVALID_IMAGE_TYPE,
			/**
			 * Illegal data access (i.e. read/write access on read only data)
			 */
			ILLEGAL_ACCESS,
			/**
			 * Allocation failure on dynamically allocated elements
			 */
			ALLOC_FAILURE,
			/**
			 * Unable to read a file
			 */
			FILE_READ_FAIL,
			/**
			 * File parse error
			 */
			FILE_PARSE_FAIL,
			/**
			 * Unable to write file
			 */
			FILE_WRITE_FAIL,
			/**
			 * OpenCV exception
			 */
			OPENCV_EXCEPTION
		} ExceptionCause;

		/**
		 * CvProcessor exception constructor
		 * @param e the chosen error case for this error
		 * @see ExceptionCause
		 */
		CvProcessorException(const CvProcessorException::ExceptionCause e);

		/**
		 * CvProcessor exception constructor with exception message descriptor
		 * @param e the chosen error case for this error
		 * @param descr character string describing the message
		 * @see ExceptionCause
		 */
		CvProcessorException(const CvProcessorException::ExceptionCause e,
							 const char * descr);

		/**
		 * CvProcessor exception from regular (typically OpenCV) exception
		 * @param e the exception to relay
		 */
		CvProcessorException(const exception & e, const char * descr = "");

		/**
		 * CvProcessor exception destructor
		 * @post message cleared
		 */
		virtual ~CvProcessorException() throw ();

		/**
		 * Explanation message of the exception
		 * @return a C-style character string describing the general cause
		 * of the current error.
		 */
		virtual const char* what() const throw();

		/**
		 * CvProcessorException cause
		 * @return the cause enum of the exception
		 */
		CvProcessorException::ExceptionCause getCause();

		/**
		 * Source message of the exception
		 * @return the message string of the exception
		 */
		string getMessage();

		/*
		 * Note output operators are not necessary since what() method is used
		 * to explain the reason of the exception.
		 * Example :
		 * try
		 * {
		 * 	... do something which throws an std::exception
		 * }
		 * catch (exception & e)
		 * {
		 * 	cerr << e.what() << endl;
		 * }
		 */

	private:
		/**
		 * The current error case
		 */
		CvProcessorException::ExceptionCause cause;

		/**
		 * description message of the exception
		 */
		string message;
};

#endif /*CVPROCESSOREXCEPTION_H_*/
