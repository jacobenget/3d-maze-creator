/*
   Project     : 3DMaze
   File        : convertMazeTo3D.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for reading in a 2-D, converting
   				 it into a 3-D maze, and writing this 3-D maze out to a file
   				 
   				 
   				 command line syntax:
   				 
   				 convertMazeTo3D [ 2DMazeFileName [ 3DMazeFileName [ wallWidth [ wallHeight ] ] ] ]
*/


#ifndef CONVERTMAZETO3D_H_
#define CONVERTMAZETO3D_H_

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Maze2D.h"
#include "Maze3D.h"
#include "LoadFile.h"
#include "WriteFile.h"

const int exit_success = 0;

const int default_wall_width = 10;
const int default_wall_height = 50;

const double default_texture_size = 50.0;

const std::string default_2D_maze_file_name = "SampleMazes/sampleMaze2D";
const std::string default_3D_maze_file_name = "SampleMazes/sampleMaze3D";

void convert2Dto3d( const Maze2D & maze2d, Maze3D & maze3d, int wallWidth, int wallHeight );

#endif /*CONVERTMAZETO3D_H_*/
