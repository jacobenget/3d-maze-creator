/*
   Project     : 3DMaze
   File        : ConversionFunctions.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Set of functions used to convert values 
   				 from one type to another
*/


#include "ConversionFunctions.h"

double toRadians( double degrees )	
{	
	return ( 2 * pi * degrees ) / degrees_in_circle; 
}

double toDegrees( double radians )	
{	
	return ( degrees_in_circle * radians )/ ( 2 * pi );
}