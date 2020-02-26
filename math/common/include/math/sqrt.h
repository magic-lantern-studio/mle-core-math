/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file sqrt.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * This file contains the utilities for computing the square-root of
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

#ifndef SQRT_H_INCLUDED
#define SQRT_H_INCLUDED

// Include Magic Lantern math header files.
#include <math/mlmath.h>

#if ML_FIXED_POINT
#include <math/scalar.h>

/**
 * @brief Compute the sqare-root of a Magic Lantern Scalar
 * in fixed-point mode [z = sqrt(x)].
 *
 * The FixedSqrt() function is used to determine the non-negative square-root of a scalar.
 * The usage should be "z = FixedSqrt(x)", where z and x are <b>MlScalar</b>s.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param val The scalar to compute the square-root of.
 *
 * @return The square-root of the specified scalar is returned.
 */
MLMATH_API MlScalar FixedSqrt(const MlScalar val);

/**
 * @brief Calculate the reciprocal value of the square-root of a Magic Lantern Scalar
 * in fixed-point mode [z = 1.0 / sqrt(x)].
 *
 * The FixedRecipSqrt() function is used to determine the reciprocal value
 * of the sqrt(x). The usage should be "z = FixedRecipSqrt(x)" where z and x are <b>MlScalar<b>s.
 * 
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param val The scalar to calculate the reciprocal of.
 *
 * @return A Magic Lantern Scalar is returned.
 */
MLMATH_API MlScalar FixedRecipSqrt(const MlScalar val);

#endif /* ML_FIXED_POINT */
#endif /* SQRT_H_INCLUDED */
