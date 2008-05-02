/*
   Project     : 3DMaze
   File        : Point2D.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 2 dimensional point
*/


#ifndef POINT2D_H_
#define POINT2D_H_

#include <iostream>
#include <math.h>

#include "IOError.h"
#include "Serializable.h"

class Point2D : public Serializable
{
	public:
		Point2D( double m_x = 0.0, double m_y = 0.0 );
		Point2D( const Point2D & otherPoint );
		virtual ~Point2D() {}
		
		double getX() const { return x; }
		double getY() const { return y; }
		void setX( double m_x ) { x = m_x; }
		void setY( double m_y ) { y = m_y; }
		
		virtual const Point2D & operator=( const Point2D & rhs );
		
		/* returns the distance between two points
		 */
		virtual double distanceTo( const Point2D & otherPoint ) const;
		
		//inherited from Serializable
		virtual void readIn( std::istream & in = std::cin ) throw( IOError & );
		virtual void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "2D Point";}
	
	private:
		double x;
		double y;
		
};

std::ostream & operator<<( std::ostream & os, const Point2D & p );
std::istream & operator>>( std::istream & in, Point2D & p );

#endif /*POINT2D_H_*/
