/*
   Project     : 3DMaze
   File        : view3DMaze.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for viewing a 3D-maze
   				 after applying textures to its walls and floors
   				 
   				 
   				 command line syntax:
   				 
   				 view3Dmaze [ 3DMazeFileName ] [ floorTexture.ppm ] [ wallTexture.ppm ]
*/


#include "view3DMaze.h"

using namespace std;


int main( int argc, char** argv )
{
	glutInit( &argc,argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( initial_window_width, initial_window_height );
	glutInitWindowPosition( initial_window_x_position, initial_window_y_position );
	glutCreateWindow( window_title.c_str() );
	glutKeyboardFunc( keyPressed );
	
	//whenever a mouse button is pressed do this:
	glutMouseFunc( mouseButtonPressed );
	
	//whenever the mouse moves without a button pressed do this:
	glutPassiveMotionFunc( mouseMoved );
	
	//whenever the mouse moves with a button pressed do this:
	glutMotionFunc( mouseMoved );
	
	//set up the menu option
	glutCreateMenu( menuCallback );
	glutAddMenuEntry( "Reinitialize", 1 );
	glutAttachMenu( GLUT_RIGHT_BUTTON );
	
	glutReshapeFunc( windowChangedSize );
	glutDisplayFunc( renderScene );
	
	glEnable( GL_DEPTH_TEST );
	
	//try to initialize the rest of the environment
	try
	{
		initEnvironment( argc, argv );
	}
	catch ( UserWishesToExitException & ue )
	{
		cout << "goodbye!";
		return exit_success;
	}
  	
	glutMainLoop();
	
	//we'll never really get here because glutMainLoop should never return.
	//But just in case, we'll clean up our dynamic variables
	ReleaseStaticVariables();
	
	return exit_success;
}


/* draw the 3-D maze
 * ( all transformations are computed outside (prior to) this function )
 */
void renderScene()
{
	glClearColor( bkgrnd_color_r, bkgrnd_color_g , bkgrnd_color_b, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	pMaze->Draw( floorTextureNumber, wallsTextureNumber );
	
	glFlush();
	glutSwapBuffers(); 
}

/* keyboard input handler....responds to 
 * the quit_button (defined in the header) for quiting
 * and allows the user to lift up their drawing pen
 */
void keyPressed( unsigned char key, int x, int y )
{
	if ( key== quit_button )
	{
		ReleaseStaticVariables();
		exit( exit_success );
	}
}


/* takes a mouse button input and determines
 * what state of interaction the system will be in
 * ( translating vs. rotating vs. scaling vs. ... )
 */
void mouseButtonPressed( int button, int state, int x, int y )
{
	//if the left botton is down
	if( ( state == GLUT_DOWN ) && ( button == GLUT_LEFT_BUTTON ) )
	{
		//if "control" is also down
		if( glutGetModifiers() == GLUT_ACTIVE_SHIFT )
		{
			pStateOfUserInteraction->setTranslating();
		}
		else if( glutGetModifiers() == GLUT_ACTIVE_CTRL )
		{
			pStateOfUserInteraction->setScaling();
		}
		else if( glutGetModifiers() == GLUT_ACTIVE_ALT )
		{
			pStateOfUserInteraction->setStretching();
		}
		else
		{
			pStateOfUserInteraction->setRotating();
		}
	}
	else
	{
		pStateOfUserInteraction->reset();
	}
	
	pStateOfUserInteraction->setLastMousePosition( x, y );
}


/* this function does all the work in tranforming mouse movement into 
 * a translation/rotation/scaling of the model
 */
void mouseMoved( int x, int y )
{
	bool movedLeft = pStateOfUserInteraction->movedMouseLeft( x );
	bool movedRight = pStateOfUserInteraction->movedMouseRight( x );
	bool movedUp = pStateOfUserInteraction->movedMouseUp( y );
	bool movedDown = pStateOfUserInteraction->movedMouseDown( y );

    //if the user is streching the model
    if( pStateOfUserInteraction->isStretching() )
    {
        //if the user moves a little up
        if( movedUp )
        {
        	pStateOfProjection->increaseFishEyeEffect();
        }
        //or down
        else if( movedDown )
        {
        	pStateOfProjection->decreaseFishEyeEffect();
        }
    	computeFrustum();
    	glutPostRedisplay();
    }
    
    else
    {
    	//if the user is translating the model
    	if( pStateOfUserInteraction->isTranslating() )
	    {
	        //if the user moves a little to the right
	        if( movedRight )
	        {
	        	pStateOfTransformation->addToXTranslation( translation_increment );
	        }
	        //or left
	        else if( movedLeft )
	        {
	        	pStateOfTransformation->addToXTranslation( -translation_increment );
	        }
	        //possibly up
	        if( movedUp )
	        {
	        	pStateOfTransformation->addToYTranslation( translation_increment );
	        }
	        //or down
	        else if( movedDown )
	        {
	        	pStateOfTransformation->addToYTranslation( -translation_increment );
	        } 
	    }
	    //if the the user is scaling the model
	    else if( pStateOfUserInteraction->isScaling() )
	    {
	        //if the user moves a little up
	        if( movedUp )
	        {
	        	pStateOfTransformation->multiplyXScaleBy( scale_multiplier );
	        	pStateOfTransformation->multiplyYScaleBy( scale_multiplier );
	        	pStateOfTransformation->multiplyZScaleBy( scale_multiplier );
	        }
	        //or down
	        else if( movedDown )
	        {
	        	pStateOfTransformation->multiplyXScaleBy( 1/scale_multiplier );
	        	pStateOfTransformation->multiplyYScaleBy( 1/scale_multiplier );
	        	pStateOfTransformation->multiplyZScaleBy( 1/scale_multiplier );
	        } 
	    }
	    
	    //if the user is rotating the model
	    else if( pStateOfUserInteraction->isRotating() )
	    {
	      //if the user moves a little to the right
	        if( movedRight )
	        {
	        	pStateOfTransformation->rotateAroundYAxis( rotation_increment );
	        }
	        //or left
	        else if( movedLeft )
	        {
	        	pStateOfTransformation->rotateAroundYAxis( -rotation_increment );
	        }
	        //possibly up
	        if( movedUp )
	        {
	        	pStateOfTransformation->rotateAroundXAxis( -rotation_increment );
	        }
	        //or down
	        else if( movedDown )
	        {
	        	pStateOfTransformation->rotateAroundXAxis( rotation_increment );
	        }
	    }
	    
    	/* now that all the logic has been performed to determine
    	 * how the user is affecting the model, now actually affect
    	 * the model and redraw it
    	 */
	    glMatrixMode( GL_MODELVIEW );
	    glLoadIdentity();
	  
	    glTranslatef( pStateOfTransformation->getXTranslation(), 
	    			  pStateOfTransformation->getYTranslation(), 
	    			  pStateOfTransformation->getZTranslation() );
	
	    glMultMatrixd( pStateOfTransformation->getRotationMatrix() );
	    
	    glScalef( pStateOfTransformation->getXScale(), 
				  pStateOfTransformation->getYScale(), 
				  pStateOfTransformation->getZScale() );
	  
	    glutPostRedisplay();
    }
    
    //update the current mouse position
	pStateOfUserInteraction->setLastMousePosition( x, y );
}


/* change size handler...
 * lets the user resize  the window 
 * but keeps everything in the correct perspective
 */
void windowChangedSize( int width, int height )
{
    //stop the user from shrinking the window completely 
	if( height == 0 )
    {
        height = 1;
    }
    
    glViewport( 0, 0, width, height );
    
    pStateOfProjection->setWidthOfScreen( width );
    pStateOfProjection->setHeightOfScreen( height );
    
    computeFrustum();
    
    glutPostRedisplay();
}


/* computes the viewing frustum
 * given the current state of affairs
 */
void computeFrustum()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    gluPerspective( pStateOfProjection->getFovyAngle(), 
    			 	pStateOfProjection->getAspectRatio(),
    			 	pStateOfProjection->getCameraDistanceToNearClippingPlane(),  
                    pStateOfProjection->getCameraDistanceToFarClippingPlane() );
    gluLookAt( 0.0, 0.0, pStateOfProjection->getCameraZPosition(), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}


/* this is the callback for handling the 
 * actions of the right mouse button menu
 */
void menuCallback( int option_number )
{
  switch( option_number )
  {
  	case 1:
  		//reinitialize the state of the display
  		glMatrixMode( GL_MODELVIEW );
  		glLoadIdentity();
     
  		//set the transformation to be the identity
  		pStateOfTransformation->reset();
  		
  		//reset all the viewing properties
  		pStateOfProjection->setFovyAngle( initial_fovy_angle );
  		pStateOfProjection->setCameraZPosition( initial_z_coord_of_camera );

  		computeFrustum();
    
  		glutPostRedisplay();
  		break;
  }
}
