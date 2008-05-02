/*
   Project     : 3DMaze
   File        : Maze2D.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 2 dimensional Maze constructed with line segments
*/


#ifndef MAZE2D_H_
#define MAZE2D_H_

#include <vector>
#include <GLUT/glut.h>

#include "LineSegment2D.h"
#include "Serializable.h"
#include "IOError.h"

class Maze2D : public Serializable
{
	public:
		Maze2D( int m_width = 0, int m_height = 0 );
		
		void addALine( const LineSegment2D & line );
		const LineSegment2D & getALine( int index ) const;
		int numberOfLines() const { return lines.size(); }
		int getWidth() const { return width; }
		int getHeight() const { return height; }
		
		/* erases all lines except the 4 outer walls
		 */
		void clear();
		
		/* Draws the maze using openGL calls
		 */
		void Draw() const;
		
		//inherited from Serializable
		void readIn( std::istream & in = std::cin ) throw( IOError & );
		void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "2D Maze";}
	
	private:
		std::vector<LineSegment2D> lines;
		int width, height;
		
		/* adds the 4 bounding walls
		 */
		void addOuterWalls();
};

#endif /*MAZE2D_H_*/
