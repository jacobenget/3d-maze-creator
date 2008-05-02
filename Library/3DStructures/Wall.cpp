/*
   Project     : 3DMaze
   File        : Wall.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : 
*/


#include "Wall.h"

using namespace std;

Wall::Wall() : 
	frontEnd(), 
	rightSide(), 
	leftSide(), 
	backEnd(), 
	top() {}

Wall::Wall( TexturedQuad & m_frontEnd, TexturedQuad & m_rightSide, TexturedQuad & m_leftSide, TexturedQuad & m_backEnd, TexturedQuad & m_top ) : 
	frontEnd( m_frontEnd ), 
	rightSide( m_rightSide ), 
	leftSide( m_leftSide ), 
	backEnd( m_backEnd ), 
	top( m_top ) {}

Wall::Wall( const Wall & rhs ) : 
	frontEnd( rhs.getFrontEnd() ), 
	rightSide( rhs.getRightSide() ), 
	leftSide( rhs.getLeftSide() ), 
	backEnd( rhs.getBackEnd() ), 
	top( rhs.getTop() ) {}


/*
 * changes the details of this wall so that it's frontEnd and backEnd Quads
 * have their centers at the end points of the given line, the wall is sitting 
 * up straight in the y-direction, and it has the given width and height
 */
void Wall::fitToLine( const LineSegment2D & line, int widthOfWall, int heightOfWall, int widthOfTexture, int heightOfTexture )
{
	//four corners of the base rectangle need to be calculated
	
	/* first calculations are to determine the coordinates of the corner
	 * that is on the same side as line.getP1(), and the line from this 
	 * to line.getP1() is 90 degrees CCW from the passed in line
	 * 
	 * so we will calculate changeInX and changeInY
	 * such that this corner is ( line.getP1().getX() + changeInx, line.getP1().getY() + changeInY)
	 */
	double changeInX;
	double changeInY;
	
	double slopeOfLine = line.slope();
	
	//if the line is horizontal
	if( slopeOfLine == 0 )
	{
		changeInX = 0;
		changeInY = widthOfWall / 2.0;
		if( ( line.getP1().getX() - line.getP2().getX() ) > 0 )
		{
			changeInY *= -1.0;
		}
	}
	//if the line is vertical
	else if ( slopeOfLine == numeric_limits<double>::max() )
	{
		changeInX = -widthOfWall / 2.0;
		if( ( line.getP1().getY() - line.getP2().getY() ) > 0 )
		{
			changeInX *= -1.0;
		}
		
		changeInY = 0;
	}
	//else if the line is neither horizontal or vertical
	else
	{
		double perpendicularSlope = -1 / slopeOfLine;
		changeInX = ( ( widthOfWall/2.0 ) * sqrt( 1 / ( 1.0 + perpendicularSlope*perpendicularSlope ) ) );
		if( ( line.getP1().getY() - line.getP2().getY() ) < 0 )
		{
			changeInX *= -1;
		}
		changeInY = perpendicularSlope * changeInX;
	}
	
	const Point2D & p1 = line.getP1();
	const Point2D & p2 = line.getP2();
	
	Point3D a1( p1.getX() + changeInX, p1.getY() + changeInY, - heightOfWall / 2.0 );
	Point3D b1( p1.getX() + changeInX, p1.getY() + changeInY, heightOfWall / 2.0 );
	Point3D c1( p1.getX() - changeInX, p1.getY() - changeInY, heightOfWall / 2.0 );
	Point3D d1( p1.getX() - changeInX, p1.getY() - changeInY, - heightOfWall / 2.0 );
	
	Point3D a2( p2.getX() - changeInX, p2.getY() - changeInY, - heightOfWall / 2.0 );
	Point3D b2( p2.getX() - changeInX, p2.getY() - changeInY, heightOfWall / 2.0 );
	Point3D c2( p2.getX() + changeInX, p2.getY() + changeInY, heightOfWall / 2.0 );
	Point3D d2( p2.getX() + changeInX, p2.getY() + changeInY, - heightOfWall / 2.0 );
	
	/* given these 8 ( a1, b1, ....., c2, d2 ) corners defining the dimensions of the wall,
	 * now construct the sides of the wall
	 */
	Quad front( a1, b1, c1, d1 );
	Quad back( a2, b2, c2, d2 );
	Quad right( d1, c1, b2, a2 );
	Quad left( d2, c2, b1, a1 );
	Quad top( b1, c2, b2, c1 );
	
	//add the coordinates for the texture that will be painted on later
	TexturedQuad frontTextured( front, heightOfTexture, widthOfTexture );
	TexturedQuad backTextured( back, heightOfTexture, widthOfTexture );
	TexturedQuad rightTextured( right, heightOfTexture, widthOfTexture );
	TexturedQuad leftTextured( left, heightOfTexture, widthOfTexture );
	TexturedQuad topTextured( top, heightOfTexture, widthOfTexture );
	
	setFrontEnd( frontTextured );
	setBackEnd( backTextured );
	setRightSide( rightTextured );
	setLeftSide( leftTextured );
	setTop( topTextured );
}


void Wall::Draw() const
{
	getFrontEnd().Draw();
	getRightSide().Draw();
	getLeftSide().Draw();
	getBackEnd().Draw();
	getTop().Draw();
}


/* returns true iff this 2D point is within the x and y range of this wall
 * ( height doesn't matter, as the point coudld be directly above the
 * wall and would still be considered to be "inside"
 */  
bool Wall::isInsideMe( const Point2D & point ) const
{
	bool pointIsInside = false;

	//point is inside this wall iff the point is to the right of every vertical
	//wall, as one walks along each wall with the inside to their right
	LineSegment2D bottomOfFrontEnd( getFrontEnd().getP4(), getFrontEnd().getP1() );
	
	if( bottomOfFrontEnd.isToTheRightOfMe( point ) )
	{
		LineSegment2D bottomOfRightSide( getRightSide().getP4(), getRightSide().getP1() );
		
		if( bottomOfRightSide.isToTheRightOfMe( point ) )
		{
			LineSegment2D bottomOfBackEnd( getBackEnd().getP4(), getBackEnd().getP1() );
			
			if( bottomOfBackEnd.isToTheRightOfMe( point ) )
			{
				LineSegment2D bottomOfLeftSide( getLeftSide().getP4(), getLeftSide().getP1() );
				
				if( bottomOfLeftSide.isToTheRightOfMe( point ) )
				{
					pointIsInside = true;
				}	
			}	
		}
	}
	
	return pointIsInside;
}


/* return the Vector2D that represents the motion that an object
 * should take after colliding with this wall while traveling
 * the path of the given "line"
 */ 
Vector2D Wall::resolveCollision( const LineSegment2D & line ) const
{
	Vector2D resolvedDirection;
	try
	{
		Vector2D wallHit = getCollisionSurface( line );
		double wallLength = wallHit.length();
		if( wallLength > 0.0 )
		{
			/* coefficient of projection of vector x onto vector y is:
			 *   ( y dot x ) / (|y| ^ 2)
			 */
			Vector2D initialTrajectory = line;
			resolvedDirection = wallHit * ( ( wallHit.dotProduct( initialTrajectory ) ) / ( wallLength * wallLength ) );
		}
		//else, if the side of the wall that we've hit has zero length
		else
		{
			resolvedDirection = Vector2D( 0.0, 0.0 );
		}
	}
	catch ( Wall::NoCollisionDetected & noCollisionError )
	{
		//if there was no collision, just return a vector representing the initial trajectory
		resolvedDirection = Vector2D( line.getP2().getX() - line.getP1().getX(), line.getP2().getY() - line.getP1().getY() );
	}
	
	return resolvedDirection;
}

void Wall::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	getFrontEnd().writeOut( out );
	getRightSide().writeOut( out );
	getLeftSide().writeOut( out );
	getBackEnd().writeOut( out );
	getTop().writeOut( out );
}

void Wall::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	frontEnd.readIn( in );
	rightSide.readIn( in );
	leftSide.readIn( in );
	backEnd.readIn( in );
	top.readIn( in );
}


/* returns the vectore that defines the base of the side of the wall that this line 
 * crosses first, when traveling from the beginning of this line to its end
 * this function throws an error is there is no such line
 */
Vector2D Wall::getCollisionSurface( const LineSegment2D & line ) const throw( Wall::NoCollisionDetected & )
{
	Point2D source = line.getP1();
	LineSegment2D closestLine;
	LineSegment2D currentSegment;
	
	/* we will now look at all 4 vertical sides of this wall
	 * and choose the side that one would collid first with 
	 * while traveling in a path from line.getP1() to line.getP2()
	 */
	double currentSourceToWallDistance = numeric_limits<double>::max();
	
	//see if one collides with the leftSide while traveling in the direction of the given line
	currentSegment = LineSegment2D( getLeftSide().getP4(), getLeftSide().getP1() );
	try
	{
		//try to get the point of intersection
		const Point2D intersection( line.getIntersection( currentSegment ) );
		Vector2D sourceToIntersection( intersection.getX() - source.getX(), intersection.getY() - source.getY() );
		
		//if this point is closer to the point of origination than any previous wall
		if( sourceToIntersection.length() < currentSourceToWallDistance )
		{
			closestLine = currentSegment;
			currentSourceToWallDistance = sourceToIntersection.length();
		}
	}
	catch ( LineSegment2D::LinesDontIntersectOnce & ignore ) { }
	

	//see if one collides with the rightSide while traveling in the direction of the given line
	currentSegment = LineSegment2D( getRightSide().getP4(), getRightSide().getP1() );
	try
	{
		//try to get the point of intersection
		const Point2D intersection( line.getIntersection( currentSegment ) );
		Vector2D sourceToIntersection( intersection.getX() - source.getX(), intersection.getY() - source.getY() );
		
		//if this point is closer to the point of origination than any previous wall
		if( sourceToIntersection.length() < currentSourceToWallDistance )
		{
			closestLine = currentSegment;
			currentSourceToWallDistance = sourceToIntersection.length();
		}
	}
	catch ( LineSegment2D::LinesDontIntersectOnce & ignore ) { }
	

	//see if one collides with the frontEnd while traveling in the direction of the given line
	currentSegment = LineSegment2D( getFrontEnd().getP4(), getFrontEnd().getP1() );
	try
	{
		//try to get the point of intersection
		const Point2D intersection = line.getIntersection( currentSegment );
		Vector2D sourceToIntersection( intersection.getX() - source.getX(), intersection.getY() - source.getY() );
		
		//if this point is closer to the point of origination than any previous wall
		if( sourceToIntersection.length() < currentSourceToWallDistance )
		{
			closestLine = currentSegment;
			currentSourceToWallDistance = sourceToIntersection.length();
		}
	}
	catch ( LineSegment2D::LinesDontIntersectOnce & ignore )  { }
	

	//see if one collides with the BackEnd while traveling in the direction of the given line
	currentSegment = LineSegment2D( getBackEnd().getP4(), getBackEnd().getP1() );
	try
	{
		//try to get the point of intersection
		const Point2D intersection( line.getIntersection( currentSegment ) );
		Vector2D sourceToIntersection( intersection.getX() - source.getX(), intersection.getY() - source.getY() );
		
		//if this point is closer to the point of origination than any previous wall
		if( sourceToIntersection.length() < currentSourceToWallDistance )
		{
			closestLine = currentSegment;
			currentSourceToWallDistance = sourceToIntersection.length();
		}
	}
	catch ( LineSegment2D::LinesDontIntersectOnce & ignore ) { }
	
	//if no intersection was found
	if( !( currentSourceToWallDistance < numeric_limits<double>::max() ) )
	{
		throw Wall::NoCollisionDetected();
	}
	
	return Vector2D( closestLine );
}
	