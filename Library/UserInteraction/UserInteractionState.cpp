/*
   Project     : 3DMaze
   File        : UserInteractionState.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Describes how the user is interacting with the model
   				 in the case when the user is interacting with the
   				 model from afar.
*/


#include "UserInteractionState.h"

UserInteractionState::UserInteractionState() : state( noAction ), lastMousePosition() {}


/* update the stored mouse position
 */
void UserInteractionState::setLastMousePosition( int x, int y )
{
	lastMousePosition.setX( x );
	lastMousePosition.setY( y );
}


/* determine whether or not the user moved the mouse
 * in a certain direction based on the mouses old position
 * and where the mouse is now
 */
bool UserInteractionState::movedMouseRight( int currentX ) const
{
	return ( lastMousePosition.getX() < currentX );
}

bool UserInteractionState::movedMouseLeft( int currentX ) const
{
	return ( lastMousePosition.getX() > currentX );
}

bool UserInteractionState::movedMouseUp( int currentY ) const
{
	return ( lastMousePosition.getY() > currentY );
}

bool UserInteractionState::movedMouseDown( int currentY ) const
{
	return ( lastMousePosition.getY() < currentY );
}
