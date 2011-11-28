/*
   Project     : 3DMaze
   File        : LineSegment2D.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a segment of a two dimensional line,
   				 this line can be represented by two end points
*/


#ifndef LineSegment2D_H_
#define LineSegment2D_H_

#include <iostream>
#include <limits>

#include "Point2D.h"
#include "Serializable.h"
#include "IOError.h"

class LineSegment2D : public Serializable
{
	public:
		class LinesDontIntersectOnce
		{
			public:
				LinesDontIntersectOnce() {}
		};
		
		LineSegment2D();
		LineSegment2D( const Point2D & m_p1, const Point2D & m_p2 );
		LineSegment2D( const LineSegment2D & otherLine );
		
		const Point2D & getP1() const { return p1; }
		const Point2D & getP2() const { return p2; }
		
		void setP1( const Point2D & m_p1 ) { p1 = m_p1; }
		void setP2( const Point2D & m_p2 ) { p2 = m_p2; }
		
		const LineSegment2D & operator=( const LineSegment2D & rhs );
		

		/* returns true iff as one travels along this line
		 * ( from p1 to p2 ) the point in question is to their right
		 * ( notice: if the point is on this line, this returns false )
		 */
		bool isToTheRightOfMe( const Point2D & point ) const;
		
		/* returns the point of intersection between two lines segments,
		 * throws an exception if the lines are parallel or don't intersect
		 */
		Point2D getIntersection( const LineSegment2D & line ) const throw( LineSegment2D::LinesDontIntersectOnce & );
		
		//returns the slope of the line
		double slope() const; 
		
		//inherited from Serializable
		void readIn( std::istream & in = std::cin ) throw( IOError & );
		void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "2D Line Segment"; }
	
	private:
		Point2D p1;
		Point2D p2;
		
		/* returns the point of intersection between two lines segments
		 * AS IF they were considered to not be segments,
		 * and instead were infinitely long
		 * throws an exception if the lines are parallel
		 */
		Point2D getIntersectionExtended( const LineSegment2D & line ) const throw( LineSegment2D::LinesDontIntersectOnce & );
		
		/* returns true iff the point lies within the smallest rectanlge
		 * that bounds this line segment and is parallel to the x axis
		 */ 
		bool pointWithinBoundingBox( const Point2D & point ) const;
		
		/* computes the determinant of the 2x2 matrix:
		 * 		|	a	b	|
		 * 		|	c	d	|
		 */
		static double determinant( double a, double b, double c, double d );
		
		/* returns true iff x lies within [ a, b ]
		 * while being a little lenient due to possible rounding
		 */
		static bool withinBounds( double x, double a, double b );
};

#endif /*LineSegment2D_H_*/
