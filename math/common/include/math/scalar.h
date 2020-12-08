/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file scalar.h
 * @ingroup MlMath
 *
 * This file contains the utilities and definitions for the Magic Lantern
 * Scalar primitive, <b>MlScalar</b>.
 *
 * <h3>
 * Fixed Point vs Floating Point Arithmetic
 * </h3>
 * <p>
 * A number of macros are used to control the definition and behavior of a
 * Magic Lantern scalar. For fixed-point behavior, the <b>ML_FIXED_POINT</b>
 * and <b>ML_FIXED_RADIX</b> macros need to be defined.
 * </p>
 * <p>
 * If ML_FIXED_POINT=1:
 *   Causes invocation of fixed-point code for <b>MlScalar</b>.
 * </p><p>
 * If ML_FIXED_POINT=0:
 *   Causes invocation of floating-point code for <b>MlScalar</b>.
 * </p><p>
 * Valid values for ML_FIXED_RADIX are 16 or 12. If ML_FIXED_RADIX is set to
 * 16, then the format of the scalar will be 16.16. If the ML_FIXED_RADIX is
 * set to 12 then the format of the scalar will be 20.12. If the ML_FIXED_RADIX
 * macro is not set, then the radix format will be set to 16.
 * </p>
 * <h3>
 * Debugging Support
 * </h3>
 * <p>
 * If ML_MATH_DEBUG=1:
 *   Accepts only legal fixed-point code.
 *   Prevents float*MlScalar and a variety of other bad practices.
 * </p><p>
 * ML_MATH_DEBUG=0:
 *   Uses no C++ error-checking classes.  The C++ compiler might
 *   let pass some incorrect fixed-point practices, but execution 
 *   speed is maximized.
 * </p>
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

#ifndef SCALAR_H_INCLUDED
#define SCALAR_H_INCLUDED

// Include Magic Lantern math header files.
#include <math/mlmath.h>

#if defined(WIN32)
// Defined ML_CDECL if a __cdecl calling convention is desired.
#if defined(ML_CDECL)
#define ML_MATH_STDCALL MLMATH_API
#else
#define ML_MATH_STDCALL __stdcall
#endif
#else
#define ML_MATH_STDCALL
#endif


// XXX - on platforms that don't have single-precision float
// truncation functions, use the double versions, at least for now.
// See also trig.h
// So here we're doing the wrong kind of rounding on the PC and others.
// And the substitute for truncf is a double kludge.

#if !defined(__linux__) && !defined(__APPLE__)
//#define sqrtf(x) ((float)sqrt((double)(x)))
//#define ceilf(x) ((float)ceil((double)(x)))
//#define floorf(x) ((float)floor((double)(x)))
#define truncf(x) ((float)floor((double)(x)))
#endif /* !defined(__linux__) */

// Setup for Magic Lantern generic parameter MlScalar 

//---------------------------------------------------------------------------
// First rationalize the ML_FIXED_POINT constant so that it is always
// defined, either to 0 or whatever the user set. Note that fixed point
// is now not the default.  You must ask for it.

#if !defined(ML_FIXED_POINT)
#if defined(__linux__) || defined(__APPLE__)
#define ML_FIXED_POINT 0      // default for Linux and MAcOS is not FIXED
#elif defined(WIN32)    
#define ML_FIXED_POINT 1      // default for PC is FIXED
#elif defined(psx)   
#define ML_FIXED_POINT 1      // default for PSX is FIXED
#else
error -- what platform is this?
#endif
#endif

#if ! ML_FIXED_POINT
#include <math.h>
#endif

//---------------------------------------------------------------------------
// The ML_MATH_DEBUG flag can be Undefined, 0, or non-zero.  Undefined
// defaults to 0, so the result is that you get debugging math support
// only if your compiler sets -DML_MATH_DEBUG=1.

#if !defined(ML_MATH_DEBUG)
#define ML_MATH_DEBUG 0
#endif /* !defined(ML_MATH_DEBUG) */

/**
 * An enumeration for specifying the <b>MlScalar</b> type.
 */
typedef enum 
{ 
    ML_SCALAR_FLOAT,       /**< The type is floating-point. */
    ML_SCALAR_FIXED_16_16, /**< The type is fixed-point, format is 16.16. */
    ML_SCALAR_FIXED_20_12, /**< The type is fixed-point, format is 20.12. */
} MlScalarType;


//------------------------------------------------------------------------
// Set the MlScalar type early

#if ML_MATH_DEBUG
class MlScalar;
#else /* ML_MATH_DEBUG */
#if ML_FIXED_POINT
/**
 * @brief The <b>MlScalar</b> type for fixed-point mode.
 *
 * If a debug version of the fixed-point library is being used, the
 * <b>MlScalar</b> is defined as a class to facilitate debugging the
 * behavior of a scalar.
 *
 * When the Magic Lantern Math Library is used in floating-point mode,
 * the <b>MlScalar</b> is typed as a <b>float</b>.
 */
typedef long MlScalar;
#else /* ML_FIXED_POINT */
typedef float MlScalar;
#endif /* ML_FIXED_POINT */
#endif /* ML_MATH_DEBUG */


//------------------------------------------------------------------------
// Set up the fixed point radix and conversion factors
// Must set these up even when not in fixed point, in case another library
// wants to do the conversion.

#include <mle/mlAssert.h>

// Can use a fixed point format of either 16.16 or 20.12. Select it here.
#ifndef ML_FIXED_RADIX
#define ML_FIXED_RADIX 16
#endif

// Could also set this for 20.12 format
// #define ML_FIXED_RADIX 12

// Check for a legal radix.
// Intended to create an error if the radix isn\'t one of the allowed choices.
#if (!((ML_FIXED_RADIX == 12) || (ML_FIXED_RADIX == 16)))
static int errorWrongRadix = ML_ASSERT(ML_FIXED_RADIX==16 || ML_FIXED_RADIX==12);
#endif /* (!(ML_FIXED_RADIX == 12 || ML_FIXED_RADIX == 16)) */

// Set up some radix dependent numbers.

#ifdef ML_FIXED_SCALE
#undef ML_FIXED_SCALE
#endif
#ifdef ML_FIXED_SCALE_I
#undef ML_FIXED_SCALE_I
#endif

#if (ML_FIXED_RADIX == 16)
#define ML_FIXED_SCALE   65536.0f
#define ML_FIXED_SCALE_I 65536
#else
#if (ML_FIXED_RADIX == 12)
#define ML_FIXED_SCALE   4096.0f
#define ML_FIXED_SCALE_I 4096
#else /* (ML_FIXED_RADIX == 12) */
#undef ML_FIXED_SCALE
#undef ML_FIXED_SCALE_I
#endif /* (ML_FIXED_RADIX == 12) */
#endif /* (ML_FIXED_RADIX == 16) */

//------------------------------------------------------------------------
// Create the ML_SCALAR() macro 4 different ways depending on
// the compiler flag settings.

#if ML_MATH_DEBUG
#define ML_SCALAR(x) mlFloatToScalar((float)(x))
#else /* ML_MATH_DEBUG */
#if ML_FIXED_POINT
#define ML_SCALAR(x) ((MlScalar)((x) * ML_FIXED_SCALE))
#else /* ML_FIXED_POINT */
#define ML_SCALAR(x) ((MlScalar)(x))
#endif /* ML_FIXED_POINT */
#endif /* ML_MATH_DEBUG */

//------------------------------------------------------------------------
// Set up radix-independent numbers

#if ML_FIXED_POINT
/**
 * Convenience macro for specifying the value 2 as a scalar.
 */
#define ML_SCALAR_TWO  ML_SCALAR(2)
/**
 * Convenience macro for specifying the value 1 as a scalar.
 */
#define ML_SCALAR_ONE ML_SCALAR(1)
/**
 * Convenience macro for specifying the value 1/2 as a scalar.
 */
#define ML_SCALAR_HALF ML_SCALAR(0.5f)
/**
 * Convenience macro for specifying the value 0 as a scalar.
 */
#define ML_SCALAR_ZERO ML_SCALAR(0)
/**
 * Convenience macro for specifying the value 2PI as a scalar.
 */
#define ML_SCALAR_TWO_PI ML_SCALAR(6.2831853071795864f)
/**
 * Convenience macro for specifying the value PI as a scalar.
 */
#define ML_SCALAR_PI ML_SCALAR(3.14159265358979323f)
/**
 * Convenience macro for specifying the value PI/2 as a scalar.
 */
#define ML_SCALAR_PI_HALF ML_SCALAR(1.57079632679489661923f)
/**
 * Convenience macro for specifying the value PI/4 as a scalar.
 */
#define ML_SCALAR_PI_FOURTH ML_SCALAR(0.7853981633974483075f)
/**
 * Convenience macro for specifying the value epsilon as a scalar.
 */
#define ML_SCALAR_EPSILON mlScalarSetValue(1)
#if ML_FIXED_RADIX == 16
#define ML_SCALAR_MAX ML_SCALAR(32767)
#else /* ML_FIXED_RADIX == 16 */
#define ML_SCALAR_MAX ML_SCALAR(1048576)
#endif /* ML_FIXED_RADIX == 16 */

#else /* ML_FIXED_POINT */
#define ML_SCALAR_TWO  ML_SCALAR(2.0f)
#define ML_SCALAR_ONE  ML_SCALAR(1.0f)
#define ML_SCALAR_HALF  ML_SCALAR(0.5f)
#define ML_SCALAR_ZERO ML_SCALAR(0.0f)
#define ML_SCALAR_TWO_PI  ML_SCALAR(6.2831853071795864f)
#define ML_SCALAR_PI  ML_SCALAR(3.14159265358979323f)
#define ML_SCALAR_PI_HALF ML_SCALAR(1.57079632679489661923f)
#define ML_SCALAR_PI_FOURTH ML_SCALAR(0.7853981633974483075f)
#define ML_SCALAR_EPSILON ML_SCALAR(1.0e-7)
#define ML_SCALAR_MAX ML_SCALAR(1.0e+38)
#endif /* ML_FIXED_POINT */

//------------------------------------------------------------------------
// Angular scale factors.
#ifndef DEG2RAD
#define DEG2RAD ML_SCALAR(0.01745329251994329500f)
#endif 
#ifndef RAD2DEG
#define RAD2DEG ML_SCALAR(57.2957795130823234020f)
#endif 

//------------------------------------------------------------------------
// The math functions we might need inside the MlScalar definition.

/**
 * @brief Multiply two Magic Lantern Scalar primitives [z = x * y].
 *
 * The mlMul() function is used to multiply two scalars together.
 * The usage should be "z = mlMul(x,y)" where z, y and x are <b>MlScalar</b>s.
 *
 * @param x The first operand.
 * @param y The second operand.
 *
 * @return A Magic Lantern Scalar is returned, the product of the
 * input values x and y.
 */
inline MLMATH_API MlScalar mlMul(const MlScalar x, const MlScalar y);

/**
 * @brief Multiply three Magic Lantern Scalar primitives [v = x * y * z].
 *
 * The mlMuMull() function is used to multiply three scalars together.
 * The usage should be "v = mlMulMul(x,y,z)" where v, z, y and x are <b>MlScalar</b>s.
 *
 * @param x The first operand.
 * @param y The second operand.
 * @param z The third operand.
 *
 * @return A Magic Lantern Scalar is returned, the product of the
 * input values x, y and z.
 */
inline MLMATH_API MlScalar mlMulMul(const MlScalar x, const MlScalar y, const MlScalar z);

/**
 * @brief Multiply a Magic Lantern Scalar primitive by another scalar
 * [x *= y].
 *
 * The mlMulBy() function is used to multiply two scalars together.
 * The usage should be "z = mlMulBy(x,y)" where z, y and x are <b>MlScalar</b>s.
 *
 * @param x The first operand.
 * @param y The second operand.
 *
 * @return A Magic Lantern Scalar is returned, the product of the
 * input values x and y. x will be modified to contain the result
 * of the multiplication.
 */
inline MLMATH_API MlScalar mlMulBy(MlScalar &x, const MlScalar y);

/**
 * @brief Divide a Magic Lantern Scalar primitive by another
 * [z = x / y].
 *
 * The mlDiv() function is used to divide one scalar by another.
 * The usage should be "z = mlDiv(x,y)" where z, y and x are <b>MlScalar</b>s.
 *
 * @param x The first operand.
 * @param y The second operand.
 *
 * @return A Magic Lantern Scalar is returned, the division of the scalar
 * x by y.
 */
inline MLMATH_API MlScalar mlDiv(const MlScalar x, const MlScalar y);

/**
 * @brief Divide a Magic Lantern Scalar primitive by another
 * [x /= y].
 *
 * The mlDivBy() function is used to divide one scalar by another.
 * The usage should be "z = mlDivBy(x,y)" where z, y and x are <b>MlScalar</b>s.
 *
 * @param x The first operand.
 * @param y The second operand.
 *
 * @return A Magic Lantern Scalar is returned, the division of the scalar
 * x by y. x will be modified to contain the result
 * of the division.
 */
inline MLMATH_API MlScalar mlDivBy(MlScalar &x, const MlScalar y);

/**
 * @brief Multiply a Magic Lantern Scalar primitive by another
 * and then divide by a third scalar
 * [w = x * y / z].
 *
 * The mlMulDiv() function is used to multiply two scalars and then
 * divide by a third scalar.
 * The usage should be "w = mlMulDiv(x,y,z)" where w, z, y and x are <b>MlScalar</b>s.
 *
 * @param x The first multiplication operand.
 * @param y The second multiplication operand.
 * @param y The third operand used for division.
 *
 * @return A Magic Lantern Scalar is returned
 */
inline MLMATH_API MlScalar mlMulDiv(const MlScalar x, const MlScalar y, const MlScalar z);

/**
 * @brief Calculate the reciprocal value of a Magic Lantern Scalar
 * [z = 1.0 / x].
 *
 * The mlReciprocal() function is used to determine the reciprocal value
 * of x. The usage should be "z = mlReciprocal(x)" where z and x are <b>MlScalar</b>s.
 * 
 * @param x The scalar to calculate the reciprocal of.
 *
 * @return A Magic Lantern Scalar is returned.
 */
inline MLMATH_API MlScalar mlReciprocal( const MlScalar x );

/**
 * @brief Calculate the reciprocal value of the square-root of a Magic Lantern Scalar
 * [z = 1.0 / sqrt(x)].
 *
 * The mlRecipSqrt() function is used to determine the reciprocal value
 * of the sqrt(x). The usage should be "z = mlRecipSqrt(x)" where z and x are <b>MlScalar<b>s.
 * 
 * @param x The scalar to calculate the reciprocal of.
 *
 * @return A Magic Lantern Scalar is returned.
 */
inline MLMATH_API MlScalar mlRecipSqrt( const MlScalar x );

/**
 * @brief Compute the absolute value of a Magic Lantern Scalar
 * [z = abs(x)].
 *
 * The mlAbs() function is used to determine the absolute value of x.
 * The usage should be "z = mlAbs(x)" where z and x are <b>MlScalar</b>s.
 *
 * @param x The scalar to calculate the absolute value of.
 *
 * @return A Magic Lantern Scalar is returned.
 */
inline MLMATH_API MlScalar mlAbs( const MlScalar x );

/**
 * @brief Determine the maiximum value for two Magic Lantern Scalars
 * [z = MAX(x,y)]
 *
 * The mlMax() function is used to determine the maximum value of
 * two scalars. The usage should be "z = mlMax(x,y)" where z, x and y are <b>MlScalar</b>s.
 *
 * @param x The first scalar to compare.
 * @param y The second scalar to compare.
 *
 * @return A Magic Lantern Scalar is returned, either x or y, whichever
 * is larger.
 */
inline MLMATH_API MlScalar mlMax( const MlScalar x, const MlScalar y );

/**
 * @brief Compute the sign of the specified Magic Lantern Scalar
 * [z = sign(x)].
 *
 * The mlSign() fucntion is used to determine the sign of a scalar.
 * The usage should be "z = mlSign(x)", where z and x are <b>MlScalar</b>s.
 *
 * @param x The scalar to check.
 *
 * @return If the scalar is 0, then <b>ML_SCALAR_ZERO</b> is reuturned.
 * If the scalar is negative, then -<b>ML_SCALAR_ONE</b> is returned.
 * If the scalar is positive, then <b>ML_SCALAR_ONE</b> is returned.
 */
inline MLMATH_API MlScalar mlSign( const MlScalar x );

/**
 * @brief Compute the sqare-root of a Magic Lantern Scalar
 * [z = sqrt(x)].
 *
 * The mlSqrt() function is used to determine the non-negative square-root of a scalar.
 * The usage should be "z = mlSqrt(x)", where z and x are <b>MlScalar</b>s.
 *
 * @param x The scalar to compute the square-root of.
 *
 * @return The square-root of the specified scalar is returned.
 */
inline MLMATH_API MlScalar mlSqrt( const MlScalar x );

/**
 * @brief Compute the sqare of a Magic Lantern Scalar
 * [z = x * x].
 *
 * The mlSquare() function is used to determine the square of a scalar.
 * The usage should be "z = mlSquare(x)", where z and x are <b>MlScalar</b>s.
 *
 * @param x The scalar to compute the square of.
 *
 * @return The square of the specified scalar is returned.
 */
inline MLMATH_API MlScalar mlSquare( const MlScalar x );

/**
 * @brief Determine whether two Magic Lantern Scalars are equal within
 * a tolerance of (ML_SCALAR_EPSILON * 2**tolMagnitude). An equivalent
 * equation would be [z = (|x - y| <= ULP * 2**tolMagnitude)].
 *
 * The mlEqualAbsError()function is used to compute whether to scalars
 * are equal within a specified tolerance.
 *
 * In fixed point this means that |x-y| differ by at most tolMagnitude bits.
 * We also do absolute error for floating-point, so that the two are more 
 * interchangeable.
 *
 * XXX - We should also implement a relative error checker for the floating-point 
 * minded.
 *
 * @param x The first scalar to comapare.
 * @param y The second scalar to comapre.
 *
 * @return 1 will be returned if the two scalars are equal. Otherwise 0 will
 * be returned.
 */
inline MLMATH_API int mlEqualAbsErr( const MlScalar x, const MlScalar y, const int tolMagnitude );

/**
 * @brief Compute the largest integral value not greater than
 * the specified argument, <b>x</b>.
 *
 * The mlFloor() function will round x down to the nearest integer.
 *
 * @param x The scalar to round.
 *
 * @return The rounded integer value is returned as a scalar.
 * If x is integral or infinite, x itself is returned. 
 */
inline MLMATH_API MlScalar mlFloor( const MlScalar x );

/**
 * @brief Compute the smallest integral value not less than
 * the specified argument, <b>x</b>.
 *
 * The mlCeil() function will round x up to the nearest integer.
 *
 * @param x The scalar to round.
 *
 * @return The rounded integer value is returned as a scalar.
 * If x is integral or infinite, x itself is returned. 
 */
inline MLMATH_API MlScalar mlCeil( const MlScalar x );

/**
 * @brief This routine will round to an integer, towards zero.
 *
 * The mlTrunc() function will round x to the nearest integer not larger in absolute value.
 *
 * @param x The scalar to truncate.
 *
 * @return The rounded integer value is returned as a scalar.
 * If x is integral, infinite or NaN, x itself is returned. 
 */
inline MLMATH_API MlScalar mlTrunc( const MlScalar x );
//------------------------------------------------------------------------
// Do not make these inlined, for we require that they return the
// compilation value of the util/math libraries, so that the devlib
// workprint read/write code can find out what form the actor is.

int ML_MATH_STDCALL mlScalarIsFloat(void);
int ML_MATH_STDCALL mlScalarIsMathDebug(void);
//------------------------------------------------------------------------
//------------------------------------------------------------------------

// XXX XXX XXX Remove this before check-in and fix all errors it causes!
#define CC_TYPE_CONVERSION_RFE_263512_FIXED 1

#if ML_MATH_DEBUG
extern MLMATH_API MlScalar mlFloatToScalar(const float);
#else
extern MlScalar ML_MATH_STDCALL mlFloatToScalar(const float); // TEST ON LINUX
#endif
extern MLMATH_API MlScalar mlLongToScalar(const long);
extern MLMATH_API MlScalar mlScalarSetValue(const long);

#if ML_FIXED_POINT

#if ML_MATH_DEBUG
class MLMATH_API MlScalar
{
  public:
#if ML_SCALAR_CHECK_UNINITIALIZED
    MlScalar() : value(0xdeadbeef) {}
#endif
    MLMATH_API friend long mlScalarGetValue(const MlScalar operand)
      { return operand.value; }
    MLMATH_API friend MlScalar mlScalarSetValue(const long val) 
      { MlScalar number; number.value = val; return number; }
    /* 	MlScalar(const long v) {value = v;} */
    MLMATH_API friend long mlScalarToLong(const MlScalar operand)
      { return operand.value >> ML_FIXED_RADIX; }
    MLMATH_API friend MlScalar mlLongToScalar(const long operand)
      { MlScalar f; f.value = operand << ML_FIXED_RADIX; return f; }
    
#ifndef ML_SCALAR_FLOAT_DISALLOWED
    MLMATH_API friend MlScalar mlFloatToScalar(const float operand)
      { MlScalar f; f.value = (long) (operand * ML_FIXED_SCALE); return f; }
    MLMATH_API friend float mlScalarToFloat(const MlScalar operand)
      { return operand.value / ML_FIXED_SCALE; }
    
#endif /* ML_SCALAR_FLOAT_DISALLOWED */
    
    
    // Intrinsic operators
    MlScalar operator+ (const MlScalar operand) const
      { MlScalar f; f.value = value + operand.value; return f; }
    MlScalar& operator+= (const MlScalar operand)
      { value += operand.value; return *this; }
    
    MlScalar operator- (const MlScalar operand) const
      { MlScalar f; f.value = value - operand.value; return f; }
    MlScalar& operator-= (const MlScalar operand)
      { value -= operand.value; return *this; }
    
#if CC_TYPE_CONVERSION_RFE_263512_FIXED
    MlScalar operator* (const long operand) const
      { MlScalar f; f.value = value * operand; return f; }
    MLMATH_API friend MlScalar operator* (const long operand, const MlScalar op2)
      { MlScalar f; f.value = operand * op2.value; return f; }
    
    MlScalar& operator*= (const long operand)
      { value *= operand; return *this; }
    
    MlScalar operator/ (const long operand) const
      { MlScalar f; f.value = value / operand; return f; }
    
    MlScalar& operator/= (const long operand)
      { value /= operand; return *this; }
#endif
    
    int operator> (const MlScalar operand) const
      { return value > operand.value; }
    int operator>= (const MlScalar operand) const
      { return value >= operand.value; }
    int operator< (const MlScalar operand) const
      { return value < operand.value; }
    int operator<= (const MlScalar operand) const
      { return value <= operand.value; }
    int operator== (const MlScalar operand) const
      { return (value == operand.value); }
    int operator!= (const MlScalar operand) const
      { return value != operand.value; }
    
    MlScalar operator- () const
      { MlScalar f; f.value = -value; return f; }
    MlScalar operator+ () const
      { MlScalar f; f.value = +value; return f; }
    MlScalar operator! () const
      { MlScalar f; f.value = !value; return f; }
    MlScalar operator|| (const MlScalar operand) const
      { MlScalar f; f.value = value || operand.value; return f; }
    MlScalar operator|| (const long operand) const
      { MlScalar f; f.value = value || operand; return f; }
    MlScalar operator|| (const float operand) const
      { MlScalar f; f.value = value || operand; return f; }
    MLMATH_API friend MlScalar operator|| (const long operand, const MlScalar op2)
      { MlScalar f; f.value = operand || op2.value; return f; }
    MLMATH_API friend MlScalar operator|| (const float operand, const MlScalar op2)
      { MlScalar f; f.value = operand || op2.value; return f; }
    
    MlScalar operator&& (const MlScalar operand) const
      { MlScalar f; f.value = value && operand.value; return f; }
    MlScalar operator&& (const long operand) const
      { MlScalar f; f.value = value && operand; return f; }
    MlScalar operator&& (const float operand) const
      { MlScalar f; f.value = value && operand; return f; }
    MLMATH_API friend MlScalar operator&& (const long operand, const MlScalar op2)
		{ MlScalar f; f.value = operand && op2.value; return f; }
	MLMATH_API friend MlScalar operator&& (const float operand, const MlScalar op2)
		{ MlScalar f; f.value = operand && op2.value; return f; }
	
  protected:
	long value;
};

#else /* ML_MATH_DEBUG */
//
// In optimized fixed-point mode we just make the scalar a long and work
// directly on it.
typedef long MlScalar;

/**
 * @brief Get the value of a Magic Lantern Scalar as a <b>long</b> data type.
 *
 * The mlScalarGetValue() function is only available in fixed-point mode.
 *
 * @param val A Magic Lantern scalar.
 *
 * @return A <b>long</b> value is returned. 
 */
inline MLMATH_API long mlScalarGetValue(const MlScalar val) { return (long)val; }

/**
 * @brief Set the value of a Magic Lantern Scalar using a <b>long</b> data type.
 *
 * The mlScalarSetValue() function is only available in fixed-point mode.
 *
 * @param val A <b>long</b> value.
 *
 * @return A Magic Lantern scalar is returned. 
 */
inline MLMATH_API MlScalar mlScalarSetValue(const long val) { return val; }

/**
 * @brief Cast the value of a Magic Lantern Scalar to a <b>long</b> data type.
 *
 * The mlScalarToLong() function is only available in fixed-point mode.
 *
 * @param operand A Magic Lantern scalar.
 *
 * @return A <b>long</b> value is returned. 
 */
inline MLMATH_API long mlScalarToLong(const MlScalar operand) { return operand >> ML_FIXED_RADIX; }

/**
 * @brief Cast the value of a <b>long</b> data type to a Magic Lantern Scalar.
 *
 * The mlLongToScalar() function is only available in fixed-point mode.
 *
 * @param val A <b>long</b> value.
 *
 * @return A Magic Lantern scalar is returned. 
 */
inline MLMATH_API MlScalar mlLongToScalar(const long operand)
{ 
    MlScalar f; 
    if (operand >= 0)
	{
	    f = operand << ML_FIXED_RADIX;
    } else {
	    f = -((-operand) << ML_FIXED_RADIX);
    }
    return f; 
}

#ifndef ML_SCALAR_FLOAT_DISALLOWED
inline MlScalar ML_MATH_STDCALL mlFloatToScalar(const float number) 
	{return (MlScalar) (number * ML_FIXED_SCALE); }
inline float ML_MATH_STDCALL mlScalarToFloat(const MlScalar number)
	{ return (float) (number / ML_FIXED_SCALE); }
#endif /* ML_SCALAR_FLOAT_DISALLOWED */

#endif /* ML_MATH_DEBUG */

// The fixed point routines that will be supplied elsewhere.
// Only available when MlScalar == fixed point.  We considered making them
// take a MlFixed argument, but that caused us to create MlFixed and MlFloat,
// which had onerous repercussions.  So now they exist for MlScalar type only
// when we\'re in fixed mode.  This means that if a customer uses them, he\'ll
// find compilation or link errors only in floating point mode.  So he shouldn\'t
// use them.

#if defined(ML_DEBUG)
void FixedPrint( MlScalar val, char *string);
#endif
/**
 * @brief Determine whether two Magic Lantern Scalars are equal
 * in fixed-point mode.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param valA The first scalar to comapare.
 * @param valB The second scalar to compare.
 *
 * @return If the two scalars are equal, then 1 will be returned.
 * Otherwise, 0 will be returned.
 */
extern int FixedEqual(const MlScalar valA, const MlScalar valB);

/**
 * @brief Determine whether two Magic Lantern Scalars are almost equal
 * in fixed-point mode.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param valA The first scalar to comapare.
 * @param valB The second scalar to compare.
 * @param nBitsTol The tolerance within n bits.
 *
 * @return If the two scalars are almost equal (close enough for government
 * work), then 1 will be returned. Otherwise, 0 will be returned.
 */
extern int FixedAlmostEqual(const MlScalar valA, const MlScalar valB, const int nBitsTol);

/**
 * @brief Determine whether two Magic Lantern Scalars are equivalent
 * in fixed-point mode.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param valA The first scalar to comapare.
 * @param valB The second scalar to compare.
 *
 * @return If the two scalars are exactly equivalent, then 1 will be returned.
 * Otherwise, 0 will be returned.
 */
extern int FixedEquiv(const MlScalar valA, const MlScalar valB);

/**
 * @brief Multiply two Magic Lantern Scalar primitives in
 * fixed-point mode [z = x * y].
 *
 * The FixedMultiply() function is used to multiply two scalars together.
 * The usage should be "z = FixedMultiply(x,y)" where z, y and x are <b>MlScalar</b>s.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param valA The first operand.
 * @param valB The second operand.
 *
 * @return A Magic Lantern Scalar is returned, the product of the
 * input values x and y.
 */
extern MlScalar FixedMultiply(const MlScalar valA, const MlScalar valB);

/**
 * @brief Divide a Magic Lantern Scalar primitive by another
 * in fixed-point mode [z = x / y].
 *
 * The FixedDivide() function is used to divide one scalar by another.
 * The usage should be "z = FixedDivide(x,y)" where z, y and x are <b>MlScalar</b>s.
 *
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param valA The first operand.
 * @param valB The second operand.
 *
 * @return A Magic Lantern Scalar is returned, the division of the scalar
 * x by y.
 */
extern MlScalar FixedDivide(const MlScalar valA, const MlScalar valB);

// Documentation in recip.h.
extern MlScalar FixedReciprocal(const MlScalar val);

// Documentation in sqrt.h.
extern MlScalar FixedSqrt(const MlScalar val);

// Documentation in sqrt.h.
extern MlScalar FixedRecipSqrt(const MlScalar val);

/**
 * @brief Multiply a Magic Lantern Scalar primitive by another
 * and then divide by a third scalar
 * [w = x * y / z].
 *
 * The FixedMulDiv() function is used to multiply two scalars and then
 * divide by a third scalar.
 * The usage should be "w = FixedMulDiv(x,y,z)" where w, z, y and x are <b>MlScalar</b>s.
 * 
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param valA The first multiplication operand.
 * @param valB The second multiplication operand.
 * @param valC The third operand used for division.
 *
 * @return A Magic Lantern Scalar is returned
 */
extern MlScalar FixedMulDiv(const MlScalar valA, const MlScalar valB, const MlScalar valC);

/**
 * @brief Compute the largest integral value not greater than
 * the specified argument, <b>x</b>.
 *
 * The FixedFloor() function will round x down to the nearest integer.
 * 
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param x The scalar to round.
 *
 * @return The rounded integer value is returned as a scalar.
 * If x is integral or infinite, x itself is returned. 
 */
extern MlScalar FixedFloor( const MlScalar val );

/**
 * @brief Compute the smallest integral value not less than
 * the specified argument, <b>x</b>.
 *
 * The FixedCeil() function will round x up to the nearest integer.
 * 
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param x The scalar to round.
 *
 * @return The rounded integer value is returned as a scalar.
 * If x is integral or infinite, x itself is returned. 
 */
extern MlScalar FixedCeil( const MlScalar val );

/**
 * @brief This routine will round to an integer, towards zero.
 *
 * The FixedTrunc() function will round x to the nearest integer not larger in absolute value.
 * 
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param x The scalar to truncate.
 *
 * @return The rounded integer value is returned as a scalar.
 * If x is integral, infinite or NaN, x itself is returned. 
 */
extern MlScalar FixedTrunc( const MlScalar val );

/**
 * @brief Interpolate data from a table.
 *
 * The FixedTableInterp() function will interpolate data from a table with a
 * power of two number of bins.
 * This functions assumes that you can index into table[] as table[index] and
 * table[index+1], unless remdr == 0, in which case you needn\'t
 * do the index+1.
 * 
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param table The table of <b>long</b> values to interpolate.
 * @param index An index into the table indicating where to begin interpolation.
 * @param remdr
 * @param sign
 * @param remdrShift
 *
 * @return The interpolated value is returned as a <b>long</b>.
 */
extern long FixedTableInterp( const long table[], 
			      const long index, 
			      const long remdr, 
			      const long sign,
			      const long remdrShift );

/**
 * @brief Interpolate data from a table.
 *
 * The FixedShortTableInterp() function will interpolate data from a table with a
 * power of two number of bins.
 * This functions assumes that you can index into table[] as table[index] and
 * table[index+1], unless remdr == 0, in which case you needn\'t
 * do the index+1.
 * 
 * This function is only available when using the fixed-point versions of
 * the Magic Lantern Math libraries.
 *
 * @param table The table of <b>short</b> values to interpolate.
 * @param index An index into the table indicating where to begin interpolation.
 * @param remdr
 * @param sign
 * @param remdrShift
 *
 * @return The interpolated value is returned as a <b>long</b>.
 */
extern long FixedShortTableInterp( const short table[], 
				   const long index, 
				   const long remdr, 
				   const long sign,
				   const long remdrShift );

#else /* ML_FIXED_POINT */

#include <mle/mlAssert.h>
#if ML_MATH_DEBUG
class MLMATH_API MlScalar
{
  public:
#if ML_CHECK_UNINITIALIZED
    MlScalar() : value(0xdeadbeef) {}
#endif
    MLMATH_API friend float mlScalarGetValue(const MlScalar operand)
      { return operand.value; }
    MLMATH_API friend MlScalar mlScalarSetValue(const float val) 
      { MlScalar number; number.value = val; return number; }
    MLMATH_API friend long mlScalarToLong(const MlScalar operand)
      { return (long)operand.value; }
    MLMATH_API friend MlScalar mlLongToScalar(const long operand)
      { MlScalar f; f.value = (float) operand ; return f; }
    
#ifndef ML_FIXED_FLOAT_DISALLOWED
    MLMATH_API friend MlScalar mlFloatToScalar(const float operand)
      { MlScalar f; f.value = operand ; return f; }
    MLMATH_API friend float mlScalarToFloat(const MlScalar operand)
      { return (float)operand.value; }
    
#endif /* ML_SCALAR_FLOAT_DISALLOWED */
    
    // Intrinsic operators
    MlScalar operator+ (const MlScalar operand) const
      { MlScalar f; f.value = value + operand.value; return f; }
    MlScalar& operator+= (const MlScalar operand)
      { value += operand.value; return *this; }
    
    MlScalar operator- (const MlScalar operand) const
      { MlScalar f; f.value = value - operand.value; return f; }
    MlScalar& operator-= (const MlScalar operand)
      { value -= operand.value; return *this; }
    
#if CC_TYPE_CONVERSION_RFE_263512_FIXED
    MlScalar operator* (const long operand) const
      { MlScalar f; f.value = value * operand; return f; }
    MLMATH_API friend MlScalar operator* (const long operand, const MlScalar op2)
      { MlScalar f; f.value = operand * op2.value; return f; }
    
    MlScalar& operator*= (const long operand)
      { value *= operand; return *this; }
    
    MlScalar operator/ (const long operand) const
      { MlScalar f; f.value = value / operand; return f; }
    
    MlScalar& operator/= (const long operand)
      { value /= operand; return *this; }
#endif
    
    int operator> (const MlScalar operand) const
      { return value > operand.value; }
    int operator>= (const MlScalar operand) const
      { return value >= operand.value; }
    int operator< (const MlScalar operand) const
      { return value < operand.value; }
    int operator<= (const MlScalar operand) const
      { return value <= operand.value; }
    int operator== (const MlScalar operand) const
      { return value == operand.value; }
    int operator!= (const MlScalar operand) const
      { return value != operand.value; }
    
    MlScalar operator- () const
      { MlScalar f; f.value = -value; return f; }
    MlScalar operator+ () const
      { MlScalar f; f.value = +value; return f; }
    MlScalar operator! () const
      { MlScalar f; f.value = (float)!value; return f; }
    MlScalar operator|| (const MlScalar operand) const
      { MlScalar f; f.value = (float)(value || operand.value); return f; }
    MlScalar operator|| (const long operand) const
      { MlScalar f; f.value = (float)(value || operand); return f; }
    MlScalar operator|| (const float operand) const
      { MlScalar f; f.value = (float)(value || operand); return f; }
    MLMATH_API friend MlScalar operator|| (const long operand, const MlScalar op2)
      { MlScalar f; f.value = (float)(operand || op2.value); return f; }
    MLMATH_API friend MlScalar operator|| (const float operand, const MlScalar op2)
      { MlScalar f; f.value = (float)(operand || op2.value); return f; }
    
    MlScalar operator&& (const MlScalar operand) const
      { MlScalar f; f.value = (float)(value && operand.value); return f; }
    MlScalar operator&& (const long operand) const
      { MlScalar f; f.value = (float)(value && operand); return f; }
    MlScalar operator&& (const float operand) const
      { MlScalar f; f.value = (float)(value && operand); return f; }
    MLMATH_API friend MlScalar operator&& (const long operand, const MlScalar op2)
		{ MlScalar f; f.value = (float)(operand && op2.value); return f; }
	MLMATH_API friend MlScalar operator&& (const float operand, const MlScalar op2)
		{ MlScalar f; f.value = (float)(operand && op2.value); return f; }
	
protected:
	float value;
};


#else /* ML_MATH_DEBUG */
typedef float MlScalar;

inline MLMATH_API float mlScalarGetValue(const MlScalar number) { return (float)number; }
inline MLMATH_API MlScalar mlScalarSetValue(const float val) { return val; }
inline MLMATH_API long mlScalarToLong(const MlScalar number) { return (long)number; };
inline MLMATH_API MlScalar mlLongToScalar(const long number) { return (MlScalar)number; };

#ifndef ML_SCALAR_FLOAT_DISALLOWED
inline MlScalar ML_MATH_STDCALL mlFloatToScalar(const float operand)
	{ return (MlScalar) operand; }
inline float ML_MATH_STDCALL mlScalarToFloat(const MlScalar operand)
	{ return (float) operand; }
#endif /* ML_SCALAR_FLOAT_DISALLOWED */

#endif /* ML_MATH_DEBUG */

#endif /* ML_FIXED_POINT */

// z = x * y
inline MlScalar 
mlMul(const MlScalar x, const MlScalar y) 
{
#if ML_FIXED_POINT
	return FixedMultiply(x, y);
#else
	return mlFloatToScalar(mlScalarToFloat(x)*mlScalarToFloat(y));
#endif
}

// v = x * y * z
inline MlScalar 
mlMulMul(const MlScalar x, const MlScalar y, const MlScalar z) 
{
#if ML_FIXED_POINT
	return FixedMultiply(x, FixedMultiply(y, z));
#else
	return mlFloatToScalar(mlScalarToFloat(x)*mlScalarToFloat(y)*mlScalarToFloat(z));
#endif
}

// x *= y
inline MlScalar
mlMulBy(MlScalar &x, const MlScalar y)
{
#if ML_FIXED_POINT
	x = FixedMultiply(x, y);
	return x;
#else
	return x = mlFloatToScalar(mlScalarToFloat(x)*mlScalarToFloat(y));
#endif
}

// z = x / y
inline MlScalar
mlDiv(const MlScalar x, const MlScalar y)
{
#if ML_FIXED_POINT
    return FixedDivide(x,y);
#else
    return mlFloatToScalar(mlScalarToFloat(x)/mlScalarToFloat(y));
#endif
}

// x /= y
inline MlScalar
mlDivBy(MlScalar &x, const MlScalar y)
{
#if ML_FIXED_POINT
    x = FixedDivide(x,y);
    return x;
#else
    return x = mlFloatToScalar(mlScalarToFloat(x)/mlScalarToFloat(y));
#endif
}

// w = x * y / z
inline MlScalar
mlMulDiv(const MlScalar x, const MlScalar y, const MlScalar z)
{
#if ML_FIXED_POINT
    return FixedMulDiv(x,y,z);
#else
    return mlFloatToScalar(mlScalarToFloat(x) * mlScalarToFloat(y) / mlScalarToFloat(z));
#endif
}

// z = 1.0 / x
inline MlScalar
mlReciprocal( const MlScalar x )
{
#if ML_FIXED_POINT
    return FixedReciprocal(x);
#else
    return mlFloatToScalar(1.0f / mlScalarToFloat(x));
#endif
}

// z = 1.0 / sqrt(x)
inline MlScalar
mlRecipSqrt( const MlScalar x )
{
#if ML_FIXED_POINT
    return FixedRecipSqrt(x);
#else
    return mlFloatToScalar(1.0f / sqrtf(mlScalarToFloat(x)));
#endif
}

// z = abs(x)
inline MlScalar
mlAbs( const MlScalar x )
{
    return ( x >= ML_SCALAR_ZERO ) ? x : -x;
}

// z = MAX(x,y)
inline MlScalar
mlMax( const MlScalar x, const MlScalar y )
{
    return ( x >= y ) ? x : y;
}

// z = sign(x)
inline MlScalar
mlSign( const MlScalar x )
{
    if (x == ML_SCALAR_ZERO)
	{
	    return ML_SCALAR_ZERO;
    }
    else
	{
	    return ( x > ML_SCALAR_ZERO ) ? ML_SCALAR_ONE : -ML_SCALAR_ONE;
	}
}

// z = sqrt(x)
inline MlScalar
mlSqrt( const MlScalar x )
{
#if ML_FIXED_POINT
    return FixedSqrt(x);
#else
    return mlFloatToScalar(sqrtf(mlScalarToFloat(x)));
#endif
}	

// z = x * x;
inline MlScalar 
mlSquare( const MlScalar x )
{
#if ML_FIXED_POINT
    // Does this assignment help avoid evaluating x twice inline?
    MlScalar y = x;
    return FixedMultiply(y, y);
#else
    return mlFloatToScalar(mlScalarToFloat(x)*mlScalarToFloat(x));
#endif
}

/**
 * @brief Compute the power of a Magic Lantern Scalar
 * [z = x ^ i].
 *
 * The mlPowInt() function is used to determine the value of a scalar
 * raised to the ith power.
 * The usage should be "z = mlPowInt(x,i)", where z and x are <b>MlScalar</b>s
 * and i is an integer.
 *
 * @param x The scalar to compute the power of.
 * @param i The scale to raise the power to.
 *
 * @return A Magic Lantern scalar is returned.
 */
MlScalar 
mlPowInt( const MlScalar x, const int i );

// z = (|x - y| <= ULP * 2**tolMagnitude);
// In fixed point this means that |x-y| differ by at most tolMagnitude bits.
// We also do absolute error for floating point, so that the two are more 
// interchangeable.  
// XXX We should also implement a relative error checker for the floating point 
// minded. 

inline int
mlEqualAbsErr( const MlScalar x, const MlScalar y, const int tolMagnitude )
{
    MLE_ASSERT(tolMagnitude >= 0);
#if ML_FIXED_POINT
    return FixedAlmostEqual(x, y, tolMagnitude);
#else
    return (mlAbs(x-y) <= ML_SCALAR_EPSILON * (1 << tolMagnitude));
#endif
}

// C math library floor() lookalike
inline MlScalar 
mlFloor( const MlScalar x )
{
#if ML_FIXED_POINT
    return FixedFloor(x);
#else
    return mlFloatToScalar(floorf(mlScalarToFloat(x)));
#endif
}

// C math library ceil() lookalike
inline MlScalar 
mlCeil( const MlScalar x )
{
#if ML_FIXED_POINT
    return FixedCeil(x);
#else
    return mlFloatToScalar(ceilf(mlScalarToFloat(x)));
#endif
}

// C math library trunc() lookalike
inline MlScalar 
mlTrunc( const MlScalar x )
{
#if ML_FIXED_POINT
    return FixedTrunc(x);
#else
    return mlFloatToScalar(truncf(mlScalarToFloat(x)));
#endif
}

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


//------------------------------------------------------------------------
// Routines that are required by the rehearsal workprint reader
// and writer.  We may want to write a fixed/float internal format into
// the floating point workprint.  
// XXX We explicity assume that sizeof(long) == sizeof(MlScalar) as fixed
// point and ignore the MlScalar type below.  The reason is that the 
// workprint read/writer is compiled with MlScalar == float, which is NOT
// what we want.

float ML_MATH_STDCALL mlFixedToFloat(long val);
long ML_MATH_STDCALL mlFloatToFixed(float f);

#endif /* SCALAR_H_INCLUDED */
