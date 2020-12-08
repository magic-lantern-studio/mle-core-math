/**
 * @defgroup MlMath Magic Lantern Math Library API
 * @brief Math library providing scalar and 3d math algorithms.
 *
 * The Magic Lantern math library module is comprised of components
 * offering both Fixed-point and Floating-point arithmetic.
 */

/**
 * @file mlmath.h
 * @ingroup MlMath
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

#ifndef __MLMATH_H_
#define __MLMATH_H_

/* Precaution to avoid an error easily made by the application programmer. */
#ifdef MLMATH_API
#error Leave the internal MLMATH_API define alone.
#endif /* MLMATH_API */


// Magic Lantern Digital Workprint export rules.
# ifdef MLMATH_EXPORTS
#  ifdef MLE_MAKE_DLL
#   define MLMATH_API __declspec(dllexport)
#  endif /* MLE_MAKE_DLL */
# else /* !MLMATH_EXPORTS */
#  ifdef MLE_DLL
#   define MLMATH_API __declspec(dllimport)
#  else /* !MLE_DLL */
#   ifndef MLE_NOT_DLL
#    error Define either MLE_DLL or MLE_NOT_DLL as appropriate for your linkage! See math/mlmath.h for further instructions.
#   endif /* MLE_NOT_DLL */
#  endif /* !MLE_DLL */
# endif /* !MLMATH_EXPORTS */

/* Empty define to avoid errors when _not_ compiling an MSWindows DLL. */
#ifndef MLMATH_API
# define MLMATH_API
#endif /* !MLMATH_API */

#endif /* __MLMATH_H_ */
