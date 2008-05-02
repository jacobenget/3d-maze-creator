/*
   Project     : 3DMaze
   File        : RegisterTexture.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Function for registering a testure 
   				 to the openGL engine so that the texture
   				 can later be used in rendering
*/


#ifndef REGISTERTEXTURE_H_
#define REGISTERTEXTURE_H_

#include <GLUT/glut.h>
#include "PPMTexture.h"

/* returns the number under which openGL registered this texture
 */
int RegisterTexture( const PPMTexture & texture );

#endif /*REGISTERTEXTURE_H_*/
