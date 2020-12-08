/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file asine.h
 * @ingroup MlMath
 *
 * This file contains the utilities for computing the arc sine and arc cosine of
 * a Magic Lantern scalar primitive.
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

#ifndef ASINE_H_INCLUDED
#define ASINE_H_INCLUDED


//Iinclude Magic Lantern math header files.
#include <math/mlmath.h>
#include <math/scalar.h>
#include <math/angle.h>

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
 * @brief The arc sine function for a Magic Lantern fixed-point Scalar primitive
 * [z = arcsin(x)].
 *
 * The FixedAsin() function calculates the arc sine of x; that is the value whose sine is x.
 * If x falls outside the range -1 to 1, FixedAsin() fails and <b>errno</b> is set. 
 * The usage should be "z = FixedAsin(x)" where z and x are MlScalars.
 * This function uses a fixed-point algorithm for determinig the arc sine value.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The FixedAsin() function returns the arc sine in radians and the value
 * is mathematically defined to be between -PI/2 and PI/2 (inclusive).
 * The return value will be a Magic Lantern scalar primitive. 
 */
MLMATH_API MlScalar FixedAsin( const MlScalar x );
/**
 * @brief The arc cosine function for a Magic Lantern fixed-point Scalar primitive
 * [z = arccos(x)].
 *
 * The FixedAcos() function calculates the arc cosine of x; that is the value whose cosine is x.
 * If x falls outside the range -1 to 1, FixedAcos() fails and <b>errno</b> is set. 
 * The usage should be "z = FixedAcos(x)" where z and x are MlScalars.
 * This function uses a fixed-point algorithm for determinig the arc sine value.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The FixedAcos() function returns the arc cosine in radians and the value
 * is mathematically defined to be between 0 and PI (inclusive).
 * The return value will be a Magic Lantern scalar primitive. 
 */
MLMATH_API MlScalar FixedAcos( const MlScalar x );
#endif


/**
 * @brief The arc sine function for a Magic Lantern Scalar primitive [z = arcsin(x)].
 *
 * The mlAsin() function calculates the arc sine of x; that is the value whose sine is x.
 * If x falls outside the range -1 to 1, mlAsin() fails and <b>errno</b> is set. 
 * The usage should be "z = mlAsin(x)" where z and x are MlScalars.
 *
 * This function is available for both the floating-point and the fixed-point versions of
 * the Magic Lantern Math libraries. It is the preferred way for calculating the arc
 * sine of a Magic Lantern scalar primitive.
 *
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The mlAsin() function returns the arc sine in radians and the value
 * is mathematically defined to be between -PI/2 and PI/2 (inclusive).
 * The return value will be a Magic Lantern scalar primitive. 
 */
MLMATH_API inline MlScalar 
mlAsin( const MlScalar x ) 
{
#if ML_FIXED_POINT
	// XXX - Convert this to real fixed-point implementation!
	return FixedAsin( x );
#else
	return mlRadiansToAngle(mlFloatToScalar(asinf(mlScalarToFloat(x))));
#endif
}


/**
 * @brief The arc cosine function for a Magic Lantern Scalar primitive [z = arccos(x)].
 *
 * The mlAcos() function calculates the arc cosine of x; that is the value whose cosine is x.
 * If x falls outside the range -1 to 1, mlAcos() fails and <b>errno</b> is set. 
 * The usage should be "z = mlAcos(x)" where z and x are MlScalars.
 *
 * This function is available for both the floating-point and the fixed-point versions of
 * the Magic Lantern Math libraries. It is the preferred way for calculating the arc
 * cosine of a Magic Lantern scalar primitive.
 *
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The mlAcos() function returns the arc cosine in radians and the value
 * is mathematically defined to be between 0 and PI (inclusive).
 * The return value will be a Magic Lantern scalar primitive. 
 */
MLMATH_API inline MlScalar
mlAcos( const MlScalar x )
{
#if ML_FIXED_POINT
	// XXX - Convert this to real fixed-point implementation!
	return FixedAcos( x );
#else
	return mlRadiansToAngle(mlFloatToScalar(acosf(mlScalarToFloat(x))));
#endif
}


#endif /* ASINE_H_INCLUDED */
