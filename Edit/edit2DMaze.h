/*
   Project     : 3DMaze
   File        : edit2DMaze.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for reading in, editing, and
   				 writing back out a file for a 2D maze
   				 
   				 
   				 command line syntax:
   				 
   				 edit2DMaze [ 2DMazeFileName ]
*/


#ifndef EDIT2DMAZE_H_
#define EDIT2DMAZE_H_

#ifdef HOST_OS_MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "Point2D.h"
#include "LineSegment2D.h"
#include "Maze2D.h"
#include "FileHandler.h" 
#include "LoadFile.h"  
#include "WriteFile.h" 

const std::string window_title = "Edit/Create your own Maze";

const  int exit_success = 0;

const int initial_window_width = 600;
const int initial_window_height = 600;
const int initial_window_x_position = 300;
const int initial_window_y_position = 200;

const double maze_width = ( 3.0 / 4.0 ) * initial_window_width;
const double maze_height = ( 3.0 / 4.0 ) * initial_window_height;

const double walls_color_r = 0.1;
const double walls_color_g = 0.1;
const double walls_color_b = 0.1;

const double bkgrd_color_r = 0.40;
const double bkgrd_color_g = 0.40;
const double bkgrd_color_b = 0.40;

const double inside_maze_color_r = 0.8;
const double inside_maze_color_g = 0.8;
const double inside_maze_color_b = 0.8;

const double figure_color_r = 0.70;
const double figure_color_g = 0.30;
const double figure_color_b = 0.30;

const char quit_button = 'q';
const char lift_up_pen_button = ' ';

const std::string menu_save_option_label = "Save Maze";
const int menu_save_option_number = 1;
const std::string menu_saveAndQuit_option_label = "Save and Quit";
const int menu_saveAndQuit_option_number = 2;
const std::string menu_clear_option_label = "Clear Maze";
const int menu_clear_option_number = 3;
const std::string menu_quit_option_label = "Quit";
const int menu_quit_option_number = 4;

const std::string default_2D_maze_file_name = "SampleMazes/sampleMaze2D";

void setMazeToDefault();
Point2D convertPointToCoordinatesSystem( int x, int y );
void renderScene();
void shadeInsideOfMaze();
void drawFigureIcon();
void keyPressed( unsigned char key, int x, int y );
void mouseButtonPressed( int button, int state, int x, int y );
void mouseMoved( int x, int y );
void windowChangedSize( int width, int height );
void saveMaze();
void menuCallback( int option_number );


#endif /*EDIT2DMAZE_H_*/
