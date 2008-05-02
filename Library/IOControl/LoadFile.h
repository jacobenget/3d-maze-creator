/*
   Project     : 3DMaze
   File        : LoadFile.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Function for reading a Serializable object from 
   				 the named file, possibly asking for user input. 
   				 Tries to handles errors gracefully
*/


#ifndef LOADFILE_H_
#define LOADFILE_H_

#include "FileHandler.h"
#include "Serializable.h"
#include "IOError.h"
#include "UserWishesToExitException.h"

const std::string loadQuitPhrase = "q";

void LoadFile( std::string fileName, Serializable & serialObject ) throw( UserWishesToExitException & );

#endif /*LOADFILE_H_*/
