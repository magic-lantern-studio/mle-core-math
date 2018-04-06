/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file vector.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * This file provides utility for vectors. The vectors are
 *
 * <li>
 * <ul>4 MlScalar elements: [a11, a12, a13, a14]</ul>
 * <ul>3 MlScalar elements: [a11, a12, a13]</ul>
 * <ul>2 MlScalar elements: [a11, a12]</ul>
 * </li>
 * <p>
 * <b>WARNING!!!!!  Transcription of arrays of these classes assume that the
 * only data stored in this class are 2 (or 3 or 4)
 * consecutive values.  Do not add any extra data members!!!</b>
 * </p>
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2015 Wizzer Works
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

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

// Include Magic Lantern math header files.
#include <math/mlmath.h>
#include <math/scalar.h>

class MlVector4;
class MlVector3;
class MlVector2;
#if 0
class MlVector3s;
class MlVector2s;
#endif


/**
 * @brief A vector of three elements.
 *
 * <b>MlVector3</b> is a 3D vector used to represent points or directions.
 * Each component of the vector is an <b>MlScalar</b>.
 */
class MLMATH_API MlVector3 
{ 
  public:

    /**
	 * Default constructor.
	 */
    MlVector3()	{ };

    /**
	 * @brief A constructor given an array of 3 components.
	 *
	 * @param v An array of three <b>MlScalar</b>s representing the
	 * x, y, and z components of the vector to construct.
	 */
    MlVector3(const MlScalar v[3])
    { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; };
    
    /**
	 * @brief A constructor given 3 individual components.
	 *
	 * @param x The first element of the vector.
	 * @param y The second element of the vector.
	 * @param z The third element of the vector.
	 */
    MlVector3(MlScalar x, MlScalar y, MlScalar z)
    { vec[0] = x; vec[1] = y; vec[2] = z; };
    
    /**
	 * @brief Check whether the vector contains all zeros.
	 *
	 * @return Returns true, 1, if all elements are zero.
	 * Otherwise false, 0, is returned.
	 */
    int isZero(void) const;
    
    /**
	 * @brief Compute the cross product of this vector with another.
	 *
	 * @param v The other vector to use for computation.
	 *
	 * @return The right-handed cross product of this vector and another vector
	 * is returned.
	 */
    MlVector3 cross(const MlVector3 &v) const;
    
    /**
	 * @brief Compute the dot product of this vector with another.
	 *
	 * @return The dot (inner) product of this vector and another vector
	 * is returned.
	 */
    MlScalar dot(const MlVector3 &v) const;
    
    /**
	 * @brief Get the value of the vector as an array.
	 *
	 * @return A pointer to an array of 3 components is returned.
	 */
    const MlScalar *getValue() const
	{ return vec; }
    
    /**
	 * @brief Get the value of the vector as three <b>MlScalar</b>
	 * components.
	 *
	 * @param x The output parameter for the first component.
	 * @param y The output parameter for the second component.
	 * @param z The output parameter for the third component.
	 */
    void getValue(MlScalar &x, MlScalar &y, MlScalar &z) const;
    
    /**
	 * @brief Get the geometric length of the vector.
	 *
	 * @return A Magic Lantern scalar is returned.
	 */
    MlScalar length() const;
    
    /**
	 * @brief Get the approximate length of the vector (+/- 7%).
	 *
	 * @return A Magic Lantern scalar is returned.
	 */
    MlScalar approximateLength() const;
    
    /**
	 * @brief Normalize the vector.
	 *
	 * Changes the vector to be unit length, returns original length.
	 *
	 * @return The original length is returned as a Magic Lantern scalar.
	 */
    MlScalar normalize();
    
    /**
	 * @brief Normalize the vector.
	 *
	 * Changes the vector to be approximately unit length.
	 *
	 * @return The original length is returned as a Magic Lantern scalar.
	 */
    MlScalar approximateNormalize();
    
    /**
	 * @brief Negate each component of the vector in place.
	 */
    void negate();
    
    /**
	 * @brief Scale the vector.
	 *
	 * Changes the vector to have length of input scale factor.
	 *
	 * @param newScale The input scale factor.
	 *
	 * @return The scaled vector is returned.
	 */
    MlVector3& scaleTo( const MlScalar newScale );

    /**
	 * @brief Perform a linear interpolation, aka lerp.
	 *
	 * Set the <b>result</b> to the interpolation
     * by <b>weight</b> from <b>v0</b> (when weight=0) to <b>v1</b> (when weight=1).
	 *
	 * @param weight The control for the interpolation. It must be a value from
	 * 0 to 1.
	 * @param v0 The first vector to interpolate between.
	 * @param v1 The second vector to interpolate between.
	 * @param result A pointer to the interpolated vector is returned.
	 */
    static void interpolate (MlScalar weight,
			     const MlVector3 *v0, const MlVector3 *v1,
			     MlVector3 *result);
    
    /**
	 * @brief Set the value of the vector.
	 *
	 * Sets the value of the vector from an array of 3 components.
	 *
	 * @param v An array of three <b>MlScalar</b>s representing the
	 * x, y, and z components of the vector.
	 *
	 * @return A reference to this vector is returned.
	 */
    MlVector3 &	setValue(const MlScalar v[3])
    { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; return *this; }
    
    /**
	 * @brief Set the value of the vector.
	 *
	 * Sets the value of the vector from 3 individual components
	 *
	 * @param x The first element of the vector.
	 * @param y The second element of the vector.
	 * @param z The third element of the vector.
	 *
	 * @return A reference to this vector is returned.
	 */
    MlVector3 &	setValue(MlScalar x, MlScalar y, MlScalar z)
    { vec[0] = x; vec[1] = y; vec[2] = z; return *this; }
    
	/**
	 * @brief Set the value of the vector.
	 *
     * Sets the value of the vector to be a convex combination of 3 other
     * vectors, using barycentic coordinates.
	 *
	 * @param barycentic The barycentic coordinates.
	 * @param v0 The first vector.
	 * @param v1 The second vector.
	 * @param v2 The third vector.
	 *
	 * @return A reference to this vector is returned.
	 */
    MlVector3 &	setValue(const MlVector3 &barycentic,
			 const MlVector3 &v0,
			 const MlVector3 &v1,
			 const MlVector3 &v2);
    
    /**
	 * @brief Finds the scale factor to put max value between 1 and TBD.
	 *
	 * @param scale The output parameter containing the found scale.
	 * @param recipScale The output parameter containing the reciprocal
	 * of the found scale.
	 */
    void getScale(MlScalar& scale, MlScalar& recipScale) const;
    
    /**
	 * @brief Accesses indexed component of vector.
	 */
    MlScalar & operator [](int i)
	{ return (vec[i]); }
    
    /**
	 * @brief Accesses indexed component of vector.
	 */
    const MlScalar & operator [](int i) const
	{ return (vec[i]); }
    
    /**
	 * @brief Multiplication operator.
	 *
	 * This operator performs a component-wise scalar multiplication operation.
	 *
  	 * @return The result of the multiplication is returned as another vector.
	 */
    MlVector3 &	operator *=(MlScalar d);
    
    /**
	 * @brief Division operator.
	 *
	 * This operator performs a component-wise scalar division operation.
	 *
	 * @return The result of the division is returned as another vector.
	 */
    MlVector3 &	operator /=(MlScalar d)
    { return *this *= mlReciprocal(d); }
    
    /**
	 * @brief Addition operator.
	 *
	 * This opertaor performs a component-wise vector addition operation.
	 *
	 * @return The result of the addition is returned as another vector.
	 */
    MlVector3 &	operator +=(MlVector3 v);
    
    /**
	 * @brief Subtraction operator.
	 *
	 * This operator performs a component-wise vector subtraction operation.
	 *
	 * @return The result of the subtraction is returned as another vector.
	 *
	 */
    MlVector3 &	operator -=(MlVector3 v);
    
    /**
	 * @brief Unary negation operator.
	 *
	 * This operator performs a nondestructive unary negation operation.
	 *
	 * @return The result of the negation is returned as another vector.
	 */
    MlVector3 operator -() const;
    
    /**
	 * @brief Binary scalar multiplication operator.
	 *
	 * This operator performs a component-wise binary scalar multiplication operation.
	 *
	 * @return The result of the multiplication is returned as another vector.
	 */
    MLMATH_API friend MlVector3	operator *(const MlVector3 &v, MlScalar d);
    
    /**
	 * @brief Binary scalar multiplication operator.
	 *
	 * This operator peforms a component-wise binary scalar multiplication operation.
	 *
	 * @return The result of the multiplication is returned as another vector.
	 */
    MLMATH_API friend MlVector3 operator *(MlScalar d, const MlVector3 &v)
    { return v * d; }
    
    /**
	 * @brief Binary scalar division operator.
	 *
	 * This operator performs a component-wise binary scalar division operation.
	 *
	 * @return The result of the division is returned as another vector.
	 */
    MLMATH_API friend MlVector3 operator /(const MlVector3 &v, MlScalar d)
    { return v * mlReciprocal(d); }
    
    /**
	 * @brief Binary vector addition operator.
	 *
	 * This operator performs a component-wise binary vector addition operation.
	 *
	 * @return The result of the addition is returned as another vector.
	 */
    MLMATH_API friend MlVector3 operator +(const MlVector3 &v1, const MlVector3 &v2);
    
    /**
	 * @brief Binary vector subtraction operator.
	 *
	 * This operator performs a component-wise binary vector subtraction operation.
	 *
	 * @return The result of the subtraction is returned as another vector.
	 */
    MLMATH_API friend MlVector3 operator -(const MlVector3 &v1, const MlVector3 &v2);
    
    /**
	 * @brief Equality comparison operator.
	 *
	 * This operator is used to determine whether two vectors are equal.
	 *
	 * @return If the vectors are equal, then 1 will be returned.
	 * Otherwise 0 will be returned if the vectors are not equal.
	 */
    MLMATH_API friend int operator ==(const MlVector3 &v1, const MlVector3 &v2);
    
    /**
	 * @brief Inequality comparison operator.
	 *
	 * This operator is used to determine whether two vectors are not equal.
	 *
	 * @return If the vectors are not equal, then 1 will be returned.
	 * Oterwise 0 will be returned if the vectors are equal.
	 */
    MLMATH_API friend int operator !=(const MlVector3 &v1, const MlVector3 &v2)
    { return !(v1 == v2); }
    
    /**
	 * @brief Equality comparison within given tolerance.
	 *
	 * The tolerance is determined by the square of the length of the maximum
	 * distance between the two vectors.
	 *
	 * @param v The other vector to compare.
	 * @param tolerance The value to determine equivalance.
	 *
	 * @return If this vector is equal to the specified vector, v, then 1 will be returned.
	 * Otherwise 0 will be returned if the vectors are not equal.
	 */
    int equals(const MlVector3 v, MlScalar tolerance) const;
    
    /**
	 * @brief Get the closest axis.
	 *
	 * Returns principal axis that is closest (based on maximum dot
     * product) to this vector.
	 *
	 * @return The axis is returned as a vector.
	 */
    MlVector3 getClosestAxis() const;
    
    /**
	 * @brief Obtain a vector whose elements are zero.
	 *
	 * This method is used to obtain a 3d origin (0, 0, 0).
	 *
	 * @return A vector is returned.
	 */
    static const MlVector3 zero;
    
  protected:

	/** Storage for the vector's components. */
    MlScalar vec[3];
};


/**
 * @brief A vector of two elements.
 *
 * <b>MlVector2</b> is a 2D vector used to represent points or directions.
 * Each component of the vector is an <b>MlScalar</b>.
 */
class MLMATH_API MlVector2 
{ 
  public:
    
    /**
	 * Default constructor.
	 */
    MlVector2() { };
    
    /**
	 * @brief A constructor given an array of 2 components.
	 *
	 * @param v An array of two <b>MlScalar</b>s representing the
	 * x, and y components of the vector to construct.
	 */
    MlVector2(const MlScalar v[2])
	{ setValue(v); };
    
    /**
	 * @brief A constructor given 2 individual components.
	 *
	 * @param x The first element of the vector.
	 * @param y The second element of the vector.
	 */
    MlVector2(MlScalar x, MlScalar y)
	{ setValue(x, y); };
    
    /**
	 * @brief Check whether the vector contains all zeros.
	 *
	 * @return Returns true, 1, if all elements are zero.
	 * Otherwise false, 0, is returned.
	 */
    int isZero(void) const;
    
	/**
	 * @brief Compute the dot product of this vector with another.
	 *
	 * @return The dot (inner) product of this vector and another vector
	 * is returned.
	 */
    MlScalar dot(const MlVector2 &v) const;
    
    /**
	 * @brief Get the value of the vector as an array.
	 *
	 * @return A pointer to an array of 2 components is returned.
	 */
    const MlScalar *getValue() const
	{ return vec; };
    
    /**
	 * @brief Get the value of the vector as two <b>MlScalar</b>
	 * components.
	 *
	 * @param x The output parameter for the first component.
	 * @param y The output parameter for the second component.
	 */
    void getValue(MlScalar &x, MlScalar &y) const;
    
    /**
	 * @brief Get the geometric length of the vector.
	 *
	 * @return A Magic Lantern scalar is returned.
	 */
    MlScalar length() const;

    /**
	 * @brief Negate each component of the vector in place.
	 */
    void negate();
    
    /**
	 * @brief Normalize the vector.
	 *
	 * Changes the vector to be unit length, returns original length.
	 *
	 * @return The original length is returned as a Magic Lantern scalar.
	 */
    MlScalar normalize();
    
    /**
	 * @brief Set the value of the vector.
	 *
	 * Sets the value of the vector from an array of 2 components.
	 *
	 * @param v An array of two <b>MlScalar</b>s representing the
	 * x, and y components of the vector.
	 *
	 * @return A reference to this vector is returned.
	 */
    MlVector2 &	setValue(const MlScalar v[2]);
    
    /**
	 * @brief Set the value of the vector.
	 *
	 * Sets the value of the vector from 2 individual components
	 *
	 * @param x The first element of the vector.
	 * @param y The second element of the vector.
	 *
	 * @return A reference to this vector is returned.
	 */
    MlVector2 &	setValue(MlScalar x, MlScalar y);

    /**
	 * @brief Finds the scale factor to put max value between 1 and TBD.
	 *
	 * @param scale The output parameter containing the found scale.
	 * @param recipScale The output parameter containing the reciprocal
	 * of the found scale.
	 */
    void getScale(MlScalar& scale, MlScalar& recipScale) const;
    
    /**
	 * @brief Accesses indexed component of vector.
	 */
    MlScalar & operator [](int i)
	{ return (vec[i]); }
    
    /**
	 * @brief Accesses indexed component of vector.
	 */
    const MlScalar & operator [](int i) const
	{ return (vec[i]); }
    
    /**
	 * @brief Multiplication operator.
	 *
	 * This operator performs a component-wise scalar multiplication operation.
	 *
  	 * @return The result of the multiplication is returned as another vector.
	 */
    MlVector2 &	operator *=(MlScalar d);
    
    /**
	 * @brief Division operator.
	 *
	 * This operator performs a component-wise scalar division operation.
	 *
	 * @return The result of the division is returned as another vector.
	 */
    MlVector2 &	operator /=(MlScalar d)
    { return *this *= mlReciprocal(d); }
    
    /**
	 * @brief Addition operator.
	 *
	 * This opertaor performs a component-wise vector addition operation.
	 *
	 * @return The result of the addition is returned as another vector.
	 */
    MlVector2 &	operator +=(const MlVector2 &u);
    
    /**
	 * @brief Subtraction operator.
	 *
	 * This operator performs a component-wise vector subtraction operation.
	 *
	 * @return The result of the subtraction is returned as another vector.
	 *
	 */
    MlVector2 & operator -=(const MlVector2 &u);
    
    /**
	 * @brief Unary negation operator.
	 *
	 * This operator performs a nondestructive unary negation operation.
	 *
	 * @return The result of the negation is returned as another vector.
	 */
    MlVector2 operator -() const;
    
    /**
	 * @brief Binary scalar multiplication operator.
	 *
	 * This operator performs a component-wise binary scalar multiplication operation.
	 *
	 * @return The result of the multiplication is returned as another vector.
	 */
    MLMATH_API friend MlVector2	operator *(const MlVector2 &v, MlScalar d);
    
    /**
	 * @brief Binary scalar multiplication operator.
	 *
	 * This operator performs a component-wise binary scalar multiplication operation.
	 *
	 * @return The result of the multiplication is returned as another vector.
	 */
    MLMATH_API friend MlVector2	operator *(MlScalar d, const MlVector2 &v)
    { return v * d; }
    
    /**
	 * @brief Binary scalar division operator.
	 *
	 * This operator performs a component-wise binary scalar division operation.
	 *
	 * @return The result of the division is returned as another vector.
	 */
    MLMATH_API friend MlVector2	operator /(const MlVector2 &v, MlScalar d)
    { return v * mlReciprocal(d); }
    
    /**
	 * @brief Binary vector addition operator.
	 *
	 * This operator performs a component-wise binary vector addition operation.
	 *
	 * @return The result of the addition is returned as another vector.
	 */
    MLMATH_API friend MlVector2 operator +(const MlVector2 &v1, const MlVector2 &v2);
    
    /**
	 * @brief Binary vector subtraction operator.
	 *
	 * This operator performs a component-wise binary vector subtraction operation.
	 *
	 * @return The result of the subtraction is returned as another vector.
	 */
    MLMATH_API friend MlVector2 operator -(const MlVector2 &v1, const MlVector2 &v2);
    
    /**
	 * @brief Equality comparison operator.
	 *
	 * This operator is used to determine whether two vectors are equal.
	 *
	 * @return If the vectors are equal, then 1 will be returned.
	 * Otherwise 0 will be returned if the vectors are not equal.
	 */
    MLMATH_API friend int operator ==(const MlVector2 &v1, const MlVector2 &v2);
    
    /**
	 * @brief Inequality comparison operator.
	 *
	 * This operator is used to determine whether two vectors are not equal.
	 *
	 * @return If the vectors are not equal, then 1 will be returned.
	 * Oterwise 0 will be returned if the vectors are equal.
	 */
    MLMATH_API friend int operator !=(const MlVector2 &v1, const MlVector2 &v2)
    { return !(v1 == v2); }
    
    /**
	 * @brief Equality comparison within given tolerance.
	 *
	 * The tolerance is determined by the square of the length of the maximum
	 * distance between the two vectors.
	 *
	 * @param v The other vector to compare.
	 * @param tolerance The value to determine equivalance.
	 *
	 * @return If this vector is equal to the specified vector, v, then 1 will be returned.
	 * Otherwise 0 will be returned if the vectors are not equal.
	 */
    int equals(const MlVector2 v, MlScalar tolerance) const;

    /**
	 * @brief Obtain a vector whose elements are zero.
	 *
	 * This method is used to obtain a 2d origin (0, 0).
	 *
	 * @return A vector is returned.
	 */
    static const MlVector2 zero;

  protected:

	/** Storage for vector components. */
    MlScalar vec[2];
};


#if 0
//  2D vector used to represet points or directions. Each component of
//  the vector is a (short) integer.
class MLMATH_API MlVector2s
{
  public:

    // Default constructor.
    MlVector2s() { }

    // Constructor given an array of 2 components.
    MlVector2s(const short v[2])
	{ setValue(v); }

    // Constructor given 2 individual components.
    MlVector2s(short x, short y)
	{ setValue(x, y); }

    // Returns dot (inner) product of vector and another vector.
    int	dot(const MlVector2s &v) const;

    // Returns pointer to array of 2 components.
    const short	*getValue() const
	{ return vec; }

    // Returns 2 individual components.
    void getValue(short &x, short &y) const;

    // Negates each component of vector in place.
    void negate();

    // Sets value of vector from array of 2 components.
    MlVector2s & setValue(const short v[2]);

    // Sets value of vector from 2 individual components.
    MlVector2s & setValue(short x, short y);

    // Accesses indexed component of vector
    short & operator [](int i)
	{ return (vec[i]); }
    const short & operator [](int i) const
	{ return (vec[i]); }

    // Component-wise scalar multiplication and division operators.
    MlVector2s & operator *=(int d);
    MlVector2s & operator *=(MlScalar d);

    MlVector2s & operator /=(int d);
    MlVector2s & operator /=(MlScalar d)
	{ return *this *= mlReciprocal(d); }

    // Component-wise vector addition and subtraction operators.
    MlVector2s & operator +=(const MlVector2s &u);
    MlVector2s & operator -=(const MlVector2s &u);

    // Nondestructive unary negation - returns a new vector.
    MlVector2s	operator -() const;

    // Component-wise binary scalar multiplication and division operators.
    MLMATH_API friend MlVector2s operator *(const MlVector2s &v, int d);
    MLMATH_API friend MlVector2s operator *(const MlVector2s &v, MlScalar d);
    MLMATH_API friend MlVector2s operator *(int d, const MlVector2s &v)
	{ return v * d; }
    MLMATH_API friend MlVector2s operator *(MlScalar d, const MlVector2s &v)
	{ return v * d; }
    MLMATH_API friend MlVector2s operator /(const MlVector2s &v, int d);
    MLMATH_API friend MlVector2s operator /(const MlVector2s &v, MlScalar d)
	{ return v * mlReciprocal(d); }

    // Component-wise binary vector addition and subtraction operators.
    MLMATH_API friend MlVector2s	operator +(const MlVector2s &v1, const MlVector2s &v2);

    MLMATH_API friend MlVector2s	operator -(const MlVector2s &v1, const MlVector2s &v2);

    // Equality comparison operator.
    MLMATH_API friend int		operator ==(const MlVector2s &v1, const MlVector2s &v2);

    // Inequality comparison operator.
    MLMATH_API friend int		operator !=(const MlVector2s &v1, const MlVector2s &v2)
	{ return !(v1 == v2); }

  protected:

	// Storage for vector components.
    short vec[2];
};

#endif /* 0 */


/**
 * @brief A vector of four elements.
 *
 * <b>MlVector4</b> is a 4D vector used to represent points or directions.
 * Each component of the vector is an <b>MlScalar</b>.
 */
class MLMATH_API MlVector4 
{
  public:

    /**
	 * Default constructor.
	 */
    MlVector4() { }

    /**
	 * @brief A constructor given an array of 4 components.
	 *
	 * @param v An array of four <b>MlScalar</b>s representing the
	 * x, y, z, and w components of the vector to construct.
	 */
    MlVector4(const MlScalar v[4])
	{ setValue(v); }

    /**
	 * @brief A constructor given 4 individual components.
	 *
	 * @param x The first element of the vector.
	 * @param y The second element of the vector.
	 * @param z The third element of the vector.
	 * @param w The fourth element of the vector.
	 */
    MlVector4(MlScalar x, MlScalar y, MlScalar z, MlScalar w)
	{ setValue(x, y, z, w); }

    /**
	 * @brief Check whether the vector contains all zeros.
	 *
	 * @return Returns true, 1, if all elements are zero.
	 * Otherwise false, 0, is returned.
	 */
    int isZero(void) const;

    /**
	 * @brief Compute the dot product of this vector with another.
	 *
	 * @return The dot (inner) product of this vector and another vector
	 * is returned.
	 */
    MlScalar dot(const MlVector4 &v) const;

    /**
	 * @brief Get the real elements of the vector.
	 *
	 * Returns the real portion of the vector by dividing by the fourth element.
	 *
	 * @param v The output parameter containing the real elements of this vector.
	 */
    void getReal(MlVector3 &v) const;

    /**
	 * @brief Get the value of the vector as an array.
	 *
	 * @return A pointer to an array of 4 components is returned.
	 */
    const MlScalar *getValue() const
	{ return vec; }

    /**
	 * @brief Get the value of the vector as four <b>MlScalar</b>
	 * components.
	 *
	 * @param x The output parameter for the first component.
	 * @param y The output parameter for the second component.
	 * @param z The output parameter for the third component.
	 * @param w The output parameter for the fourth component.
	 */
    void getValue(MlScalar &x, MlScalar &y, MlScalar &z, MlScalar &w) const;

    /**
	 * @brief Get the geometric length of the vector.
	 *
	 * @return A Magic Lantern scalar is returned.
	 */
    MlScalar length() const;

    /**
	 * @brief Negate each component of the vector in place.
	 */
    void negate();

    /**
	 * @brief Normalize the vector.
	 *
	 * Changes the vector to be unit length, returns original length.
	 *
	 * @return The original length is returned as a Magic Lantern scalar.
	 */
    MlScalar normalize();

    /**
	 * @brief Set the value of the vector.
	 *
	 * Sets the value of the vector from an array of 4 components.
	 *
	 * @param v An array of four <b>MlScalar</b>s representing the
	 * x, y, z and w components of the vector.
	 *
	 * @return A reference to this vector is returned.
	 */
    MlVector4 &	setValue(const MlScalar v[4]);

    /**
	 * @brief Set the value of the vector.
	 *
	 * Sets the value of the vector from 4 individual components
	 *
	 * @param x The first element of the vector.
	 * @param y The second element of the vector.
	 * @param z The third element of the vector.
	 * @param w The fourth element of the vector.
	 *
	 * @return A reference to this vector is returned.
	 */
    MlVector4 &	setValue(MlScalar x, MlScalar y, MlScalar z, MlScalar w);

    /**
	 * @brief Finds the scale factor to put max value between 1 and TBD.
	 *
	 * @param scale The output parameter containing the found scale.
	 * @param recipScale The output parameter containing the reciprocal
	 * of the found scale.
	 */
    void getScale(MlScalar& scale, MlScalar& recipScale) const;

    /**
	 * @brief Accesses indexed component of vector.
	 */
    MlScalar & operator [](int i) { return (vec[i]); }

    /**
	 * @brief Accesses indexed component of vector.
	 */
    const MlScalar & operator [](int i) const { return (vec[i]); }

    /**
	 * @brief Multiplication operator.
	 *
	 * This operator performs a component-wise scalar multiplication operation.
	 *
  	 * @return The result of the multiplication is returned as another vector.
	 */
    MlVector4 &	operator *=(MlScalar d);

	/**
	 * @brief Division operator.
	 *
	 * This operator performs a component-wise scalar division operation.
	 *
	 * @return The result of the division is returned as another vector.
	 */
    MlVector4 &	operator /=(MlScalar d)
	{ return *this *= mlReciprocal(d); }

    /**
	 * @brief Addition operator.
	 *
	 * This opertaor performs a component-wise vector addition operation.
	 *
	 * @return The result of the addition is returned as another vector.
	 */
    MlVector4 &	operator +=(const MlVector4 &u);

    /**
	 * @brief Subtraction operator.
	 *
	 * This operator performs a component-wise vector subtraction operation.
	 *
	 * @return The result of the subtraction is returned as another vector.
	 *
	 */
    MlVector4 &	operator -=(const MlVector4 &u);

    /**
	 * @brief Unary negation operator.
	 *
	 * This operator performs a nondestructive unary negation operation.
	 *
	 * @return The result of the negation is returned as another vector.
	 */
    MlVector4	operator -() const;

    /**
	 * @brief Binary scalar multiplication operator.
	 *
	 * This operator performs a component-wise binary scalar multiplication operation.
	 *
	 * @return The result of the multiplication is returned as another vector.
	 */
    MLMATH_API friend MlVector4	operator *(const MlVector4 &v, MlScalar d);

	/**
	 * @brief Binary scalar multiplication operator.
	 *
	 * This operator performs a component-wise binary scalar multiplication operation.
	 *
	 * @return The result of the multiplication is returned as another vector.
	 */
    MLMATH_API friend MlVector4	operator *(MlScalar d, const MlVector4 &v)
	{ return v * d; }

	/**
	 * @brief Binary scalar division operator.
	 *
	 * This operator performs a component-wise binary scalar division operation.
	 *
	 * @return The result of the division is returned as another vector.
	 */
    MLMATH_API friend MlVector4	operator /(const MlVector4 &v, MlScalar d)
	{ return v * mlReciprocal(d); }

    /**
	 * @brief Binary vector addition operator.
	 *
	 * This operator performs a component-wise binary vector addition operation.
	 *
	 * @return The result of the addition is returned as another vector.
	 */
    MLMATH_API friend MlVector4	operator +(const MlVector4 &v1, const MlVector4 &v2);

    /**
	 * @brief Binary vector subtraction operator.
	 *
	 * This operator performs a component-wise binary vector subtraction operation.
	 *
	 * @return The result of the subtraction is returned as another vector.
	 */
    MLMATH_API friend MlVector4	operator -(const MlVector4 &v1, const MlVector4 &v2);

    /**
	 * @brief Equality comparison operator.
	 *
	 * This operator is used to determine whether two vectors are equal.
	 *
	 * @return If the vectors are equal, then 1 will be returned.
	 * Otherwise 0 will be returned if the vectors are not equal.
	 */
    MLMATH_API friend int operator ==(const MlVector4 &v1, const MlVector4 &v2);

    /**
	 * @brief Inequality comparison operator.
	 *
	 * This operator is used to determine whether two vectors are not equal.
	 *
	 * @return If the vectors are not equal, then 1 will be returned.
	 * Oterwise 0 will be returned if the vectors are equal.
	 */
    MLMATH_API friend int operator !=(const MlVector4 &v1, const MlVector4 &v2)
	{ return !(v1 == v2); }

    /**
	 * @brief Equality comparison within given tolerance.
	 *
	 * The tolerance is determined by the square of the length of the maximum
	 * distance between the two vectors.
	 *
	 * @param v The other vector to compare.
	 * @param tolerance The value to determine equivalance.
	 *
	 * @return If this vector is equal to the specified vector, v, then 1 will be returned.
	 * Otherwise 0 will be returned if the vectors are not equal.
	 */
    int equals(const MlVector4 v, MlScalar tolerance) const;

    /**
	 * @brief Obtain a vector whose elements are zero.
	 *
	 * @return A vector is returned.
	 */
    static const MlVector4 zero;

  protected:

	/** Storage for vector components. */
    MlScalar vec[4];
};



#if 0
//  3D vector used to represent points or directions. Each component of
//  the vector is a short integer.
//
//  WARNING!!!!!  Transcription of arrays of this class assume that the
//                only data stored in this class are three consecutive values.
//                Do not add any extra data members!!!

class MLMATH_API MlVector3s 
{ 
  public:

    // Default constructor.
    MlVector3s() { }

    // Constructor given an array of 3 components.
    MlVector3s(const short v[3])
	{ vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; }

    // Constructor given 3 individual components.
    MlVector3s(short x, short y, short z)
	{ vec[0] = x; vec[1] = y; vec[2] = z; }

    // Returns right-handed cross product of vector and another vector.
    MlVector3s	cross(const MlVector3s &v) const;

    // Returns dot (inner) product of vector and another vector.
    int	dot(const MlVector3s &v) const;

    // Returns pointer to array of 3 components.
    const short	*getValue() const { return vec; }

    // Returns 3 individual components.
    void getValue(short &x, short &y, short &z) const;

    // Returns geometric length of vector.
    MlScalar length() const;

    // Changes vector to be unit length, returns original length.
    int	normalize();

    // Negates each component of vector in place.
    void negate();

    // Sets value of vector from array of 3 components.
    MlVector3s & setValue(const short v[3])
	{ vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; return *this; }

    // Sets value of vector from 3 individual components.
    MlVector3s & setValue(short x, short y, short z)
	{ vec[0] = x; vec[1] = y; vec[2] = z; return *this; }

    // Sets value of vector to be convex combination of 3 other.
    // vectors, using barycentic coordinates
    MlVector3s & setValue(const MlVector3s &barycentic,
		const MlVector3s &v0, const MlVector3s &v1, const MlVector3s &v2);

    // Accesses indexed component of vector.
    short & operator [](int i) { return (vec[i]); }
    const short & operator [](int i) const { return (vec[i]); }

    // Component-wise scalar multiplication and division operators.
    MlVector3s & operator *=(short d);

    MlVector3s & operator /=(short d) 
	{ return *this *= ((short)(1.0 / d)); } // XXX: THIS IS BOGUS!

    // Component-wise vector addition and subtraction operators.
    MlVector3s & operator +=(MlVector3s v);
    MlVector3s & operator -=(MlVector3s v);

    // Nondestructive unary negation - returns a new vector.
    MlVector3s	operator -() const;

    // Component-wise binary scalar multiplication and division operators.
    MLMATH_API friend MlVector3s operator *(const MlVector3s &v, short d);
    MLMATH_API friend MlVector3s operator *(short d, const MlVector3s &v)
	{ return v * d; }
    MLMATH_API friend MlVector3s operator /(const MlVector3s &v, short d)
	{ return v * (1 / d); }

    // Component-wise binary vector addition and subtraction operators.
    MLMATH_API friend MlVector3s operator +(const MlVector3s &v1, const MlVector3s &v2);

    MLMATH_API friend MlVector3s operator -(const MlVector3s &v1, const MlVector3s &v2);

    // Equality comparison operator.
    MLMATH_API friend int		operator ==(const MlVector3s &v1, const MlVector3s &v2);

    // Inequality comparison operator.
    MLMATH_API friend int		operator !=(const MlVector3s &v1, const MlVector3s &v2)
	{ return !(v1 == v2); }

    // Equality comparison within given tolerance - the square of the
    // length of the maximum distance between the two vectors.
    int equals(const MlVector3s v, short tolerance) const;

    // Returns principal axis that is closest (based on maximum dot
    // product) to this vector.
    MlVector3s getClosestAxis() const;

  protected:

	// Storage for vector components.
    short vec[3];
};
#endif /* 0 */


#endif /* VECTOR_H_INCLUDED */
