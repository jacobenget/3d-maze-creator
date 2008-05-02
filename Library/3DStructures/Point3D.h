/*
   Project     : 3DMaze
   File        : Point3D.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 3-dimensional point
*/


#ifndef POINT3D_H_
#define POINT3D_H_

#include <iostream>
#include <math.h>
#include "Serializable.h"
#include "IOError.h"
#include "Point2D.h"

class Point3D : public Point2D
{
	public:
		Point3D( double m_x = 0.0, double m_y = 0.0, double m_z = 0.0 );
		Point3D( const Point3D & otherPoint );
		
		double getZ() const { return z; }
		void setZ( double m_z ) { z = m_z; }
		
		const Point3D & operator=( const Point3D & rhs );
		
		/* returns the distance between two points
		 */
		double distanceTo( const Point3D & otherPoint ) const;
		
		//inherited from Serializable
		void readIn( std::istream & in = std::cin ) throw( IOError & );
		void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "3D Point";}
	
	private:
		double z;
		
};

std::ostream & operator<<( std::ostream & os, const Point3D & p );
std::istream & operator>>( std::istream & in, Point3D & p );

#endif /*POINT3D_H_*/
