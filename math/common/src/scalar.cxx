
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
//  For information concerning this source file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// Include Magic Lantern header files.
#include "mle/mlTypes.h"

#if (! ML_FIXED_POINT)
#include <math.h>
#endif

// Include Magic Lantern math header files.
#include "math/scalar.h"

//------------------------------------------------------------------------

static inline int
isOdd(const unsigned long number)
{
    return (number & 0x1);
}

// z = x ^ i;
MlScalar
mlPowInt( const MlScalar x, const int i )
{
    if (i == 0) {
        return ML_SCALAR_ONE;
    }

    if (x == ML_SCALAR_ZERO) {
        if (i > 0) {
            return ML_SCALAR_ZERO;
        }
        else {
            return mlReciprocal( ML_SCALAR_ZERO );
        }
    }

    // Now pick up signs of x, i.

    int sign = x < ML_SCALAR_ZERO;
    MlScalar op = x < ML_SCALAR_ZERO ? -x : x;
    unsigned long exp = i < 0 ? -i : i;
    if (i < 0) {
        op = mlReciprocal(op);
    }

    // Now iterate over powers.
    // Let op become op^(2^j) and ans = product of 
    // op^(2^j + 2^k + 2^l + ...) for jkl.. the bits of exp.

    MlScalar ans = ML_SCALAR_ONE;
    while (exp != 0) {
        if (isOdd(exp)) {
            mlMulBy( ans, op );
        }
        if (exp > 1) {
            (void) mlMulBy( op, op );
        }
        exp >>= 1;
    }
    
    return sign ? -ans : ans;
}

//------------------------------------------------------------------------

int
mlScalarIsFloat(void)
{
#if ML_FIXED_POINT
    return FALSE;
#else
    return TRUE;
#endif
}

int
mlScalarIsMathDebug(void)
{
#if ML_MATH_DEBUG
    return TRUE;
#else
    return FALSE;
#endif
}

float 
mlFixedToFloat(long val)
{
    return val / ML_FIXED_SCALE;
}

long 
mlFloatToFixed(float f)
{
    return f * ML_FIXED_SCALE;
}
