#include <string>
#include <sstream>
using namespace std;

#include <QDebug>

#include "QcvAlgoParam.h"
#include "QcvAlgoParamSets.h"

/*
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
QcvAlgoParamSets::QcvAlgoParamSets(ifstream & stream,
								   QMutex * lock,
								   QObject *parent) :
	QObject(parent),
	CvAlgoParamSets() // Default protected constructor does not parse stream
{
	string lineString;
	while (stream.good())
	{
		getline(stream, lineString, eol); // read until next line

		if (!checkSeparators(lineString))
		{
			break;
		}

		istringstream lineStream(lineString);
		string algoName;
		if (lineStream.good())
		{
			getline(lineStream, algoName, CvAlgoParam::sep); // read a string until next semicolon

			if (algoName.length() > 0)
			{
				if (!contains(algoName))
				{
					// Adds this paramSet
					addParamSet(CvAlgoParamSet(algoName));
				}

				CvAlgoParamSet * const paramSet = getParamSet(algoName);

				// Adds this parameter to this param set,
				// this is where CvAlgoParamSets and QcvAlgoParamSets differs.
				// Also don't forget to add "this" as a parent so when "this"
				// is moved to another thread the QcvAlgoParams will also be
				// moved to thread.
				paramSet->addParameter(new QcvAlgoParam(lineString, lock, this));
			}
		}
	}
}

/*
 * Destructor
 */
QcvAlgoParamSets::~QcvAlgoParamSets()
{
//	qDebug() << "Destroying qAlgoParamSets";
}


/*
 * Sets new mutex lock on all parameters of all parameters sets
 * @param mutex the new mutex lock to st on all parameters
 */
void QcvAlgoParamSets::setLock(QMutex * mutex)
{
	// Iterate over all params sets
	for (map<string, CvAlgoParamSet>::iterator psit = paramSets.begin();
		 psit!= paramSets.end(); ++psit)
	{
		CvAlgoParamSet & paramSet = psit->second;
		// iterate over all params in this set
		for (map<string, Ptr<CvAlgoParam> >::iterator pit = paramSet.begin();
			 pit != paramSet.end(); ++pit)
		{
			CvAlgoParam * param = pit->second;
			QcvAlgoParam * qparam = dynamic_cast<QcvAlgoParam *>(param);
			if (qparam != NULL)
			{
				qparam->setLock(mutex);
			}
			else
			{
				qDebug() << "Unable to cast param"
						 << pit->second->getName().c_str()
						 << "into QcvAlgoParam";
			}
		}
	}
}

/*
 * Debug operator for CvAlgoParam
 * @param debug the debug stream
 * @param p the parameter to send to debug stream
 * @return the debug stream
 */
QDebug operator<<(QDebug debug, const CvAlgoParam & p)
{
	QDebugStateSaver saver(debug);
	debug.nospace() << "(";
	if (p.isGettable())
	{
		debug.nospace() << "r";
	}
	if (p.isSettable())
	{
		debug.nospace() << "w";
	}
	debug.nospace() << ") ";

	QString name = QString::fromStdString(p.getName());
	switch (p.getType())
	{
		case CvAlgoParam::BOOLEAN:
			debug.nospace() << name << " [boolean] = "
							<< (p.getBoolValue() ? "true" : "false");
			if (p.isConstant())
			{
				debug.nospace() << " (constant)";
			}
			debug.nospace() << '\n';
			break;
		case CvAlgoParam::INT:
			debug.nospace() << name << " [integer] = " << p.getIntValue();
			if (!p.isConstant())
			{
				debug.nospace()
					<< " [" << p.getIntValue(CvAlgoParam::MINVALUE) << ".."
					<< p.getIntValue(CvAlgoParam::MAXVALUE) << "]"
					<< (p.getStepMode() == CvAlgoParam::ADD ? "+" : "*") << "["
					<< p.getIntValue(CvAlgoParam::STEPVALUE) << "]";
			}
			else
			{
				debug.nospace() << " (Constant)";
			}
			if (p.isEnum())
			{
				debug.nospace() << " {";
				vector<string> descriptions = p.getValueDescriptions();
				for (vector<string>::const_iterator it = descriptions.begin();
					 it != descriptions.end();
					 ++it)
				{
					debug.nospace() << " " << QString::fromStdString(*it);
				}
				debug.nospace() << "}";
			}
			debug.nospace() << '\n';
			break;
		case CvAlgoParam::REAL:
			debug.nospace() << name << " [real] = " << p.getDoubleValue();
			if (!p.isConstant())
			{
				debug.nospace()
					<< " [" << p.getDoubleValue(CvAlgoParam::MINVALUE) << ".."
					<< p.getDoubleValue(CvAlgoParam::MAXVALUE) << "]"
					<< (p.getStepMode() == CvAlgoParam::ADD ? "+" : "*") << "["
					<< p.getDoubleValue(CvAlgoParam::STEPVALUE) << "]";
			}
			else
			{
				debug.nospace() << " (Constant)";
			}
			debug.nospace() << '\n';
			break;
		case CvAlgoParam::UNKNOWN:
			debug.nospace() << name << "[unknown]" << '\n';
			break;
	}

	debug.nospace() << "\t" << QString::fromStdString(p.getDescription()) << '\n';
	set<const Feature2D *> algoSet = p.getAlgorithmsPtr();
	if (!algoSet.empty())
	{
		debug.nospace() << "\t algorithms = {";
		for (set<const Feature2D *>::const_iterator it = algoSet.cbegin();
			 it != algoSet.cend(); ++it)
		{
			const Feature2D * algoPtr = *it;
			debug.nospace() << " " << algoPtr;
		}
		debug.nospace() << "}" << '\n';
	}

	return debug;
}

/*
 * Debug operator for CvAlgoParamSet
 * @param debug the debug stream
 * @param p the parameter set to send to debug stream
 * @return the debug stream
 */
QDebug operator<<(QDebug debug, const CvAlgoParamSet & p)
{
	QDebugStateSaver saver(debug);
	debug.nospace()	<< "----------------------------------------------------------\n";
	debug.nospace() << QString::fromStdString(p.getName()) << " parameters ("
					<< p.nbParameters() << ")\n";
	for (map<string, Ptr<CvAlgoParam> >::const_iterator it = p.cbegin(); it != p.cend();
		 ++it)
	{
		debug.nospace() << *(it->second);
	}
	debug.nospace()	<< "----------------------------------------------------------\n";

	return debug;
}
