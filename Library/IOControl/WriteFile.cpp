/*
   Project     : 3DMaze
   File        : WriteFile.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Function for writing a Serializable object to 
   				 the named file, possibly asking for user input. 
   				 Tries to handles errors gracefully
*/


#include "WriteFile.h"

using namespace std;

void WriteFile( string fileName, Serializable & serialObject ) throw( UserWishesToExitException & )
{
	//if we don't yet have the name of the file to read from
	if( fileName == "" )
	{
		cout << "Enter a " << serialObject.type() <<" file name: ";
		cin >> fileName;
	}

	bool tryToWriteFile = true;
	while( tryToWriteFile )
	{
		try
		{
			FileHandler File( fileName );
			File.WriteToFile( serialObject );
			tryToWriteFile = false;
		}
		catch ( IOError  & readError )
		{
			/* if there was an error, ask the user for more input
			 * and give them the chance to exit
			 */
			cout << "There was an error writing to the file: " << fileName << '\n';
			cout << "Please enter a different " << serialObject.type() <<" file name ( '" << writeQuitPhrase << "' to quit ): ";
			cin >> fileName;
			if( fileName == writeQuitPhrase )	throw UserWishesToExitException();
		}
	}
}
