/*
   Project     : 3DMaze
   File        : Maze3D.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 3D maze made constructed with Walls and a floor
*/


#ifndef MAZE3D_H_
#define MAZE3D_H_

#include <vector>

#include "Wall.h"
#include "TexturedQuad.h"
#include "Point2D.h"
#include "Serializable.h"
#include "IOError.h"

class Maze3D : public Serializable
{
	public:
		Maze3D();
		Maze3D( TexturedQuad & m_floor );
		
		void addAWall( const Wall & wall );
		const Wall & getAWall( int index ) const;
		int numberOfWalls() const;
		const TexturedQuad & getFloor() const	{ return floor; }
		void setFloor( const TexturedQuad & m_floor ) {	floor = m_floor; }
		
		/* Draws the maze using openGL calls
		 */
		void Draw( int floorTextureNumber, int wallTextureNumber ) const;
		
		/* takes in a two dimensional point and returns the first Wall
		 * in this maze that this point is "inside"  (defined by the Wall class)
		 * throws and exception if the point doesn't lie in any wall in this maze
		 */
		const Wall & detectCollision( const Point2D & point ) const throw( Wall::NoCollisionDetected & );
		
		//inherited form Serializable
		void readIn( std::istream & in = std::cin ) throw( IOError & );
		void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "3D Maze";}
		
	private:
		std::vector<Wall> walls;
		TexturedQuad floor;
};

/*
ostream & operator<<( ostream & os, const Maze3D & maze );
istream & operator>>( istream & in, Maze3D & maze );
*/

#endif /*MAZE3D_H_*/
