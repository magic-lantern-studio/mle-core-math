/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file atan.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * This file contains the utilities for computing the arc tangent of
 * a Magic Lantern scalar primitive.
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

#ifndef ATAN_H_INCLUDED
#define ATAN_H_INCLUDED


// include Magic Lantern math header files
#include <math/mlmath.h>
#include <math/scalar.h>
#include <math/angle.h>

#if !defined(__sgi)
// XXX - on platforms that don't have single-precision float
// trig functions, use the double versions, at least for now.
// See also scalar.h

//#define atanf(x) ((float)atan((double)(x)))
//#define fatan(x) ((float)atan((double)(x)))
//#define atan2f(y,x) ((float)atan2((double)(y),(double)(x)))
//#define fatan2(y,x) ((float)atan2((double)(y),(double)(x)))

#endif /* !defined(__sgi) */

#if ML_FIXED_POINT
// Debugging stuff for now.
#include <math.h>
#include <stdio.h>
#endif

// Really need this for all time.
#if ! ML_FIXED_POINT
#include <math.h>
#endif


#if ML_FIXED_POINT
/**
 * @brief An arc tangent function for a Magic Lantern fixed-point Scalar primitive
 * [z = atan2(x,y)].
 *
 * The FixedAtan2() function calculates the arc tangent of the two variables x and y.
 * It is similar to calculating the arc tangent of y / x, except that the signs of
 * both arguments are used to determine the quadrant of the result.
 * The usage should be "z = FixedAtan2(x,y)" where z, y and x are MlScalars.
 * This function uses a fixed-point algorithm for determinig the arc tangent value.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param y A Magic Lantern Scalar primitive.
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The FixedAtan2() function returns the arc tangent in radians and the value
 * is mathematically defined to be between -PI and PI (inclusive).
 * The return value will be a Magic Lantern scalar primitive. 
 */
MLMATH_API MlScalar FixedAtan2( const MlScalar y, const MlScalar x);
/**
 * @brief An arc tangent function for a Magic Lantern fixed-point Scalar primitive
 * [z = atan2(x,y)].
 *
 * The FixedAtan2Quick() function calculates the arc tangent of the two variables x and y.
 * It is similar to calculating the arc tangent of y / x, except that the signs of
 * both arguments are used to determine the quadrant of the result.
 * The usage should be "z = FixedAtan2Quick(x,y)" where z, y and x are MlScalars.
 * This function uses a fixed-point algorithm for determinig the arc tangent value.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param y A Magic Lantern Scalar primitive.
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The FixedAtan2Quick() function returns the arc tangent in radians and the value
 * is mathematically defined to be between -PI and PI (inclusive).
 * The return value will be a Magic Lantern scalar primitive. The value calculated
 * by FixedAtan2Quick() will not be as accurate as that returned by FixedAtan2() since
 * it is an approximation.
 */
MLMATH_API MlScalar FixedAtan2Quick( const MlScalar y, const MlScalar x );
#endif


/**
 * @brief An arc tangent function for a Magic Lantern Scalar primitive [z = atan2(x,y)].
 *
 * The mlAtan2() function calculates the arc tangent of the two variables x and y.
 * It is similar to calculating the arc tangent of y / x, except that the signs of
 * both arguments are used to determine the quadrant of the result.
 * The usage should be "z = mlAtan2(x,y)" where z, y and x are MlScalars.
 *
 * This function is available for both the floating-point and the fixed-point versions of
 * the Magic Lantern Math libraries. It is the preferred way for calculating the arc
 * tangent of a Magic Lantern scalar primitive.
 *
 * @param y A Magic Lantern Scalar primitive.
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The mlAtan2() function returns the arc tangent in radians and the value
 * is mathematically defined to be between -PI and PI (inclusive).
 * The return value will be a Magic Lantern scalar primitive. 
 */
MLMATH_API inline MlScalar
mlAtan2( const MlScalar y, const MlScalar x)
{
#if ML_FIXED_POINT
	// XXX - Convert this to real fixed-point implementation!
	return FixedAtan2(y, x);
#else
	return mlRadiansToAngle(mlFloatToScalar(atan2f(mlScalarToFloat(y),mlScalarToFloat(x))));
#endif
}


/**
 * @brief An arc tangent function for a Magic Lantern Scalar primitive [z = atan2(x,y)].
 *
 * The mlAtan2Quick() function calculates the arc tangent of the two variables x and y.
 * It is similar to calculating the arc tangent of y / x, except that the signs of
 * both arguments are used to determine the quadrant of the result.
 * The usage should be "z = mlAtan2uick(x,y)" where z, y and x are MlScalars.
 *
 * This function is available for both the floating-point and the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param y A Magic Lantern Scalar primitive.
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The mlAtan2Quick() function returns the arc tangent in radians and the value
 * is mathematically defined to be between -PI and PI (inclusive).
 * The return value will be a Magic Lantern scalar primitive. The value calculated
 * by mlAtan2Quick() will not be as accurate as that returned by mlAtan2() since
 * it is an approximation.
 */
MLMATH_API inline MlScalar
mlAtan2Quick( const MlScalar y, const MlScalar x )
{
	// XXX - Convert this to something quicker.
	return mlAtan2(y,x);
}


#endif /* ATAN_H_INCLUDED */
