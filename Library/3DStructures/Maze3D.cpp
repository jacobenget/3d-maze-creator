/*
   Project     : 3DMaze
   File        : Maze3D.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 3D maze made constructed with Walls and a floor
*/


#include "Maze3D.h"

using namespace std;

Maze3D::Maze3D() : 
	walls(), 
	floor() {}

Maze3D::Maze3D( TexturedQuad & m_floor ) : 
	walls(), 
	floor( m_floor ) {}

void Maze3D::addAWall( const Wall & wallToAdd )
{
	walls.push_back( wallToAdd );;
}

const Wall & Maze3D::getAWall( int index ) const
{
	return walls.at( index );
}

int Maze3D::numberOfWalls() const
{
	return walls.size();
}


/* Draws the maze using openGL calls
 */
void Maze3D::Draw( int floorTextureNumber, int wallTextureNumber ) const
{
	glEnable( GL_TEXTURE_2D );
    
	//do the floor first
	glBindTexture( GL_TEXTURE_2D, floorTextureNumber );
	getFloor().Draw();
    
	//now do the walls
	glBindTexture( GL_TEXTURE_2D, wallTextureNumber );
	for( int i = 0; i < numberOfWalls(); i++ )
	{
		getAWall( i ).Draw();
	}
    
    glDisable( GL_TEXTURE_2D );
}


/* takes in a two dimensional point and returns the first Wall
 * in this maze that this point lies in  ( the dimension of height isn't considered,
 * so a point lieing above a wall be considered to be in the wall)
 * throws and exception if the point doesn't lie in any wall in this maze
 */
const Wall & Maze3D::detectCollision( const Point2D & point ) const throw( Wall::NoCollisionDetected & )
{
	for( int i = 0; i < numberOfWalls(); i++ )
	{
		const Wall & wall = getAWall( i );
		if( wall.isInsideMe( point ) )
		{
			return wall;
		}
	}
	
	//if we've made it here then this point collides with no walls
	throw Wall::NoCollisionDetected();
}


void Maze3D::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	int numberOfVertices = 0;
	int numberOfQuads = 0;
	
	in >> numberOfVertices;
	in >> numberOfQuads;
	
	int numberOfWallsAccordingToVertices = ( ( numberOfVertices - Quad::getNumberOfVerticesPerQuad() )/ ( Wall::getNumberOfQuadsPerWall() * Quad::getNumberOfVerticesPerQuad() ) );
	int numberOfWallsAccordingToQuads = ( ( numberOfQuads - 1 ) / Wall::getNumberOfQuadsPerWall() );;
	
	if( numberOfWallsAccordingToVertices != numberOfWallsAccordingToQuads )
	{
		//could report some type of error noting the miscount of vertices and quads
		return;
	}
	
	//floor is read in first, before any other walls
	floor.readIn( in );
	
	//then, read in all the walls
	Wall wall;
	
	for( int i = 0; i < numberOfWallsAccordingToQuads; i++ )
	{
		wall.readIn( in );
		addAWall( wall );
	}
}

void Maze3D::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	int numberOfVertices = ( numberOfWalls() * Wall::getNumberOfQuadsPerWall() + 1 ) * Quad::getNumberOfVerticesPerQuad();
	int numberOfQuads = ( numberOfWalls() * Wall::getNumberOfQuadsPerWall() ) + 1;
	
	out << numberOfVertices << " " << numberOfQuads << '\n';
	
	getFloor().writeOut( out );
	
	for( int i = 0; i < numberOfWalls(); i++ )
	{
		const Wall & wall = getAWall( i );
		wall.writeOut( out );
	}
	
	out << '\n';
	
	for( int i = 0; i < numberOfQuads; i++ )
	{
		//write out the character denoting a "quad"
		out << "q ";
		for( int j = 0; j < Quad::getNumberOfVerticesPerQuad(); j++ )
		{
			out << Quad::getNumberOfVerticesPerQuad()*i + j << ' ';
		}
		out << '\n';
	}
}
