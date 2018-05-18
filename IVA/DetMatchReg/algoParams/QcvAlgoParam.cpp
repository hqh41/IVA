#include <QDebug>

#include "QcvAlgoParam.h"

/*
 * Constructor for dummy parameter
 * @param lock the lock to use when setting new values
 * @param parent the parent object
 */
QcvAlgoParam::QcvAlgoParam(QMutex * lock,
						   QObject *parent) :
	QObject(parent),
	CvAlgoParam(),
	lock(lock)
{
}

/*
 * Copy Constructor for dummy parameter
 * @param param the parameter to copy (evt with its lock)
 * @param parent the parent object
 */
QcvAlgoParam::QcvAlgoParam(const QcvAlgoParam & param,
						   QObject *parent) :
	QObject(parent),
	CvAlgoParam(param),
	lock(param.lock)
{
}

/*
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
 * @param lock the mutex to check before setting new values
 * @param parent the parent object
 */
QcvAlgoParam::QcvAlgoParam(const string & name,
						   const ParamType & type,
						   const string & description,
						   const ValueType & value,
						   const ValueType & minValue,
						   const ValueType & maxValue,
						   const ValueType & stepValue,
						   const StepMode stepMode,
						   const vector<string> & descriptions,
						   QMutex * lock,
						   QObject *parent) :
	QObject(parent),
	CvAlgoParam(name,
				type,
				description,
				value,
				minValue,
				maxValue,
				stepValue,
				stepMode,
				descriptions),
	lock(lock)
{
}

/*
 * Constructor for an boolean parameter
 * @param name parameter name
 * @param description parameter description
 * @param value parameter value
 * @param lock the mutex to check before setting new values
 * @param parent the parent object
 */
QcvAlgoParam::QcvAlgoParam(const string & name,
						   const string & description,
						   const bool & value,
						   QMutex * lock,
						   QObject * parent) :
	QObject(parent),
	CvAlgoParam(name,
				description,
				value),
	lock(lock)
{
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
 * @param lock the mutex to check before setting new values
 * @param parent the parent object
 */
QcvAlgoParam::QcvAlgoParam(const string & name,
						   const string & description,
						   const int & value,
						   const int & minValue,
						   const int & maxValue,
						   const int & stepValue,
						   const StepMode stepMode,
						   const vector<string> & descriptions,
						   QMutex * lock,
						   QObject * parent) :
	QObject(parent),
	CvAlgoParam(name,
				description,
				value,
				minValue,
				maxValue,
				stepValue,
				stepMode,
				descriptions),
	lock(lock)
{
}

/*
 * Constructor for a double parameter
 * @param name parameter name
 * @param description parameter description
 * @param value parameter value
 * @param minValue parameter minimum value
 * @param maxValue parameter maximum value
 * @param stepValue parameter step value
 * @param stepMode parameter step value mode (additive or
 * multiplicative)
 * @param lock the mutex to check before setting new values
 * @param parent the parent object
 */
QcvAlgoParam::QcvAlgoParam(const string & name,
						   const string & description,
						   const double & value,
						   const double & minValue,
						   const double & maxValue,
						   const double & stepValue,
						   const StepMode stepMode,
						   QMutex * lock,
						   QObject * parent) :
	QObject(parent),
	CvAlgoParam(name,
				description,
				value,
				minValue,
				maxValue,
				stepValue,
				stepMode),
	lock(lock)
{
}

/*
 * Constructor from a line extracted from a CSV file where each element
 * is separated by a semicolon
 * @param line the line to parse in order to setup this paramter
 * @param lock the mutex to check before setting new values
 * @param parent the parent object
 */
QcvAlgoParam::QcvAlgoParam(const string & line,
						   QMutex * lock,
						   QObject * parent) :
	QObject(parent),
	CvAlgoParam(line),
	lock(lock)
{
}

/*
 * Destructor
 */
QcvAlgoParam::~QcvAlgoParam()
{
//	qDebug() << "Destroying qparameter :" << name.c_str();
	// lock does not belong to parameter so don't destroy it
}

/*
 * Sets a new lock
 * @param lock the new lock to set
 */
void QcvAlgoParam::setLock(QMutex * lock)
{
	this->lock = lock;
}

/*
 * Set a new boolean value for this parameter iff this parameter is a
 * boolean parameter, otherwise the parameter value is not set
 * @param value the new boolean value for this parameter
 */
void QcvAlgoParam::setBoolValue(const bool value)
{
	setBoolValue(value, false);
}

/*
 * Set a new boolean value for this parameter iff this parameter is a
 * boolean parameter, otherwise the parameter value is not set
 * @param value the new boolean value for this parameter
 * @param setDefault indicates if we are setting the current value or
 * the current value AND the default value (when setting the default
 * value the #hasDefaultValue becomes true).
 * @return true if the new boolean value has been set on this parameter
 */
bool QcvAlgoParam::setBoolValue(const bool value, const bool setDefault)
{
//	qDebug("%s::setBoolValue(%s)",name.c_str(), (value ? "true" : "false"));

	bool result = false;
	bool hasLock = lock != NULL;
	if (hasLock)
	{
		lock->lock();
	}

	result = CvAlgoParam::setBoolValue(value, setDefault);

	if (hasLock)
	{
		lock->unlock();
	}

	return result;
}

/*
 * Set a new integer value for this parameter iff this parameter is a
 * integer parameter, otherwise the parameter value is not set
 * @param value the new integer value for this parameter
 */
void QcvAlgoParam::setIntValue(const int value)
{
	setIntValue(value, false);
}

/*
 * Set a new integer value for this parameter iff this parameter is a
 * integer parameter, otherwise the parameter value is not set
 * @param value the new integer value for this parameter
 * @param setDefault indicates if we are setting the current value or
 * the current value AND the default value (when setting the default
 * value the #hasDefaultValue becomes true).
 * @return true if the new integer value has been set on this parameter
 */
bool QcvAlgoParam::setIntValue(const int value, const bool setDefault)
{
//	qDebug("%s::setIntValue(%d)", name.c_str(), value);

	bool result = false;
	bool hasLock = lock != NULL;
	if (hasLock)
	{
		lock->lock();
	}

	result = CvAlgoParam::setIntValue(value, setDefault);

	if (hasLock)
	{
		lock->unlock();
	}

	return result;
}

/*
 * Set a new integer value for this parameter from a new index in
 * enumerated values iff this parameter is a integer parameter
 * and also an enumerable parameter, otherwise the parameter value
 * is not set.
 * @param index the index in enumerated values to set the actual value
 */
void QcvAlgoParam::setIndexValue(const int index)
{
	setIndexValue(index, false);
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
bool QcvAlgoParam::setIndexValue(const int index, const bool setDefault)
{
//	qDebug("%s::setIndexValue(%d)", name.c_str(), index);

	bool result = false;
	bool hasLock = lock != NULL;
	if (hasLock)
	{
		lock->lock();
	}

	result = CvAlgoParam::setIndexValue(index, setDefault);

	if (hasLock)
	{
		lock->unlock();
	}

	return result;
}

/*
 * Set a new double value for this parameter iff this parameter is a
 * double parameter, otherwise the parameter value is not set
 * @param value the new double value for this parameter
 */
void QcvAlgoParam::setDoubleValue(const double value)
{
	setDoubleValue(value, false);
}

/*
 * Set a new double value for this parameter iff this parameter is a
 * double parameter, otherwise the parameter value is not set
 * @param value the new double value for this parameter
 * @param setDefault indicate if we are setting the current value or
 * the current value AND the default value (when setting the default
 * value the #hasDefaultValue becomes true).
 * @return true if the new double value has been set on this parameter
 */
bool QcvAlgoParam::setDoubleValue(const double value, const bool setDefault)
{
//	qDebug("%s::setDoubleValue(%f)", name.c_str(), value);

	bool result = false;
	bool hasLock = lock != NULL;
	if (hasLock)
	{
		lock->lock();
	}

	result = CvAlgoParam::setDoubleValue(value, setDefault);

	if (hasLock)
	{
		lock->unlock();
	}

	return result;
}

/*
 * Reset the current value to default value
 * @return true if this parameter has a default value and has been reset
 * to this default value, false otherwise;
 */
bool QcvAlgoParam::resetToDefaultValue()
{
	switch (type)
	{
		case CvAlgoParam::BOOLEAN:
			qDebug("%s::resetToDefaultValue() = %s",
				   name.c_str(),
				   (getBoolValue(CvAlgoParam::DEFAULTVALUE) ? "true" : "false"));
			break;
		case CvAlgoParam::INT:
			qDebug("%s::resetToDefaultValue() = %d",
				   name.c_str(),
				   getIntValue(CvAlgoParam::DEFAULTVALUE));
			break;
		case CvAlgoParam::REAL:
			qDebug("%s::resetToDefaultValue() = %8.3f",
				   name.c_str(),
				   getDoubleValue(CvAlgoParam::DEFAULTVALUE));
		default:
			qDebug() << "Unknown type";
			break;
	}

	bool result = false;
	bool hasLock = lock != NULL;
	if (hasLock)
	{
		lock->lock();
	}

	result = CvAlgoParam::resetToDefaultValue();

	if (hasLock)
	{
		lock->unlock();
	}

	return result;
}

/*
 * Synchronise current value in all algorithms
 */
//void QcvAlgoParam::syncAlgorithms()
//{
//	bool hasLock = lock != NULL;
//	if (hasLock)
//	{
//		lock->lock();
//	}

//	CvAlgoParam::syncAlgorithms();

//	if (hasLock)
//	{
//		lock->unlock();
//	}

//}
