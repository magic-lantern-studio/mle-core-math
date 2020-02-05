/*
 * MlAngle.java
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
 * Utility class to help process angles.
 * 
 * @author Mark S. Millard
 */
public class MlAngle
{
    /** The angle: 0. */
    public static final float ML_ANGLE_ZERO      = 0f;
    /** The angle: 2 * PI. */
    public static final float ML_ANGLE_TWO_PI    = 1f;
    /** The angle: PI. */
    public static final float ML_ANGLE_PI        = 0.5f;
    /** The angle: PI / 2. */
    public static final float ML_ANGLE_PI_HALF   = 0.25f;
    /** The angle: PI / 4. */
    public static final float ML_ANGLE_PI_FOURTH = 0.125f;

    // Functions for doing conversions to angles, which use 2PI == 0x10000
    // in fixed and regular floating point values in float mode.
    
    /**
     * Convert angle to degrees.
     * 
     * @param a The angle to convert.
     * 
     * @return The corresponding angle is returned, in degrees.
     */
    public final static float angleToDegrees(float a) 
	{
        return (360 * a); 
	}

    /**
     * Convert angle to radians.
     * 
     * @param a The angle to convert.
     * 
     * @return The corresponding angle is returned, in radians.
     */
	public final static float angleToRadians(float a) 
	{
	    return (MlScalar.ML_SCALAR_TWO_PI * a); 
	}

    /**
     * Convert degrees to angle.
     * 
     * @param s The degrees to convert.
     * 
     * @return The corresponding angle is returned.
     */
	public final static float degreesToAngle(float s) 
	{
	    // Divide by 360 as 1.42/512.
        return (s * (float)2.77777777777777777e-3); 
	}

    /**
     * Convert radians to angle.
     * 
     * @param s The radians to convert.
     * 
     * @return The corresponding angle is returned.
     */
	public static final float radiansToAngle(float s) 
	{
	    // Divide by 2PI as 1/2PI = 5.09/32
	    return (s * 0.15915494309189533619f);
	}

    // Hide default constructor.
    private MlAngle() {}

}
