/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file angle.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * This file contains utilities for doing conversions to angles, which use 2PI == 0x10000
 * in fixed-point mode and regular floating-point values in float mode.
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

#ifndef ANGLE_H_INCLUDED
#define ANGLE_H_INCLUDED

// include Magic Lantern math header files
#include <math/scalar.h>

/** @brief The angle value for 0. */
#define ML_ANGLE_ZERO  ML_SCALAR_ZERO
/** @brief The angle value for 2PI. */
#define ML_ANGLE_TWO_PI  ML_SCALAR_ONE
/** @brief The angle value for PI */
#define ML_ANGLE_PI  ML_SCALAR_HALF
#if ML_FIXED_POINT
/**
 * @brief The angle value for PI/2.
 *
 * This is the definition for the fixed-point libraries. For the floating-point
 * libraries, the definition is ML_SCALAR(0.25f).
 */
#define ML_ANGLE_PI_HALF mlScalarSetValue((ML_FIXED_SCALE_I)>>2)
/**
 * @brief The angle value for PI/4.
 *
 * This is the definition for the fixed-point libraries. For the floating-point
 * libraries, the definition is ML_SCALAR(0.125f).
 */
#define ML_ANGLE_PI_FOURTH mlScalarSetValue((ML_FIXED_SCALE_I)>>3)
#else
#define ML_ANGLE_PI_HALF ML_SCALAR(0.25f)
#define ML_ANGLE_PI_FOURTH ML_SCALAR(0.125f)
#endif

// Functions for doing conversions to angles, which use 2PI == 0x10000
// in fixed and regular floating point values in float mode.

/**
 * @brief Convert angle to degrees [z = a * 360].
 *
 * The mlAngleToDegrees() function converts the specified angle value into
 * degrees by multiplying it by 360.
 *
 * @param a The angle to convert, as a Magic Lantern scalar.
 *
 * @return A Magic Lantern scalar primitive is returned.
 */
inline MlScalar 
mlAngleToDegrees( const MlScalar a ) 
{
    return mlMul(ML_SCALAR(360),a); 
}


/**
 * @brief Convert angle to radians [z = a * 2PI].
 *
 * The mlAngleToRadians() function converts the specified angle value into
 * radians by multiplying it by 2PI.
 *
 * @param a The angle to convert, as a Magic Lantern scalar.
 *
 * @return A Magic Lantern scalar primitive is returned.
 */
inline MlScalar
mlAngleToRadians( const MlScalar a ) 
{
    return mlMul(ML_SCALAR_TWO_PI,a); 
}


/**
 * @brief Convert degrees to angle [z = s / 360].
 *
 * The mlDegreesToAngle() function converts the specified degree value into
 * an angle by dividing it by 360.
 *
 * @param s The degree to convert, as a Magic Lantern scalar.
 *
 * @return A Magic Lantern scalar primitive is returned.
 */
inline MlScalar
mlDegreesToAngle( const MlScalar s ) 
{
    // Divide by 360 as 1.42/512.
#if ML_FIXED_POINT
    MlScalar tmp = mlMul(s,ML_SCALAR(1.42222222222222222222));
    long val = mlScalarGetValue(tmp);
    val >>= 9;
    tmp = mlScalarSetValue(val);
    return tmp;
#else
    return mlMul(s,ML_SCALAR(2.77777777777777777e-3)); 
#endif
}


/**
 * @brief Convert radians to angle [z = s / 2PI].
 *
 * The mlRadiansToAngle() function converts the specified radian value into
 * an angle by dividing it by 2PI.
 *
 * @param s The degree to convert, as a Magic Lantern scalar.
 *
 * @return A Magic Lantern scalar primitive is returned.
 */
inline MlScalar 
mlRadiansToAngle( const MlScalar s ) 
{
    // Divide by 2PI as 1/2PI = 5.09/32
#if ML_FIXED_POINT
    MlScalar tmp = mlMul(s,ML_SCALAR(5.09295817894065075808));
    long val = mlScalarGetValue(tmp);
    val >>= 5;
    tmp = mlScalarSetValue(val);
    return tmp;
#else
    return mlMul(s,ML_SCALAR(0.15915494309189533619f));
#endif
}


/**
 * @brief Convert an angle to a floating-point value.
 *
 * The mlAngleToFloat() function converts an angle represented as a
 * Magic Lantern scalar primitive into its floating-point representation.
 *
 * @param a The angle represented as a Magic Lantern scalar primitive.
 *
 * @return The angle is returned as a floating-point value.
 */
inline float
mlAngleToFloat( const MlScalar a ) 
{
    return mlScalarToFloat( a ); 
}

/**
 * @brief Convert a floating-point value to a Magic Lantern scalar value.
 *
 * The mlFloatToAngle() function converts an angle represented as a
 * floating-point value into its Magic Lantern scalar representation.
 *
 * @param f The angle represented as a floating-point value.
 *
 * @return The angle is returned as a Magic Lantern scalar primitive.
 */
inline MlScalar
mlFloatToAngle( const float f ) 
{
    return mlFloatToScalar( f ); 
}


#endif /* ANGLE_H_INCLUDED */
