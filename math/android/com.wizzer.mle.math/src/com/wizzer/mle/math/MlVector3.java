/*
 * MlVector3.java
 * Created on Dec 6, 2004
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
 * 3D vector used to represent points or directions.  Each component of
 * the vector is a single-precision floating-point value.
 * 
 * @author Mark S. Millard
 */
public class MlVector3
{
    // The internal vector representation.
    public float[] m_vector = new float[3];
    
    /**
     * The default constructor. All elements in the vector are
     * initialized to zero (0.0f).
     */
    public MlVector3()
    {
        super();
        m_vector[0] = 0;
        m_vector[1] = 0;
        m_vector[2] = 0;
    }
    
    /**
     * A constructor given an array of 3 components
     * to initialize from.
     * 
     * @param v The array of components to initialize.
     */
    public MlVector3(float[] v)
    {
        m_vector[0] = v[0];
        m_vector[1] = v[1];
        m_vector[2] = v[2];
    }
    
    /**
     * A constructor given 3 individual components
     * to initialize from.
     * 
     * @param x The x element.
     * @param y The y element.
     * @param z The z element.
     */
    public MlVector3(float x, float y, float z)
    {
        m_vector[0] = x;
        m_vector[1] = y;
        m_vector[2] = z;
    }
    
    /**
     * A constructor given another vector to
     * initialize from.
     * 
     * @param v The other vector.
     */
    public MlVector3(MlVector3 v)
    {
        m_vector[0] = v.m_vector[0];
        m_vector[1] = v.m_vector[1];
        m_vector[2] = v.m_vector[2];
    }
    
    /**
     * Determine if the vector is set to [0 0 0].
     * 
     * @return Returns <b>true</b> if all elements are zero.
     * Otherwise, returns <b>false</b>.
     */
    public final boolean isZero()
    {
        return ((m_vector[0] == 0) &&
                (m_vector[1] == 0) &&
                (m_vector[2] == 0));
    }
    
    /**
     * Calculate the cross-product of this vector and the passed
     * argument <b>v</b>.
     * 
     * @param v The other vector.
     * 
     * @return Returns the right-handed cross product of this vector
     * and another vector, v.
     */
    public final MlVector3 cross(MlVector3 v)
    {
        MlVector3 result = new MlVector3(
        	(m_vector[1] * v.m_vector[2]) - (m_vector[2] * v.m_vector[1]),
            (m_vector[2] * v.m_vector[0]) - (m_vector[0] * v.m_vector[2]),
        	(m_vector[0] * v.m_vector[1]) - (m_vector[1] * v.m_vector[0]));
        return result;
    }
    
    /**
     * Calculate the dot-product of this vector and the passed
     * argument <b>v</b>.
     * 
     * @param v The other vector.
     * 
     * @return Returns the dot (inner) product of this vector
     * and another vector, v.
     */
    public final float dot(MlVector3 v)
    {
        return ((m_vector[0] * v.m_vector[0]) +
                (m_vector[1] * v.m_vector[1]) +
                (m_vector[2] * v.m_vector[2]));
    }

    /**
     * Get the value of the vector.
     * 
     * @param v Returns an array of 3 components.
     */
    public final void getValue(float[] v)
    {
        v[0] = m_vector[0];
        v[1] = m_vector[1];
        v[2] = m_vector[2];
    }

    /**
     * Set the value of the vector.
     * 
     * @param v An array of 3 components.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlVector3 setValue(float v[])
    {
        m_vector[0] = v[0];
        m_vector[1] = v[1];
        m_vector[2] = v[2];
        
        return this;
    }
    
    /**
     * Set the value of the vector.
     * 
     * @param v The vector to copy from.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlVector3 setValue(MlVector3 v)
    {
        m_vector[0] = v.m_vector[0];
        m_vector[1] = v.m_vector[1];
        m_vector[2] = v.m_vector[2];
        
        return this;
    }

    /**
     * Sets value of vector from 3 individual components.
     * 
     * @param x The x element to set.
     * @param y The y element to set.
     * @param z The z element to set.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlVector3 setValue (float x, float y, float z)
    {
        m_vector[0] = x;
        m_vector[1] = y;
        m_vector[2] = z;
        
        return this;
    }

    /**
     * Sets value of vector to be convex combination of 3 other
     * vectors, using barycentic coordinates.
     * 
     * @param barycentic Barycentic coordinate vector.
     * @param v0 The first vector.
     * @param v1 The second vector.
     * @param v2 The third vector.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlVector3 setValue(MlVector3 barycentic,
		MlVector3 v0, MlVector3 v1, MlVector3 v2)
    {
        m_vector[0] = (v0.m_vector[0] * barycentic.m_vector[0]) +
                      (v1.m_vector[0] * barycentic.m_vector[1]) +
                      (v2.m_vector[0] * barycentic.m_vector[2]);
        m_vector[1] = (v0.m_vector[1] * barycentic.m_vector[0]) +
                      (v1.m_vector[1] * barycentic.m_vector[1]) +
                      (v2.m_vector[1] * barycentic.m_vector[2]);
        m_vector[2] = (v0.m_vector[2] * barycentic.m_vector[0]) +
                      (v1.m_vector[2] * barycentic.m_vector[1]) +
                      (v2.m_vector[2] * barycentic.m_vector[2]);
        
        return this;
    }

    /**
     * Get the length of the vector.
     * 
     * @return Returns geometric length of vector.
     */
    public final float length()
    {
        return (float)Math.sqrt(
            (m_vector[0] * m_vector[0]) +
            (m_vector[1] * m_vector[1]) +
            (m_vector[2] * m_vector[2]));
    }
    
    /**
     * Returns approximate length of vector (+/- 7%).
     * <p>
	 * Fast approximation to the length of a vector.  3-D Euclidean distance
	 * approximation: c1 = 15/16 , c2 = c3 = 3/8 and max(e) = 7.7 %.  Based on
	 * <i>"Fast Linear Approximations of Euclidean Distance in Higher Dimensions"</i>
	 * by Yoshikazu Ohashi, yoshi@cognex.com in "Graphics Gems IV", Academic
	 * Press, 1994.
	 * </p>
	 * 
	 * @return The length is returned.
	 */
    public final float approximateLength()
    {
        float a = m_vector[0];
        float b = m_vector[1];
        float c = m_vector[2];

        // Set a, b, and c to absolute values of x, y, and z coordinates.
        a = Math.abs(a);
        b = Math.abs(b);
        c = Math.abs(c);

        // Test and swap so that a is the largest coordinate.
        if ( a < b ) {float x = a;  a = b;  b = x;}
        if ( a < c ) {float x = a;  a = c;  c = x;}

        return ((a * (0.9375f)) + ((b + c) * (0.375f)));        
    }
    
    /**
     * Normalize the vector.
     * <p>
     * Changes vector to be unit length.
     * </p>
     * 
     * @return The original length is returned.
     */
    public final float normalize()
    {
        if (isZero())
        {
            return MlScalar.ML_SCALAR_ZERO;
        }
        
        float len = length();

        if (len != MlScalar.ML_SCALAR_ZERO)
        {
            m_vector[0] = m_vector[0] * (1/ len);
            m_vector[1] = m_vector[1] * (1/ len);
            m_vector[2] = m_vector[2] * (1/ len);
        } else 
            setValue(MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ZERO);

        return len;
    }
    
    /**
     * Normalize the vector.
     * <p>
     * Changes vector to be approximately unit length.
     * </p>
     * 
     * @return The original length is returned.
     */
    public final float approximateNormalize()
    {
        float length = this.approximateLength();
        if (length != MlScalar.ML_SCALAR_ZERO)
        {
            m_vector[0] = m_vector[0] / length;
            m_vector[1] = m_vector[1] / length;
            m_vector[2] = m_vector[2] / length;            
        }
        return length;

    }
    
    /**
     * Negates each component of vector in place.
     */ 
    public final void negate()
    {
        m_vector[0] = -m_vector[0];
        m_vector[1] = -m_vector[1];
        m_vector[2] = -m_vector[2];
    }
    
    /**
     * Nondestructive unary negation.
     * 
     * @return A new vector is returned.
     */
    public final MlVector3 unaryNegate()
    {
        return new MlVector3(-m_vector[0], -m_vector[1], -m_vector[2]);
    }

    /**
     * Changes vector to have length of input scale factor.
     * 
     * @param newScale The new scale to use.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlVector3 scaleTo(float newScale)
    {
        float oldScale = length();

        if (oldScale != MlScalar.ML_SCALAR_ZERO)
        {
            oldScale = (newScale / oldScale);
            m_vector[0] = m_vector[0] * oldScale;
            m_vector[1] = m_vector[1] * oldScale;
            m_vector[2] = m_vector[2] * oldScale;            
        }
        
        return this;
    }
    
    // Calculate the scale.
    private static void calcScale( 
    	float[] v, int numElements, 
        float[] scale, float[] recipScale)
    {
        // Don't touch the vector.

        scale[0] = MlScalar.ML_SCALAR_ONE;
        recipScale[0] = MlScalar.ML_SCALAR_ONE;

        return;
    }
    
    /**
     * Finds the scale factor to put max value between 1 and TBD.
     * 
     * @param scale The retrieved scale, an array of length 1.
     * @param recipScale The reciprocal of the retrieved scale, an arary of length 1.
     */
    public final void getScale(float[] scale, float[] recipScale)
    {
        calcScale(m_vector, 3, scale, recipScale);
    }
 
    /**
     * Linear interpolation, aka lerp.  Set "result" to the interpolation
     * by "weight" from "v0" (when weight=0) to "v1" (when weight=1).
     * 
     * @param weight The factor.
     * @param v0 The first vector.
     * @param v1 The second vector.
     * @param result The result of the interpolation.
     */
    static public final void interpolate (float weight,
		MlVector3 v0, MlVector3 v1, MlVector3 result)
    {
        result.m_vector[0] = (v0.m_vector[0] * (MlScalar.ML_SCALAR_ONE - weight)) +
        	(v1.m_vector[0] * weight) ;
        result.m_vector[1] = (v0.m_vector[1] * (MlScalar.ML_SCALAR_ONE - weight)) +
    		(v1.m_vector[1] * weight) ;
        result.m_vector[2] = (v0.m_vector[2] * (MlScalar.ML_SCALAR_ONE - weight)) +
    		(v1.m_vector[2] * weight) ;
    }

    /**
     * Determine if the passed vector <b>v</b> is equal to <b>this</b>.
     * 
     * @param v The vector to test against.
     * 
     * @return <b>true</b> is returned if the vectors are equal.
     * <b>false</b> is returned if the vectors are not equal.
     */
    public final boolean equals(MlVector3 v)
    {
        return ((m_vector[0] == v.m_vector[0]) &&
                (m_vector[1] == v.m_vector[1]) &&
                (m_vector[2] == v.m_vector[2]));
    }
    
    /**
     * Equality comparison within given tolerance - the square of the
     * length of the maximum distance between the two vectors.
     * 
     * @param v The vector to test against.
     * @param tolerance The specified tolerance.
     * 
     * @return <b>true</b> is returned if the vectors are equal.
     * <b>false</b> is returned if the vectors are not equal.
     */
    public final boolean equals(MlVector3 v, float tolerance)
    {
        MlVector3 diff =  new MlVector3(m_vector[0] - v.m_vector[0],
                m_vector[1] - v.m_vector[1], m_vector[2] - v.m_vector[2]);

        return diff.dot(diff) <= tolerance;
    }
    
    /**
     * Returns principal axis that is closest (based on maximum dot
     * product) to this vector.
     * 
     * @return The principal axis is returned as a vector.
     */
    public final MlVector3 getClosestAxis()
    {
        MlVector3 axis = new MlVector3(MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ZERO);
        MlVector3 bestAxis = new MlVector3();
        float d, max = -21.234f;

        axis.m_vector[0] = MlScalar.ML_SCALAR_ONE;     // +x axis
        if ((d = dot(axis)) > max) { max = d; bestAxis = axis; }

        axis.m_vector[0] = -MlScalar.ML_SCALAR_ONE;    // -x axis
        if ((d = dot(axis)) > max) { max = d; bestAxis = axis; }
        axis.m_vector[0] = MlScalar.ML_SCALAR_ZERO;

        axis.m_vector[1] = MlScalar.ML_SCALAR_ONE;     // +y axis
        if ((d = dot(axis)) > max) { max = d; bestAxis = axis; }

        axis.m_vector[1] = -MlScalar.ML_SCALAR_ONE;    // -y axis
        if ((d = dot(axis)) > max) { max = d; bestAxis = axis; }
        axis.m_vector[1] = MlScalar.ML_SCALAR_ZERO;

        axis.m_vector[2] = MlScalar.ML_SCALAR_ONE;     // +z axis
        if ((d = dot(axis)) > max) { max = d; bestAxis = axis; }

        axis.m_vector[2] = -MlScalar.ML_SCALAR_ONE;    // -z axis
        if ((d = dot(axis)) > max) { max = d; bestAxis = axis; }

        return bestAxis;
    }

    /**
     * Component-wise scalar multiplication.
     * 
     * @param d The scalar value to multiply by.
     * 
     * @return <b>this</b> vector is returned.
     */
    public final MlVector3 mul(float d)
    {
        m_vector[0] = m_vector[0] * d;
        m_vector[1] = m_vector[1] * d;
        m_vector[2] = m_vector[2] * d;

        return this;
    }

    /**
     * Component-wise binary scalar multiplication.
     * 
     * @param v The vector to multiply.
     * @param d The scalar value to multiply by.
     * 
     * @return A new vector containing the result is returned.
     */
    public final MlVector3 mul(MlVector3 v, float d)
    {
        return new MlVector3((v.m_vector[0] * d),
        	(v.m_vector[1] * d), (v.m_vector[2] * d));
    }
    
    /**
     * Component-wise scalar division.
     * 
     * @param d The scalar value to divide by.
     * 
     * @return <b>this</b> vector is returned.
     */
    public final MlVector3 div(float d)
    {
        mul(1/d);
        
        return this;
    }
    
    /**
     * Component-wise vector addition.
     * 
     * @param v The vector to add.
     * 
     * @return A new vector containing the result is returned.
     */
    public final MlVector3 add(MlVector3 v)
    {
        m_vector[0] += v.m_vector[0];
        m_vector[1] += v.m_vector[1];
        m_vector[2] += v.m_vector[2];

        return this;
    }

    /**
     * Component-wise binary vector addition.
     * 
     * @param v1 The first vector.
     * @param v2 The second vector.
     * 
     * @return A new vector containing the result is returned.
     */
    public final MlVector3 add(MlVector3 v1, MlVector3 v2)
    {
        return new MlVector3(v1.m_vector[0] + v2.m_vector[0],
        	v1.m_vector[1] + v2.m_vector[1],
        	v1.m_vector[2] + v2.m_vector[2]);
    }
    
    /**
     * Component-wise vector subtraction.
     * 
     * @param v The vector to subtract.
     * 
     * @return A new vector containing the result is returned.
     */
    public final MlVector3 sub(MlVector3 v)
    {
        m_vector[0] -= v.m_vector[0];
        m_vector[1] -= v.m_vector[1];
        m_vector[2] -= v.m_vector[2];

        return this;
    }
    
    /**
     * Component-wise binary vector subtraction.
     * 
     * @param v1 The first vector.
     * @param v2 The second vector.
     * 
     * @return A new vector containing the result is returned.
     */
    public final MlVector3 sub(MlVector3 v1, MlVector3 v2)
    {
        return new MlVector3(v1.m_vector[0] - v2.m_vector[0],
            v1.m_vector[1] - v2.m_vector[1],
            v1.m_vector[2] - v2.m_vector[2]);
    }

}
