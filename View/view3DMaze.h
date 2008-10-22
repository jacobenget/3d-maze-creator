/*
   Project     : 3DMaze
   File        : view3DMaze.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for viewing a 3D-maze
   				 after applying textures to its walls and floors
   				 
   				 
   				 command line syntax:
   				 
   				 view3Dmaze [ 3DMazeFileName ] [ floorTexture.ppm ] [ wallTexture.ppm ]
*/


#ifndef VIEW3DMAZE_H_
#define VIEW3DMAZE_H_

#ifdef HOST_OS_MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Maze3D.h"
#include "PPMTexture.h"
#include "ProjectionState.h"
#include "UserInteractionState.h"
#include "TransformationState.h"
#include "LoadFile.h"
#include "RegisterTexture.h"
#include "UserWishesToExitException.h"

const std::string window_title = "3D Viewer for Maze Model";

const std::string default_3D_maze_file_name = "SampleMazes/sampleMaze3D";
const std::string default_floor_texture_file_name = "SampleTextures/brushed_metal3.ppm";
const std::string default_walls_texture_file_name = "SampleTextures/checker_mush.ppm";

const int exit_success = 0;

const char quit_button = 'q';

const int initial_window_width = 900;
const int initial_window_height = 900;
const int initial_window_x_position = 300;
const int initial_window_y_position = 200;

const double bkgrnd_color_r = 0.8;
const double bkgrnd_color_g = 0.8;
const double bkgrnd_color_b = 0.95;

const double max_x_translation = initial_window_width / 2;
const double max_y_translation = initial_window_height / 2;

const double max_scale = 6;
const double min_scale = 0.05;

const double rotation_increment = 5.0;
const double translation_increment = 6.0;
const double scale_multiplier = 1.1;

const double fovy_angle_ratio_change = 0.92;
const double initial_fovy_angle = 45.0;
const double initial_z_coord_of_camera = 1000.0;

const int z_value_of_far_clipping_plane = -1000;
const int distance_between_camera_and_near_clipping_plane = 1;
const int min_z_coord_of_camera = 200;
const int max_z_coord_of_camera = 10000;

GLuint floorTextureNumber;
GLuint wallsTextureNumber;

Maze3D *pMaze;
ProjectionState *pStateOfProjection;
TransformationState *pStateOfTransformation;
UserInteractionState *pStateOfUserInteraction;


/* draw the 3-D maze
 * ( all transformations are computed outside (prior to) this function )
 */
void renderScene();

/* keyboard input handler....responds to 
 * the quit_button (defined in the header) for quiting
 * and allows the user to lift up their drawing pen
 */
void keyPressed( unsigned char key, int x, int y );

/* takes a mouse button input and determines
 * what state of interaction the system will be in
 * ( translating vs. rotating vs. scaling vs. ... )
 */
void mouseButtonPressed( int button, int state, int x, int y );

/* this function does all the work in tranforming mouse movement into 
 * a translation/rotation/scaling of the model
 */
void mouseMoved( int x, int y );

/* change size handler...
 * lets the user resize  the window 
 * but keeps everything in the correct perspective
 */
void windowChangedSize( int width, int height );

/* computes the viewing frustum
 * given the current state of affairs
 */
void computeFrustum();

/* this is the callback for handling the 
 * actions of the right mouse button menu
 */
void menuCallback( int option_number );


/* this handles all intialization:
 * setting up global variables,
 * reading in files,
 * and the loading of textures
 */
void initEnvironment( int argc, char ** argv ) throw( UserWishesToExitException & )
{
	pMaze = new Maze3D();
	pStateOfUserInteraction = new UserInteractionState();
	pStateOfProjection = new ProjectionState( initial_fovy_angle,
											  initial_z_coord_of_camera, 
											  initial_window_width,
											  initial_window_height,
											  z_value_of_far_clipping_plane,
											  distance_between_camera_and_near_clipping_plane,
											  fovy_angle_ratio_change,
											  min_z_coord_of_camera,
											  max_z_coord_of_camera );
	
	pStateOfTransformation = new TransformationState();
	pStateOfTransformation->setUpXScale( min_scale, max_scale, 1 );
	pStateOfTransformation->setUpYScale( min_scale, max_scale, 1 );
	pStateOfTransformation->setUpZScale( min_scale, max_scale, 1 );
	pStateOfTransformation->setUpXTranslation( -max_x_translation, max_x_translation, 0 );
	pStateOfTransformation->setUpYTranslation( -max_y_translation, max_y_translation, 0 );
	pStateOfTransformation->setUpZTranslation( 0, 0, 0 );
		
	std::string maze3DfileName = default_3D_maze_file_name;
	std::string floorTextureFileName = default_floor_texture_file_name;
	std::string wallsTextureFileName = default_walls_texture_file_name;
	
	//try to read in the 2-D maze file
	if( argc > 1 )
	{ 
		maze3DfileName = argv[ 1 ];
	}
  	
  	//may throw an exception which signals that the user wishes to quit
	LoadFile( maze3DfileName, *pMaze );
	
	//try to read in the floorTexture file
	if( argc > 2  )
  	{
  		floorTextureFileName = argv[ 2 ];
  	}
  	
  	//may throw an exception which signals that the user wishes to quit
	PPMTexture * floorTexture = new PPMTexture();
	LoadFile( floorTextureFileName, *floorTexture );
	
	//register the texture
	floorTextureNumber = RegisterTexture( *floorTexture );
	delete floorTexture;
	
	//try to read in the wallTexture file
	if( argc > 3 )
  	{
  		wallsTextureFileName = argv[3];
  	}
  	
  	//may throw an exception which signals that the user wishes to quit
	PPMTexture * wallsTexture = new PPMTexture();
	LoadFile( wallsTextureFileName, *wallsTexture );
	
	//register the texture
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
	delete pStateOfTransformation;
	delete pStateOfUserInteraction;
}


#endif /*VIEW3DMAZE_H_*/
