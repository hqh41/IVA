/*
 * CvAlgoParam.h
 *
 *  Created on: 20 avr. 2014
 *      Author: davidroussel
 */

#ifndef CVALGOPARAM_H_
#define CVALGOPARAM_H_

#include <opencv2/core/core.hpp>	// Ptr<X> & Algorithm
#include <opencv2/features2d.hpp>
using namespace cv;

#include <functional>
#include <set>
#include <string>
using namespace std;

/**
 * Class representing an algorithm parameter (according to OpenCV)
 * @author David Roussel
 * @date 2014/04/24
 */
class CvAlgoParam
{
	public:

//		/**
//		 * Dummy empty parameter (default constructed)
//		 */
//		static const CvAlgoParam dummyParam;

		/**
		 * Parameter type
		 */
		typedef enum EParamType
		{
			UNKNOWN = -1,
			BOOLEAN = 0,//!< BOOLEAN
			INT,        //!< INT
			REAL        //!< REAL
		} ParamType;

		/**
		 * Value Union
		 */
		typedef union UValueType
		{
			bool boolValue;		//!< Boolean value
			int intValue;		//!< Integer value
			double doubleValue;	//!< Double value
			bool operator ==(const union UValueType & val) const;
		} ValueType;

		/**
		 * Enum used in getters to determine which value to return
		 */
		typedef enum EWhichValue
		{
			VALUE = 0, //!< The value itself
			MINVALUE, //!< The minimum value
			MAXVALUE, //!< The maximum value
			STEPVALUE, //!< The step value
			DEFAULTVALUE, //!< The default value (to reset to)
			ACTUALVALUE //!< The actual value from a registered algorithm
		} WhichValue;

		/**
		 * Step value mode: add or multiply
		 */
		typedef enum EStepMode
		{
			ADD = 0,//!< ADD
			MUL     //!< MUL
		} StepMode;

		/**
		 * Maximum number of values descriptions
		 */
		static size_t nbValueDescriptionsMax;

		/**
		 * Maximum number of tags in line of a CSV file containing a parameter
		 * description.
		 * @code
		 * SURF;hessianThreshold;double;Threshold for hessian keypoint detector used in SURF;100;10;1000;10;ADD;;;;;;;;
		 * @endcode
		 */
		static size_t nbParamMaxTag;

		/**
		 * The differents elements we'll find on a line defining a parameter
		 */
		typedef enum ETagStep
		{
			ALGONAME_STEP = 0,     //!< Algorithm name
			PARAMNAME_STEP = 1,        //!< Parameter name
			PARAMTYPE_STEP = 2,        //!< Parameter type (boolean, integer, real)
			PARAMDESCRIPTION_STEP = 3, //!< Help string describing the parameter
			VALUE_STEP = 4,            //!< parameter default value
			MINVALUE_STEP = 5,         //!< parameter minimum value
			MAXVALUE_STEP = 6,         //!< parameter maximum value
			STEPVALUE_STEP = 7,        //!< parameter step value
			STEPMODE_STEP = 8,         //!< stepvalue application mode (ADD or MUL)
			VALUEDESCRIPTION_STEP = 9, //!< One or several value descriptions
			NBSTEPS = 10      //!< Total number of steps
		} TagStep;

		/**
		 * Boolean getter method pointer type in a Feature2D
		 */
		typedef bool(Feature2D::*BoolGetter)() const;
		//typedef function<bool(Feature2D *)const> BoolGetter;
		//using BoolGetter = function<bool(Feature2D *)const>;

		/**
		 * Integer getter method pointer type in a Feature2D
		 */
		typedef int(Feature2D::*IntGetter)() const;
		//typedef function<int(Feature2D *)const> IntGetter;

		/**
		 * Double getter method pointer type in a Feature2D
		 */
		typedef double(Feature2D::*DoubleGetter)() const;
		//typedef function<double(Feature2D *)const> DoubleGetter;

		/**
		 * Boolean setter method pointer type in a Feature2D
		 */
		typedef void(Feature2D::*BoolSetter)(bool);
		//typedef function<void(Feature2D *, bool)> BoolSetter;

		/**
		 * Integer setter method pointer type in a Feature2D
		 */
		typedef void(Feature2D::*IntSetter)(int);
		//typedef function<void(Feature2D *, int)> IntSetter;

		/**
		 * Double setter method pointer type in a Feature2D
		 */
		typedef void(Feature2D::*DoubleSetter)(double);
		//typedef function<void(Feature2D *, double)> DoubleSetter;

		/**
		 * Default Constructor to dummy parameter
		 */
		CvAlgoParam();

		/**
		 * Copy constructor
		 * @param param the parameter to copy
		 */
		CvAlgoParam(const CvAlgoParam & param);

		/**
		 * Valued Constructor
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
		 */
		CvAlgoParam(const string & name,
					const ParamType & type,
					const string & description,
					const ValueType & value,
					const ValueType & minValue,
					const ValueType & maxValue,
					const ValueType & stepValue,
					const StepMode stepMode = ADD,
					const vector<string> & descriptions = vector<string>());

		/**
		 * Constructor for an boolean parameter
		 * @param name parameter name
		 * @param description parameter description
		 * @param value parameter value
		 */
		CvAlgoParam(const string & name,
					const string & description,
					const bool & value);

		/**
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
		 */
		CvAlgoParam(const string & name,
					const string & description,
					const int & value,
					const int & minValue,
					const int & maxValue,
					const int & stepValue,
					const StepMode stepMode = ADD,
					const vector<string> & descriptions = vector<string>());

		/**
		 * Constructor for a double parameter
		 * @param name parameter name
		 * @param description parameter description
		 * @param value parameter value
		 * @param minValue parameter minimum value
		 * @param maxValue parameter maximum value
		 * @param stepValue parameter step value
		 * @param stepMode parameter step value mode (additive or
		 * multiplicative)
		 */
		CvAlgoParam(const string & name,
					const string & description,
					const double & value,
					const double & minValue,
					const double & maxValue,
					const double & stepValue,
					const StepMode stepMode = ADD);

		/**
		 * Constructor from a line extracted from a CSV file where each element
		 * is separated by a semicolon
		 * @param line the line to parse in order to setup this paramter
		 */
		CvAlgoParam(const string & line);

		/**
		 * Destructor
		 */
		virtual ~CvAlgoParam();

		/**
		 * Parameter name accessor
		 * @return the parameter's name
		 */
		string getName() const;

		/**
		 * Get the parameter type
		 * @return the parameter type
		 */
		ParamType getType() const;

		/**
		 * Parameter's description accessor
		 * @return the parameter's description
		 */
		string getDescription() const;

		/**
		 * Get the boolean value of this parameter
		 * @param which the value to return :
		 * 	- the value itself : VALUE
		 * 	- the minimum value : MINVALUE
		 * 	- the maximum value : MAXVALUE
		 * 	- the step value : STEPVALUE
		 *	- the default value : DEFAULTVALUE
		 *	- the actual value from a registered algorithm (if possible) ACTUALVALUE
		 * @return the boolean value of this parameter
		 */
		bool getBoolValue(const WhichValue which = VALUE) const;

		/**
		 * Get the integer value of this parameter
		 * @param which the value to return :
		 * 	- the value itself : VALUE
		 * 	- the minimum value : MINVALUE
		 * 	- the maximum value : MAXVALUE
		 * 	- the step value : STEPVALUE
		 *	- the default value : DEFAULTVALUE
		 * @return the integer value of this parameter
		 */
		int getIntValue(const WhichValue which = VALUE) const;

		/**
		 * Get int value from index in enumerable parameter
		 * @param index the index
		 * @return the integer value corresponding to this index
		 */
		int getIntValueFromIndex(const size_t index) const;

		/**
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
		int getValueIndex(const WhichValue which = VALUE) const;

		/**
		 * Get the double value of this parameter
		 * @param which the value to return :
		 * 	- the value itself : VALUE
		 * 	- the minimum value : MINVALUE
		 * 	- the maximum value : MAXVALUE
		 * 	- the step value : STEPVALUE
		 *	- the default value : DEFAULTVALUE
		 * @return the double value of this parameter
		 */
		double getDoubleValue(const WhichValue which = VALUE) const;

		/**
		 * Get the step mode between values
		 * @return the step mode
		 */
		StepMode getStepMode() const;

		/**
		 * Set a new boolean value for this parameter iff this parameter is a
		 * boolean parameter, otherwise the parameter value is not set
		 * @param value the new boolean value for this parameter
		 * @param setDefault indicates if we are setting the current value or
		 * the current value AND the default value (when setting the default
		 * value the #hasDefaultValue becomes true).
		 * @return true if the new boolean value has been set on this parameter
		 */
		virtual bool setBoolValue(const bool value, const bool setDefault = false);

		/**
		 * Set a new integer value for this parameter iff this parameter is a
		 * integer parameter, otherwise the parameter value is not set
		 * @param value the new integer value for this parameter
		 * @param setDefault indicates if we are setting the current value or
		 * the current value AND the default value (when setting the default
		 * value the #hasDefaultValue becomes true).
		 * @return true if the new integer value has been set on this parameter
		 */
		virtual bool setIntValue(const int value, const bool setDefault = false);

		/**
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
		virtual bool setIndexValue(const int index, const bool setDefault = false);

		/**
		 * Set a new double value for this parameter iff this parameter is a
		 * double parameter, otherwise the parameter value is not set
		 * @param value the new double value for this parameter
		 * @param setDefault indicate if we are setting the current value or
		 * the current value AND the default value (when setting the default
		 * value the #hasDefaultValue becomes true).
		 * @return true if the new double value has been set on this parameter
		 */
		virtual bool setDoubleValue(const double value, const bool setDefault = false);

		/**
		 * Reset the current value to default value
		 * @return true if this parameter has a default value and has been reset
		 * to this default value, false otherwise;
		 */
		virtual bool resetToDefaultValue();

		/**
		 * Adds an algorithm and if the algorithm contains a parameter of this
		 * name then add it to the list of algorithms linked to this parameter
		 * @param ptr the algorithm smart pointer
		 * @return true if algorithm have been added (iff it containts a
		 * parameter matching this parameter), false otherwise.
		 */
		bool addAlgorithm(const Ptr<Feature2D> & ptr);

		/**
		 * Remove an algorithm from the list of algorithms linked to this
		 * parameter
		 * @param ptr the algorithm smart pointer to remove
		 * @return true if the algorithm smart pointer have been removed from
		 * the list of related algorithms
		 */
		bool removeAlgorithm(const Ptr<Feature2D> & ptr);

		/**
		 * Remove all associated algorithms
		 */
		void removeAllAlgorithms();

		/**
		 * Is this parameter an enum
		 * @return true if the number of possible values is less than
		 * #nbValueDescriptionsMax and each possible value has a corresponding
		 * description
		 */
		bool isEnum() const;

		/**
		 * Is this parameter a constant
		 * @return true if this parameter has a stepValue equivalent to zero
		 * and/or if min & max value are the same
		 */
		bool isConstant() const;

		/**
		 * Is this parameter ok: Used when parameter is constructed from parsing
		 * a text line to indicates it has no parsing error
		 */
		bool isOk() const;

		/**
		 * Is this parameter value obtainable from an actual algorithm ?
		 * @return true if the value is gettable from an actual algorithm,
		 * false otherwise
		 */
		bool isGettable() const;

		/**
		 * Can we set this value in an actual algorithm ?
		 * @return true if the value is settable into an actual algorithm,
		 * false otherwise
		 */
		bool isSettable() const;

		/**
		 * Get all possible values descriptions.
		 * @note the number of possible values is always < #nbValueDescriptionsMax
		 * @return a vector constaining all possible values descriptions if
		 * this parameter is an enum (according to #isEnum()) or an empty
		 * vector if this parameter has no values descriptions
		 */
		vector<string> getValueDescriptions() const;

		/**
		 * Value description for value value (if it exists)
		 * @param value the value for which we request a description
		 * @return the description corresponding tho the value or an empty
		 * string if there is no description for this value.
		 */
		string getDescription(const int value) const;

		/**
		 * Set of algorithm pointers associated with this parameter
		 * @return a set of cosntant Algorithm pointers associated with this
		 * parameter
		 */
		set<const Feature2D *> getAlgorithmsPtr() const;

		/**
		 * Comparison operator
		 * @param param the parameter to compare
		 * @return true param contains exactly the same values as in this
		 * parameter
		 */
		bool operator ==(const CvAlgoParam & param) const;

		/**
		 * Difference operator
		 * @param param the parameter to compare
		 * @return false if param contains exactly the same values as in this
		 * parameter
		 */
		inline bool operator !=(const CvAlgoParam & param) const
		{
			return !operator ==(param);
		}

		/**
		 * Copy operator
		 * @param param the parameter to copy
		 * @return a reference to this parameter
		 */
		CvAlgoParam & operator =(const CvAlgoParam & param);

		/**
		 * Friend output operatpr
		 * @param out the output stream
		 * @param p the parameter to print on the output stream
		 * @return a reference to the output stream
		 */
		friend ostream & operator <<(ostream & out, const CvAlgoParam & p);

		/**
		 * character separating tags in the file : ';'
		 */
		static const char sep;

	protected:

		/**
		 * Parameter name
		 */
		string name;

		/**
		 * Parameter type
		 */
		ParamType type;

		/**
		 * Parameter description
		 */
		string description;

		/**
		 * Parameter value
		 */
		ValueType value;

		/**
		 * Parameter minimum value
		 */
		ValueType minValue;

		/**
		 * Parameter maximum value
		 */
		ValueType maxValue;

		/**
		 * Parameter step value
		 */
		ValueType stepValue;

		/**
		 * The mode to apply to step mode
		 */
		StepMode stepMode;

		/**
		 * Default value to reset to.
		 * Only parameters read from file can have a default value which is
		 * the initial value. This is why defaultValue is not part of the
		 * argument of valued constructors. The default value has to be set
		 * later with the setDefaultValue method
		 * @see #hasDefaultValue
		 */
		ValueType defaultValue;

		/**
		 * Indicates that default value has been set and such a parameter
		 * can be resetted to this default value
		 */
		bool hasDefaultValue;

		/**
		 * Values descriptions for enumerated values
		 */
		vector<string> valueDescriptions;

		/**
		 * Parse error when param is read from a file line
		 */
		bool parseError;

		/**
		 * Indicates the pasring has completed and that each field
		 * has been initialized
		 */
		bool parsingCompleted;

		/**
		 * Indicates if value can be retrived from actual algorihtm
		 */
		bool gettable;

		/**
		 * Indicates if vale can be set into actual algorithm
		 */
		bool settable;

		/**
		 * Function pointer to use for getting a boolean value from a Ptr<Feature2D>
		 * @note such a getter is set during first #addAlgorithm(const Ptr<Feature2D> &)
		 */
		BoolGetter boolGetter;

		/**
		 * Function pointer to use for setting a boolean value in a Ptr<Feature2D>
		 * @note such a setter is set during first #addAlgorithm(const Ptr<Feature2D> &)
		 */
		BoolSetter boolSetter;

		/**
		 * Function pointer to use for getting a int value from a Ptr<Feature2D>
		 * @note such a getter is set during first #addAlgorithm(const Ptr<Feature2D> &)
		 */
		IntGetter intGetter;

		/**
		 * Function pointer to use for setting a int value in a Ptr<Feature2D>
		 * @note such a setter is set during first #addAlgorithm(const Ptr<Feature2D> &)
		 */
		IntSetter intSetter;

		/**
		 * Function pointer to use for getting a double value from a Ptr<Feature2D>
		 * @note such a getter is set during first #addAlgorithm(const Ptr<Feature2D> &)
		 */
		DoubleGetter doubleGetter;

		/**
		 * Function pointer to use for setting a double value in a Ptr<Feature2D>
		 * @note such a setter is set during first #addAlgorithm(const Ptr<Feature2D> &)
		 */
		DoubleSetter doubleSetter;

		/**
		 * Set of Smart pointers to algorithm featuring this parameter
		 * in order to change their parameter's value
		 */
		set<Ptr<Feature2D> > algorithms;

		/**
		 * Synchronise current value in all algorithms linked to this parameter
		 * @note only used in #addAlgorithm(const Ptr<Feature2D> &)
		 */
		void syncValueInAlgorithms();

		/**
		 * index of this value in the values descriptions
		 * @param value the value that we are searching for its index
		 * @return the index of this value in the descriptions or -1
		 * if there is no description for this value.
		 */
		int indexOf(const int value) const;

		/**
		 * Sets the appropriate getter according to the type Feature2D in ptr
		 * @param ptr the algorithm smart pointer
		 * @return true if the appropriate getter has been set, false otherwise
		 */
		bool setGetterFrom(const Ptr<Feature2D> & ptr);

		/**
		 * Sets the appropriate setter according to the type Feature2D in ptr
		 * @param ptr the algorithm smart pointer
		 * @return true if the appropriate setter has been set, false otherwise
		 */
		bool setSetterFrom(const Ptr<Feature2D> & ptr);
};

#endif /* CVALGOPARAM_H_ */
