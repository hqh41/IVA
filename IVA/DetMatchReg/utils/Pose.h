/*
 * Pose.h
 *
 *  Created on: 25 juin 2014
 *      Author: davidroussel
 */

#ifndef POSE_H_
#define POSE_H_

#include <exception>
#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
using namespace cv;

/**
 * A Class to represent a camera pose (position + orientation) expressed as
 * two triplets (x, y, z) for position and (rx, ry, rz) for euler rotation
 * angles.
 * @author David Roussel
 * @date 2014/06/25
 */
class Pose
{
	public:
		/**
		 * Shortcuts to access pose elements
		 */
		typedef enum
		{
			X = 0,      //!< x coordinate index
			Y = 1,      //!< y coordinate index
			Z = 2,      //!< z coordinate index
			RX = 3,     //!< rotation around x axis index
			RY = 4,     //!< rotation around y axis index
			RZ = 5,     //!< rotation around z axis index
			NBCOORDS = 6//!< Number of elements in the pose
		} CoordIndex;
	private:
		/**
		 * the six coordinates of the pose
		 */
		double coord[NBCOORDS];

		/**
		 * All poses common epsilon to compare positions values
		 */
		static double positionEpsilon;

		/**
		 * All poses common epsilon to compare rotations values
		 */
		static double orientationEpsilon;

	public:
//		/*
//		 * Pose valued constructor
//		 * @param x the x coordinate
//		 * @param y the y coordinate
//		 * @param z the z coordinate
//		 * @param rx the rotation around x axis
//		 * @param ry the rotation around y axis
//		 * @param rz the rotation around z axis
//		 */
//		Pose(const double x,
//		     const double y,
//		     const double z,
//		     const double rx,
//		     const double ry,
//		     const double rz);

		/**
		 * Pose constructor from translation and rotation values such as
		 * provided by solvePNP (1 line,3 columns,CV_64FC1 matrices)
		 * @param translation vector (1x3 matrix)
		 * @param rotation vector (1x3 matrix)
		 * @throw exception if translation or rotation are not of the right
		 * type (CV_64FC1) or dimensions (1x3)
		 */
		Pose(const Mat & translation, const Mat & rotation) throw (exception);

		/**
		 * Pose constructor from pose values such as
		 * provided by solvePNP (1 line,3 columns,CV_64FC1 matrices)
		 * @param pose vector (1x6 matrix)
		 * @throw exception if pose is not of the right
		 * type (CV_64FC1) or dimensions (1x6)
		 */
		Pose(const Mat & pose) throw (exception);

		/**
		 * Copy constructor
		 * @param pose the other pose to copy
		 */
		Pose(const Pose & pose);

		/**
		 * Pose fill constructor
		 * @param value the value for every coordinates of the pose
		 * @post all coordinates of the pose are filled with value
		 * @note this particular constructor should be used in order to
		 * construct a scale factor for other poses and apply the multiply
		 * or divide operator
		 * @code
		 * Pose p1(...);
		 * Pose scale(2.0);
		 * Pose p2 = p1 * scale;
		 * @endcode
		 */
		Pose(const double value = 0.0);

		/**
		 * Pose destructor
		 */
		virtual ~Pose();

		/**
		 * Update current pose with new translation & rotation values
		 * @param translation new translation
		 * @param rotation new rotation
		 * @throw exception if translation or rotation are not of the right
		 * type (CV_64FC1) or dimensions (1x3)
		 */
		void update(const Mat & translation, const Mat & rotation) throw (exception);

		/**
		 * Update current pose
		 * @param pose new pose value [1x6] vector
		 * @throw exception if pose is not of the right type (CV_64FC1)
		 * or dimensions (1x6)
		 */
		void update(const Mat & pose) throw (exception);

		/**
		 * Copy operator
		 * @param pose the other pose to copy
		 * @return a reference to this after copy
		 */
		Pose & operator =(const Pose & pose);

		/**
		 * Pose comparison operator
		 * @param pose the cother pose to compare
		 * @return true if each position coordinates compare less than
		 * positionEpsilon and each orientationEpsilon compares less than
		 * orientationEpsilon
		 */
		bool operator ==(const Pose & pose) const;

		/**
		 * Pose difference operator
		 * @param pose the cother pose to compare
		 * @return true if each position coordinates compare less than
		 * positionEpsilon and each orientationEpsilon compares less than
		 * orientationEpsilon
		 */
		bool operator !=(const Pose & pose) const;

		/**
		 * Pose less than operator
		 * @param pose the other pose to compare
		 * @return true if this pose is lexicographically smaller than
		 * the other.
		 * Where lexicographical compare means that if this->x < pose.x then we
		 * return true without comparing further coordinates.
		 */
		bool operator <(const Pose & pose) const;

		/**
		 * Pose less or equal operator
		 * @param pose the other pose to compare
		 * @return true if this pose is lexicographically smaller or equal to
		 * the other.
		 */
		bool operator <=(const Pose & pose) const;


		/**
		 * Pose greater than operator
		 * @param pose the other pose to compare
		 * @return true if this pose is lexicographically greater than
		 * the other.
		 * Where lexicographical compare means that if this->x < pose.x then we
		 * return true without comparing further coordinates.
		 */
		bool operator >(const Pose & pose) const;

		/**
		 * Pose greater or equal operator
		 * @param pose the other pose to compare
		 * @return true if this pose is lexicographically greater or equal to
		 * the other.
		 */
		bool operator >=(const Pose & pose) const;

		/**
		 * Pose self addition
		 * @param pose the other pose to add to the current pose
		 * @return a reference to this
		 */
		Pose & operator +=(const Pose & pose);

		/**
		 * Pose self substraction
		 * @param pose the other pose to substract to the current pose
		 * @return a reference to this
		 */
		Pose & operator -=(const Pose & pose);

		/**
		 * Pose self multiplication with other pose
		 * @param pose the other pose to mulitply the current pose
		 * @return a reference to this
		 */
		Pose & operator *=(const Pose & pose);

		/**
		 * Pose self multiplication with scalar
		 * @param value the scale factor to apply to pose coordinates
		 * @return a reference to this
		 */
		Pose & operator *=(const double value);

		/**
		 * Pose self division
		 * @param pose the other pose to divide the current pose
		 * @return a reference to this
		 */
		Pose & operator /=(const Pose & pose);

		/**
		 * Pose self division with scalar
		 * @param value the scale factor to apply to pose coordinates
		 * @return a reference to this
		 */
		Pose & operator /=(const double value);

		/**
		 * Pose add operator
		 * @param pose the other pose to add to the current pose
		 * @return a new pose contaning the addition of the current and
		 * other pose
		 */
		Pose operator +(const Pose & pose) const;

		/**
		 * Pose substract operator
		 * @param pose the other pose to substract to the current pose
		 * @return a new pose contaning the substraction of the current and
		 * other pose
		 */
		Pose operator -(const Pose & pose) const;

		/**
		 * Pose multiply operator with other pose
		 * @param pose the other pose to multiply to the current pose
		 * @return a new pose contaning the multiplication of the current and
		 * other pose
		 */
		Pose operator *(const Pose & pose) const;

		/**
		 * Pose multiply operator with scalar
		 * @param value the scale factor to apply to pose coordinates
		 * @return a new pose contaning the multiplication of the current pose
		 * by factor
		 */
		Pose operator *(const double value) const;

		/**
		 * Pose divide operator
		 * @param pose the other pose to divide to the current pose
		 * @return a new pose contaning the division of the current and
		 * other pose
		 */
		Pose operator /(const Pose & pose) const;

		/**
		 * Pose divide operator with scalar
		 * @param value the scale factor to apply to pose coordinates
		 * @return a new pose contaning the multiplication of the current pose
		 * by factor
		 */
		Pose operator /(const double value) const;

		/**
		 * Bracket operator to access specific pose element (in r/w mode)
		 * @param index the index of the required element
		 * @return a reference to the required element
		 * @throws an exception when the index is invalid
		 */
		double & operator [](size_t index) throw (exception);

		/**
		 * Bracket operator to access specific pose element (in read only mode)
		 * @param index the index of the required element
		 * @return a reference to the required element
		 * @throws an exception when the index is invalid
		 */
		double operator [](size_t index) const throw (exception);

		/**
		 * Translation vector
		 * @param transpose triggers vector transposition in order to obtain
		 * a (3x1) vector instead of a (1x3) vector
		 * @return the translation vector (1x3) if not transposed or (3x1) if
		 * transposed
		 */
		Mat translationVector(const bool transpose = false) const;

		/**
		 * Rotation vector
		 * @return the rotation vector (1x3)
		 */
		Mat rotationVector() const;

		/**
		 * Return rotation as a matrix rotation (3x3) instead of a vector (1x3).
		 * rotation vector:
		 * \f[
		 * r = \left( r_{x}, r_{y}, r_{z} \right)
		 * \f]
		 * rotation matrix:
		 * \f[
		 * \theta \leftarrow norm(r)
		 * \f]
		 * \f[
		 * r \leftarrow \frac{r}{\theta}
		 * \f]
		 * \f[
		 *	R =
		 *	cos(\theta) \left(
		 *		\begin{array}{ccc}
		 *		1 & 0 & 0\\
		 *		0 & 1 & 0\\
		 *		0 & 0 & 1\\
		 *		\end{array}
		 *	\right) + (1 - cos(\theta)) r r^{t} + sin(\theta)
		 *	\left(
		 *		\begin{array}{ccc}
		 *		0 & -r_{z} & r_{y}\\
		 *		r_{z} & 0 & -r_{x}\\
		 *		-r_{y} & r_{x} & 0\\
		 *		\end{array}
		 *	\right)
		 * \f]
		 * @return a matrix rotation
		 */
		Mat rotationMatrix() const;

		/**
		 * Homogeneous (4x4) matrix containing pose, such as
		 * \f[
		 * Pose = \left(
		 * 	\begin{array}{cccc}
		 * 		r_{11} & r_{12} & r_{13} & t_{1}\\
		 * 		r_{21} & r_{22} & r_{23} & t_{2}\\
		 * 		r_{31} & r_{32} & r_{33} & t_{3}\\
		 * 		0      & 0      & 0      & 1\\
		 * 	\end{array}
		 * \right) =
		 * \left(
		 * 	\begin{array}{cccc}
		 * 		       & \vdots         &        & \vdots\\
		 * 		\dots  & R_{3 \times 3} & \dots  & T_{3 \times 1}\\
		 * 		       & \vdots         &        & \vdots\\
		 * 		0      & 0              & 0      & 1\\
		 * 	\end{array}
		 * \right)
		 * \f]
		 * @return the pose 4x4 matrix
		 */
		Mat poseMatrix() const;

		/**
		 * Pose (translation & rotation) vector (6x1) or (1x6), such as
		 * \f[
		 * Pose = (x, y, z, r_x, r_y, r_z)_{T}
		 * \f]
		 * @param transpose if transpose is false then returns a (6x1) matrix
		 * and if transpose is true returns a (1x6) matrix.
		 * @return the pose as a monodimensional matrix
		 */
		Mat poseVector(const bool transpose = false) const;

		/**
		 * Compute the inverse pose.
		 * such that if pose is expressed as a 4x4 matrix
		 * \f[
		 * Pose = \left(
		 * 	\begin{array}{cccc}
		 * 		r_{11} & r_{12} & r_{13} & t_{1}\\
		 * 		r_{21} & r_{22} & r_{23} & t_{2}\\
		 * 		r_{31} & r_{32} & r_{33} & t_{3}\\
		 * 		0      & 0      & 0      & 1\\
		 * 	\end{array}
		 * \right) =
		 * \left(
		 * 	\begin{array}{cccc}
		 * 		       & \vdots         &        & \vdots\\
		 * 		\dots  & R_{3 \times 3} & \dots  & T_{3 \times 1}\\
		 * 		       & \vdots         &        & \vdots\\
		 * 		0      & 0              & 0      & 1\\
		 * 	\end{array}
		 * \right)
		 * \f]
		 * the inverse pose is expressed as follows
		 * \f[
		 * Inverse Pose = \left(
		 * 	\begin{array}{cccc}
		 * 		       & \vdots         &        & \vdots\\
		 * 		\dots  & R_{3 \times 3}^{t} & \dots  & -R_{3 \times 3}^{t} \times T_{3 \times 1}\\
		 * 		       & \vdots         &        & \vdots\\
		 * 		0      & 0              & 0      & 1\\
		 * 	\end{array}
		 * \right)
		 * \f]
		 * @return the inverse pose
		 */
		Pose inverse() const;

		/**
		 * Friend output operator
		 * @param out the output stream to write to
		 * @param pose the pose to write to the output stream
		 * @return a reference to the output stream
		 */
		friend ostream & operator <<(ostream & out, const Pose & pose);

	private:
		/**
		 * Check the matrix is monodimensional (1xn) or (nx1)
		 * @param mat the matrix to check for monodimensionality
		 * @return true if the matrix is monodimensional (1xn) or (nx1)
		 */
		inline bool checkMonodimensional(const Mat & mat) const
		{
			Size s(mat.size());

			return (s.height == 1) || (s.width == 1);
		}

		/**
		 * Line or column matrix size
		 * @param mat the matrix to check
		 * @return the biggest dimension of the matrix
		 */
		inline size_t length(const Mat & mat) const
		{
			Size s(mat.size());

			return (s.width > s.height ? size_t(s.width) : size_t(s.height));
		}
};

#endif /* POSE_H_ */
