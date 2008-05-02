/*
   Project     : 3DMaze
   File        : ProjectionState.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents the current state through which any
   				 3D structures is being projected onto the user's screen
*/


#include "ProjectionState.h"

ProjectionState::ProjectionState( GLdouble i_fovyAngle,
				 GLdouble i_cameraZPosition,
				 int i_widthOfScreen,
				 int i_heightOfScreen,
				 int i_zCoordFarClippingPlane,
				 int i_cameraToNearClippingPlane,
				 double i_fishEyeRatioChange,
				 int i_minCameraZCoord,
				 int i_maxCameraZCoord ) :
	fovyAngle( i_fovyAngle ),
	cameraZPosition( i_cameraZPosition ),
	widthOfScreen( i_widthOfScreen ),
	heightOfScreen( i_heightOfScreen ),
	zCoordFarClippingPlane( i_zCoordFarClippingPlane ),
	cameraToNearClippingPlane( i_cameraToNearClippingPlane ),
	fishEyeRatioChange( i_fishEyeRatioChange ),
	minCameraZCoord( i_minCameraZCoord ),
	maxCameraZCoord( i_maxCameraZCoord ) {}

void ProjectionState::increaseFishEyeEffect()
{
	if( cameraZPosition > minCameraZCoord )
	{
		//expand the fovy angle;
		fovyAngle = toDegrees( 2*atan( ( 1/fishEyeRatioChange ) * tan( toRadians( fovyAngle/2 ) ) ) );
		cameraZPosition = fishEyeRatioChange * cameraZPosition;
	}
}

void ProjectionState::decreaseFishEyeEffect()
{
	if( cameraZPosition < maxCameraZCoord )
	{
		//shrink the fovy angle;
		fovyAngle = toDegrees( 2*atan( fishEyeRatioChange * tan( toRadians( fovyAngle/2 ) ) ) );
		cameraZPosition = ( 1/fishEyeRatioChange ) * cameraZPosition;
	}
}
