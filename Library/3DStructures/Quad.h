/*
   Project     : 3DMaze
   File        : Quad.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Represents a 3-dimensional flat rectangle
*/


#ifndef QUAD_H_
#define QUAD_H_

#include "Point3D.h"
#include "Serializable.h"
#include "IOError.h"

class Quad : public Serializable
{
	public:
		Quad();
		Quad( const Point3D & m_p1, const Point3D & m_p2, const Point3D & m_p3, const Point3D & m_p4 );
		Quad( const Quad & rhs );
		virtual ~Quad() {}
		
		const Point3D & getP1() const { return p1; }
		const Point3D & getP2() const { return p2; }
		const Point3D & getP3() const { return p3; }
		const Point3D & getP4() const { return p4; } 
		
		void setP1( const Point3D & m_p1 ) { p1 = m_p1; }
		void setP2( const Point3D & m_p2 ) { p2 = m_p2; }
		void setP3( const Point3D & m_p3 ) { p3 = m_p3; }
		void setP4( const Point3D & m_p4 ) { p4 = m_p4; }
		
		virtual const Quad & operator=( const Quad & rhs );
		
		double height() const;
		double width() const;
		
		//inherited from Serializable
		virtual void readIn( std::istream & in = std::cin ) throw( IOError & );
		virtual void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "Quad";}
		
		static int getNumberOfVerticesPerQuad()
		{
			int numberOfVerticesPerQuad = 4;
			return numberOfVerticesPerQuad;
		}
		
	private:
		Point3D p1;  //bottom left
		Point3D p2;  //top left
		Point3D p3;  //top right
		Point3D p4;  //bottom right

};

#endif /*QUAD_H_*/
