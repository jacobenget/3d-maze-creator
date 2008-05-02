/*
   Project     : 3DMaze
   File        : TransformationState.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Describes the total current transformation
   				 for an object that is seperate from the viewer...
   				 at a distance ( this is used to "view" the maze )  
   				 This class also allows boundaries to be set up 
   				 on all of its values
*/


#include "TransformationState.h"

TransformationState::TransformationState() :
	xScale(),
	yScale(),
	zScale(),
	xTranslation(),
	yTranslation(),
	zTranslation(),
	rotation() {}


/* set up scalar boundaries
 */
void TransformationState::setUpXScale( double min, double max, double initialValue )
{
	xScale.setMin( min );
	xScale.setMax( max );
	xScale = initialValue;
}

void TransformationState::setUpYScale( double min, double max, double initialValue )
{
	yScale.setMin( min );
	yScale.setMax( max );
	yScale = initialValue;
}

void TransformationState::setUpZScale( double min, double max, double initialValue )
{
	zScale.setMin( min );
	zScale.setMax( max );
	zScale = initialValue;
}



/* set up translation boundaries
 */
void TransformationState::setUpXTranslation( double min, double max, double initialValue )
{
	xTranslation.setMin( min );
	xTranslation.setMax( max );
	xTranslation = initialValue;
}

void TransformationState::setUpYTranslation( double min, double max, double initialValue )
{
	yTranslation.setMin( min );
	yTranslation.setMax( max );
	yTranslation = initialValue;
}

void TransformationState::setUpZTranslation( double min, double max, double initialValue )
{
	zTranslation.setMin( min );
	zTranslation.setMax( max );
	zTranslation = initialValue;
}



/* resets the transformation to be just the identity
 */
void TransformationState::reset()
{
	xScale = 1;
	yScale = 1;
	zScale = 1;
	
	xTranslation = 0;
	yTranslation = 0;
	zTranslation = 0;
	
	rotation.reset();
}



/* affect the scalar transformation
 */
void TransformationState::multiplyXScaleBy( double factor )
{
	xScale *= factor;
}

void TransformationState::multiplyYScaleBy( double factor )
{
	yScale *= factor;
}

void TransformationState::multiplyZScaleBy( double factor )
{
	zScale *= factor;
}



/* affect the translation
 */		
void TransformationState::addToXTranslation( double amount )
{
	xTranslation += amount;
}

void TransformationState::addToYTranslation( double amount )
{
	yTranslation += amount;
}

void TransformationState::addToZTranslation( double amount )
{
	zTranslation += amount;
}



/* affect the rotation
 */		
void TransformationState::rotateAroundXAxis( double degrees )
{
	TransformationMatrix newRotation;
	newRotation.becomeXRotation( toRadians( degrees ) );
	rotation = newRotation * rotation;
}

void TransformationState::rotateAroundYAxis( double degrees )
{
	TransformationMatrix newRotation;
	newRotation.becomeYRotation( toRadians( degrees ) );
	rotation = newRotation * rotation;
}

void TransformationState::rotateAroundZAxis( double degrees )
{
	TransformationMatrix newRotation;
	newRotation.becomeZRotation( toRadians( degrees ) );
	rotation = newRotation * rotation;
}
