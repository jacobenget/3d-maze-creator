/*
   Project     : 3DMaze
   File        : convertMazeTo3D.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for reading in a 2-D, converting
   				 it into a 3-D maze, and writing this 3-D maze out to a file
   				 
   				 
   				 command line syntax:
   				 
   				 convertMazeTo3D [ 2DMazeFileName ] [ 3DMazeFileName ] [ wallWidth ] [ wallHeight ]
*/


#include "convertMazeTo3D.h"

using namespace std;

int main( int argc, char **argv )
{
	string TwoDfileName = default_2D_maze_file_name;
	string ThreeDfileName = default_3D_maze_file_name;
	int width = default_wall_width;
	int height = default_wall_height;
	
	//fill out values according to parameters given at the command line
	if( argc > 1 )
	{
		TwoDfileName = argv[ 1 ];
		
		if( argc > 2 )
		{
			ThreeDfileName = argv[ 2 ];
			
			if( argc > 3 )
			{
				width = atoi( argv[ 3 ] );
				
				if( argc > 4 )
				{
					height = atoi( argv[ 4 ] );
				}
			}
		}
	}
	
	Maze2D fromMaze2D;
	Maze3D toMaze3D;
	
	//try to read in the 2D maze file
	try
	{
		LoadFile( TwoDfileName, fromMaze2D );
	}
	catch ( UserWishesToExitException & ue )
	{
		cout << "goodbye!";
		return exit_success;
	}
	
	convert2Dto3d( fromMaze2D, toMaze3D, width, height );
	
	//try to write out the 3D maze file
	try
	{
		WriteFile( ThreeDfileName, toMaze3D );
	}
	catch ( UserWishesToExitException & ue )
	{
		cout << "goodbye!";
		return exit_success;
	}
	
	return 0;
}

/* given a 2-D maze, create a  3-D maze by extrapolating it's 
 * lines into 3D walls with the given width and height
 */
void convert2Dto3d( const Maze2D & maze2d, Maze3D & maze3d, int wallWidth, int wallHeight )
{
	
	//iterate through the lines in the 2D maze and create 3D walls out of them
	//and add these walls to the 3D maze;
	int numberOfLines = maze2d.numberOfLines();
	Wall wall;
	
	for( int i = 0; i < numberOfLines; i++ )
	{
		wall.fitToLine( maze2d.getALine( i ), wallWidth, wallHeight, default_texture_size, default_texture_size );
		maze3d.addAWall( wall );
	}
	
	//add the floor
	Point3D bottomLeft( -( maze2d.getWidth() / 2.0 ), -( maze2d.getHeight() / 2.0 ), -wallHeight/2 );
	Point3D topLeft( -( maze2d.getWidth() / 2.0 ), ( maze2d.getHeight() / 2.0 ), -wallHeight/2 );
	Point3D topRight( ( maze2d.getWidth() / 2.0 ), ( maze2d.getHeight() / 2.0 ), -wallHeight/2 );
	Point3D bottomRight( ( maze2d.getWidth() / 2.0 ), -( maze2d.getHeight() / 2.0 ), -wallHeight/2 );
	
	Quad floor( bottomLeft, topLeft, topRight, bottomRight );
	TexturedQuad tFloor( floor, default_texture_size, default_texture_size );
	
	maze3d.setFloor( tFloor );
}