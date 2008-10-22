/*
   Project     : 3DMaze
   File        : edit2DMaze.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for reading in, editing, and
   				 writing out a file for a 2D maze
   				 
   				 
   				 command line syntax:
   				 
   				 edit2DMaze [ 2DMazeFileName ]
*/


#include "edit2DMaze.h"

using namespace std;

Maze2D * pMaze;
Point2D lastPointClicked;
Point2D mouseCursor;
bool drawLineToCursor = false;
std::string maze2DfileName = default_2D_maze_file_name;
double lineWidth = 1.0;

int main( int argc, char** argv )
{
	pMaze = new Maze2D( maze_width, maze_height );
		
	//try to read in the 2-D maze file
	if( argc > 1 )
	{ 
		maze2DfileName = argv[ 1 ];
	}
	try
	{
		FileHandler File( maze2DfileName );
		File.ReadFromFile( *pMaze );
	}
	//an error will come up if the file doesn't exist
	//which is ok....we'll just continue with a blank maze
	catch ( IOError  & ignore ) { }
	
	glutInit( &argc,argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize( initial_window_width, initial_window_height );
	glutInitWindowPosition( initial_window_x_position, initial_window_x_position );
	glutCreateWindow( window_title.c_str() );     
	
	glutKeyboardFunc( keyPressed ); 
	glutMouseFunc( mouseButtonPressed );
	glutPassiveMotionFunc( mouseMoved );
	glutMotionFunc( mouseMoved );
	glutReshapeFunc( windowChangedSize );
	glutDisplayFunc( renderScene ); 
	
	//create and attach the menu options
	glutCreateMenu( menuCallback );
	glutAddMenuEntry( menu_save_option_label.c_str(), menu_save_option_number );
	glutAddMenuEntry( menu_saveAndQuit_option_label.c_str(), menu_saveAndQuit_option_number );
	glutAddMenuEntry( menu_clear_option_label.c_str(), menu_clear_option_number );
	glutAddMenuEntry( menu_quit_option_label.c_str(), menu_quit_option_number );
	glutAttachMenu( GLUT_RIGHT_BUTTON );
	
	/* find a medium sized line width
	 * to use to draw the walls of the maze
	 */
	GLfloat sizes[2];
	GLfloat step;
		
	glGetFloatv( GL_LINE_WIDTH_RANGE, sizes );
	glGetFloatv( GL_LINE_WIDTH_GRANULARITY, &step );
	int stepsAvailable = ( int ) ( ( sizes[1] - sizes[0] ) / step );
	//lineWidth will be about halfway between the thinnest and thickest possible line
	lineWidth = sizes[0] + ( step ) * ( stepsAvailable / 2 );
	
	glutMainLoop();
	  
	return exit_success;
}


/* erase all work done on the maze
 * leaving just the bounding walls
 */
void setMazeToDefault() 
{
	pMaze->clear();
	glutPostRedisplay();
}


/* account for the fact that openGL places the point ( 0, 0 ) 
 * at the top left of the screen, while I want ( 0, 0 ) to
 * be at the center of the screen
 */ 
Point2D convertPointToCoordinatesSystem( int x, int y )
{
	return Point2D( x - initial_window_width/2, initial_window_height/2 - y );
}


/* color in the background, draw and color the 2-D maze,
 * and draw a small "you will be here" triangle
 */  
void renderScene()
{
	glClearColor( bkgrd_color_r, bkgrd_color_g , bkgrd_color_b, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT );

	glLineWidth( lineWidth );

	shadeInsideOfMaze();
	
	glColor3f( walls_color_r, walls_color_g ,walls_color_b );
	
	//draw the walls of the maze
	pMaze->Draw();
    
    glBegin( GL_LINES ); 
    //if the user hasn't lifted up their pen, draw the current pen line
    if( drawLineToCursor )
    {
    	glVertex2f( lastPointClicked.getX(), lastPointClicked.getY() );
    	glVertex2f( mouseCursor.getX(), mouseCursor.getY() );
    }
    glEnd();
    
    /* draw an icon which represents the user's placement if and when 
     * the user wishes to explore this maze in First Person
     */
    drawFigureIcon();
    
    glFlush(); 
    glutSwapBuffers();
}


void shadeInsideOfMaze()
{
	glColor3f( inside_maze_color_r, inside_maze_color_g ,inside_maze_color_b );
	glBegin( GL_TRIANGLES ); 
	
	glVertex2f( -( maze_width / 2 ), ( maze_height / 2 ) );
	glVertex2f( ( maze_width / 2 ), ( maze_height / 2 ) );
	glVertex2f( ( maze_width / 2 ), -( maze_height / 2 ) );
	glVertex2f( ( maze_width / 2 ), -( maze_height / 2 ) );
	glVertex2f( -( maze_width / 2 ), -( maze_height / 2 ) );
	glVertex2f( -( maze_width / 2 ), ( maze_height / 2 ) );
	
	glEnd();
}


void drawFigureIcon()
{
	glColor3f( figure_color_r, figure_color_g ,figure_color_b );
	glBegin( GL_TRIANGLES ); 
	
	glVertex2f( -6, -3 );
	glVertex2f( 6, -3 );
	glVertex2f( 0, 15 );
	
	glEnd();
}

/* keyboard input handler....responds to 
 * the quit_button (defined in the header) for quiting
 * and allows the user to lift up their drawing pen
 */
void keyPressed( unsigned char key, int x, int y )
{
	switch( key )
	{
		case quit_button:			
			exit( exit_success );
			break;
							
		case lift_up_pen_button:	
			drawLineToCursor = !drawLineToCursor;
			glutPostRedisplay();
			break;
			
		default:
			break;
	}
}


/* callback for handling mouse button presses
 */
void mouseButtonPressed( int button, int state, int x, int y )
{
	//if the user pressed the left mouse button
	if( ( state == GLUT_DOWN ) && ( button == GLUT_LEFT_BUTTON ) )
	{
		mouseCursor = convertPointToCoordinatesSystem( x, y );
		//if the user had thier pen down
		if( drawLineToCursor )
		{
			//then you know to create a new line for this maze
			LineSegment2D line( lastPointClicked, mouseCursor );
			pMaze->addALine( line );
		}
    
		//now the user has their pen down
		drawLineToCursor = true;
		lastPointClicked = convertPointToCoordinatesSystem( x, y );
		glutPostRedisplay();
	}
}


/* callback for hanlding mouse movement
 */
void mouseMoved( int x, int y )
{
	mouseCursor = convertPointToCoordinatesSystem( x, y );
	if( drawLineToCursor ) glutPostRedisplay();
}


/* change size handler...keeps the user from altering the size of the window
 * (the window will snap back to its original size when the user tries to resize it)
 */
void windowChangedSize( int width, int height )
{
	glViewport( 0, 0, initial_window_width, initial_window_height );
  
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -initial_window_width/2, initial_window_width/2, -initial_window_height/2, initial_window_height/2, -1.0, 1.0 );
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glutReshapeWindow( initial_window_width, initial_window_height );
	
	glutPostRedisplay();
}


/* save the 2D maze out to a file
 */
void saveMaze()
{
  	try
	{
		WriteFile( maze2DfileName, *pMaze );
	}
	catch ( UserWishesToExitException & ue )
	{
		cout << "goodbye";
		exit( exit_success );
	}
}

/* handles the actions of the menu, when a menu choice has been chosen
 */
void menuCallback( int option_number )
{
	switch( option_number )
	{
		case menu_save_option_number:
			//save but don't quit
			saveMaze();
			break;
		case menu_saveAndQuit_option_number:
			//save and quit
			saveMaze();
			exit( exit_success );
			break;
		case menu_clear_option_number:
			//clear maze
			setMazeToDefault();
			break;
		case menu_quit_option_number:
			exit( exit_success );
			break;
		default:
			break;
	}
}
