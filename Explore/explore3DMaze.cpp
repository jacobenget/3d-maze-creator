/*
   Project     : 3DMaze
   File        : explore3DMaze.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : contains the definition for ExploreWidget,
				 which is used for exploring a 3D maze in first-person view
				 with basic WASD move controls and mouse-look
*/


#include "explore3DMaze.h"

#include <GL/glu.h>		// this will need to be smarter for Mac builds (possibly by including <OpenGL/glu.h> instead

const int exit_success = 0;

const QColor ExploreWidget::bkgrnd_color( 179, 179, 230 );

const double ExploreWidget::global_x_tilt = -90.0;

const double ExploreWidget::fovy_angle_ratio_change = 0.985;
const double ExploreWidget::initial_fovy_angle = 90.0;
const double ExploreWidget::initial_z_coord_of_camera = 0.0;

const double ExploreWidget::distance_between_camera_and_near_clipping_plane = 1;

const double ExploreWidget::incremental_angle_change = 3.0;  //in degrees
const double ExploreWidget::incremental_position_change = 2.0;
const double ExploreWidget::jump_velocity = 3.0;

//buffer between player and walls, so the walls don't clip when the user collids with them
//should NOT be larger than the width of the walls divided by incremental_position_change
const double ExploreWidget::buffer_distance = 2.0;

const Qt::Key ExploreWidget::release_focus_button = Qt::Key_Q;
const Qt::Key ExploreWidget::move_forward_button = Qt::Key_W;
const Qt::Key ExploreWidget::move_backward_button = Qt::Key_S;
const Qt::Key ExploreWidget::strafe_right_button = Qt::Key_D;
const Qt::Key ExploreWidget::strafe_left_button = Qt::Key_A;
const Qt::Key ExploreWidget::jump_button = Qt::Key_Space;
const Qt::Key ExploreWidget::zoom_in_button = Qt::Key_C;
const Qt::Key ExploreWidget::zoom_out_button = Qt::Key_R;


ExploreWidget::ExploreWidget( const Maze3D & maze_, const QImage & floorTexture_, const QImage & wallsTexture_, QWidget * parent /*= NULL*/ ) :
	QGLWidget( QGLFormat( QGL::DoubleBuffer | QGL::Rgba | QGL::DepthBuffer ), parent ),
	maze( maze_ ),
	floorTexture( floorTexture_ ),
	wallsTexture( wallsTexture_ ),
	floorTextureNumber( 0 ),
	wallsTextureNumber( 0 ),
	stateOfProjection(	initial_fovy_angle,
						initial_z_coord_of_camera,
						z_value_of_far_clipping_plane,
						distance_between_camera_and_near_clipping_plane,
						fovy_angle_ratio_change,
						min_z_coord_of_camera,
						max_z_coord_of_camera ),
	stateOfTransformationFP(	incremental_position_change,
								incremental_position_change,
								jump_velocity,
								buffer_distance ),
	timesCursorHidden( 0 )
{
	setMouseTracking( true );	// so the widget can listen to mouse movement when a mouse button isn't down
	setFocusPolicy( Qt::ClickFocus );	// so the widget can accept keyboard input
}


/* make sure the cursor is no longer hidden when this widget is detroyed
 */
ExploreWidget::~ExploreWidget()
{
	stopHidingCursor();
}


void ExploreWidget::initializeGL()
{
	glEnable( GL_DEPTH_TEST );

	//register the floor texture
	floorTextureNumber = bindTexture( floorTexture, GL_TEXTURE_2D );

	//register the wall texture
	wallsTextureNumber = bindTexture( wallsTexture, GL_TEXTURE_2D );

	// set up a timer to control the frame rate
	QTimer * redrawTimer = new QTimer( this );
	connect( redrawTimer, SIGNAL( timeout() ), this, SLOT( updateGL() ) );
	redrawTimer->start( 1000 / frames_per_second );
}


/* compute the placement of the player based on current movement,
 * and then draw the textured maze
 */
void ExploreWidget::paintGL()
{
	//update the players position
	stateOfTransformationFP.updatePosition( maze, stateOfUserInteractionFP );
	
	//set up the drawing environment
	qglClearColor( bkgrnd_color );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	//tilt the camera towards where the player is looking
	glRotatef( stateOfTransformationFP.getTiltAngleDegrees(), 1.0, 0.0, 0.0 );
	glRotatef( stateOfTransformationFP.getSpinAngleDegrees(), 0.0, 1.0, 0.0 );
    //tranlate the world so that the character inside it at the right place
	glTranslatef( -stateOfTransformationFP.getXPositionOffset(),
				  -stateOfTransformationFP.getYPositionOffset(),
				  -stateOfTransformationFP.getZPositionOffset() );
    
    //tilt everything upright
    glRotatef( global_x_tilt, 1.0, 0.0, 0.0 );
    
    //draw the maze
	maze.Draw( floorTextureNumber, wallsTextureNumber );
    
    //if the user is changing their perspective
	if( stateOfUserInteractionFP.isZoomingIn() )
    {
		stateOfProjection.decreaseFishEyeEffect();
    }
	else if( stateOfUserInteractionFP.isZoomingOut() )
    {
		stateOfProjection.increaseFishEyeEffect();
    }
    
	computeFrustum();

	// if this widget has focus then
	// draw instructions on how to close this widget or force it to release the mouse
	if ( hasFocus() )
	{
		QKeySequence quitSequence( Qt::Key_Escape );
		QString quitInstructions = QString( "Press %1 to quit exploring" ).arg( quitSequence.toString() );
		QKeySequence releaseFocusSequence( release_focus_button );
		QString releaseMouseInstructions = QString( "Press %1 to release the mouse" ).arg( releaseFocusSequence.toString() );

		QFont font;
		QFontMetrics fontMetrics( font );

		QRect instructionsRect = fontMetrics.boundingRect( quitInstructions );
		int padding = 4;
		renderText( padding, padding + instructionsRect.height(), quitInstructions, font );
		renderText( padding, 2 * ( padding + instructionsRect.height() ), releaseMouseInstructions, font );
	}

	glFlush();
}


/* keyboard input handler for pressing a key
 * responds to key commands for movement,
 * changing perspective, and quiting
 */
void ExploreWidget::keyPressEvent( QKeyEvent * event )
{
	Qt::Key pressedKey = static_cast< Qt::Key >( event->key() );
	switch( pressedKey )
	{
		case release_focus_button:	stopHidingCursor();
									emit stealMyFocus();
									break;
									
		case strafe_left_button: 	stateOfUserInteractionFP.setStrafingLeft( true );
									break;
									
		case strafe_right_button: 	stateOfUserInteractionFP.setStrafingRight( true );
									break;
									
		case move_backward_button: 	stateOfUserInteractionFP.setMovingBackward( true );
									break;
									
		case move_forward_button: 	stateOfUserInteractionFP.setMovingForward( true );
									break;
									
		case zoom_out_button: 		stateOfUserInteractionFP.setZoomingOut( true );
									break;
									
		case zoom_in_button: 		stateOfUserInteractionFP.setZoomingIn( true );
									break;
									
		case jump_button:			stateOfTransformationFP.jump();
									break;
									
		default:					QGLWidget::keyPressEvent( event );
									break;
	}
	updateGL();
}


/* keyboard input handler for letting up on a key
 * responds to key commands for movement,
 * and changing perspective
 */
void ExploreWidget::keyReleaseEvent( QKeyEvent * event )
{
	Qt::Key pressedKey = static_cast< Qt::Key >( event->key() );
	switch( pressedKey )
	{
		case strafe_left_button: 	stateOfUserInteractionFP.setStrafingLeft( false );
									break;
									
		case strafe_right_button: 	stateOfUserInteractionFP.setStrafingRight( false );
									break;
									
		case move_backward_button: 	stateOfUserInteractionFP.setMovingBackward( false );
									break;
									
		case move_forward_button: 	stateOfUserInteractionFP.setMovingForward( false );
									break;
									
		case zoom_out_button: 		stateOfUserInteractionFP.setZoomingOut( false );
									break;
									
		case zoom_in_button: 		stateOfUserInteractionFP.setZoomingIn( false );
									break;
									
	default:						QGLWidget::keyReleaseEvent( event );
									break;
	}
	updateGL();
}


/* rotates the world based on user input with the mouse
 */
void ExploreWidget::mouseMoveEvent( QMouseEvent * event )
{
	// only listen to mouse events if focus is had
	if ( !hasFocus() )
	{
		return;
	}

    //if rotating down to up, 
	if( stateOfUserInteractionFP.mouseMovedUp( event->y() ) )
    {
		stateOfTransformationFP.lookUp( incremental_angle_change );
    }
    //if rotating up to down, 
	else if( stateOfUserInteractionFP.mouseMovedDown( event->y() ) )
    {
		stateOfTransformationFP.lookDown( incremental_angle_change );
    }
    //if rotating left to right, 
	if( stateOfUserInteractionFP.mouseMovedRight( event->x() ) )
    {
		stateOfTransformationFP.lookRight( incremental_angle_change );
    }
    //if rotating right to left,
	else if( stateOfUserInteractionFP.mouseMovedLeft( event->x() ) )
    {
		stateOfTransformationFP.lookLeft( incremental_angle_change );
	}

	// reposition the cursor to the middle of the screen
	QCursor::setPos( mapToGlobal( QPoint( width() / 2, height() / 2 ) ) );

	//update the current mouse position
	stateOfUserInteractionFP.setLastMousePosition( width() / 2, height() / 2 );
}


/* hide the cursor when focus is received, show the cursor otherwise
 */
void ExploreWidget::focusInEvent( QFocusEvent * event )
{
	if ( event->gotFocus() )
	{
		hideCursor();
	}
	else if ( event->lostFocus() )
	{
		stopHidingCursor();
	}
}


/* computes the viewing frustum
 * given the current state of affairs
 */
void ExploreWidget::computeFrustum()
{
	makeCurrent();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
	gluPerspective( stateOfProjection.getFovyAngle(),
					stateOfProjection.getAspectRatio(),
					stateOfProjection.getCameraDistanceToNearClippingPlane(),
					stateOfProjection.getCameraDistanceToFarClippingPlane() );
    
	gluLookAt( 0.0, 0.0, stateOfProjection.getCameraZPosition(), 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 );
}


/* hide the cursor
 */
void ExploreWidget::hideCursor()
{
	QApplication::setOverrideCursor( Qt::BlankCursor );
	timesCursorHidden++;
}


/* undo all the times we've hid the cursor
 */
void ExploreWidget::stopHidingCursor()
{
	while ( timesCursorHidden > 0 )
	{
		QApplication::restoreOverrideCursor();
		timesCursorHidden--;
	}
}


/* change size handler...
 * lets the user resize  the window 
 * but keeps everything in the correct perspective
 */
void ExploreWidget::resizeGL( int width, int height )
{
	makeCurrent();

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

