#include <cmath>
#include <opencv2/core/core.hpp>	// for MeanValue<cv::Mat, cv::Mat> specialization
#include "Pose.h"					// for MeanValue<Pose, Pose> specialization

#include "MeanValue.h"

/*
 * Constructor.
 * Initialize sum & sum2 to T(0) and count to 0
 * @param initialValue [optional] a T specimen can be provided in order
 * to initialise sum and sum2 by copying the specimen
 * @param initialMinimum [optional] initial value of minimum and minimum
 * reset value
 */
template <typename T, typename R>
MeanValue<T, R>::MeanValue(const T & initialValue,
						   const T & initialMinimum) :
	sum(initialValue),
	sum2(initialValue),
	count(0),
	minValue(initialMinimum),
	maxValue(initialValue),
	resetMinValue(initialMinimum),
	resetMaxValue(initialValue)
{
}

/*
 * Copy constructor
 * @param mv the other mean value to copy
 */
template <typename T, typename R>
MeanValue<T, R>::MeanValue(const MeanValue<T, R> & mv) :
	sum(mv.sum),
	sum2(mv.sum2),
	count(mv.count),
	minValue(mv.minValue),
	maxValue(mv.maxValue),
	resetMinValue(mv.resetMinValue),
	resetMaxValue(mv.resetMaxValue)
{
}

/*
 * Move constructor
 * @param mv the other mean value to copy
 */
template <typename T, typename R>
MeanValue<T, R>::MeanValue(MeanValue<T, R> && mv) :
	sum(mv.sum),
	sum2(mv.sum2),
	count(mv.count),
	minValue(mv.minValue),
	maxValue(mv.maxValue),
	resetMinValue(mv.resetMinValue),
	resetMaxValue(mv.resetMaxValue)
{
}

/*
 * Destructor
 */
template <typename T, typename R>
MeanValue<T, R>::~MeanValue()
{
}

/*
 * Function call operator
 * @param value value to add to the values sum and values square sum
 * @post elements count has been increased
 */
template <typename T, typename R>
void MeanValue<T, R>::operator ()(const T & value)
{
	sum += value;
	sum2 += value * value;
	count++;
	if (value > maxValue)
	{
		maxValue = value;
	}
	if (value < minValue)
	{
		minValue = value;
	}
}

/*
 * Self increment operator
 * @param value value to add to the values sum and values square sum
 * @post elements count has been increased
 * @note does the same thing as Function call operator
 */
template <typename T, typename R>
void MeanValue<T, R>::operator +=(const T & value)
{
	operator()(value);
}

/*
 * Copy operator from another mean value
 * @param mv the mean value to copy
 * @return a reference to the current mean value
 */
template <typename T, typename R>
MeanValue<T, R> & MeanValue<T, R>::operator =(const MeanValue<T, R> & mv)
{
	sum = mv.sum;
	sum2 = mv.sum2;
	count = mv.count;
	minValue = mv.minValue;
	maxValue = mv.maxValue;
	// can't copy resetMinValue & resetMaxValue 'cause they're constants

	return *this;
}

/*
 * Move operator from another mean value
 * @param mv the mean value to move
 * @return a reference to the current mean value
 */
template <typename T, typename R>
MeanValue<T, R> & MeanValue<T, R>::operator =(MeanValue<T, R> && mv)
{
	sum = mv.sum;
	sum2 = mv.sum2;
	count = mv.count;
	minValue = mv.minValue;
	maxValue = mv.maxValue;
	// can't copy resetMinValue & resetMaxValue 'cause they're constants

	return *this;
}

/*
 * Cast operator to result type
 * @return the mean value
 */
template <typename T, typename R>
MeanValue<T, R>::operator R() const
{
	return mean();
}

/*
 * Compute mean value : E(X) = sum/nbElements
 * @return the mean value of all added elements.
 */
template <typename T, typename R>
R MeanValue<T, R>::mean() const
{
	if (count != 0)
	{
		return R(sum / (R) count);
	}
	else
	{
		return R(0);
	}
}

/*
 * Compute standard deviation of values : sqrt(E(X^2) - E(X)^2)
 * @return the standard deviation of all added elements.
 */
template <typename T, typename R>
R MeanValue<T, R>::std() const
{
	if (count != 0)
	{
		R ex = mean();
		double ex2 = sum2 / (double) count;
		return R(sqrt(ex2 - double(ex * ex)));
	}
	else
	{
		return R(0);
	}
}

/*
 * Minimum recorded value accessor
 * @return the minimum recorded value (until reset)
 */
template <typename T, typename R>
T MeanValue<T, R>::min() const
{
	if (count != 0)
	{
		return minValue;
	}
	else
	{
		return T(0);
	}
}

/*
 * Maximum recorded value accessor
 * @return the maximum recorded value (until reset)
 */
template <typename T, typename R>
T MeanValue<T, R>::max() const
{
	if (count != 0)
	{
		return maxValue;
	}
	else
	{
		return T(0);
	}
}

/*
 * Reset added values, square values and count to 0
 */
template <typename T, typename R>
void MeanValue<T, R>::reset()
{
	sum = T(0);
	sum2 = T(0);
	count = 0;
	minValue = resetMinValue;
	maxValue = resetMaxValue;
}

/*
 * Output operator for MeanValue
 * @param out the output stream
 * @param mv the MeanValue to print on the output stream
 * @return a reference to the current output stream
 * @post put mean value ± std value on the stream
 */
template <typename T, typename R>
ostream & operator <<(ostream & out, const MeanValue<T, R> & mv)
{
	out << mv.mean() << " ± " << mv.std() << " [" << mv.min() << "..."
		<< mv.max() << "]";

	return out;
}

// ----------------------------------------------------------------------------
// Specializations for MeanValue<cv::Mat, cv::Mat>
// ----------------------------------------------------------------------------

/**
 * Function call operator (specialization for MeanValue<cv::Mat, cv::Mat>)
 * @param value value to add to the values sum and values square sum
 * @post elements count has been increased
 */
template <>
void MeanValue<cv::Mat>::operator ()(const cv::Mat & value)
{
	sum += value;
	sum2 += value * value.t();
	count++;
	int rows = value.rows;
	int cols = value.cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			/*
			 * FIXME Caution accessing pixels values in double only works
			 * with matrices of double
			 */
			double & currentMin = minValue.at<double>(i, j);
			double & currentMax = maxValue.at<double>(i, j);
			double currentValue = value.at<double>(i, j);
			if (currentValue < currentMin)
			{
				currentMin = currentValue;
			}
			if (currentValue > currentMax)
			{
				currentMax = currentValue;
			}
		}
	}
}

/**
 * Compute mean value (specialization for MenValue<cv::Mat, cv::Mat>):
 * E(X) = sum/nbElements
 * @return the mean value of all added elements.
 */
template <>
cv::Mat MeanValue<cv::Mat>::mean() const
{
	if (count != 0)
	{
		return cv::Mat(sum * double(1.0/(double)count));
	}
	else
	{
		return cv::Mat(sum * double(0));
	}
}

/**
 * Compute standard deviation of values (specialization for
 * MeanValue<cv::Mat; cv::Mat>): sqrt(E(X^2) - E(X)^2)
 * @return the standard deviation of all added elements.
 */
template <>
cv::Mat MeanValue<cv::Mat>::std() const
{
	if (count != 0)
	{
		cv::Mat ex = mean();
		cv::Mat ex2 = sum2 * double(1.0 / (double) count);
		int rows = sum.rows;
		int cols = sum.cols;
		cv::Mat result(rows, cols, CV_64FC1);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				double exij = ex.at<double>(i,j);
				result.at<double>(i,j) = sqrt( ex2.at<double>(i,j) - (exij * exij) );
			}
		}

		return result;
	}
	else
	{
		return cv::Mat(sum2 * double(0.0));
	}
}

/**
 * Minimum recorded value accessor (specialization for
 * MeanValue<cv::Mat; cv::Mat>)
 * @return the minimum recorded value (until reset)
 */
template <>
cv::Mat  MeanValue<cv::Mat>::min() const
{
	if (count != 0)
	{
		return minValue;
	}
	else
	{
		return cv::Mat();
	}
}

/**
 * Maximum recorded value accessor (specialization for
 * MeanValue<cv::Mat; cv::Mat>)
 * @return the maximum recorded value (until reset)
 */
template <>
cv::Mat MeanValue<cv::Mat>::max() const
{
	if (count != 0)
	{
		return maxValue;
	}
	else
	{
		return cv::Mat();
	}
}

/**
 * Reset added values (specialization for MeanValue<cv::Mat, cv::Mat>),
 * square values and count to 0
 */
template <>
void MeanValue<cv::Mat>::reset()
{
	sum *= double(0);
	sum2 *= double(0);
	count = 0;
	minValue = resetMinValue;
	maxValue = resetMaxValue;
}

// ----------------------------------------------------------------------------
// Specializations for MeanValue<Pose, Pose>
// ----------------------------------------------------------------------------

/**
 * Compute mean value (specialization for MenValue<Pose, Pose>):
 * E(X) = sum/nbElements
 * @return the mean value of all added elements.
 */
template <>
Pose MeanValue<Pose, Pose>::mean() const
{
	if (count != 0)
	{
		return Pose(sum / double(count));
	}
	else
	{
		return Pose();
	}
}

/**
 * Compute standard deviation of values (specialization for
 * MeanValue<Pose; Pose>): sqrt(E(X^2) - E(X)^2)
 * @return the standard deviation of all added elements.
 */
template <>
Pose MeanValue<Pose, Pose>::std() const
{
	if (count != 0)
	{
		Pose ex = mean();
		Pose ex2 = sum2 / double(count);
		Pose ssum = ex2 - (ex * ex);

		for (size_t i = size_t(Pose::X); i < size_t(Pose::NBCOORDS); i++)
		{
			ssum[i] = sqrt(ssum[i]);
		}

		return ssum;
	}
	else
	{
		return Pose();
	}
}

/**
 * Minimum recorded value accessor (specialization for
 * MeanValue<Pose; Pose>)
 * @return the minimum recorded value (until reset)
 */
template <>
Pose  MeanValue<Pose>::min() const
{
	if (count != 0)
	{
		return minValue;
	}
	else
	{
		return Pose();
	}
}

/**
 * Maximum recorded value accessor (specialization for
 * MeanValue<Pose; Pose>)
 * @return the minimum recorded value (until reset)
 */
template <>
Pose MeanValue<Pose>::max() const
{
	if (count != 0)
	{
		return maxValue;
	}
	else
	{
		return Pose();
	}
}

// ----------------------------------------------------------------------------
// Template protoinstanciations for
//	- int
//	- clock_t (unsigned long)
//	- float
//	- double
// 	- cv::Mat
//	- Pose
// ----------------------------------------------------------------------------

// Proto instanciations
template class MeanValue<int, double>;
template class MeanValue<clock_t, double>;
template class MeanValue<float, double>;
template class MeanValue<double>;
template class MeanValue<int, float>;
template class MeanValue<clock_t, float>;
template class MeanValue<float>;
template class MeanValue<double, float>;
template class MeanValue<cv::Mat>;
template class MeanValue<Pose>;

// Output operators proto-instanciations
template ostream & operator << (ostream &, const MeanValue<int, double> &);
template ostream & operator << (ostream &, const MeanValue<clock_t, double> &);
template ostream & operator << (ostream &, const MeanValue<float, double> &);
template ostream & operator << (ostream &, const MeanValue<double> &);
template ostream & operator << (ostream &, const MeanValue<int, float> &);
template ostream & operator << (ostream &, const MeanValue<clock_t, float> &);
template ostream & operator << (ostream &, const MeanValue<float> &);
template ostream & operator << (ostream &, const MeanValue<double, float> &);
template ostream & operator << (ostream &, const MeanValue<cv::Mat> &);
template ostream & operator << (ostream &, const MeanValue<Pose> &);
