/*
   Project     : 3DMaze
   File        : UserInteractionStateFP.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Describes how the user is interacting with the model
   				 in the case that they are exploring the model
   				 in a First Person manner
*/


#ifndef USERINTERACTIONSTATEFP_H_
#define USERINTERACTIONSTATEFP_H_

#include "Point2D.h"

class UserInteractionStateFP
{
	public:
		UserInteractionStateFP();
		
		void setMovingForward( bool newState ) { movingForward = newState; }
		void setMovingBackward( bool newState ) { movingBackward = newState; }
		void setStrafingRight( bool newState ) { strafingRight = newState; }
		void setStrafingLeft( bool newState ) { strafingLeft = newState; }
		void setZoomingIn( bool newState ) { zoomingIn = newState; }
		void setZoomingOut( bool newState ) { zoomingOut = newState; }
		
		bool isMovingForward() const { return movingForward; }
		bool isMovingBackward() const { return movingBackward; }
		bool isStrafingRight() const { return strafingRight; }
		bool isStrafingLeft() const { return strafingLeft; }
		bool isZoomingIn() const { return zoomingIn; }
		bool isZoomingOut() const { return zoomingOut; }
		
		/* update the stored mouse position
		 */
		void setLastMousePosition( int x, int y );
		
		/* determine whether or not the user moved the mouse
		 * in a certain direction based on the mouses old position
		 * and where the mouse is now
		 */
		bool mouseMovedRight( int currentX ) const;
		bool mouseMovedLeft( int currentX ) const;
		bool mouseMovedUp( int currentY ) const;
		bool mouseMovedDown( int currentY ) const;
		
	private:
		Point2D lastMousePosition;
		
		bool movingForward;
		bool movingBackward;
		bool strafingRight;
		bool strafingLeft;
		bool zoomingIn;
		bool zoomingOut;
};

#endif /*USERINTERACTIONSTATEFP_H_*/
