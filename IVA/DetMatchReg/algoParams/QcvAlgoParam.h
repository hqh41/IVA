#ifndef QCVALGOPARAM_H
#define QCVALGOPARAM_H

#include <QObject>
#include <QMutex>

#include "CvAlgoParam.h"

/**
 * Class representing a set of parameters for an algorithm with Qt flavor,
 * i.e. a QObject parent and a QMutex for operations from multiple threads
 * @author David Roussel
 * @date 2015/04/29
 */
class QcvAlgoParam : public QObject, public CvAlgoParam
{
	Q_OBJECT
	private:
		/**
		 * Mutex to use when modifying values (iff not NULL) when
		 * operated from multiple threads
		 */
		QMutex * lock;

	public:
		/**
		 * Constructor for dummy parameter with mutex lock and parent
		 * @param lock the lock to use when setting new values
		 * @param parent the parent object
		 */
		explicit QcvAlgoParam(QMutex * lock = NULL,
							  QObject *parent = NULL);

		/**
		 * Copy Constructor with mutex lock and parent
		 * @param param the parameter to copy (evt with its lock)
		 * @param parent the parent object
		 */
		explicit QcvAlgoParam(const QcvAlgoParam & param,
							  QObject *parent = NULL);

		/**
		 * Valued Constructor with mutex lock and parent
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
		explicit QcvAlgoParam(const string & name,
							  const ParamType & type,
							  const string & description,
							  const ValueType & value,
							  const ValueType & minValue,
							  const ValueType & maxValue,
							  const ValueType & stepValue,
							  const StepMode stepMode = ADD,
							  const vector<string> & descriptions = vector<string>(),
							  QMutex * lock = NULL,
							  QObject *parent = NULL);
		/**
		 * Constructor for an boolean parameter with mutex lock and parent
		 * @param name parameter name
		 * @param description parameter description
		 * @param value parameter value
		 * @param lock the mutex to check before setting new values
		 * @param parent the parent object
		 */
		explicit QcvAlgoParam(const string & name,
							  const string & description,
							  const bool & value,
							  QMutex * lock = NULL,
							  QObject * parent = NULL);

		/**
		 * Constructor for an integer parameter with mutex lock and parent
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
		explicit QcvAlgoParam(const string & name,
							  const string & description,
							  const int & value,
							  const int & minValue,
							  const int & maxValue,
							  const int & stepValue,
							  const StepMode stepMode = ADD,
							  const vector<string> & descriptions = vector<string>(),
							  QMutex * lock = NULL,
							  QObject * parent = NULL);

		/**
		 * Constructor for a double parameter with mutex lock and parent
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
		explicit QcvAlgoParam(const string & name,
							  const string & description,
							  const double & value,
							  const double & minValue,
							  const double & maxValue,
							  const double & stepValue,
							  const StepMode stepMode = ADD,
							  QMutex * lock = NULL,
							  QObject * parent = NULL);

		/**
		 * Constructor from a line extracted from a CSV file where each element
		 * is separated by a semicolon with mutex lock and parent
		 * @param line the line to parse in order to setup this paramter
		 * @param lock the mutex to check before setting new values
		 * @param parent the parent object
		 */
		explicit QcvAlgoParam(const string & line,
							  QMutex * lock = NULL,
							  QObject * parent = NULL);

		/**
		 * Destructor
		 */
		virtual ~QcvAlgoParam();

		/**
		 * Sets a new lock
		 * @param lock the new lock to set
		 */
		void setLock(QMutex * lock);

		/**
		 * Set a new boolean value for this parameter iff this parameter is a
		 * boolean parameter, otherwise the parameter value is not set
		 * @param value the new boolean value for this parameter
		 * @param setDefault indicates if we are setting the current value or
		 * the current value AND the default value (when setting the default
		 * value the #hasDefaultValue becomes true).
		 * @return true if the new boolean value has been set on this parameter
		 */
		bool setBoolValue(const bool value, const bool setDefault);

		/**
		 * Set a new integer value for this parameter iff this parameter is a
		 * integer parameter, otherwise the parameter value is not set
		 * @param value the new integer value for this parameter
		 * @param setDefault indicates if we are setting the current value or
		 * the current value AND the default value (when setting the default
		 * value the #hasDefaultValue becomes true).
		 * @return true if the new integer value has been set on this parameter
		 */
		bool setIntValue(const int value, const bool setDefault);

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
		bool setIndexValue(const int index, const bool setDefault);

		/**
		 * Set a new double value for this parameter iff this parameter is a
		 * double parameter, otherwise the parameter value is not set
		 * @param value the new double value for this parameter
		 * @param setDefault indicate if we are setting the current value or
		 * the current value AND the default value (when setting the default
		 * value the #hasDefaultValue becomes true).
		 * @return true if the new double value has been set on this parameter
		 */
		bool setDoubleValue(const double value, const bool setDefault);

	signals:

	public slots:
		/**
		 * Set a new boolean value for this parameter iff this parameter is a
		 * boolean parameter, otherwise the parameter value is not set
		 * @param value the new boolean value for this parameter
		 */
		void setBoolValue(const bool value);

		/**
		 * Set a new integer value for this parameter iff this parameter is a
		 * integer parameter, otherwise the parameter value is not set
		 * @param value the new integer value for this parameter
		 */
		void setIntValue(const int value);

		/**
		 * Set a new integer value for this parameter from a new index in
		 * enumerated values iff this parameter is a integer parameter
		 * and also an enumerable parameter, otherwise the parameter value
		 * is not set.
		 * @param index the index in enumerated values to set the actual value
		 */
		void setIndexValue(const int index);

		/**
		 * Set a new double value for this parameter iff this parameter is a
		 * double parameter, otherwise the parameter value is not set
		 * @param value the new double value for this parameter
		 */
		void setDoubleValue(const double value);

		/**
		 * Reset the current value to default value
		 * @return true if this parameter has a default value and has been reset
		 * to this default value, false otherwise;
		 */
		bool resetToDefaultValue();

//		/**
//		 * Synchronise current value in all algorithms
//		 */
//		void syncAlgorithms();
};

#endif // QCVALGOPARAM_H
