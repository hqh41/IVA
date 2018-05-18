/*
 * CvMatcher.h
 *
 *  Created on: 1 mars 2012
 *	  Author: davidroussel
 */

#ifndef CVMATCHER_H_
#define CVMATCHER_H_

#include <string>
#include <ctime>	// for clock_t
#include <vector>
#include <utility>
using namespace std;

#include <opencv2/features2d.hpp>	// DescriptorMatcher
using namespace cv;

#include "CvProcessor.h"	// for VerboseLevel
#include "CvProcessorException.h"

/**
 * OpenCV Matcher Match descriptors extracted on two sets of key points
 * in order to produce a match vector
 * @note Please note that all virtual methods may be reimplemented in
 * CvMatcher progeny such as QcvMatcher which will reimplement these
 * methods with added Qt capabilities (such as signals and slots)
 * @author David Roussel
 * @date 2012/03/01
 */
class CvMatcher
{
	public:
		/**
		 * Descriptor Matcher Type
		 */
		typedef enum
		{
			/**
			 * BruteForce : Brute Force Matcher (with L2 dist).
			 * works with any descriptors.
			 */
			BRUTEFORCE_MATCHER = 0,
			/**
			 * BruteForce-L1 : Brute Force Matcher (with L1 dist).
			 * works with any descriptors
			 */
			BRUTEFORCE_L1 = 1,
			/**
			 * BruteForce-Hamming : Brute Force Matcher (with Hamming dist).
			 * Only works with binary descriptors.
			 */
			BRUTEFORCE_HAMMING = 2,
			/**
			 * BruteForce-HammingLUT : Brute force Matcher (With Hamming LUT)
			 * Only works with binary descriptors.
			 */
			BRUTEFORCE_HAMMINGLUT = 3,
			/**
			 * FlannBased : Flann based matcher (Fast Library Approximate Nearest Neighbor).
			 * Only works with floating point valued descriptors
			 */
			FLANNBASED_MATCHER = 4,
			/**
			 * Matchers number
			 */
			MATCHER_NUMBER = 5
		} MatcherType;

		/**
		 * Descriptors matcher names to compare with arguments:
		 *	- "BruteForce",
		 *	- "BruteForce-L1",
		 *	- "BruteForce-Hamming",
		 *	- "BruteForce-Hamming(2)",
		 *	- "FlannBased"
		 */
		static const string MatcherNames[MATCHER_NUMBER];

		/**
		 * Matchers capability to support binary content descriptors:
		 *	- Brute force matcher supports binary descriptors: true,
		 *	- Brute force L1 matcher supports binary descriptors: true,
		 *	- Brute force Hamming supports binary descriptors: true,
		 *	- Brute force Hamming LUT supports binary descriptors: true,
		 *	- Flann based DOES NOT support binary descriptors: false
		 */
		static const bool MatcherBinary[MATCHER_NUMBER];

		/**
		 * Matchers capability to support floating points numbers content
		 * descriptors:
		 *	- Brute force matcher supports valued descriptors: true,
		 *	- Brute force L1 matcher supports valued descriptors: true,
		 *	- Brute force Hamming DOES NOT support valued descriptors: false,
		 *	- Brute force Hamming LUT DOES NOT support valued descriptors: false,
		 *	- Flann based supports valued descriptors: true
		 */
		static const bool MatcherFloat[MATCHER_NUMBER];

		/**
		 * Match type to perform
		 */
		typedef enum
		{
			/**
			 * Find the best match for each descriptor from a query set with train
			 * descriptors: match should be performed with matcher->match(...)
			 */
			SIMPLE_MATCH = 0,
			/**
			 * Find the k best matches for each descriptor from a query set with
			 * train descriptors: match should be performed with matcher->knnMatch(...)
			 * Since knnMatch produces vector<vector<DMatch> > we should cross match
			 * knnMatch(query,train) and knnMatch(train,query) to find cross matches
			 * and put them in a vector<DMatch>
			 */
			KNN_MATCH = 1,
			/**
			 * Find the best matches for each query descriptor which have distance less
			 * than given threshold: match should be performed with
			 * matcher->radiusMatch(...).
			 * But a threshold should be found first
			 * Since radiusMatch produces vector<vector<DMatch> > we should cross match
			 * radiusMatch(query,train) and radiusMatch(train,query) to find cross matches
			 * and put them in a vector<DMatch>
			 */
			RADIUS_MATCH = 2,
			/**
			 * Number of match modes
			 */
			NBMATCHMODES = 3
		} MatchType;

		/**
		 * Matching types names:
		 *	- "Simple Match",
		 *	- "Cross Best Match",
		 *	- "Radius Best Match"
		 */
		static const string MatchTypeNames[NBMATCHMODES];

	protected:
		/**
		 * Matcher Type
		 */
		MatcherType matcherType;

		/**
		 * The Matcher name to create the Matcher with
		 * DescriptorMatcher::create(name)
		 */
		string matcherName;

		/**
		 * The Matching mode (simple, cross, radius)
		 */
		MatchType matcherMode;

		/*
		 * TODO add a temporal match boolean and accessors
		 */

		/**
		 * Descriptor Matcher.
		 * Ptr is needed here since the descriptor matcher is obtained
		 * through the DescriptorMatcher::create factory method
		 */
		Ptr<DescriptorMatcher> descriptorMatcher;

		/**
		 * Training or Models descriptors
		 */
		Mat * modelDescriptors;

		/**
		 * Query or Scene descriptors
		 */
		Mat * sceneDescriptors;

		/**
		 * Match vector
		 */
		vector<DMatch> matches;

		/**
		 * Forward best matches (when using cross match)
		 */
		vector<vector<DMatch> > matches12;

		/**
		 * Backward best matches (when using cross match)
		 */
		vector<vector<DMatch> > matches21;

		/**
		 * Indices in model point set that are matched
		 */
		vector<int> modelMatchedIndex;

		/**
		 * Indices in query point set that are matched
		 */
		vector<int> sceneMatchedIndex;

		/**
		 * distances between matched points
		 */
		vector<float> matchDistances;

		/**
		 * Minimum match error (in terms of distance (DMatch.distance))
		 */
		double minMatchError;

		/**
		 * Maximum match error (in terms of distance (DMatch.distance))
		 */
		double maxMatchError;

		/**
		 * Mean match error (in terms of distance (DMatch.distance))
		 */
		double meanMatchError;

		/**
		 * Standard deviation match error (in terms of distance (DMatch.distance))
		 */
		double stdMatchError;

		/**
		 * Minimum match error absolute upper bound [1.0]
		 */
		static const double MinMatchErrorBound;

		/**
		 * Maximum match error absolute lower bound [0.0]
		 */
		static const double MaxMatchErrorBound;

		/**
		 * number of best matches to find when using knnMatch
		 */
		int knn;

		/**
		 * Maximum number of best matches (5 or 10)
		 */
		static const int knnMax;

		/**
		 * radius threshold to apply when using radiusMatch
		 */
		double radiusThreshold;

		/**
		 * Default radius threshold value
		 */
		static const double radiusThresholdDefault;

		/**
		 * Minimum radius threshold
		 */
		static const double radiusThresholdMin;

		/**
		 * Maximum radius threshold
		 */
		static const double radiusThresholdMax;

		/**
		 * Steps to radiusThreshold values
		 */
		static const double radiusThresholdStep;

		/**
		 * Verbose level to show messages
		 */
		CvProcessor::VerboseLevel verboseLevel;

		/**
		 * Time in ticks/scene point used to match scene points to model points
		 */
		clock_t processTime;

		/**
		 * Mean/std time in ticks/scene point used to match scene points to
		 * model points
		 */
		MeanValue<clock_t, double> meanProcessTime;

		/**
		 * Indicates if time should be measured per matched point or in absolute
		 * time.
		 */
		bool timePerFeature;

	public:
		/**
		 * OpenCV Matcher constructor
		 * @param matcherType type of matcher
		 * @param matcherMode type of match
		 * @param verboseLevel verbosity
		 */
		CvMatcher(const MatcherType matcherType = BRUTEFORCE_MATCHER,
				  const MatchType matcherMode = SIMPLE_MATCH,
				  const CvProcessor::VerboseLevel verboseLevel = CvProcessor::VERBOSE_NONE);

		/**
		 * OpenCV Matcher destructor
		 */
		virtual ~CvMatcher();

		/**
		 * Update matches between modelDescriptors and sceneDescriptors
		 * using the current matcher mode (simple, knn or radius)
		 */
		virtual void update();

		/**
		 * Gets the current Matcher type
		 * @return the current Matcher type
		 */
		MatcherType getMatcherType() const;

		/**
		 * Sets a new matcher type
		 * @param matcherType the new matcher type to set
		 * @param full true when matches and matcher needs to be cleaned up
		 * first
		 * @post the old DescriptorMatcher has been released and a new one
		 * has been created
		 * @throw CvProcessorException if matcher is empty because it
		 * couldn't be created properly
		 */
		virtual void setMatcherType(const MatcherType matcherType,
									const bool full = true)
			throw (CvProcessorException);

		/**
		 * Gets the current match mode
		 * @return the current match mode
		 */
		MatchType getMatcherMode() const;

		/**
		 * Sets a new matcher mode
		 * @param matcherMode the new matcher mode to set
		 */
		virtual void setMatcherMode(const MatchType matcherMode);

		/**
		 * Indicates if the current matcher can match binary descriptors
		 * @return true if the current matcher can match binary descriptors
		 * and false otherwiser
		 */
		bool matchBinary() const;

		/**
		 * Indicates if the current matcher can match valued descriptors
		 * @return true if the current matcher can match valued descriptors
		 * and false otherwise
		 */
		bool matchFloat() const;

//		/**
//		 * Gets the matches
//		 * @return the current matches
//		 */
//		const vector<DMatch> & getMatches() const;

		/**
		 * Gets the number of matches
		 * @return the current number of matches
		 */
		int getNbMatches() const;

		/*
		 * TODO add
		 * 	bool getTemporalMatch() const;
		 * 	void setTemporalMatch(const bool value);
		 */

		/**
		 * Gets the indices of train point set matches
		 * @return the indices of train point set matches
		 * retreiving points or keypoints from these index is easy:
		 * @code
		 * vector<SomePoint> points;
		 * // matcher matches points descriptors corresponding to points
		 * ...
		 * vector<int> index = matcher.getModelMatchedIndexes();
		 * SomePointpoints[index[i]]
		 * @endcode
		 */
		const vector<int> & getModelMatchedIndexes() const;

		/**
		 * Gets the indices of query point set matches
		 * @return the indices of query point set matches
		 */
		const vector<int> & getSceneMatchedIndexes() const;

		/**
		 * Gets the distances of matched points (in match space)
		 * @return the distances of matched points (in match space)
		 */
		const vector<float> & getMatchDistances() const;

		/**
		 * Gets the minimum match distance
		 * @return the minimum match distance
		 */
		double getMinMatchError() const;

		/**
		 * Gets the maximum match distance
		 * @return the maximum match distance
		 */
		double getMaxMatchError() const;

		/**
		 * Gets the mean match distance
		 * @return the mean match distance
		 */
		double getMeanMatchError() const;

		/**
		 * Gets the mean match distance
		 * @return the mean match distance
		 */
		double getStdMatchError() const;

		/**
		 * Gets the current number of best matches to search for each descriptor
		 * when using knnMatch
		 * @return the current number of best matches to search for each
		 * descriptor
		 */
		int getKnn() const;

		/**
		 * Sets a new number of best matches to search for each descriptor
		 * when using knnMatch
		 * @param knn the new number of best matches to search for each
		 * descriptor
		 */
		virtual void setKnn(const int knn);

		/**
		 * Gets the current radius threshold to search for each descriptor when
		 * using radiusMatch
		 * @return the current radius thresold to search for each descriptor
		 */
		double getRadiusThreshold() const;

		/**
		 * Sets a new radius Threshold to search for each descriptor when using
		 * radiusMatch
		 * @param radiusThreshold the new radius threshold to set.
		 * @post if the new threshold is contained within the bounds
		 * [radiusThresholdMin..radiusThresholdMax] the new threshold is set,
		 * otherwise min or max are set depending on the saturation side
		 */
		virtual void setRadiusThreshold(const double radiusThreshold);

		/**
		 * Set the address of the new query/scene descriptors
		 * @param sceneDescriptors the new query descriptors
		 */
		virtual void setSceneDescriptors(Mat *sceneDescriptors);

		/**
		 * Set the address of the new train/model descriptors
		 * @param modelDescriptors the new train descriptors
		 */
		virtual void setModelDescriptors(Mat *modelDescriptors);

		/**
		 * Get the current verbose level
		 * @return the current verbose level
		 */
		CvProcessor::VerboseLevel getVerboseLevel() const;

		/**
		 * Set new verbose level
		 * @param level the new verobse level
		 */
		virtual void setVerboseLevel(const CvProcessor::VerboseLevel level);

		/**
		 * Gets the matching time in ticks or ticks/scene point to match
		 * depending on #timePerFeature attibute
		 * @return number of ticks used to process current image in absolute
		 * time or time per matched points depending on #timePerFeature attribute
		 * @see #timePerFeature
		 */
		double getProcessTime() const;

		/**
		 * Gets the mean matching time in ticks or ticks/scene point to match
		 * depending on #timePerFeature attibute
		 * @return number of ticks used to process current image in absolute
		 * time or time per matched points depending on #timePerFeature attribute
		 * @see #timePerFeature
		 */
		double getMeanProcessTime() const;

		/**
		 * Gets the mean matching time std in ticks or ticks/scene point to match
		 * depending on #timePerFeature attibute
		 * @return number of ticks used to process current image in absolute
		 * time or time per matched points depending on #timePerFeature attribute
		 * @see #timePerFeature
		 */
		double getStdProcessTime() const;

		/**
		 * Reset mean and std process time to 0
		 */
		void resetMeanProcessTime();

		/**
		 * Indicates if matching time is per matched points in the current
		 * image or absolute
		 * @return
		 */
		bool isTimePerFeature() const;

		/**
		 * Sets Time per matched point processing time unit
		 * @param value the time per feature value (true or false)
		 */
		virtual void setTimePerFeature(const bool value);

		/**
		 * Indicates if the current matching leads to the recognition of the
		 * model in the image
		 * @return the current recognition state
		 */
		bool isRecognized() const;
};

#endif /* CVMATCHER_H_ */
