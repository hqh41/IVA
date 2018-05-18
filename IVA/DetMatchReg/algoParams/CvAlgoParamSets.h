/*
 * CvAlgoParamSets.h
 *
 *  Created on: 20 avr. 2014
 *      Author: davidroussel
 */

#ifndef CVALGOPARAMSETS_H_
#define CVALGOPARAMSETS_H_

#include "CvAlgoParamSet.h"

#include <map>
#include <fstream>
#include <string>
using namespace std;

/**
 * Parameters sets for several algorithms
 * @author David Roussel
 * @date 2014/04/24
 */
class CvAlgoParamSets
{
	public:

		/**
		 * Known feature types
		 */
		typedef enum
		{
			AGAST = 0, //!< Adaptive and generic corner detection based on the accelerated segment test
			AKAZE = 1, //!< Accelerated KAZE Features
			BRIEF = 2, //!< BRIEF Descriptor: Binary Robust Independent Elementary Features
			BRISK = 3, //!< BRISK : Binary Robust Invariant Scalable Keypoints
			FAST = 4, //!< FAST: FAST Corner detection
			FREAK = 5, //!< FREAK Descriptor: Fast Retina Keypoint
			GFTT = 6, //!< GFTT : Good Features To Track
			KAZE = 7, //!< KAZE Features
			MSER = 8, //!< MSER : Maximally Stable Extremal Regions
			ORB = 9, //!< ORB : Oriented BRIEF Features
			SIFT = 10, //!< SIFT: Scale Invariant Feature Transform
			STAR = 11, //!< STAR: STAR feature
			SURF = 12, //!< SURF : Speeded Up Robust Features
			FEATURES = 13 //!< Number of Feature types
		} FeatureType;

		/**
		 * Known feature names
		 *	- "AGAST",
		 *	- "AKAZE",
		 *	- "BRIEF",
		 *	- "BRISK",
		 *	- "FAST",
		 *	- "FREAK",
		 *	- "GFTT",
		 *	- "KAZE"
		 *	- "MSER",
		 *	- "ORB",
		 *	- "SIFT",
		 *	- "STAR",
		 *	- "SURF"
		 * @note AKAZE needs to be before KAZE because "AKAZE" already contains
		 * "KAZE" in its name
		 */
		static const string FeatureNames[FEATURES];

	protected:
		/**
		 * Default Constructor (to use in subclasses which feature their own
		 * file parsing)
		 */
		CvAlgoParamSets();

	public:
		/**
		 * Constructor from CSV file containing algorithms parameters
		 * @param stream the stream to read from
		 */
		CvAlgoParamSets(ifstream & stream);

		/**
		 * Destructor
		 */
		virtual ~CvAlgoParamSets();

		/**
		 * Get algorithm parameter set from algo name
		 * @param name the name of the algorithm to search
		 * @return a pointer to the requested parameter set or NULL
		 * if this parameter set does not exist
		 */
		CvAlgoParamSet * getParamSet(const string & name);

		/**
		 * Get algorithm parameter set from algo smart pointer
		 * @param ptr the smart pointer of the algorithm to search
		 * @return a pointer to the requested parameter set or NULL
		 * if this parameter set does not exist
		 */
		CvAlgoParamSet * getParamSetPtr(const Ptr<Feature2D> & ptr);

		/**
		 * Checks if there is a parameter set with name "name"
		 * @param name the name of the parameter set we're looking for
		 * @return true if there is a parameter set with this name
		 */
		bool contains(const string & name);

		/**
		 * Add a new parameter set for an algorithm
		 * @param paramSet the new algorithm parameter set to add
		 * @return true if the new parameter set was not already present
		 */
		bool addParamSet(const CvAlgoParamSet & paramSet);

		/**
		 * Check parameter sets content
		 * @return true if parameter sets are empty (contains no paramter sets)
		 */
		bool empty() const;

		/**
		 * Friend output operator
		 * @param out the output stream
		 * @param paramSets the parameters sets to send to output
		 * @return a reference to output stream
		 */
		friend ostream & operator <<(ostream & out,
									 const CvAlgoParamSets & paramSets);

	protected:

		/**
		 * character indicating end of line : '\n' or '\r'
		 */
		static char eol;

		/**
		 * The map from algo name to algo parameters set
		 */
		map<string, CvAlgoParamSet> paramSets;

		/**
		 * Checks if a line contains the right number of separators
		 * @param line the line to check
		 * @param sep the separator to check
		 * @param nb the number of separators we exect in this line
		 * @return true if the line contains the right number of separators, false
		 * otherwise
		 */
		bool checkSeparators(const string & line,
							 const char sep = CvAlgoParam::sep,
							 const size_t nb = (CvAlgoParam::nbParamMaxTag - 1));
};

#endif /* CVALGOPARAMSETS_H_ */
