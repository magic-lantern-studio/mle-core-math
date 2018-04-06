/*
 * MlRotation.java
 * Created on Dec 3, 2004
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
 * This class specifies a rotation, used to define the orientation of a 3d object.
 * 
 * @author Mark S. Millard
 */
public class MlRotation
{
    // The internal quaternion representation.
    public float[] m_quat = new float[4];
    
    /**
     * The default constructor. The quaternion is created as an
     * identity or null rotation.
     */
    public MlRotation()
    {
        super();
        setValue(0,0,0,1);
    }
    
    /**
     * A constructor given 4 individual components of a quaternion.
     * 
     * @param q1 The first component.
     * @param q2 The second component.
     * @param q3 The third component.
     * @param q4 The fourth component.
     */
    public MlRotation(float q1, float q2, float q3, float q4)
    {
        super();
        setValue(q1,q2,q3,q4);        
    }
    
    /**
     * A constructor given a quaternion as an array of 4 components.
     * 
     * @param v The array of components.
     */
    public MlRotation(float[] v)
    {
        super();
        setValue(v);               
    }
    
    /**
     * A constructor given a rotation matrix.
     * 
     * @param q The rotation matrix.
     */
    public MlRotation(MlTransform q)
    {
        super();
        setValue(q);        
    }

    /**
     * Create a null rotation.
     * 
     * @return An identity quaternion is returned.
     */
    public final static MlRotation identity()
	{
        return new MlRotation(
            MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ZERO,
            MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ONE);
    }

    /**
     * Returns 4 individual components of a rotation quaternion.
     * 
     * @param v The array the components will be returned in.
     */
    public final void getValue(float[] v)
    {
        v[0] = m_quat[0];
        v[1] = m_quat[1];
        v[2] = m_quat[2];
        v[3] = m_quat[3];
    }
    
    /**
     * Returns corresponding 3D rotation axis vector and angle in radians.
     * 
     * @param axis The rotation axis vector.
     * @param radians The angle, in radians.
     */
    public final void getValue(MlVector3 axis, float[] radians)
    {
        float len;
        MlVector3 q = new MlVector3();

        q.m_vector[0] = m_quat[0];
        q.m_vector[1] = m_quat[1];
        q.m_vector[2] = m_quat[2];

        if ((len = q.length()) > 0.00001f)
        {
            axis = q.mul(1 / len);
            radians[0] = MlAngle.angleToRadians(2 * (float)Math.acos(m_quat[3]));
        } else
        {
            axis.setValue(MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ONE);
            radians[0] = MlScalar.ML_SCALAR_ZERO;
        }
    }
    
    /**
     * Returns corresponding 4x3 rotation matrix.
     * 
     * @param matrix The rotation matrix that is returned
     */
    public final void getValue(MlTransform matrix)
    {
        MlTransform m = new MlTransform();

        m.m_matrix[0][0] = MlScalar.ML_SCALAR_ONE - 2 * ((m_quat[1] * m_quat[1]) + (m_quat[2] * m_quat[2]));
        m.m_matrix[0][1] = 2 * ((m_quat[0] * m_quat[1]) + (m_quat[2] * m_quat[3]));
        m.m_matrix[0][2] = 2 * ((m_quat[2] * m_quat[0]) - (m_quat[1] * m_quat[3]));

        m.m_matrix[1][0] = 2 * ((m_quat[0] * m_quat[1]) - (m_quat[2] * m_quat[3]));
        m.m_matrix[1][1] = MlScalar.ML_SCALAR_ONE - 2 * ((m_quat[2] * m_quat[2]) + (m_quat[0] * m_quat[0]));
        m.m_matrix[1][2] = 2 * ((m_quat[1] * m_quat[2]) + (m_quat[0] * m_quat[3]));

        m.m_matrix[2][0] = 2 * ((m_quat[2] * m_quat[0]) + (m_quat[1] * m_quat[3]));
        m.m_matrix[2][1] = 2 * ((m_quat[1] * m_quat[2]) - (m_quat[0] * m_quat[3]));
        m.m_matrix[2][2] = MlScalar.ML_SCALAR_ONE - 2 * ((m_quat[1] * m_quat[1]) + (m_quat[0] * m_quat[0]));

        m.m_matrix[3][0] = MlScalar.ML_SCALAR_ZERO;
        m.m_matrix[3][1] = MlScalar.ML_SCALAR_ZERO;
        m.m_matrix[3][2] = MlScalar.ML_SCALAR_ZERO;

        matrix = m;
    }
    
	/**
	 * Sets the value of the rotation from 4 individual components of a
	 * quaternion.
	 * 
	 * @param q1 The first component.
	 * @param q2 The second component.
	 * @param q3 The third component.
	 * @param q4 The fourth component.
	 * 
	 * @return <b>this</b> is returned.
	 */
    public final MlRotation setValue(float q1, float q2, float q3, float q4)
    {
	    m_quat[0] = q1;
	    m_quat[1] = q2;
	    m_quat[2] = q3;
	    m_quat[3] = q4;
	    
	    normalize();
	    
	    return this;        
    }

	/**
	 * Sets the value of the rotation from array of 4 components of a
	 * quaternion.
	 * 
	 * @param q The array of components to set.
	 * 
	 * @return <b>this</b> is returned.
	 */
	public final MlRotation setValue(float[] q)
    {
	    m_quat[0] = q[0];
	    m_quat[1] = q[1];
	    m_quat[2] = q[2];
	    m_quat[3] = q[3];
	    
	    normalize();
	    
	    return this;
    }
	
	/**
	 * Sets the value of the rotation from a transform matrix.
	 * 
	 * @param m The transform matrix to set,
	 * 
	 * @return <b>this</b> is returned.
	 */
	public final MlRotation setValue(MlTransform m)
	{
	    int i, j, k;

	    // First, find largest diagonal in matrix:
	    if (m.isZero())
	    {
	        m_quat[3] = MlScalar.ML_SCALAR_ONE;
	        m_quat[0] = MlScalar.ML_SCALAR_ZERO;
	        m_quat[1] = MlScalar.ML_SCALAR_ZERO;
	        m_quat[2] = MlScalar.ML_SCALAR_ZERO;

	        return this;
	    }

	    if (m.m_matrix[0][0] > m.m_matrix[1][1])
	    { 
	        if (m.m_matrix[0][0] > m.m_matrix[2][2])
	            i = 0;
	        else i = 2;
	    } else
	    {
	        if (m.m_matrix[1][1] > m.m_matrix[2][2]) 
	            i = 1;
	        else i = 2;
	    }

	    if (m.m_matrix[0][0] + m.m_matrix[1][1] + m.m_matrix[2][2] > m.m_matrix[i][i]) 
	    {
	        // Compute w first:
	        m_quat[3] = ((float)Math.sqrt(m.m_matrix[0][0] + m.m_matrix[1][1] +
	        	m.m_matrix[2][2] + MlScalar.ML_SCALAR_ONE) * MlScalar.ML_SCALAR_HALF);

	        // And compute other values:
	        m_quat[0] = ((m.m_matrix[1][2] - m.m_matrix[2][1]) / (4 * m_quat[3]));
	        m_quat[1] = ((m.m_matrix[2][0] - m.m_matrix[0][2]) / (4 * m_quat[3]));
	        m_quat[2] = ((m.m_matrix[0][1] - m.m_matrix[1][0]) / (4 * m_quat[3]));
	    } else
	    {
	        // Compute x, y, or z first:
	        j = (i+1) % 3; k = (i+2) % 3;
	    
	        // Compute first value:
	        m_quat[i] = ((float)Math.sqrt(m.m_matrix[i][i] - m.m_matrix[j][j] -
	        	m.m_matrix[k][k] + MlScalar.ML_SCALAR_ONE) * MlScalar.ML_SCALAR_HALF);
	       
	        // And the others:
	        m_quat[j] = ((m.m_matrix[i][j] + m.m_matrix[j][i]) / (4 * m_quat[i]));
	        m_quat[k] = ((m.m_matrix[i][k] + m.m_matrix[k][i]) / (4 * m_quat[i]));

	        m_quat[3] = ((m.m_matrix[j][k] - m.m_matrix[k][j]) / (4 * m_quat[i]));
	    }
	    
	    return this;
	}
	
    /**
     * Sets the value of the rotation from 3D rotation axis vector and angle in radians.
     * 
     * @param axis The rotation axis vector.
     * @param radians The angle, in radians.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlRotation setValue(MlVector3 axis, float radians)
    {
        MlVector3 q = new MlVector3();

        q.setValue(axis);
        q.normalize();

        q.mul((float)Math.sin(MlAngle.radiansToAngle((radians * MlScalar.ML_SCALAR_HALF))));

        m_quat[0] = q.m_vector[0];
        m_quat[1] = q.m_vector[1];
        m_quat[2] = q.m_vector[2];

        m_quat[3] = (float)Math.cos(MlAngle.radiansToAngle((radians * MlScalar.ML_SCALAR_HALF)));

        return this;
    }

    /**
     * Sets rotation to rotate from one direction vector to another.
     * 
     * @param rotateFrom The vector to rotate from.
     * @param rotateTo The vector to rotate to.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlRotation setValue(MlVector3 rotateFrom, MlVector3 rotateTo)
    {
        MlVector3 from = new MlVector3(rotateFrom);
        MlVector3 to = new MlVector3(rotateTo);
        MlVector3 axis = new MlVector3();
        float  cost;

        from.normalize();
        to.normalize();
        cost = from.dot(to);

        // Check for degeneracies.
        if (cost > 0.99999f)
        {
            // Vectors are parallel.
            m_quat[0] = m_quat[1] = m_quat[2] = MlScalar.ML_SCALAR_ZERO;
            m_quat[3] = MlScalar.ML_SCALAR_ONE;
            
            return this;
        } else if (cost < -0.99999f)
        {
            // Vectors are opposite.

            // Find an axis to rotate around, which should be
            // perpendicular to the original axis.
            //
            // Try cross product with (1,0,0) first, if that's one of our
            // original vectors then try  (0,1,0).
            MlVector3 tmp = from.cross(new MlVector3(MlScalar.ML_SCALAR_ONE, MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ZERO));
            if (tmp.length() < 0.00001f)
                tmp = from.cross(new MlVector3(MlScalar.ML_SCALAR_ZERO, MlScalar.ML_SCALAR_ONE, MlScalar.ML_SCALAR_ZERO));

            tmp.normalize();
            setValue(tmp.m_vector[0], tmp.m_vector[1], tmp.m_vector[2], MlScalar.ML_SCALAR_ZERO);
            
            return this;
        }

        axis = rotateFrom.cross(rotateTo);
        axis.normalize();

        // Use half-angle formulae.
        // sin^2 t = ( 1 - cos (2t) ) / 2
        axis.mul((float)Math.sqrt((MlScalar.ML_SCALAR_HALF * (MlScalar.ML_SCALAR_ONE - cost))));

        // Scale the axis by the sine of half the rotation angle to get
        // the normalized quaternion.
        m_quat[0] = axis.m_vector[0];
        m_quat[1] = axis.m_vector[1];
        m_quat[2] = axis.m_vector[2];

        // cos^2 t = ( 1 + cos (2t) ) / 2
        // w part is cosine of half the rotation angle.
        m_quat[3] = (float)Math.sqrt((MlScalar.ML_SCALAR_HALF * (MlScalar.ML_SCALAR_ONE + cost)));

        return this;   
    }

	/* 
	 * Calculate the norm of the rotation vector.
	 * 
	 * @return Returns the norm (square of the 4D length) of the quaternion
	 * defining the rotation.
	 */
	private float norm()
	{
	    return ((m_quat[0] * m_quat[0]) +
	            (m_quat[1] * m_quat[1]) +
	            (m_quat[2] * m_quat[2]) +
	            (m_quat[3] * m_quat[3]));
	}
	
	/*
	 * Normalizes a rotation quaternion to unit 4D length.
	 */
	private void normalize()
	{
	    float dist = 1 / (float)Math.sqrt(norm());

	    m_quat[0] = m_quat[0] * dist;
	    m_quat[1] = m_quat[1] * dist;
	    m_quat[2] = m_quat[2] * dist;
	    m_quat[3] = m_quat[3] * dist;
	}
	
    /**
     * Changes a rotation to be its inverse.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlRotation invert()
    {
        float invNorm = (1 / norm());

        m_quat[0] = -(m_quat[0] * invNorm);
        m_quat[1] = -(m_quat[1] * invNorm);
        m_quat[2] = -(m_quat[2] * invNorm);
        m_quat[3] =  (m_quat[3] * invNorm);

        return this;
    }

    /**
     * Calculates the inverse of a rotation.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlRotation inverse()
	{
        MlRotation q = this;
        return q.invert();
    }

    /**
     * Multiplies this rotation by another rotation;
     * results in product of rotations.
     * 
     * @param q The rotation to multiply with.
     * 
     * @return <b>this</b> is returned.
     */
    public final MlRotation mul(MlRotation q)
    {
        float p0, p1, p2, p3;

        p0 = ((q.m_quat[3] * m_quat[0]) + (q.m_quat[0] * m_quat[3]) +
              (q.m_quat[1] * m_quat[2]) - (q.m_quat[2] * m_quat[1]));
        p1 = ((q.m_quat[3] * m_quat[1]) + (q.m_quat[1] * m_quat[3]) +
              (q.m_quat[2] * m_quat[0]) - (q.m_quat[0] * m_quat[2]));
        p2 = ((q.m_quat[3] * m_quat[2]) + (q.m_quat[2] * m_quat[3]) +
              (q.m_quat[0] * m_quat[1]) - (q.m_quat[1] * m_quat[0]));
        p3 = ((q.m_quat[3] * m_quat[3]) - (q.m_quat[0] * m_quat[0]) -
              (q.m_quat[1] * m_quat[1]) - (q.m_quat[2] * m_quat[2]));
        m_quat[0] = p0;
        m_quat[1] = p1;
        m_quat[2] = p2;
        m_quat[3] = p3;

        normalize();

        return this;
    }
    
    /**
     * The binary multiplication of two rotations.
     * 
     * @param q1 The first rotation.
     * @param q2 The second rotation.
     * 
     * @return A new rotation is created and returned.
     */
    public final MlRotation mul(MlRotation q1, MlRotation q2)
    {
        MlRotation q = new MlRotation
        	((q2.m_quat[3] * q1.m_quat[0]) + (q2.m_quat[0] * q1.m_quat[3]) +
             (q2.m_quat[1] * q1.m_quat[2]) - (q2.m_quat[2] * q1.m_quat[1]),

             (q2.m_quat[3] * q1.m_quat[1]) + (q2.m_quat[1] * q1.m_quat[3]) +
             (q2.m_quat[2] * q1.m_quat[0]) - (q2.m_quat[0] * q1.m_quat[2]),

             (q2.m_quat[3] * q1.m_quat[2]) + (q2.m_quat[2] * q1.m_quat[3]) +
             (q2.m_quat[0] * q1.m_quat[1]) - (q2.m_quat[1] * q1.m_quat[0]),

             (q2.m_quat[3] * q1.m_quat[3]) - (q2.m_quat[0] * q1.m_quat[0]) -
             (q2.m_quat[1] * q1.m_quat[1]) - (q2.m_quat[2] * q1.m_quat[2]));

        q.normalize();

        return (q);
    }
    
	/**
	 * Puts the given vector through this rotation.
     * Multiplies the given vector by the matrix of this rotation.
     * 
     * @param src The source vector.
     * @param dst The result of the rotation.
     */
    public final void multVec(MlVector3 src, MlVector3 dst)
    {
        MlTransform myMat = new MlTransform();
        getValue(myMat);

        myMat.mulVecMatrix(src, dst);
    }
    
	/**
	 * Scale the angle of rotation.
	 * <p>
	 * Keep the axis the same. Multiply the angle of rotation by
	 * the amount <b>scaleFactor</b>.
	 * </p>
	 * 
	 * @param scaleFactor The amount to scale by.
	 */
    public final void scaleAngle(float scaleFactor)
    {
        MlVector3 myAxis = new MlVector3();
        float[] myAngle = new float[1];;

        // Get the Axis and angle.
        getValue(myAxis, myAngle);

        setValue(myAxis, (myAngle[0] * scaleFactor));
    }
    
	/**
	 * Spherical linear interpolation: as <b>t</b> goes from 0 to 1, returned
	 * value goes from <b>rot0</b> to <b>rot1</b>.
	 * 
	 * @param rot0 The first rotation.
	 * @param rot1 The second rotation.
	 * @param t The weight.
	 * 
	 * @return A new rotation is returned.
	 */
    public final MlRotation slerp(MlRotation rot0, MlRotation rot1, float t)
    {
        float[] r1q = new float[4];
        rot1.getValue(r1q);

        MlRotation rot = new MlRotation();
        float[] rot1q = new float[4];
        float omega, cosom, sinom;
        float scalerot0, scalerot1;
        int i;

        // Calculate the cosine.
        cosom = (rot0.m_quat[0] * rot1.m_quat[0]) + (rot0.m_quat[1] * rot1.m_quat[1])
                + (rot0.m_quat[2] * rot1.m_quat[2]) + (rot0.m_quat[3] * rot1.m_quat[3]);

        // Adjust signs if necessary.
        if ( cosom < MlScalar.ML_SCALAR_ZERO )
        {
            cosom = -cosom;
            for ( int j = 0; j < 4; j++ )
                rot1q[j] = -r1q[j];
        } else 
        {
            for ( int j = 0; j < 4; j++ )
                rot1q[j] = r1q[j];
        }

        // Calculate interpolating coeffs.
        if ( (MlScalar.ML_SCALAR_ONE - cosom) > 0.00001f )
        {
            // standard case.
            omega = (float)Math.acos(cosom);
            sinom = (float)Math.sin(omega);
            scalerot0 = (float)(Math.sin(((MlScalar.ML_SCALAR_ONE - t) * omega)) / sinom);
            scalerot1 = (float)(Math.sin((t * omega)) / sinom);
        } else
        {        
            // rot0 and rot1 very close - just do linear interp.
            scalerot0 = MlScalar.ML_SCALAR_ONE - t;
            scalerot1 = t;
        }

        // Build the new quarternion.
        for (i = 0; i < 4; i++)
            rot.m_quat[i] = (scalerot0 * rot0.m_quat[i]) + (scalerot1 * rot1q[i]);

        return rot;
    }
    
    /**
     * Equality comparison.
     * 
     * @param q The rotation to test against.
     * 
     * @return <b>true</b> is returned if the rotations are equal.
     * Otherwise, <b>false</b> is returned.
     */
    public final boolean equals(MlRotation q)
    {
	    return (m_quat[0] == q.m_quat[0] &&
	            m_quat[1] == q.m_quat[1] &&
	            m_quat[2] == q.m_quat[2] &&
	            m_quat[3] == q.m_quat[3]);
    }
    
	/**
	 * Equality comparison operator within given tolerance - the square
	 * of the length of the maximum distance between the two vectors.
	 * 
	 * @param q The rotation to test against.
	 * @param tolerance The tolerance.
	 * 
	 * @return <b>true</b> is returned if the rotations are equal within.
     * the specified tolerance. Otherwise, <b>false</b> is returned.
	 */
	public final boolean equals(MlRotation q, float tolerance)
    {
	    return new MlVector4(m_quat).equals(new MlVector4(q.m_quat), tolerance);
    }

}
