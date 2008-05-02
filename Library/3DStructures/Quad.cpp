/*
   Project     : 3DMaze
   File        : Quad.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 3-dimensional flat rectangle
*/


#include "Quad.h"

using namespace std;

Quad::Quad() : 
	p1(), 
	p2(), 
	p3(), 
	p4() {}
		
Quad::Quad( const Point3D & m_p1, const Point3D & m_p2, const Point3D & m_p3, const Point3D & m_p4 ) : 
	p1( m_p1 ), 
	p2( m_p2 ), 
	p3( m_p3 ), 
	p4( m_p4 ) {}
		
Quad::Quad( const Quad & rhs ) : 
	p1( rhs.getP1() ), 
	p2( rhs.getP2() ), 
	p3( rhs.getP3() ), 
	p4( rhs.getP4() ) {}

const Quad & Quad::operator=( const Quad & rhs )
{
	if( this != &rhs )
	{
		p1 = rhs.getP1();
		p2 = rhs.getP2();
		p3 = rhs.getP3();
		p4 = rhs.getP4();
	}
	return *this;
}

double Quad::height() const 
{
	return getP1().distanceTo( getP2() );
}

double Quad::width() const
{
	return getP1().distanceTo( getP4() );
}


void Quad::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	char symbol;
	
	in >> symbol;
	if( symbol != 'v' )	return;
	p1.readIn( in );

	in >> symbol;
	if( symbol != 'v' )	return;
	p2.readIn( in );

	in >> symbol;
	if( symbol != 'v' )	return;
	p3.readIn( in );

	in >> symbol;
	if( symbol != 'v' )	return;
	p4.readIn( in );
}

void Quad::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	out << "v ";
	getP1().writeOut( out );
	out << '\n';
	out << "v ";
	getP1().writeOut( out );
	out << '\n';
	out << "v ";
	getP1().writeOut( out );
	out << '\n';
	out << "v ";
	getP1().writeOut( out );
	out << '\n';
}