/*
   Project     : 3DMaze
   File        : Vector2D.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 2 dimensional vector
*/


#include "Vector2D.h"

Vector2D::Vector2D( double m_x, double m_y ) :
	x( m_x ),
	y( m_y ) {}

Vector2D::Vector2D( const Vector2D & rhs ) :
	x( rhs.getX() ),
	y( rhs.getY() ) {}

Vector2D::Vector2D( const LineSegment2D & line ) :
	x( line.getP2().getX() - line.getP1().getX() ),
	y( line.getP2().getY() - line.getP1().getY() ) {}

const Vector2D & Vector2D::operator=( const Vector2D & rhs )
{
	if( this != &rhs )
	{
		setX( rhs.getX() );
		setY( rhs.getY() );
	}
	return *this;
}

const Vector2D Vector2D::operator+( const Vector2D & rhs ) const
{
	Vector2D sum( this->getX() + rhs.getX(), this->getY() + rhs.getY() );
	return sum;
}

const Vector2D & Vector2D::operator+=( const Vector2D & rhs )
{
	setX( this->getX() + rhs.getX() );
	setY( this->getY() + rhs.getY() );
	return *this;
}

const Vector2D Vector2D::operator*( double scalar ) const
{
	Vector2D sum( scalar * this->getX(), scalar * this->getY() );
	return sum;
}


/* returns the length of this vector
 */
double Vector2D::length() const
{
	return sqrt( lengthSquared() );
}


/* returns the length of this vector
 */
double Vector2D::lengthSquared() const
{
	return ( getX() * getX() ) + ( getY() * getY() );
}


/* noramlizes the vector to its length is 1
 */
void Vector2D::normalize()
{
	double vectorLength = length();
	x /= vectorLength;
	y /= vectorLength;
}


/* returns the dot product of two vectors
 */
double Vector2D::dotProduct( const Vector2D & rhs ) const
{
	return ( this->getX() * rhs.getX() ) + ( this->getY() * rhs.getY() );
}


