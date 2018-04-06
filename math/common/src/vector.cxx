
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
//  For information concerning this source file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// include system header files
#include <math.h>

// include Mltuer math header files
#include "math/vector.h"


//////////////////////////////////////////////////////////////////////////////
//
// Handy routine for scaling a MlVectorN to a size that is suitable
// for squaring its components.  The max sized number is scaled to lie
// between 1 and 64, while the others are scaled by the same factor.
//
//////////////////////////////////////////////////////////////////////////////

static void 
calcScale( 
#if ML_FIXED_POINT
          const MlScalar *vec, 
          const int n, 
#else
          const MlScalar *, 
          const int, 
#endif
          MlScalar& scale, MlScalar& recipScale )
{
#if ML_FIXED_POINT
    int i;
    unsigned long mxVal;
    unsigned long logScale;
    MlScalar mx, v;

    mx = mlAbs(vec[0]);

    for (i=1; i<n; i++) {
        v = mlAbs(vec[i]);
        mx = (mx > v) ? mx : v;
    }

    if (mx == ML_SCALAR_ZERO) {
        scale = ML_SCALAR_ONE;
        recipScale = ML_SCALAR_ONE;
        return;
    }

    // Use (1<<6) as a number that gets some bits > 1, because squaring
    // sends bits away from 1.  Don\'t want all the useful bits to
    // be < 1.
    
    logScale = 0;
    mxVal = mlScalarGetValue( mx );

    if (mx > ML_SCALAR_ONE) {
        while (mxVal > (ML_FIXED_SCALE_I << 6)) {
            mxVal >>= 6;
            logScale += 6;
        }
        scale = mlScalarSetValue( ML_FIXED_SCALE_I >> logScale );
        recipScale = mlScalarSetValue( ML_FIXED_SCALE_I << logScale );
    }
    else {
        while (mxVal < ML_FIXED_SCALE_I) {
            mxVal <<= 6;
            logScale += 6;
        }
        scale = mlScalarSetValue( ML_FIXED_SCALE_I << logScale );
        recipScale = mlScalarSetValue( ML_FIXED_SCALE_I >> logScale );
    }

    return;
#else
    // Don\'t touch the vector.

    scale = ML_SCALAR_ONE;
    recipScale = ML_SCALAR_ONE;

    return;
#endif
}

//////////////////////////////////////////////////////////////////////////////
//
// Vec3f class
//
//////////////////////////////////////////////////////////////////////////////


const MlVector3 MlVector3::zero (ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO);


int MlVector3::isZero(void) const
//
// Returns true if all elements are zero
//
{
    return (vec == zero);
}

// constructor that creates vector from intersection of three planes
//

MlVector3 MlVector3::cross(const MlVector3&v) const
//
// Returns right-handed cross product of vector and another vector
//
{
    return MlVector3(mlMul(vec[1], v.vec[2]) - mlMul(vec[2], v.vec[1]),
                     mlMul(vec[2], v.vec[0]) - mlMul(vec[0], v.vec[2]),
                     mlMul(vec[0], v.vec[1]) - mlMul(vec[1], v.vec[0]));
}


MlScalar MlVector3::dot(const MlVector3&v) const
//
// Returns dot (inner) product of vector and another vector
//
{
    return (mlMul(vec[0], v.vec[0]) +
            mlMul(vec[1], v.vec[1]) +
            mlMul(vec[2], v.vec[2]));
}


void MlVector3::getValue(MlScalar&x, MlScalar&y, MlScalar&z) const
//
// Returns 3 individual components
//
{
    x = vec[0];
    y = vec[1];
    z = vec[2];
}


MlScalar MlVector3::length() const
//
// Returns geometric length of vector.  Do it without computing
// a large or small squared number in fixed point, but use the
// dynamic range of the floating point numbers if you can.
//
{
#if ML_FIXED_POINT
    // Somewhat more expensive, but avoids overflow.

    // Scale it into an appropriate range for the length calculation.
    MlScalar scale      = ML_SCALAR_ZERO;
    MlScalar recipScale = ML_SCALAR_ZERO;

    getScale( scale, recipScale );
    MlVector3 tmp;
    tmp[0] = mlMul(vec[0], scale);
    tmp[1] = mlMul(vec[1], scale);
    tmp[2] = mlMul(vec[2], scale);

    MlScalar len = mlSqrt(mlSquare(tmp[0]) + mlSquare(tmp[1]) + mlSquare(tmp[2]));
    return mlMul( len, recipScale );

#else /* ML_FIXED_POINT */
    return mlSqrt(mlSquare(vec[0]) + mlSquare(vec[1]) + mlSquare(vec[2]));
#endif /* ML_FIXED_POINT */
}


MlScalar MlVector3::approximateLength() const
// Fast approximation to the length of a vector.  3-D Euclidean distance
// approximation: c1 = 15/16 , c2 = c3 = 3/8 and max(e) = 7.7 %.  Based on
// "Fast Linear Approximations of Euclidean Distance in Higher Dimensions"
// by Yoshikazu Ohashi, yoshi@cognex.com in "Graphics Gems IV", Academic
// Press, 1994
{
    MlScalar a = vec[0];
    MlScalar b = vec[1];
    MlScalar c = vec[2];

    // set a, b, and c to absolute values of x, y, and z coordinates
    a = mlAbs(a);
    b = mlAbs(b);
    c = mlAbs(c);

    // test and swap so that a is the largest coordinate
    if( a < b ) {MlScalar x = a;  a = b;  b = x;}
    if( a < c ) {MlScalar x = a;  a = c;  c = x;}

//  float exact = v->length();
//  float approx = ((a * 0.9375) + ((b + c) * 0.375));
//  printf ("exact = %8.3f approx = %8.3f    error = %4.1f%%\n",
//         exact, approx, ((exact - approx)/exact)*100);

    return (mlMul(a, ML_SCALAR(0.9375f)) + mlMul(b + c, ML_SCALAR(0.375)));
}


void MlVector3::negate()
//
// Negates each component of vector in place
//
{
    vec[0] = -vec[0];
    vec[1] = -vec[1];
    vec[2] = -vec[2];
}


MlScalar MlVector3::normalize()
//
// Changes vector to be unit length
//
{
    if (isZero()) {
        return ML_SCALAR_ZERO;
    }

#if ML_FIXED_POINT
    // Scale it into an appropriate range for the length calculation.
    MlScalar scale      = ML_SCALAR_ZERO;
    MlScalar recipScale = ML_SCALAR_ZERO;

    getScale( scale, recipScale );
    (*this) *= scale;
#endif

    MlScalar len = length();

    if (len != ML_SCALAR_ZERO)
        (*this) *= mlReciprocal(len);
    else 
        setValue(ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ZERO);

    return len;
}


MlScalar MlVector3::approximateNormalize()
{
    MlScalar length = this->approximateLength();
    if (length != ML_SCALAR_ZERO) (*this) /= length;
    return length;
}


//
// Changes vector to have length of input scale factor.
//
MlVector3&    
MlVector3::scaleTo( const MlScalar newScale )
{
    MlScalar oldScale = length();

    if (oldScale != ML_SCALAR_ZERO) {
        oldScale = mlDiv(newScale, oldScale);
        (*this) *= oldScale;
    }
    
    return *this;
}


void MlVector3::interpolate (MlScalar weight,
    const MlVector3 *v0, const MlVector3 *v1,
    MlVector3 *result)
// Linear interpolation, aka lerp.  Set "result" to the interpolation
// by "weight" from "v0" (when weight=0) to "v1" (when weight=1)
{
    (*result) = (((*v0) * (ML_SCALAR_ONE - weight)) +
                 ((*v1) * weight));
}


MlVector3& MlVector3::setValue(const MlVector3&barycentric,
    const MlVector3&v0, const MlVector3&v1, const MlVector3&v2)
{
    *this = v0 * barycentric[0] + v1 * barycentric[1] + v2 * barycentric[2];
    return (*this);
}
    

void
MlVector3::getScale(MlScalar& scale, MlScalar& recipScale) const
//
// Finds the scale factor to put max value between 1 and TBD.
//
{
    calcScale( vec, 3, scale, recipScale );
}


MlVector3& MlVector3::operator *=(MlScalar d)
//
// Component-wise scalar multiplication operator
//
{
    mlMulBy(vec[0], d);
    mlMulBy(vec[1], d);
    mlMulBy(vec[2], d);

    return *this;
}


MlVector3& MlVector3::operator +=(MlVector3 v)
//
// Component-wise vector addition operator
//
{
    vec[0] += v.vec[0];
    vec[1] += v.vec[1];
    vec[2] += v.vec[2];

    return *this;
}


MlVector3& MlVector3::operator -=(MlVector3 v)
//
// Component-wise vector subtraction operator
//
{
    vec[0] -= v.vec[0];
    vec[1] -= v.vec[1];
    vec[2] -= v.vec[2];

    return *this;
}


MlVector3 MlVector3::operator -() const
//
// Nondestructive unary negation - returns a new vector
//
{
    return MlVector3(-vec[0], -vec[1], -vec[2]);
}


MlVector3 operator *(const MlVector3&v, MlScalar d)
//
// Component-wise binary scalar multiplication operator
//
{
    return MlVector3(mlMul(v.vec[0], d),
                     mlMul(v.vec[1], d),
                     mlMul(v.vec[2], d));
}


MlVector3 operator +(const MlVector3&v1, const MlVector3&v2)
//
// Component-wise binary vector addition operator
//
{
    return MlVector3(v1.vec[0] + v2.vec[0],
                     v1.vec[1] + v2.vec[1],
                     v1.vec[2] + v2.vec[2]);
}


MlVector3 operator -(const MlVector3&v1, const MlVector3&v2)
//
// Component-wise binary vector subtraction operator
//
{
    return MlVector3(v1.vec[0] - v2.vec[0],
                     v1.vec[1] - v2.vec[1],
                     v1.vec[2] - v2.vec[2]);
}


int operator ==(const MlVector3&v1, const MlVector3&v2)
//
// Equality comparison operator. Componenents must match exactly.
//
{
    return (v1.vec[0] == v2.vec[0]&&
            v1.vec[1] == v2.vec[1]&&
            v1.vec[2] == v2.vec[2]);
}


int MlVector3::equals(const MlVector3 v, MlScalar tolerance) const
//
// Equality comparison operator within a tolerance.
//
{
    MlVector3 diff = *this - v;

    return diff.dot(diff) <= tolerance;
}


MlVector3 MlVector3::getClosestAxis() const
//
// Returns principal axis that is closest (based on maximum dot
// product) to this vector.
//
{
    MlVector3    axis(ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ZERO), bestAxis;
    MlScalar    d, max = mlFloatToScalar(-21.234f);

#define TEST_AXIS()              \
    if ((d = dot(axis)) > max) { \
    max = d;                     \
    bestAxis = axis;             \
    }

    axis[0] = ML_SCALAR_ONE;     // +x axis
    TEST_AXIS();

    axis[0] = -ML_SCALAR_ONE;    // -x axis
    TEST_AXIS();
    axis[0] = ML_SCALAR_ZERO;

    axis[1] = ML_SCALAR_ONE;     // +y axis
    TEST_AXIS();

    axis[1] = -ML_SCALAR_ONE;    // -y axis
    TEST_AXIS();
    axis[1] = ML_SCALAR_ZERO;

    axis[2] = ML_SCALAR_ONE;     // +z axis
    TEST_AXIS();

    axis[2] = -ML_SCALAR_ONE;    // -z axis
    TEST_AXIS();

#undef TEST_AXIS

    return bestAxis;
}


#if 0
//////////////////////////////////////////////////////////////////////////////
//
// Vec2s class
//
//////////////////////////////////////////////////////////////////////////////


int MlVector2s::dot(const MlVector2s&v) const
//
// Returns dot (inner) product of vector and another vector
//
{
    return vec[0] * v.vec[0] + vec[1] * v.vec[1];
}


void MlVector2s::getValue(short&x, short&y) const
//
// Returns 2 individual components
//
{
    x = vec[0];
    y = vec[1];
}


void MlVector2s::negate()
//
// Negates each component of vector in place
//
{
    vec[0] = -vec[0];
    vec[1] = -vec[1];
}


MlVector2s& MlVector2s::setValue(const short v[2])    
//
// Sets value of vector from array of 2 components
//
{
    vec[0] = v[0];
    vec[1] = v[1];

    return (*this);
}


MlVector2s& MlVector2s::setValue(short x, short y)    
//
// Sets value of vector from 2 individual components
//
{
    vec[0] = x;
    vec[1] = y;

    return (*this);
}


MlVector2s& MlVector2s::operator *=(int d)
//
// Component-wise scalar multiplication operator
//
// Note: didn't complain about assignment of int to short !
{
    vec[0] *= d;
    vec[1] *= d;

    return *this;
}


MlVector2s& MlVector2s::operator *=(MlScalar d)
{
    vec[0] = short(mlScalarToLong(vec[0] * d));
    vec[1] = short(mlScalarToLong(vec[1] * d));

    return *this;
}


MlVector2s& MlVector2s::operator /=(int d)
//
// Component-wise scalar division operator
//
{
    vec[0] /= d;
    vec[1] /= d;

    return *this;
}


MlVector2s& MlVector2s::operator +=(const MlVector2s&u)
//
// Component-wise vector addition operator
//
{
    vec[0] += u.vec[0];
    vec[1] += u.vec[1];

    return *this;
}


MlVector2s& MlVector2s::operator -=(const MlVector2s&u)
//
// Component-wise vector subtraction operator
//
{
    vec[0] -= u.vec[0];
    vec[1] -= u.vec[1];

    return *this;
}


MlVector2s MlVector2s::operator -() const
//
// Nondestructive unary negation - returns a new vector
//
{
    return MlVector2s(-vec[0], -vec[1]);
}


MlVector2s operator *(const MlVector2s&v, int d)
//
// Component-wise binary scalar multiplication operator
//
{
    return MlVector2s(v.vec[0] * d, v.vec[1] * d);
}


MlVector2s operator *(const MlVector2s&v, MlScalar d)
{
    return MlVector2s(short(mlScalarToLong(v.vec[0] * d)), short(mlScalarToLong(v.vec[1] * d)));
}


MlVector2s operator /(const MlVector2s&v, int d)
//
// Component-wise binary scalar division operator
//
{
    return MlVector2s(
        mlScalarToLong(mlDiv(mlLongToScalar(v.vec[0]), mlLongToScalar(d))), 
        mlScalarToLong(mlDiv(mlLongToScalar(v.vec[1]),mlLongToScalar(d))));
}


MlVector2s operator +(const MlVector2s&v1, const MlVector2s&v2)
//
// Component-wise binary vector addition operator
//
{
    return MlVector2s(v1.vec[0] + v2.vec[0],
                      v1.vec[1] + v2.vec[1]);
}


MlVector2s operator -(const MlVector2s&v1, const MlVector2s&v2)
//
// Component-wise binary vector subtraction operator
//
{
    return MlVector2s(v1.vec[0] - v2.vec[0],
                      v1.vec[1] - v2.vec[1]);
}


int operator ==(const MlVector2s&v1, const MlVector2s&v2)
//
// Equality comparison operator
//
{
    return (v1.vec[0] == v2.vec[0]&&
            v1.vec[1] == v2.vec[1]);
}
#endif

//////////////////////////////////////////////////////////////////////////////
//
// Vec2f class
//
//////////////////////////////////////////////////////////////////////////////


const MlVector2 MlVector2::zero (ML_SCALAR_ZERO,ML_SCALAR_ZERO);


int MlVector2::isZero(void) const
//
// Returns true if all elements are zero
//
{
    return (vec == zero);
}

MlScalar MlVector2::dot(const MlVector2&v) const
//
// Returns dot (inner) product of vector and another vector
//
{
    return mlMul(vec[0], v.vec[0]) + mlMul(vec[1], v.vec[1]);
}


void MlVector2::getValue(MlScalar &x, MlScalar &y) const
//
// Returns 2 individual components
//
{
    x = vec[0];
    y = vec[1];
}


MlScalar MlVector2::length() const
// Returns geometric length of vector.  Do it without computing
// a large or small squared number in fixed point, but use the
// dynamic range of the floating point numbers if you can.
//
{
#if ML_FIXED_POINT
    // Scale it into an appropriate range for the length calculation.
    MlScalar scale      = ML_SCALAR_ZERO;
    MlScalar recipScale = ML_SCALAR_ZERO;

    getScale( scale, recipScale );
    MlVector2 tmp;
    tmp[0] = mlMul(vec[0], scale);
    tmp[1] = mlMul(vec[1], scale);

    MlScalar len = mlSqrt(mlSquare(tmp[0]) + mlSquare(tmp[1]));
    return mlMul( len, recipScale );

#else /* ML_FIXED_POINT */
    return mlSqrt(mlSquare(vec[0]) + mlSquare(vec[1]));
#endif /* ML_FIXED_POINT */
}


void MlVector2::negate()
//
// Negates each component of vector in place
//
{
    vec[0] = -vec[0];
    vec[1] = -vec[1];
}


MlScalar MlVector2::normalize()
//
// Changes vector to be unit length
//
{
    if (isZero()) {
        return ML_SCALAR_ZERO;
    }

#if ML_FIXED_POINT
    // Scale it into an appropriate range for the length calculation.
    MlScalar scale      = ML_SCALAR_ZERO;
    MlScalar recipScale = ML_SCALAR_ZERO;

    getScale( scale, recipScale );
    (*this) *= scale;
#endif

    MlScalar len = length();

    if (len != ML_SCALAR_ZERO)
        (*this) *= mlReciprocal(len);
    else
        setValue(ML_SCALAR_ZERO, ML_SCALAR_ZERO);

    return len;
}


MlVector2& MlVector2::setValue(const MlScalar v[2])    
//
// Sets value of vector from array of 2 components
//
{
    vec[0] = v[0];
    vec[1] = v[1];

    return (*this);
}


MlVector2& MlVector2::setValue(MlScalar x, MlScalar y)    
//
// Sets value of vector from 2 individual components
//
{
    vec[0] = x;
    vec[1] = y;

    return (*this);
}


void
MlVector2::getScale(MlScalar& scale, MlScalar& recipScale) const
//
// Finds the scale factor to put max value between 1 and TBD.
//
{
    calcScale( vec, 2, scale, recipScale );
}


MlVector2& MlVector2::operator *=(MlScalar d)
//
// Component-wise scalar multiplication operator
//
{
    mlMulBy(vec[0], d);
    mlMulBy(vec[1], d);

    return *this;
}


MlVector2& MlVector2::operator +=(const MlVector2&u)
//
// Component-wise vector addition operator
//
{
    vec[0] += u.vec[0];
    vec[1] += u.vec[1];

    return *this;
}


MlVector2& MlVector2::operator -=(const MlVector2&u)
//
// Component-wise vector subtraction operator
//
{
    vec[0] -= u.vec[0];
    vec[1] -= u.vec[1];

    return *this;
}


MlVector2 MlVector2::operator -() const
//
// Nondestructive unary negation - returns a new vector
//
{
    return MlVector2(-vec[0], -vec[1]);
}


MlVector2 operator *(const MlVector2&v, MlScalar d)
//
// Component-wise binary scalar multiplication operator
//
{
    return MlVector2(mlMul(v.vec[0], d), mlMul(v.vec[1], d));
}


MlVector2 operator +(const MlVector2&v1, const MlVector2&v2)
//
// Component-wise binary vector addition operator
//
{
    return MlVector2(v1.vec[0] + v2.vec[0],
                     v1.vec[1] + v2.vec[1]);
}


MlVector2 operator -(const MlVector2&v1, const MlVector2&v2)
//
// Component-wise binary vector subtraction operator
//
{
    return MlVector2(v1.vec[0] - v2.vec[0],
                     v1.vec[1] - v2.vec[1]);
}


int operator ==(const MlVector2&v1, const MlVector2&v2)
//
// Equality comparison operator. Componenents must match exactly.
//
{
    return (v1.vec[0] == v2.vec[0]&&
            v1.vec[1] == v2.vec[1]);
}


int MlVector2::equals(const MlVector2 v, MlScalar tolerance) const
//
// Equality comparison operator within a tolerance.
//
{
    MlVector2    diff = *this - v;

    return diff.dot(diff) <= tolerance;
}



//////////////////////////////////////////////////////////////////////////////
//
// Vec4f class
//
//////////////////////////////////////////////////////////////////////////////


const MlVector4 MlVector4::zero (ML_SCALAR_ZERO,ML_SCALAR_ZERO,
                                 ML_SCALAR_ZERO,ML_SCALAR_ZERO);


int MlVector4::isZero(void) const
//
// Returns true if all elements are zero
//
{
    return ((MlVector4)vec == zero);
}

MlScalar MlVector4::dot(const MlVector4&v) const
//
// Returns dot (inner) product of vector and another vector
//
{
    return mlMul(vec[0], v.vec[0]) + mlMul(vec[1], v.vec[1]) + 
           mlMul(vec[2], v.vec[2]) + mlMul(vec[3], v.vec[3]) ;
}


void MlVector4::getValue(MlScalar&x, MlScalar&y, MlScalar&z, MlScalar&w) const
//
// Returns 4 individual components
//
{
    x = vec[0];
    y = vec[1];
    z = vec[2];
    w = vec[3];
}


MlScalar MlVector4::length() const
// Returns geometric length of vector.  Do it without computing
// a large or small squared number in fixed point, but use the
// dynamic range of the floating point numbers if you can.
//
{
#if ML_FIXED_POINT
    // Somewhat more expensive, but avoids overflow.

    MlScalar scale      = ML_SCALAR_ZERO;
    MlScalar recipScale = ML_SCALAR_ZERO;

    getScale( scale, recipScale );
    MlVector4 tmp;
    tmp[0] = mlMul(vec[0], scale);
    tmp[1] = mlMul(vec[1], scale);
    tmp[2] = mlMul(vec[2], scale);
    tmp[3] = mlMul(vec[3], scale);

    MlScalar len = mlSqrt(mlSquare(tmp[0]) + mlSquare(tmp[1]) 
              + mlSquare(tmp[2]) + mlSquare(tmp[3]));

    return mlMul( len, recipScale );

#else /* ML_FIXED_POINT */
    return mlSqrt(mlSquare(vec[0]) + mlSquare(vec[1])
         + mlSquare(vec[2]) + mlSquare(vec[3]));
#endif /* ML_FIXED_POINT */
}


void MlVector4::negate()
//
// Negates each component of vector in place
//
{
    vec[0] = -vec[0];
    vec[1] = -vec[1];
    vec[2] = -vec[2];
    vec[3] = -vec[3];
}


MlScalar MlVector4::normalize()
//
// Changes vector to be unit length
//
{
    if (isZero()) {
        return ML_SCALAR_ZERO;
    }

#if ML_FIXED_POINT
    // Scale it into an appropriate range for the length calculation.
    MlScalar scale      = ML_SCALAR_ZERO;
    MlScalar recipScale = ML_SCALAR_ZERO;

    getScale( scale, recipScale );
    (*this) *= scale;
#endif

    MlScalar len = length();

    if (len != ML_SCALAR_ZERO)
        (*this) *= mlReciprocal(len);

    else setValue(ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ZERO);

    return len;
}


MlVector4& MlVector4::setValue(const MlScalar v[4])    
//
// Sets value of vector from array of 4 components
//
{
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    vec[3] = v[3];

    return (*this);
}


MlVector4& MlVector4::setValue(MlScalar x, MlScalar y, MlScalar z, MlScalar w)    
//
// Sets value of vector from 4 individual components
//
{
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;

    return (*this);
}


void MlVector4::getReal(MlVector3&v ) const
//
// Returns the real portion of the vector by dividing the first three
// values by the fourth.
//
{
    v[0] = mlDiv(vec[0],vec[3]);
    v[1] = mlDiv(vec[1],vec[3]);
    v[2] = mlDiv(vec[2],vec[3]);
}


void
MlVector4::getScale(MlScalar& scale, MlScalar& recipScale) const
//
// Finds the scale factor to put max value between 1 and TBD.
//
{
    calcScale( vec, 4, scale, recipScale );
}


MlVector4& MlVector4::operator *=(MlScalar d)
//
// Component-wise scalar multiplication operator
//
{
    mlMulBy(vec[0], d);
    mlMulBy(vec[1], d);
    mlMulBy(vec[2], d);
    mlMulBy(vec[3], d);

    return *this;
}

//
// Component-wise vector addition operator
//
MlVector4& MlVector4::operator +=(const MlVector4&u)
{
    vec[0] += u.vec[0];
    vec[1] += u.vec[1];
    vec[2] += u.vec[2];
    vec[3] += u.vec[3];

    return *this;
}


MlVector4& MlVector4::operator -=(const MlVector4&u)
//
// Component-wise vector subtraction operator
//
{
    vec[0] -= u.vec[0];
    vec[1] -= u.vec[1];
    vec[2] -= u.vec[2];
    vec[3] -= u.vec[3];

    return *this;
}


MlVector4 MlVector4::operator -() const
//
// Nondestructive unary negation - returns a new vector
//
{
    return MlVector4(-vec[0], -vec[1], -vec[2], -vec[3]);
}


MlVector4 operator *(const MlVector4&v, MlScalar d)
//
// Component-wise binary scalar multiplication operator
//
{
    return MlVector4(mlMul(v.vec[0], d),
                     mlMul(v.vec[1], d),
                     mlMul(v.vec[2], d),
                     mlMul(v.vec[3], d));
}


MlVector4 operator +(const MlVector4&v1, const MlVector4&v2)
//
// Component-wise binary vector addition operator
//
{
    return MlVector4(v1.vec[0] + v2.vec[0],
                     v1.vec[1] + v2.vec[1],
                     v1.vec[2] + v2.vec[2],
                     v1.vec[3] + v2.vec[3]);
}


MlVector4 operator -(const MlVector4&v1, const MlVector4&v2)
//
// Component-wise binary vector subtraction operator
//
{
    return MlVector4(v1.vec[0] - v2.vec[0],
                     v1.vec[1] - v2.vec[1],
                     v1.vec[2] - v2.vec[2],
                     v1.vec[3] - v2.vec[3]);
}


int operator ==(const MlVector4&v1, const MlVector4&v2)
//
// Equality comparison operator. Componenents must match exactly.
//
{
    return (v1.vec[0] == v2.vec[0]&&
            v1.vec[1] == v2.vec[1]&&
            v1.vec[2] == v2.vec[2]&&
            v1.vec[3] == v2.vec[3]);
}


int MlVector4::equals(const MlVector4 v, MlScalar tolerance) const
//
// Equality comparison operator within a tolerance.
//
{
    MlVector4 diff = *this - v;

    return diff.dot(diff) <= tolerance;
}


#if 0
//////////////////////////////////////////////////////////////////////////////
//
// Vec3s class
//
//////////////////////////////////////////////////////////////////////////////

// constructor that creates vector from intersection of three planes
//

MlVector3s MlVector3s::cross(const MlVector3s&v) const
//
// Returns right-handed cross product of vector and another vector
//
{
    return MlVector3s(vec[1] * v.vec[2] - vec[2] * v.vec[1],
                      vec[2] * v.vec[0] - vec[0] * v.vec[2],
                      vec[0] * v.vec[1] - vec[1] * v.vec[0]);
}


int MlVector3s::dot(const MlVector3s&v) const
//
// Returns dot (inner) product of vector and another vector
//
{
    return (vec[0] * v.vec[0] +
            vec[1] * v.vec[1] +
            vec[2] * v.vec[2]);
}


void MlVector3s::getValue(short&x, short&y, short&z) const
//
// Returns 3 individual components
//
{
    x = vec[0];
    y = vec[1];
    z = vec[2];
}


MlScalar MlVector3s::length() const
//
// Returns geometric length of vector
//
{
    return mlSqrt(mlLongToScalar(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]));
}


void MlVector3s::negate()
//
// Negates each component of vector in place
//
{
    vec[0] = -vec[0];
    vec[1] = -vec[1];
    vec[2] = -vec[2];
}


int MlVector3s::normalize()
//
// Changes vector to be unit length
//
{
    MlScalar len = length();

    if (len != ML_SCALAR_ZERO)
        (*this) *= mlReciprocal(len);
    else
        setValue(0,0,0);

    return len;
}


MlVector3s& MlVector3s::setValue(const MlVector3s&barycentric,
    const MlVector3s&v0, const MlVector3s&v1, const MlVector3s&v2)
{
    *this = v0 * barycentric[0] + v1 * barycentric[1] + v2 * barycentric[2];
    return (*this);
}
    

MlVector3s& MlVector3s::operator *=(short d)
//
// Component-wise scalar multiplication operator
//
{
    vec[0] *= d;
    vec[1] *= d;
    vec[2] *= d;

    return *this;
}


MlVector3s& MlVector3s::operator +=(MlVector3s v)
//
// Component-wise vector addition operator
//
{
    vec[0] += v.vec[0];
    vec[1] += v.vec[1];
    vec[2] += v.vec[2];

    return *this;
}


MlVector3s& MlVector3s::operator -=(MlVector3s v)
//
// Component-wise vector subtraction operator
//
{
    vec[0] -= v.vec[0];
    vec[1] -= v.vec[1];
    vec[2] -= v.vec[2];

    return *this;
}


MlVector3s MlVector3s::operator -() const
//
// Nondestructive unary negation - returns a new vector
//
{
    return MlVector3s(-vec[0], -vec[1], -vec[2]);
}


MlVector3s operator *(const MlVector3s&v, short d)
//
// Component-wise binary scalar multiplication operator
//
{
    return MlVector3s(v.vec[0] * d,
                      v.vec[1] * d,
                      v.vec[2] * d);
}


MlVector3s operator +(const MlVector3s&v1, const MlVector3s&v2)
//
// Component-wise binary vector addition operator
//
{
    return MlVector3s(v1.vec[0] + v2.vec[0],
                      v1.vec[1] + v2.vec[1],
                      v1.vec[2] + v2.vec[2]);
}


MlVector3s operator -(const MlVector3s&v1, const MlVector3s&v2)
//
// Component-wise binary vector subtraction operator
//
{
    return MlVector3s(v1.vec[0] - v2.vec[0],
                      v1.vec[1] - v2.vec[1],
                      v1.vec[2] - v2.vec[2]);
}


int operator ==(const MlVector3s&v1, const MlVector3s&v2)
//
// Equality comparison operator. Componenents must match exactly.
//
{
    return (v1.vec[0] == v2.vec[0]&&
            v1.vec[1] == v2.vec[1]&&
            v1.vec[2] == v2.vec[2]);
}


int MlVector3s::equals(const MlVector3s v, short tolerance) const
//
// Equality comparison operator within a tolerance.
//
{
    MlVector3s    diff = *this - v;

    return diff.dot(diff) <= tolerance;
}


MlVector3s MlVector3s::getClosestAxis() const
//
// Returns principal axis that is closest (based on maximum dot
// product) to this vector.
//
{
    MlVector3s axis(0, 0, 0), bestAxis;
    short d, max = -21;

#define TEST_AXIS()               \
    if ((d = dot(axis)) > max) {  \
    max = d;                      \
    bestAxis = axis;              \
    }

    axis[0] = 1;     // +x axis
    TEST_AXIS();

    axis[0] = -1;    // -x axis
    TEST_AXIS();
    axis[0] = 0;

    axis[1] = 1;     // +y axis
    TEST_AXIS();

    axis[1] = -1;    // -y axis
    TEST_AXIS();
    axis[1] = 0;

    axis[2] = 1;     // +z axis
    TEST_AXIS();

    axis[2] = -1;    // -z axis
    TEST_AXIS();

#undef TEST_AXIS

    return bestAxis;
}

#endif
