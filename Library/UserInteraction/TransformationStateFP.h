/*
   Project     : 3DMaze
   File        : TransformationStateFP.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Describes the total current transformation
   				 for a situation where the world is being
   				 explored in a First Person perspective.
   				 This calculates the player's movement
   				 step by step as time passes
*/


#ifndef TRANSFORMATIONSTATEFP_H_
#define TRANSFORMATIONSTATEFP_H_

#ifdef HOST_OS_MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>

#include "Maze3D.h"
#include "Vector2D.h"
#include "UserInteractionStateFP.h"
#include "ConversionFunctions.h"

class TransformationStateFP
{
	public:
		TransformationStateFP( GLdouble m_walkForwardVelocity,
							   GLdouble m_strafeVelocity,
							   GLdouble m_jumpVelocity,
							   GLdouble m_bufferDistance = 0.0,
							   GLdouble m_tiltAngleDegrees = 0.0, 
							   GLdouble m_spinAngleDegrees = 0.0,
							   GLdouble m_xPositionOffset = 0.0,
							   GLdouble m_yPositionOffset = 0.0,
							   GLdouble m_zPositionOffset = 0.0 );
		
		GLdouble getTiltAngleDegrees() const { return tiltAngleDegrees; }
		GLdouble getSpinAngleDegrees() const { return spinAngleDegrees; }
		
		GLdouble getXPositionOffset() const { return xPositionOffset; }
		GLdouble getYPositionOffset() const { return yPositionOffset; }
		GLdouble getZPositionOffset() const { return zPositionOffset; }
		
		
		void lookUp( GLdouble degrees );
		void lookDown( GLdouble degrees );
		void lookRight( GLdouble degrees );
		void lookLeft( GLdouble degrees );
		
		/* the user will jump into the air
		 * the speed of his fall will depend on gravity settings
		 */
		void jump();
		
		/* recalculates all values defining the users position and viewing angle
		 * bases on the given UserInteractionState passed in
		 * This function uses the given Maze3D to find and resolve possible physical collisions
		 */
		void updatePosition( const Maze3D & maze, const UserInteractionStateFP & state );
								
	private:
		const GLdouble walkForwardVelocity;
		const GLdouble strafeVelocity;
		const GLdouble jumpVelocity;
		
		GLdouble currentYVelocity;
		
		const GLdouble bufferDistance;
		
		GLdouble tiltAngleDegrees;
		GLdouble spinAngleDegrees;
		GLdouble xPositionOffset;
		GLdouble yPositionOffset;
		GLdouble zPositionOffset;
		
		static GLdouble minTiltAngle()	{	return -90.0; }
		static GLdouble maxTiltAngle()	{	return 90.0; }
		static GLdouble gravity()	{	return -.08; }
		
		/* return the Vector2D that represents the motion that an object
		 * should take after possibly colliding with a wall in "maze" while traveling
		 * the path from point "source" to "destination"
		 * ( this takes in account the fact that collision with more than one wall is possible )
		 */ 
		static const Vector2D resolveCollision( const Point2D & source, const Point2D & destination, const Maze3D & maze );
};

#endif /*TRANSFORMATIONSTATEFP_H_*/
