/*
   Project     : 3DMaze
   File        : Vector2D.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 2 dimensional vector
*/


#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <math.h>
#include "LineSegment2D.h"

class Vector2D
{
	public:
		Vector2D( double m_x = 0.0, double m_y=0.0 );
		Vector2D( const Vector2D & rhs );
		Vector2D( const LineSegment2D & line );
		
		const Vector2D & operator=( const Vector2D & rhs );
		const Vector2D operator+( const Vector2D & rhs ) const;
		const Vector2D & operator+=( const Vector2D & rhs );
		const Vector2D operator*( double scalar ) const;
		
		double getX() const { return x; }
		double getY() const { return y; }
		
		void setX( double newX ) { x = newX; }
		void setY( double newY ) { y = newY; }
		
		/* returns the length of this vector
		 */
		double length() const;
		
		/* returns the dot product of two vectors
		 */
		double dotProduct( const Vector2D & rhs ) const;
		
		
	private:
		double x;
		double y;
};

#endif /*VECTOR2D_H_*/
