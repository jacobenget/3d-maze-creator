/*
   Project     : 3DMaze
   File        : UserInteractionStateFP.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Describes how the user is interacting with the model
   				 in the case that they are exploring the model
   				 in a First Person manner
*/


#include "UserInteractionStateFP.h"

UserInteractionStateFP::UserInteractionStateFP() :
	lastMousePosition(),
	movingForward( false ),
	movingBackward( false ),
	strafingRight( false ),
	strafingLeft( false ),
	zoomingIn( false ),
	zoomingOut( false ) {}



/* update the stored mouse position
 */	
void UserInteractionStateFP::setLastMousePosition( int x, int y )
{
	lastMousePosition.setX( x );
	lastMousePosition.setY( y );
}



/* determine whether or not the user moved the mouse
 * in a certain direction based on the mouses old position
 * and where the mouse is now
 */
bool UserInteractionStateFP::mouseMovedRight( int currentX ) const
{
	return ( lastMousePosition.getX() < currentX );
}

bool UserInteractionStateFP::mouseMovedLeft( int currentX ) const
{
	return ( lastMousePosition.getX() > currentX );
}

bool UserInteractionStateFP::mouseMovedUp( int currentY ) const
{
	return ( lastMousePosition.getY() > currentY );
}

bool UserInteractionStateFP::mouseMovedDown( int currentY ) const
{
	return ( lastMousePosition.getY() < currentY );
}
