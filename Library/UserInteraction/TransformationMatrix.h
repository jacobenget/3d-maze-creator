/*
   Project     : 3DMaze
   File        : TransformationMatrix.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 4x4 matrix that is used to describe
   				 the state of transformation of some object
*/


#ifndef TRANSFORMATIONMATRIX_H_
#define TRANSFORMATIONMATRIX_H_

#include <math.h>
#include <GLUT/glut.h>

class TransformationMatrix
{	
	public:
		TransformationMatrix();
		TransformationMatrix( const TransformationMatrix & rhs );
		
		const TransformationMatrix & operator=( const TransformationMatrix & rhs );
		const TransformationMatrix operator*( const TransformationMatrix & rhs ) const;
		const TransformationMatrix & operator*=( const TransformationMatrix & rhs ); 
		
		/* sets this transformation to be the identity transformation
		 * (this becomes a transformation that does nothing)
		 */
		void reset();
		
		/* sets this transformation to be the transformation
		 * that rotates around the x-axis clockwise by "radians" radians
		 */
		void becomeXRotation( double radians );
		
		/* sets this transformation to be the transformation
		 * that rotates around the y-axis clockwise by "radians" radians
		 */
		void becomeYRotation( double radians );
		
		/* sets this transformation to be the transformation
		 * that rotates around the z-axis clockwise by "radians" radians
		 */
		void becomeZRotation( double radians );
		
		/* returns the guts of this transformation in a one dimensional
		 * array (COLUMN major ordering)
		 * this is the format for transformations that openGL can best deal with
		 */
		const GLdouble * const getData() const { return matrix; }
		
		/* sets a specific value of this matrix
		 * ( while protecting against writing outside of the matrix due to bounds )
		 */
		void set( int row, int column, GLdouble value );
		
		/* gets a specific value of this matrix
		 * ( while protecting against reading outside of the matrix due to bounds )
		 */
		GLdouble get( int row, int column ) const;
		
	private:
		static const int dimension = 4;
		
		//column major ordering!!!!
		static int getIndex( int row, int column )
			{	return ( dimension * ( column ) ) + row; }
		
		GLdouble matrix[ dimension * dimension ];
		
		/* common copying algorithm used for the copy operator and copy constructor
		 */
		void init( const TransformationMatrix & rhs );
		
		/* sets all 16 entries of the matrix to zero
		 */
		void setToAllZeros();
};

#endif /*TRANSFORMATIONMATRIX_H_*/
