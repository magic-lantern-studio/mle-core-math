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
 * 2D vector used to represent points or directions.  Each component of
 * the vector is a single-precision floating-point value.
 * 
 * @author Mark S. Millard
 */
public class MlVector2
{
    // The internal vector representation.
    public float[] m_vector = new float[2];
    
    /**
     * The default constructor. All elements in the vector are
     * initialized to zero (0.0f).
     */
    public MlVector2()
    {
        super();
        m_vector[0] = 0;
        m_vector[1] = 0;
    }
    
    /**
     * A constructor given an array of 2 components
     * to initialize from.
     * 
     * @param v The array of components to initialize.
     */
    public MlVector2(float[] v)
    {
        m_vector[0] = v[0];
        m_vector[1] = v[1];
    }
    
    /**
     * A constructor given 2 individual components
     * to initialize from.
     * 
     * @param x The x element.
     * @param y The y element.
     */
    public MlVector2(float x, float y)
    {
        m_vector[0] = x;
        m_vector[1] = y;
    }
    
    /**
     * A constructor given another vector to
     * initialize from.
     * 
     * @param v The other vector.
     */
    public MlVector2(MlVector2 v)
    {
        m_vector[0] = v.m_vector[0];
        m_vector[1] = v.m_vector[1];
    }
    
    /**
     * Determine if the vector is set to [0 0 0 0].
     * 
     * @return Returns <b>true</b> if all elements are zero.
     * Otherwise, returns <b>false</b>.
     */
    public final boolean isZero()
    {
        return ((m_vector[0] == 0) &&
                (m_vector[1] == 0));
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
    public final float dot(MlVector2 v)
    {
        return ((m_vector[0] * v.m_vector[0]) +
                (m_vector[1] * v.m_vector[1]));
    }

    /**
     * Get the value of the vector.
     * 
     * @param v Returns an array of 2 components.
     */
    public final void getValue(float[] v)
    {
        v[0] = m_vector[0];
        v[1] = m_vector[1];
    }

    /**
     * Set the value of the vector.
     * 
     * @param v An array of 2 components.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlVector2 setValue(float v[])
    {
        m_vector[0] = v[0];
        m_vector[1] = v[1];
        
        return this;
    }
    
    /**
     * Set the value of the vector.
     * 
     * @param v The vector to copy from.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlVector2 setValue(MlVector2 v)
    {
        m_vector[0] = v.m_vector[0];
        m_vector[1] = v.m_vector[1];
        
        return this;
    }

    /**
     * Sets value of vector from 2 individual components.
     * 
     * @param x The x element to set.
     * @param y The y element to set.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlVector2 setValue (float x, float y)
    {
        m_vector[0] = x;
        m_vector[1] = y;
        
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
            (m_vector[1] * m_vector[1]));
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
        } else 
            setValue(MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ZERO);

        return len;
    }
    
	/**
	 * Returns the real portion of the vector by dividing the first three
	 * values by the fourth.
	 * 
	 * @param v The vector result.
	 */
    public final void getReal(MlVector3 v)
    {
        v.m_vector[0] = (m_vector[0] / m_vector[3]);
        v.m_vector[1] = (m_vector[1] / m_vector[3]);
        v.m_vector[2] = (m_vector[2] / m_vector[3]);
    }
    
    /**
     * Negates each component of vector in place.
     */ 
    public final void negate()
    {
        m_vector[0] = -m_vector[0];
        m_vector[1] = -m_vector[1];
    }
    
    /**
     * Nondestructive unary negation.
     * 
     * @return A new vector is returned.
     */
    public final MlVector2 unaryNegate()
    {
        return new MlVector2(-m_vector[0], -m_vector[1]);
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
        calcScale(m_vector, 2, scale, recipScale);
    }

    /**
     * Determine if the passed vector <b>v</b> is equal to <b>this</b>.
     * 
     * @param v The vector to test against.
     * 
     * @return <b>true</b> is returned if the vectors are equal.
     * <b>false</b> is returned if the vectors are not equal.
     */
    public final boolean equals(MlVector2 v)
    {
        return ((m_vector[0] == v.m_vector[0]) &&
                (m_vector[1] == v.m_vector[1]));
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
    public final boolean equals(MlVector2 v, float tolerance)
    {
        MlVector2 diff =  new MlVector2(m_vector[0] - v.m_vector[0],
                m_vector[1] - v.m_vector[1]);

        return diff.dot(diff) <= tolerance;
    }

    /**
     * Component-wise scalar multiplication.
     * 
     * @param d The scalar value to multiply by.
     * 
     * @return <b>this</b> vector is returned.
     */
    public final MlVector2 mul(float d)
    {
        m_vector[0] = m_vector[0] * d;
        m_vector[1] = m_vector[1] * d;

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
    public final MlVector2 mul(MlVector2 v, float d)
    {
        return new MlVector2((v.m_vector[0] * d),
        	(v.m_vector[1] * d));
    }
    
    /**
     * Component-wise scalar division.
     * 
     * @param d The scalar value to divide by.
     * 
     * @return <b>this</b> vector is returned.
     */
    public final MlVector2 div(float d)
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
    public final MlVector2 add(MlVector2 v)
    {
        m_vector[0] += v.m_vector[0];
        m_vector[1] += v.m_vector[1];

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
    public final MlVector2 add(MlVector2 v1, MlVector2 v2)
    {
        return new MlVector2(v1.m_vector[0] + v2.m_vector[0],
        	v1.m_vector[1] + v2.m_vector[1]);
    }
    
    /**
     * Component-wise vector subtraction.
     * 
     * @param v The vector to subtract.
     * 
     * @return A new vector containing the result is returned.
     */
    public final MlVector2 sub(MlVector2 v)
    {
        m_vector[0] -= v.m_vector[0];
        m_vector[1] -= v.m_vector[1];

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
    public final MlVector2 sub(MlVector2 v1, MlVector2 v2)
    {
        return new MlVector2(v1.m_vector[0] - v2.m_vector[0],
            v1.m_vector[1] - v2.m_vector[1]);
    }

}
