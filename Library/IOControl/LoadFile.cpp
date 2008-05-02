/*
   Project     : 3DMaze
   File        : LoadFile.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Function for reading a Serializable object from 
   				 the named file, possibly asking for user input. 
   				 Tries to handles errors gracefully
*/


#include "LoadFile.h"

using namespace std;

void LoadFile( string fileName, Serializable & serialObject ) throw( UserWishesToExitException & )
{
	//if we don't yet have the name of the file to read from
	if( fileName == "" )
	{
		cout << "Enter a " << serialObject.type() <<" file name: ";
		cin >> fileName;
	}

	bool tryToLoadFile = true;
	while( tryToLoadFile )
	{
		try
		{
			FileHandler File( fileName );
			File.ReadFromFile( serialObject );
			tryToLoadFile = false;
		}
		catch ( IOError  & readError )
		{
			/* if there was an error, ask the user for more input
			 * and give them the chance to exit
			 */
			cout << "There was an error reading from the file: " << fileName << '\n';
			cout << "Please enter a different " << serialObject.type() <<" file name ( '" << loadQuitPhrase << "' to quit ): ";
			cin >> fileName;
			if( fileName == loadQuitPhrase )	throw UserWishesToExitException();
		}
	}
}