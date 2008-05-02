/*
   Project     : 3DMaze
   File        : explore3DMaze.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for exploring a 3D-maze
   				 after applying textures to its walls and floors
   				 
   				 
   				 command line syntax:
   				 
   				 explore3DMaze [ 3DMazeFileName ] [ floorTexture.ppm ] [ wallTexture.ppm ]
*/


#include "explore3DMaze.h"

using namespace std;


int main( int argc, char** argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( initial_window_width, initial_window_height );
	glutInitWindowPosition( initial_window_x_position, initial_window_y_position );
	glutCreateWindow( window_title.c_str() );

	glutKeyboardFunc( keyPressed ); 
	glutKeyboardUpFunc( keyReleased ); 
   
	//whenever the mouse moves without a button pressed do this:
	glutPassiveMotionFunc( mouseMoved );
  
	//whenever the mouse moves with a button pressed do this:
	glutMotionFunc( mouseMoved );
  
	glutReshapeFunc( windowChangedSize );
	glutDisplayFunc( renderScene ); 
	glutIdleFunc( renderScene ); 
  
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


/* wait until the next frame has to be rendered,
 * compute the placement of the player based on current movement,
 * and then draw the textured maze
 */
void renderScene()
{
	//wait until the next frame needs to be rendered
	fpsController.waitForNextFrame();
	
	//update the players position
	pStateOfTransformationFP->updatePosition( *pMaze, *pStateOfUserInteractionFP );
	
	//set up the drawing environment
	glClearColor( bkgrnd_color_r, bkgrnd_color_g , bkgrnd_color_b, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	//tilt the camera towards where the player is looking
	glRotatef( pStateOfTransformationFP->getTiltAngleDegrees(), 1.0, 0.0, 0.0 );
    glRotatef( pStateOfTransformationFP->getSpinAngleDegrees(), 0.0, 1.0, 0.0 );
    //tranlate the world so that the character inside it at the right place
    glTranslatef( -pStateOfTransformationFP->getXPositionOffset(), 
    			  -pStateOfTransformationFP->getYPositionOffset(), 
    			  -pStateOfTransformationFP->getZPositionOffset() );
    
    //tilt everything upright
    glRotatef( global_x_tilt, 1.0, 0.0, 0.0 );
    
    //draw the maze
    pMaze->Draw( floorTextureNumber, wallsTextureNumber );
    
    //if the user is changing their perspective
    if( pStateOfUserInteractionFP->isZoomingIn() )
    {
    	pStateOfProjection->decreaseFishEyeEffect();
    }
    else if( pStateOfUserInteractionFP->isZoomingOut() )
    {
    	pStateOfProjection->increaseFishEyeEffect();
    }
    
	computeFrustum();
    glFlush();
    glutSwapBuffers();
}


/* keyboard input handler for pressing a key
 * responds to key commands for movement,
 * changing perspective, and quiting
 */
void keyPressed( unsigned char key, int x, int y )
{
	switch( key )
	{
		case quit_button:			exit( exit_success );
									break;
									
		case strafe_left_button: 	pStateOfUserInteractionFP->setStrafingLeft( true );
									break;
									
		case strafe_right_button: 	pStateOfUserInteractionFP->setStrafingRight( true );
									break;
									
		case move_backward_button: 	pStateOfUserInteractionFP->setMovingBackward( true );
									break;
									
		case move_forward_button: 	pStateOfUserInteractionFP->setMovingForward( true );
									break;
									
		case zoom_out_button: 		pStateOfUserInteractionFP->setZoomingOut( true );
									break;
									
		case zoom_in_button: 		pStateOfUserInteractionFP->setZoomingIn( true );
									break;
									
		case jump_button:			pStateOfTransformationFP->jump();
									break;
									
		default:					break;
	}
}


/* keyboard input handler for letting up on a key
 * responds to key commands for movement,
 * and changing perspective
 */
void keyReleased( unsigned char key, int x, int y )
{
	switch( key )
	{
		case strafe_left_button: 	pStateOfUserInteractionFP->setStrafingLeft( false );
									break;
									
		case strafe_right_button: 	pStateOfUserInteractionFP->setStrafingRight( false );
									break;
									
		case move_backward_button: 	pStateOfUserInteractionFP->setMovingBackward( false );
									break;
									
		case move_forward_button: 	pStateOfUserInteractionFP->setMovingForward( false );
									break;
									
		case zoom_out_button: 		pStateOfUserInteractionFP->setZoomingOut( false );
									break;
									
		case zoom_in_button: 		pStateOfUserInteractionFP->setZoomingIn( false );
									break;
									
		default:					break;
	}
}


/* rotates the world based on user input with the mouse
 */
void mouseMoved( int x, int y )
{ 
    //if rotating down to up, 
    if( pStateOfUserInteractionFP->mouseMovedUp( y ) )
    {
        pStateOfTransformationFP->lookUp( incremental_angle_change );
    }
    //if rotating up to down, 
    else if( pStateOfUserInteractionFP->mouseMovedDown( y ) )
    {
        pStateOfTransformationFP->lookDown( incremental_angle_change );
    }
    //if rotating left to right, 
    if( pStateOfUserInteractionFP->mouseMovedRight( x ) )
    {
        pStateOfTransformationFP->lookRight( incremental_angle_change );
    }
    //if rotating right to left,
    else if( pStateOfUserInteractionFP->mouseMovedLeft( x ) )
    {
        pStateOfTransformationFP->lookLeft( incremental_angle_change );
    }
    
    //update the current mouse position
    pStateOfUserInteractionFP->setLastMousePosition( x, y );
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
    
    gluLookAt( 0.0, 0.0, pStateOfProjection->getCameraZPosition(), 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 );
}


/* change size handler...
 * lets the user resize  the window 
 * but keeps everything in the correct perspective
 */
void windowChangedSize( int width, int height )
{
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

