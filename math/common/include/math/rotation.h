/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file rotation.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * This file provides utility for 3D rotations.
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2015-2020 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  For information concerning this header file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

#ifndef ROTATION_H_INCLUDED
#define ROTATION_H_INCLUDED

// Include math header files.
#include <math/mlmath.h>
#include <math/scalar.h>
#include <math/vector.h>

class MlTransform;


/**
 * @brief Specifies a rotation, used to define the orientation of a 3D object.
 *
 * The <b>MlRotation</b> class implements a quaternion.
 */
class MLMATH_API MlRotation 
{
  public:

    /**
	 * Default constructor.
	 */
    MlRotation() {}

    /**
	 * @brief A constructor given a quaternion as an array of 4 components.
	 *
	 * @param v An array of four <b>MlScalar</b>s representing a quaternion.
	 */
    MlRotation(const MlScalar v[4])
	{ setValue(v); }

    /**
	 * @brief A constructor given 4 individual components of a quaternion.
	 *
	 * @param q0 The first element of the quaternion.
	 * @param q1 The second element of the quaternion.
	 * @param q2 The third element of the quaternion.
	 * @param q3 The fourth element of the quaternion.
	 */
    MlRotation(MlScalar q0, MlScalar q1, MlScalar q2, MlScalar q3)
	{ setValue(q0, q1, q2, q3); }

    /**
	 * @brief A constructor given a rotation matrix.
	 *
	 * @param m A reference to a transformation matrix.
	 */
    MlRotation(const MlTransform& m)
	{ setValue(m); }

    /**
	 * @brief A constructor given 3D rotation axis vector and angle in radians.
	 *
	 * @param axis A reference to the 3D rotation axis.
	 * @param radians The angle in radians.
	 */
    MlRotation(const MlVector3& axis, MlScalar radians)
	{ setValue(axis, radians); }

    /**
	 * @brief A constructor for rotation that rotates one direction vector to another.
	 *
	 * @param rotateFrom The vector to rotate from.
	 * @param rotateTo The vector to rotate to.
	 */
    MlRotation(const MlVector3& rotateFrom, const MlVector3& rotateTo)
	{ setValue(rotateFrom, rotateTo); }

    /**
	 * @brief Get the value of rotation as a quaternion.
	 *
	 * Returns a pointer to array of 4 components defining the quaternion
     * (questionalble API, should probably be deprecated).
	 *
	 * @return A pointer to a <b>MlScalar</b> array is returned. The array will
	 * contain the 4 components of the quaternion.
	 */
    const MlScalar *getValue() const
	{ return (quat); }

    /**
	 * @brief Get the value of rotation as the four components of a quaternion.
	 *
	 * Returns 4 individual components of rotation quaternion.
	 *
	 * @param q0 This is an output parameter containing the first element of the quaternion.
	 * @param q1 This is an output parameter containing the second element of the quaternion.
	 * @param q2 This is an output parameter containing the third element of the quaternion.
	 * @param q3 This is an output parameter containing the fourth element of the quaternion.
	 */
    void getValue(MlScalar& q0, MlScalar& q1,
                  MlScalar& q2, MlScalar& q3) const;

    /**
	 * @brief Get the value of the rotation as a 3D rotation axis vector
	 * and an angle.
     *
	 * Returns corresponding 3D rotation axis vector and angle in radians.
	 *
	 * @param axis A reference to the 3D rotation axis.
	 * @param radians The angle in radians.
	 *
	 */
    void getValue(MlVector3& axis, MlScalar& radians) const;

    /**
	 * @brief Get the value of the rotation as a 4x3 rotation matrix.
	 *
	 * Returns corresponding 4x3 rotation matrix.
	 *
	 * @param matrix A reference to the transformation matrix that will
	 * be returned.
	 */
    void getValue(MlTransform& matrix) const;

    /**
	 * @brief Invert this rotation.
	 *
	 * Changes a rotation to be its inverse.
	 *
	 * @return A reference to this <b>MlRotation</b> is returned.
	 */
    MlRotation &invert();

    /**
	 * @brief Convenience method for inverting this rotation.
	 *
	 * Returns the inverse of this rotation.
	 *
	 * @return A reference to this <b>MlRotation</b> is returned.
	 */
    MlRotation inverse() const
	{ MlRotation q = *this; return q.invert(); }

    /**
	 * @brief Set the value of the rotation.
	 *
	 * Sets value of rotation from array of 4 components of a quaternion.
	 *
	 * @param q An array of <b>MlScalar</b>s containing the quaternion components.
	 *
	 * @return A reference to this <b>MlRotation</b> is returned.
	 */
    MlRotation &setValue(const MlScalar q[4]);

    /**
	 * @brief Set the value of the rotation.
	 *
	 * Sets value of rotation from 4 individual components of a quaternion.
	 *
	 * @param q0 The first element of the quaternion.
	 * @param q1 The second element of the quaternion.
	 * @param q2 The third element of the quaternion.
	 * @param q3 The fourth element of the quaternion.
	 *
	 * @return A reference to this <b>MlRotation</b> is returned.
	 */
    MlRotation &setValue(MlScalar q0, MlScalar q1, MlScalar q2, MlScalar q3);

    /**
	 * @brief Set the value of the rotation.
	 *
	 * Sets value of rotation from a rotation matrix.
	 *
	 * @param m A reference to the transformation matrix to obtain
	 * the values from.
	 *
	 * @return A reference to this <b>MlRotation</b> is returned.
	 */
    MlRotation &setValue(const MlTransform& m);
    // I don't know what will happen if you call this with something
    // that isn't a rotation.

    /**
	 * @brief Set the value of the rotation.
	 *
	 * Sets value of vector from 3D rotation axis vector and angle in radians.
	 *
 	 * @param axis A reference to the 3D rotation axis.
	 * @param radians The angle in radians.
     *
	 * @return A reference to this <b>MlRotation</b> is returned.
	 */
    MlRotation &setValue(const MlVector3& axis, MlScalar radians);

    /**
	 * @brief Set the value of the rotation.
	 *
	 * Sets rotation to rotate one direction vector to another.
	 *
	 * @param rotateFrom The vector to rotate from.
	 * @param rotateTo The vector to rotate to.
     *
	 * @return A reference to this <b>MlRotation</b> is returned.
	 */
    MlRotation &setValue(const MlVector3& rotateFrom,
                         const MlVector3& rotateTo);

	/**
     * @brief Accesses indexed component of quaternion.
	 *
     * This operator is used to get/set values in the Digitial Workprint
	 * read/write methods
     * (questionalble API, should probably be deprecated).
	 *
	 * @return A scalar is returned.
	 */
    MlScalar &operator [](int i)
	{ return (quat[i]); }

	/**
     * @brief Accesses indexed component of quaternion.
	 *
     * This operator is used to get/set values in the Digitial Workprint
	 * read/write methods
     * (questionalble API, should probably be deprecated).
	 *
	 * @return A scalar is returned.
	 */
    const MlScalar &operator [](int i) const
	{ return (quat[i]); }

    /**
	 * @brief Multiplication operator.
	 *
	 * This operator multiplies this rotation by another rotation.
	 * The result is a product of the rotations.
	 *
	 * @return The product of the rotations is returned as another rotation.
	 */
    MlRotation &operator *=(const MlRotation& q);

    /**
	 * @brief Equality comparison operator.
	 *
	 * This operator is used to determine whether two rotations are equal.
	 *
	 * @return If the rotations are equal, then 1 will be returned.
	 * Otherwise 0 will be returned if the rotations are not equal.
	 */
    MLMATH_API friend int operator ==(const MlRotation& q1, const MlRotation& q2);

    /**
	 * @brief Inequality comparison operator.
	 *
	 * This operator is used to determine whether two rotations are not equal.
	 *
	 * @return If the rotations are not equal, then 1 will be returned.
	 * Oterwise 0 will be returned if the rotations are equal.
	 */
    MLMATH_API friend int operator !=(const MlRotation& q1, const MlRotation& q2)
	{ return !(q1 == q2); }

    /**
	 * @brief Equality comparison within given tolerance.
	 *
	 * The tolerance is determined by the square of the length of the maximum
	 * distance between the two quaternion vectors.
	 *
	 * @param r The other rotation matrix to compare.
	 * @param tolerance The value to determine equivalance.
	 *
	 * @return If this rotation is equal to the specified rotation, r, then 1 will be returned.
	 * Otherwise 0 will be returned if the rotations are not equal.
	 */
    int	equals(const MlRotation& r, MlScalar tolerance) const;

    /**
	 * @brief Multiplication operator.
	 *
	 * This operator is used to produce the multiplication of two rotations.
	 * The result is the product of the rotations.
	 *
	 * @return The product of the rotations is returned as another rotation.
	 */
    MLMATH_API friend MlRotation operator *(const MlRotation& q1, const MlRotation& q2);

    /**
	 * @brief Multiply a vector by this rotation.
	 *
	 * This method puts the given vector, <i>src</i>, through this rotation
     * It essentially multiplies the given vector by the matrix of this rotation.
	 * The result is placed is the <i>dst</i> vector.
	 *
	 * @param src The source vector to rotate.
	 * @param dst The result of the rotated vector.
	 */
    void multVec(const MlVector3& src, MlVector3& dst) const;

    /**
	 * @brief Scale the angle of rotation.
	 *
	 * This method will multiply the angle of rotation by 
     * the specified amount, <i>scaleFactor</i>.
	 * It will keep the axis of the rotation the same.
	 *
	 * @param scaleFactor The amount to scale the rotation by.
	 */
    void scaleAngle( MlScalar scaleFactor );

    /**
	 * @brief Perform a spherical linear interpolation between
	 * two rotation matrices.
	 *
	 * The algorithm for the spherical linear interpolation is:
	 * as <i>t</i> goes from 0 to 1, the returned
     * value goes from <i>rot0</i> to <i>rot1</i>.
	 *
	 * @param rot0 The lower bound of the interpolation.
	 * @param rot1 The upper bound of the interpolation.
	 * @param t The control for the interpolation. It must be a value from
	 * 0 to 1.
	 *
	 * @return The interpolated rotation is returned.
	 */
    static MlRotation slerp(const MlRotation& rot0,
                            const MlRotation& rot1, MlScalar t);

    /**
	 * @brief Get the identity of a rotation matrix.
	 *
	 * This is effectively a null rotation.
	 *
	 * @return A <b>MlRotation</b> is returned where the elements of the
	 * quaternion are [0, 0, 0, 1].
	 */
    static MlRotation identity()
	{ return MlRotation(ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ONE); }

  private:

	// Storage for quaternion components.
    MlScalar quat[4];

    // Returns the normal (square of the 4D length) of a rotation's quaterion.
    MlScalar norm() const;

    // Normalizes a rotation quaternion to unit 4D length.
    void normalize();
};


#endif /* ROTATION_H_INCLUDED */
