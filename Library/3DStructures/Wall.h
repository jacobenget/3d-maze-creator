/*
   Project     : 3DMaze
   File        : Wall.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 3-dimensional Wall that is made up of a
   				 front, a back, two sides, and a top
*/


#ifndef WALL_H_
#define WALL_H_

#include <math.h>

#include "Serializable.h"
#include "IOError.h"
#include "TexturedQuad.h"
#include "LineSegment2D.h"
#include "Vector2D.h"

class Wall : public Serializable
{
	public:
		class NoCollisionDetected
		{
			public:
				NoCollisionDetected() {}
		};
		
		Wall();
		Wall( TexturedQuad & m_frontEnd, TexturedQuad & m_rightSide, TexturedQuad & m_leftSide, TexturedQuad & m_backEnd, TexturedQuad & m_top );
		Wall( const Wall & rhs );
		
		/*
		 * changes the specifics of this wall so that it's frontEnd and backEnd Quads
		 * have their centers at the end points of the given line, the wall is sitting 
		 * up straight in the y-direction, and it has the given width and height
		 */
		void fitToLine( const LineSegment2D & line, int widthOfWall, int heightOfWall, int widthOfTexture, int heightOfTexture );
		
		const TexturedQuad & getFrontEnd() const { return frontEnd; }
		const TexturedQuad & getRightSide() const { return rightSide; }
		const TexturedQuad & getLeftSide() const { return leftSide; }
		const TexturedQuad & getBackEnd() const { return backEnd; }
		const TexturedQuad & getTop() const { return top; }

		void setFrontEnd( const TexturedQuad & m_frontEnd ) { frontEnd = m_frontEnd; }
		void setRightSide( const TexturedQuad & m_rightSide ) { rightSide = m_rightSide; }
		void setLeftSide( const TexturedQuad & m_leftSide ) { leftSide = m_leftSide; }
		void setBackEnd( const TexturedQuad & m_backEnd ) { backEnd = m_backEnd; }
		void setTop( const TexturedQuad & m_top ) { top = m_top; }
		
		void Draw() const;
		
		/* returns true iff this 2D point is within the x and y range of this wall
		 * ( height doesn't matter, as the point coudld be directly above the
		 * wall and would still be considered to be "inside"
		 */  
		bool isInsideMe( const Point2D & point ) const;
		
		/* return the Vector2D that represents the motion that an object
		 * should take after colliding with this wall while traveling
		 * the path of the given "line"
		 */ 
		Vector2D resolveCollision( const LineSegment2D & line ) const;
		
		//inherited from Serializable
		void readIn( std::istream & in = std::cin ) throw( IOError & );
		void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "3D Wall";}
		
		static int getNumberOfQuadsPerWall() 
		{ 
			static int numberOfQuadsPerWall = 5;
			return numberOfQuadsPerWall;
		}
		static int getNumberOfVerticesPerWall() 
		{ 
			static int numberOfVerticesPerWall = 8;
			return numberOfVerticesPerWall;
		}
		
	private:
		TexturedQuad frontEnd;
		TexturedQuad rightSide;
		TexturedQuad leftSide;
		TexturedQuad backEnd;
		TexturedQuad top;
		
		/* returns the vectore that defines the base of the side of the wall that this line 
		 * crosses first, when traveling from the beginning of this line to its end
		 * this function throws an error is there is no such line
		 */
		Vector2D getCollisionSurface( const LineSegment2D & line ) const throw( Wall::NoCollisionDetected & );
};

#endif /*WALL_H_*/
