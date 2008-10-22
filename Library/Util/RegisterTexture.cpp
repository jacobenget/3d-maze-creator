/*
   Project     : 3DMaze
   File        : RegisterTexture.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Function for registering a testure 
   				 to the openGL engine so that the texture
   				 can later be used in rendering
*/


#include "RegisterTexture.h"


/* returns the number under which openGL registered this texture
 */
int RegisterTexture( const PPMTexture & texture )
{
	GLuint textureNumber = 0;
	//tell openGL that we'd like to register 1 texture
	glGenTextures( 1 /*number of texture object names to generate*/, &textureNumber );
  		
	/* set up the environment so openGL will know how to 
	 * handle the testure data we're going to feed it
	 */
  	glBindTexture( GL_TEXTURE_2D, textureNumber );
  	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
  		
  	//have the textures wrap in both the X and the Y direction
  	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  		
  	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  		
  	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  		
  	//feed texture data in
  	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texture.getWidth(), 
  			texture.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,
  			texture.getData() );
  	
  	return textureNumber;
}
