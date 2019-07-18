// COPYRTIGH_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2016 - 2019 Wizzer Works
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

// Include Google Test header files.
#include "gtest/gtest.h"

// Include Magic Lantern header files.
#include "math/rotation.h"
#include "math/transfrm.h"
#include "math/angle.h"

// Print rotation for debugging purposes.
void printTransform(MlRotation &r) {
    printf("t[0] = %.9g\n", r[0]);
    printf("t[1] = %.9g\n", r[1]);
    printf("t[2] = %.9g\n", r[2]);
    printf("t[3] = %.9g\n", r[3]);
}

TEST(MlRotationTest, DefaultConstrutor) {
    // This test is named "DefaultConstructor", and belongs to the "MlRotationTest"
    // test case.

    MlRotation *r = new MlRotation();
    EXPECT_TRUE(r != NULL);
}

TEST(MlRotationTest, GetValue) {
    // This test is named "GetValue", and belongs to the "MlRotationTest"
    // test case.

    MlRotation *r = new MlRotation();
    EXPECT_TRUE(r != NULL);
    r->setValue(0, 0, 0, 1);

    MlScalar q0, q1, q2, q3;
    r->getValue(q0, q1, q2, q3);
    EXPECT_FLOAT_EQ(q0, 0);
    EXPECT_FLOAT_EQ(q1, 0);
    EXPECT_FLOAT_EQ(q2, 0);
    EXPECT_FLOAT_EQ(q3, 1);

    const MlScalar *quat = r->getValue();
    EXPECT_FLOAT_EQ(quat[0], 0);
    EXPECT_FLOAT_EQ(quat[1], 0);
    EXPECT_FLOAT_EQ(quat[2], 0);
    EXPECT_FLOAT_EQ(quat[3], 1);

    MlVector3 axis;
    MlScalar angle;
    r->getValue(axis, angle);
    EXPECT_FLOAT_EQ(axis[0], 0);
    EXPECT_FLOAT_EQ(axis[1], 0);
    EXPECT_FLOAT_EQ(axis[2], 1);
    EXPECT_FLOAT_EQ(angle, 0);

    MlTransform t;
    r->getValue(t);
    EXPECT_FLOAT_EQ(t[0][0], 1);
    EXPECT_FLOAT_EQ(t[0][1], 0);
    EXPECT_FLOAT_EQ(t[0][2], 0);
    EXPECT_FLOAT_EQ(t[1][0], 0);
    EXPECT_FLOAT_EQ(t[1][1], 1);
    EXPECT_FLOAT_EQ(t[1][2], 0);
    EXPECT_FLOAT_EQ(t[2][0], 0);
    EXPECT_FLOAT_EQ(t[2][1], 0);
    EXPECT_FLOAT_EQ(t[2][2], 1);
    EXPECT_FLOAT_EQ(t[3][0], 0);
    EXPECT_FLOAT_EQ(t[3][1], 0);
    EXPECT_FLOAT_EQ(t[3][2], 0);
}

TEST(MlRotationTest, Multiplication) {
    // This test is named "Multiplication", and belongs to the "MlRotationTest"
    // test case.

    MlRotation *r = new MlRotation();
    EXPECT_TRUE(r != NULL);
    r->setValue(0, 0, 0, 1);

    MlRotation *delta = new MlRotation(ML_SCALAR_ZERO, ML_SCALAR_ONE, ML_SCALAR_ZERO, 0.035f);
    *r *= *delta;
    MlScalar q0, q1, q2, q3;
    r->getValue(q0, q1, q2, q3);
    EXPECT_FLOAT_EQ(q0, 0.0);
    EXPECT_FLOAT_EQ(q1, 0.9993880987167358);
    EXPECT_FLOAT_EQ(q2, 0.0);
    EXPECT_FLOAT_EQ(q3, 0.034978583455085754);
}
