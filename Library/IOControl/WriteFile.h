/*
   Project     : 3DMaze
   File        : WriteFile.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Function for writing a Serializable object to 
   				 the named file, possibly asking for user input. 
   				 Tries to handles errors gracefully
*/


#ifndef WRITEFILE_H_
#define WRITEFILE_H_

#include "FileHandler.h"
#include "Serializable.h"
#include "IOError.h"
#include "UserWishesToExitException.h"

const std::string writeQuitPhrase = "q";

void WriteFile( std::string fileName, Serializable & serialObject ) throw( UserWishesToExitException & );

#endif /*WRITEFILE_H_*/
