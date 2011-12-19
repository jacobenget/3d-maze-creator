/*
   Project     : 3DMaze
   File        : LineSegment2D.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a segment of a two dimensional line,
   				 this line can be represented by two end points
*/


#include "LineSegment2D.h"
#include "Vector2D.h"

using namespace std;

LineSegment2D::LineSegment2D() :
	p1(),
	p2() {}


LineSegment2D::LineSegment2D( const Point2D & m_p1, const Point2D & m_p2 ) : 
	p1( m_p1 ), 
	p2( m_p2 ) {}


LineSegment2D::LineSegment2D( const LineSegment2D & otherLine ) : 
	p1( otherLine.getP1() ), 
	p2( otherLine.getP2() ) {}

const LineSegment2D & LineSegment2D::operator=( const LineSegment2D & rhs )
{
	if( this != &rhs )
	{
		p1 = rhs.getP1();
		p2 = rhs.getP2();
	}
	return *this;
}


/* returns true iff as one travels along this line
 * ( from p1 to p2 ) the point in question is to their right
 * ( notice: if the point is on this line, this returns false )
 */
bool LineSegment2D::isToTheRightOfMe( const Point2D & point ) const
{
	// the cross product of the vector for this line and the vector from the start of this line and the point
	// points in the direction of the negative z-axis if and only if the point is to the right of the line

	// so compute the z-coordinate of the cross product and check if it's greater than zero
	Vector2D lineVector( *this );
	Vector2D pointToLineVector( point.getX() - getP1().getX(), point.getY() - getP1().getY() );

	double zCoordOfCrossProduct = ( ( lineVector.getX() * pointToLineVector.getY() ) - ( lineVector.getY() * pointToLineVector.getX() ) );

	return ( zCoordOfCrossProduct < 0 );
}


/* returns the point of intersection between two lines segments,
 * throws an exception if the lines are parallel or don't intersect
 */
Point2D LineSegment2D::getIntersection( const LineSegment2D & line ) const throw( LineSegment2D::LinesDontIntersectOnce & )
{
	//get the intersection of the two lines, assuming they aren't segments
	//( this might throw an error, which is ok, we'll let the error propagate up )
	Point2D intersection( getIntersectionExtended( line ) ); 
	
	//now check to see if this intersecting point lies within both of these lines
	//( this accounts for the fact that these lines ARE segments )
	if( pointWithinBoundingBox( intersection ) )
	{
		if( line.pointWithinBoundingBox( intersection ) )
		{
			return intersection;
		}
	}
	
	//if this line doesn't lie within either one of these lines, throw an exception
	throw LinesDontIntersectOnce();
}

void LineSegment2D::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	p1.readIn( in );
	p2.readIn( in );
}

void LineSegment2D::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	out << getP1() << "      " << getP2();
}

//returns the slope of the line
double LineSegment2D::slope() const
{
	double deltaY = getP2().getY() - getP1().getY();
	double deltaX = getP2().getX() - getP1().getX();
	if( deltaX != 0 )
	{
		return ( deltaY )/( deltaX );
	}
	else
	{
		return numeric_limits<double>::max();
	}
}


/* returns the point of intersection between two lines segments
 * AS IF they were considered to not be segments,
 * and instead were infinitely long
 * throws an exception if the lines are parallel
 */
Point2D LineSegment2D::getIntersectionExtended( const LineSegment2D & line ) const throw( LineSegment2D::LinesDontIntersectOnce & )
{
	Vector2D otherLineVector( line );
	Vector2D perpendicularVector( p1.getY() - p2.getY(), p2.getX() - p1.getX() );

	double dotProduct = otherLineVector.dotProduct( perpendicularVector );

	//first, check to make sure the lines aren't parallel
	if( dotProduct == 0.0 )
	{
		throw LinesDontIntersectOnce();
	}

	Vector2D firstLineToSecond( p1.getX() - line.getP1().getX(), p1.getY() - line.getP1().getY() );
	double t = ( firstLineToSecond.dotProduct( perpendicularVector ) ) / dotProduct;

	return Point2D( line.getP1().getX() + ( otherLineVector.getX() * t ), line.getP1().getY() + ( otherLineVector.getY() * t ) );
}


/* returns true iff the point lies within the smallest rectanlge
 * that bounds this line segment and is parallel to the x axis
 */ 
bool LineSegment2D::pointWithinBoundingBox( const Point2D & point ) const
{
	double x = point.getX();
	double y = point.getY();
	
	bool withinBox = false;
	
	bool betweenX1andX2 = withinBounds( x, getP1().getX(), getP2().getX() );
	bool betweenX2andX1 = withinBounds( x, getP2().getX(), getP1().getX() );
	
	bool betweenY1andY2 = withinBounds( y, getP1().getY(), getP2().getY() );
	bool betweenY2andY1 = withinBounds( y, getP2().getY(), getP1().getY() );
	
	//if the point is within the X bounds of this line
	if( betweenX1andX2 || betweenX2andX1 )
	{
		//if the point is within the Y bounds of this line
		if( betweenY1andY2 || betweenY2andY1 )
		{
			withinBox = true;
		}
	}
	
	return withinBox;
}


/* computes the determinant of the 2x2 matrix:
 * 		|	a	b	|
 * 		|	c	d	|
 */
double LineSegment2D::determinant( double a, double b, double c, double d )
{
	return ( a * d ) - ( c * b );
}

/* returns true iff x lies within [ a, b ]
 * while being a little lenient due to possible rounding
 */
bool LineSegment2D::withinBounds( double x, double a, double b )
{
	const double smudgeFactor = 0.001;
	return ( ( x >= ( a - smudgeFactor ) ) && ( x <= ( b + smudgeFactor ) ) ); 
}
