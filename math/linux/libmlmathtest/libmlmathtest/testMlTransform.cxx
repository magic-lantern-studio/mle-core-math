// COPYRTIGH_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2016 - 2017 Wizzer Works
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
#include "math/transfrm.h"
#include "math/angle.h"

// Print transform for debugging purposes.
void printTransform(MlTransform &t) {
	printf("t[0][0] = %.9g\n", t[0][0]);
	printf("t[0][1] = %.9g\n", t[0][1]);
	printf("t[0][2] = %.9g\n", t[0][2]);
	printf("t[1][0] = %.9g\n", t[1][0]);
	printf("t[1][1] = %.9g\n", t[1][1]);
	printf("t[1][2] = %.9g\n", t[1][2]);
	printf("t[2][0] = %.9g\n", t[2][0]);
	printf("t[2][1] = %.9g\n", t[2][1]);
	printf("t[2][2] = %.9g\n", t[2][2]);
	printf("t[3][0] = %.9g\n", t[3][0]);
	printf("t[3][1] = %.9g\n", t[3][1]);
	printf("t[3][2] = %.9g\n", t[3][2]);
}

// Print vector for debugging purposes.
void printVector3(MlVector3 &v, char *m) {
	printf("%s[0] = %.9g\n", m, v[0]);
	printf("%s[1] = %.9g\n", m, v[1]);
	printf("%s[2] = %.9g\n", m, v[2]);
}

// Print rotation for debugging purposes.
void printRotation(MlRotation &r, char *m) {
	printf("%s[0] = %.9g\n", m, r[0]);
	printf("%s[0] = %.9g\n", m, r[1]);
	printf("%s[0] = %.9g\n", m, r[2]);
	printf("%s[0] = %.9g\n", m, r[3]);
}

TEST(MlTransformTest, DefaultConstrutor) {
    // This test is named "DefaultConstructor", and belongs to the "MlTransformTest"
    // test case.

	MlTransform *t = new MlTransform();

    EXPECT_TRUE(t != NULL);
}

TEST(MlTransformTest, InitConstrutorFromElements) {
    // This test is named "InitConstructorFromElements", and belongs to the "MlTransformTest"
    // test case.

	MlScalar a11 = 0;
	MlScalar a12 = 0;
	MlScalar a13 = 0;
	MlScalar a21 = 0;
	MlScalar a22 = 0;
	MlScalar a23 = 0;
	MlScalar a31 = 0;
	MlScalar a32 = 0;
	MlScalar a33 = 0;
	MlScalar a41 = 0;
	MlScalar a42 = 0;
	MlScalar a43 = 0;

	MlTransform *t = new MlTransform(a11, a12, a13, a21, a22, a23, a31, a32, a33, a41, a42, a43);

	EXPECT_TRUE(t != NULL);

	int v = t->isZero();
	EXPECT_EQ(v, 1);
}

TEST(MlTransformTest, InitConstrutorFrom4x3Array) {
    // This test is named "InitConstructorFrom4x3Array", and belongs to the "MlTransformTest"
    // test case.

	MlScalar a[4][3];
	a[0][0] = 0; a[0][1] = 0; a[0][2] = 0;
	a[1][0] = 0; a[1][1] = 0; a[1][2] = 0;
	a[2][0] = 0; a[2][1] = 0; a[2][2] = 0;
	a[3][0] = 0; a[3][1] = 0; a[3][2] = 0;


	MlTransform *t = new MlTransform(a);

	EXPECT_TRUE(t != NULL);

	int v = t->isZero();
	EXPECT_EQ(v, 1);
}

TEST(MlTransformTest, InitConstrutorFrom4x4Array) {
    // This test is named "InitConstructorFrom4x4Array", and belongs to the "MlTransformTest"
    // test case.

	MlScalar a[4][4];
	a[0][0] = 0; a[0][1] = 0; a[0][2] = 0; a[0][3] = 0;
	a[1][0] = 0; a[1][1] = 0; a[1][2] = 0; a[1][3] = 0;
	a[2][0] = 0; a[2][1] = 0; a[2][2] = 0; a[2][3] = 0;
	a[3][0] = 0; a[3][1] = 0; a[3][2] = 0; a[3][3] = 0;


	MlTransform *t = new MlTransform(a);

	EXPECT_TRUE(t != NULL);

	int v = t->isZero();
	EXPECT_EQ(v, 1);
}

TEST(MlTransformTest, MakeIdentity) {
    // This test is named "MakeIdentity", and belongs to the "MlTransformTest"
    // test case.

	MlTransform t;
	t.makeIdentity();

	int v = t.isIdentity();
	EXPECT_EQ(v, 1);

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

TEST(MlTransformTest, GetIdentity) {
    // This test is named "GetIdentity", and belongs to the "MlTransformTest"
    // test case.

	MlTransform t;
	t = MlTransform::identity();

	int v = t.isIdentity();
	EXPECT_EQ(v, 1);

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

TEST(MlTransformTest, Determinant) {
    // This test is named "Determinant", and belongs to the "MlTransformTest"
    // test case.

	MlTransform t = MlTransform::identity();

	MlScalar v = t.det();
	EXPECT_EQ(v, 1);

	MlTrans a;
	a.m[0][0] = 6; a.m[0][1] = 1; a.m[0][2] = 1;
	a.m[1][0] = 4; a.m[1][1] = -2; a.m[1][2] = 5;
	a.m[2][0] = 2; a.m[2][1] = 8; a.m[2][2] = 7;
	a.m[3][0] = 0; a.m[3][1] = 0; a.m[3][2] = 0;

	t.setValue(a);
	v = t.det();
	EXPECT_FLOAT_EQ(v, -306);
}

TEST(MlTransformTest, SetUniformScale) {
    // This test is named "SetUniformScale", and belongs to the "MlTransformTest"
    // test case.

	MlTransform t = MlTransform::identity();

	MlScalar s = 5;
	t.setScale(s);

	EXPECT_FLOAT_EQ(t[0][0], 5);
	EXPECT_FLOAT_EQ(t[0][1], 0);
	EXPECT_FLOAT_EQ(t[0][2], 0);
	EXPECT_FLOAT_EQ(t[1][0], 0);
	EXPECT_FLOAT_EQ(t[1][1], 5);
	EXPECT_FLOAT_EQ(t[1][2], 0);
	EXPECT_FLOAT_EQ(t[2][0], 0);
	EXPECT_FLOAT_EQ(t[2][1], 0);
	EXPECT_FLOAT_EQ(t[2][2], 5);
	EXPECT_FLOAT_EQ(t[3][0], 0);
	EXPECT_FLOAT_EQ(t[3][1], 0);
	EXPECT_FLOAT_EQ(t[3][2], 0);
}

TEST(MlTransformTest, SetNonUniformScale) {
    // This test is named "SetNonUniformScale", and belongs to the "MlTransformTest"
    // test case.

	MlTransform t = MlTransform::identity();

	MlVector3 s;
	s[0] = 2;
	s[1] = 4;
	s[2] = 8;
	t.setScale(s);

	EXPECT_FLOAT_EQ(t[0][0], 2);
	EXPECT_FLOAT_EQ(t[0][1], 0);
	EXPECT_FLOAT_EQ(t[0][2], 0);
	EXPECT_FLOAT_EQ(t[1][0], 0);
	EXPECT_FLOAT_EQ(t[1][1], 4);
	EXPECT_FLOAT_EQ(t[1][2], 0);
	EXPECT_FLOAT_EQ(t[2][0], 0);
	EXPECT_FLOAT_EQ(t[2][1], 0);
	EXPECT_FLOAT_EQ(t[2][2], 8);
	EXPECT_FLOAT_EQ(t[3][0], 0);
	EXPECT_FLOAT_EQ(t[3][1], 0);
	EXPECT_FLOAT_EQ(t[3][2], 0);
}

TEST(MlTransformTest, SetScaleOnly) {
    // This test is named "SetScaleOnly", and belongs to the "MlTransformTest"
    // test case.

	// Initialize the transform.
	MlTrans a;
	a.m[0][0] = 6; a.m[0][1] = 1; a.m[0][2] = 1;
	a.m[1][0] = 4; a.m[1][1] = -2; a.m[1][2] = 5;
	a.m[2][0] = 2; a.m[2][1] = 8; a.m[2][2] = 7;
	a.m[3][0] = 0; a.m[3][1] = 0; a.m[3][2] = 0;

	MlTransform t;
	t.setValue(a);

	// Set only the nonuniform scale values, not touching translation and rotation.
	MlVector3 s;
	s[0] = 2;
	s[1] = 4;
	s[2] = 8;
	t.setScaleOnly(s);

	//printTransform(t);
	EXPECT_FLOAT_EQ(t[0][0], 1.67600882);
	EXPECT_FLOAT_EQ(t[0][1], -0.925301969);
	EXPECT_FLOAT_EQ(t[0][2], 0.578628063);
	EXPECT_FLOAT_EQ(t[1][0], 2.05352569);
	EXPECT_FLOAT_EQ(t[1][1], 1.9552827);
	EXPECT_FLOAT_EQ(t[1][2], -2.82132959);
	EXPECT_FLOAT_EQ(t[2][0], 1.47920048);
	EXPECT_FLOAT_EQ(t[2][1], 5.91680145);
	EXPECT_FLOAT_EQ(t[2][2], 5.1772027);
	EXPECT_FLOAT_EQ(t[3][0], 0);
	EXPECT_FLOAT_EQ(t[3][1], 0);
	EXPECT_FLOAT_EQ(t[3][2], 0);

	// Check whether extracted nonuniform scale values are the same as the one set above.
	MlVector3 result;
	t.getScale(result);

	//printVector3(result, (char *) "s");
	EXPECT_FLOAT_EQ(result[0], 2);
	EXPECT_FLOAT_EQ(result[1], 4);
	EXPECT_FLOAT_EQ(result[2], 8);
}

TEST(MlTransformTest, SetTranslation) {
    // This test is named "SetTranslation", and belongs to the "MlTransformTest"
    // test case.

	MlTransform t = MlTransform::identity();

	// Set only the translation values, not touching scale and rotation.
	MlVector3 v;
	v[0] = -1;   // Translate along x.
	v[1] = -25;  // Translate along y.
	v[2] = 50;   // Translate along z
	t.setTranslation(v);

	EXPECT_FLOAT_EQ(t[0][0], 1);
	EXPECT_FLOAT_EQ(t[0][1], 0);
	EXPECT_FLOAT_EQ(t[0][2], 0);
	EXPECT_FLOAT_EQ(t[1][0], 0);
	EXPECT_FLOAT_EQ(t[1][1], 1);
	EXPECT_FLOAT_EQ(t[1][2], 0);
	EXPECT_FLOAT_EQ(t[2][0], 0);
	EXPECT_FLOAT_EQ(t[2][1], 0);
	EXPECT_FLOAT_EQ(t[2][2], 1);
	EXPECT_FLOAT_EQ(t[3][0], -1);
	EXPECT_FLOAT_EQ(t[3][1], -25);
	EXPECT_FLOAT_EQ(t[3][2], 50);

	// Check whether extracted translation values are the same as the one set above.
	MlVector3 result;
	t.getTranslation(result);
	EXPECT_FLOAT_EQ(result[0], -1);
	EXPECT_FLOAT_EQ(result[1], -25);
	EXPECT_FLOAT_EQ(result[2], 50);
}

TEST(MlTransformTest, SetTranslationOnly) {
    // This test is named "SetTranslationOnly", and belongs to the "MlTransformTest"
    // test case.

	MlTrans a;
	a.m[0][0] = 6; a.m[0][1] = 1; a.m[0][2] = 1;
	a.m[1][0] = 4; a.m[1][1] = -2; a.m[1][2] = 5;
	a.m[2][0] = 2; a.m[2][1] = 8; a.m[2][2] = 7;
	a.m[3][0] = 0; a.m[3][1] = 0; a.m[3][2] = 0;

	MlTransform t;
	t.setValue(a);

	// Set only the translation values, not touching scale and rotation.
	MlVector3 v;
	v[0] = -1;   // Translate along x
	v[1] = -25;  // Translate along y
	v[2] = 50;   // Translate along z
	t.setTranslationOnly(v);

	EXPECT_FLOAT_EQ(t[0][0], 6);
	EXPECT_FLOAT_EQ(t[0][1], 1);
	EXPECT_FLOAT_EQ(t[0][2], 1);
	EXPECT_FLOAT_EQ(t[1][0], 4);
	EXPECT_FLOAT_EQ(t[1][1], -2);
	EXPECT_FLOAT_EQ(t[1][2], 5);
	EXPECT_FLOAT_EQ(t[2][0], 2);
	EXPECT_FLOAT_EQ(t[2][1], 8);
	EXPECT_FLOAT_EQ(t[2][2], 7);
	EXPECT_FLOAT_EQ(t[3][0], -1);
	EXPECT_FLOAT_EQ(t[3][1], -25);
	EXPECT_FLOAT_EQ(t[3][2], 50);

	// Check whether extracted translation values are the same as the one set above.
	MlVector3 result;
	t.getTranslation(result);
	EXPECT_FLOAT_EQ(result[0], -1);
	EXPECT_FLOAT_EQ(result[1], -25);
	EXPECT_FLOAT_EQ(result[2], 50);
}

TEST(MlTransformTest, SetRotationOnly) {
    // This test is named "SetRotationOnly", and belongs to the "MlTransformTest"
    // test case.

	MlTransform t = MlTransform::identity();

	// Set only the rotation values, not touching scale and translation.
	MlVector3 v;
	v[0] = 10;  // Rotate 10 degrees around the x axis.
	v[1] = 10;  // Rotate 10 degrees around the y axis.
	v[2] = 10;  // Rotate 10 degrees around the z axis.
	t.setRotationOnly(v);

	/*
	printTransform(t);
	*/
	EXPECT_FLOAT_EQ(t[0][0], 0.969846249);
	EXPECT_FLOAT_EQ(t[0][1], 0.200705662);
	EXPECT_FLOAT_EQ(t[0][2], -0.138258353);
	EXPECT_FLOAT_EQ(t[1][0], -0.171010077);
	EXPECT_FLOAT_EQ(t[1][1], 0.9646101);
	EXPECT_FLOAT_EQ(t[1][2], 0.200705677);
	EXPECT_FLOAT_EQ(t[2][0], 0.173648193);
	EXPECT_FLOAT_EQ(t[2][1], -0.171010077);
	EXPECT_FLOAT_EQ(t[2][2], 0.969846249);
	EXPECT_FLOAT_EQ(t[3][0], 0);
	EXPECT_FLOAT_EQ(t[3][1], 0);
	EXPECT_FLOAT_EQ(t[3][2], 0);

	// Check whether extracted nonuniform scale values are the same as the one set above.
	MlVector3 scale;
	t.getScale(scale);
	//printVector3(scale, (char *) "s");
	EXPECT_FLOAT_EQ(scale[0], 1);
	EXPECT_FLOAT_EQ(scale[1], 1);
	EXPECT_FLOAT_EQ(scale[2], 1);

	// Check whether extracted translation values are the same as the one set above.
	MlVector3 translation;
	t.getTranslation(translation);
	//printVector3(translation, (char *) "t");
	EXPECT_FLOAT_EQ(translation[0], 0);
	EXPECT_FLOAT_EQ(translation[1], 0);
	EXPECT_FLOAT_EQ(translation[2], 0);

	// Check whether extracted rotation values are the same as the one set above.
	MlVector3 rotation;
	t.getRotation(rotation);
	//printVector3(rotation, (char *) "r");
	EXPECT_FLOAT_EQ(rotation[0], 10);
	EXPECT_FLOAT_EQ(rotation[1], 10);
	EXPECT_FLOAT_EQ(rotation[2], 10);
}

TEST(MlTransformTest, SetRotation) {
    // This test is named "SetRotation", and belongs to the "MlTransformTest"
    // test case.

	//MlTransform t = MlTransform::identity();
	MlTransform t(0,0,0,0,0,0,0,0,0,0,0,0);

	MlRotation rot;
	MlVector3 *axis = new MlVector3(1, 1, 1);
	MlScalar angle = mlAngleToRadians(10);
	rot.setValue(*axis, angle);
	//printRotation(rot, (char *) "rot");

	t.setRotation(rot);

	//printTransform(t);
	EXPECT_FLOAT_EQ(t[0][0], 1);
	EXPECT_FLOAT_EQ(t[0][1], 1.5600766e-06);
	EXPECT_FLOAT_EQ(t[0][2], -1.56007411e-06);
	EXPECT_FLOAT_EQ(t[1][0], -1.56007411e-06);
	EXPECT_FLOAT_EQ(t[1][1], 1);
	EXPECT_FLOAT_EQ(t[1][2], 1.56007661e-06);
	EXPECT_FLOAT_EQ(t[2][0], 1.56007661e-06);
	EXPECT_FLOAT_EQ(t[2][1], -1.56007411e-06);
	EXPECT_FLOAT_EQ(t[2][2], 1);
	EXPECT_FLOAT_EQ(t[3][0], 0);
	EXPECT_FLOAT_EQ(t[3][1], 0);
	EXPECT_FLOAT_EQ(t[3][2], 0);

	// Check whether extracted rotation values are the same as the one set above.
	MlVector3 rotation;
	t.getRotation(rotation);
	//printVector3(rotation, (char *) "r");
	EXPECT_FLOAT_EQ(rotation[0], 8.93856632e-05);
	EXPECT_FLOAT_EQ(rotation[1], 8.93858014e-05);
	EXPECT_FLOAT_EQ(rotation[2], 8.93856632e-05);
}

TEST(MlTransformTest, Factor) {
    // This test is named "Factor", and belongs to the "MlTransformTest"
    // test case.

	MlTransform t = MlTransform::identity();

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
