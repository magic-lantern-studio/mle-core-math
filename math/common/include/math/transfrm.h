/** @defgroup MlMath Magic Lantern Math Library API */

/**
 * @file transfrm.h
 * @ingroup MlMath
 *
 * @author Mark S. Millard
 * @date Jan 24, 2006
 *
 * This file provides utility for 4x3 Affine Matrix Transformations.
 */

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
//  For information concerning this header file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

#ifndef TRANSFRM_H_INCLUDED
#define TRANSFRM_H_INCLUDED

#ifdef ML_REHEARSAL
#include <stdio.h>
#endif

// Include Magic Lantern math header files.
#include <math/mlmath.h>
#include <math/scalar.h>
#include <math/vector.h>
#include <math/rotation.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// Conversion factor from Degrees to Radians.
#ifndef DEG2RAD
#define DEG2RAD ML_SCALAR(0.01745329251994329500d)
#endif


// XXX  This used to be:
// 	typedef MlScalar MlTrans[4][3];
// but the Visual C++ compiler has a bug that won't let you pass a 
// const array type to a function, so this is the quickest fix.

/**
 * @brief A container for the elements of a transform.
 */
typedef struct MLMATH_API _MlTrans
{
    MlScalar m[4][3]; /**< A 4x3 array of Magic Lantern Scalars. */
} MlTrans;


/**
 * @brief Specifies a transform, used to define a transformatin of a 3D object.
 *
 * The <b>MlTransform</b> class manages a 4x3 affine matrix of floating-point elements.
 */
class MLMATH_API MlTransform 
{ 
  public:
    
    /**
	 * Default constructor.
	  */
    MlTransform() {}
    
    /**
	 * @brief A constructor given all 12 elements in row-major order.
	 *
	 * @param a11 The m[1,1] element of the transform.
	 * @param a12 The m[1,2] element of the transform.
	 * @param a13 The m[1,3] element of the transform.
	 * @param a21 The m[2,1] element of the transform.
	 * @param a22 The m[2,2] element of the transform.
	 * @param a23 The m[2,3] element of the transform.
	 * @param a31 The m[3,1] element of the transform.
	 * @param a32 The m[3,2] element of the transform.
	 * @param a33 The m[3,3] element of the transform.
	 * @param a41 The m[4,1] element of the transform.
	 * @param a42 The m[4,3] element of the transform.
	 * @param a43 The m[4,3] element of the transform.
	 */
    MlTransform(MlScalar a11, MlScalar a12, MlScalar a13,
	        MlScalar a21, MlScalar a22, MlScalar a23,  
	        MlScalar a31, MlScalar a32, MlScalar a33,  
	        MlScalar a41, MlScalar a42, MlScalar a43);
    
    /**
	 * @brief A constructor from a 4x3 array of elements.
	 *
	 * @param m A 4x3 array of Magic Lantern Scalars.
	 */
    MlTransform(const MlTrans& m);
    
	/**
	 * @brief A constructor from a 4x3 array of elements.
	 *
	 * @param m A 4x3 array of Magic Lantern Scalars.
	 */
    MlTransform(MlScalar m[4][3]);
    
	/**
	 * @brief A constructor from a 4x4 array of elements.
	 *
	 * The last column is thrown away; i.e not used.
	 *
	 * @param m A 4x4 array of Magic Lantern Scalars.
	 */
    MlTransform(MlScalar m[4][4]);
    
    /**
	 * @brief Set the value from a 4x3 array of elements.
	 *
	 * @param m A 4x3 array of Magic Lantern Scalars.
	 */
    void setValue(const MlTrans& m);
    
  public:
    
    /**
	 * @brief Sets this matrix to be identity.
	 */
    void makeIdentity();
    
    /**
	 * @brief Get an identity matrix.
	 *
	 * @return A <b>MlTransform</b> is returned.
	 */
    static MlTransform identity();
    
    /**
	 * @brief Determine whether this matrix is an identity matrix.
	 *
	 * @return If this matrix is an identity matrix, then 1 will be returned.
	 * Otherwise 0 will be returned.
	 */
    int isIdentity() const;
    
    /**
	 * @brief Determine whether this matrix is all zeros.
	 *
	 * @return If this matrix contains all zeros, then 1 will be returned.
	 * Otherwise 0 will be returned.
	 */
    int isZero() const;
    
    /**
	 * @brief Get the value of the transform.
	 *
	 * @param m The value of the transform is returned as a 4x3 array of elements.
	 */
    void getValue(MlTrans& m) const;

	/**
	 * @brief Get the value of the transform.
	 *
	 * @return The value of the transform is returned as a 4x3 array of elements.
	 */
    const MlTrans &getValue() const
	{ return matrix; }
    
    /**
	 * @brief Calculate the determinant of the matrix.
	 *
	 * Returns determinant of 3x3 submatrix composed of given row 
     * indices (0-3).
	 *
	 * @return The determinant is returned as a Magic Lantern scalar.
	 */
    MlScalar det3(int r1, int r2, int r3) const;
    
	/**
	 * @brief Calculate the determinant of the matrix.
	 *
     * Returns determinant of upper-left 3x3 matrix.
	 *
	 * @return The determinant is returned as a Magic Lantern scalar.
	 */
    MlScalar det() const;
    
    /**
	 * @brief Deconstruct this transform matrix.
	 *
	 * This method factors a matrix m into 5 pieces: m = r s r^ u t, where <b>r^</b>
     * means transpose of <b>r</b>, and <b>r</b> and <b>u</b> are rotations, <b>s</b> is a scale,
     * and <b>t</b> is a translation. Any projection information is returned
     * in <b>proj<b>.
	 *
	 * @param r Output parameter containing a rotation matrix.
	 * @param s Output parameter containing a scaling vector.
	 * @param u Output parameter containing a rotation matrix.
	 * @param t Output parameter containing a translation vector.
	 * @param proj Output parameter containing a projection matrix.
	 */
    int	factor(MlTransform& r, MlVector3& s, MlTransform& u,
	       MlVector3& t, MlTransform& proj) const;
    
    /**
	 * @brief Calculate the inverse of the matrix.
	 *
	 * The results are undefined for singular matrices.
	 * This algorithm uses LU decompostion.
	 *
	 * @return The inverse is returned as a transform matrix.
	 */
    MlTransform	inverse() const;
    
    /**
	 * @brief Compute the tranpose of the matrix.
	 * 
	 * @return The transpose is returned as a transform matrix.
	 */
    MlTransform	transpose() const;
    
    // The following methods provide Mx/mx and mx/vec arithmetic:
    
    /**
	 * @brief Multiply this matrix by m.
	 *
	 * This method multiplies the matrix by the given matrix, m,
	 * on its right: <i>this = this *  m</i>.
	 *
	 * @param m The matrix to multiply.
	 *
	 * @return The product is returned as a transform.
	 */
    MlTransform &multRight(const MlTransform& m);

	/**
	 * @brief Multiply this matrix by m.
	 *
	 * This method multiplies the matrix by the given matrix, m,
	 * on its left: <i>this = m * this</i>.
	 *
	 * @param m The matrix to multiply.
	 *
	 * @return The product is returned as a transform.
	 */
    MlTransform &multLeft(const MlTransform& m);
    
    /**
	 * @brief Multiply this matrix by a vector.
	 *
	 * This method multiplies the matrix by a given column vector,
	 * giving a vector result.
	 *
	 * @param src The vector to multiply.
	 * @param dst The resulting vector.
	 */
    void multMatrixVec(const MlVector3& src, MlVector3& dst) const;
 
	/**
	 * @brief Multiply a vector by this matrix.
	 *
	 * This method multiplies a given row vector by this matrix,
	 * giving a vector result.
	 *
	 * @param src The vector to multiply.
	 * @param dst The resulting vector.
	 */
    void multVecMatrix(const MlVector3& src, MlVector3& dst) const;
    
	/**
	 * @brief Multiply a vector by this matrix.
	 *
     * This method multiplies a given row vector by matrix,
	 * giving a vector result.
     *
	 * @param src Assumed to be a direction vector, so translation part of
     * matrix is ignored.
	 * @param dst The resulting vector.
	 */
    void multDirMatrix(const MlVector3& src, MlVector3& dst) const;
    
    
    // The following methods are miscellaneous Mx functions:
    
#ifdef ML_REHEARSAL
    // Prints a formatted version of the matrix to the given file pointer.
    void print(FILE* fp) const;
#endif
    
    /**
	 * @brief Cast operator: returns pointer to storage of first element.
	 */
    operator MlScalar * () { return& matrix.m[0][0]; }
    
    /**
	 * @brief Cast operator: returns reference to 4x3 array.
	 */
    operator MlTrans & () { return matrix; }
    
    /**
	 * @brief Index operator.
	 *
	 * This operator makes the transform look like a usual matrix
	 * (so you can do m[i][j]).
	 */
    MlVector3 &operator [](int i)
        { return *((MlVector3*) &matrix.m[i][0]); }

	/**
	 * @brief Index operator for const versions.
	 *
	 * This operator makes the transform look like a usual matrix
	 * (so you can do m[i][j]).
	 */
    const MlVector3 &operator [] (int i) const
        { return *((MlVector3*) &matrix.m[i][0]); }
    
    /**
	 * @brief Assignment operator.
	 *
	 * Sets the value of the transform from 4x3 array of elements.
	 */
    MlTransform &operator = (const MlTrans& m);
    
	/**
	 * @brief Assignment operator.
	 *
	 * Sets the value of the transform from another transform.
	 */
    MlTransform &operator = (const MlTransform& m);

    // This silly little inline method is needed because some
    // compilers won't use the above method...
    MlTransform &operator = (MlTrans& m)
        { return (*this) = (const MlTrans& )m; }

	/**
	 * @brief Assignment operator.
	 *
	 * Sets the value of the transform from a rotation.
	 */
    MlTransform &operator = (const MlRotation& q)
        { setRotation(q); return* this; }
    
    /**
	 * @brief Multiplication operator.
	 *
	 * Performs right multiplication with another matrix,
	 * <i>this = this * m</i>.
	 *
	 * @param m The matrix to multiply this one by.
	 *
	 * @return The product of the multiplication is returned as
	 * another transform.
     */
	MlTransform &operator *= (const MlTransform& m)
        { return multRight(m); }
    
    /**
	 * @brief Binary multiplication of matrices.
	 *
	 * @return The product of the multiplication is returned as
	 * another transform.
	 */
    MLMATH_API friend MlTransform	operator * (const MlTransform& m1,
                                    const MlTransform& m2);
    
    /**
	 * @brief Equality comparison operator.
	 *
	 * @return If the matrices are equal, then 1 will be returned.
	 * Otherwise 0 will be returned.
	 */
    MLMATH_API friend int	 operator == (const MlTransform& m1, const MlTransform& m2);

	/**
	 * @brief Inequality comparison operator.
	 *
	 * @return If the matrices are not equal, then 1 will be returned.
	 * Otherwise 0 will be returned.
	 */
    MLMATH_API friend int	 operator != (const MlTransform& m1, const MlTransform& m2)
        { return !(m1 == m2); }
    
    /**
	 * @brief Equality comparison within given tolerance.
	 *
	 * The tolerance is determined by the square of the length of the maximum
	 * distance between the two transforms.
	 *
	 * @param m The other transform matrix to compare.
	 * @tolerance The tolerance value to use for equality.
	 *
	 * @return If this transform is equal to the specified matrix, m, then 1 will be returned.
	 * Otherwise 0 will be returned if the rotations are not equal.
	 */
    int	equals(const MlTransform& m, MlScalar tolerance) const;
    
    /**
	 * @brief Set the value of this transform.
	 *
     * This method sets the given transform to the matrix constructed from the given 
     * translation, fixed rotation, and scale vectors.
	 *
     * Note: This method uses scale - rotate - translate order with rotation order Z-Y-X.
	 *
	 * @param translation The translation vector.
	 * @param rotation The rotation vector.
	 * @param scale The scale vector.
	 */
    void setTransform(const MlVector3 translation, const MlVector3 rotation, 
		      const MlVector3 scale);
    
	/**
	 * @brief Set the value of this transform.
	 *
     * This method sets the given transform to the matrix constructed from the given 
     * translation, rotation, and nonuniformScale*scale vector.
	 *
     * Note: This method uses scale - rotate - translate order with rotation order Z-Y-X.
	 *
	 * @param translation The translation vector.
	 * @param rotation The rotation vector.
	 * @param nonuniformScale The nonuniform scale vector.
	 * @param scale The scale vector.
	 */
    void setTransform(const MlVector3 translation, const MlVector3 rotation, 
		      const MlVector3 nonuniformScale, MlScalar scale);
    
	/**
	 * @brief Set the value of this transform.
	 *
     * Composes the matrix based on a translation, rotation, scale,
     * orientation for scale, and center.  The "center" is the
     * center point for scaling and rotation.  The "scaleOrientation"
     * chooses the primary axes for the scale.
	 *
	 * @param translation The translation vector.
	 * @param rotation The rotation matrix.
	 * @param scaleFactor The scale vector.
	 * @param scaleRotation The scale rotation matrix.
	 * @param center The center vector.
	 */
    void setTransform(const MlVector3& translation,
		      const MlRotation& rotation,
		      const MlVector3& scaleFactor,
		      const MlRotation& scaleOrientation,
		      const MlVector3& center);
     
    // Overloaded methods as a kludge because the compiler won't let
    // us have MlVector3(0,0,0) as a default value:
    void setTransform(const MlVector3& t, const MlRotation& r,
		      const MlVector3& s)
    { setTransform(t, r, s,
		     MlRotation(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ONE), 
		     MlVector3(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO)); }

    void setTransform(const MlVector3& t, const MlRotation& r,
		      const MlVector3& s, const MlRotation& so)
    { setTransform(t, r, s, so, MlVector3(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO)); }
    
	/**
	 * @brief Deconstruct the transform.
	 *
     * Decomposes the matrix into a translation, rotation, scale,
     * and scale orientation.  Any projection information is discarded.
     * The decomposition depends upon choice of center point for
     * rotation and scaling, which is optional as the last parameter.
     * Note that if the center is 0, decompose() is the same as
     * factor() where "t" is translation, "u" is rotation, "s" is scaleFactor,
     * and "r" is ScaleOrientation.
	 *
	 * @param translation The output parameter containing the translation.
	 * @param rotation The output parameter containing the rotation.
	 * @param scaleFactor The output parameter containing the scale factor.
	 * @param scaleOrientation The output parameter containing the scale orientation.
	 * @param center The output parameter containing the center of rotation.
	 */
    void getTransform(MlVector3& translation,
		      MlRotation& rotation,
		      MlVector3& scaleFactor,
		      MlRotation& scaleOrientation,
		      const MlVector3& center) const;

	/**
	 * @brief Deconstruct the transform.
	 *
     * Decomposes the matrix into a translation, rotation, scale,
     * and scale orientation.  Any projection information is discarded.
     * The decomposition depends upon choice of center point for
     * rotation and scaling, which is optional as the last parameter.
     * Note that if the center is 0, decompose() is the same as
     * factor() where "t" is translation, "u" is rotation, "s" is scaleFactor,
     * and "r" is ScaleOrientattion.
	 *
	 * @param t The output parameter containing the translation.
	 * @param r The output parameter containing the rotation.
	 * @param s The output parameter containing the scale factor.
	 * @param so The output parameter containing the scale orientation.
	 */
    void getTransform(MlVector3& t, MlRotation& r,
		      MlVector3& s, MlRotation& so) const
	{ getTransform(t, r, s, so, MlVector3(ML_SCALAR_ZERO,ML_SCALAR_ZERO,ML_SCALAR_ZERO)); }
    
	/**
	 * @brief Get translation component of transform.
	 *
	 * @param translation The output parameter containing the translation.
	 */
    void getTranslation(MlVector3& translation);
    
	/**
	 * @brief Set translation component of transform.
	 *
	 * @param newTranslation The translation matrix given by a vector.
	 */
    void setTranslation(const MlVector3 newTranslation);
    
	/**
	 * @brief Set translation component of transform.
	 *
	 * Sets only the translation of the given transform to the X,Y,Z translations 
     * contained in the given new translation vector, without otherwise 
     * disturbing the rest of the transformation matrix.
	 *
	 * @param translation The translation matrix given by a vector.
	 */
    void setTranslationOnly(const MlVector3 translation);
    
	/**
	 * @brief Apply a translation to this transform.
	 *
	 * This method applies the given X,Y,Z translations to the existing translation
     * contained in the transform.
	 *
	 * @param translation The translation matrix given by a vector.
	 */
    void applyTranslation(const MlVector3 translation);
    
	/**
	 * @brief Get rotation component of transform.
	 *
	 * Gets the quaternion rotation contained in the transform matrix.
	 *
	 * @param rotation The output parameter containing the rotation.
	 */
    void getRotation(MlRotation& rotation);
   
	/**
	 * @brief Get rotation component of transform.
	 *
	 * Gets the X,Y,Z fixed rotations contained in the transform matrix.
	 * Note: normalizes angles to positive degrees.
	 *
	 * @param rotation The output parameter containing the rotation.
	 */
    void getRotation(MlVector3& rotation);
    
	/**
	 * @ brief Set the rotation component of the transform.
	 *
	 * Sets matrix to the rotation matrix given by the new rotation.
	 *
	 * @param newRotation The rotation to set.
	 */
    void setRotation(const MlRotation newRotation);
    
	/**
	 * @brief Set the rotation component of the transform.
	 *
	 * Sets only the rotation matrix of the transform to the rotation specified
     * by the given rotation quaternion, without otherwise disturbing the rest 
     * of the transformation matrix.
     *
	 * @param rotation The rotation matrix to set.
	 */
    void setRotationOnly(const MlRotation rotation);
    
	/**
	 * @brief Set the rotation component of the transform.
	 *
	 * Sets only the rotation matrix of the transform to the X,Y,Z fixed angle
     * rotations specified by the given rotation vector, without otherwise 
     * disturbing the rest of the transformation matrix.
	 *
	 * @param rotation The rotation vector to set.
     */
    void setRotationOnly(const MlVector3 rotation);
    
	/**
	 * @brief Apply the rotation to the transform.
	 *
	 * Applies the rotation matrix formed from given quaternion rotation
     * to the current transformation matrix.
     *
	 * @param rotation The rotation matrix to apply.
	 */
    void applyRotation(const MlRotation rotation);
    
	/**
	 * @brief Apply the rotation to the transform.
	 *
	 * Applies the rotation matrix formed from the X,Y,Z fixed angle rotations
     * to the current transformation matrix.
     *
	 * @param rotation The rotation vector to apply.
     */
    void applyRotation(const MlVector3 rotation);
    
    /**
	 * @brief Get the scale component of the transform.
	 *
	 * Gets the X,Y, and Z scales of the transformation.
	 *
	 * @param scale The output parameter containing the scale factor.
	 */
    void getScale(MlVector3& scale);
    
	/**
	 * @brief Set the scale component of the transform.
	 *
	 * Sets the new scale of the matrix to the given uniform scale.
	 *
	 * @param newScale The scale factor to set.
	 */
    void setScale(MlScalar newScale);
    
	/**
	 * @brief Set the scale component of the transform.
	 *
	 * Sets the new scale of the matrix to given nonuniform vector scale.
	 *
	 * @param newScale The nonuniform scale factors to set.
     */
    void setScale(const MlVector3 newScale);
    
	/**
	 * @brief Set the scale component of the transform.
	 *
	 * Sets only the scales of the given transform to the X,Y,Z nonuniform scales
     * contained in the given new scale vector, without otherwise disturbing the
     * rest of the transformation matrix.
	 *
	 * @param scae The nonuniform scale factors to set.
	 */
    void setScaleOnly(const MlVector3 scale);
    
    
  private:

	// Storage for the 4x3 affine matrix.
    MlTrans matrix;
    
    // Diagonalizes 3x3 matrix.
    void jacobi3(MlScalar evalues[3], MlVector3 evectors[3], int& rots) const;

};

#endif /* TRANSFRM_H_INCLUDED */
