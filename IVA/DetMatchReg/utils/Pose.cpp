/*
 * Pose.cpp
 *
 *  Created on: 25 juin 2014
 *      Author: davidroussel
 */

#include <cmath>
#include <opencv2/calib3d/calib3d.hpp>	// for Rodrigues formula

#include "Pose.h"

/*
 * All poses common epsilon to compare positions values [default = 1e-6]
 */
double Pose::positionEpsilon = 1e-6;

/*
 * All poses common epsilon to compare positions values [default = 1/2 degree]
 */
double Pose::orientationEpsilon = M_PI / 360.0;

/*
 * Pose valued constructor
 * @param x the x coordinate
 * @param y the y coordinate
 * @param z the z coordinate
 * @param rx the rotation around x axis
 * @param ry the rotation around y axis
 * @param rz the rotation around z axis
 */
//Pose::Pose(const double x,
//           const double y,
//           const double z,
//           const double rx,
//           const double ry,
//           const double rz) // : coord{x, y, z, rx, ry, rz} <-- C++11 only
//{
//	coord[X] = x;
//	coord[Y] = y;
//	coord[Z] = z;
//	coord[RX] = rx;
//	coord[RY] = ry;
//	coord[RZ] = rz;
//}

/*
 * Pose constructor from translation and rotation values such as
 * provided by solvePNP (1 line,3 columns,CV_64FC1 matrices)
 * @param translation
 * @param rotation
 */
Pose::Pose(const Mat & translation, const Mat & rotation) throw (exception)
{
	update(translation, rotation);
}


/*
 * Pose constructor from pose values such as
 * provided by solvePNP (1 line,3 columns,CV_64FC1 matrices)
 * @param pose vector (1x6 matrix)
 * @throw exception if pose is not of the right
 * type (CV_64FC1) or dimensions (1x6)
 */
Pose::Pose(const Mat & pose) throw (exception)
{
	update(pose);
}


/*
 * Copy constructor
 * @param pose the other pose to copy
 */
Pose::Pose(const Pose & pose) // : coord(pose.coord)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] = pose.coord[i];
	}
}

/*
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
Pose::Pose(const double value)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] = value;
	}
}

/*
 * Pose destructor
 */
Pose::~Pose()
{
}

/*
 * Update current pose with new translation & rotation values
 * @param translation new translation
 * @param rotation new rotation
 * @throw exception if translation or rotation are not of the right
 * type (CV_64FC1) or dimensions (1x3)
 */
void Pose::update(const Mat & translation, const Mat & rotation)
	throw (exception)
{
	size_t rightLength = 3;

	if (translation.type() == CV_64FC1 &&
		rotation.type() == CV_64FC1 &&
		checkMonodimensional(translation) &&
		checkMonodimensional(rotation) &&
		length(translation) == rightLength &&
		length(rotation) == rightLength)
	{
		coord[X] = translation.at<double>(0);
		coord[Y] = translation.at<double>(1);
		coord[Z] = translation.at<double>(2);
		coord[RX] = rotation.at<double>(0);
		coord[RY] = rotation.at<double>(1);
		coord[RZ] = rotation.at<double>(2);
	}
	else
	{
		throw exception();
	}
}

/*
 * Update current pose
 * @param pose new pose value (1x6) or (6x1) vector
 * @throw exception if pose is not of the right type (CV_64FC1)
 * or dimensions (1x6) or (6x1)
 */
void Pose::update(const Mat & pose) throw (exception)
{
	if (pose.type() == CV_64FC1 &&
		checkMonodimensional(pose) &&
		length(pose) == NBCOORDS)
	{
		coord[X] = pose.at<double>(0);
		coord[Y] = pose.at<double>(1);
		coord[Z] = pose.at<double>(2);
		coord[RX] = pose.at<double>(3);
		coord[RY] = pose.at<double>(4);
		coord[RZ] = pose.at<double>(5);
	}
	else
	{
		throw exception();
	}
}

/*
 * Copy operator
 * @param pose the other pose to copy
 * @return a reference to this after copy
 */
Pose & Pose::operator =(const Pose & pose)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] = pose.coord[i];
	}

	return *this;
}

/*
 * Pose comparison operator
 * @param pose the cother pose to compare
 * @return true if each position coordinates compare less than
 * positionEpsilon and each orientationEpsilon compares less than
 * orientationEpsilon
 */
bool Pose::operator ==(const Pose & pose) const
{
	double epsilon = positionEpsilon;
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		if (i == 2)
		{
			epsilon = orientationEpsilon;
		}

		if (abs(coord[i] - pose.coord[i]) > epsilon)
		{
			return false;
		}
	}

	return true;
}

/*
 * Pose difference operator
 * @param pose the cother pose to compare
 * @return true if each position coordinates compare less than
 * positionEpsilon and each orientationEpsilon compares less than
 * orientationEpsilon
 */
bool Pose::operator !=(const Pose & pose) const
{
	return !operator ==(pose);
}

/*
 * Pose less than operator
 * @param pose the other pose to compare
 * @return true if this pose is lexicographically smaller than
 * the other.
 * Where lexicographical compare means that if this->x < pose.x then we
 * return true without comparing further coordinates.
 */
bool Pose::operator <(const Pose & pose) const
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		if (coord[i] < pose.coord[i])
		{
			return true;
		}
		else
		{
			if (coord[i] > pose.coord[i])
			{
				return false;
			}
		}
	}

	// finished for loop without returning ==> all keys are equal, hence not <
	return false;
}

/*
 * Pose less or equal operator
 * @param pose the other pose to compare
 * @return true if this pose is lexicographically smaller or equal to
 * the other.
 */
bool Pose::operator <=(const Pose & pose) const
{
	return !pose.operator <(*this);
}

/*
 * Pose greater than operator
 * @param pose the other pose to compare
 * @return true if this pose is lexicographically greater than
 * the other.
 * Where lexicographical compare means that if this->x < pose.x then we
 * return true without comparing further coordinates.
 */
bool Pose::operator >(const Pose & pose) const
{
	return pose.operator <(*this);
}

/*
 * Pose greater or equal operator
 * @param pose the other pose to compare
 * @return true if this pose is lexicographically greater or equal to
 * the other.
 */
bool Pose::operator >=(const Pose & pose) const
{
	return !operator <(pose);
}

/*
 * Pose self addition
 * @param pose the other pose to add to the current pose
 * @return a reference to this
 */
Pose & Pose::operator +=(const Pose & pose)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] += pose.coord[i];
	}

	return *this;
}

/*
 * Pose self substraction
 * @param pose the other pose to substract to the current pose
 * @return a reference to this
 */
Pose & Pose::operator -=(const Pose & pose)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] -= pose.coord[i];
	}

	return *this;
}

/*
 * Pose self multiplication
 * @param pose the other pose to mulitply the current pose
 * @return a reference to this
 */
Pose & Pose::operator *=(const Pose & pose)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] *= pose.coord[i];
	}

	return *this;
}

/*
 * Pose self multiplication with scalar
 * @param value the scale factor to apply to pose coordinates
 * @return a reference to this
 */
Pose & Pose::operator *=(const double value)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] *= value;
	}

	return *this;
}

/*
 * Pose self division
 * @param pose the other pose to divide the current pose
 * @return a reference to this
 */
Pose & Pose::operator /=(const Pose & pose)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] /= pose.coord[i];
	}

	return *this;
}

/*
 * Pose self division with scalar
 * @param value the scale factor to apply to pose coordinates
 * @return a reference to this
 */
Pose & Pose::operator /=(const double value)
{
	for (size_t i = 0; i < NBCOORDS; i++)
	{
		coord[i] /= value;
	}

	return *this;
}

/*
 * Pose add operator
 * @param pose the other pose to add to the current pose
 * @return a new pose contaning the addition of the current and
 * other pose
 */
Pose Pose::operator +(const Pose & pose) const
{
	Pose newPose(*this);

	newPose += pose;

	return newPose;
}

/*
 * Pose substract operator
 * @param pose the other pose to substract to the current pose
 * @return a new pose contaning the substraction of the current and
 * other pose
 */
Pose Pose::operator -(const Pose & pose) const
{
	Pose newPose(*this);

	newPose -= pose;

	return newPose;
}

/*
 * Pose multiply operator
 * @param pose the other pose to multiply to the current pose
 * @return a new pose contaning the multiplication of the current and
 * other pose
 */
Pose Pose::operator *(const Pose & pose) const
{
	Pose newPose(*this);

	newPose *= pose;

	return newPose;
}

/*
 * Pose multiply operator with scalar
 * @param value the scale factor to apply to pose coordinates
 * @return a new pose contaning the multiplication of the current pose
 * by factor
 */
Pose Pose::operator *(const double value) const
{
	Pose newPose(*this);

	newPose *= value;

	return newPose;
}

/*
 * Pose divide operator
 * @param pose the other pose to divide to the current pose
 * @return a new pose contaning the division of the current and
 * other pose
 */
Pose Pose::operator /(const Pose & pose) const
{
	Pose newPose(*this);

	newPose /= pose;

	return newPose;
}

/*
 * Pose divide operator with scalar
 * @param value the scale factor to apply to pose coordinates
 * @return a new pose contaning the multiplication of the current pose
 * by factor
 */
Pose Pose::operator /(const double value) const
{
	Pose newPose(*this);

	newPose /= value;

	return newPose;
}

/*
 * Bracket operator to access specific pose element (in r/w mode)
 * @param index the index of the required element
 * @return a reference to the required element
 * @throws an exception when the index is invalid
 */
double & Pose::operator [](size_t index) throw (exception)
{
	if (index < NBCOORDS)
	{
		return coord[index];
	}
	else
	{
		throw exception();
	}
}

/*
 * Bracket operator to access specific pose element (in read only mode)
 * @param index the index of the required element
 * @return a reference to the required element
 * @throws an exception when the index is invalid
 */
double Pose::operator [](size_t index) const throw (exception)
{
	if (index < NBCOORDS)
	{
		return coord[index];
	}
	else
	{
		throw exception();
	}
}

/*
 * Translation vector
 * @param transpose triggers vector transposition in order to obtain
 * a (3x1) vector instead of a (1x3) vector
 * @return the translation vector (1x3) if not transposed or (3x1) if
 * transposed
 */
Mat Pose::translationVector(const bool transpose) const
{
	if (transpose)
	{
		return (Mat_<double>(3, 1) << coord[X], coord[Y], coord[Z]);
	}
	else
	{
		return (Mat_<double>(1, 3) << coord[X], coord[Y], coord[Z]);
	}
}

/*
 * Rotation vector
 * @return the rotation vector (1x3)
 */
Mat Pose::rotationVector() const
{
	return (Mat_<double>(1, 3) << coord[RX], coord[RY], coord[RZ]);
}

/*
 * Return rotation as a matrix rotation (3x3) instead of a vector (1x3).
 * @return a matrix rotation
 */
Mat Pose::rotationMatrix() const
{
	// recreates the rotation vector(1x3)
	Mat rotVec = rotationVector();

	// convert rotation vector to rotation matrix(3x3)
	Mat rotMat(3, 3, CV_64FC1);
	Rodrigues(rotVec, rotMat);

	return rotMat;
}

/*
 * Homogeneous (4x4) matrix containing pose
 * @return the pose 4x4 matrix
 */
Mat Pose::poseMatrix() const
{
	Mat pose = Mat::eye(4, 4, CV_64FC1);

	// recreates rotation matrix (3x3)
	Mat rotMat = rotationMatrix();

	// recreates translation vector (3x1)
	Mat transVec = translationVector(true);

	// place rotation matrix into pose
	Mat poseSubRot = pose.colRange(0, 4).rowRange(0, 4);
	rotMat.copyTo(poseSubRot);

	// place translation vector into pose
	Mat poseSubTrans = pose.colRange(3, 4).rowRange(0, 4);
	transVec.copyTo(poseSubTrans);

	return pose;
}

/*
 * Pose (translation & rotation) vector (6x1) or (1x6), such as
 * @param transpose if transpose is false then returns a (6x1) matrix
 * and if transpose is true returns a (1x6) matrix.
 * @return the pose as a monodimensional matrix
 */
Mat Pose::poseVector(const bool transpose) const
{
	Mat pose;

	if (transpose)
	{
		pose = (Mat_<double>(1, NBCOORDS) << coord[X], coord[Y], coord[Z],
			coord[RX], coord[RY], coord[RZ]);
	}
	else
	{
		pose = (Mat_<double>(NBCOORDS,1) << coord[X], coord[Y], coord[Z],
			coord[RX], coord[RY], coord[RZ]);
	}

	return pose;
}


/*
 * Compute the inverse pose.
 * @return the inverse pose
 */
Pose Pose::inverse() const
{
	// convert rotation vector to rotation matrix(3x3)
	Mat rotMat = rotationMatrix();

	// transpose rotation matrix(3x3) == inverse rotation
	Mat invRotMat = rotMat.t();

	// recreates inv rotation vector
	Mat invRotVec;
	Rodrigues(invRotMat, invRotVec);

	// recreates translation vector(3x1)
	Mat transVec = translationVector(true);

	// compute inverse translation vector (3x1)
	Mat invTransVec = invRotMat.mul(transVec, -1.0);

	// check invRotVec dimensions (3x1) or (1x3) cause doc says both
	if (invRotVec.rows == 3)
	{
		invRotVec = invRotVec.t();
	}

	return Pose(invTransVec.t(), invRotVec);
}

/*
 * Friend output operator
 * @param out the output stream to write to
 * @param pose the pose to write to the output stream
 * @return a reference to the output stream
 */
ostream & operator <<(ostream & out, const Pose & pose)
{
	for (size_t i = 0; i < Pose::NBCOORDS; i++)
	{
		out << pose.coord[i];
		if (i < Pose::RZ)
		{
			out << ", ";
		}
		else
		{
			out << "; ";
		}
	}

	return out;
}
