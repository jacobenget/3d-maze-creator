/*
   Project     : 3DMaze
   File        : PPMTexture.cpp
   Author      : Jeremy Moc  (mocx0001@umn.edu), Jacob Enget  (jacob.enget@gmail.com)

   Description : Object containing the raw data from a PPM image file.
   				 NOTE: the PPM image file MUST be "PPM 3",
   				 which is formated as basic ASCII
   				 (as opposed to "PPM 6" which is written in binary)
*/


#include "PPMTexture.h"

using namespace std;

PPMTexture::PPMTexture() : 
	height( -1 ), 
	width( -1 ), 
	pixelData( 0 ) {}

void PPMTexture::readIn( istream & in /* = cin */ ) throw( IOError & )
{
	if ( pixelData != NULL )
	{
		delete[] pixelData;
	}

	char buffer[80];
   
	// read the header: "P3".  Report errors to cerr
	
	in.getline( buffer, sizeof( buffer ) );
	if ( buffer != ( string )"P3" )
	{
		cerr << "Invalid Texture Header: ( " << buffer << " )" << endl;
		throw IOError();
	}

	// read and discard the comments, which start with '#'

	while ( in.peek() == '#' )
	{
		in.getline( buffer, sizeof( buffer ) );
	}

	int maxval;    	// need to read maxval field from the file
					// even though in this case it is not being
                  	// used  ( we're assuming it's 255 )

	// read the size fields and maxval

	in >> width >> height >> maxval;

	// allocate storage for image data - throw fatal exception on error
	try
	{
		pixelData = new unsigned char[ 3 * height * width ];
	}
	catch ( bad_alloc & )
	{
		cerr << "FATAL EXCEPTION: Texture memory allocation error." << endl;
		throw IOError();
	}

	for ( int i = 0; i < height; i++ )
	{
		for ( int k = 0; k < 3 * width; k += 3 )
		{
			int x, j = 3 * width * ( height - 1 - i );

			// read red value from the file and store
			in >> x;
			pixelData[ j + k ] = x;

			// read green value from the file and store
			in >> x;
			pixelData[ j + k + 1 ] = x;

			// read blue value from the file and store
			in >> x;
			pixelData[ j + k + 2 ] = x;

			// check for any read errors
			if ( in.bad() || in.fail() )
			{
				cerr << "Read Error occured." << endl;
				in.clear();   // clear these errors for next read operation...
			}
		}
	}
}


void PPMTexture::writeOut( ostream & out /* = cout */ ) const throw( IOError & )
{
	//don't have the need to write out a PPM file just yet
	//this may be implemented later
	cerr << "PPMTexture::writeOut NOT implemented!!!";
}
