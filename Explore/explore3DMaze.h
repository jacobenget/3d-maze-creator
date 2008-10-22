/*
   Project     : 3DMaze
   File        : explore3DMaze.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for exploring a 3D-maze
   				 after applying textures to its walls and floors
   				 
   				 
   				 command line syntax:
   				 
   				 explore3DMaze [ 3DMazeFileName [ floorTexture.ppm [ wallTexture.ppm ] ] ]
*/


#ifndef EXPLOREDMAZE_H_
#define EXPLOREDMAZE_H_

#ifdef HOST_OS_MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctime>

#include "Maze3D.h"
#include "PPMTexture.h"
#include "ProjectionState.h"
#include "TransformationStateFP.h"
#include "UserInteractionStateFP.h"
#include "LoadFile.h"
#include "RegisterTexture.h"
#include "FramesPerSecondController.h"

const std::string window_title = "First Person 3D Explorer for Maze Model";

const std::string default_3D_maze_file_name = "SampleMazes/sampleMaze3D";
const std::string default_floor_texture_file_name = "SampleTextures/brushed_metal3.ppm";
const std::string default_walls_texture_file_name = "SampleTextures/checker_mush.ppm";

const int exit_success = 0;

const int initial_window_width = 900;
const int initial_window_height = 900;
const int initial_window_x_position = 300;
const int initial_window_y_position = 200;

const double bkgrnd_color_r = 0.7;
const double bkgrnd_color_g = 0.7;
const double bkgrnd_color_b = 0.90;

const double global_x_tilt = -90.0;

const double fovy_angle_ratio_change = 0.985;
const double initial_fovy_angle = 90.0;
const double initial_z_coord_of_camera = 0.0;

const int z_value_of_far_clipping_plane = -1000;
const double distance_between_camera_and_near_clipping_plane = 1;
const int min_z_coord_of_camera = -200;
const int max_z_coord_of_camera = 10000;

const double incremental_angle_change = 3.0;  //in degrees
const double incremental_position_change = 2.0;
const double jump_velocity = 3.0;

//buffer between player and walls, so the walls don't clip when the user collids with them
//should NOT be larger than the width of the walls divided by incremental_position_change
const double buffer_distance = 2.0;

const int frames_per_second = 60;

const char quit_button = 'z';
const char move_forward_button = 'w';
const char move_backward_button = 's';
const char strafe_right_button = 'd';
const char strafe_left_button = 'a';
const char jump_button = ' ';
const char zoom_in_button = 'c';
const char zoom_out_button = 'r';

GLuint floorTextureNumber;
GLuint wallsTextureNumber;

Maze3D *pMaze;
ProjectionState *pStateOfProjection;
TransformationStateFP *pStateOfTransformationFP;
UserInteractionStateFP *pStateOfUserInteractionFP;

FramesPerSecondController fpsController( frames_per_second );


/* wait until the next frame has to be rendered,
 * compute the placement of the player based on current movement,
 * and then draw the textured maze
 */
void renderScene();

/* keyboard input handler for pressing a key
 * responds to key commands for movement,
 * changing perspective, and quiting
 */
void keyPressed( unsigned char key, int x, int y );

/* keyboard input handler for letting up on a key
 * responds to key commands for movement,
 * and changing perspective
 */
void keyReleased( unsigned char key, int x, int y );

/* rotates the world based on user input with the mouse
 */
void mouseMoved( int x, int y );

/* computes the viewing frustum
 * given the current state of affairs
 */
void computeFrustum();

/* change size handler...
 * lets the user resize  the window 
 * but keeps everything in the correct perspective
 */
void windowChangedSize( int width, int height );


/* this handles all intialization:
 * setting up global variables,
 * reading in files,
 * and the loading of textures
 */
void initEnvironment( int argc, char ** argv ) throw( UserWishesToExitException & )
{
	pMaze = new Maze3D();
	pStateOfUserInteractionFP = new UserInteractionStateFP();
	pStateOfProjection = new ProjectionState( initial_fovy_angle,
											  initial_z_coord_of_camera, 
											  initial_window_width,
											  initial_window_height,
											  z_value_of_far_clipping_plane,
											  distance_between_camera_and_near_clipping_plane,
											  fovy_angle_ratio_change,
											  min_z_coord_of_camera,
											  max_z_coord_of_camera );
	
	pStateOfTransformationFP = new TransformationStateFP( incremental_position_change,
														  incremental_position_change,
														  jump_velocity, 
														  buffer_distance );
		
	std::string maze3DfileName = default_3D_maze_file_name;
	std::string floorTextureFileName = default_floor_texture_file_name;
	std::string wallsTextureFileName = default_walls_texture_file_name;
		
	//try to load in the 3-D maze from a file
	if( argc > 1 )
	{ 
		maze3DfileName = argv[ 1 ];
	}
  	
  	//may throw an exception which signals that the user wishes to quit
	LoadFile( maze3DfileName, *pMaze );
	
	//try to lead in the floorTexture
	if( argc > 2  )
  	{
  		floorTextureFileName = argv[ 2 ];
  	}
  	
  	//may throw an exception which signals that the user wishes to quit
	PPMTexture * floorTexture = new PPMTexture();
	LoadFile( floorTextureFileName, *floorTexture );
	//register the floor texture
	floorTextureNumber = RegisterTexture( *floorTexture );
	delete floorTexture;
	
  	//try to read in the wall texture
	if( argc > 3 )
  	{
  		wallsTextureFileName = argv[3];
  	}
  	
  	//may throw an exception which signals that the user wishes to quit
	PPMTexture * wallsTexture = new PPMTexture();
	LoadFile( wallsTextureFileName, *wallsTexture );
	//register the wall texture
	wallsTextureNumber = RegisterTexture( *wallsTexture );
	delete wallsTexture;
}

/* this is the inverse of initialization:
 * dynamically allocated static variables are released
 */
void ReleaseStaticVariables()
{
	delete pMaze;
	delete pStateOfProjection;
	delete pStateOfTransformationFP;
	delete pStateOfUserInteractionFP;
}

#endif /*EXPLOREDMAZE_H_*/
