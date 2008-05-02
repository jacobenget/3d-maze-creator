/*
   Project     : 3DMaze
   File        : FileHandler.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Handles reading from and writing to files
   				 for Serializable objects
*/


#include "FileHandler.h"

#include "Serializable.h"

using namespace std;

FileHandler::FileHandler( const std::string & m_fileName ) : 
	fileName( m_fileName ) {}

void FileHandler::ReadFromFile( Serializable & serialObject ) const throw( IOError & )
{
	ifstream inFile( fileName.c_str() );
	if( !inFile )
	{
		throw IOError();
	}
	
	//this might throw an IOError, but if it does we'll just have it propagate up
	serialObject.readIn( inFile );
}


void FileHandler::WriteToFile( const Serializable & serialObject ) const throw( IOError & )
{
	ofstream outFile( fileName.c_str() );
	if( !outFile )
	{
		throw IOError();
	}

	//this might throw an IOError, but if it does we'll just have it propagate up
	serialObject.writeOut( outFile );
}
