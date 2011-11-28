/*
   Project     : 3DMaze
   File        : Serializable.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Interface for objects that can be read from 
   				 and writen to files.  These objects need to also
   				 know what "type" they are we can seek assistacne from 
   				 a user when an error occurs
*/


#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <iostream>

#include "IOError.h"

class Serializable
{
	public:
		virtual ~Serializable() {}
		virtual void readIn( std::istream & in = std::cin ) throw( IOError & ) = 0;
		virtual void writeOut( std::ostream & out = std::cout ) const throw( IOError & ) = 0;
		virtual std::string type() const = 0;
};

#endif /*SERIALIZABLE_H_*/
