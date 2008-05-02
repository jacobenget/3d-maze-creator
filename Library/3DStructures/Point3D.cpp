/*
   Project     : 3DMaze
   File        : Point3D.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 3-dimensional point
*/


#include "Point3D.h"

using namespace std;

Point3D::Point3D( double m_x /* = 0.0 */, double m_y /* = 0.0 */, double m_z /* = 0.0 */ ) : 
	Point2D( m_x, m_y ), 
	z( m_z ) {}

Point3D::Point3D( const Point3D & otherPoint ) : 
	Point2D( otherPoint.getX(), otherPoint.getY() ), 
	z( otherPoint.getZ() ) {}

const Point3D & Point3D::operator=( const Point3D & rhs )
{
	if( this != &rhs )
	{
		Point2D::operator=( rhs );
		setZ( rhs.getZ() );
	}
	return *this;
}

void Point3D::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	Point2D::readIn( in );
	double z;
	in >> z;
	setZ( z );
}

void Point3D::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	Point2D::writeOut( out );
	out << " " << getZ();
}


/* returns the distance between two points
 */
double Point3D::distanceTo( const Point3D & otherPoint ) const
{
	double xDistance = getX() - otherPoint.getX();
	double yDistance = getY() - otherPoint.getY();
	double zDistance = getZ() - otherPoint.getZ();
	return sqrt( ( xDistance*xDistance ) + ( yDistance*yDistance ) + ( zDistance*zDistance ) );
}

ostream & operator<<( ostream & out, const Point3D & p )
{
	p.writeOut( out );
	return out;
}

istream & operator>>( istream & in, Point3D & p )
{
	p.readIn( in );
	return in;
}