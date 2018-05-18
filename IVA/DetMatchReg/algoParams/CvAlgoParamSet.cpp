/*
 * CvAlgoParamSet.cpp
 *
 *  Created on: 20 avr. 2014
 *      Author: davidroussel
 */

#include <iostream>		// cerr
#include <typeinfo>		// typeid
using namespace std;

#include "CvAlgoParamSet.h"

/*
 * Parameter set constructor with name
 * @param name the name of the algorithm
 */
CvAlgoParamSet::CvAlgoParamSet(const string& name) :
	name(name)
{
}

/*
 * Parameter set destructor
 */
CvAlgoParamSet::~CvAlgoParamSet()
{
	name.clear();

	params.clear();
}

/*
 * Algorithm name accessor
 * @return the name of this parameter set
 */
string CvAlgoParamSet::getName() const
{
	return name;
}

/*
 * Add a specific parameter to this parameter set
 * @param param the parameter to add to this set
 * @return true if the parameter was not already present in this
 * parameter set, and has been added to this set, false otherwise
 */
bool CvAlgoParamSet::addParameter(CvAlgoParam * param)
{
	if (param->isOk() && !contains(*param))
	{
		params.insert(pair<string, Ptr<CvAlgoParam> >(param->getName(),
													  Ptr<CvAlgoParam>(param)));
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Parameter accessor by name
 * @param name the name of the parameter we're looking for
 * @return the requested parameter or CvAlgoParam::dummyParam if this
 * parameter does not exist in this set.
 */
CvAlgoParam * CvAlgoParamSet::getParameter(const string& name)
{
	for (map<string, Ptr<CvAlgoParam> >::iterator it = params.begin();
		 it != params.end(); ++it)
	{
		if (it->first == name)
		{
//			clog << "Getting parameter " << name << " address =  "
//				 << (it->second) << endl;
			return (it->second);
		}
	}

	return NULL;
}

/*
 * Remove a named parameter from this parameter set
 * @param name the name of the parameter to remove
 * @return true if the parameter was present in this set and has
 * been removed
 */
bool CvAlgoParamSet::removeParameter(const string& name)
{
	map<string, Ptr<CvAlgoParam> >::iterator pos = params.find(name);
	if (pos != params.end())
	{
		params.erase(pos);
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Check if this set contains a parameter by name
 * @param name the name of the parameter
 * @return true if this set contains a parameter with this name,
 * false otherwise
 */
bool CvAlgoParamSet::contains(const string& name) const
{
	return params.find(name) != params.end();
}

/*
 * Check if this set contains this specific parameter
 * @param param a reference to a parameter
 * @return true if this set already contains this exact parameter,
 * false otherwise
 */
bool CvAlgoParamSet::contains(const CvAlgoParam& param) const
{
	for (map<string, Ptr<CvAlgoParam> >::const_iterator it = params.begin();
		 it != params.end(); ++it)
	{
		if (*(it->second) == param)
		{
			return true;
		}
	}

	return false;
}

/*
 * Number of parameters in this set
 * @return the number of parameters in this set
 */
size_t CvAlgoParamSet::nbParameters() const
{
	return params.size();
}

/*
 * Indicates this parameter set is empty
 * @return true if this parameter set has no parameters,
 * false otherwise
 */
bool CvAlgoParamSet::isEmpty() const
{
	return params.size() == 0;
}

/*
 * Tests if this parameter set matches the name of a particular Feature2D
 * @param ptr the smart pointer to a Feature2D algorithm
 * @return true if the class of ptr content contains the name
 * of this parameter set
 */
bool CvAlgoParamSet::matches(const Ptr<Feature2D> & ptr)
{
	if (!ptr.empty())
	{
		const Feature2D * algoPtr = ptr.get();
		if (algoPtr != NULL)
		{
			string actualName = typeid(*algoPtr).name();
			// Might be something like N2cv11xfeatures2d9SURF_ImplE
			string actualNameUp(actualName);
			std::transform(actualName.begin(),
						   actualName.end(),
						   actualNameUp.begin(),
						   ::toupper);

			return actualNameUp.find(name) != string::npos;
		}
	}
	return false;
}

/*
 * Adds an algorithm and if the algorithm contains all the parameter of this
 * set then add it to set of algorithms associated to this set
 * @param ptr the algorithm smart pointer
 * @return true if algorithm have been added (iff it contains the same
 * parameters as this set), false otherwise.
 */
bool CvAlgoParamSet::addAlgorithm(const Ptr<Feature2D> & ptr)
{
	if (!ptr.empty())
	{
		bool added = true;
		// Add this algorithm to all parameters
		for (map<string, Ptr<CvAlgoParam> >::iterator it = params.begin();
			 it != params.end(); ++it)
		{
			added &= it->second->addAlgorithm(ptr);
		}
		return added;
	}
	else
	{
		cerr << "CvAlgoParamSet::addAlgorithm(Empty pointer)" << endl;
	}

	return false;
}

/*
 * Remove an algorithm from the list of algorithms linked to this
 * parameter set
 * @param ptr the algorithm smart pointer to remove
 * @return true if the algorithm smart pointer have been removed from
 * the list of related algorithms
 */
bool CvAlgoParamSet::removeAlgorithm(const Ptr<Feature2D> & ptr)
{
	bool removed = true;

	// First remove this algorithm from all parameters
	for (map<string, Ptr<CvAlgoParam> >::iterator it = params.begin();
		 it != params.end(); ++it)
	{
		removed &= it->second->removeAlgorithm(ptr);
	}

	return removed;
}

/*
 * Remove all algorithms from the list of algorithms linked to this
 * parameter set.
 */
void CvAlgoParamSet::removeAllAlgorithms()
{
	for (map<string, Ptr<CvAlgoParam> >::iterator it = params.begin();
		 it != params.end(); ++it)
	{
		it->second->removeAllAlgorithms();
	}
}

/*
 * Iterator to the first element of map of params
 * @return an iterator to the first element of the map of params
 */
map<string, Ptr<CvAlgoParam> >::iterator CvAlgoParamSet::begin()
{
	return params.begin();
}

/*
 * Iterator past the last element of map of params
 * @return an iterator past the last element of the map of params
 */
map<string, Ptr<CvAlgoParam> >::iterator CvAlgoParamSet::end()
{
	return params.end();
}

/*
 * Constant iterator to the first element of map of params
 * @return an iterator to the first element of the map of params
 */
map<string, Ptr<CvAlgoParam> >::const_iterator CvAlgoParamSet::cbegin() const
{
	return params.cbegin();
}

/*
 * Constantn iterator past the last element of map of params
 * @return an iterator past the last element of the map of params
 */
map<string, Ptr<CvAlgoParam> >::const_iterator CvAlgoParamSet::cend() const
{
	return params.cend();
}

/*
 * Output friend operator
 * @param out the output stream
 * @param paramSet the parameter set to print on the output
 * @return the output stream
 */
ostream & operator <<(ostream & out, const CvAlgoParamSet & paramSet)
{
	out << "----------------------------------------------------------" << endl;
	out << paramSet.name << " parameters (" << paramSet.params.size() << ")"
		<< endl;
	for (map<string, Ptr<CvAlgoParam> >::const_iterator it =
		 paramSet.params.begin(); it != paramSet.params.end(); ++it)
	{
		out << *(it->second);
	}
	out << "----------------------------------------------------------" << endl;

	return out;
}
