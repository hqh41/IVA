/*
 * CvAlgoParam.cpp
 *
 *  Created on: 20 avr. 2014
 *      Author: davidroussel
 */

#include <iostream>
#include <sstream>

using namespace std;

#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
using namespace cv::xfeatures2d;

#include "CvAlgoParam.h"

/*
 * character separating tags in the file : ';'
 */
const char CvAlgoParam::sep = ';';

/*
 * Dummy empty parameter (default constructed)
 */
//const CvAlgoParam CvAlgoParam::dummyParam;

/*
 * Maximum number of values descriptions
 */
size_t CvAlgoParam::nbValueDescriptionsMax = 8;

/*
 * Maximum number of tags in a parameter
 */
size_t CvAlgoParam::nbParamMaxTag = 17;

bool CvAlgoParam::UValueType::operator ==(const CvAlgoParam::UValueType & val) const
{
	return doubleValue == val.doubleValue;
}

/*
 * Default Constructor to dummy parameter
 */
CvAlgoParam::CvAlgoParam() :
	name(""),
	type(UNKNOWN),
	description(""),
	stepMode(CvAlgoParam::ADD),
	hasDefaultValue(false),
	parseError(true),
	parsingCompleted(true),
	gettable(false),
	settable(false),
	boolGetter(NULL),
	boolSetter(NULL),
	intGetter(NULL),
	intSetter(NULL),
	doubleGetter(NULL),
	doubleSetter(NULL)
{
}

/*
 * Copy constructor
 * @param param the param to copy
 */
CvAlgoParam::CvAlgoParam(const CvAlgoParam & param) :
	name(param.name),
	type(param.type),
	description(param.description),
	value(param.value),
	minValue(param.minValue),
	maxValue(param.maxValue),
	stepValue(param.stepValue),
	stepMode(param.stepMode),
	defaultValue(param.defaultValue),
	hasDefaultValue(param.hasDefaultValue),
	valueDescriptions(param.valueDescriptions),
	parseError(param.parseError),
	parsingCompleted(param.parsingCompleted),
	gettable(param.gettable),
	settable(param.settable),
	boolGetter(param.boolGetter),
	boolSetter(param.boolSetter),
	intGetter(param.intGetter),
	intSetter(param.intSetter),
	doubleGetter(param.doubleGetter),
	doubleSetter(param.doubleSetter),
	algorithms(param.algorithms)
{
}


/*
 * Constructor
 * @param name parameter name
 * @param type parameter type
 * @param description parameter description
 * @param value parameter value
 * @param minValue parameter minimum value
 * @param maxValue parameter maximum value
 * @param stepValue parameter step value
 * @param stepMode parameter step value mode (additive or
 * multiplicative)
 * @param descriptions parameter values descriptions
 * @param ptr smart pointer to an algorithm in order to change its
 * parameter value
 */
CvAlgoParam::CvAlgoParam(const string & name,
						 const ParamType & type,
						 const string & description,
						 const ValueType & value,
						 const ValueType & minValue,
						 const ValueType & maxValue,
						 const ValueType & stepValue,
						 const StepMode stepMode,
						 const vector<string> & descriptions) :
	name(name),
	type(type),
	description(description),
	value(value),
	minValue(minValue),
	maxValue(maxValue),
	stepValue(stepValue),
	stepMode(stepMode),
	hasDefaultValue(false),
	valueDescriptions(descriptions),
	parseError(false),
	parsingCompleted(true),
	gettable(false),
	settable(false),
	boolGetter(NULL),
	boolSetter(NULL),
	intGetter(NULL),
	intSetter(NULL),
	doubleGetter(NULL),
	doubleSetter(NULL)
{
}

/*
 * Constructor for an boolean parameter
 * @param name parameter name
 * @param description parameter description
 * @param value parameter value
 * @param ptr smart pointer to an algorithm in order to change its
 * parameter value
 */
CvAlgoParam::CvAlgoParam(const string & name,
						 const string & description,
						 const bool & value) :
	name(name),
	type(BOOLEAN),
	description(description),
	stepMode(ADD),
	hasDefaultValue(false),
	parseError(false),
	parsingCompleted(true),
	gettable(false),
	settable(false),
	boolGetter(NULL),
	boolSetter(NULL),
	intGetter(NULL),
	intSetter(NULL),
	doubleGetter(NULL),
	doubleSetter(NULL)
{
	this->value.boolValue = value;
	minValue.boolValue = false;
	maxValue.boolValue = true;
	stepValue.boolValue = true;
}

/*
 * Constructor for an integer parameter
 * @param name parameter name
 * @param description parameter description
 * @param value parameter value
 * @param minValue parameter minimum value
 * @param maxValue parameter maximum value
 * @param stepValue parameter step value
 * @param stepMode parameter step value mode (additive or
 * multiplicative)
 * @param descriptions parameter values descriptions
 * @param ptr smart pointer to an algorithm in order to change its
 * parameter value
 */
CvAlgoParam::CvAlgoParam(const string & name,
						 const string & description,
						 const int & value,
						 const int & minValue,
						 const int & maxValue,
						 const int & stepValue,
						 const StepMode stepMode,
						 const vector<string> & descriptions) :
	name(name),
	type(INT),
	description(description),
	stepMode(stepMode),
	hasDefaultValue(false),
	valueDescriptions(descriptions),
	parseError(false),
	parsingCompleted(true),
	gettable(false),
	settable(false),
	boolGetter(NULL),
	boolSetter(NULL),
	intGetter(NULL),
	intSetter(NULL),
	doubleGetter(NULL),
	doubleSetter(NULL)
{
	this->value.intValue = value;
	this->minValue.intValue = minValue;
	this->maxValue.intValue = maxValue;
	this->stepValue.intValue = stepValue;
}

/*
 * Constructor for an double parameter
 * @param name parameter name
 * @param description parameter description
 * @param value parameter value
 * @param minValue parameter minimum value
 * @param maxValue parameter maximum value
 * @param stepValue parameter step value
 * @param stepMode parameter step value mode (additive or
 * multiplicative)
 * @param ptr smart pointer to an algorithm in order to change its
 * parameter value
 */
CvAlgoParam::CvAlgoParam(const string & name,
						 const string & description,
						 const double & value,
						 const double & minValue,
						 const double & maxValue,
						 const double & stepValue,
						 const StepMode stepMode) :
	name(name),
	type(REAL),
	description(description),
	stepMode(stepMode),
	hasDefaultValue(false),
	valueDescriptions(),
	parseError(false),
	parsingCompleted(true),
	gettable(false),
	settable(false),
	boolGetter(NULL),
	boolSetter(NULL),
	intGetter(NULL),
	intSetter(NULL),
	doubleGetter(NULL),
	doubleSetter(NULL)
{
	this->value.doubleValue = value;
	this->minValue.doubleValue = minValue;
	this->maxValue.doubleValue = maxValue;
	this->stepValue.doubleValue = stepValue;
}

/*
 * Constructor from a line extracted from a CSV file where each element
 * is separated by a semicolon
 * @param line
 * @param ptr smart pointer to an algorithm in order to change its
 * parameter value
 */
CvAlgoParam::CvAlgoParam(const string & line) :
	name(""),
	description(""),
	hasDefaultValue(false), // Not yet but will have in the parsing below
	parseError(false),
	parsingCompleted(false),
	gettable(false),
	settable(false),
	boolGetter(NULL),
	boolSetter(NULL),
	intGetter(NULL),
	intSetter(NULL),
	doubleGetter(NULL),
	doubleSetter(NULL)
{
	istringstream lineStream(line);
	string tag;
	string algoName;
	size_t nbValuesDescriptionRead = 0;
	size_t step = (size_t)ALGONAME_STEP;
	size_t nbValuesDescriptionMax = CvAlgoParam::nbValueDescriptionsMax;

	while (lineStream.good() && !parseError && step < (size_t)NBSTEPS)
	{
		getline(lineStream, tag, sep); // read a string until next semicolon

		// clog << "read tag : " << tag << endl;

		if (tag.length() == 0)
		{
			// parseError = true; // no : empty tags appends all the time
			// cerr << "Empty tag" << endl;
			break;
		}
		else // tag.length != 0
		{
			switch((TagStep)step)
			{
				case ALGONAME_STEP:
					algoName = tag;
					step++;
					break;
				case PARAMNAME_STEP:
					name = tag;
					step++;
					break;
				case PARAMTYPE_STEP:
					if (tag == "boolean")
					{
						type = BOOLEAN;
						step++;
					}
					else if (tag == "integer")
					{
						type = INT;
						step++;
					}
					else if (tag == "double")
					{
						type = REAL;
						step++;
					}
					else
					{
						cerr << "Unknown param type: " << tag << endl;
						parseError = true;
					}
					break;
				case PARAMDESCRIPTION_STEP:
					description = tag;
					step++;
					break;
				case VALUE_STEP:
				case MINVALUE_STEP:
				case MAXVALUE_STEP:
				case STEPVALUE_STEP:
				{
					istringstream tagStream(tag); // local stream

					switch(type)
					{
						case BOOLEAN:
							if (step == (size_t)VALUE_STEP)
							{
								if (tag == "true")
								{
									value.boolValue = true;
								}
								else if (tag == "false")
								{
									value.boolValue = false;
								}
								else
								{
									cerr << "Unknown boolean value: "
										<< tag << endl;
									parseError = true;
								}
								if (!parseError)
								{
									// automatically set default, min, max & step
									// values and jump to end
									defaultValue = value;
									minValue.boolValue = false;
									maxValue.boolValue = true;
									stepValue.boolValue = true;
									stepMode = ADD;
									step = (size_t)NBSTEPS;
								}
							}
							break;
						case INT:
						{
							switch((size_t)step)
							{
								case VALUE_STEP:
									tagStream >> value.intValue;
									break;
								case MINVALUE_STEP:
									tagStream >> minValue.intValue;
									break;
								case MAXVALUE_STEP:
									tagStream >> maxValue.intValue;
									break;
								case STEPVALUE_STEP:
									tagStream >> stepValue.intValue;
									break;
							}

							if (tagStream.fail())
							{
								cerr << "Failed to read integer value: "
									<< tag << endl;
								parseError = true;
							}
							else
							{
								if ((TagStep)step == VALUE_STEP)
								{
									// also setup default value
									defaultValue = value;
									hasDefaultValue = true;
								}

								step++;
							}
							break;
						}
						case REAL:
						{
							switch((size_t)step)
							{
								case VALUE_STEP:
									tagStream >> value.doubleValue;
									break;
								case MINVALUE_STEP:
									tagStream >> minValue.doubleValue;
									break;
								case MAXVALUE_STEP:
									tagStream >> maxValue.doubleValue;
									break;
								case STEPVALUE_STEP:
									tagStream >> stepValue.doubleValue;
									break;
							}
							if (tagStream.fail())
							{
								cerr << "Failed to read double value: "
									<< tag << endl;
								parseError = true;
							}
							else
							{
								if ((TagStep)step == VALUE_STEP)
								{
									// also setup default value
									defaultValue = value;
									hasDefaultValue = true;
								}

								step++;
							}
							break;
						}
						case UNKNOWN: // This should not happend
						default:
							parseError = true;
							break;
					}
					break;
				}
				case STEPMODE_STEP:
					if (tag == "ADD")
					{
						stepMode = ADD;

						if (type == INT &&
							stepValue.intValue == 1)
						{
							nbValuesDescriptionMax =
								maxValue.intValue -
								minValue.intValue + 1;

							// clog << "number of ADD values = "
							//     << nbValuesDescriptionMax << endl;

							if (nbValuesDescriptionMax <=
								CvAlgoParam::nbValueDescriptionsMax)
							{
								step++;
							}
							else
							{
								step = NBSTEPS;
							}
						}
						else
						{
							step = NBSTEPS;
						}
					}
					else if (tag == "MUL")
					{
						stepMode = MUL;

						if (type == INT)
						{
							if (minValue.intValue != 0)
							{
								int range = maxValue.intValue /
											minValue.intValue;

								if (range %
									stepValue.intValue == 0)
								{
									nbValuesDescriptionMax = 0;
									while (range >= 1)
									{
										range /= stepValue.intValue;
										nbValuesDescriptionMax++;
									}
									// clog << "number of MUL values = "
									//      << nbValuesDescriptionMax << endl;
								}

								if (nbValuesDescriptionMax <=
									CvAlgoParam::nbValueDescriptionsMax)
								{
									step++;
								}
								else
								{
									step = NBSTEPS;
								}
							}
							else
							{
								step = NBSTEPS;
							}
						}
						else
						{
							step = NBSTEPS;
						}
					}
					else
					{
						cerr << "Unkown step mode: " << tag << endl;
						parseError = true;
					}
					break;
				case VALUEDESCRIPTION_STEP:
					if (type == INT &&
						nbValuesDescriptionRead < nbValuesDescriptionMax)
					{
						valueDescriptions.push_back(tag);
						nbValuesDescriptionRead++;
					}
					if (nbValuesDescriptionRead >= nbValuesDescriptionMax)
					{
						step++;
					}
					break;
				case NBSTEPS:
					// Parsing completed
					// clog << "Parsing completed" << endl;
					parsingCompleted = true;
					break;
			} // end of switch(step)
		} // end of tag.length != 0

		if (parseError)
		{
			// something was wrong in this parameter, better remove it
			cerr << "Parse error at step <";
			switch((TagStep)step)
			{
				case ALGONAME_STEP:
					cerr << "Algorithm Name";
					break;
				case PARAMNAME_STEP:
					cerr << "Parameter name";
					break;
				case PARAMTYPE_STEP:
					cerr << "Parameter type";
					break;
				case PARAMDESCRIPTION_STEP:
					cerr << "Parameter description";
					break;
				case VALUE_STEP:
					cerr << "Parameter value";
					break;
				case MINVALUE_STEP:
					cerr << "Parameter min value";
					break;
				case MAXVALUE_STEP:
					cerr << "Parameter max value";
					break;
				case STEPVALUE_STEP:
					cerr << "Parameter step value";
					break;
				case STEPMODE_STEP:
					cerr << "Parameter step value mode";
					break;
				case VALUEDESCRIPTION_STEP:
					cerr << "Parameter values description";
					break;
				case NBSTEPS:
					break;
			}
		} // end of if (parseError)

		if (step == NBSTEPS)
		{
			parsingCompleted = true;
		}
	}
}

/*
 * Destructor
 */
CvAlgoParam::~CvAlgoParam()
{
	name.clear();
	description.clear();
	valueDescriptions.erase(valueDescriptions.begin(), valueDescriptions.end());

	removeAllAlgorithms();
}

/*
 * Parameter name accessor
 * @return the parameter's name
 */
string CvAlgoParam::getName() const
{
	return name;
}

/*
 * Get the parameter type
 * @return the parameter type
 */
CvAlgoParam::ParamType CvAlgoParam::getType() const
{
	return type;
}

/*
 * Parameter's description accessor
 * @return the parameter's description
 */
string CvAlgoParam::getDescription() const
{
	return description;
}

/*
 * Get the boolean value of this parameter
 * @param which the value to return :
 * 	- the value itself : VALUE
 * 	- the minimum value : MINVALUE
 * 	- the maximum value : MAXVALUE
 * 	- the step value : STEPVALUE
 *	- the default value : DEFAULTVALUE
 * @return the boolean value of this parameter
 */
bool CvAlgoParam::getBoolValue(const CvAlgoParam::WhichValue which) const
{
	if (type == BOOLEAN)
	{
		bool returnValue;
		switch(which)
		{
			case MINVALUE:
				returnValue = minValue.boolValue;
				break;
			case MAXVALUE:
				returnValue = maxValue.boolValue;
				break;
			case STEPVALUE:
				returnValue = stepValue.boolValue;
				break;
			case DEFAULTVALUE:
				if (hasDefaultValue)
				{
					returnValue = defaultValue.boolValue;
				}
				else
				{
					returnValue = value.boolValue;
				}
				break;
			case ACTUALVALUE:
				if (!algorithms.empty() && boolGetter != NULL)
				{
					// Gets first algo
					const Feature2D * algo = (algorithms.begin())->get();
					if (boolGetter != NULL)
					{
						returnValue = (algo->*boolGetter)();
					}
					else
					{
						cerr << name << ".getBoolValue() impossible : no getter"
							 << endl;
						returnValue = value.boolValue;
					}
				}
				else
				{
					returnValue = value.boolValue;
				}
				break;
			case VALUE:
			default:
				returnValue = value.boolValue;
				break;
		}

		// cout << name << ".getBoolValue(" << (returnValue ? "true" : "false")
		// 	 << ")" << endl;

		return returnValue;
	}
	else
	{
		cerr << name << ".getBoolValue() is not of type BOOLEAN" << endl;
		return false;
	}
}

/*
 * Get the integer value of this parameter
 * @param which the value to return :
 * 	- the value itself : VALUE
 * 	- the minimum value : MINVALUE
 * 	- the maximum value : MAXVALUE
 * 	- the step value : STEPVALUE
 *	- the default value : DEFAULTVALUE
 * @return the integer value of this parameter
 */
int CvAlgoParam::getIntValue(const CvAlgoParam::WhichValue which) const
{
	if (type == INT)
	{
		int returnValue;
		switch(which)
		{
			case MINVALUE:
				returnValue = minValue.intValue;
				break;
			case MAXVALUE:
				returnValue = maxValue.intValue;
				break;
			case STEPVALUE:
				returnValue = stepValue.intValue;
				break;
			case DEFAULTVALUE:
				if (hasDefaultValue)
				{
					returnValue = defaultValue.intValue;
				}
				else
				{
					returnValue = value.intValue;
				}
				break;
			case ACTUALVALUE:
				if (!algorithms.empty() && intGetter != NULL)
				{
					Feature2D * algo = algorithms.begin()->get();
					if (intGetter != NULL)
					{
						returnValue = (algo->*intGetter)();
					}
					else
					{
						cerr << name << ".getIntValue() impossible : no getter" << endl;
						returnValue = value.intValue;
					}
				}
				else
				{
					returnValue = value.intValue;
				}
				break;
			case VALUE:
			default:
				returnValue = value.intValue;
				break;
		}
		// cout << name << ".getIntValue() = " << returnValue << endl;
		return returnValue;
	}
	else
	{
		cerr << name << ".getIntValue() is not of type INT" << endl;
		return 0;
	}
}
/*
 * Get int value from index in enumerable parameter
 * @param index the index
 * @return the integer value corresponding to this index
 */
int CvAlgoParam::getIntValueFromIndex(const size_t index) const
{
	size_t localIndex = index;
	if (localIndex >= valueDescriptions.size())
	{
		localIndex = valueDescriptions.size() - 1;
	}
	int indexValue = minValue.intValue;
	for(size_t i = 0; i < localIndex; i++)
	{
		switch(stepMode)
		{
			case ADD:
				indexValue+= stepValue.intValue;
				break;
			case MUL:
				indexValue*= stepValue.intValue;
				break;
		}
	}
	// cout << name << ".getIntValueFromIndex(" << index << ") = " << indexValue << endl;
	return indexValue;
}

/*
 * Get the index corresponding to the value if this parameter is an
 * enumerable parameter (according to #isEnum method)
 * @param which the index of the value to return :
 * 	- the value itself : VALUE
 * 	- the minimum value : MINVALUE
 * 	- the maximum value : MAXVALUE
 *	- the default value : DEFAULTVALUE
 * @note Note that STEPVALUE is not considered since it make no sense
 * to find the index of the stepValue (if this case occurs the returned
 * index will be the value index, not the stepValue index).
 * @return The index corresponding to the current value if this
 * parameter is an enumerable parameter (according to #isEnum method)
 * or -1 if this parameter is not enumerable
 */
int CvAlgoParam::getValueIndex(const WhichValue which) const
{
	if (isEnum())
	{
		int whichValue;
		switch (which)
		{
			case MINVALUE:
				whichValue = minValue.intValue;
				break;
			case MAXVALUE:
				whichValue = maxValue.intValue;
				break;
			case DEFAULTVALUE:
				whichValue = defaultValue.intValue;
				break;
			case VALUE:
			default:
				whichValue = value.intValue;
				break;
		}

		int index = 0;
		int indexValue = minValue.intValue;
		switch (stepMode)
		{
			case MUL:
				while (indexValue < whichValue)
				{
					indexValue *= stepValue.intValue;
					index++;
				}
				break;
			case ADD:
			default:
				while (indexValue < whichValue)
				{
					indexValue += stepValue.intValue;
					index++;
				}
				break;
		}

		// cout << name << ".getValueIndex() = " << index << endl;
		return index;
	}
	else
	{
		cerr << name << ".getValueIndex() on NON Enum parameter" << endl;
		return -1;
	}
}

/*
 * Get the double value of this parameter
 * @param which the value to return :
 * 	- the value itself [Default]
 * 	- the minimum value
 * 	- the maximum value
 * 	- the step value
 * @return the double value of this parameter
 */
double CvAlgoParam::getDoubleValue(const CvAlgoParam::WhichValue which) const
{
	if (type == REAL)
	{
		double returnValue;
		switch(which)
		{
			case MINVALUE:
				returnValue = minValue.doubleValue;
				break;
			case MAXVALUE:
				returnValue =  maxValue.doubleValue;
				break;
			case STEPVALUE:
				returnValue =  stepValue.doubleValue;
				break;
			case DEFAULTVALUE:
				if (hasDefaultValue)
				{
					returnValue = defaultValue.doubleValue;
				}
				else
				{
					returnValue = value.doubleValue;
				}
				break;
			case ACTUALVALUE:
				if (!algorithms.empty() && doubleGetter != NULL)
				{
					Feature2D * algo = algorithms.begin()->get();
					if (doubleGetter != NULL)
					{
						returnValue = (algo->*doubleGetter)();
					}
					else
					{
						cerr << name << ".getDoubleValue() : impossible : no getter" << endl;
						returnValue = value.doubleValue;
					}
				}
				else
				{
					returnValue = value.doubleValue;
				}
				break;
			case VALUE:
			default:
				returnValue =  value.doubleValue;
				break;
		}

		// cout << name << ".getDoubleValue() = " << returnValue << endl;
		return returnValue;
	}
	else
	{
		cerr << name << ".getDoubleValue() on NON Double parameter" << endl;
		return 0.0;
	}
}

/*
 * Get the step mode between values
 * @return the step mode
 */
CvAlgoParam::StepMode CvAlgoParam::getStepMode() const
{
	return stepMode;
}

/*
 * Set a new boolean value for this parameter iff this parameter is a
 * boolean parameter, otherwise the parameter value is not set
 * @param value the new boolean value for this parameter
 * @param setDefault indicates if we are setting the current value or
 * the current value AND the default value (when setting the default
 * value the #hasDefaultValue becoms true).
 * @return true if the new boolean value has been set on this parameter
 */
bool CvAlgoParam::setBoolValue(const bool value, const bool setDefault)
{
	if (type == BOOLEAN)
	{
		this->value.boolValue = value;
		if (setDefault)
		{
			this->defaultValue.boolValue = value;
			hasDefaultValue = true;
		}

		if (boolSetter != NULL)
		{
			for (set<Ptr<Feature2D> >::iterator it = algorithms.begin();
				 it != algorithms.end(); ++it)
			{
				Feature2D * algo = it->get();
				(algo->*boolSetter)(this->value.boolValue);
			}
		}
		else
		{
			cerr << name << ".setBoolValue(" << (value ? "true" : "false")
				 << ") impossible : no setter" << endl;
		}

		// cout << name << ".setBoolValue(" << (value ? "true" : "false") <<")"<< endl;
		return true;
	}
	else
	{
		cerr << name << ".setBoolValue(...) on non Boolean parameter" << endl;
	}

	return false;
}

/*
 * Set a new integer value for this parameter iff this parameter is a
 * integer parameter, otherwise the parameter value is not set
 * @param value the new integer value for this parameter
 * @param setDefault indicates if we are setting the current value or
 * the current value AND the default value (when setting the default
 * value the #hasDefaultValue becoms true).
 * @return true if the new integer value has been set on this parameter
 */
bool CvAlgoParam::setIntValue(const int value, const bool setDefault)
{
	if (type == INT)
	{
		if (value >= minValue.intValue && value <= maxValue.intValue)
		{
			this->value.intValue = value;
			if (setDefault)
			{
				defaultValue.intValue = value;
				hasDefaultValue = true;
			}
			if (intSetter != NULL)
			{
				for (set<Ptr<Feature2D> >::iterator it = algorithms.begin();
					 it != algorithms.end(); ++it)
				{
					Feature2D * algo = it->get();
					(algo->*intSetter)(this->value.intValue);
				}
			}
			else
			{
				cerr << name << ".setIntValue(" << value
					 << ") impossible : no setter" << endl;
			}

			// cout << name << ".setIntValue(" << value <<")"<< endl;
			return true;
		}
		else
		{
			cerr << name << ".setIntValue(" << value << ") outside range["
				 << minValue.intValue << ".." << maxValue.intValue
				 << "] Cancelled" << endl;
		}
	}
	else
	{
		cerr << name << ".setIntValue(...) on NON Int parameter" << endl;
	}

	return false;
}

/*
 * Set a new integer value for this parameter from a new index in
 * enumerated values iff this parameter is a integer parameter
 * and also an enumerable parameter, otherwise the parameter value
 * is not set.
 * @param index the index in enumerated values to set the actual value
 * @param setDefault indicates if we are setting the current value or
 * the current value AND the default value (when setting the default
 * value the #hasDefaultValue becomes true).
 * @return true if the new integer value has been set on this parameter
 * from the index (when it's valid), and false otherwise
 */
bool CvAlgoParam::setIndexValue(const int index, const bool setDefault)
{

	if (index >= 0 && index < (int)valueDescriptions.size())
	{
		int intValue = minValue.intValue;
		switch (stepMode)
		{
			case ADD:
				for (int i = 0; i < index; i++)
				{
					intValue += stepValue.intValue;
				}
				break;
			case MUL:
				for (int i = 0; i < index; i++)
				{
					intValue *= stepValue.intValue;
				}
				break;
			default:
				cerr << name << ".setIndexValue(" << index << ") unknown stepMode"
					 << endl;
				return false;
		}

		// cout << name << ".setIndexValue(" << index << ")" << endl;
		return CvAlgoParam::setIntValue(intValue, setDefault);
	}
	else
	{
		cerr << name << ".setIndexValue(" << index << ") outside range[0.."
			 << valueDescriptions.size() - 1 << "] Cancelled" << endl;
	}

	return false;
}


/*
 * Set a new double value for this parameter iff this parameter is a
 * double parameter, otherwise the parameter value is not set
 * @param value the new double value for this parameter
 * @return true if the new double value has been set on this parameter
 */
bool CvAlgoParam::setDoubleValue(const double value, const bool setDefault)
{
	if (type == REAL)
	{
		if (value >= minValue.doubleValue && value <= maxValue.doubleValue)
		{
			this->value.doubleValue = value;
			if (setDefault)
			{
				defaultValue.doubleValue = value;
				hasDefaultValue = true;
			}

			if (doubleSetter != NULL)
			{
				for (set<Ptr<Feature2D> >::iterator it = algorithms.begin();
					 it != algorithms.end();
					 ++it)
				{
					Feature2D * algo = it->get();
					(algo->*doubleSetter)(this->value.doubleValue);
				}
			}
			else
			{
				cerr << name << ".setDoubleValue(" << value
					 << ") impossible : no setter" << endl;
			}

			// cout << name << ".setDoubleValue(" << value << ")" << endl;
			return true;
		}
		else
		{
			cerr << name << ".setDoubleValue(" << value << ") outside range["
				 << minValue.doubleValue << ".." << maxValue.doubleValue
				 << "] Cancelled" << endl;
		}
	}
	else
	{
		cerr << name << ".setDoubleValue(...) on NON Double parameter" << endl;
	}

	return false;
}

/*
 * Reset the current value to default value
 * @return true if this parameter has a default value and has been reset
 * to this default value, false otherwise;
 */
bool CvAlgoParam::resetToDefaultValue()
{
	if (hasDefaultValue)
	{
		/*
		 * Note: We need to use CvAlgoParam::setXXXValue instead of just
		 * setting value.XXXValue to defaultvalue.XXXValue because
		 * setXXXValue also sets this value in all associated Algorithms
		 * which is what we want here.
		 * using CvAlgoParam::setXXXValue also prevent dynamic link to
		 * subclasses setXXXValue (and avoid deadlocks as resetToDefaultValue()
		 * as well as setXXXValue might both require to lock the same mutex)
		 */
		switch(type)
		{
			case BOOLEAN:
				CvAlgoParam::setBoolValue(defaultValue.boolValue);
				break;
			case INT:
				CvAlgoParam::setIntValue(defaultValue.intValue);
				break;
			case REAL:
				CvAlgoParam::setDoubleValue(defaultValue.doubleValue);
				break;
			default:
				cerr << "CvAlgoParam::resetToDefaultValue() : unknown type";
				return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Adds an algorithm and if the algorithm contains a parameter of this
 * name then add it to the list of algorithms linked to this parameter
 * @param ptr the algorithm smart pointer
 * @return true if algorithm have been added (iff it containts a
 * parameter matching this parameter), false otherwise.
 */
bool CvAlgoParam::addAlgorithm(const Ptr<Feature2D> & ptr)
{
	if (!ptr.empty())
	{
		/*
		 * insert this algorithm in the algo set (if it is not here
		 * already : set does not contains duplicates)
		 */
		pair<set<Ptr<Feature2D> >::iterator, bool> resultPair = algorithms.insert(ptr);

		if (resultPair.second) // Algo has been added
		{
			/*
			 * If this algorithm is the first one we should either get
			 * its value or set its value depending on the updateFrom
			 * argument
			 */
			if (algorithms.size() == 1)
			{
				// Sets appropriate getters and setters
				gettable = setGetterFrom(ptr);
				settable = setSetterFrom(ptr);
				if (settable && gettable)
				{
					switch (type)
					{
						case BOOLEAN:
							CvAlgoParam::setBoolValue(CvAlgoParam::getBoolValue(ACTUALVALUE), true);
							break;
						case INT:
							CvAlgoParam::setIntValue(CvAlgoParam::getIntValue(ACTUALVALUE), true);
							break;
						case REAL:
							CvAlgoParam::setDoubleValue(CvAlgoParam::getDoubleValue(ACTUALVALUE), true);
							break;
						default:
							break;
					}

				}
			}
			else
			{
				/*
				 * This algorithm is NOT the first one associated with
				 * this parameter so we should set the algorithm with
				 * the current value of the parameter
				 */
				syncValueInAlgorithms();
			}
			return true;
		}
	}
	else
	{
		cerr << "CvAlgoParam::addAlgorithm(empty algorithm)" << endl;
	}

	return false;
}

/*
 * Remove an algorithm from the list of algorithms linked to this
 * parameter
 * @param ptr the algorithm smart pointer to remove
 * @return true if the algorithm smart pointer have been removed from
 * the list of related algorithms
 */
bool CvAlgoParam::removeAlgorithm(const Ptr<Feature2D> & ptr)
{
	set<Ptr<Feature2D> >::iterator pos = algorithms.find(ptr);
	if (pos != algorithms.end())
	{
		Ptr<Feature2D> localPtr = *pos;
		localPtr.release();
		algorithms.erase(pos);
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Synchronise current value in all algorithms linked to this parameter
 * @note only used in #addAlgorithm(const Ptr<Feature2D> &)
 */
void CvAlgoParam::syncValueInAlgorithms()
{
	if (settable)
	{
		for (set<Ptr<Feature2D> >::iterator it = algorithms.begin();
			 it != algorithms.end(); ++it)
		{
			Feature2D * algo = it->get();
			if (algo != NULL)
			{
				switch(type)
				{
					case BOOLEAN:
						// algo->set(name, value.boolValue);
						// boolSetter(algo, value.boolValue);
						(algo->*boolSetter)(value.boolValue);
						break;
					case INT:
						// algo->set(name, value.intValue);
						// intSetter(algo, value.intValue);
						(algo->*intSetter)(value.intValue);
						break;
					case REAL:
						// algo->set(name, value.doubleValue);
						// doubleSetter(algo, value.doubleValue);
						(algo->*doubleSetter)(value.doubleValue);
						break;
					default:
						break;
				}
			}
		}
	}
}

/*
 * Remove all associated algorithms
 */
void CvAlgoParam::removeAllAlgorithms()
{
	for (set<Ptr<Feature2D> >::iterator it = algorithms.begin();
		 it != algorithms.end(); ++it)
	{
		Ptr<Feature2D> ptr = *it;
		ptr.release();
	}

	algorithms.clear();
}

/*
 * Is this parameter an enum
 * @return true if the number of possible values is less than
 * #nbValueDescriptionsMax and each possible value has a corresponding
 * description
 */
bool CvAlgoParam::isEnum() const
{
	size_t nbValuesDescriptionSize = valueDescriptions.size();
	int nbValuesDescription = 0;

	if (type == INT)
	{
		if (stepMode == ADD)
		{
			if (stepValue.intValue == 1)
			{
				nbValuesDescription = maxValue.intValue - minValue.intValue + 1;
			}
		}
		else if (stepMode == MUL)
		{
			if (minValue.intValue != 0)
			{
				int range = maxValue.intValue / minValue.intValue;
				if (range % stepValue.intValue == 0)
				{
					while (range >= 1)
					{
						range /= stepValue.intValue;
						nbValuesDescription++;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		return (nbValuesDescriptionSize > 0) &&
			   ((int)nbValuesDescriptionSize == nbValuesDescription);
	}
	else
	{
		return false;
	}
}

/*
 * Is this parameter a constant
 * @return true if this parameter has a stepValue equivalent to zero
 * and/or if min & max value are the same
 */
bool CvAlgoParam::isConstant() const
{
	switch(type)
	{
		case BOOLEAN:
			return minValue.boolValue == value.boolValue &&
				   maxValue.boolValue == value.boolValue;
		case INT:
			return maxValue.intValue == minValue.intValue &&
				   minValue.intValue == value.intValue &&
				   stepValue.intValue == 0;
		case REAL:
			return maxValue.doubleValue == minValue.doubleValue &&
				   minValue.doubleValue == value.doubleValue &&
				   stepValue.doubleValue == 0.0;
		default:
			return false;
	}
}

/*
 * Is this parameter ok: Used when parameter is constructed from parsing
 * a text line to indicates it has no parsing error
 */
bool CvAlgoParam::isOk() const
{
	return !parseError && parsingCompleted;
}

/*
 * Is this parameter value obtainable from an actual algorithm ?
 * @return true if the value is gettable from an actual algorithm,
 * false otherwise
 */
bool CvAlgoParam::isGettable() const
{
	return gettable;
}

/*
 * Can we set this value in an actual algorithm ?
 * @return true if the value is settable into an actual algorithm,
 * false otherwise
 */
bool CvAlgoParam::isSettable() const
{
	return settable;
}

/*
 * Get all possible values descriptions.
 * @note the number of possible values is always < #nbValueDescriptionsMax
 * @return a vector constaining all possible values descriptions if
 * this parameter is an enum (according to #isEnum()) or an empty
 * vector if this parameter has no values descriptions
 */
vector<string> CvAlgoParam::getValueDescriptions() const
{
	return valueDescriptions;
}

/*
 * Value description for value value (if it exists)
 * @param value the value for which we request a description
 * @return the description corresponding tho the value or an empty
 * string if there is no description for this value.
 */
string CvAlgoParam::getDescription(const int value) const
{
	int index = indexOf(value);
	if (index != -1)
	{
		return valueDescriptions[index];
	}
	else
	{
		return string();
	}
}

/*
 * Set of algorithm pointers associated with this parameter
 * @return a set of cosntant Algorithm pointers associated with this
 * parameter
 */
set<const Feature2D *> CvAlgoParam::getAlgorithmsPtr() const
{
	set<const Feature2D *> pset;

	if (!algorithms.empty())
	{
		for (set<Ptr<Feature2D> >::const_iterator it = algorithms.cbegin();
			 it != algorithms.cend(); ++it)
		{
			pset.insert(it->get());
		}
	}

	return pset;
}


/*
 * index of this value in the values descriptions
 * @param value the value that we are searching for its index
 * @return the index of this value in the descriptions or -1
 * if there is no description for this value.
 */
int CvAlgoParam::indexOf(const int value) const
{
	if (isEnum() &&
		value >= minValue.intValue &&
		value <= maxValue.intValue)
	{
		int index = 0;
		int indexValue = minValue.intValue;
		switch (stepMode)
		{
			case ADD:
				while (indexValue < value)
				{
					indexValue += stepValue.intValue;
					index++;
				}
				break;
			case MUL:
				while (indexValue < value)
				{
					indexValue *= stepValue.intValue;
					index++;
				}
				break;
			default:
				break;
		}
		if (index <= (int)valueDescriptions.size() - 1)
		{
			return index;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

/*
 * Comparison operator
 * @param param the parameter to compare
 * @return true param contains exactly the same values as in this
 * parameter
 */
bool CvAlgoParam::operator ==(const CvAlgoParam & param) const
{
	bool result = true;

	result &= (name == param.name);
	result &= (type == param.type);

	switch(type)
	{
		case BOOLEAN:
			result &= (minValue.boolValue == param.minValue.boolValue);
			result &= (maxValue.boolValue == param.maxValue.boolValue);
			break;
		case INT:
			result &= (minValue.intValue == param.minValue.intValue);
			result &= (maxValue.intValue == param.maxValue.intValue);
			break;
		case REAL:
			result &= (minValue.doubleValue == param.minValue.doubleValue);
			result &= (maxValue.doubleValue == param.maxValue.doubleValue);
			break;
		default:
			result &= false;
			break;
	}

	return result;
}

/*
 * Copy operator
 * @param param the parameter to copy
 * @return a reference to this parameter
 */
CvAlgoParam & CvAlgoParam::operator =(const CvAlgoParam & param)
{
	removeAllAlgorithms();

	name = param.name;
	type = param.type;
	description = param.description;
	value = param.value;
	minValue = param.minValue;
	maxValue = param.maxValue;
	stepValue = param.stepValue;
	stepMode = param.stepMode;
	valueDescriptions = param.valueDescriptions;
	parseError = param.parseError;
	parsingCompleted = param.parsingCompleted;
	gettable = param.gettable;
	settable = param.settable;
	boolGetter = param.boolGetter;
	boolSetter = param.boolSetter;
	intGetter = param.intGetter;
	intSetter = param.intSetter;
	doubleGetter = param.doubleGetter;
	doubleSetter = param.doubleSetter;
	algorithms = param.algorithms;

	return *this;
}

/*
 * Friend output operatpr
 * @param out the output stream
 * @param p the parameter to print on the output stream
 * @return a reference to the output stream
 */
ostream & operator <<(ostream & out, const CvAlgoParam & p)
{
	out << "(";
	if (p.gettable)
	{
		out << "r";
	}
	if (p.settable)
	{
		out << "w";
	}
	if (p.isOk())
	{
		out << "x";
	}
	out << ") ";
	switch(p.type)
	{
		case CvAlgoParam::BOOLEAN:
			out << p.name << " [boolean] = "
				<< (p.value.boolValue ? "true" : "false");
			if (p.isConstant())
			{
				out << " (constant)";
			}
			break;
		case CvAlgoParam::INT:
			out << p.name << " [integer] = "
				<< p.value.intValue;
			if (!p.isConstant())
			{
				out << " [" << p.minValue.intValue
					<< ".." << p.maxValue.intValue << "]"
					<< (p.stepMode == CvAlgoParam::ADD ? "+" : "*")
					<< "[" << p.stepValue.intValue << "]";
			}
			else
			{
				out << " (Constant)";
			}
			if (p.isEnum())
			{
				out << " {";
				for (vector<string>::const_iterator it =
					 p.valueDescriptions.begin();
					 it != p.valueDescriptions.end(); ++it)
				{
					out << " " << *it;
				}
				out  << "}";
			}
			break;
		case CvAlgoParam::REAL:
			out << p.name << " [real] = "
				<< p.value.doubleValue;
			if (!p.isConstant())
			{
				out << " [" << p.minValue.doubleValue
					<< ".." << p.maxValue.doubleValue << "]"
					<< (p.stepMode == CvAlgoParam::ADD ? "+" : "*")
					<< "[" << p.stepValue.doubleValue << "]";
			}
			else
			{
				out << " (Constant)";
			}
			break;
		case CvAlgoParam::UNKNOWN:
			out << p.name << "[unknown]";
			break;
	}
	out << endl << "\t" << p.description << endl;
	if (!p.algorithms.empty())
	{
		out << "\t algorithms = {";
		for (set<Ptr<Feature2D> >::const_iterator it = p.algorithms.begin();
			 it != p.algorithms.end(); ++it)
		{
			const Ptr<Feature2D> algoPtr = *it;
			out << " " << algoPtr.get();
		}
		out << "}" << endl;
	}

	return out;
}

/*
 * Sets the appropriate getter according to the type Feature2D in ptr
 * @param ptr the algorithm smart pointer
 * @return true if the appropriate getter has been set, false otherwise
 */
bool CvAlgoParam::setGetterFrom(const Ptr<Feature2D> & ptr)
{
	if (!ptr.empty())
	{
		// Get actual pointer to Feature
		const Feature2D * algoPtr = ptr.get();

		clog << "CvAlgoParam::setGetterFrom(" << typeid(*algoPtr).name() << ")" << endl;

		if (dynamic_cast<const AgastFeatureDetector *>(algoPtr) != NULL)
		{
			if (name =="nonmaxSuppression" && type == BOOLEAN)
			{
				boolGetter = reinterpret_cast<BoolGetter>(&AgastFeatureDetector::getNonmaxSuppression);
				return true;
			}
			if (name =="threshold" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&AgastFeatureDetector::getThreshold);
				return true;
			}
			if (name =="type" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&AgastFeatureDetector::getType);
				return true;
			}
		}
		if (dynamic_cast<const AKAZE *>(algoPtr) != NULL)
		{
			if (name == "descriptor_channels" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&AKAZE::getDescriptorChannels);
				return true;
			}
			if (name == "descriptor_size" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&AKAZE::getDescriptorSize);
				return true;
			}
			if (name == "descriptor_type" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&AKAZE::getDescriptorType);
				return true;
			}
			if (name == "diffusivity" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&AKAZE::getDiffusivity);
				return true;
			}
			if (name =="nOctaveLayers" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&AKAZE::getNOctaveLayers);
				return true;
			}
			if (name =="nOctaves" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&AKAZE::getNOctaves);
				return true;
			}
			if (name =="threshold" && type == REAL)
			{
				doubleGetter = reinterpret_cast<DoubleGetter>(&AKAZE::getThreshold);
				return true;
			}
		}
		if (dynamic_cast<const BRISK *>(algoPtr) != NULL)
		{
			if (name =="octaves" && type == INT)
			{
				/*
				 * there is an octave parameter in the constructor bu no accessor
				 * to it
				 */
				return false;
			}
			if (name =="thres" && type == INT)
			{
				/*
				 * there is a thres parameter in the constructor bu no accessor
				 * to it
				 */
				return false;
			}
		}
		if (dynamic_cast<const FastFeatureDetector *>(algoPtr) != NULL)
		{
			if (name =="nonmaxSuppression" && type == BOOLEAN)
			{
				boolGetter = reinterpret_cast<BoolGetter>(&FastFeatureDetector::getNonmaxSuppression);
				return true;
			}
			if (name =="threshold" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&FastFeatureDetector::getThreshold);
				return true;
			}
			if (name =="type" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&FastFeatureDetector::getType);
				return true;
			}
		}
		if (dynamic_cast<const GFTTDetector *>(algoPtr) != NULL)
		{
			if (name =="blockSize" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&GFTTDetector::getBlockSize);
				return true;
			}
			if (name =="k" && type == REAL)
			{
				doubleGetter = reinterpret_cast<DoubleGetter>(&GFTTDetector::getK);
				return true;
			}
			if (name =="minDistance" && type == REAL)
			{
				doubleGetter = reinterpret_cast<DoubleGetter>(&GFTTDetector::getMinDistance);
				return true;
			}
			if (name =="nfeatures" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&GFTTDetector::getMaxFeatures);
				return true;
			}
			if (name =="qualityLevel" && type == REAL)
			{
				doubleGetter = reinterpret_cast<DoubleGetter>(&GFTTDetector::getQualityLevel);
				return true;
			}
			if (name =="useHarrisDetector" && type == BOOLEAN)
			{
				boolGetter = reinterpret_cast<BoolGetter>(&GFTTDetector::getHarrisDetector);
				return true;
			}
		}
		if (dynamic_cast<const KAZE *>(algoPtr) != NULL)
		{
			if (name =="diffusivity" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&KAZE::getDiffusivity);
				return true;
			}
			if (name =="extended" && type == BOOLEAN)
			{
				boolGetter = reinterpret_cast<BoolGetter>(&KAZE::getExtended);
				return true;
			}
			if (name =="nOctaveLayers" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&KAZE::getNOctaveLayers);
				return true;
			}
			if (name =="nOctaves" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&KAZE::getNOctaves);
				return true;
			}
			if (name =="threshold" && type == REAL)
			{
				doubleGetter = reinterpret_cast<DoubleGetter>(&KAZE::getThreshold);
				return true;
			}
			if (name =="upright" && type == BOOLEAN)
			{
				boolGetter = reinterpret_cast<BoolGetter>(&KAZE::getUpright);
				return true;
			}
		}
		if (dynamic_cast<const MSER *>(algoPtr) != NULL)
		{
			if (name =="delta" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&MSER::getDelta);
				return true;
			}
			if (name =="edgeBlurSize" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="maxArea" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&MSER::getMaxArea);
				return true;
			}
			if (name =="maxEvolution" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="maxVariation" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="minArea" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&MSER::getMinArea);
				return true;
			}
			if (name =="minDiversity" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="minMargin" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="pass2Only" && type == BOOLEAN)
			{
				boolGetter = reinterpret_cast<BoolGetter>(&MSER::getPass2Only);
				return true;
			}
		}
		if (dynamic_cast<const ORB *>(algoPtr) != NULL)
		{
			if (name =="edgeThreshold" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&ORB::getEdgeThreshold);
				return true;
			}
			if (name =="fastThreshold" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&ORB::getFastThreshold);
				return true;
			}
			if (name =="firstLevel" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&ORB::getFirstLevel);
				return true;
			}
			if (name =="nFeatures" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&ORB::getMaxFeatures);
				return true;
			}
			if (name =="nLevels" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&ORB::getNLevels);
				return true;
			}
			if (name =="patchSize" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&ORB::getPatchSize);
				return true;
			}
			if (name =="scaleFactor" && type == REAL)
			{
				doubleGetter = reinterpret_cast<DoubleGetter>(&ORB::getScaleFactor);
				return true;
			}
			if (name =="scoreType" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&ORB::getScoreType);
				return true;
			}
			if (name =="WTA_K" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&ORB::getWTA_K);
				return true;
			}
		}
		if (dynamic_cast<const xfeatures2d::BriefDescriptorExtractor *>(algoPtr) != NULL)
		{
			if (name =="bytes" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="use_orientation" && type == BOOLEAN)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
		}
		if (dynamic_cast<const xfeatures2d::FREAK *>(algoPtr) != NULL)
		{
			if (name =="nbOctave" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="orientationNormalized" && type == BOOLEAN)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="patternScale" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="scaleNormalized" && type == BOOLEAN)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
		}
		if (dynamic_cast<const xfeatures2d::SIFT *>(algoPtr) != NULL)
		{
			if (name =="contrastThreshold" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="edgeThreshold" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="nFeatures" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="nOctaveLayers" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="sigma" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
		}
		if (dynamic_cast<const xfeatures2d::StarDetector *>(algoPtr) != NULL)
		{
			if (name =="lineThresholdBinarized" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="lineThresholdProjected" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="maxSize" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="responseThreshold" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="suppressNonmaxSize" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
		}
		if (dynamic_cast<const xfeatures2d::SURF *>(algoPtr) != NULL)
		{
			if (name =="extended" && type == BOOLEAN)
			{
				boolGetter = reinterpret_cast<BoolGetter>(&xfeatures2d::SURF::getExtended);
				return true;
			}
			if (name =="hessianThreshold" && type == REAL)
			{
				doubleGetter = reinterpret_cast<DoubleGetter>(&xfeatures2d::SURF::getHessianThreshold);
				return true;
			}
			if (name =="nOctaveLayers" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&xfeatures2d::SURF::getNOctaveLayers);
				return true;
			}
			if (name =="nOctaves" && type == INT)
			{
				intGetter = reinterpret_cast<IntGetter>(&xfeatures2d::SURF::getNOctaves);
				return true;
			}
			if (name =="upright" && type == BOOLEAN)
			{
				boolGetter = reinterpret_cast<BoolGetter>(&xfeatures2d::SURF::getUpright);
				return true;
			}
		}
		cerr << "CvAlgoParam(" << name << ")::setGetterFrom("
			 << typeid(*algoPtr).name() << ") unrecognized" << endl;
	}

	return false;
}

/*
 * Sets the appropriate setter according to the type Feature2D in ptr
 * @param ptr the algorithm smart pointer
 * @return true if the appropriate setter has been set, false otherwise
 */
bool CvAlgoParam::setSetterFrom(const Ptr<Feature2D> & ptr)
{
	if (!ptr.empty())
	{
		const Feature2D * algoPtr = ptr.get();

		// clog << "CvAlgoParam::setSetterFrom(" << typeid(algoPtr).name() << ")" << endl;
		if (dynamic_cast<const AgastFeatureDetector *>(algoPtr) != NULL)
		{
			if (name =="nonmaxSuppression" && type == BOOLEAN)
			{
				boolSetter = reinterpret_cast<BoolSetter>(&AgastFeatureDetector::setNonmaxSuppression);
				return true;
			}
			if (name =="threshold" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&AgastFeatureDetector::setThreshold);
				return true;
			}
			if (name =="type" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&AgastFeatureDetector::setType);
				return true;
			}
		}
		if (dynamic_cast<const AKAZE *>(algoPtr) != NULL)
		{
			if (name == "descriptor_channels" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&AKAZE::setDescriptorChannels);
				return true;
			}
			if (name == "descriptor_size" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&AKAZE::setDescriptorSize);
				return true;
			}
			if (name == "descriptor_type" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&AKAZE::setDescriptorType);
				return true;
			}
			if (name == "diffusivity" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&AKAZE::setDiffusivity);
				return true;
			}
			if (name =="nOctaveLayers" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&AKAZE::setNOctaveLayers);
				return true;
			}
			if (name =="nOctaves" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&AKAZE::setNOctaves);
				return true;
			}
			if (name =="threshold" && type == REAL)
			{
				doubleSetter = reinterpret_cast<DoubleSetter>(&AKAZE::setThreshold);
				return true;
			}
		}
		if (dynamic_cast<const BRISK *>(algoPtr) != NULL)
		{
			if (name =="octaves" && type == INT)
			{
				/*
				 * there is an octave parameter in the constructor bu no accessor
				 * to it
				 */
				return false;
			}
			if (name =="thres" && type == INT)
			{
				/*
				 * there is a thres parameter in the constructor bu no accessor
				 * to it
				 */
				return false;
			}
		}
		if (dynamic_cast<const FastFeatureDetector *>(algoPtr) != NULL)
		{
			if (name =="nonmaxSuppression" && type == BOOLEAN)
			{
				boolSetter = reinterpret_cast<BoolSetter>(&FastFeatureDetector::setNonmaxSuppression);
				return true;
			}
			if (name =="threshold" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&FastFeatureDetector::setThreshold);
				return true;
			}
			if (name =="type" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&FastFeatureDetector::setType);
				return true;
			}
		}
		if (dynamic_cast<const GFTTDetector *>(algoPtr) != NULL)
		{
			if (name =="blockSize" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&GFTTDetector::setBlockSize);
				return true;
			}
			if (name =="k" && type == REAL)
			{
				doubleSetter = reinterpret_cast<DoubleSetter>(&GFTTDetector::setK);
				return true;
			}
			if (name =="minDistance" && type == REAL)
			{
				doubleSetter = reinterpret_cast<DoubleSetter>(&GFTTDetector::setMinDistance);
				return true;
			}
			if (name =="nfeatures" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&GFTTDetector::setMaxFeatures);
				return true;
			}
			if (name =="qualityLevel" && type == REAL)
			{
				doubleSetter = reinterpret_cast<DoubleSetter>(&GFTTDetector::setQualityLevel);
				return true;
			}
			if (name =="useHarrisDetector" && type == BOOLEAN)
			{
				boolSetter = reinterpret_cast<BoolSetter>(&GFTTDetector::setHarrisDetector);
				return true;
			}
		}
		if (dynamic_cast<const KAZE *>(algoPtr) != NULL)
		{
			if (name =="diffusivity" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&KAZE::setDiffusivity);
				return true;
			}
			if (name =="extended" && type == BOOLEAN)
			{
				boolSetter = reinterpret_cast<BoolSetter>(&KAZE::setExtended);
				return true;
			}
			if (name =="nOctaveLayers" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&KAZE::setNOctaveLayers);
				return true;
			}
			if (name =="nOctaves" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&KAZE::setNOctaves);
				return true;
			}
			if (name =="threshold" && type == REAL)
			{
				doubleSetter = reinterpret_cast<DoubleSetter>(&KAZE::setThreshold);
				return true;
			}
			if (name =="upright" && type == BOOLEAN)
			{
				boolSetter = reinterpret_cast<BoolSetter>(&KAZE::setUpright);
				return true;
			}
		}
		if (dynamic_cast<const MSER *>(algoPtr) != NULL)
		{
			if (name =="delta" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&MSER::setDelta);
				return true;
			}
			if (name =="edgeBlurSize" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="maxArea" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&MSER::setMaxArea);
				return true;
			}
			if (name =="maxEvolution" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="maxVariation" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="minArea" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&MSER::setMinArea);
				return true;
			}
			if (name =="minDiversity" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="minMargin" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="pass2Only" && type == BOOLEAN)
			{
				boolSetter = reinterpret_cast<BoolSetter>(&MSER::setPass2Only);
				return true;
			}
		}
		if (dynamic_cast<const ORB *>(algoPtr) != NULL)
		{
			if (name =="edgeThreshold" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&ORB::setEdgeThreshold);
				return true;
			}
			if (name =="fastThreshold" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&ORB::setFastThreshold);
				return true;
			}
			if (name =="firstLevel" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&ORB::setFirstLevel);
				return true;
			}
			if (name =="nFeatures" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&ORB::setMaxFeatures);
				return true;
			}
			if (name =="nLevels" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&ORB::setNLevels);
				return true;
			}
			if (name =="patchSize" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&ORB::setPatchSize);
				return true;
			}
			if (name =="scaleFactor" && type == REAL)
			{
				doubleSetter = reinterpret_cast<DoubleSetter>(&ORB::setScaleFactor);
				return true;
			}
			if (name =="scoreType" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&ORB::setScoreType);
				return true;
			}
			if (name =="WTA_K" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&ORB::setWTA_K);
				return true;
			}
		}
		if (dynamic_cast<const xfeatures2d::BriefDescriptorExtractor *>(algoPtr) != NULL)
		{
			if (name =="bytes" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="use_orientation" && type == BOOLEAN)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}

		}
		if (dynamic_cast<const xfeatures2d::FREAK *>(algoPtr) != NULL)
		{
			if (name =="nbOctave" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="orientationNormalized" && type == BOOLEAN)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="patternScale" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="scaleNormalized" && type == BOOLEAN)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
		}
		if (dynamic_cast<const xfeatures2d::SIFT *>(algoPtr) != NULL)
		{
			if (name =="contrastThreshold" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="edgeThreshold" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="nFeatures" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="nOctaveLayers" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="sigma" && type == REAL)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
		}
		if (dynamic_cast<const xfeatures2d::StarDetector *>(algoPtr) != NULL)
		{
			if (name =="lineThresholdBinarized" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="lineThresholdProjected" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="maxSize" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="responseThreshold" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
			if (name =="suppressNonmaxSize" && type == INT)
			{
				/*
				 * Mentionned in constructor, but no accessor
				 */
				return false;
			}
		}
		if (dynamic_cast<const xfeatures2d::SURF *>(algoPtr) != NULL)
		{
			if (name =="extended" && type == BOOLEAN)
			{
				boolSetter = reinterpret_cast<BoolSetter>(&xfeatures2d::SURF::setExtended);
				return true;
			}
			if (name =="hessianThreshold" && type == REAL)
			{
				doubleSetter = reinterpret_cast<DoubleSetter>(&xfeatures2d::SURF::setHessianThreshold);
				return true;
			}
			if (name =="nOctaveLayers" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&xfeatures2d::SURF::setNOctaveLayers);
				return true;
			}
			if (name =="nOctaves" && type == INT)
			{
				intSetter = reinterpret_cast<IntSetter>(&xfeatures2d::SURF::setNOctaves);
				return true;
			}
			if (name =="upright" && type == BOOLEAN)
			{
				boolSetter = reinterpret_cast<BoolSetter>(&xfeatures2d::SURF::setUpright);
				return true;
			}
		}
		cerr << "CvAlgoParam(" << name << ")::setSetterFrom("
			 << typeid(*algoPtr).name() << ") unrecognized" << endl;
	}
	return false;
}
