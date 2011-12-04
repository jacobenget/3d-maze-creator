/*
   Project     : 3DMaze
   File        : TexturedQuad.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a flat 3-dimensional rectanlge that has been 
   				 plastered with a texture
*/


#ifndef TEXTUREDQUAD_H_
#define TEXTUREDQUAD_H_

#include <QtOpenGL>

#include "Quad.h"
#include "Point2D.h"
#include "IOError.h"
#include "Serializable.h"

class TexturedQuad : public Quad
{
	public:
		TexturedQuad();
		TexturedQuad( const Quad & rhs, int heightOfTexture, int widthOfTexture );
		TexturedQuad( const Quad & rhs, const Point2D & m_tp1, const Point2D & m_tp2, const Point2D & m_tp3, const Point2D & m_tp4 );
		TexturedQuad( const TexturedQuad & rhs );
		
		const Point2D & getP1Texture() const { return p1Texture; }
		const Point2D & getP2Texture() const { return p2Texture; }
		const Point2D & getP3Texture() const { return p3Texture; }
		const Point2D & getP4Texture() const { return p4Texture; } 
		
		void setP1Texture( const Point2D & m_p1Texture ) { p1Texture = m_p1Texture; }
		void setP2Texture( const Point2D & m_p2Texture ) { p2Texture = m_p2Texture; }
		void setP3Texture( const Point2D & m_p3Texture ) { p3Texture = m_p3Texture; }
		void setP4Texture( const Point2D & m_p4Texture ) { p4Texture = m_p4Texture; }
		
		const TexturedQuad & operator=( const TexturedQuad & rhs );
		
		/* Draw this Textured Quad with openGL calls
		 * assuming that the appropriate textures have been 
		 * registered to openGL elsewhere
		 */
		void Draw() const;

		//inherited from Serializable
		void readIn( std::istream & in = std::cin ) throw( IOError & );
		void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "Textured Quad";}
		
	private:
		// texture coodinates of the four corners of the quad
		Point2D p1Texture;
		Point2D p2Texture;
		Point2D p3Texture;
		Point2D p4Texture;
};

#endif /*TEXTUREDQUAD_H_*/
