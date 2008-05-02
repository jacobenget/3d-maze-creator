/*
   Project     : 3DMaze
   File        : UserInteractionState.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Describes how the user is interacting with the model
   				 in the case when the user is interacting with the
   				 model from afar.
*/


#ifndef USERINTERACTIONSTATE_H_
#define USERINTERACTIONSTATE_H_

#include "Point2D.h"

class UserInteractionState
{
	public:
		UserInteractionState();
		
		bool isRotating() { return ( state == rotating ); }
		bool isScaling() { return ( state == scaling ); }
		bool isTranslating() { return ( state == translating ); }
		bool isStretching() { return ( state == stretching ); }
		
		void setRotating() { state = rotating; }
		void setScaling() { state = scaling; }
		void setTranslating() { state = translating; }
		void setStretching() { state = stretching; }
		
		void reset() { state = noAction; }
		
		/* update the stored mouse position
		 */
		void setLastMousePosition( int x, int y );
		
		/* determine whether or not the user moved the mouse
		 * in a certain direction based on the mouses old position
		 * and where the mouse is now
		 */
		bool movedMouseRight( int currentX ) const;
		bool movedMouseLeft( int currentX ) const;
		bool movedMouseUp( int currentY ) const;
		bool movedMouseDown( int currentY ) const;
		
	private:
		int state;
		Point2D lastMousePosition;
		
		static const int rotating = 1;
		static const int scaling = 2;
		static const int translating = 3;
		static const int stretching = 4;
		static const int noAction = 0;
};

#endif /*USERINTERACTIONSTATE_H_*/
