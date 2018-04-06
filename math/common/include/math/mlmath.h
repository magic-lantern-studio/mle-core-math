/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file mlmath.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * \mainpage Magic Lantern Math Library API
 *
 * \section overview Overview
 * <p>
 * The Magic Lantern Math Library is a component of Magic Lantern,
 * an interactive, title development platform for authoring highly interactive titles,
 * such as interactive TV applications, games, educational programs, and
 * point-of-information/sales kiosks. The math library provides utilities for
 * fixed-point and floating-point arithmetic. The library is designed to be
 * used outside the context of the Magic Lantern framework.
 * </p>
 * <p>
 * The Magic Lantern Math Library is distributed as six static libraries and two
 * dynamic link libraries. The build environment distributed with the source for the
 * math library can be used to build any or all of these libraries.
 * The libraries are
 * <ul>
 * <li>runtime/mlmath.lib     - Floating-point Release Library</li>
 * <li>runtime/mlmathd.lib    - Floating-point Debug Library</li>
 * <li>runtime/mlfmath.lib    - Fixed-point Release Library</li>
 * <li>runtime/mlfmathd.lib   - Fixed-point Debug Library</li>
 * <li>tools/mlmath.lib       - Floating-point Release Library</li>
 * <li>tools/mlmathd.lib      - Floating-point Debug Library</li>
 * <li>rehearsal/mlmath.dll   - Floating-point Release Library</li>
 * <li>rehearsal/mlmathd.dll  - Floating-point Debug Library</li>
 * </ul>
 * </p>
 * <p>
 * The runtime version of the libraries can be found under <b>MLE_HOME/lib/runtime</b>
 * where <b>MLE_HOME</b> is the directory where Magic Lantern components are
 * installed. The tools version of the libraries are used with Magic Lantern
 * tools and can be found under <b>MLE_HOME/lib/tools</b>. The rehearsal version
 * of the libraries are distributed as a DLL/DSO and are used with the Magic Lantern
 * Rehearsal Player. They can be found under <b>MLE_HOME/bin/rehearsal</b>.
 * </p>
 * <p>
 * To use the math library, you need to set certain compiler flags in your compilation.
 * These compiler flags enable you to select the mode to use for the compilation.
 * You can choose floating or fixed-point mode, or optimized or debugging mode.
 * If you are using fixed-point mode, you may want to set the radix to give you 16.16 or 20.12 numbers.
 * The default is 16.16 fixed-point numbers.
 * </p><p>
 * Use the following constants to set the mode you are interested in:
 * <ul>
 * <li><b>ML_FIXED_POINT</b> | <b>ML_FLOATING_POINT</b></li>
 * <li><b>ML_MATH_OPTIMIZED</b> | <b>ML_MATH_DEBUG</b></li>
 * </ul>
 * </p><p>
 * Set the desired radix by using one of the following statements in scalar.h:
 * <ul>
 * <li>#define ML_FIXED_RADIX 16</li>
 * <li>#define ML_FIXED_RADIX 12</li>
 * </p>
 *
 * \section ms_build Building for Microsoft Windows
 * <p>
 * On Microsoft Windows platforms, one of these defines must always be set when
 * building application programs:
 * <ul>
 * <li><b>MLE_DLL</b>, when the application programmer is using the
 *     library in the form of a dynamic link library (DLL)
 * </li>
 * <li><b>MLE_NOT_DLL</b>, when the application programmer is using the
 *     library in the form of a static object library (LIB)
 * </ul></p>
 * <p>
 * Note that either MLE_DLL or MLE_NOT_DLL <b><i>must</i></b> be defined by
 * the application programmer on MSWindows platforms, or else the
 * #error statement will be processed (see mlmath.h). Set up one or the other of these two
 * defines in your compiler environment according to how the library
 * was built -- as a DLL (use "MLE_DLL") or as a LIB (use
 * "MLE_NOT_DLL").
 * </p><p>
 * Setting up defines for the compiler is typically done by either
 * adding something like "/DMLE_DLL" to the compiler's argument
 * line (for command-line build processes), or by adding the define to
 * the list of preprocessor symbols in your IDE GUI (in the MSVC IDE,
 * this is done from the "Project->Settings" menu; choose the "C/C++"
 * tab, then "Preprocessor" from the dropdown box and add the
 * appropriate define)).
 * </p><p>
 * It is extremely important that the application programmer uses the
 * correct define, as using "MLE_NOT_DLL" when "MLE_DLL" is
 * correct is likely to cause mysterious crashes.
 * </p>
 *
 * \section linux_build Building for Linux
 * <p>
 * Instructions for building on this platform are forthcoming.
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
