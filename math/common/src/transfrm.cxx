
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
//  For information concerning this source file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

#ifdef ML_REHEARSAL
#include <stdio.h>
#endif

// include Mlteur math header files
#include "math/scalar.h"
#include "math/trig.h"
#include "math/vector.h"
#include "math/rotation.h"
#include "math/transfrm.h"


//
// Handy absolute value macro:
//
#define ABS(a) ((a) < ML_SCALAR_ZERO ? -(a) : (a))


//
// Macro for checking if a matrix is idenity or zero.
//
#define IS_IDENTITY(matrix) ( \
    (matrix[0][0] == ML_SCALAR_ONE) && \
    (matrix[0][1] == ML_SCALAR_ZERO) && \
    (matrix[0][2] == ML_SCALAR_ZERO) && \
    (matrix[1][0] == ML_SCALAR_ZERO) && \
    (matrix[1][1] == ML_SCALAR_ONE) && \
    (matrix[1][2] == ML_SCALAR_ZERO) && \
    (matrix[2][0] == ML_SCALAR_ZERO) && \
    (matrix[2][1] == ML_SCALAR_ZERO) && \
    (matrix[2][2] == ML_SCALAR_ONE) && \
    (matrix[3][0] == ML_SCALAR_ZERO) && \
    (matrix[3][1] == ML_SCALAR_ZERO) && \
    (matrix[3][2] == ML_SCALAR_ZERO))

#define IS_ZERO(matrix) ( \
    (matrix[0][0] == ML_SCALAR_ZERO) && \
    (matrix[0][1] == ML_SCALAR_ZERO) && \
    (matrix[0][2] == ML_SCALAR_ZERO) && \
    (matrix[1][0] == ML_SCALAR_ZERO) && \
    (matrix[1][1] == ML_SCALAR_ZERO) && \
    (matrix[1][2] == ML_SCALAR_ZERO) && \
    (matrix[2][0] == ML_SCALAR_ZERO) && \
    (matrix[2][1] == ML_SCALAR_ZERO) && \
    (matrix[2][2] == ML_SCALAR_ZERO) && \
    (matrix[3][0] == ML_SCALAR_ZERO) && \
    (matrix[3][1] == ML_SCALAR_ZERO) && \
    (matrix[3][2] == ML_SCALAR_ZERO))


MlTransform::MlTransform(MlScalar a11, MlScalar a12, MlScalar a13, 
                         MlScalar a21, MlScalar a22, MlScalar a23, 
                         MlScalar a31, MlScalar a32, MlScalar a33, 
                         MlScalar a41, MlScalar a42, MlScalar a43)
//
// Constructor given all 12 elements in row-major order
//
{
    matrix.m[0][0] = a11;
    matrix.m[0][1] = a12;
    matrix.m[0][2] = a13;

    matrix.m[1][0] = a21;
    matrix.m[1][1] = a22;
    matrix.m[1][2] = a23;

    matrix.m[2][0] = a31;
    matrix.m[2][1] = a32;
    matrix.m[2][2] = a33;

    matrix.m[3][0] = a41;
    matrix.m[3][1] = a42;
    matrix.m[3][2] = a43;
}


MlTransform::MlTransform(const MlTrans &m)
//
// Constructor from a 4x3 array of float elements
//
{
    matrix.m[0][0] = m.m[0][0];
    matrix.m[0][1] = m.m[0][1];
    matrix.m[0][2] = m.m[0][2];
    matrix.m[1][0] = m.m[1][0];
    matrix.m[1][1] = m.m[1][1];
    matrix.m[1][2] = m.m[1][2];
    matrix.m[2][0] = m.m[2][0];
    matrix.m[2][1] = m.m[2][1];
    matrix.m[2][2] = m.m[2][2];
    matrix.m[3][0] = m.m[3][0];
    matrix.m[3][1] = m.m[3][1];
    matrix.m[3][2] = m.m[3][2];
}


MlTransform::MlTransform(MlScalar m[4][4])
//
// Constructor from a 4x4 array of double elements 
// Warning: The input better be an affine matrix (with last column
//          being 0,0,0,1) because this last column is thrown away!
//
{
    matrix.m[0][0] = m[0][0];
    matrix.m[0][1] = m[0][1];
    matrix.m[0][2] = m[0][2];
    matrix.m[1][0] = m[1][0];
    matrix.m[1][1] = m[1][1];
    matrix.m[1][2] = m[1][2];
    matrix.m[2][0] = m[2][0];
    matrix.m[2][1] = m[2][1];
    matrix.m[2][2] = m[2][2];
    matrix.m[3][0] = m[3][0];
    matrix.m[3][1] = m[3][1];
    matrix.m[3][2] = m[3][2];
}



MlTransform::MlTransform(MlScalar m[4][3])
//
// Constructor from a 4x3 array of double elements
//
{
    matrix.m[0][0] = m[0][0];
    matrix.m[0][1] = m[0][1];
    matrix.m[0][2] = m[0][2];
    matrix.m[1][0] = m[1][0];
    matrix.m[1][1] = m[1][1];
    matrix.m[1][2] = m[1][2];
    matrix.m[2][0] = m[2][0];
    matrix.m[2][1] = m[2][1];
    matrix.m[2][2] = m[2][2];
    matrix.m[3][0] = m[3][0];
    matrix.m[3][1] = m[3][1];
    matrix.m[3][2] = m[3][2];
}


////////////////////////////////////////////
//
// Setting matrix values
//
////////////////////////////////////////////

void MlTransform::setValue(const MlTrans &m)
//
// Sets value from 4x3 array of elements
//
{
    matrix.m[0][0] = m.m[0][0];
    matrix.m[0][1] = m.m[0][1];
    matrix.m[0][2] = m.m[0][2];
    matrix.m[1][0] = m.m[1][0];
    matrix.m[1][1] = m.m[1][1];
    matrix.m[1][2] = m.m[1][2];
    matrix.m[2][0] = m.m[2][0];
    matrix.m[2][1] = m.m[2][1];
    matrix.m[2][2] = m.m[2][2];
    matrix.m[3][0] = m.m[3][0];
    matrix.m[3][1] = m.m[3][1];
    matrix.m[3][2] = m.m[3][2];
}



////////////////////////////////////////////
//
// Operators
//
////////////////////////////////////////////

MlTransform& MlTransform::operator =(const MlTrans &m)
//
// Sets value from 4x3 array of elements
//
{
    setValue(m);
    return *this;
}


MlTransform& MlTransform::operator =(const MlTransform &m)
//
// ??? why do we need to write this out like this?
// ??? it doesn't seem to work otherwise, but why not?
//
{
    matrix.m[0][0] = m.matrix.m[0][0];
    matrix.m[0][1] = m.matrix.m[0][1];
    matrix.m[0][2] = m.matrix.m[0][2];
    matrix.m[1][0] = m.matrix.m[1][0];
    matrix.m[1][1] = m.matrix.m[1][1];
    matrix.m[1][2] = m.matrix.m[1][2];
    matrix.m[2][0] = m.matrix.m[2][0];
    matrix.m[2][1] = m.matrix.m[2][1];
    matrix.m[2][2] = m.matrix.m[2][2];
    matrix.m[3][0] = m.matrix.m[3][0];
    matrix.m[3][1] = m.matrix.m[3][1];
    matrix.m[3][2] = m.matrix.m[3][2];

    return *this;
}


MlTransform operator *(const MlTransform &l, const MlTransform &r)
//
// Binary multiplication of matrices
//
{
    MlTransform m = l;
    
    m *= r;
    
    return m;
}


int operator ==(const MlTransform &m1, const MlTransform &m2)
//
// Equality comparison operator. All componenents must match exactly.
//
{
    return (m1.matrix.m[0][0] == m2.matrix.m[0][0] &&
            m1.matrix.m[0][1] == m2.matrix.m[0][1] &&
            m1.matrix.m[0][2] == m2.matrix.m[0][2] &&
            m1.matrix.m[1][0] == m2.matrix.m[1][0] &&
            m1.matrix.m[1][1] == m2.matrix.m[1][1] &&
            m1.matrix.m[1][2] == m2.matrix.m[1][2] &&
            m1.matrix.m[2][0] == m2.matrix.m[2][0] &&
            m1.matrix.m[2][1] == m2.matrix.m[2][1] &&
            m1.matrix.m[2][2] == m2.matrix.m[2][2] &&
            m1.matrix.m[3][0] == m2.matrix.m[3][0] &&
            m1.matrix.m[3][1] == m2.matrix.m[3][1] &&
            m1.matrix.m[3][2] == m2.matrix.m[3][2] );
}


void MlTransform::getValue(MlTrans &m) const
//
// Returns 4x3 array of elements
//
{
    m.m[0][0] = matrix.m[0][0];
    m.m[0][1] = matrix.m[0][1];
    m.m[0][2] = matrix.m[0][2];
    m.m[1][0] = matrix.m[1][0];
    m.m[1][1] = matrix.m[1][1];
    m.m[1][2] = matrix.m[1][2];
    m.m[2][0] = matrix.m[2][0];
    m.m[2][1] = matrix.m[2][1];
    m.m[2][2] = matrix.m[2][2];
    m.m[3][0] = matrix.m[3][0];
    m.m[3][1] = matrix.m[3][1];
    m.m[3][2] = matrix.m[3][2];
}


#ifdef ML_REHEARSAL
void MlTransform::print(FILE *fp) const
//    Prints a formatted version of the matrix to the given file pointer.
{
    int i, j;
    
    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            fprintf(fp, "%10.5g%c", matrix.m[i][j], j < 2 ? '\t' : '\n');
}
#endif


int MlTransform::equals(const MlTransform &m, MlScalar tolerance) const
//
// Equality comparison operator within given tolerance for each component
//
{
    int i, j;
    MlScalar d;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++) {
            d = matrix.m[i][j] - m.matrix.m[i][j];
            if (mlAbs(d) > tolerance)
                return FALSE;
        }

    return TRUE;
}


MlTransform MlTransform::identity()    
//
// Return an identity matrix
//
{
    return MlTransform(ML_SCALAR_ONE, ML_SCALAR_ZERO, ML_SCALAR_ZERO,
                       ML_SCALAR_ZERO, ML_SCALAR_ONE, ML_SCALAR_ZERO, 
                       ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ONE,  
                       ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ZERO );
}


void MlTransform::makeIdentity()
//
// Sets matrix to be identity
//
{
    matrix.m[0][0] = ML_SCALAR_ONE;
    matrix.m[0][1] = ML_SCALAR_ZERO;
    matrix.m[0][2] = ML_SCALAR_ZERO;
    matrix.m[1][0] = ML_SCALAR_ZERO;
    matrix.m[1][1] = ML_SCALAR_ONE;
    matrix.m[1][2] = ML_SCALAR_ZERO;
    matrix.m[2][0] = ML_SCALAR_ZERO;
    matrix.m[2][1] = ML_SCALAR_ZERO;
    matrix.m[2][2] = ML_SCALAR_ONE;
    matrix.m[3][0] = ML_SCALAR_ZERO;
    matrix.m[3][1] = ML_SCALAR_ZERO;
    matrix.m[3][2] = ML_SCALAR_ZERO;
}


// Returns whether matrix is identity
int MlTransform::isIdentity() const
{
    return IS_IDENTITY(matrix.m);
}


// Returns whether matrix is all zeros
int MlTransform::isZero() const
{
    return IS_ZERO(matrix.m);
}



MlScalar MlTransform::det3(int r1, int r2, int r3) const
//
// Returns determinant of 3x3 submatrix composed of given row indices (0-3).
//
{
    return (mlMulMul(matrix.m[r1][0], matrix.m[r2][1], matrix.m[r3][2])
         +  mlMulMul(matrix.m[r1][1], matrix.m[r2][2], matrix.m[r3][0])
         +  mlMulMul(matrix.m[r1][2], matrix.m[r2][0], matrix.m[r3][1])
         -  mlMulMul(matrix.m[r1][0], matrix.m[r2][2], matrix.m[r3][1])
         -  mlMulMul(matrix.m[r1][1], matrix.m[r2][0], matrix.m[r3][2])
         -  mlMulMul(matrix.m[r1][2], matrix.m[r2][1], matrix.m[r3][0]));
}


MlScalar MlTransform::det() const
//
// Returns determinant of upper-left 3x3 matrix
//
{
    return (det3(0, 1, 2));
}


int MlTransform::factor(MlTransform &r, MlVector3& s,
                        MlTransform &u, MlVector3& t,
                        MlTransform &proj) const
//
// Factors a matrix m into 5 pieces: m = r s r^ u t, where r^
// means transpose of r, and r and u are rotations, s is a scale,
// and t is a translation. Any projection information is returned
// in proj.
//
/*
 * Variable declarations from the original source:
 *
 * n    : order of matrix A
 * eivec: true if eigenvectors are desired, false otherwise.
 * a    : Array [1:n, 1:n] of numbers, assumed symmetric!
 *
 * a    : Superdiagonal elements of the original array a are destroyed.
 *        Diagonal and subdiagonal elements are untouched.
 * d    : Array [1:n] of eigenvalues of a.
 * v    : Array [1:n, 1:n] containing (if eivec = TRUE), the eigenvectors of
 *        a, with the kth column being the normalized eigenvector with
 *        eigenvalue d[k].
 * rot  : The number of jacobi rotations required to perform the operation.
 */
{
    MlScalar    det;        /* Determinant of matrix A    */
    MlScalar    det_sign;    /* -1 if det < 0, 1 if det > 0    */
    MlScalar    scratch;
    int         i, j;
    int         junk;
    MlTransform a, b, si;
    MlScalar    evalues[3];
    MlVector3   evectors[3];
    
    a = *this;
    proj.makeIdentity();
    scratch = ML_SCALAR_ONE;
    
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mlMulBy(a.matrix.m[i][j], scratch);
        }
        t[i] = mlMul(matrix.m[3][i], scratch);
        a.matrix.m[3][i] = ML_SCALAR_ZERO;
    }
    
    /* (3) Compute det A. If negative, set sign = -1, else sign = 1 */
    det = a.det();
    det_sign = (det < ML_SCALAR_ZERO ? -ML_SCALAR_ONE : ML_SCALAR_ONE);
    if (mlMul(det_sign, det) < ML_SCALAR(1e-12))
        return(FALSE);        // singular
    
    /* (4) B = A * A^  (here A^ means A transpose) */
    b = a * a.transpose();
    
    b.jacobi3(evalues, evectors, junk);

    // find min / max eigenvalues and do ratio test to determine singularity
    
    r = MlTransform(evectors[0][0], evectors[0][1], evectors[0][2], 
                    evectors[1][0], evectors[1][1], evectors[1][2], 
                    evectors[2][0], evectors[2][1], evectors[2][2], 
                    ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ZERO);
    
    /* Compute s = sqrt(evalues), with sign. Set si = s-inverse */
    si.makeIdentity();
    for (i = 0; i < 3; i++) {
        s[i] = mlMul(det_sign, mlSqrt(evalues[i]));
        si.matrix.m[i][i] = mlReciprocal(s[i]);
    }
    
    /* (5) Compute U = R^ S! R A. */
    u = r * si * r.transpose() * a;
    
    return(TRUE);
}


void MlTransform::jacobi3(MlScalar evalues[3],
                  MlVector3 evectors[3], int &rots) const
//
// Diagonalizes 3x3 matrix. See comment for factor().
//
{
    MlScalar    sm;       // smallest entry
    MlScalar    theta;    // angle for Jacobi rotation
    MlScalar    c, s, t;  // cosine, sine, tangent of theta
    MlScalar    tau;      // sine / (1 + cos)
    MlScalar    h, g;     // two scrap values
    MlScalar    thresh;   // threshold below which no rotation done
    MlScalar    b[3];     // more scratch
    MlScalar    z[3];     // more scratch
    int         p, q, i, j;
    MlScalar    a[3][3];
    
    // initializations
    for (i = 0; i < 3; i++) {
        b[i] = evalues[i] = matrix.m[i][i];
        z[i] = ML_SCALAR_ZERO;
        for (j = 0; j < 3; j++) {
            evectors[i][j] = (i == j) ? ML_SCALAR_ONE : ML_SCALAR_ZERO;
            a[i][j] = matrix.m[i][j];
        }
    }
    
    rots = 0;

    // Why 50? I don't know--it's the way the folks who wrote the
    // algorithm did it:
    for (i = 0; i < 50; i++) {
        sm = ML_SCALAR_ZERO;
        for (p = 0; p < 3 - 1; p++)
            for (q = p+1; q < 3; q++)
                sm += ABS(a[p][q]);
    
        if (sm == ML_SCALAR_ZERO)
            return;
    
        // thresh = (i < 3 ?
        //          (.2 * sm / (3 * 3)) :
        //          ML_SCALAR_ZERO);

        thresh = (i < 3 ?
                  mlMul(sm, ML_SCALAR(.022222222222f) ) :
                  ML_SCALAR_ZERO);
    
        for (p = 0; p < 3 - 1; p++) {
            for (q = p+1; q < 3; q++) {
        
                g = mlMul(ML_SCALAR(100.0), mlAbs(a[p][q]));
        
                if (i > 3 && (mlAbs(evalues[p]) + g == mlAbs(evalues[p])) &&
                             (mlAbs(evalues[q]) + g == mlAbs(evalues[q])))
                    a[p][q] = ML_SCALAR_ZERO;
        
                else if (mlAbs(a[p][q]) > thresh) {
                    h = evalues[q] - evalues[p];
            
                    if (mlAbs(h) + g == mlAbs(h))
                        t = mlDiv(a[p][q], h);
                    else {
                        theta = mlMulDiv(ML_SCALAR_HALF, h, a[p][q]);
                        t = mlReciprocal(mlAbs(theta) + mlSqrt(ML_SCALAR_ONE + mlSquare(theta)));
                        if (theta < ML_SCALAR_ZERO)  t = -t;
                    }
                    // End of computing tangent of rotation angle
            
                    c = mlReciprocal(mlSqrt(ML_SCALAR_ONE + mlSquare(t)));
                    s = mlMul(t, c);
                    tau = mlDiv(s, (ML_SCALAR_ONE + c));
                    h = mlMul(t, a[p][q]);
                    z[p]    -= h;
                    z[q]    += h;
                    evalues[p] -= h;
                    evalues[q] += h;
                    a[p][q] = ML_SCALAR_ZERO;
            
                    for (j = 0; j < p; j++) {
                        g = a[j][p];
                        h = a[j][q];
                        a[j][p] = g - mlMul(s, (h + mlMul(g, tau)));
                        a[j][q] = h + mlMul(s, (g - mlMul(h, tau)));
                    }
            
                    for (j = p+1; j < q; j++) {
                        g = a[p][j];
                        h = a[j][q];
                        a[p][j] = g - mlMul(s, (h + mlMul(g, tau)));
                        a[j][q] = h + mlMul(s, (g - mlMul(h, tau)));
                    }
            
                    for (j = q+1; j < 3; j++) {
                        g = a[p][j];
                        h = a[q][j];
                        a[p][j] = g - mlMul(s, (h + mlMul(g, tau)));
                        a[q][j] = h + mlMul(s, (g - mlMul(h, tau)));
                    }
            
                    for (j = 0; j < 3; j++) {
                        g = evectors[j][p];
                        h = evectors[j][q];
                        evectors[j][p] = g - mlMul(s, (h + mlMul(g, tau)));
                        evectors[j][q] = h + mlMul(s, (g - mlMul(h, tau)));
                    }
                }
                rots++;
            }
        }
        for (p = 0; p < 3; p++) {
            evalues[p] = b[p] += z[p];
            z[p] = ML_SCALAR_ZERO;
        }
    }
}


MlTransform MlTransform::inverse() const
// The following method finds the inverse of an affine matrix.
// The last column MUST be [0 0 0 1] for this to work.
// This is taken from graphics gems 2, page 603
//
// computes the inverse of a 3d affine matrix; i.e. a matrix with a 
// dimensionality of 4 where the right column has the entries (0,0,0,1).
//
// This procedure treats the 4 by 4 matrix as a block matrix and calculates
// the inverse of one submatrix for a significant performance 
// improvement over a general procedure that can invert any nonsingular matrix.
//
//             -1 
//  -1   |    |      |  -1    |
// M   = |A  0|  =   | A     0|
//       |    |      |        |
//       |    |      |   -1   |
//       |C  1|      |-CA    1|
//
// where   M is a 4 by 4 matrix,
//         A is the 3 by 3 upper left submatrix of M,
//         C is the 1 by 3 lower left submatrix of M.
// Input:
//   in - 3D affine matrix
// Output:
//   out - inverse of 3D affine matrix
// Returned Value:
//   inverse matrix if input matrix is nonsingular and affine
//   unchanged otherwise
{
    // Trivial case
    if (IS_IDENTITY(matrix.m))
    return MlTransform::identity();

    MlTransform result;

    // Calculate the determinant of submatrix A and determine if the matrix
    // is singular as limited by the double precision floating 
    // point data representation

    MlScalar det_1;
    MlScalar pos, neg, temp;

#define ACCUMULATE \
    if (temp >= ML_SCALAR_ZERO) \
        pos += temp; \
    else             \
        neg += temp;

    pos = neg = ML_SCALAR_ZERO;
    temp =  mlMulMul(matrix.m[0][0], matrix.m[1][1], matrix.m[2][2]);
    ACCUMULATE
    temp =  mlMulMul(matrix.m[0][1], matrix.m[1][2], matrix.m[2][0]);
    ACCUMULATE
    temp =  mlMulMul(matrix.m[0][2], matrix.m[1][0], matrix.m[2][1]);
    ACCUMULATE
    temp = -mlMulMul(matrix.m[0][2], matrix.m[1][1], matrix.m[2][0]);
    ACCUMULATE
    temp = -mlMulMul(matrix.m[0][1], matrix.m[1][0], matrix.m[2][2]);
    ACCUMULATE
    temp = -mlMulMul(matrix.m[0][0], matrix.m[1][2], matrix.m[2][1]);
    ACCUMULATE
    det_1 = pos + neg;

#undef ACCUMULATE

#define PRECISION_LIMIT ML_SCALAR(1.0e-15)

    // Is the submatrix A singular?
    temp = mlDiv(det_1, (pos - neg));
    if (mlAbs(temp) < PRECISION_LIMIT)
        return matrix;

    // Calculate inverse(A) = adj(A) / det(A)
    det_1 = mlReciprocal(det_1);
    result[0][0] =  mlMul(mlMul(matrix.m[1][1], matrix.m[2][2]) - mlMul(matrix.m[1][2], matrix.m[2][1]), det_1);
    result[1][0] = -mlMul(mlMul(matrix.m[1][0], matrix.m[2][2]) - mlMul(matrix.m[1][2], matrix.m[2][0]), det_1);
    result[2][0] =  mlMul(mlMul(matrix.m[1][0], matrix.m[2][1]) - mlMul(matrix.m[1][1], matrix.m[2][0]), det_1);
    result[0][1] = -mlMul(mlMul(matrix.m[0][1], matrix.m[2][2]) - mlMul(matrix.m[0][2], matrix.m[2][1]), det_1);
    result[1][1] =  mlMul(mlMul(matrix.m[0][0], matrix.m[2][2]) - mlMul(matrix.m[0][2], matrix.m[2][0]), det_1);
    result[2][1] = -mlMul(mlMul(matrix.m[0][0], matrix.m[2][1]) - mlMul(matrix.m[0][1], matrix.m[2][0]), det_1);
    result[0][2] =  mlMul(mlMul(matrix.m[0][1], matrix.m[1][2]) - mlMul(matrix.m[0][2], matrix.m[1][1]), det_1);
    result[1][2] = -mlMul(mlMul(matrix.m[0][0], matrix.m[1][2]) - mlMul(matrix.m[0][2], matrix.m[1][0]), det_1);
    result[2][2] =  mlMul(mlMul(matrix.m[0][0], matrix.m[1][1]) - mlMul(matrix.m[0][1], matrix.m[1][0]), det_1);

    // Calculate -C * inverse(A)
    result[3][0] = -( mlMul(matrix.m[3][0], result[0][0]) + 
                      mlMul(matrix.m[3][1], result[1][0]) + 
                      mlMul(matrix.m[3][2], result[2][0]) );
    result[3][1] = -( mlMul(matrix.m[3][0], result[0][1]) + 
                      mlMul(matrix.m[3][1], result[1][1]) + 
                      mlMul(matrix.m[3][2], result[2][1]) );
    result[3][2] = -( mlMul(matrix.m[3][0], result[0][2]) + 
                      mlMul(matrix.m[3][1], result[1][2]) + 
                      mlMul(matrix.m[3][2], result[2][2]) );

#undef PRECISION_LIMIT

    return result;
}



MlTransform MlTransform::transpose() const
//
// Returns transpose of matrix
//
{
    return MlTransform(matrix.m[0][0], matrix.m[1][0], matrix.m[2][0], 
                       matrix.m[0][1], matrix.m[1][1], matrix.m[2][1], 
                       matrix.m[0][2], matrix.m[1][2], matrix.m[2][2], 
                       ML_SCALAR_ZERO, ML_SCALAR_ZERO, ML_SCALAR_ZERO);
}



////////////////////////////////////////////
//
// Matrix/matrix and matrix/vector arithmetic
//
////////////////////////////////////////////

MlTransform& MlTransform::multRight(const MlTransform &m)
//
// Multiplies matrix by given matrix on right
//
{
    // Trivial cases
    if (IS_IDENTITY(m.matrix.m))
        return *this;
    else if (IS_IDENTITY(matrix.m))
        return (*this = m);
    
    MlTrans tmp;

#define MULT_RIGHT(i,j) (mlMul(matrix.m[i][0], m.matrix.m[0][j]) + \
                         mlMul(matrix.m[i][1], m.matrix.m[1][j]) + \
                         mlMul(matrix.m[i][2], m.matrix.m[2][j]))

    tmp.m[0][0] = MULT_RIGHT(0,0);
    tmp.m[0][1] = MULT_RIGHT(0,1);
    tmp.m[0][2] = MULT_RIGHT(0,2);
    tmp.m[1][0] = MULT_RIGHT(1,0);
    tmp.m[1][1] = MULT_RIGHT(1,1);
    tmp.m[1][2] = MULT_RIGHT(1,2);
    tmp.m[2][0] = MULT_RIGHT(2,0);
    tmp.m[2][1] = MULT_RIGHT(2,1);
    tmp.m[2][2] = MULT_RIGHT(2,2);
#undef MULT_RIGHT


#define MULT_RIGHT_1(i,j) (mlMul(matrix.m[i][0], m.matrix.m[0][j]) + \
                           mlMul(matrix.m[i][1], m.matrix.m[1][j]) + \
                           mlMul(matrix.m[i][2], m.matrix.m[2][j]) + \
                           m.matrix.m[3][j])
    tmp.m[3][0] = MULT_RIGHT_1(3,0);
    tmp.m[3][1] = MULT_RIGHT_1(3,1);
    tmp.m[3][2] = MULT_RIGHT_1(3,2);
#undef MULT_RIGHT_1

    return (*this = tmp);
}


MlTransform& MlTransform::multLeft(const MlTransform &m)
//
// Multiplies matrix by given matrix on left
//
{
    // Trivial cases
    if (IS_IDENTITY(m.matrix.m))
        return *this;
    else if (IS_IDENTITY(matrix.m))
        return (*this = m);
    
    MlTrans tmp;

//Here we know last column entries are 0.0
#define MULT_LEFT(i,j) (mlMul(m.matrix.m[i][0], matrix.m[0][j]) + \
                        mlMul(m.matrix.m[i][1], matrix.m[1][j]) + \
                        mlMul(m.matrix.m[i][2], matrix.m[2][j]))

    tmp.m[0][0] = MULT_LEFT(0,0);
    tmp.m[0][1] = MULT_LEFT(0,1);
    tmp.m[0][2] = MULT_LEFT(0,2);
    tmp.m[1][0] = MULT_LEFT(1,0);
    tmp.m[1][1] = MULT_LEFT(1,1);
    tmp.m[1][2] = MULT_LEFT(1,2);
    tmp.m[2][0] = MULT_LEFT(2,0);
    tmp.m[2][1] = MULT_LEFT(2,1);
    tmp.m[2][2] = MULT_LEFT(2,2);
#undef MULT_LEFT


//Here we know last column entry is 1.0
#define MULT_LEFT_1(i,j) (mlMul(m.matrix.m[i][0], matrix.m[0][j]) + \
                          mlMul(m.matrix.m[i][1], matrix.m[1][j]) + \
                          mlMul(m.matrix.m[i][2], matrix.m[2][j]) + \
                          matrix.m[3][j])
    tmp.m[3][0] = MULT_LEFT_1(3,0);
    tmp.m[3][1] = MULT_LEFT_1(3,1);
    tmp.m[3][2] = MULT_LEFT_1(3,2);
#undef MULT_LEFT_1

    return (*this = tmp);

}


void MlTransform::multMatrixVec(const MlVector3& src, MlVector3& dst) const
//
// Multiplies matrix by given column vector, giving vector result
//
{
    MlScalar x,y,z;
    
    x = mlMul(matrix.m[0][0], src[0]) + mlMul(matrix.m[0][1], src[1]) +
        mlMul(matrix.m[0][2], src[2]);
    y = mlMul(matrix.m[1][0], src[0]) + mlMul(matrix.m[1][1], src[1]) +
        mlMul(matrix.m[1][2], src[2]);
    z = mlMul(matrix.m[2][0], src[0]) + mlMul(matrix.m[2][1], src[1]) +
        mlMul(matrix.m[2][2], src[2]);
//    w = mlMul(matrix.m[3][0], src[0]) + mlMul(matrix.m[3][1], src[1]) +
//    mlMul(matrix.m[3][2], src[2]) + ML_SCALAR_ONE;
//    
//    MlScalar wr = mlReciprocal(w);
//    dst.setValue(mlMul(x,wr), mlMul(y,wr), mlMul(z,wr));

    dst.setValue(x,y,z);
}


void MlTransform::multVecMatrix(const MlVector3& src, MlVector3& dst) const
//
// Multiplies given row vector by matrix, giving vector result
//
{
    MlScalar x,y,z;
    
    x = mlMul(src[0], matrix.m[0][0]) + mlMul(src[1], matrix.m[1][0]) +
        mlMul(src[2], matrix.m[2][0]) + matrix.m[3][0];
    y = mlMul(src[0], matrix.m[0][1]) + mlMul(src[1], matrix.m[1][1]) +
        mlMul(src[2], matrix.m[2][1]) + matrix.m[3][1];
    z = mlMul(src[0], matrix.m[0][2]) + mlMul(src[1], matrix.m[1][2]) +
        mlMul(src[2], matrix.m[2][2]) + matrix.m[3][2];

//    w = mlMul(src[0], matrix.m[0][3]) + mlMul(src[1], matrix.m[1][3]) +
//    mlMul(src[2], matrix.m[2][3]) + ML_SCALAR_ONE;
//    
//    MlScalar wr = mlReciprocal(w);
//    dst.setValue(mlMul(x,wr), mlMul(y,wr), mlMul(z,wr));

    dst.setValue(x,y,z);
}


void MlTransform::multDirMatrix(const MlVector3& src, MlVector3& dst) const
//
// Multiplies given row vector by matrix, giving vector result
// src is assumed to be a direction vector, so translation part of
// matrix is ignored.
//
{
    MlScalar x,y,z;
    
    x = mlMul(src[0], matrix.m[0][0]) + mlMul(src[1], matrix.m[1][0]) + mlMul(src[2], matrix.m[2][0]);
    y = mlMul(src[0], matrix.m[0][1]) + mlMul(src[1], matrix.m[1][1]) + mlMul(src[2], matrix.m[2][1]);
    z = mlMul(src[0], matrix.m[0][2]) + mlMul(src[1], matrix.m[1][2]) + mlMul(src[2], matrix.m[2][2]);
    
    dst.setValue(x, y, z);
}


//////////////////////////////////////////////////////////////////
//
// Miscellaneous get/set convenience routines for translations
//
//////////////////////////////////////////////////////////////////

void MlTransform::getTranslation(MlVector3& translation)
//Sets the given translation vector to the X,Y,Z translations contained 
//in the given transformation matrix
{ 
  for (int i=0;i<3;i++)
      translation[i]=matrix.m[3][i];
}


void MlTransform::setTranslation(const MlVector3 newTranslation)
//
// Sets matrix to the translation matrix given by the vector
//
{
    matrix.m[0][0] = ML_SCALAR_ONE;
    matrix.m[0][1] = ML_SCALAR_ZERO;
    matrix.m[0][2] = ML_SCALAR_ZERO;
    matrix.m[1][0] = ML_SCALAR_ZERO;
    matrix.m[1][1] = ML_SCALAR_ONE;
    matrix.m[1][2] = ML_SCALAR_ZERO;
    matrix.m[2][0] = ML_SCALAR_ZERO;
    matrix.m[2][1] = ML_SCALAR_ZERO;
    matrix.m[2][2] = ML_SCALAR_ONE;
    matrix.m[3][0] = newTranslation[0];
    matrix.m[3][1] = newTranslation[1];
    matrix.m[3][2] = newTranslation[2];
}


void MlTransform::setTranslationOnly(const MlVector3 translation)
//Sets the translation of the given transform to the X,Y,Z translations 
//contained in the given new translation vector
{
    for (int i=0;i<3;i++)
        matrix.m[3][i]=translation[i];
}


void MlTransform::applyTranslation(const MlVector3 translation)
//Adds the given X,Y,Z translations to the existing translation
//contained in the transform
{
    for (int i=0;i<3;i++)
        matrix.m[3][i]+=translation[i];
}


//////////////////////////////////////////////////////////////////
//
// Miscellaneous get/set convenience routines for rotations
//
//////////////////////////////////////////////////////////////////

void MlTransform::getRotation(MlRotation& rotation)
//
// Gets the quaternion rotation from the matrix 
//
{
    rotation.setValue(*this);
}


void MlTransform::getRotation(MlVector3& rotation)
//Gets the the X,Y,Z fixed rotations from the transformation matrix  
//and returns it in the given rotation vector 
//Note: normalizes angles to positive degrees
{ 
    MlTransform t;
    int i,j;

    //Normalize the rotation matrix portion of the transform
    for (i=0;i<3;i++) {
         MlScalar total=ML_SCALAR_ZERO;

         for (j=0;j<3;j++) {
             t[i][j]=matrix.m[i][j];
             total+=mlMul(t[i][j], t[i][j]);
         }
         if (total!=ML_SCALAR_ZERO) {
             total=mlSqrt(total);
             for (j=0;j<3;j++)
                 mlDivBy(t[i][j], total);
         }
    }

    //Get Y rotation
    rotation[1]=mlAngleToDegrees(mlAsin(t[2][0]));

    if (mlAbs(t[2][0]-ML_SCALAR_ONE)>ML_SCALAR(0.001)) {
        //Get X and Z rotations
        rotation[0]=mlAngleToDegrees(mlAtan2(-t[2][1],t[2][2]));
        rotation[2]=mlAngleToDegrees(mlAtan2(-t[1][0],t[0][0]));
    } else {
        //Have Gimbal lock--lost Z degree of freedom, so
       //express rotation as only a X rotation
       //This can be avoided by moving to quaternion rotations!
       rotation[0]=mlAngleToDegrees(mlAtan2(t[0][1],t[2][1]));
       rotation[2]=ML_SCALAR_ZERO;
    }

    for (i=0;i<3;i++)
        if (rotation[i]<ML_SCALAR_ZERO)
            rotation[i]+=ML_SCALAR(360);
}


void MlTransform::setRotation(const MlRotation newRotation)
//
// Sets matrix to the rotate matrix given the rotation
//
{
    newRotation.getValue(*this);
}


void MlTransform::setRotationOnly(const MlRotation rotation)
//Sets the rotation matrix of the given transform to the X,Y,Z fixed rotations
//contained in the given new rotation vector
{
    MlVector3 translation,scale;
    getTranslation(translation);
    getScale(scale);

    setTransform(translation, rotation, scale);
}


void MlTransform::setRotationOnly(const MlVector3 rotation)
//Sets the rotation matrix of the given transform to the X,Y,Z fixed rotations
//contained in the given new rotation vector
{
    MlVector3 translation,scale;

    getTranslation(translation);
    getScale(scale);

    setTransform(translation, rotation, scale);
}


void MlTransform::applyRotation(const MlRotation rotation)
//Applies the quaternion rotation to the matrix
{
    MlTransform mat; 

    rotation.getValue(mat);
    multRight(mat);
}


void MlTransform::applyRotation(const MlVector3 rotation)
//Applies the fixed angle rotation to the matrix
{
    MlTransform mat; 
    mat.makeIdentity();

    //Apply Z Rotation
    if (rotation[2]!=ML_SCALAR_ZERO) {
        MlScalar angle = mlDegreesToAngle(rotation[2]);
        MlScalar sz=mlSin(angle);
        MlScalar cz=mlCos(angle);
        mat[0][0]=cz;
        mat[0][1]=sz;
        mat[1][0]=-sz;
        mat[1][1]=cz;
        mat[2][2]=ML_SCALAR_ONE;
        mat[0][2]=mat[1][2]=mat[2][0]=
        mat[2][1]=mat[3][0]=mat[3][1]=mat[3][2]=ML_SCALAR_ZERO;
        multRight(mat);
    }

    //Apply Y Rotation
    if (rotation[1]!=ML_SCALAR_ZERO) {
        MlScalar angle = mlDegreesToAngle(rotation[1]);
        MlScalar sy=mlSin(angle);
        MlScalar cy=mlCos(angle);
        mat[0][0]=cy;
        mat[0][2]=-sy;
        mat[1][1]=ML_SCALAR_ONE;
        mat[2][0]=sy;
        mat[2][2]=cy;
        mat[0][1]=mat[1][0]=mat[1][2]=
        mat[2][1]=mat[3][0]=mat[3][1]=mat[3][2]=ML_SCALAR_ZERO;
        multRight(mat);
     }

    //Apply X Rotation
    if (rotation[0]!=ML_SCALAR_ZERO) {
        MlScalar angle = mlDegreesToAngle(rotation[0]);
        MlScalar sx=mlSin(angle);
        MlScalar cx=mlCos(angle);
        mat[0][0]=ML_SCALAR_ONE;
        mat[1][1]=cx;
        mat[1][2]=sx;
        mat[2][1]=-sx;
        mat[2][2]=cx;
        mat[0][1]=mat[0][2]=mat[1][0]=
        mat[2][0]=mat[3][0]=mat[3][1]=mat[3][2]=ML_SCALAR_ZERO;
        multRight(mat);
    }
}



//////////////////////////////////////////////////////////////////
//
// Miscellaneous get/set convenience routines for scales
//
//////////////////////////////////////////////////////////////////


void MlTransform::getScale(MlVector3& scale)
// Given a transformation matrix returns a vector containing
// the X,Y,Z nonuniform scales
{
    for (int i=0;i<3;i++)
        scale[i]=mlSqrt(mlMul(matrix.m[i][0],
                        matrix.m[i][0]) + mlMul(matrix.m[i][1], matrix.m[i][1])+
                        mlMul(matrix.m[i][2], matrix.m[i][2]));
}


void MlTransform::setScale(MlScalar newScale)
//
// Sets matrix to scale by given uniform factor
//
{
    matrix.m[0][0] = newScale;
    matrix.m[0][1] = ML_SCALAR_ZERO;
    matrix.m[0][2] = ML_SCALAR_ZERO;
    matrix.m[1][0] = ML_SCALAR_ZERO;
    matrix.m[1][1] = newScale;
    matrix.m[1][2] = ML_SCALAR_ZERO;
    matrix.m[2][0] = ML_SCALAR_ZERO;
    matrix.m[2][1] = ML_SCALAR_ZERO;
    matrix.m[2][2] = newScale;
    matrix.m[3][0] = ML_SCALAR_ZERO;
    matrix.m[3][1] = ML_SCALAR_ZERO;
    matrix.m[3][2] = ML_SCALAR_ZERO;
}


void MlTransform::setScale(const MlVector3 newScale)
//
// Sets matrix to scale by given vector
//
{
    matrix.m[0][0] = newScale[0];
    matrix.m[0][1] = ML_SCALAR_ZERO;
    matrix.m[0][2] = ML_SCALAR_ZERO;
    matrix.m[1][0] = ML_SCALAR_ZERO;
    matrix.m[1][1] = newScale[1];
    matrix.m[1][2] = ML_SCALAR_ZERO;
    matrix.m[2][0] = ML_SCALAR_ZERO;
    matrix.m[2][1] = ML_SCALAR_ZERO;
    matrix.m[2][2] = newScale[2];
    matrix.m[3][0] = ML_SCALAR_ZERO;
    matrix.m[3][1] = ML_SCALAR_ZERO;
    matrix.m[3][2] = ML_SCALAR_ZERO;
}


void MlTransform::setScaleOnly(const MlVector3 scale)
//Sets the scales of the given transform to the X,Y,Z nonuniform scales
//contained in the given new scale vector
{
    MlVector3 translation,rotation;
    getTranslation(translation);
    getRotation(rotation);
    setTransform(translation, rotation, scale);
}


//////////////////////////////////////////////////////////////////
//
// Miscellaneous get/set convenience routines for transformations
//
//////////////////////////////////////////////////////////////////

void MlTransform::getTransform(MlVector3& translation,
                               MlRotation &rotation,
                               MlVector3& scaleFactor,
                               MlRotation &scaleOrientation,
                               const MlVector3& center) const
//
// Decomposes a rotation into translation etc, based on scale
//
{
    MlTransform so, rot, proj;
    if (center != MlVector3(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO)) {
    // to get fields for a non-0 center, we
    // need to decompose a new matrix "m" such
    // that [-center][m][center] = [this]
    // i.e., [m] = [center][this][-center]
    // (this trick stolen from Showcase code)
        MlTransform m,c;
        m.setTranslation(-center);
        m.multLeft(*this);
        c.setTranslation(center);
        m.multLeft(c);
        m.factor(so,scaleFactor,rot,translation,proj);
    } else
        this->factor(so,scaleFactor,rot,translation,proj);

    // have to transpose because factor 
    // gives us transpose of correct answer.
    scaleOrientation = so.transpose();

    rotation = rot;
}


void MlTransform::setTransform(const MlVector3& translation,
                               const MlRotation &rotation,
                               const MlVector3& scaleFactor,
                               const MlRotation &scaleOrientation,
                               const MlVector3& center)
//
// Composes the matrix from translation, rotation, scale, etc.
//
{
#define TRANSLATE(vec) m.setTranslation(vec), multLeft(m)
#define ROTATE(rot)    rot.getValue(m), multLeft(m)
    MlTransform m;

    makeIdentity();
    
    if (translation != MlVector3(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO))
        TRANSLATE(translation);

    if (center != MlVector3(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO))
        TRANSLATE(center);

    if (rotation != MlRotation(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ONE))
        ROTATE(rotation);

    if (scaleFactor != MlVector3(ML_SCALAR_ONE,ML_SCALAR_ONE,ML_SCALAR_ONE)) 
    {
        MlRotation so = scaleOrientation;
        if (so != MlRotation(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ONE))
            ROTATE(so);

         m.setScale(scaleFactor);
         multLeft(m);
 
         if (so != MlRotation(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ONE)) {
             so.invert();
             ROTATE(so);
         }
    }

    if (center != MlVector3(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO))
        TRANSLATE(-center);

#undef TRANSLATE
#undef ROTATE
}


void MlTransform::setTransform(const MlVector3 translation,
                               const MlVector3 rotation,
                               const MlVector3 scale)
//Sets the given transform to the matrix constructed from the given 
//translation, fixed angle rotation, and scale vectors
//Note** Uses scale - rotate - translate order with rotation order Z-Y-X
{
    MlTransform mat;

    setScale(scale);
    applyRotation(rotation);
    setTranslationOnly(translation);

}


void MlTransform::setTransform(const MlVector3 translation,
                               const MlVector3 rotation, 
                               const MlVector3 nonuniformScale, MlScalar scale)
//Sets the given transform to the matrix constructed from the given 
//translation, fixed angle rotation, and nonuniformScale*scale vectors
//Note** Uses scale - rotate - translate order with rotation order Z-Y-X
{
    MlVector3 newScale;
    for (int i=0;i<3;i++)
        newScale[i]=mlMul(scale, nonuniformScale[i]);
    setTransform(translation, rotation, newScale);
}

