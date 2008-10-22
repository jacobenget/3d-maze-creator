/*
   Project     : 3DMaze
   File        : FramesPerSecondController.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Object that can be used to "wait" in order 
   				 to control the speed of rendering, to produce
   				 a constant FPS
*/


#include "FramesPerSecondController.h"

#include <iostream>

FramesPerSecondController::FramesPerSecondController( int m_fps ) :
	secondsBetweenFrames( 1.0 / m_fps ),
	lastFrame( clock() ),
	now( clock() ) {}



/* doesn't return until the time has passed
 * when the next frame should be displayed
 */
void FramesPerSecondController::waitForNextFrame()
{
	//store the current time
	now = clock();
	
	/* wait until the time between now and the time we displayed 
	 * the last frame is large enough to guarantee a constant FPS
	 */
	while( ( double( now - lastFrame ) / CLOCKS_PER_SEC ) < secondsBetweenFrames )
	{
		now = clock();
	}
	
	//reset the lastFrame time to be now
	lastFrame = now;
}
