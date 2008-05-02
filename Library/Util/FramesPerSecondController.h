/*
   Project     : 3DMaze
   File        : FramesPerSecondController.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Object that can be used to "wait" in order 
   				 to control the speed of rendering, to produce
   				 a constant FPS.
*/


#ifndef FRAMESPERSECONDCONTROLLER_H_
#define FRAMESPERSECONDCONTROLLER_H_

#include <ctime>

class FramesPerSecondController
{
	public:
		FramesPerSecondController( int m_fps );
		
		/* doesn't return until the time has passed
		 * when the next frame should be displayed
		 */
		void waitForNextFrame();
		
	private:
		const double secondsBetweenFrames;
		clock_t lastFrame;
		clock_t now;
};

#endif /*FRAMESPERSECONDCONTROLLER_H_*/
