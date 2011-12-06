/*
   Project     : 3DMaze
   File        : view3DMaze.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : contains the definition for ViewWidget,
				 which is used for viewing a 3D maze from afar
*/

#include <assert.h>

#include "view3DMaze.h"

const QColor ViewWidget::bkgrnd_color( 204, 204, 242 );

const double ViewWidget::max_x_translation = 450;
const double ViewWidget::max_y_translation = 450;

const double ViewWidget::max_scale = 6;
const double ViewWidget::min_scale = 0.05;

const double ViewWidget::rotation_increment = 5.0;
const double ViewWidget::translation_increment = 6.0;
const double ViewWidget::scale_multiplier = 1.1;

const double ViewWidget::fovy_angle_ratio_change = 0.92;
const double ViewWidget::initial_fovy_angle = 45.0;
const double ViewWidget::initial_z_coord_of_camera = 1000.0;

const int exit_success = 0;
const Qt::Key quit_button = Qt::Key_Q;


/* construct a ViewWidget with a default translation
 */
ViewWidget::ViewWidget( QWidget * parent /* = NULL */ ) :
	QGLWidget( QGLFormat( QGL::DoubleBuffer | QGL::Rgba | QGL::DepthBuffer ), parent ),
	floorTextureNumber( 0 ),
	wallsTextureNumber( 0 ),
	maze( NULL ),
	stateOfProjection(	initial_fovy_angle,
						initial_z_coord_of_camera,
						z_value_of_far_clipping_plane,
						distance_between_camera_and_near_clipping_plane,
						fovy_angle_ratio_change,
						min_z_coord_of_camera,
						max_z_coord_of_camera )
{

	stateOfTransformation.setUpXScale( min_scale, max_scale, 1 );
	stateOfTransformation.setUpYScale( min_scale, max_scale, 1 );
	stateOfTransformation.setUpZScale( min_scale, max_scale, 1 );
	stateOfTransformation.setUpXTranslation( -max_x_translation, max_x_translation, 0 );
	stateOfTransformation.setUpYTranslation( -max_y_translation, max_y_translation, 0 );
	stateOfTransformation.setUpZTranslation( 0, 0, 0 );

	initializeTransformation();

	setMouseTracking( true );	// so the widget can listen to mouse movement when a mouse button isn't down
	setFocusPolicy( Qt::ClickFocus );	// so the widget can accept keyboard input
	setContextMenuPolicy( Qt::ActionsContextMenu );	// so the widget can respond to context menu requests with it list of actions
}


void ViewWidget::initializeGL()
{
	glEnable( GL_DEPTH_TEST );
}


/* draw the 3-D maze
 */
void ViewWidget::paintGL()
{
	qglClearColor( bkgrnd_color );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glTranslatef( stateOfTransformation.getXTranslation(),
				  stateOfTransformation.getYTranslation(),
				  stateOfTransformation.getZTranslation() );

	glMultMatrixd( stateOfTransformation.getRotationMatrix() );

	glScalef( stateOfTransformation.getXScale(),
			  stateOfTransformation.getYScale(),
			  stateOfTransformation.getZScale() );

	if ( maze != NULL )
	{
		maze->Draw( floorTextureNumber, wallsTextureNumber );
	}
	
	glFlush();
}


/* takes a mouse button input and determines
 * what state of interaction the system will be in
 * ( translating vs. rotating vs. scaling vs. ... )
 */
void ViewWidget::mousePressEvent( QMouseEvent * event )
{
	//if the user pressed the left mouse button
	if( ( ( event->button() & Qt::LeftButton ) != 0 ) )
	{
		//if "shift" is also down
		if( event->modifiers() & Qt::ShiftModifier )
		{
			stateOfUserInteraction.setTranslating();
		}
		//or if "control" is also down
		else if( event->modifiers() & Qt::ControlModifier )
		{
			stateOfUserInteraction.setScaling();
		}
		//or if "alt" is also down
		else if( event->modifiers() & Qt::AltModifier )
		{
			stateOfUserInteraction.setStretching();
		}
		else
		{
			stateOfUserInteraction.setRotating();
		}
	}
	
	stateOfUserInteraction.setLastMousePosition( event->x(), event->y() );
}


/* catch when the mouse button is released
 */
void ViewWidget::mouseReleaseEvent( QMouseEvent * event )
{
	stateOfUserInteraction.reset();

	stateOfUserInteraction.setLastMousePosition( event->x(), event->y() );
}


/* this function does all the work in tranforming mouse movement into 
 * a translation/rotation/scaling of the model
 */
void ViewWidget::mouseMoveEvent( QMouseEvent * event )
{
	makeCurrent();

	bool movedLeft = stateOfUserInteraction.movedMouseLeft( event->x() );
	bool movedRight = stateOfUserInteraction.movedMouseRight( event->x() );
	bool movedUp = stateOfUserInteraction.movedMouseUp( event->y() );
	bool movedDown = stateOfUserInteraction.movedMouseDown( event->y() );

    //if the user is streching the model
	if( stateOfUserInteraction.isStretching() )
    {
        //if the user moves a little up
        if( movedUp )
        {
			stateOfProjection.increaseFishEyeEffect();
        }
        //or down
        else if( movedDown )
        {
			stateOfProjection.decreaseFishEyeEffect();
        }
    	computeFrustum();
		updateGL();
    }
    else
    {
    	//if the user is translating the model
		if( stateOfUserInteraction.isTranslating() )
	    {
	        //if the user moves a little to the right
	        if( movedRight )
	        {
				stateOfTransformation.addToXTranslation( translation_increment );
	        }
	        //or left
	        else if( movedLeft )
	        {
				stateOfTransformation.addToXTranslation( -translation_increment );
	        }
	        //possibly up
	        if( movedUp )
	        {
				stateOfTransformation.addToYTranslation( translation_increment );
	        }
	        //or down
	        else if( movedDown )
	        {
				stateOfTransformation.addToYTranslation( -translation_increment );
	        } 
	    }
	    //if the the user is scaling the model
		else if( stateOfUserInteraction.isScaling() )
	    {
	        //if the user moves a little up
	        if( movedUp )
	        {
				stateOfTransformation.multiplyXScaleBy( scale_multiplier );
				stateOfTransformation.multiplyYScaleBy( scale_multiplier );
				stateOfTransformation.multiplyZScaleBy( scale_multiplier );
	        }
	        //or down
	        else if( movedDown )
	        {
				stateOfTransformation.multiplyXScaleBy( 1/scale_multiplier );
				stateOfTransformation.multiplyYScaleBy( 1/scale_multiplier );
				stateOfTransformation.multiplyZScaleBy( 1/scale_multiplier );
	        } 
	    }
	    
	    //if the user is rotating the model
		else if( stateOfUserInteraction.isRotating() )
	    {
	      //if the user moves a little to the right
	        if( movedRight )
	        {
				stateOfTransformation.rotateAroundYAxis( rotation_increment );
	        }
	        //or left
	        else if( movedLeft )
	        {
				stateOfTransformation.rotateAroundYAxis( -rotation_increment );
	        }
	        //possibly up
	        if( movedUp )
	        {
				stateOfTransformation.rotateAroundXAxis( -rotation_increment );
	        }
	        //or down
	        else if( movedDown )
	        {
				stateOfTransformation.rotateAroundXAxis( rotation_increment );
	        }
		}

		updateGL();
    }
    
    //update the current mouse position
	stateOfUserInteraction.setLastMousePosition( event->x(), event->y() );
}


/* change size handler...
 * lets the user resize the window
 * but keeps everything in the correct perspective
 */
void ViewWidget::resizeGL( int width, int height )
{
    //stop the user from shrinking the window completely 
	if( height == 0 )
    {
        height = 1;
    }
    
    glViewport( 0, 0, width, height );
    
	stateOfProjection.setWidthOfScreen( width );
	stateOfProjection.setHeightOfScreen( height );
    
    computeFrustum();
    
	updateGL();
}


/* computes the viewing frustum
 * given the current state of affairs
 */
void ViewWidget::computeFrustum()
{
	makeCurrent();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
	gluPerspective( stateOfProjection.getFovyAngle(),
					stateOfProjection.getAspectRatio(),
					stateOfProjection.getCameraDistanceToNearClippingPlane(),
					stateOfProjection.getCameraDistanceToFarClippingPlane() );
	gluLookAt( 0.0, 0.0, stateOfProjection.getCameraZPosition(), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}


/* reinitialize the maze's translation, scale, and rotation
 */
void ViewWidget::initializeTransformation()
{
	//set the transformation to be the identity
	stateOfTransformation.reset();

	// tilt the view a bit so the 3D-ness of the model is apparent
	stateOfTransformation.rotateAroundZAxis( 50 );
	stateOfTransformation.rotateAroundXAxis( -70 );
}


/* update to display the given maze with the images speficifed
 */
void ViewWidget::displayMaze3D( const Maze3D * maze3D, const QImage & floorTexture, const QImage & wallsTexture )
{
	assert( !floorTexture.isNull() );
	assert( !wallsTexture.isNull() );

	makeCurrent();

	maze = maze3D;

	// bind the wall and floor textures
	deleteTexture( floorTextureNumber );
	floorTextureNumber = bindTexture( floorTexture, GL_TEXTURE_2D );
	deleteTexture( wallsTextureNumber );
	wallsTextureNumber = bindTexture( wallsTexture, GL_TEXTURE_2D );

	updateGL();
}


/* resets the transformation and projection of the model
 */
void ViewWidget::reinitializeView()
{
	makeCurrent();

	//reinitialize the state of the display
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	initializeTransformation();

	//reset all the viewing properties
	stateOfProjection.setFovyAngle( initial_fovy_angle );
	stateOfProjection.setCameraZPosition( initial_z_coord_of_camera );

	computeFrustum();

	updateGL();
}
