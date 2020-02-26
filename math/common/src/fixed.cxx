
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

#if defined(ML_DEBUG)
#include <stdio.h>
#endif

// include Magic Lantern math header files
#include "math/scalar.h"

// include Magic Lantern kernel header files
#include "mle/mlAssert.h"


//------------------------------------------------------------------------
// Only do this if we\'re compiled in fixed point mode.  Otherwise 
// don\'t build any of these functions.

#if ML_FIXED_POINT

#define _ML_FD_BIGNUM 0x7fffffff

// Find the index of the highest bit set in a ulong integer.  Thus
// if ind = HighBitIndex(A), then A & (1<<ind) is true, but not true
// for A & (1<<N), for N > ind.

static long 
HighBitIndex(const unsigned long opA)
{
    unsigned long op = opA;
    long ind = 0;
    if (op & 0xffff0000) {
        ind += 16;
        op >>= 16;
    }
    if (op & 0x0000ff00) {
        ind += 8;
        op >>= 8;
    }
    if (op & 0x000000f0) {
        ind += 4;
        op >>= 4;
    }
    if (op & 0x0000000c) {
        ind += 2;
        op >>= 2;
    }
    if (op & 0x00000002) {
        ind += 1;
        op >>= 1;
    }
    if (op & 0x00000001) {
        ind += 1;
    }
    return ind;
}

// Don\'t build this in a runtime title, as it requires the C stdio lib.
#if defined(ML_DEBUG) 
void 
FixedPrint( MlScalar number, char *string=NULL )
{
    char buf[128];

    if (string) {
        sprintf( buf, "Var: %20.20s  ", string );
    }
    else {
        buf[0] = '\0';
    }

    printf("%sFixed: 0x%lx  Int: %d  Float: %f\n",
           buf,
           mlScalarGetValue(number),
           mlScalarToLong(number),
           mlScalarToFloat(number));
}
#endif

// Test for near equality in fixed point. We don\'t use relative error,
// but rather the number of bits to ignore in the test, an absolute measure
// of the error we\'ll allow.
int
FixedAlmostEqual(const MlScalar valA, const MlScalar valB, const int nBitsTol)
{
    register long opA = mlScalarGetValue(valA);
    register long opB = mlScalarGetValue(valB);
#if ML_FIXED_CHECK_UNINITIALIZED
    MLE_ASSERT(opA != 0xdeadbeef);
    MLE_ASSERT(opB != 0xdeadbeef);
    MLE_ASSERT(nBitsTol >= 0 && nBitsTol <= 31);
#endif
    int ans;
    if (nBitsTol > 0) {
        ans = (opA >> nBitsTol) == (opB >> nBitsTol);
        // Could be off by 1 in last bit, as in 0x0ffff vs 0x10000.
        // Make a special effort to catch this, by shifting off
        // one fewer bits, then seeing if the difference is 1 in
        // the last place.  Why is it so complicated?
        if (!ans) {
            int tol = nBitsTol - 1;
            long diff = (opA >> tol) - (opB >> tol);
            diff = (diff < 0) ? -diff : diff;
            ans = diff == 1;
        }
    }
    else {
        ans = opA == opB;
    }

#if 0
    ML_DEBUG_CATLEVEL("math",3, {
        if (!ans) {
            int neededBitsTol;
            for ( neededBitsTol=0; neededBitsTol<31 && opA != opB; neededBitsTol++) {
                opA >>= 1;
                opB >>= 1;
            }
            printf("Fix pt inequality with %d bits error; need up to %d bits\n",
                   nBitsTol, neededBitsTol);
            FixedPrint( valA, "A" );
            FixedPrint( valB, "B" );
        }
    });
#endif /* 0 */

    return ans;        
}

// Test for exact equality in fixed point.
int
FixedEqual(const MlScalar valA, const MlScalar valB)
{
    return FixedAlmostEqual(valA,valB,0);
}

// Test for exact equality in fixed point.
int
FixedEquiv(const MlScalar valA, const MlScalar valB)
{
    register long opA = mlScalarGetValue(valA);
    register long opB = mlScalarGetValue(valB);
#if ML_FIXED_CHECK_UNINITIALIZED
    MLE_ASSERT(opA != 0xdeadbeef);
    MLE_ASSERT(opB != 0xdeadbeef);
#endif
    return opA == opB;
}


// Interpolate data from a table with a power of two number of bins.
// Assumes that you can index into table[] as table[index] and
// table[index+1], unless remdr == 0, in which case you needn\'t
// do the index+1.

long
FixedTableInterp( const long table[], 
          const long index, 
          const long remdr, 
          const long sign,
          const long remdrShift )
{
    // value == index + remdr*scale, and want to interpolate
    // into the table to approximate table[value]:
    //
    // lower = table(trunc[value])
    // upper = table(ceil[value])
    // remdr = value - trunc[value]
    // so table(value) ~= lower + (upper-lower)*ratio(rmder/binsize)

    long lower = table[index];
    long ans;

    if (remdr != 0) {
        long upper = table[index+1];
        long slope;
        long delta;

        // Take value as linear combination of lower and upper.
        // Notice that we add 0.5 * 2^-RADIX to delta before shifting
        // so that the truncation will actually round.

        slope = (upper - lower);
        delta = slope * (remdr << remdrShift);
        lower += (delta  + (1 << (ML_FIXED_RADIX-1))) 
                      >> ML_FIXED_RADIX;
    }

    ans = (sign) ? -lower : lower;
    return ans;
}


// Interpolate data from a table with a power of two number of bins.
// Assumes that you can index into table[] as table[index] and
// table[index+1], unless remdr == 0, in which case you needn\'t
// do the index+1.

long
FixedShortTableInterp( const short table[], 
               const long index, 
               const long remdr, 
               const long sign,
               const long remdrShift )
{
    // value == index + remdr*scale, and want to interpolate
    // into the table to approximate table[value]:
    //
    // lower = table(trunc[value])
    // upper = table(ceil[value])
    // remdr = value - trunc[value]
    // so table(value) ~= lower + (upper-lower)*ratio(rmder/binsize)

    long lower = table[index];
    long ans;

    if (remdr != 0) {
        long upper = table[index+1];
        long slope;
        long delta;

        // Take value as linear combination of lower and upper.
        // Notice that we add 0.5 * 2^-RADIX to delta before shifting
        // so that the truncation will actually round.

        slope = (upper - lower);
        delta = slope * (remdr << remdrShift);
        lower += (delta  + (1 << (ML_FIXED_RADIX-1))) 
                      >> ML_FIXED_RADIX;
    }

    ans = (sign) ? -lower : lower;
    return ans;
}


#if !(__sgi && ML_FIXED_POINT && !ML_MATH_DEBUG)

// Multiplication in fixed point, with a little bit of multi-radix
// thrown in.
MlScalar
FixedMultiply(const MlScalar valA, const MlScalar valB)
{
    MlScalar ans; 
    register long opA = mlScalarGetValue(valA);
    register long opB = mlScalarGetValue(valB);

    ans = ML_SCALAR(0);

#if ML_FIXED_CHECK_UNINITIALIZED
    MLE_ASSERT(opA != 0xdeadbeef);
    MLE_ASSERT(opB != 0xdeadbeef);
#endif
    char sign = (opA < 0) ^ (opB < 0);
    unsigned long a = opA < 0 ? -opA : opA;
    unsigned long b = opB < 0 ? -opB : opB;
    unsigned long lo32 = ((unsigned short) a) * ((unsigned short) b);
    unsigned long mid32 = ((unsigned short) a) * ((unsigned short) (b >> 16));
#if defined(ML_DEBUG)
    unsigned long temp;
#endif
    MLE_ASSERT(((temp = mid32), 1));
    mid32 += ((unsigned short) (a >> 16)) * ((unsigned short) b);
    MLE_ASSERT(mid32 >= temp); 
    unsigned long top32 = ((unsigned short) (a >> 16)) * ((unsigned short) (b >> 16));

    // Now have 3 32-bit quantities that represent the pairs of 
    // short word multiples.  We want to add them together, but 
    // have to shift into position first.
    // Let D = ML_FIXED_RADIX (eg, 12 or 16) and let I = 32-D.  This is
    // I.D format.  

    // The low order bit of top32 = 2^(2*(I-16)).  And the bits 
    // from top32 have to make a number of <= I-1 bits, so check this 
    // equation to avoid overflow or corruption of the sign bit.
    //     top32 < 2^( I-1 - (2I-32) )
    //     top32 < 2^( 31 - I )
    //     top32 < 2^( D-1 )
    // We want the low order bit of the answer to be 2^-D, so shift
    // top left by D+(2I-32) = 32-I+2I-32 = I = 32-D

    // The low order bit of mid32 = 2^(I-16-D) = 2^(2I-48)  
    // And the bits from mid32 have to make a number of <= I-1 bits, 
    // so check this equation to avoid overflow or corruption of the 
    // sign bit.
    //     mid32 < 2^( I-1 - (2I-48) )
    //     mid32 < 2^( 47 - I )
    // We want the low order bit of the answer to be 2^-D, so shift
    // mid left by D+(2I-48) = 32-I+2I-48 = I-16 = 16-D

    // None of the bits of lo32 will fall off the left of the
    // answer, so don\'t need a test there.
    // Infer from the above that we shift low left by I-32, or
    // shift low right by 32-I=D bits.

#if ML_FIXED_CHECK_OVERFLOW
    ML_DEBUG_CATLEVEL("math",1, {
        // Fix it up.
        if (top32 >= (1 << (ML_FIXED_RADIX-1))) {
            top32 = (1 << (ML_FIXED_RADIX-1)) - 1;
        }
    });
    ML_DEBUG_CATLEVEL("math",3, {
        if (top32 >= (1 << (ML_FIXED_RADIX-1))) {
            printf("Overflow during fixed point multiply 0x%x x 0x%x.\n", opA, opB);
        }
    });
#endif /* ML_FIXED_CHECK_OVERFLOW */
    MLE_ASSERT(top32 < (1 << (ML_FIXED_RADIX-1)));

#if 16 > ML_FIXED_RADIX 
    mid32 << (16-ML_FIXED_RADIX);
#endif
    MLE_ASSERT(((temp = mid32), 1));
    mid32 += lo32 >> ML_FIXED_RADIX;
    MLE_ASSERT(mid32 >= temp);
    MLE_ASSERT(((temp = mid32), 1));
    mid32 += top32 << (32-ML_FIXED_RADIX);

#if ML_FIXED_CHECK_OVERFLOW
    ML_DEBUG_CATLEVEL("math",1, {
        // Fix it up.
        if (mid32 < temp) {
            mid32 = temp;
        }
    });
    ML_DEBUG_CATLEVEL("math",3, {
        if (mid32 < temp) {
            printf("Overflow during fixed point multiply 0x%x x 0x%x.\n", opA, opB);
        }
    });
#endif /* ML_FIXED_CHECK_OVERFLOW */
    MLE_ASSERT(mid32 >= temp);
    MLE_ASSERT(ML_FIXED_RADIX == 12 || ML_FIXED_RADIX == 16);

    // Finally assert that the answer really did fit into 31 bits
    // then apply sign conversion.

#if ML_FIXED_CHECK_OVERFLOW
    ML_DEBUG_CATLEVEL("math",1, {
        // Fix it up.
        if (mid32 >= 0x80000000) {
            mid32 = 0x80000000 - 0x1;
        }
    });
    ML_DEBUG_CATLEVEL("math",3, {
        if (mid32 >= 0x80000000) {
            printf("Overflow during fixed point multiply 0x%x x 0x%x.\n", opA, opB);
        }
    });
#endif /* ML_FIXED_CHECK_OVERFLOW */
    MLE_ASSERT(mid32 < 0x80000000);
    //long intVal = sign ? -mid32 : mid32;
	long intVal;
	if (sign) intVal = 0 - mid32;
	else intVal = mid32;
    ans = mlScalarSetValue( intVal);
    return ans;
}

#endif /* !(__sgi && ML_FIXED_POINT && !ML_MATH_DEBUG) */


MlScalar
FixedDivide(const MlScalar valA, const MlScalar valB)
{
    register long opA = mlScalarGetValue(valA);
    register long opB = mlScalarGetValue(valB);
    MlScalar ans;

#if ML_FIXED_CHECK_UNINITIALIZED
    MLE_ASSERT(opA != 0xdeadbeef);
    MLE_ASSERT(opB != 0xdeadbeef);
#endif

    // Check for x/0, 0/0, and 0/x as special cases.
    // We\'ll leave it for 

    if (opB == 0) {
#if 0
        ML_DEBUG_CATLEVEL("math",1, {
            // Fix it up.
            if (opB == 0) {
                opB = 1;
            }
        });
        ML_DEBUG_CATLEVEL("math",3, {
            if (opB == 0) {
                printf("Fixed point divide by zero 0x%x / 0.\n", opA);
            }
        });
#endif /* 0 */

        MLE_ASSERT(opB != 0);
        if (opA == 0) {
            ans = ML_SCALAR_ONE;
            return ans;
        }
        else {
            ans = mlScalarSetValue(_ML_FD_BIGNUM);
            return ans;
        }
    }
    else if (opA == 0) {
        ans = ML_SCALAR_ZERO;
        return ans;
    }
        

    char sign = (opA < 0) ^ (opB < 0);
    unsigned long dividend = opA < 0 ?  -opA : opA;
    unsigned long divisor = opB < 0 ? -opB : opB;
    unsigned long divisorTimes2 = divisor << 1;
    int shift = 16;

    // normalize dividend to be >= divisor
    // XXX - You might try to optimize this to shift by 2,4,8 to get 
    // faster normalization.  But you\'d really want to instrument
    // the code to get some idea of how often this is useful.

    if (dividend < divisor) {
        while ((dividend < divisor) && --shift >= 0) {
            dividend <<= 1;
        }
        if (shift < 0) {
#ifdef ML_FIXED_DETECT_UNDERFLOW
            MLE_ASSERT(shift >= 0); // underflow
#endif
            return ML_SCALAR_ZERO;
        }
    }
    else if (dividend >= divisorTimes2) {
        // normalize dividend to be in [divisor...2*divisor]
        // XXX - Again you might be able to optimize this.
        
        while ((dividend >= divisorTimes2) && ++shift < 31) {
            // Which is faster?
            // divisor <<= 1;
            // divisorTimes2 <<= 1;
            divisorTimes2 = (divisor = divisorTimes2) << 1;
        }

        // Always detect overflow in one way or another.
        if (shift >= 31) {
            MLE_ASSERT(shift < 31); // overflow
            MlScalar bigNum;
            bigNum = mlScalarSetValue(_ML_FD_BIGNUM);
            return bigNum;
        }
    }

    // Now we have dividend > divisor with dividend/divisor = 1.xxxxx
    // Do the shift and subtract work until we\'ve collected enough
    // bits of the answer.  The variable shift+1 tells us how many we
    // need.

    // XXX Could probably make this faster by handling 2,3,4 bits at
    // a time.  Is it worth it?

    unsigned long bit;
    unsigned long quotient = 0;
    do {
        if (bit = (dividend >= divisor)) {
            dividend -= divisor;
        }
        dividend <<= 1;
        quotient = (quotient << 1) | bit;
    } while ((--shift >= 0) && dividend);

    if (shift >= 0) {
        quotient <<= (shift + 1);
    }

    // XXX - You could do rounding here if you wanted, by checking
    // whether dividend>=divisor and then adjusting the last bit.
    // Graphics guys don\'t care about this, though :-).

    //ans = mlScalarSetValue(sign ? -quotient : quotient);
    if (sign) ans = mlScalarSetValue(0 - quotient);
	else ans = mlScalarSetValue(quotient);
    return ans;
}

// Do this to avoid intermediate underflow or overflow when the final
// result does not have it.  
// Let indA, indB, and indC be indices of high-order bits of a/b/c.
// let I.D be format as usual.
// if (indA+indB-D-1) > 31 (sometimes 30)  you\'ll get overflow
// if you multiply (a*b)/c.
//    in this case if C > (1<<D), do (a/c)*b.
//
// if (indA+indB-D-1) <= 0 (sometimes -1)  you\'ll get underflow
// if you multiply (a*b)/c.
//    in this case if C < (1<<D), do (a/c)*b.
//
MlScalar
FixedMulDiv(const MlScalar valA, const MlScalar valB, const MlScalar valC)
{
    register long opA = mlScalarGetValue(valA);
    register long opB = mlScalarGetValue(valB);
    MlScalar ans;
#if ML_FIXED_CHECK_UNINITIALIZED
    MLE_ASSERT(opA != 0xdeadbeef);
    MLE_ASSERT(opB != 0xdeadbeef);
    register long opC = mlScalarGetValue(valC);
    MLE_ASSERT(opC != 0xdeadbeef);
#endif
    int indA = HighBitIndex( opA );
    int indB = HighBitIndex( opB );

    int indAB = (indA + indB - ML_FIXED_RADIX - 1);
    if (indAB < 31 && indAB > 0) {
        ans = FixedDivide(FixedMultiply(valA,valB),valC);
    }
    else {
        unsigned long a = opA < 0 ? -opA : opA;
        unsigned long b = opB < 0 ? -opB : opB;

        // swap a to larger.
        if (b > a) {
            ans = FixedMultiply(FixedDivide(valB,valC),valA);
        }
        else {
            // I think this is the best we can do, letting
            // over/underflow happen if it\'s unavoidable.
            ans = FixedMultiply(FixedDivide(valA,valC),valB);
        }
    }
    return ans;
}
#undef _ML_FD_BIGNUM 

#define LOWER_BIT_MASK ((1 << ML_FIXED_RADIX) - 1)
#define UPPER_BIT_MASK (0xffffffff ^ LOWER_BIT_MASK)

// Round down (biased)
MlScalar 
FixedFloor( const MlScalar val )
{
    register long opA = mlScalarGetValue(val);
#if ML_FIXED_CHECK_UNINITIALIZED
    MLE_ASSERT(opA != 0xdeadbeef);
#endif
    MlScalar ans;

    opA &= UPPER_BIT_MASK;
    ans = mlScalarSetValue( opA );

    return ans;
}

// Round up (biased)
MlScalar 
FixedCeil( const MlScalar val )
{
    register long opA = mlScalarGetValue(val);
#if ML_FIXED_CHECK_UNINITIALIZED
    MLE_ASSERT(opA != 0xdeadbeef);
#endif
    MlScalar ans;

    // subtract 1 ULP, round down, then add 0001.0000 
    // to round up
    //

    opA = (1<<ML_FIXED_RADIX) + ((opA-1) & UPPER_BIT_MASK);
    ans = mlScalarSetValue( opA );

    return ans;
}

// Round toward zero
MlScalar 
FixedTrunc( const MlScalar val )
{
    register long opA = mlScalarGetValue(val);
#if ML_FIXED_CHECK_UNINITIALIZED
    MLE_ASSERT(opA != 0xdeadbeef);
#endif
    MlScalar ans;
    char sign = opA < 0;
    unsigned long a = opA < 0 ? -opA : opA;

    a &= UPPER_BIT_MASK;
    //ans = mlScalarSetValue( sign ? -a : a );
	if (sign) ans = mlScalarSetValue(0 - a);
	else ans = mlScalarSetValue(a);

    return ans;
}
#undef LOWER_BIT_MASK
#undef UPPER_BIT_MASK


#endif /* ML_FIXED_POINT */
