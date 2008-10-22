/*
   Project     : 3DMaze
   File        : PPMTexture.h
   Author      : Jeremy Moc  (mocx0001@umn.edu), Jacob Enget  (jacob.enget@gmail.com)

   Description : Object containing the raw data from a PPM image file.
   				 NOTE: the PPM image file MUST be "PPM 3",
   				 which is formated as basic ASCII
   				 (as opposed to "PPM 6" which is written in binary)
*/


#ifndef PPMTEXTURE_H
#define PPMTEXTURE_H

#include <string>

#ifdef HOST_OS_MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <math.h>


#include "Serializable.h"

class PPMTexture : public Serializable
{
	public:
   
		PPMTexture();
   
		~PPMTexture() { delete [] pixelData; }
   
		int readIn( std::string filename );
   
		unsigned char *getData() const { return pixelData; }
		int getHeight() const { return height; }
		int getWidth() const { return width; }
		
      	void readIn( std::istream & in = std::cin ) throw( IOError & );
		void writeOut( std::ostream & out = std::cout ) const throw( IOError & );
		std::string type() const { return "PPM Texture";}
   
   private:
   
      int height, width;
      unsigned char *pixelData;
};

#endif /*PPMTEXTURE_H_*/
