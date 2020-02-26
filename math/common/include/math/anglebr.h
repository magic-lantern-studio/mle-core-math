/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file anglebr.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * This file provides utility for integrating with the BRender
 * game engine. Utilities are provided for the conversion of angles
 * in MlScalar type to/from BRender angle types.
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

#ifndef ANGLEBR_H_INCLUDED
#define ANGLEBR_H_INCLUDED

// include Magic Lantern math header files
#include <math/scalar.h>
#include <math/angle.h>
#ifdef __sgi
#include <brender/scalar.h>
#include <brender/angles.h>
#else
#include <scalar.h>
#include <angles.h>
#endif /* __sgi */


//
// Do this in a separate header file to avoid including BRender in all scalar ops.
//

/**
 * @brief Convert from Magic Lantern angle to BRender angle.
 *
 * This routine takes into count whether fixed-point arithmetic
 * should be used.
 *
 * @param s The angle to convert.
 *
 * @return A BRender angle is returned.
 */
inline br_angle
mlAngleToBRAngle( MlScalar s )
{
#if (BASED_FLOAT || ! ML_FIXED_POINT)
    // At least one of these function calls is a no-op, and the other
    // is actually required.
    return BrScalarToAngle(BrFloatToScalar(mlAngleToFloat(s)));
#else /* (BASED_FLOAT || ! ML_FIXED_POINT) */
    //
    // Both are fixed point, so an integer based conversion is OK.
    // The BR Fixed Point Angle uses 16.16 format.
    // Assume that our Angle and Scalar are the same!	
    //
#if (ML_FIXED_RADIX == 16)
    return (br_angle) mlScalarGetValue(s);
#else /* (ML_FIXED_RADIX == 16) */
#if (ML_FIXED_RADIX < 16)
    return (br_angle) mlScalarGetValue(s) << (16 - ML_FIXED_RADIX);
#else /* (ML_FIXED_RADIX < 16) */
    return (br_angle) mlScalarGetValue(s) >> (ML_FIXED_RADIX - 16);
#endif /* (ML_FIXED_RADIX < 16) */
#endif /* (ML_FIXED_RADIX == 16) */
#endif /* (BASED_FLOAT || ! ML_FIXED_POINT) */
}


/**
 * @brief Convert from BRender angle to Magic Lantern angle.
 *
 * This routine takes into count whether fixed-point arithmetic
 * should be used.
 *
 * @param s The angle to convert.
 *
 * @return A Magic Lantern angle is returned.
 */
inline MlScalar
mlBRAngleToAngle( br_angle b )
{
#if (BASED_FLOAT || ! ML_FIXED_POINT)
    // At least one of these function calls is a no-op, and the other
    // is actually required.
    return mlFloatToAngle(BrScalarToFloat(BrAngleToScalar(b)));
#else /* (BASED_FLOAT || ! ML_FIXED_POINT) */
    //
    // Both are fixed point, so an integer based conversion is OK.
    // The BR Fixed Point Angle uses 16.16 format.
    //
    MlScalar f;
#if (ML_FIXED_RADIX == 16)
    f = mlScalarSetValue((long) b);
#else /* (ML_FIXED_RADIX == 16) */
#if (ML_FIXED_RADIX < 16)
    f = mlScalarSetValue((long) b >> (16 - ML_FIXED_RADIX));
#else /* (ML_FIXED_RADIX < 16) */
    f = mlScalarSetValue((long) b << (ML_FIXED_RADIX - 16));
#endif /* (ML_FIXED_RADIX < 16) */
#endif /* (ML_FIXED_RADIX == 16) */
    return f;
#endif /* (BASED_FLOAT || ! ML_FIXED_POINT) */
}


#endif /* ANGLEBR_H_INCLUDED */
