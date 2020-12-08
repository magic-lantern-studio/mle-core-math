/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file trig.h
 * @ingroup MlMath
 *
 * This file provides a convenience for including the trigonometric
 * functionality of the Magic Lantern Math Library.
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

#ifndef TRIG_H_INCLUDED
#define TRIG_H_INCLUDED

// include Magic Lantern math header files
#include <math/scalar.h>
#include <math/asine.h>
#include <math/atan.h>
#include <math/sine.h>

#if !defined(__sgi)
// XXX - on platforms that don't have single-precision float
// trig functions, use the double versions, at least for now.
// See also scalar.h

#define sqrtf(x) ((float)sqrt((double)(x)))
#define fsqrt(x) ((float)sqrt((double)(x)))

#endif /* !defined(__sgi) */

#if ML_FIXED_POINT
// Debugging stuff for now.
#include <stdio.h>
#endif

// Really need this for all time.
#if ! ML_FIXED_POINT
#include <math.h>
#endif

// XXX Only need this while I\'m implementing fixed pt functions.
// XXX Once they\'re in, remove it.
#if ML_FIXED_POINT
#include <math.h>
#endif

#endif /* TRIG_H_INCLUDED */
