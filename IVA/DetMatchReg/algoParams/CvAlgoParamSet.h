/*
 * CvAlgoParamSet.h
 *
 *  Created on: 20 avr. 2014
 *      Author: davidroussel
 */

#ifndef CVALGOPARAMSET_H_
#define CVALGOPARAMSET_H_

#include <fstream>
#include <map>
using namespace std;

#include <opencv2/core/core.hpp>	// Ptr<Feature2D>
using namespace cv;

#include "CvAlgoParam.h"

/**
 * Class representing a set of parameters for an algorithm
 * @author David Roussel
 * @date 2014/04/24
 */
class CvAlgoParamSet
{
	public:
		/**
		 * Parameter set constructor with name
		 * @param name the name of the algorithm
		 */
		CvAlgoParamSet(const string & name);

		/**
		 * Parameter set destructor
		 */
		virtual ~CvAlgoParamSet();

		/**
		 * Algorithm name accessor
		 * @return the name of this parameter set
		 */
		string getName() const;

		/**
		 * Add a specific parameter to this parameter set
		 * @param param the parameter to add to this set
		 * @return true if the parameter was not already present in this
		 * parameter set, and has been added to this set, false otherwise
		 */
		virtual bool addParameter(CvAlgoParam * param);

		/**
		 * Parameter accessor by name
		 * @param name the name of the parameter we're looking for
		 * @return the requested parameter or CvAlgoParam::dummyParam if this
		 * parameter does not exist in this set.
		 */
		CvAlgoParam * getParameter(const string & name);

		/**
		 * Remove a named parameter from this parameter set
		 * @param name the name of the parameter to remove
		 * @return true if the parameter was present in this set and has
		 * been removed
		 */
		virtual bool removeParameter(const string & name);

		/**
		 * Check if this set contains a parameter by name
		 * @param name the name of the parameter
		 * @return true if this set contains a parameter with this name,
		 * false otherwise
		 */
		bool contains(const string & name) const;

		/**
		 * Check if this set contains this specific parameter
		 * @param param a reference to a parameter
		 * @return true if this set already contains this exact parameter,
		 * false otherwise
		 */
		bool contains(const CvAlgoParam & param) const;

		/**
		 * Number of parameters in this set
		 * @return the number of parameters in this set
		 */
		size_t nbParameters() const;

		/**
		 * Indicates this parameter set is empty
		 * @return true if this parameter set has no parameters,
		 * false otherwise
		 */
		bool isEmpty() const;

		/**
		 * Tests if this parameter set matches the name of a particular Feature2D
		 * @param ptr the smart pointer to a Feature2D algorithm
		 * @return true if the class of ptr content contains the name
		 * of this parameter set
		 */
		bool matches(const Ptr<Feature2D> & ptr);

		/**
		 * Adds an algorithm and if the algorithm contains all the parameters of
		 * this set then add it to set of algorithms associated to this set
		 * @param ptr the algorithm smart pointer
		 * @return true if algorithm have been added (iff it contains the same
		 * parameters as this set), false otherwise.
		 */
		bool addAlgorithm(const Ptr<Feature2D> & ptr);

		/**
		 * Remove an algorithm from the list of algorithms linked to this
		 * parameter set
		 * @param ptr the algorithm smart pointer to remove
		 * @return true if the algorithm smart pointer have been removed from
		 * the list of related algorithms
		 */
		bool removeAlgorithm(const Ptr<Feature2D> & ptr);

		/**
		 * Remove all algorithms from the list of algorithms linked to this
		 * parameter set.
		 */
		void removeAllAlgorithms();

		/**
		 * Iterator to the first element of map of params
		 * @return an iterator to the first element of the map of params
		 */
		map<string, Ptr<CvAlgoParam> >::iterator begin();

		/**
		 * Iterator past the last element of map of params
		 * @return an iterator past the last element of the map of params
		 */
		map<string, Ptr<CvAlgoParam> >::iterator end();

		/**
		 * Constant iterator to the first element of map of params
		 * @return an iterator to the first element of the map of params
		 */
		map<string, Ptr<CvAlgoParam> >::const_iterator cbegin() const;

		/**
		 * Constantn iterator past the last element of map of params
		 * @return an iterator past the last element of the map of params
		 */
		map<string, Ptr<CvAlgoParam> >::const_iterator cend() const;

		/**
		 * Output friend operator
		 * @param out the output stream
		 * @param paramSet the parameter set to print on the output
		 * @return the output stream
		 */
		friend ostream & operator <<(ostream & out,
									 const CvAlgoParamSet & paramSet);

	protected:
		/**
		 * The algorithm name for this parameters set
		 */
		string name;

		/**
		 * The map of parameters for this algorithm with associaction
		 * string = algorithm parameter name
		 * Ptr<CvAlgoParam> = smart pointer to algorithm parameter
		 */
		map<string, Ptr<CvAlgoParam> > params;
};

#endif /* CVALGOPARAMSET_H_ */
