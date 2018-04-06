
// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2015 Wizzer Works
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

// include system header files
#include <math.h>
#include <stdio.h>

// include Magic Lantern math header files
#include "math/scalar.h"
#include "math/trig.h"
#include "math/vector.h"
#include "math/rotation.h"
#include "math/transfrm.h"


void MlRotation::getValue(MlScalar& q0, MlScalar& q1, MlScalar& q2, MlScalar& q3) const
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns 4 individual components of rotation quaternion.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    q0 = quat[0];
    q1 = quat[1];
    q2 = quat[2];
    q3 = quat[3];
}


void MlRotation::getValue(MlVector3& axis, MlScalar& radians) const
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns corresponding 3D rotation axis vector and angle in radians.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlScalar  len;
    MlVector3 q;

    q[0] = quat[0];
    q[1] = quat[1];
    q[2] = quat[2];

    if ((len = q.length()) > ML_SCALAR(0.00001f)) {
        axis = q *  mlReciprocal(len);
        radians = mlAngleToRadians(2 * mlAcos(quat[3]));
    }

    else {
        axis.setValue(ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ONE);
        radians = ML_SCALAR_ZERO;
    }
}


void MlRotation::getValue(MlTransform& matrix) const
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns corresponding 4x4 rotation matrix.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlTransform m;

    m[0][0] = ML_SCALAR_ONE - 2 * (mlMul(quat[1], quat[1]) + mlMul(quat[2], quat[2]));
    m[0][1] = 2 * (mlMul(quat[0], quat[1]) + mlMul(quat[2], quat[3]));
    m[0][2] = 2 * (mlMul(quat[2], quat[0]) - mlMul(quat[1], quat[3]));

    m[1][0] = 2 * (mlMul(quat[0], quat[1]) - mlMul(quat[2], quat[3]));
    m[1][1] = ML_SCALAR_ONE - 2 * (mlMul(quat[2], quat[2]) + mlMul(quat[0], quat[0]));
    m[1][2] = 2 * (mlMul(quat[1], quat[2]) + mlMul(quat[0], quat[3]));

    m[2][0] = 2 * (mlMul(quat[2], quat[0]) + mlMul(quat[1], quat[3]));
    m[2][1] = 2 * (mlMul(quat[1], quat[2]) - mlMul(quat[0], quat[3]));
    m[2][2] = ML_SCALAR_ONE - 2 * (mlMul(quat[1], quat[1]) + mlMul(quat[0], quat[0]));

    m[3][0] = ML_SCALAR_ZERO;
    m[3][1] = ML_SCALAR_ZERO;
    m[3][2] = ML_SCALAR_ZERO;

    matrix = m;
}


MlRotation& MlRotation::invert()
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Changes a rotation to be its inverse.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlScalar invNorm = mlReciprocal(norm());

    quat[0] = -mlMul(quat[0], invNorm);
    quat[1] = -mlMul(quat[1], invNorm);
    quat[2] = -mlMul(quat[2], invNorm);
    quat[3] =  mlMul(quat[3], invNorm);

    return* this;
}


MlRotation& MlRotation::setValue(const MlScalar q[4])
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets value of rotation from array of 4 components of a
//    quaternion.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    quat[0] = q[0];
    quat[1] = q[1];
    quat[2] = q[2];
    quat[3] = q[3];
    normalize();

    return (*this);
}


MlRotation& MlRotation::setValue(MlScalar q0, MlScalar q1, MlScalar q2, MlScalar q3)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets value of rotation from 4 individual components of a
//    quaternion.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    quat[0] = q0;
    quat[1] = q1;
    quat[2] = q2;
    quat[3] = q3;
    normalize();

    return (*this);
}


MlRotation& MlRotation::setValue(const MlTransform& m)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets value of rotation from a rotation matrix.
//    This algorithm is from "Quaternions and 4x4 Matrices", Ken
//    Shoemake, Graphics Gems II.
//
//  Here's the logic:
//    We're trying to find a quaterion 'q' that represents the same
//    rotation as the given matrix 'm'.
//    We know how to convert a quaterion to a rotation matrix; the
//    matrix is given by (where x,y,z,w are the quaterion elements):
//
//    x^2-y^2-z^2+w^2  2xy+2zw          2wx - 2yw        0
//    2xy-2zw          y^2-z^2-x^2+w^2  2yz + 2xw        0
//    2zx+2zw          2yz-2xw          z^2-x^2-y^2+w^2  0
//    0                0                0                1
//
//    We know m, we want to find x,y,z,w.  If you don't mind doing
//    square roots, then it is easy; for example:
//    m[0][0]+m[1][1]+m[2][2]+1.0 = 4w^2
//       (write it all out, and see all the terms cancel)
//    Or, w = sqrt(m[0][0]+m[1][1]+m[2][2]+1.0)/2
//    Similarly,
//        x = sqrt(m[0][0]-m[1][1]-m[2][2]+1.0)/2
//        y = sqrt(m[1][1]-m[2][2]-m[0][0]+1.0)/2
//        z = sqrt(m[2][2]-m[0][0]-m[1][1]+1.0)/2
//    However, you only really need to do one sqrt and find one of
//    x,y,z,w, because using the other elements of the matrix you
//    find, for example, that:
//    m[0][1]+m[1][0] = 2xy+2zw+2xy-2zw = 4xy
//    So if you know either x or y, you can find the other.
//
//    That is assuming that the first thing you find isn't zero, of
//    course.  In fact, you want the first element you find to be as
//    large as possible, to get more accuracy in the division.  You
//    can rewrite the diagonal elements as:
//    (w^2 - x^2 - y^2 - z^2) + 2x^2    = m[0][0]
//    (w^2 - x^2 - y^2 - z^2) + 2y^2    = m[1][1]
//    (w^2 - x^2 - y^2 - z^2) + 2z^2    = m[2][2]
//    ... and write the sum of the diagonals as:
//    (w^2 - x^2 - y^2 - z^2) + 2w^2    = m[0][0]+m[1][1]+m[2][2]+1.0
//
//    Why do this?  Because now it is easy to see that if x is greater
//    than y, z, or w, then m[0][0] will be greater than the other
//    diagonals or the sum of the diagonals.
//
//    So, the overall strategy is:  Figure out which if x,y,z, or w
//    will be greatest by looking at the diagonals.  Compute that
//    value using the sqrt() formula.  Then compute the other values
//    using the other set of formulas.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    int i, j, k;

    // First, find largest diagonal in matrix:
    if (m.isZero()) {
        quat[3] = ML_SCALAR_ONE;
        quat[0] = ML_SCALAR_ZERO;
        quat[1] = ML_SCALAR_ZERO;
        quat[2] = ML_SCALAR_ZERO;

        return (*this);
    }

    if (m[0][0] > m[1][1]) { 
        if (m[0][0] > m[2][2])
            i = 0;
        else i = 2;
    } else {
        if (m[1][1] > m[2][2]) 
            i = 1;
        else i = 2;
    }

    if (m[0][0]+m[1][1]+m[2][2] > m[i][i]) 
    {
        // Compute w first:
        quat[3] = mlMul(mlSqrt(m[0][0]+m[1][1]+m[2][2]+ML_SCALAR_ONE), ML_SCALAR_HALF);

        // And compute other values:
        quat[0] = mlDiv((m[1][2]-m[2][1]), (4*quat[3]));
        quat[1] = mlDiv((m[2][0]-m[0][2]), (4*quat[3]));
        quat[2] = mlDiv((m[0][1]-m[1][0]), (4*quat[3]));
    } else {
        // Compute x, y, or z first:
        j = (i+1)%3; k = (i+2)%3;
    
        // Compute first value:
        quat[i] = mlMul(mlSqrt(m[i][i]-m[j][j]-m[k][k]+ML_SCALAR_ONE), ML_SCALAR_HALF);
       
        // And the others:
        quat[j] = mlDiv((m[i][j]+m[j][i]), (4*quat[i]));
        quat[k] = mlDiv((m[i][k]+m[k][i]), (4*quat[i]));

        quat[3] = mlDiv((m[j][k]-m[k][j]), (4*quat[i]));
    }

#if defined(ML_DEBUG)
    // Check to be sure output matches input:
    MlTransform check;
    getValue(check);
    int ok = 1;
    for (i = 0; i < 4 && ok; i++) {
        for (j = 0; j < 3 && ok; j++) {
#if ML_FIXED_POINT
            if (mlAbs(m[i][j]-check[i][j]) > mlFloatToScalar(1.0e-1))
#else
            if (mlAbs(m[i][j]-check[i][j]) > mlFloatToScalar(1.0e-5))
#endif
                ok = FALSE;
        }
    }
    if (!ok) {
        fprintf(stderr,"MlRotation::setValue(const MlTransform& ): Rotation does not agree with matrix; this routine only works with rotation matrices!");
    }
#endif

    return (*this);
}


MlRotation& MlRotation::setValue(const MlVector3& axis, MlScalar radians)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets value of rotation from 3D rotation axis vector and angle in
//    radians.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlVector3    q;

    q = axis;
    q.normalize();

    q *= mlSin(mlRadiansToAngle(mlMul(radians, ML_SCALAR_HALF)));

    quat[0] = q[0];
    quat[1] = q[1];
    quat[2] = q[2];

    quat[3] = mlCos(mlRadiansToAngle(mlMul(radians, ML_SCALAR_HALF)));

    return(*this);
}


MlRotation& MlRotation::setValue(const MlVector3& rotateFrom, const MlVector3& rotateTo)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets rotation to rotate one direction vector to another.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlVector3 from = rotateFrom;
    MlVector3 to = rotateTo;
    MlVector3 axis;
    MlScalar  cost;

    from.normalize();
    to.normalize();
    cost = from.dot(to);

    // check for degeneracies
    if (cost > mlFloatToScalar(0.99999f)) {        // vectors are parallel
        quat[0] = quat[1] = quat[2] = ML_SCALAR_ZERO;
        quat[3] = ML_SCALAR_ONE;
        return* this;
    } else if (cost < mlFloatToScalar(-0.99999f)) {
        // vectors are opposite

        // find an axis to rotate around, which should be
        // perpendicular to the original axis
        // Try cross product with (1,0,0) first, if that's one of our
        // original vectors then try  (0,1,0).
        MlVector3 tmp = from.cross(MlVector3(ML_SCALAR_ONE, ML_SCALAR_ZERO, ML_SCALAR_ZERO));
        if (tmp.length() < mlFloatToScalar(0.00001f))
            tmp = from.cross(MlVector3(ML_SCALAR_ZERO, ML_SCALAR_ONE, ML_SCALAR_ZERO));

        tmp.normalize();
        setValue(tmp[0], tmp[1], tmp[2], ML_SCALAR_ZERO);
        return *this;
    }

    axis = rotateFrom.cross(rotateTo);
    axis.normalize();

    // use half-angle formulae
    // sin^2 t = ( 1 - cos (2t) ) / 2
    axis *= mlSqrt(mlMul(ML_SCALAR_HALF,  (ML_SCALAR_ONE - cost)));

    // scale the axis by the sine of half the rotation angle to get
    // the normalized quaternion
    quat[0] = axis[0];
    quat[1] = axis[1];
    quat[2] = axis[2];

    // cos^2 t = ( 1 + cos (2t) ) / 2
    // w part is cosine of half the rotation angle
    quat[3] = mlSqrt(mlMul(ML_SCALAR_HALF,  (ML_SCALAR_ONE + cost)));

    return (*this);
}


MlRotation& MlRotation::operator *=(const MlRotation& q)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Multiplies by another rotation.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlScalar p0, p1, p2, p3;

    p0 = (mlMul(q.quat[3], quat[0]) + mlMul(q.quat[0], quat[3]) +
          mlMul(q.quat[1], quat[2]) - mlMul(q.quat[2], quat[1]));
    p1 = (mlMul(q.quat[3], quat[1]) + mlMul(q.quat[1], quat[3]) +
          mlMul(q.quat[2], quat[0]) - mlMul(q.quat[0], quat[2]));
    p2 = (mlMul(q.quat[3], quat[2]) + mlMul(q.quat[2], quat[3]) +
          mlMul(q.quat[0], quat[1]) - mlMul(q.quat[1], quat[0]));
    p3 = (mlMul(q.quat[3], quat[3]) - mlMul(q.quat[0], quat[0]) -
          mlMul(q.quat[1], quat[1]) - mlMul(q.quat[2], quat[2]));
    quat[0] = p0;
    quat[1] = p1;
    quat[2] = p2;
    quat[3] = p3;

    normalize();

    return(*this);
}


int operator == (const MlRotation& q1, const MlRotation& q2)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Equality comparison operator.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    return (q1.quat[0] == q2.quat[0] &&
            q1.quat[1] == q2.quat[1] &&
            q1.quat[2] == q2.quat[2] &&
            q1.quat[3] == q2.quat[3]);
}


int MlRotation::equals(const MlRotation& r, MlScalar tolerance) const
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Equality comparison operator within given tolerance - the square
//    of the length of the maximum distance between the two vectors.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    return MlVector4(quat).equals(MlVector4(r.quat), tolerance);
}


MlRotation operator* (const MlRotation& q1, const MlRotation& q2)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Binary multiplication operator.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlRotation q(mlMul(q2.quat[3], q1.quat[0]) + mlMul(q2.quat[0], q1.quat[3]) +
                 mlMul(q2.quat[1], q1.quat[2]) - mlMul(q2.quat[2], q1.quat[1]),

                 mlMul(q2.quat[3], q1.quat[1]) + mlMul(q2.quat[1], q1.quat[3]) +
                 mlMul(q2.quat[2], q1.quat[0]) - mlMul(q2.quat[0], q1.quat[2]),

                 mlMul(q2.quat[3], q1.quat[2]) + mlMul(q2.quat[2], q1.quat[3]) +
                 mlMul(q2.quat[0], q1.quat[1]) - mlMul(q2.quat[1], q1.quat[0]),

                 mlMul(q2.quat[3], q1.quat[3]) - mlMul(q2.quat[0], q1.quat[0]) -
                 mlMul(q2.quat[1], q1.quat[1]) - mlMul(q2.quat[2], q1.quat[2]));
    q.normalize();

    return (q);
}


void MlRotation::multVec(const MlVector3& src, MlVector3& dst) const
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Puts the given vector through this rotation
//    (Multiplies the given vector by the matrix of this rotation).
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlTransform myMat;
    getValue(myMat);

    myMat.multVecMatrix(src, dst);
}


void MlRotation::scaleAngle(MlScalar scaleFactor)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Keep the axis the same. Multiply the angle of rotation by
//    the amount 'scaleFactor'
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    MlVector3 myAxis;
    MlScalar  myAngle;

    // Get the Axis and angle.
    getValue(myAxis, myAngle);

    setValue(myAxis, mlMul(myAngle,  scaleFactor));
}


MlRotation MlRotation::slerp(const MlRotation& rot0, const MlRotation& rot1, MlScalar t)
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Spherical linear interpolation: as t goes from 0 to 1, returned
//    value goes from rot0 to rot1.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////
{
    const MlScalar *r1q = rot1.getValue();

    MlRotation      rot;
    MlScalar        rot1q[4];
    MlScalar        omega, cosom, sinom;
    MlScalar        scalerot0, scalerot1;
    int             i;

    // Calculate the cosine
    cosom = mlMul(rot0.quat[0], rot1.quat[0]) + mlMul(rot0.quat[1], rot1.quat[1])
            + mlMul(rot0.quat[2], rot1.quat[2]) + mlMul(rot0.quat[3], rot1.quat[3]);

    // adjust signs if necessary
    if ( cosom < ML_SCALAR_ZERO ) {
        cosom = -cosom;
        for ( int j = 0; j < 4; j++ )
            rot1q[j] = -r1q[j];
    } else  {
        for ( int j = 0; j < 4; j++ )
            rot1q[j] = r1q[j];
    }

    // calculate interpolating coeffs
    if ( (ML_SCALAR_ONE - cosom) > mlFloatToScalar(0.00001f) ) {
        // standard case
        omega = mlAcos(cosom);
        sinom = mlSin(omega);
        scalerot0 = mlDiv(mlSin(mlMul((ML_SCALAR_ONE - t),  omega)), sinom);
        scalerot1 = mlDiv(mlSin(mlMul(t, omega)), sinom);
    } else {        
        // rot0 and rot1 very close - just do linear interp.
        scalerot0 = ML_SCALAR_ONE - t;
        scalerot1 = t;
    }

    // build the new quarternion
    for (i = 0; i <4; i++)
        rot.quat[i] = mlMul(scalerot0, rot0.quat[i]) + mlMul(scalerot1, rot1q[i]);

    return rot;
}


MlScalar MlRotation::norm() const
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns the norm (square of the 4D length) of the quaternion
//    defining the rotation.
//
// Use: private
//
////////////////////////////////////////////////////////////////////////
{
    return (mlSquare(quat[0]) +
            mlSquare(quat[1]) +
            mlSquare(quat[2]) +
            mlSquare(quat[3]));
}


void MlRotation::normalize()
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Normalizes a rotation quaternion to unit 4D length.
//
// Use: private
//
////////////////////////////////////////////////////////////////////////
{
    MlScalar    dist = mlRecipSqrt(norm());

    mlMulBy(quat[0], dist);
    mlMulBy(quat[1], dist);
    mlMulBy(quat[2], dist);
    mlMulBy(quat[3], dist);
}
