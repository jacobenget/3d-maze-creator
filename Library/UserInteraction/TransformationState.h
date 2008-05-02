/*
   Project     : 3DMaze
   File        : TransformationState.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Describes the total current transformation
   				 for an object that is seperate from the viewer...
   				 at a distance ( this is used to "view" the maze ) 
   				 This class also allows boundaries to be set up 
   				 on all of its values
*/


#ifndef TRANSFORMATIONSTATE_H_
#define TRANSFORMATIONSTATE_H_

#include "TransformationMatrix.h"
#include "BoundsCheckingContainer.h"
#include "ConversionFunctions.h"

class TransformationState
{
	public:
		TransformationState();
		
		/* set up scalar boundaries
		 */
		void setUpXScale( double min, double max, double initialValue );
		void setUpYScale( double min, double max, double initialValue );
		void setUpZScale( double min, double max, double initialValue );
		
		/* set up translation boundaries
		 */
		void setUpXTranslation( double min, double max, double initialValue );
		void setUpYTranslation( double min, double max, double initialValue );
		void setUpZTranslation( double min, double max, double initialValue );
		
		/* resets the transformation to be just the identity
		 */
		void reset();
		
		/* affect the scalar transformation
		 */
		void multiplyXScaleBy( double factor );
		void multiplyYScaleBy( double factor );
		void multiplyZScaleBy( double factor );
		
		/* affect the translation
		 */
		void addToXTranslation( double amount );
		void addToYTranslation( double amount );
		void addToZTranslation( double amount );
		
		/* affect the rotation
		 */
		void rotateAroundXAxis( double degrees );
		void rotateAroundYAxis( double degrees );
		void rotateAroundZAxis( double degrees );
		
		
		double getXScale() const { return xScale.getValue(); }
		double getYScale() const { return yScale.getValue(); }
		double getZScale() const { return zScale.getValue(); }
		
		double getXTranslation() const { return xTranslation.getValue(); }
		double getYTranslation() const { return yTranslation.getValue(); }
		double getZTranslation() const { return zTranslation.getValue(); }
	
		const GLdouble * const getRotationMatrix() const { return rotation.getData(); }
		
	private:
		BoundsCheckingContainer<double> xScale;
		BoundsCheckingContainer<double> yScale;
		BoundsCheckingContainer<double> zScale;
		
		BoundsCheckingContainer<double> xTranslation;
		BoundsCheckingContainer<double> yTranslation;
		BoundsCheckingContainer<double> zTranslation;
		
		TransformationMatrix rotation;
};

#endif /*TRANSFORMATIONSTATE_H_*/
