/*
 * CvAlgoParamSets.cpp
 *
 *  Created on: 20 avr. 2014
 *      Author: davidroussel
 */
#include <iostream>
#include <sstream>
#include <cctype>	// for toupper
#include <algorithm>	// for transform
using namespace std;

#include "CvAlgoParamSets.h"

/*
 * character indicating end of line : '\n' or '\r'
 */
char CvAlgoParamSets::eol = '\n';


/*
 * Known feature names
 */
const string CvAlgoParamSets::FeatureNames[FEATURES] =
{
	"AGAST",
	"AKAZE",
	"BRIEF",
	"BRISK",
	"FAST",
	"FREAK",
	"GFTT",
	"KAZE",
	"MSER",
	"ORB",
	"SIFT",
	"STAR",
	"SURF"
};

/*
 * Default Constructor (to use in subclasses which feature their own
 * file parsing)
 */
CvAlgoParamSets::CvAlgoParamSets()
{
}

/*
 * Constructor from CSV file containing algorithms parameters
 * @param stream the stream to read from
 */
CvAlgoParamSets::CvAlgoParamSets(ifstream & stream)
{
	string lineString;
	while (stream.good())
	{
		std::getline(stream, lineString, eol); // read until next line

		if (!checkSeparators(lineString))
		{
			break;
		}

		istringstream lineStream(lineString);
		string algoName;
		if (lineStream.good())
		{
			getline(lineStream, algoName, CvAlgoParam::sep); // read a string until next tag

			if (algoName.length() > 0)
			{
				if (!contains(algoName))
				{
					// Adds this paramSet
					addParamSet(CvAlgoParamSet(algoName));
				}

				CvAlgoParamSet * const paramSet = getParamSet(algoName);

				// Adds this parameter to this param set
				paramSet->addParameter(new CvAlgoParam(lineString));
			}
		}
	}
}

/*
 * Destructor
 */
CvAlgoParamSets::~CvAlgoParamSets()
{
	paramSets.clear();
}

/*
 * Get algorithm parameter set
 * @param name the name of the algorithm to search
 * @return a pointer to the requested parameter set or NULL
 * if this parameter set does not exist
 */
CvAlgoParamSet * CvAlgoParamSets::getParamSet(const string& name)
{
	map<string, CvAlgoParamSet>::iterator pos = paramSets.find(name);

	if (pos != paramSets.end())
	{
		return &(pos->second);
	}
	else
	{
		return NULL;
	}
}

/*
 * Get algorithm parameter set from algo smart pointer
 * @param ptr the smart pointer of the algorithm to search
 * @return a pointer to the requested parameter set or NULL
 * if this parameter set does not exist
 */
CvAlgoParamSet * CvAlgoParamSets::getParamSetPtr(const Ptr<Feature2D> & ptr)
{
	if (!ptr.empty())
	{
		const Feature2D * algoPtr = ptr.get();
		string actualName = typeid(*algoPtr).name(); // Migh be something like N2cv11xfeatures2d9SURF_ImplE
		string actualNameUp(actualName);
		std::transform(actualName.begin(), actualName.end(), actualNameUp.begin(), ::toupper);
		for (size_t i = 0; i < (size_t) FEATURES; i++)
		{
			if (actualNameUp.find(FeatureNames[i]) != string::npos)
			{
				return CvAlgoParamSets::getParamSet(FeatureNames[i]);
			}
		}
	}

	return NULL;
}

/*
 * Checks if there is a parameter set with name "name"
 * @param name the name of the parameter set we're looking for
 * @return true if there is a parameter set with this name
 */
bool CvAlgoParamSets::contains(const string & name)
{
	map<string, CvAlgoParamSet>::const_iterator pos = paramSets.find(name);
	return pos != paramSets.end();
}

/*
 * Add a new parameter set for an algorithm
 * @param paramSet the new algorithm parameter set to add
 * @return true if the new parameter set was not already present
 */
bool CvAlgoParamSets::addParamSet(const CvAlgoParamSet& paramSet)
{
	string name = paramSet.getName();
	if (paramSets.find(name) == paramSets.end())
	{
		paramSets.insert(pair<string, CvAlgoParamSet>(name, paramSet));
		return true;
	}
	else
	{
		cerr << "CvAlgoParamSet::addParamSet(" << name
			 << ") already exists in parameters sets" << endl;
		return false;
	}
}

/*
 * Check parameter sets content
 * @return true if parameter sets are empty (contains no paramter sets)
 */
bool CvAlgoParamSets::empty() const
{
	return paramSets.empty();
}


/*
 * Friend output operator
 * @param out the output stream
 * @param paramSets the parameters sets to send to output
 * @return a reference to output stream
 */
ostream & operator <<(ostream & out, const CvAlgoParamSets & paramSets)
{
	for (map<string, CvAlgoParamSet>::const_iterator it =
		 paramSets.paramSets.begin(); it != paramSets.paramSets.end(); ++it)
	{
		out << it->second;
	}

	return out;
}

/*
 * Checks if a line contains the right number of separators
 * @param line the line to check
 * @param sep the separator to check
 * @param nb the number of separators we exect in this line
 * @return true if the line contains the right number of separators, false
 * otherwise
 */
bool CvAlgoParamSets::checkSeparators(const string & line,
									  const char sep,
									  const size_t nb)
{
	size_t pos = 0;
	size_t count = 0;
	size_t max = line.length();
	while (((pos = line.find(sep, pos)) != string::npos) && (pos < max))
	{
		pos++;
		count++;
	}

	return count == nb;
}
