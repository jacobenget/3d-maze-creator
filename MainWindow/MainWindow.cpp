
#include <algorithm>

#include "MainWindow.h"
#include "../Edit/edit2DMaze.h"
#include "../View/view3DMaze.h"

const int MainWindow::min_wall_width = 8;	// walls any smaller than this and the collision detection code will have to be revisited
const int MainWindow::max_wall_width = 20;
const int MainWindow::min_wall_height = 20;
const int MainWindow::max_wall_height = 100;

const int MainWindow::default_wall_width = qBound( min_wall_width, max_wall_width, 10 );
const int MainWindow::default_wall_height = qBound( min_wall_height, max_wall_height, 50 );


/* construct a mainwindow with the edit and view widgets along with a few controls
 */
MainWindow::MainWindow() :
	editWidget( NULL ),
	wallWidth( default_wall_width ),
	wallHeight( default_wall_height )
{
	setWindowTitle( "Edit/Create your own Maze" );

	// create an editWidget along with a few actions that wil be available in the editWidget's context menu
	editWidget = new EditWidget;
	QAction * openMazeAction = new QAction( tr( "Open Maze..." ), this );
	QAction * saveAction = new QAction( tr( "Save Maze" ), this );
	QAction * resetMazeAction = new QAction( tr( "Clear Maze" ), this );
	connect( openMazeAction, SIGNAL( triggered() ), editWidget, SLOT( openMaze() ) );
	connect( saveAction, SIGNAL( triggered() ), editWidget, SLOT( saveMaze() ) );
	connect( resetMazeAction, SIGNAL( triggered() ), editWidget, SLOT( setMazeToDefault() ) );
	editWidget->addAction( openMazeAction );
	editWidget->addAction( saveAction );
	editWidget->addAction( resetMazeAction );

	// create an viewWidget along with a few actions that wil be available in the viewWidget's context menu
	ViewWidget * viewWidget = new ViewWidget;
	QAction * replaceFloorTextureAction = new QAction( tr( "Replace Floor Texture" ), this );
	QAction * replaceWallTextureAction = new QAction( tr( "Replace Wall Texture" ), this );
	QAction * reinitializeMazeAction = new QAction( tr( "Reinitialize" ), this );
	QAction * exploreMazeAction = new QAction( tr( "Explore..." ), this );
	connect( replaceFloorTextureAction, SIGNAL( triggered() ), viewWidget, SLOT( replaceFloorTexture() ) );
	connect( replaceWallTextureAction, SIGNAL( triggered() ), viewWidget, SLOT( replaceWallTexture() ) );
	connect( reinitializeMazeAction, SIGNAL( triggered() ), viewWidget, SLOT( reinitializeView() ) );
	connect( exploreMazeAction, SIGNAL( triggered() ), viewWidget, SLOT( exploreMaze() ) );
	viewWidget->addAction( replaceFloorTextureAction );
	viewWidget->addAction( replaceWallTextureAction );
	viewWidget->addAction( reinitializeMazeAction );
	viewWidget->addAction( exploreMazeAction );

	// make sure that this main window knows when the maze is edited in the editWidget, and tells the viewWidget about this when it happens
	connect( editWidget, SIGNAL( mazeEdited( const Maze2D & ) ), this, SLOT( respondToMazeChange( const Maze2D & ) ) );
	connect( this, SIGNAL( maze3DChanged( const Maze3D * ) ), viewWidget, SLOT( displayMaze3D( const Maze3D * ) ) );

	// respond to the initial maze having been created in the editWidget
	respondToMazeChange( editWidget->getMaze() );

	QSplitter * splitter = new QSplitter;
	splitter->addWidget( editWidget );
	splitter->addWidget( viewWidget );

	// add a few sliders to control the wall width and height to the top of the main window
	QGridLayout * wallControls = new QGridLayout;
	wallControls->addWidget( new QLabel( tr( "Wall width:" ) ), 0, 0 );
	wallControls->addWidget( new QLabel( tr( "Wall height:" ) ), 1, 0 );
	{
		QSlider * wallsWidthSlider = new QSlider( Qt::Horizontal );
		wallsWidthSlider->setRange( min_wall_width, max_wall_width );
		wallsWidthSlider->setSliderPosition( wallWidth );
		wallControls->addWidget( wallsWidthSlider, 0, 1 );
		connect( wallsWidthSlider, SIGNAL( valueChanged( int ) ), this, SLOT( wallWidthChanged( int ) ) );
	}
	{
		QSlider * wallsHeightSlider = new QSlider( Qt::Horizontal );
		wallsHeightSlider->setRange( min_wall_height, max_wall_height );
		wallsHeightSlider->setSliderPosition( wallHeight );
		wallControls->addWidget( wallsHeightSlider, 1, 1 );
		connect( wallsHeightSlider, SIGNAL( valueChanged( int ) ), this, SLOT( wallHeightChanged( int ) ) );
	}

	QVBoxLayout * mainVerticalLayout = new QVBoxLayout;
	mainVerticalLayout->addLayout( wallControls );
	mainVerticalLayout->addWidget( splitter );

	setCentralWidget( new QWidget );
	centralWidget()->setLayout( mainVerticalLayout );
}


/* update the 3D maze when the 2D maze is edited
 */
void MainWindow::respondToMazeChange( const Maze2D & maze2D )
{
	update3DMaze( maze2D );
}

/* respond to a wall width change
 */
void MainWindow::wallWidthChanged( int newWidth )
{
	wallWidth = newWidth;
	update3DMaze( editWidget->getMaze() );
}

/* respond to a wall height change
 */
void MainWindow::wallHeightChanged( int newHeight )
{
	wallHeight = newHeight;
	update3DMaze( editWidget->getMaze() );
}

/* update the 3D maze based on the 2D maze and other maze settings
 */
void MainWindow::update3DMaze( const Maze2D & maze2D )
{
	const double default_texture_size = 50.0;

	maze3D.clearWalls();

	//iterate through the lines in the 2D maze and create 3D walls out of them
	//and add these walls to the 3D maze;
	Wall wall;
	for( int i = 0; i < maze2D.numberOfLines(); i++ )
	{
		wall.fitToLine( maze2D.getALine( i ), wallWidth, wallHeight, default_texture_size, default_texture_size );
		maze3D.addAWall( wall );
	}

	//add the floor
	Point3D bottomLeft( -( maze2D.getWidth() / 2.0 ), -( maze2D.getHeight() / 2.0 ), -wallHeight / 2.0 );
	Point3D topLeft( -( maze2D.getWidth() / 2.0 ), ( maze2D.getHeight() / 2.0 ), -wallHeight / 2.0 );
	Point3D topRight( ( maze2D.getWidth() / 2.0 ), ( maze2D.getHeight() / 2.0 ), -wallHeight / 2.0 );
	Point3D bottomRight( ( maze2D.getWidth() / 2.0 ), -( maze2D.getHeight() / 2.0 ), -wallHeight / 2.0 );

	Quad floor( bottomLeft, topLeft, topRight, bottomRight );
	TexturedQuad tFloor( floor, default_texture_size, default_texture_size );

	maze3D.setFloor( tFloor );

	emit maze3DChanged( &maze3D );
}
