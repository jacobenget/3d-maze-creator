/*
   Project     : 3DMaze
   File        : FileHandler.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Handles reading from and writing to files
   				 for Serializable objects
*/


#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <fstream>
#include <iostream>

#include "Serializable.h"
#include "IOError.h"

class FileHandler
{
	public:
		FileHandler( const std::string & m_fileName );
		void ReadFromFile( Serializable & serialObject ) const throw( IOError & );
		void WriteToFile( const Serializable &serialObject ) const throw( IOError & );
		
	private:
		std::string fileName;
};

#endif /*FILEHANDLER_H_*/
