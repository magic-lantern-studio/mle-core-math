/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file sine.h
 * @ingroup MlMath
 *
 * This file contains the utilities for computing the sine and cosine of
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

#ifndef SINE_H_INCLUDED
#define SINE_H_INCLUDED

// include Auteur math header files
#include <math/mlmath.h>
#include <math/scalar.h>
#include <math/angle.h>

#if !defined(__sgi)
// XXX - on platforms that don't have single-precision float
// trig functions, use the double versions, at least for now.
// See also scalar.h

#define cosf(x) ((float)cos((double)(x)))
#define fcos(x) ((float)cos((double)(x)))
#define sinf(x) ((float)sin((double)(x)))
#define fsin(x) ((float)sin((double)(x)))

#endif /* !defined(__sgi) */

#if ML_FIXED_POINT
/**
 * @brief The sine function for a Magic Lantern fixed-point Scalar primitive
 * [z = sin(x)].
 *
 * The FixedSin() function returns the sine of x, where x is given in radians. 
 * The usage should be "z = FixedSin(x)" where z and x are MlScalars.
 * This function uses a fixed-point algorithm for determinig the sine value.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The FixedSin() function returns a value between -1 and 1 (as a scalar). 
 */
MLMATH_API MlScalar FixedSin( const MlScalar x );
/**
 * @brief The cosine function for a Magic Lantern fixed-point Scalar primitive
 * [z = cos(x)].
 *
 * The FixedCos() function returns the cosine of x, where x is given in radians. 
 * The usage should be "z = FixedCos(x)" where z and x are MlScalars.
 * This function uses a fixed-point algorithm for determinig the cosine value.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The FixedCos() function returns a value between -1 and 1 (as a scalar). 
 */
MLMATH_API MlScalar FixedCos( const MlScalar x );
/**
 * @brief A sine and cosine function for a Magic Lantern fixed-point Scalar primitive
 * [s = sin(x) and c = cos(x)].
 *
 * The FixedSinCos() function returns the sine of x, where x is given in radians.
 * It also returns the cosine of x. Essentially, s = sin(x) and c = cos(x).
 * The usage should be "FixedSinCos(x,s,c)" where c, s and x are MlScalars.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param x A Magic Lantern Scalar primitive.
 * @param s The sine result of x. The value is returned as a Magic Lantern Scalar between -1 and 1.
 * @param c The cosine result of x. The value is returned as a Magic Lantern Scalar between -1 and 1.
 */
MLMATH_API void FixedSinCos( const MlScalar x, MlScalar &s, MlScalar &c ) ;
#endif


/**
 * @brief The sine function for a Magic Lantern Scalar primitive [z = sin(x)].
 *
 * The mlSin() function returns the sine of x, where x is given in radians. 
 * The usage should be "z = mlSin(x)" where z and x are MlScalars.
 *
 * This function is available for both the floating-point and the fixed-point versions of
 * the Magic Lantern Math libraries. It is the preferred way for calculating the
 * sine of a Magic Lantern scalar primitive.
 *
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The mlSin() function returns a value between -1 and 1 (as a scalar). 
 */
inline MLMATH_API MlScalar
mlSin( const MlScalar x ) 
{
#if ML_FIXED_POINT
    return FixedSin( x );
#else
    return mlFloatToScalar(sinf(mlScalarToFloat(mlAngleToRadians(x))));
#endif
}


/**
 * @brief The cosine function for a Magic Lantern Scalar primitive [z = cos(x)].
 *
 * The mlCos() function returns the cosine of x, where x is given in radians. 
 * The usage should be "z = mlCos(x)" where z and x are MlScalars.
 *
 * This function is available for both the floating-point and the fixed-point versions of
 * the Magic Lantern Math libraries. It is the preferred way for calculating the
 * cosine of a Magic Lantern scalar primitive.
 *
 * @param x A Magic Lantern Scalar primitive.
 *
 * @return The mlCos() function returns a value between -1 and 1 (as a scalar). 
 */
inline MLMATH_API MlScalar
mlCos( const MlScalar x ) 
{
#if ML_FIXED_POINT
    return FixedCos( x );
#else
    return mlFloatToScalar(cosf(mlScalarToFloat(mlAngleToRadians(x))));
#endif
}


/**
 * @brief A sine and cosine function for a Magic Lantern Scalar primitive
 * [s = sin(x) and c = cos(x)].
 *
 * The mlSinCos() function returns the sine of x, where x is given in radians.
 * It also returns the cosine of x. Essentially, s = sin(x) and c = cos(x).
 * The usage should be "mlSinCos(x,s,c)" where c, s and x are MlScalars.
 *
 * @param x A Magic Lantern Scalar primitive.
 * @param s The sine result of x. The value is returned as a Magic Lantern Scalar between -1 and 1.
 * @param c The cosine result of x. The value is returned as a Magic Lantern Scalar between -1 and 1.
 */
inline MLMATH_API void 
mlSinCos( const MlScalar x, MlScalar &s, MlScalar &c )
{
#if ML_FIXED_POINT
    FixedSinCos( x, s, c );
#else
    s = mlSin(x);
    c = mlCos(x);
#endif
}


#endif /* SINE_H_INCLUDED */
