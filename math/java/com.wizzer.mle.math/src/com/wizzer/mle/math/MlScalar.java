/*
 * MlScalar.java
 * Created on Dec 1, 2004
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2000-2020 Wizzer Works
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

// Declare package.
package com.wizzer.mle.math;

/**
 * This class is a convenience class for specifying scalar values.
 * 
 * @author Mark S. Millard
 */
public class MlScalar
{
    /** The scalar value: 2f. */
    public static final float ML_SCALAR_TWO       = 2.0f;
    /** The scalar value: 1f. */
    public static final float ML_SCALAR_ONE       = 1.0f;
    /** The scalar value: 0.5f. */
    public static final float ML_SCALAR_HALF      = 0.5f;
    /** The scalar value 0f. */
    public static final float ML_SCALAR_ZERO      = 0.0f;
    /** The scalar value: 2 * PI. */
    public static final float ML_SCALAR_TWO_PI    = 6.2831853071795864f;
    /** The scalar value: PI. */
    public static final float ML_SCALAR_PI        = 3.14159265358979323f;
    /** The scalar value: PI / 2. */
    public static final float ML_SCALAR_PI_HALF   = 1.57079632679489661923f;
    /** The scalar value: PI / 4. */
    public static final float ML_SCALAR_PI_FOURTH = 0.7853981633974483075f;
    /** The scalar value: epsilon. */
    public static final float ML_SCALAR_EPSILON   = (float)1.0e-7;
    /** The maximum scalar value. */
    public static final float ML_SCALAR_MAX       = (float)1.0e+38;

    // Hide default constructor.
    private MlScalar() {}

}
