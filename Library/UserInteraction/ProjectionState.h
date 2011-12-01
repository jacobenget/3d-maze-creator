/*
   Project     : 3DMaze
   File        : ProjectionState.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents the current state through which any
   				 3D structures is being projected onto the user's screen
*/


#ifndef PROJECTIONSTATE_H_
#define PROJECTIONSTATE_H_

#include <QtOpenGL>

#include "ConversionFunctions.h"

class ProjectionState
{
	public:
		ProjectionState( GLdouble i_fovyAngle,
						 GLdouble i_cameraZPosition,
						 int i_zCoordFarClippingPlane,
						 int i_cameraToNearClippingPlane,
						 double i_fishEyeRatioChange,
						 int i_minCameraZCoord,
						 int i_maxCameraZCoord );
		
		void setWidthOfScreen( int m_width ) { widthOfScreen = m_width; }
		void setHeightOfScreen( int m_height ) { heightOfScreen = m_height; }
		
		GLdouble getAspectRatio() const { return ( GLdouble )widthOfScreen/ ( GLdouble )heightOfScreen; }
		GLdouble getCameraZPosition() const { return cameraZPosition; }
		GLdouble getFovyAngle()	const { return fovyAngle; }
		
		/* increse the camera angle so that peripheral object come into view
		 * this gives the effect of zooming out
		 */
		void increaseFishEyeEffect();
		
		/* decrese the camera angle so that peripheral object move out of view
		 * this gives the effect of zooming in
		 */
		void decreaseFishEyeEffect();
		
		GLdouble getCameraDistanceToNearClippingPlane() { return cameraToNearClippingPlane; }
		GLdouble getCameraDistanceToFarClippingPlane() { return cameraZPosition - zCoordFarClippingPlane; }
		
		void setFovyAngle( GLdouble newFovyAngle ) { fovyAngle = newFovyAngle; }
		void setCameraZPosition( GLdouble newCameraZPosition ) { cameraZPosition = newCameraZPosition; }
		
	private:
		GLdouble fovyAngle, cameraZPosition;
		int widthOfScreen, heightOfScreen;

		const int zCoordFarClippingPlane;
		const int cameraToNearClippingPlane;
		const double fishEyeRatioChange;
		const int minCameraZCoord;
		const int maxCameraZCoord;
};

#endif /*PROJECTIONSTATE_H_*/
