/*
   Project     : 3DMaze
   File        : TransformationMatrix.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 4x4 matrix that is used to describe
   				 the state of transformation of some object
*/


#include "TransformationMatrix.h"

TransformationMatrix::TransformationMatrix() 
{ 
	reset(); 
}

TransformationMatrix::TransformationMatrix( const TransformationMatrix & rhs )
{
	init( rhs );
}


/* common copying algorithm used for the copy operator and copy constructor
 */
void TransformationMatrix::init( const TransformationMatrix & rhs )
{
	const GLdouble * const rhsData = rhs.getData();
	for( int i = 0; i < ( dimension * dimension ); i++ )
	{
		matrix[ i ] = rhsData[ i ];
	}
}

const TransformationMatrix & TransformationMatrix::operator=( const TransformationMatrix & rhs )
{
	init( rhs );
	return *this;
}

const TransformationMatrix TransformationMatrix::operator*( const TransformationMatrix & rhs ) const
{
	TransformationMatrix result;
	result.setToAllZeros();
	
	for( int i = 0; i < dimension; i++ )
		for( int j = 0; j < dimension; j++ )
			for( int k= 0; k < dimension; k++ )
			{
				result.set( i, j, result.get( i, j ) + this->get( i, k ) * rhs.get( k, j ) );
			}
	return result;
}

const TransformationMatrix & TransformationMatrix::operator*=( const TransformationMatrix & rhs )
{
	this->operator =( this->operator *( rhs ) );
	return *this;
}


/* sets this transformation to be the identity transformation
 * (this becomes a transformation that does nothing)
 */
void TransformationMatrix::reset()
{
	setToAllZeros();
	for( int i = 0; i < dimension; i++ )
	{
		//have 1's down the diagonal
		set( i, i, 1.0 );
	}
}


/* sets this transformation to be the transformation
 * that rotates around the x-axis clockwise by "radians" radians
 */
void TransformationMatrix::becomeXRotation( double radians )
{
	setToAllZeros();
	
	/*		this is the matrix we will be creating:
	 * 		_										_
	 * 		|		1		0		0		0		|
	 * 		|		0		cos(r)	-sin(r)	0		|
	 * 		|		0		sin(r)	cos(r)	0		|
	 * 		|		0		0		0		1		|
	 * 		_										_
	 */
	
	set( 0, 0, 1.0 );
	set( 1, 1, cos( radians ) );
	set( 1, 2, -sin( radians ) );
	set( 2, 1, sin( radians ) );
	set( 2, 2, cos( radians ) );
	set( 3, 3, 1.0 );
}


/* sets this transformation to be the transformation
 * that rotates around the y-axis clockwise by "radians" radians
 */
void TransformationMatrix::becomeYRotation( double radians )
{
	setToAllZeros();
	
	/*		this is the matrix we will be creating:
	 * 		_										_
	 * 		|		cos(r)	0		sin(r)	0		|
	 * 		|		0		1		0		0		|
	 * 		|		-sin(r)	0		cos(r)	0		|
	 * 		|		0		0		0		1		|
	 * 		_										_
	 */
	
	set( 1, 1, 1.0 );
	set( 2, 2, cos( radians ) );
	set( 2, 0, -sin( radians ) );
	set( 0, 2, sin( radians ) );
	set( 0, 0, cos( radians ) );
	set( 3, 3, 1.0 );
}


/* sets this transformation to be the transformation
 * that rotates around the z-axis clockwise by "radians" radians
 */
void TransformationMatrix::becomeZRotation( double radians )
{
	setToAllZeros();
	
	/*		this is the matrix we will be creating:
	 * 		_										_
	 * 		|		cos(r)	-sin(r)	0		0		|
	 * 		|		sin(r)	cos(r)	0		0		|
	 * 		|		0		0		1		0		|
	 * 		|		0		0		0		1		|
	 * 		_										_
	 */
	
	set( 2, 2, 1.0 );
	set( 0, 0, cos( radians ) );
	set( 0, 1, -sin( radians ) );
	set( 1, 0, sin( radians ) );
	set( 1, 1, cos( radians ) );
	set( 3, 3, 1.0 );
}


/* sets a specific value of this matrix
 * ( while protecting against writing outside of the matrix due to bounds )
 */
void TransformationMatrix::set( int row, int column, GLdouble value )
{
	if( ( row >= 0 ) && ( row < dimension ) && ( column >= 0 ) && ( column < dimension ) )
	{
		matrix[ getIndex( row, column ) ] = value;
	}
}


/* gets a specific value of this matrix
 * ( while protecting against reading outside of the matrix due to bounds )
 */
GLdouble TransformationMatrix::get( int row, int column ) const
{
	if( ( row >= 0 ) && ( row < dimension ) && ( column >= 0 ) && ( column < dimension ) )
	{
		return matrix[ getIndex( row, column ) ];
	}
	else
	{
		return NAN;
	}
}


/* sets all 16 entries of the matrix to zero
 */
void TransformationMatrix::setToAllZeros()
{
	for( int i = 0; i < ( dimension * dimension ); i++ )
	{
		matrix[ i ] = 0.0;
	}
}