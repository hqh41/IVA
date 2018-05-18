#ifndef QCVALGOPARAMSETS_H
#define QCVALGOPARAMSETS_H

#include <QObject>
#include <QMutex>
#include <QDebug>
#include "CvAlgoParamSets.h"

/**
 * Parameters sets for several algorithms with Qtflavor:
 *	- Adds a mutex lock capabilities to algorithm parameters withing the
 *	algorithm parameters sets
 * @author David Roussel
 * @date 2015/05/01
 */
class QcvAlgoParamSets : public QObject, public CvAlgoParamSets
{
	Q_OBJECT
	public:
		/**
		 * Constructor from CSV file containing algorithms parameters and parent
		 * @param stream the stream to read from
		 * @param lock the lock to apply on parameters (if any)
		 * @param parent the parent object (if any)
		 * @note does the same file parsing as CvAlgoParamSets valued
		 * constructor but constructs QcvAlgoParam instances instead of
		 * CvAlgoParam instances. These QcvAlgoParam instances could then
		 * receive a mutex lock for operating parameters values from multiple
		 * threads.
		 */
		explicit QcvAlgoParamSets(ifstream & stream,
								  QMutex * lock = NULL,
								  QObject * parent = NULL);

		/**
		 * Destructor
		 */
		virtual ~QcvAlgoParamSets();

		/**
		 * Sets new mutex lock on all parameters of all parameters sets
		 * @param mutex the new mutex lock to set on all parameters
		 */
		void setLock(QMutex * mutex);
	signals:

	public slots:

};


/**
 * Debug operator for CvAlgoParam
 * @param debug the debug stream
 * @param p the parameter to send to debug stream
 * @return the debug stream
 */
QDebug operator<<(QDebug debug, const CvAlgoParam & p);

/**
 * Debug operator for CvAlgoParamSet
 * @param debug the debug stream
 * @param p the parameter set to send to debug stream
 * @return the debug stream
 */
QDebug operator<<(QDebug debug, const CvAlgoParamSet & p);

#endif // QCVALGOPARAMSETS_H
