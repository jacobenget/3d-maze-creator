/*
   Project     : 3DMaze
   File        : BoundsCheckingContainer.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Provides the control needed to guarantee that
   				 a "value" is always withing a specific range 
*/


#ifndef BOUNDSCHECKINGCONTAINER_H_
#define BOUNDSCHECKINGCONTAINER_H_

template <typename ValueType>

class BoundsCheckingContainer
{
	public:
		BoundsCheckingContainer( ValueType m_max = 0, ValueType m_min = 0 ) :
			max( m_max ),
			min( m_min ),
			currentValue( min ) {}  //default the value to min
		
		void setMax( ValueType newMax )	
		{	
			max = newMax;
			this->operator=( getValue() );
		}
		
		void setMin( ValueType newMin )
		{	
			min = newMin; 
			this->operator=( getValue() );
		}
		
		/* this operator does the work of bounds checking
		 * ( equals assignment will return void because piping 
		 * this operation might have unexpected results due to 
		 * the limits set on this type of container )
		 */
		void operator=( const ValueType & newValue )	
		{	
			if( newValue > max )
			{
				currentValue = max; 
			}
			else if( newValue < min )
			{
				currentValue = min; 
			}
			else
			{
				currentValue = newValue;
			}
		}
		
		void operator+=( const ValueType & factor )
		{
			this->operator =( getValue() + factor );
		}
		
		void operator*=( const ValueType & factor )
		{
			this->operator =( getValue() * factor );
		}
		
		ValueType getValue() const	{	return currentValue; }
		
	private:
		ValueType max;
		ValueType min;
		ValueType currentValue;
};

#endif /*BOUNDSCHECKINGCONTAINER_H_*/
