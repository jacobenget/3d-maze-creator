/*
   Project     : 3DMaze
   File        : TransformationStateFP.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Describes the total current transformation
   				 for a situation where the world is being
   				 explored in a First Person perspective.
   				 This calculates the player's movement
   				 step by step as time passes
*/


#include "TransformationStateFP.h"

using namespace std;

TransformationStateFP::TransformationStateFP( GLdouble m_walkForwardVelocity,
		   									  GLdouble m_strafeVelocity,
		   									  GLdouble m_jumpVelocity,
		   									  GLdouble m_bufferDistance,
		   									  GLdouble m_tiltAngleDegrees, 
							 			   	  GLdouble m_spinAngleDegrees,
							 			   	  GLdouble m_xPositionOffset,
							 			   	  GLdouble m_yPositionOffset,
							 			   	  GLdouble m_zPositionOffset ) :
	walkForwardVelocity( m_walkForwardVelocity ),
	strafeVelocity( m_strafeVelocity ),
	jumpVelocity( m_jumpVelocity ),
	currentYVelocity( 0.0 ),
	bufferDistance( m_bufferDistance ),
	tiltAngleDegrees( m_tiltAngleDegrees ),
	spinAngleDegrees( m_spinAngleDegrees ),
	xPositionOffset( m_xPositionOffset ),
	yPositionOffset( m_yPositionOffset ),
	zPositionOffset( m_zPositionOffset ) {}

void TransformationStateFP::lookUp( GLdouble degrees )
{
	if( ( tiltAngleDegrees - degrees ) >= minTiltAngle() )
	{
		tiltAngleDegrees -= degrees;
	}
}

void TransformationStateFP::lookDown( GLdouble degrees )
{
	if( ( tiltAngleDegrees + degrees ) <= maxTiltAngle() )
	{
		tiltAngleDegrees += degrees;
	}
}

void TransformationStateFP::lookRight( GLdouble degrees )
{
	spinAngleDegrees += degrees;
}

void TransformationStateFP::lookLeft( GLdouble degrees )
{
	spinAngleDegrees -= degrees;
}



/* the user will jump into the air
 * the speed of his fall will depend on gravity settings
 */
void TransformationStateFP::jump()
{
	//only allow jumping if the user is on the ground
	if( yPositionOffset <= 0.0 )
	{
		currentYVelocity = jumpVelocity;
	}
}



/* recalculates all values defining the users position and viewing angle
 * bases on the given UserInteractionState passed in
 * This function uses the given Maze3D to find and resolve possible physical collisions
 */
void TransformationStateFP::updatePosition( const Maze3D & maze, const UserInteractionStateFP & state )
{
	//update yPositionOffset according to currentYVelocity
	yPositionOffset += currentYVelocity;
	if( yPositionOffset < 0 )
	{
		yPositionOffset = 0.0;
	}
	
	//then update currentYVelocity based on gravity
	currentYVelocity += gravity();
	if( yPositionOffset <= 0 )
	{
		currentYVelocity = 0.0;
	}
	
	double additionToX = 0.0;
	double additionToZ = 0.0;
	
	//determine where to move the character based on the UserInteractionStateFP obejct
	if( state.isMovingForward() && ( !state.isMovingBackward() ) )
	{
		additionToX += walkForwardVelocity*sin( toRadians( spinAngleDegrees ) );
		additionToZ += walkForwardVelocity*-cos( toRadians( spinAngleDegrees ) );
	}
	else if( state.isMovingBackward() && ( !state.isMovingForward() ) )
	{
		additionToX += walkForwardVelocity*sin( toRadians( spinAngleDegrees + 180 ) );
		additionToZ += walkForwardVelocity*-cos( toRadians( spinAngleDegrees + 180 ) );
	}
	
	if( state.isStrafingRight() && ( !state.isStrafingLeft() ) )
	{
		additionToX += walkForwardVelocity*sin( toRadians( spinAngleDegrees + 90 ) );
		additionToZ += walkForwardVelocity*-cos( toRadians( spinAngleDegrees + 90 ) );
	}
	else if( state.isStrafingLeft() && ( !state.isStrafingRight() ) )
	{
		additionToX += walkForwardVelocity*sin( toRadians( spinAngleDegrees - 90 ) );
		additionToZ += walkForwardVelocity*-cos( toRadians( spinAngleDegrees - 90 ) );
	}
	
	/* we want to keep a buffer between the user and the walls
	 * to aviod excessive clipping when the user hit the wall
	 */
	double bufferAdditionX = bufferDistance * additionToX;
	double bufferAdditionZ = bufferDistance * additionToZ;
	
	const Point2D source( xPositionOffset + bufferAdditionX, -( zPositionOffset + bufferAdditionZ ) );
	//the proposed destination befor collision is checked
	const Point2D destination( xPositionOffset + bufferAdditionX + additionToX, -( zPositionOffset + bufferAdditionZ + additionToZ ) );
	
	//get the resolved direction
	Vector2D resolvedDirection = resolveCollision( source, destination, maze );
	
	//now update the player's position based on the resolvedDirection
	xPositionOffset += resolvedDirection.getX();
	zPositionOffset += -resolvedDirection.getY();
}



/* return the Vector2D that represents the motion that an object
 * should take after possibly colliding with a wall in "maze" while traveling
 * the path from point "source" to "destination"
 * ( this takes in account the fact that collision with more than one wall is possible )
 */ 
const Vector2D TransformationStateFP::resolveCollision( const Point2D & source, const Point2D & destination, const Maze3D & maze )
{
	Vector2D resultantDirection;
	try
	{
		//check for a collision
		const Wall & wallThatWasHit = maze.detectCollision( destination );
		resultantDirection = wallThatWasHit.resolveCollision( LineSegment2D( source, destination ) );	
		
		Point2D resultantPoint( source.getX() + resultantDirection.getX(), source.getY() + resultantDirection.getY() );
		
		/* if the resultant direction from this first collision is one that 
		 * still makes the player collide with a second wall
		 * make it so the player doesn't move at all.
		 */
		try
		{
			maze.detectCollision( resultantPoint );
			resultantDirection = Vector2D( 0.0, 0.0 );
		}
		catch ( Wall::NoCollisionDetected & ignore ) { }
	}
	catch ( Wall::NoCollisionDetected & nc )
	{
		//if no collicion was detected in the first place
		resultantDirection = Vector2D( destination.getX() - source.getX(), destination.getY() - source.getY()  );
	}
	
	return resultantDirection;
}


