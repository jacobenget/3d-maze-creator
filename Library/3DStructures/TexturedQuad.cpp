/*
   Project     : 3DMaze
   File        : TexturedQuad.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a flat 3-dimensional rectanlge that has been 
   				 plastered with a texture
*/


#include "TexturedQuad.h"

using namespace std;

TexturedQuad::TexturedQuad() : 
	Quad(), 
	p1Texture(), 
	p2Texture(),
	p3Texture(), 
	p4Texture() {}

TexturedQuad::TexturedQuad( const Quad & rhs, int widthOfTexture, int heightOfTexture )  :
	Quad( rhs ), 
	p1Texture( 0, rhs.height()/heightOfTexture ), 
	p2Texture( 0, 0 ), 
	p3Texture( rhs.width()/widthOfTexture, 0 ), 
	p4Texture( rhs.width()/widthOfTexture, rhs.height()/heightOfTexture ) {}

TexturedQuad::TexturedQuad( const Quad & rhs, const Point2D & m_tp1, const Point2D & m_tp2, const Point2D & m_tp3, const Point2D & m_tp4 ) :
	Quad( rhs ), 
	p1Texture( m_tp1 ), 
	p2Texture( m_tp2 ), 
	p3Texture( m_tp3 ), 
	p4Texture( m_tp4 ) {}

TexturedQuad::TexturedQuad( const TexturedQuad & rhs ) : 
	Quad( rhs ), 
	p1Texture( rhs.getP1Texture() ), 
	p2Texture( rhs.getP2Texture() ), 
	p3Texture( rhs.getP3Texture() ), 
	p4Texture( rhs.getP4Texture() ) {}

const TexturedQuad & TexturedQuad::operator=( const TexturedQuad & rhs )
{
	if( this != &rhs )
	{
		Quad::operator=( rhs );
		p1Texture = rhs.getP1Texture();
		p2Texture = rhs.getP2Texture();
		p3Texture = rhs.getP3Texture();
		p4Texture = rhs.getP4Texture();
	}
	return *this;
}


/* Draw this Textured Quad with openGL calls
 * assuming that the appropriate textures have been 
 * registered to openGL elsewhere
 */
void TexturedQuad::Draw() const
{
	glBegin( GL_QUADS );
		glTexCoord2f( getP1Texture().getX(), getP1Texture().getY() );
		glVertex3f( getP1().getX(), getP1().getY(), getP1().getZ() );
		
		glTexCoord2f( getP2Texture().getX(), getP2Texture().getY() );
		glVertex3f( getP2().getX(), getP2().getY(), getP2().getZ() );
		
		glTexCoord2f( getP3Texture().getX(), getP3Texture().getY() );
		glVertex3f( getP3().getX(), getP3().getY(), getP3().getZ() );
		
		glTexCoord2f( getP4Texture().getX(), getP4Texture().getY() );
		glVertex3f( getP4().getX(), getP4().getY(), getP4().getZ() );
    glEnd();
}


void TexturedQuad::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	Point3D a, b, c, d;
	char symbol;
	
	in >> symbol;
	if( symbol != 'v' )	return;
	a.readIn( in );
	p1Texture.readIn( in );
	setP1( a );

	in >> symbol;
	if( symbol != 'v' )	return;
	b.readIn( in );
	p2Texture.readIn( in );
	setP2( b );

	in >> symbol;
	if( symbol != 'v' )	return;
	c.readIn( in );
	p3Texture.readIn( in );
	setP3( c );

	in >> symbol;
	if( symbol != 'v' )	return;
	d.readIn( in );
	p4Texture.readIn( in );
	setP4( d );
}


void TexturedQuad::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	out << "v ";
	getP1().writeOut( out );
	out << " ";
	getP1Texture().writeOut( out );
	out << '\n';
	
	out << "v ";
	getP2().writeOut( out );
	out << " ";
	getP2Texture().writeOut( out );
	out << '\n';
	
	out << "v ";
	getP3().writeOut( out );
	out << " ";
	getP3Texture().writeOut( out );
	out << '\n';
	
	out << "v ";
	getP4().writeOut( out );
	out << " ";
	getP4Texture().writeOut( out );
	out << '\n';
}
