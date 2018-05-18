#ifndef MEANVALUE_H
#define MEANVALUE_H

#include <iostream>
#include <limits>
using namespace std;

/**
 * Mean and std value for type T values expressed in type R
 * @tparam T the type of value to compute mean and std with
 * @tparam R the type of value of mean and std computation
 * @example
 * @code
 *	MeanValue<clock_t, double>
 * @endcode
 * @author David Roussel
 * @date 2014/05/31
 */
template <typename T, typename R = T>
class MeanValue
{
	private:
		/**
		 * Elements sum
		 * @warning this implementation can lead to sum overflow
		 */
		T sum;

		/**
		 * Element square sum (used to get std)
		 * @warning this implementation can lead to sum2 overflow
		 */
		T sum2;

		/**
		 * Number of elements counted so far
		 */
		size_t count;

		/**
		 * Minimum recorded value
		 */
		T minValue;

		/**
		 * Maximum recorded value
		 */
		T maxValue;

		/**
		 * Value to reset minimum value to
		 * (a high value so that next value will have reasonable chances to be
		 * less than this value)
		 */
		const T resetMinValue;

		/**
		 * Value to reset maximum value to
		 * (a low value so that next value will have reasonable chances to be
		 * greater than this value)
		 */
		const T resetMaxValue;
	public:
		/**
		 * Constructor.
		 * Initialize sum & sum2 to T(0) and count to 0
		 * @param initialValue [optional] a T specimen can be provided in order
		 * to initialise sum and sum2 by copying the specimen
		 * @param initialMinimum [optional] initial value of minimum and minimum
		 * reset value
		 */
		MeanValue(const T & initialValue = static_cast<T>(0),
				  const T & initialMinimum = static_cast<T>(numeric_limits<T>::max()));

		/**
		 * Copy constructor
		 * @param mv the other mean value to copy
		 */
		MeanValue(const MeanValue<T, R> & mv);

		/**
		 * Move constructor
		 * @param mv the other mean value to copy
		 */
		MeanValue(MeanValue<T, R> && mv);

		/**
		 * Destructor
		 */
		virtual ~MeanValue();

		/**
		 * Function call operator
		 * @param value value to add to the values sum and values square sum
		 * @post elements count has been increased
		 */
		void operator ()(const T & value);

		/**
		 * Self increment operator
		 * @param value value to add to the values sum and values square sum
		 * @post elements count has been increased
		 * @note does the same thing as Function call operator
		 */
		void operator +=(const T & value);

		/**
		 * Copy operator from another mean value
		 * @param mv the mean value to copy
		 * @return a reference to the current mean value
		 */
		MeanValue<T, R> & operator =(const MeanValue<T, R> & mv);

		/**
		 * Move operator from another mean value
		 * @param mv the mean value to move
		 * @return a reference to the current mean value
		 */
		MeanValue<T, R> & operator =(MeanValue<T, R> && mv);

		/**
		 * Cast operator to result type
		 * @return the mean value
		 */
		operator R() const;

		/**
		 * Compute mean value : E(X) = sum/nbElements
		 * @return the mean value of all added elements.
		 */
		R mean() const;

		/**
		 * Compute standard deviation of values : sqrt(E(X^2) - E(X)^2)
		 * @return the standard deviation of all added elements.
		 */
		R std() const;

		/**
		 * Minimum recorded value accessor
		 * @return the minimum recorded value (until reset)
		 */
		T min() const;

		/**
		 * Maximum recorded value accessor
		 * @return the maximum recorded value (until reset)
		 */
		T max() const;

		/**
		 * Reset added values, square values and count to 0, and reset
		 * min & max values to their default values
		 */
		void reset();
};

/**
 * Output operator for MeanValue
 * @param out the output stream
 * @param mv the MeanValue to print on the output stream
 * @return a reference to the current output stream
 * @post put mean value ± std value on the stream
 */
template <typename T, typename R>
ostream & operator <<(ostream & out, const MeanValue<T, R> & mv);

#endif // MEANVALUE_H
