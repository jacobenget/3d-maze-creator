/*
   Project     : 3DMaze
   File        : Maze2D.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 2 dimensional Maze constructed with line segments
*/


#include "Maze2D.h"

using namespace std;

Maze2D::Maze2D( int m_width /* = 0 */, int m_height /* = 0 */ ) : 
	lines(), 
	width( m_width ), 
	height( m_height ) { addOuterWalls(); }


/* erases all lines except the 4 outer walls
 */
void Maze2D::clear()
{
	lines.clear();
	addOuterWalls();
}


/* Draws the maze using openGL calls
 */
void Maze2D::Draw() const
{
	glBegin( GL_LINES );        
    
	for( int i = 0; i < numberOfLines(); i++ )
    {
    	const LineSegment2D & lineToDraw = getALine( i );
    	glVertex2f( lineToDraw.getP1().getX(), lineToDraw.getP1().getY() );        
    	glVertex2f( lineToDraw.getP2().getX(), lineToDraw.getP2().getY() );        
    }   
    glEnd();
    
    glBegin( GL_LINES );
	
}

void Maze2D::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	lines.clear();
	
	in >> width >> height;
	
	int numberOfLinesToReadIn = 0;
	in >> numberOfLinesToReadIn;
	
	LineSegment2D line;
	for( int i = 0; i < numberOfLinesToReadIn; i++ )
	{
		line.readIn( in );
		addALine( line );
	}
}

void Maze2D::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	//should we just get an iterator of the vector of lines??
	out << width << " " << height << '\n';
	int numberOfLinesToWrite = numberOfLines();
	out << numberOfLinesToWrite << '\n';
	for( int i = 0; i < numberOfLinesToWrite; i++ )
	{
		const LineSegment2D & line = getALine( i );
		line.writeOut( out );
		out << '\n';
	}
}

void Maze2D::addALine( const LineSegment2D & lineToAdd )
{
	lines.push_back( lineToAdd );
}

const LineSegment2D & Maze2D::getALine( int index ) const
{
	return lines.at( index );
}


/* adds the 4 bounding walls
 */
void Maze2D::addOuterWalls()
{
	//add four bounding lines to the maze
	Point2D bottomLeft( -( width/2.0 ), -( height/2.0 ) );
	Point2D topLeft( -( width/2.0 ), ( height/2.0 ) );
	Point2D topRight( ( width/2.0 ), ( height/2.0 ) );
	Point2D bottomRight( ( width/2.0 ), -( height/2.0 ) );
		
	LineSegment2D leftSide( bottomLeft, topLeft );
	LineSegment2D topSide( topRight, topLeft );
	LineSegment2D rightSide( topRight, bottomRight );
	LineSegment2D bottomSide( bottomLeft, bottomRight );
		
	addALine( leftSide );
	addALine( topSide );
	addALine( rightSide );
	addALine( bottomSide );
}