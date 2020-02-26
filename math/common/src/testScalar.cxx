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
//
//  For information concerning this source file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// include Magic Lantern math header files.
#include "math/scalar.h"

#if (!defined(TEST_SCALAR_ILLEGAL) && !defined(TEST_SCALAR_LEGAL))
#define TEST_SCALAR_LEGAL 1
#endif

// test
static AuScalar ExpectsAScalarArgument(AuScalar number)
{
    return number;
}

static long ExpectsALongArgument(long number)
{
    return number;
}

#ifdef TEST_SCALAR_ILLEGAL
static int
Illegal(void)
{
// Every line in the body of this function should generate an error
// The Makefile will pass the output through a filter that expects an error on
// each line.  If you add a comment between lines, you\'ll break the testing
// setup!
//
// printf("%d\n", scalarArg); // this does not generate an error, unfortunately
//
// First line MUST generate an error.
    AuScalar scalarArg = 3;
    long longArg = ExpectsALongArgument(scalarArg);
    AuScalar c = ExpectsAScalarArgument(3);
    long e = ExpectsAScalarArgument(scalarArg);
    AuScalar f = ExpectsALongArgument(3);
    scalarArg + 3;         // void operator+ (const long) const {}
    scalarArg + longArg;
    3 + scalarArg;         // friend void operator+ (const long, const AuScalar) {}
    longArg + scalarArg;
    scalarArg += 3;        // void operator+= (const long) {}
    scalarArg += longArg;
    longArg += scalarArg;  // friend void operator+= (const long, const AuScalar) {}
    scalarArg + 3.0;       // void operator+ (const double) const {}
    double dblArg = 3.0; scalarArg + dblArg;
    3.0 + scalarArg;
    dblArg + scalarArg;
    scalarArg += 3.0;
    scalarArg += dblArg;
    scalarArg - longArg;   // void operator- (const long) const {}
    longArg - scalarArg;   // friend void operator- (const long, const AuScalar) {}
    scalarArg -= longArg;  // void operator-= (const long) {}
    longArg -= scalarArg;  // friend void operator-= (const long, const AuScalar) {}
    scalarArg - dblArg;    // void operator- (const double) const {}
    longArg *= scalarArg;  // friend void operator*= (const long, const AuScalar) {}
    longArg / scalarArg;   // friend void operator/ (const long, const AuScalar) {}
    scalarArg / 0.25;      //    
    longArg /= scalarArg;  // friend void operator/= (const long, const AuScalar) {}
    scalarArg << scalarArg;// void operator<< (const AuScalar) const {}
    scalarArg << longArg;  // void operator<< (const AuScalar) const {}
    longArg << scalarArg;  // friend void operator<< (const long, const AuScalar) {}
    scalarArg <<= scalarArg;// void operator<<= (const AuScalar) {}
    longArg <<= scalarArg;  // friend void operator<<= (const long, const AuScalar) {}
    scalarArg <<= longArg;  // void operator<<= (const AuScalar) {}
    scalarArg >> scalarArg; // void operator>> (const AuScalar) const {}
    longArg >> scalarArg;   // friend void operator>> (const long, const AuScalar) {}
    scalarArg >> longArg;   // void operator>> (const AuScalar) const {}
    scalarArg >>= scalarArg;// void operator>>= (const AuScalar) {}
    longArg >>= scalarArg;  // friend void operator>>= (long, const AuScalar) {}
    scalarArg >>= longArg;  // void operator>>= (const AuScalar) {}
    scalarArg * scalarArg;  // AuScalar operator* (const AuScalar operand) const ;
    scalarArg *= scalarArg; // AuScalar& operator*= (const AuScalar operand) ;
    scalarArg / scalarArg;  // AuScalar operator/ (const AuScalar operand) const ;
    scalarArg /= scalarArg; // AuScalar& operator/= (const AuScalar operand) ;
    ~scalarArg;             // AuScalar operator~ () const
    scalarArg|scalarArg;    // AuScalar operator| (const AuScalar operand) const
    scalarArg|longArg;      // AuScalar operator| (const long operand) const
    longArg|scalarArg;      // friend AuScalar operator| (const long operand,const AuScalar s) const
    return scalarArg;       // XXX Make sure to keep this last so you end on an error.
// Last line MUST generate an error.
}
#endif

#ifdef TEST_SCALAR_LEGAL
static int 
Legal(void)
{
    AuScalar a = AU_SCALAR(3);
    AuScalar b = a + AU_SCALAR(2.0f);
    AU_ASSERT(3==auScalarToLong(a));
    AU_ASSERT(3.0f==auScalarToFloat(a));
    AU_ASSERT(5==auScalarToLong(b));
    AU_ASSERT(5.0f==auScalarToFloat(b));
    AU_ASSERT(3==auScalarGetValue(a)>>AU_FIXED_RADIX);
    AU_ASSERT(5==auScalarGetValue(b)>>AU_FIXED_RADIX);

    int i = 37;
    int ni = -48;
    float f = 3.14159265358979323f;
    float nf = -0.314159265358979323f;

    AuScalar scalarInt = auLongToScalar(i);
    AuScalar scalarFloat = auFloatToScalar(f);
    AuScalar scalarNegInt = auLongToScalar(ni);
    AuScalar scalarNegFloat = auFloatToScalar(nf);

    long longArg = ExpectsALongArgument(3);
    AuScalar scalarArg = ExpectsAScalarArgument(scalarInt);

    //    AuScalar operator+ (const AuScalar number) const ;
    scalarArg = scalarInt + scalarFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i+f),1));

    scalarArg = scalarNegInt + scalarNegFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(ni+nf),0));

    scalarArg = scalarInt + scalarNegFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i+nf),3));

    //    AuScalar& operator+= (const AuScalar number) ;
    scalarArg = scalarInt;
    scalarArg += scalarFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i+f),1));

    scalarArg = scalarNegInt;
    scalarArg += scalarNegFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(ni+nf),0));

    scalarArg = scalarInt;
    scalarArg += scalarNegFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i+nf),3));

    //    AuScalar& operator-= (const AuScalar number) ;
    scalarArg = scalarInt;
    scalarArg -= scalarFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i-f),1));

    scalarArg = scalarNegInt;
    scalarArg -= scalarNegFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(ni-nf),2));

    scalarArg = scalarInt;
    scalarArg -= scalarNegFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i-nf),1));

    //    AuScalar operator- (const AuScalar number) const ;
    scalarArg = scalarInt - scalarFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar((float)(i-f)),1));

    scalarArg = scalarNegInt - scalarNegFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar((float)(ni-nf)),2));

    scalarArg = scalarInt - scalarNegFloat;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar((float)(i-nf)),1));

    //    AuScalar operator* (const long operand) const ;
    scalarArg = scalarInt * longArg;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i*3),0));

    scalarArg = scalarNegInt * longArg;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(ni*3),0));

    scalarArg = scalarInt * longArg;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i*3),0));

    //    friend AuScalar operator* (const long operand, const AuScalar op2) ;
    scalarArg = longArg * scalarInt;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i*3),0));

    scalarArg = longArg * scalarNegInt;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(ni*3),0));

    //    AuScalar& operator*= (const long operand) ;
    scalarArg = scalarInt;
    scalarArg *= longArg;    
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(i*3),0));

    scalarArg = scalarNegInt;
    scalarArg *= longArg;    
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(ni*3),0));

    //    AuScalar operator/ (const long operand) const ;
    scalarArg = scalarFloat / longArg;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(f/3),0));

    scalarArg = scalarNegFloat / longArg;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(nf/3),0));

    //    AuScalar& operator/= (const long operand) ;
    scalarArg = scalarFloat;
    scalarArg /= longArg;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(f/3),0));

    scalarArg = scalarNegFloat;
    scalarArg /= longArg;
    AU_ASSERT(FixedAlmostEqual(scalarArg,auFloatToScalar(nf/3),0));

#define SCALAR_UNOP_TEST(operator,op,convert,expr,bits) \
    scalarArg = operator op; \
    AU_ASSERT(FixedAlmostEqual(scalarArg,convert(expr),bits))

#define SCALAR_BINOP_TEST(operator,op1,op2,convert,expr,bits) \
    scalarArg = op1 operator op2; \
    AU_ASSERT(FixedAlmostEqual(scalarArg,convert(expr),bits))

#define SCALAR_LOGICAL_BINOP_TEST(operator,op1,op2,expr,bits) \
    scalarArg = auLongToScalar(op1 operator op2); \
    AU_ASSERT(FixedAlmostEqual(scalarArg,auLongToScalar((expr)),bits))

    //    int operator> (const AuScalar operand) const
    SCALAR_LOGICAL_BINOP_TEST(>,scalarFloat,scalarInt,f>i,0);
    SCALAR_LOGICAL_BINOP_TEST(>,scalarInt,scalarInt,i>i,0);
    SCALAR_LOGICAL_BINOP_TEST(>,scalarNegFloat,scalarInt,nf>i,0);

    //    int operator>= (const AuScalar operand) const
    SCALAR_LOGICAL_BINOP_TEST(>=,scalarFloat,scalarInt,f>=i,0);
    SCALAR_LOGICAL_BINOP_TEST(>=,scalarInt,scalarInt,i>=i,0);
    SCALAR_LOGICAL_BINOP_TEST(>=,scalarNegFloat,scalarInt,nf>=i,0);

    //    int operator< (const AuScalar operand) const
    SCALAR_LOGICAL_BINOP_TEST(<,scalarFloat,scalarInt,f<i,0);
    SCALAR_LOGICAL_BINOP_TEST(<,scalarInt,scalarInt,i<i,0);
    SCALAR_LOGICAL_BINOP_TEST(<,scalarNegFloat,scalarInt,nf<i,0);

    //    int operator<= (const AuScalar operand) const
    SCALAR_LOGICAL_BINOP_TEST(<=,scalarFloat,scalarInt,f<=i,0);
    SCALAR_LOGICAL_BINOP_TEST(<=,scalarInt,scalarInt,i<=i,0);
    SCALAR_LOGICAL_BINOP_TEST(<=,scalarNegFloat,scalarInt,nf<=i,0);

    //    int operator== (const AuScalar operand) const
    SCALAR_LOGICAL_BINOP_TEST(==,scalarFloat,scalarInt,f==i,0);
    SCALAR_LOGICAL_BINOP_TEST(==,scalarInt,scalarInt,i==i,0);
    SCALAR_LOGICAL_BINOP_TEST(==,scalarNegFloat,scalarInt,nf==i,0);

    //    int operator!= (const AuScalar operand) const
    SCALAR_LOGICAL_BINOP_TEST(!=,scalarFloat,scalarInt,f!=i,0);
    SCALAR_LOGICAL_BINOP_TEST(!=,scalarInt,scalarInt,i!=i,0);
    SCALAR_LOGICAL_BINOP_TEST(!=,scalarNegFloat,scalarInt,nf!=i,0);

    //    AuScalar operator- () const
    SCALAR_UNOP_TEST(-,scalarFloat,auFloatToScalar,-f,1);
    SCALAR_UNOP_TEST(-,scalarInt,auLongToScalar,-i,0);
    SCALAR_UNOP_TEST(-,scalarNegFloat,auFloatToScalar,-nf,1);

    //    AuScalar operator+ () const
    SCALAR_UNOP_TEST(+,scalarFloat,auFloatToScalar,+f,0);
    SCALAR_UNOP_TEST(+,scalarInt,auLongToScalar,+i,0);
    SCALAR_UNOP_TEST(+,scalarNegFloat,auFloatToScalar,+nf,0);

    //    AuScalar operator! () const
    SCALAR_UNOP_TEST(!,scalarFloat,auLongToScalar,!f,0);
    SCALAR_UNOP_TEST(!,scalarInt,auLongToScalar,!i,0);
    SCALAR_UNOP_TEST(!,scalarNegFloat,auLongToScalar,!nf,0);

    //    friend AuScalar operator| (const long operand, const AuScalar op2)
    //    AuScalar& operator|= (const AuScalar operand)
    //    AuScalar& operator|= (const long operand)
    //    friend long operator|= (const long operand, const AuScalar op2)
    //    AuScalar operator^ (const AuScalar operand) const
    //    AuScalar operator^ (const long operand) const
    //    friend AuScalar operator^ (const long operand, const AuScalar op2)
    //    AuScalar& operator^= (const AuScalar operand)
    //    AuScalar& operator^= (const long operand)
    //    friend long operator^= (const long operand, const AuScalar op2)
    //    AuScalar operator& (const AuScalar operand) const
    //    AuScalar operator& (const long operand) const
    //    friend AuScalar operator& (const long operand, const AuScalar op2)
    //    AuScalar& operator&= (const AuScalar operand)
    //    AuScalar& operator&= (const long operand)
    //    friend long operator&= (const long operand, const AuScalar op2)
    //    AuScalar operator|| (const AuScalar operand) const
    //    AuScalar operator|| (const long operand) const
    //    friend AuScalar operator|| (const long operand, const AuScalar op2)
    //    AuScalar operator&& (const AuScalar operand) const
    //    AuScalar operator&& (const long operand) const
    //    friend AuScalar operator&& (const long operand, const AuScalar op2)

#if 0
    // Some code for when you\'re constructing the tests.
    AU_ASSERT(1==0); /* Only done to here. */
#endif
    
    return 0;
}
#endif

int
main()
{
    int ans = 0;

#if TEST_SCALAR_LEGAL
    printf("Testing legal code ... ");
    ans = Legal();
#else
    printf("No tests executed!\n");
#endif
    printf("passed.\n");
    return ans;
}
