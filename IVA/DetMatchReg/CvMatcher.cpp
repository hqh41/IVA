/*
 * CvMatcher.cpp
 *
 *  Created on: 1 mars 2012
 *	  Author: davidroussel
 */
#include <cmath>
#include <limits>
#include "CvMatcher.h"

/*
 * Descriptors matcher names to compare with arguments:
 */
const string CvMatcher::MatcherNames[MATCHER_NUMBER] =
{
	"BruteForce",
	"BruteForce-L1",
	"BruteForce-Hamming",
	"BruteForce-Hamming(2)",
	"FlannBased"
};

/*
 * Matchers capability to support binary content descriptors:
 */
const bool CvMatcher::MatcherBinary[MATCHER_NUMBER] =
{
	true,	// Brute force matcher supports binary descriptors
	true,	// Brute force L1 matcher supports binary descriptors
	true,	// Brute force Hamming supports binary descriptors
	true,	// Brute force Hamming LUT supports binary descriptors
	false	// Flann based DOES NOT support binary descriptors
};

/*
 * Matchers capability to support floating points numbers content
 * descriptors:
 */
const bool CvMatcher::MatcherFloat[MATCHER_NUMBER] =
{
	true,	// Brute force matcher supports valued descriptors
	true,	// Brute force L1 matcher supports valued descriptors
	false,	// Brute force Hamming DOES NOT support valued descriptors
	false,	// Brute force Hamming LUT DOES NOT support valued descriptors
	true	// Flann based supports valued descriptors
};

/*
 * Matching types names
 */
const string CvMatcher::MatchTypeNames[NBMATCHMODES] =
{
	"Simple Match",
	"Cross Best Match",
	"Radius Best Match"
};

/*
 * Minimum match error absolute upper bound [1.0]
 */
const double CvMatcher::MinMatchErrorBound = numeric_limits<double>::max();

/*
 * Maximum match error absolute lower bound [0.0]
 */
const double CvMatcher::MaxMatchErrorBound = 0.0;


/*
 * Maximum number of best matches (5 or 10)
 */
const int CvMatcher::knnMax = 5;

/*
 * Default radius threshold value
 */
const double CvMatcher::radiusThresholdDefault = 0.25;

/*
 * Minimum radius threshold
 */
const double CvMatcher::radiusThresholdMin = 0.0;

/*
 * Maximum radius threshold
 */
const double CvMatcher::radiusThresholdMax = 1.0;

/*
 * Steps to radiusThreshold values
 */
const double CvMatcher::radiusThresholdStep = 0.01;

/*
 * OpenCV Matcher constructor
 * @param matcherType type of matcher
 * @param matcherMode type of match
 */
CvMatcher::CvMatcher(const MatcherType matcherType,
					 const MatchType matcherMode,
					 const CvProcessor::VerboseLevel level) :
	matcherMode(matcherMode),
	modelDescriptors(NULL),
	sceneDescriptors(NULL),
	minMatchError(MinMatchErrorBound),
	maxMatchError(MaxMatchErrorBound),
	meanMatchError(MaxMatchErrorBound),
	stdMatchError(MaxMatchErrorBound),
	knn(1),
	radiusThreshold(radiusThresholdDefault),
	verboseLevel(level),
	processTime(0),
	meanProcessTime(),
	timePerFeature(false)
	// all vectors are set with their default constructors
{
	setMatcherType(matcherType, false);
}

/*
 * OpenCV Matcher destructor
 */
CvMatcher::~CvMatcher()
{
	matchDistances.clear();
	sceneMatchedIndex.clear();
	modelMatchedIndex.clear();
	matches21.clear();
	matches12.clear();
	matches.clear();
	descriptorMatcher.release();
}

/*
 * Gets the current Matcher type
 * @return the current Matcher type
 */
CvMatcher::MatcherType CvMatcher::getMatcherType() const
{
	return matcherType;
}

/*
 * Sets a new matcher type
 * @param matcherType the new matcher type to set
 * @param full true when matches and matcher needs to be cleaned up
 * first
 * @post the old DescriptorMatcher has been released and a new one
 * has been created
 * @throw CvProcessorException if matcher is empty because it
 * couldn't be created properly
 */
void CvMatcher::setMatcherType(const MatcherType matcherType,
							   const bool full)
	throw (CvProcessorException)
{
	if (full)
	{
		// cleanup
		matchDistances.clear();
		sceneMatchedIndex.clear();
		modelMatchedIndex.clear();
		matches21.clear();
		matches12.clear();
		matches.clear();
		matcherName.clear();
		descriptorMatcher.release();

		// setup
		minMatchError = MinMatchErrorBound;
		maxMatchError = MaxMatchErrorBound;
		meanMatchError = 0.0;
		stdMatchError = 0.0;
	}

	// Setup Matcher
	this->matcherType = matcherType;
	matcherName = MatcherNames[matcherType];

	clog << "Creating Matcher #" << matcherType  << ": " << matcherName << endl;

	// TODO Création du descriptormatcher à partir de matcherName
	// grâce à la factory method DescriptorMatcher::create
	// see http://docs.opencv.org/3.1.0/db/d39/classcv_1_1DescriptorMatcher.html#ab5dc5036569ecc8d47565007fa518257
    descriptorMatcher = DescriptorMatcher::create(matcherName); // TODO replace with descriptorMatcher = ...

	if (descriptorMatcher.empty())
	{
		// TODO Décommentez les ligne suivantes une fois le
		// descriptorMatcher créé
        ostringstream msg;
        msg <<  "Can't create matcher [" << MatcherNames[matcherType]
            << "]";

        throw CvProcessorException(CvProcessorException::ALLOC_FAILURE,
                                   msg.str().c_str());
	}
	else
	{
		if (verboseLevel >= CvProcessor::VERBOSE_NOTIFICATIONS )
		{
			clog << "Created " << MatcherNames[matcherType] << " matcher"
				 << endl;
		}
	}

	resetMeanProcessTime();
}

/*
 * Gets the current match mode
 * @return the current match mode
 */
CvMatcher::MatchType CvMatcher::getMatcherMode() const
{
	return matcherMode;
}

/*
 * Sets a new matcher mode
 * @param matcherMode the new matcher mode to set
 */
void CvMatcher::setMatcherMode(const MatchType matcherMode)
{
	if (matcherMode < NBMATCHMODES)
	{
		this->matcherMode = matcherMode;

		if (verboseLevel >= CvProcessor::VERBOSE_NOTIFICATIONS)
		{
			cout << "Match mode set to " << MatchTypeNames[matcherMode] << endl;
		}
	}
	else
	{
		if (verboseLevel >= CvProcessor::VERBOSE_WARNINGS)
		{
			cerr << "unknown match mode : " << matcherMode << endl;
		}
	}

	resetMeanProcessTime();
}


/*
 * Indicates if the current matcher can match binary descriptors
 * @return true if the current matcher can match binary descriptors
 * and false otherwiser
 */
bool CvMatcher::matchBinary() const
{
	return MatcherBinary[matcherType];
}

/*
 * Indicates if the current matcher can match valued descriptors
 * @return true if the current matcher can match valued descriptors
 * and false otherwise
 */
bool CvMatcher::matchFloat() const
{
	return MatcherFloat[matcherType];
}


/*
 * Gets the matches
 * @return the current matches
 */
//const vector<DMatch> & CvMatcher::getMatches() const
//{
//	return matches;
//}

/*
 * Gets the number of matches
 * @return the current number of matches
 */
int CvMatcher::getNbMatches() const
{
	return matches.size();
}

/*
 * Gets the indices of train point set matches
 * @return the indices of train point set matches
 */
const vector<int> & CvMatcher::getModelMatchedIndexes() const
{
	return modelMatchedIndex;
}

/*
 * Gets the indices of query point set matches
 * @return the indices of query point set matches
 */
const vector<int> & CvMatcher::getSceneMatchedIndexes() const
{
	return sceneMatchedIndex;
}

/*
 * Gets the distances of matched points (in match space)
 * @return the distances of matched points (in match space)
 */
const vector<float> & CvMatcher::getMatchDistances() const
{
	return matchDistances;
}

/*
 * Gets the minimum match distance
 * @return the minimum match distance
 */
double CvMatcher::getMinMatchError() const
{
	return minMatchError;
}

/*
 * Gets the maximum match distance
 * @return the maximum match distance
 */
double CvMatcher::getMaxMatchError() const
{
	return maxMatchError;
}

/*
 * Gets the mean match distance
 * @return the mean match distance
 */
double CvMatcher::getMeanMatchError() const
{
	return meanMatchError;
}

/*
 * Gets the mean match distance
 * @return the mean match distance
 */
double CvMatcher::getStdMatchError() const
{
	return stdMatchError;
}

/*
 * Gets the current number of best matches to search for each descriptor
 * when using knnMatch
 * @return the current number of best matches to search for each
 * descriptor
 */
int CvMatcher::getKnn() const
{
	return knn;
}

/*
 * Sets a new number of best matches to search for each descriptor
 * when using knnMatch
 * @param knn the new number of best matches to search for each
 * descriptor
 */
void CvMatcher::setKnn(const int knn)
{
	if (knn > knnMax)
	{
		this->knn = knnMax;
	}
	else if (knn < 1)
	{
		this->knn = 1;
	}
	else
	{
		this->knn = knn;
	}

	resetMeanProcessTime();
}

/*
 * Gets the current radius threshold to search for each descriptor when
 * using radiusMatch
 * @return the current radius thresold to search for each descriptor
 */
double CvMatcher::getRadiusThreshold() const
{
	return radiusThreshold;
}

/*
 * Sets a new radius Threshold to search for each descriptor when using
 * radiusMatch
 * @param radiusThreshold the new radius threshold to set.
 * @post if the new threshold is contained within the bounds
 * [radiusThresholdMin..radiusThresholdMax] the new threshold is set,
 * otherwise min or max are set depending on the saturation side
 */
void CvMatcher::setRadiusThreshold(const double radiusThreshold)
{
	if (radiusThreshold > radiusThresholdMax)
	{
		this->radiusThreshold = radiusThresholdMax;
	}
	else if (radiusThreshold < radiusThresholdMin)
	{
		this->radiusThreshold = radiusThresholdMin;
	}
	else
	{
		this->radiusThreshold = radiusThreshold;
	}

	resetMeanProcessTime();
}

/*
 * Set the address of the new query/scene descriptors
 * @param sceneDescriptors the new query descriptors
 */
void CvMatcher::setSceneDescriptors(Mat *sceneDescriptors)
{
	assert (sceneDescriptors != NULL);

	this->sceneDescriptors = sceneDescriptors;
}

/*
 * Set the address of the new train/model descriptors
 * @param modelDescriptors the new train descriptors
 */
void CvMatcher::setModelDescriptors(Mat *modelDescriptors)
{
	assert (modelDescriptors != NULL);

	this->modelDescriptors = modelDescriptors;
}

/*
 * Update matches between modelDescriptors and sceneDescriptors
 * using the current matcher mode (simple, knn or radius)
 */
void CvMatcher::update()
{
//	clog << "Matcher update" << endl;

	if ((modelDescriptors != NULL) && (sceneDescriptors != NULL))
	{
		// clear previous matches
		matches.clear();

		// --------------------------------------------------------------------
		// Perform the match
		// --------------------------------------------------------------------

		if (!descriptorMatcher.empty()) // No empty pointer
		{
			clock_t start = clock();
			clock_t end;
			if (matcherMode < KNN_MATCH) // Simple match
			{
				// TODO match *sceneDescriptors with *modelDescriptors
				// with descriptorMatcher match method to produce matches
				// see http://docs.opencv.org/3.1.0/db/d39/classcv_1_1DescriptorMatcher.html#a695c0aceafc907c024c24a0b5cdff758
                descriptorMatcher->match(*sceneDescriptors,*modelDescriptors,matches);

			}
			else // knn or radius best cross match
			{
				/*
				 * Cross match consists in
				 * 	- match *sceneDescriptors and *modelDescriptors in matches12
				 * 	- match *modelDescriptors and *sceneDescriptors in matches21
				 * 	- Then find common matches between matches12 & matches21
				 * 		and push them to matches
				 */
				// Clear previous cross matches
				matches12.clear();
				matches21.clear();

				if (matcherMode == KNN_MATCH)
				{
					// Forward best matches
					// TODO Match *sceneDescriptors and *modelDescriptors to
					// produce matches12 with descriptorMatcher knnMatch method
					// with currennt knn
					// see http://docs.opencv.org/3.1.0/db/d39/classcv_1_1DescriptorMatcher.html#a004de1c3a73701701828da2bbc2c63a1
                    descriptorMatcher->knnMatch(*sceneDescriptors,*modelDescriptors,matches12,knn);

					if (matches12.size() > 0)
					{
						// Backward best matches
						// TODO Match *modelDescriptors and *sceneDescriptors to
						// produce matches21 with descriptorMatcher knnMatch method
						// with currennt knn
                        descriptorMatcher->knnMatch(*modelDescriptors,*sceneDescriptors,matches21,knn);
					}
				}
				else // Radius match
				{
					// Forward best matches
					// TODO Match *sceneDescriptors and *modelDescriptors to
					// produce matches12 with descriptorMatcher radiusMatch method
					// with current radiusThreshold
					// see http://docs.opencv.org/3.1.0/db/d39/classcv_1_1DescriptorMatcher.html#a2efcb4a32e740aa59cb6554aebea9af9
                    descriptorMatcher->radiusMatch(*sceneDescriptors,*modelDescriptors,matches12,radiusThreshold);

					if (matches12.size() > 0)
					{
						// Backward best matches
						// TODO Match *modelDescriptors and *sceneDescriptors to
						// produce matches21 with descriptorMatcher radiusMatch method
						// with current radiusThreshold
                        descriptorMatcher->radiusMatch(*modelDescriptors,*sceneDescriptors,matches21,radiusThreshold);
					}
				}

				// for all best matches (possibly limiting to only one best match
				// with knn=1)
				for (size_t m = 0; m < matches12.size(); m++)
				{
					// we are searching for a cross match
					bool findCrossCheck = false;

					// for each forward match in matches12[m]
					for (size_t fk = 0; fk < matches12[m].size(); fk++)
					{
						// fk forward match
						DMatch forward = matches12[m][fk];

						// We are looking for a reverse match in
						// matches21[forward.trainIdx]
						for (size_t bk = 0; bk < matches21[forward.trainIdx].size(); bk++)
						{
							// bk reverse match
							DMatch backward = matches21[forward.trainIdx][bk];

							// if forward match queryIdx is equal to
							// backward match trainIdx
							// Then we have found a cross match so add this DMatch
							// to matches by pushing "foward" match to matches vector,
							// set findCrossCheck to true and break both loop (fk AND bk)
							if (backward.trainIdx == forward.queryIdx)
							{
								// TODO push forward match to global matches
                                matches.push_back(forward);
								// We found a cross match so break inner loop
								findCrossCheck = true;
								break;
							}
						}
						// If we have found a cross match then also break outer loop
						if (findCrossCheck)
						{
							break;
						}
					}
				}
			}
			end = clock();

			processTime = end - start;
			meanProcessTime += processTime;
		}

		// --------------------------------------------------------------------
		// update internal attributes according to matches
		// --------------------------------------------------------------------
		size_t nbMatches = matches.size();
		modelMatchedIndex.clear();
		modelMatchedIndex.reserve(nbMatches);
		sceneMatchedIndex.clear();
		sceneMatchedIndex.reserve(nbMatches);
		matchDistances.clear();
		matchDistances.reserve(nbMatches);

		minMatchError = MinMatchErrorBound;
		maxMatchError = MaxMatchErrorBound;
		meanMatchError = 0.0;
		stdMatchError = 0.0;

		for (vector<DMatch>::const_iterator matchIt = matches.begin();
			 matchIt != matches.end();
			 ++matchIt)
		{
			DMatch match = *matchIt;
			float distance = match.distance;
			// ----------------------------------------------------------------
			// Build train and query matched indices vector
			// ----------------------------------------------------------------
			// TODO Push the trainIdx of the current match to modelMatchedIndex
            modelMatchedIndex.push_back(match.trainIdx);
			// TODO Push the queryIdx of the current match to sceneMatchedIndex
            sceneMatchedIndex.push_back(match.queryIdx);
			// Push the current match distance to the matchDistances
			matchDistances.push_back(distance);
			// ----------------------------------------------------------------
			// and post-Match statistics
			// ----------------------------------------------------------------
			if (distance < minMatchError)
			{
				minMatchError = distance;
			}
			if (distance > maxMatchError)
			{
				maxMatchError = distance;
			}
			meanMatchError += distance;
			stdMatchError += (distance * distance);
		}

		if (nbMatches > 0)
		{
			meanMatchError /= (double)nbMatches;
			stdMatchError /= (double)nbMatches;
			stdMatchError -= (meanMatchError * meanMatchError);
			stdMatchError = sqrt(stdMatchError);
		}
		else
		{
			meanMatchError = 0.0;
			stdMatchError = 0.0;
		}

		if (verboseLevel >= CvProcessor::VERBOSE_ACTIVITY)
		{
			clog << "Matcher matched " << nbMatches << " points out of " << endl
				 << "\t" << modelDescriptors->rows << " model points and "
				 << sceneDescriptors->rows<< " scene points "<< endl
				 << "\twith match score " << "[" << minMatchError
				 << " < " << meanMatchError << "(± " << stdMatchError
				 << ") < " << maxMatchError << "]"
				 << endl;
		}
	}
	else
	{
		if (verboseLevel >= CvProcessor::VERBOSE_ERRORS)
		{
			if (modelDescriptors == NULL)
			{
				cerr << "CvMatcher::update: Train descriptors are not set"
					 << endl;
			}

			if (sceneDescriptors == NULL)
			{
				cerr << "CvMatcher::update: Query descriptors are not set"
					 << endl;
			}
		}
	}
}

/*
 * Get the current verbose level
 * @return the current verbose level
 */
CvProcessor::VerboseLevel CvMatcher::getVerboseLevel() const
{
	return verboseLevel;
}

/*
 * Set new verbose level
 * @param level the new verobse level
 */
void CvMatcher::setVerboseLevel(const CvProcessor::VerboseLevel level)
{
	if ((level >= CvProcessor::VERBOSE_NONE) && (level < CvProcessor::NBVERBOSELEVEL))
	{
		verboseLevel = level;
	}
}

/*
 * Gets the matching time in ticks or ticks/scene point to match
 * depending on #timePerFeature attibute
 * @return number of ticks used to process current image in absolute
 * time or time per matched points depending on #timePerFeature attribute
 * @see #timePerFeature
 */
double CvMatcher::getProcessTime() const
{
	if (timePerFeature)
	{
		return (double) processTime / (double) MAX(1,matches.size());
	}
	else
	{
		return (double) processTime;
	}
}

/*
 * Gets the mean matching time in ticks or ticks/scene point to match
 * depending on #timePerFeature attibute
 * @return number of ticks used to process current image in absolute
 * time or time per matched points depending on #timePerFeature attribute
 * @see #timePerFeature
 */
double CvMatcher::getMeanProcessTime() const
{
	if (timePerFeature)
	{
		return meanProcessTime.mean() / (double) MAX(1,matches.size());
	}
	else
	{
		return meanProcessTime.mean();
	}
}

/*
 * Gets the mean matching time std in ticks or ticks/scene point to match
 * depending on #timePerFeature attibute
 * @return number of ticks used to process current image in absolute
 * time or time per matched points depending on #timePerFeature attribute
 * @see #timePerFeature
 */
double CvMatcher::getStdProcessTime() const
{
	if (timePerFeature)
	{
		return meanProcessTime.std() / (double) MAX(1,matches.size());
	}
	else
	{
		return meanProcessTime.std();
	}
}

/*
 * Reset mean and std process time to 0
 */
void CvMatcher::resetMeanProcessTime()
{
	meanProcessTime.reset();
}

/*
 * Indicates if matching time is per matched points in the current
 * image or absolute
 * @return
 */
bool CvMatcher::isTimePerFeature() const
{
	return timePerFeature;
}

/*
 * Sets Time per matched point processing time unit
 * @param value the time per feature value (true or false)
 */
void CvMatcher::setTimePerFeature(const bool value)
{
	timePerFeature = value;
}

