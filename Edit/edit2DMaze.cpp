/*
   Project     : 3DMaze
   File        : edit2DMaze.cpp
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for reading in, editing, and
   				 writing out a file for a 2D maze
   				 
   				 
   				 command line syntax:
   				 
   				 edit2DMaze [ 2DMazeFileName ]
*/

#include <assert.h>
#include "edit2DMaze.h"
#include "Maze3D.h"

const QColor EditWidget::walls_color( 26, 26, 26 );
const QColor EditWidget::bkgrd_color( 102, 102, 102 );
const QColor EditWidget::inside_maze_color( 205, 205, 205 );
const QColor EditWidget::figure_color( 178, 77, 77 );

const float EditWidget::maxMazeToAllScreenRatio = 0.75f;
const QString EditWidget::mazeFileExtension = "maze";
const QString EditWidget::default_maze_file_name = "unnamed";

const int exit_success = 0;
const Qt::Key quit_button = Qt::Key_Q;
const Qt::Key lift_up_pen_button = Qt::Key_Space;

EditWidget::EditWidget( QWidget * parent /* = NULL */ ) :
	QGLWidget( QGLFormat( QGL::DoubleBuffer | QGL::Rgba ), parent ),
	maze( 450, 450 ),
	drawLineToCursor( false ),
	maze2DfileName( default_maze_file_name ),
	lineWidth( 1.0 ) {

	setMouseTracking( true );	// so the widget can listen to mouse movement when a mouse button isn't down
	setFocusPolicy( Qt::ClickFocus );	// so the widget can accept keyboard input
	setContextMenuPolicy( Qt::ActionsContextMenu );	// so the widget can respond to context menu requests with it list of actions
}

void EditWidget::initializeGL()
{

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
}


/* change size handler...keeps the user from altering the size of the window
 * (the window will snap back to its original size when the user tries to resize it)
 */
void EditWidget::resizeGL( int width, int height )
{
	glViewport( 0, 0, width, height );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	float idealWidth = maze.getWidth() / maxMazeToAllScreenRatio;
	float idealHeight = maze.getHeight() / maxMazeToAllScreenRatio;
	float idealRatio = idealWidth / idealHeight;
	float currentRatio = ( ( float ) width ) / height;
	if ( currentRatio > idealRatio )
	{
		// constrained by height of window
		glOrtho( -( currentRatio / idealRatio ) * idealWidth / 2, ( currentRatio / idealRatio ) * idealWidth / 2, -idealHeight / 2, idealHeight / 2, -1.0, 1.0 );
	}
	else
	{
		// constrained by width of window
		glOrtho( -idealWidth / 2, idealWidth / 2, -( idealRatio / currentRatio ) * idealHeight / 2, ( idealRatio / currentRatio ) * idealHeight / 2, -1.0, 1.0 );
	}

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	updateGL();
}

/* color in the background, draw and color the 2-D maze,
 * and draw a small "you will be here" triangle
 */
void EditWidget::paintGL()
{
	qglClearColor( bkgrd_color );
	glClear( GL_COLOR_BUFFER_BIT );

	glLineWidth( lineWidth );

	// shade inside of maze
	{
		qglColor( inside_maze_color );
		glBegin( GL_TRIANGLES );

		glVertex2f( -( maze.getWidth() / 2 ), ( maze.getHeight() / 2 ) );
		glVertex2f( ( maze.getWidth() / 2 ), ( maze.getHeight() / 2 ) );
		glVertex2f( ( maze.getWidth() / 2 ), -( maze.getHeight() / 2 ) );
		glVertex2f( ( maze.getWidth() / 2 ), -( maze.getHeight() / 2 ) );
		glVertex2f( -( maze.getWidth() / 2 ), -( maze.getHeight() / 2 ) );
		glVertex2f( -( maze.getWidth() / 2 ), ( maze.getHeight() / 2 ) );

		glEnd();
	}

	qglColor( walls_color );

	//draw the walls of the maze
	maze.Draw();

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
	{
		qglColor( figure_color );
		glBegin( GL_TRIANGLES );

		glVertex2f( -6, -3 );
		glVertex2f( 6, -3 );
		glVertex2f( 0, 15 );

		glEnd();
	}

	glFlush();
}

void EditWidget::mousePressEvent( QMouseEvent * event )
{
	//if the user pressed the left mouse button
	if( ( ( event->button() & Qt::LeftButton ) != 0 ) )
	{
		mouseCursor = convertPointToCoordinatesSystem( event->x(), event->y() );
		//if the user had thier pen down
		if( drawLineToCursor )
		{
			//then you know to create a new line for this maze
			LineSegment2D line( lastPointClicked, mouseCursor );
			maze.addALine( line );
		}

		//now the user has their pen down
		drawLineToCursor = true;
		lastPointClicked = convertPointToCoordinatesSystem( event->x(), event->y() );
		updateGL();
	}
}

void EditWidget::mouseMoveEvent( QMouseEvent * event )
{
	mouseCursor = convertPointToCoordinatesSystem( event->x(), event->y() );
	if( drawLineToCursor )
	{
		updateGL();
	}
}


/* keyboard input handler....responds to
 * the quit_button (defined in the header) for quiting
 * and allows the user to lift up their drawing pen
 */
void EditWidget::keyPressEvent( QKeyEvent * event )
{
	Qt::Key pressedKey = static_cast< Qt::Key >( event->key() );
	switch( pressedKey )
	{
		case quit_button:
			exit( exit_success );
			break;

		case lift_up_pen_button:
			drawLineToCursor = !drawLineToCursor;
			updateGL();
			break;

		default:
			break;
	}
}

/* build the context menu for the application
 */
void EditWidget::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu contextMenu;
	contextMenu.popup( event->pos() );
	//contextMenu.addAction(  )
}


/* open a maze file
 */
void EditWidget::openMaze()
{
	QString fileTypes = QString( tr( "Maze Files (*.%1)" ) ).arg( mazeFileExtension );
	QString newFileName = QFileDialog::getOpenFileName( this, tr( "Open 2D Maze File" ), QDir::currentPath(), fileTypes );
	if ( !newFileName.isEmpty() ) {
		maze2DfileName = newFileName;
		try
		{
			LoadFile( maze2DfileName.toStdString(), maze );
			updateGL();
		}
		catch ( UserWishesToExitException & ue )
		{
			std::cout << "goodbye";
			exit( exit_success );
		}
	}
}


/* erase all work done on the maze
 * leaving just the bounding walls
 */
void EditWidget::setMazeToDefault()
{
	maze.clear();
	updateGL();
}


/* save the 2D maze out to a file
 */
void EditWidget::saveMaze()
{
	if ( maze2DfileName == default_maze_file_name )
	{
		QString fileTypes = QString( tr( "Maze Files (*.%1)" ) ).arg( mazeFileExtension );
		QFileDialog fileDialog( this, "Save Maze File" );
		fileDialog.setFileMode( QFileDialog::AnyFile );
		fileDialog.setNameFilter( fileTypes );
		fileDialog.setDefaultSuffix( mazeFileExtension );
		if ( !fileDialog.exec() )
		{
			return;
		}

		maze2DfileName = fileDialog.selectedFiles().first();
	}

	try
	{
		WriteFile( maze2DfileName.toStdString(), maze );
	}
	catch ( UserWishesToExitException & ue )
	{
		std::cout << "goodbye";
		exit( exit_success );
	}
}


/* for converting the 2-D maze into t a 3-D maze
 * and writing this 3-D maze out to a file
 */
void EditWidget::convertTo3D()
{
	static const int default_wall_width = 10;
	static const int default_wall_height = 50;

	WidthHeightDialog getWidthAndHeightDialog( default_wall_width, default_wall_height, this );

	if ( !getWidthAndHeightDialog.exec() ) {
		return;
	}

	int selectedWallWidth = getWidthAndHeightDialog.getSelectedWidth();
	int selectedWallHeight = getWidthAndHeightDialog.getSelectedHeight();

	const double default_texture_size = 50.0;

	//iterate through the lines in the 2D maze and create 3D walls out of them
	//and add these walls to the 3D maze;
	int numberOfLines = maze.numberOfLines();
	Wall wall;

	Maze3D toMaze3D;
	for( int i = 0; i < numberOfLines; i++ )
	{
		wall.fitToLine( maze.getALine( i ), selectedWallWidth, selectedWallHeight, default_texture_size, default_texture_size );
		toMaze3D.addAWall( wall );
	}

	//add the floor
	Point3D bottomLeft( -( maze.getWidth() / 2.0 ), -( maze.getHeight() / 2.0 ), -selectedWallHeight / 2.0 );
	Point3D topLeft( -( maze.getWidth() / 2.0 ), ( maze.getHeight() / 2.0 ), -selectedWallHeight / 2.0 );
	Point3D topRight( ( maze.getWidth() / 2.0 ), ( maze.getHeight() / 2.0 ), -selectedWallHeight / 2.0 );
	Point3D bottomRight( ( maze.getWidth() / 2.0 ), -( maze.getHeight() / 2.0 ), -selectedWallHeight / 2.0 );

	Quad floor( bottomLeft, topLeft, topRight, bottomRight );
	TexturedQuad tFloor( floor, default_texture_size, default_texture_size );

	toMaze3D.setFloor( tFloor );

	//try to write out the 3D maze file
	try
	{
		QString threeDFileName = maze2DfileName;
		threeDFileName.chop( threeDFileName.length() - threeDFileName.lastIndexOf( '.' ) );
		WriteFile( threeDFileName.toStdString(), toMaze3D );
	}
	catch ( UserWishesToExitException & ue )
	{
		std::cout << "goodbye!";
		exit( exit_success );
	}
}


/* map a window coordinate point (relative to the top left of the screen)
 * to world coordinates
 */ 
Point2D EditWidget::convertPointToCoordinatesSystem( int x, int y )
{
	class MatrixUtil
	{
		public:
			static void invertGLMatrix( const GLfloat matrix[ 16 ], GLfloat inverse[ 16 ] )
			{
				// assume the bottom right corner of the matrix is 1
				assert( aboutEqual( matrix[ 15 ], 1.0f ) );
				// assume the rest of the last (4th) row is all zeros
				assert( aboutEqual( matrix[ 3 ], 0.0f ) );
				assert( aboutEqual( matrix[ 7 ], 0.0f ) );
				assert( aboutEqual( matrix[ 11 ], 0.0f ) );
				// assume the rest of the last (4th) column is all zeros
				// (assume there's no translation in the matrix)
				assert( aboutEqual( matrix[ 12 ], 0.0f ) );
				assert( aboutEqual( matrix[ 13 ], 0.0f ) );
				assert( aboutEqual( matrix[ 14 ], 0.0f ) );

				// with the above assumptions we can fill in the last row and last column of the inverse
				inverse[ 3 ] = 0.0f;
				inverse[ 7 ] = 0.0f;
				inverse[ 11 ] = 0.0f;
				inverse[ 12 ] = 0.0f;
				inverse[ 13 ] = 0.0f;
				inverse[ 14 ] = 0.0f;
				inverse[ 15 ] = 1.0f;

				// compute the inverse of the remaining 3x3 matrix using cofactors
				GLfloat determinant = ( matrix[ 0 ] * deteminant2x2( matrix[ 5 ], matrix[ 6 ], matrix[ 9 ], matrix[ 10 ] ) )
									- ( matrix[ 1 ] * deteminant2x2( matrix[ 4 ], matrix[ 6 ], matrix[ 8 ], matrix[ 10 ] ) )
									+ ( matrix[ 2 ] * deteminant2x2( matrix[ 4 ], matrix[ 5 ], matrix[ 8 ], matrix[ 9 ] ) );

				inverse[ 0 ] =	deteminant2x2( matrix[ 5 ], matrix[ 6 ], matrix[ 9 ], matrix[ 10 ] ) / determinant;
				inverse[ 1 ] = -deteminant2x2( matrix[ 4 ], matrix[ 6 ], matrix[ 8 ], matrix[ 10 ] ) / determinant;
				inverse[ 2 ] =	deteminant2x2( matrix[ 4 ], matrix[ 5 ], matrix[ 8 ], matrix[ 9 ] ) / determinant;
				inverse[ 4 ] = -deteminant2x2( matrix[ 1 ], matrix[ 2 ], matrix[ 9 ], matrix[ 10 ] ) / determinant;
				inverse[ 5 ] =	deteminant2x2( matrix[ 0 ], matrix[ 2 ], matrix[ 8 ], matrix[ 10 ] ) / determinant;
				inverse[ 6 ] = -deteminant2x2( matrix[ 0 ], matrix[ 1 ], matrix[ 8 ], matrix[ 9 ] ) / determinant;
				inverse[ 8 ] =	deteminant2x2( matrix[ 1 ], matrix[ 2 ], matrix[ 5 ], matrix[ 6 ] ) / determinant;
				inverse[ 9 ] = -deteminant2x2( matrix[ 0 ], matrix[ 2 ], matrix[ 4 ], matrix[ 6 ] ) / determinant;
				inverse[ 10 ] = deteminant2x2( matrix[ 0 ], matrix[ 1 ], matrix[ 4 ], matrix[ 5 ] ) / determinant;
			}

			static void multiplyByMatrix( const GLfloat vector[ 4 ], const GLfloat matrix[ 16 ], GLfloat result[ 4 ] ) {
				for ( int i = 0; i < 4; i++ ) {
					result[ i ] = vector[ 0 ] * matrix[ i ] + vector[ 1 ] * matrix[ 4 + i ] + vector[ 2 ] * matrix[ 8 + i ] + vector[ 3 ] * matrix[ 12 + i ];
				}
			}

		private:
			static GLfloat deteminant2x2( const GLfloat a11, const GLfloat a12, const GLfloat a21, const GLfloat a22 )
			{
				return ( ( a11 * a22 ) - ( a12 * a21 ) );
			}

			static bool aboutEqual( const GLfloat a, const GLfloat b )
			{
				return withinEpsilon( a, b, 0.0001 );
			}

			static bool withinEpsilon( const GLfloat a, const GLfloat b, const GLfloat epsilon )
			{
				return fabs( a - b ) < fabs( epsilon );
			}
	};

	makeCurrent();

	GLint viewport[ 4 ];
	glGetIntegerv( GL_VIEWPORT, viewport );

	// map screen coordinates relative to the top left corner
	// to viewport coordinates
	y = viewport[ 3 ] - y;

	// map viewport coordinates to normalized device coordinates
	GLfloat normalized[ 4 ];
	normalized[ 0 ] = ( ( x - viewport[ 0 ] ) * ( 2.0f / viewport[ 2 ] ) ) - 1;
	normalized[ 1 ] = ( ( y - viewport[ 1 ] ) * ( 2.0f / viewport[ 3 ] ) ) - 1;
	normalized[ 2 ] = 0.0f;	// z value isn't important, so we'll just assume 0
	normalized[ 3 ] = 1.0f;

	// map normalized device coordinates to world coordinates
	GLfloat projectionMatrix[ 16 ];
	glGetFloatv( GL_PROJECTION_MATRIX, projectionMatrix );
	GLfloat inverseProjectionMatrix[ 16 ];
	MatrixUtil::invertGLMatrix( projectionMatrix, inverseProjectionMatrix );
	GLfloat worldspace[ 4 ];
	MatrixUtil::multiplyByMatrix( normalized, inverseProjectionMatrix, worldspace );

	return Point2D( worldspace[ 0 ], worldspace[ 1 ] );
}

/*  WidthHeightDialog::WidthHeightDialog
 */
WidthHeightDialog::WidthHeightDialog( int default_wall_width_, int default_wall_height_, QWidget * parent /*= NULL*/ ) :
	QDialog( parent ),
	default_wall_width( default_wall_width_ ),
	default_wall_height( default_wall_height_ ),
	widthLabel( NULL ),
	widthEdit( NULL ),
	heightLabel( NULL ),
	heightEdit( NULL ),
	okButton( NULL ),
	cancelButton( NULL ),
	gridLayout( NULL ),
	horizontalLayout( NULL ),
	verticalLayout( NULL )
{
	widthLabel = new QLabel( tr( "Wall width" ) );
	widthEdit = new QLineEdit( QString( "%1" ).arg( default_wall_width ) );
	heightLabel = new QLabel( tr( "Wall height" ) );
	heightEdit = new QLineEdit( QString( "%1" ).arg( default_wall_height ) );

	okButton = new QPushButton( tr( "OK" ) );
	cancelButton = new QPushButton( tr( "Cancel" ) );

	gridLayout = new QGridLayout;
	horizontalLayout = new QHBoxLayout;
	verticalLayout = new QVBoxLayout;

	widthEdit->setValidator( new QIntValidator( 1, 2 * default_wall_width, widthEdit ) );
	heightEdit->setValidator( new QIntValidator( 1, 2 * default_wall_height, heightEdit ) );

	gridLayout->addWidget( widthLabel, 0, 0 );
	gridLayout->addWidget( widthEdit, 0, 1 );
	gridLayout->addWidget( heightLabel, 1, 0 );
	gridLayout->addWidget( heightEdit, 1, 1 );

	okButton->setDefault( true );
	okButton->setEnabled( false );

	horizontalLayout->addStretch();
	horizontalLayout->addWidget( okButton, 0, Qt::AlignRight );
	horizontalLayout->addWidget( cancelButton, 0, Qt::AlignRight );

	verticalLayout->addLayout( gridLayout );
	verticalLayout->addStretch();
	verticalLayout->addLayout( horizontalLayout );

	setLayout( verticalLayout );

	connect( widthEdit, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits() ) );
	connect( heightEdit, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits() ) );
	connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

	checkLineEdits();
}

/*  return the wall width
 */
int WidthHeightDialog::getSelectedWidth() {
	if ( widthEdit != NULL ) {
		return widthEdit->displayText().toInt();
	} else {
		return default_wall_width;
	}
}

/*  return the wall height
 */
int WidthHeightDialog::getSelectedHeight() {
	if ( heightEdit != NULL ) {
		return heightEdit->displayText().toInt();
	} else {
		return default_wall_height;
	}
}

/*  enable the 'OK' button, if it should be enabled
 */
void WidthHeightDialog::checkLineEdits()
{
	bool allInputOK = true;
	QList< QLineEdit * > lineEditList = findChildren< QLineEdit * >();
	foreach ( QLineEdit * lineEdit, lineEditList ) {
		allInputOK &= !lineEdit->text().isEmpty();
	}

	okButton->setEnabled( allInputOK );
}

