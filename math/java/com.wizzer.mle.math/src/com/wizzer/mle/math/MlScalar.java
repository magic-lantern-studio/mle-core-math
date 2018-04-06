/*
 * MlScalar.java
 * Created on Dec 1, 2004
 */

// COPYRIGHT_BEGIN
//
//  Copyright (C) 2000-2007  Wizzer Works
//
//  Wizzer Works makes available all content in this file ("Content").
//  Unless otherwise indicated below, the Content is provided to you
//  under the terms and conditions of the Common Public License Version 1.0
//  ("CPL"). A copy of the CPL is available at
//
//      http://opensource.org/licenses/cpl1.0.php
//
//  For purposes of the CPL, "Program" will mean the Content.
//
//  For information concerning this Makefile, contact Mark S. Millard,
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
