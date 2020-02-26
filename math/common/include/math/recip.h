/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file recip.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * This file contains the utilities for computing the reciprocal of
 * a Magic Lantern scalar primitive.
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2015-202 Wizzer Works
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

#ifndef RECIP_H_INCLUDED
#define RECIP_H_INCLUDED

// Include Magic Lantern math header files.
#include <math/mlmath.h>

#if ML_FIXED_POINT
#include <math/scalar.h>

/**
 * @brief Determine the reciprocal value for a Magic Lantern fixed-point Scalar primitive
 * [z = 1 / x].
 *
 * The FixedReciprocal() function calculates the reciprocal value of the specified
 * input. The usage should be "z = FixedReciprocal(x)" where z and x are MlScalars.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param val Magic Lantern Scalar primitive.
 *
 * @return The value 1/val is returned as a Magic Lantern scalar primitive.
 */
MLMATH_API MlScalar FixedReciprocal(const MlScalar val);

#endif /* ML_FIXED_POINT */
#endif /* RECIP_H_INCLUDED */
