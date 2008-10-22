/*
   Project     : 3DMaze
   File        : Point2D.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 2 dimensional point
*/


#include "Point2D.h"

using namespace std;

Point2D::Point2D( double m_x /* = 0.0 */, double m_y /* = 0.0 */ ): 
	x( m_x ), 
	y( m_y ) {}

Point2D::Point2D( const Point2D & otherPoint ) : 
	x( otherPoint.getX() ), 
	y( otherPoint.getY() ) {}

const Point2D & Point2D::operator=( const Point2D & rhs )
{
	if( this != &rhs )
	{
		setX( rhs.getX() );
		setY( rhs.getY() );
	}
	return *this;
}

void Point2D::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	double x, y;
	in >> x >> y;
		
	setX( x );
	setY( y );
}

void Point2D::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	out << getX() << " " << getY();
}


/* returns the distance between two points
 */
double Point2D::distanceTo( const Point2D & otherPoint ) const
{
	double xDistance = getX() - otherPoint.getX();
	double yDistance = getY() - otherPoint.getY();
	return sqrt( ( xDistance*xDistance ) + ( yDistance*yDistance ) );
}


ostream & operator<<( ostream & out, const Point2D & p )
{
	p.writeOut( out );
	return out;
}

istream & operator>>( istream & in, Point2D & p )
{
	p.readIn( in );
	return in;
}
