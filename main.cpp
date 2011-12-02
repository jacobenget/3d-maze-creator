

#include <QtGui/QApplication>
#include "Edit/edit2DMaze.h"
#include "View/view3DMaze.h"

int main( int argc, char * argv[] ) {
	QApplication application( argc, argv );

	// set up a message handler
	QErrorMessage::qtHandler();

	QMainWindow window;
	window.setWindowTitle( "Edit/Create your own Maze" );

	EditWidget * editWidget = new EditWidget;
	QAction * openMazeAction = new QAction( window.tr( "Open Maze..." ), &window );
	QAction * saveAction = new QAction( window.tr( "Save Maze" ), &window );
	QAction * resetMazeAction = new QAction( window.tr( "Clear Maze" ), &window );
	QAction * convertMazeAction = new QAction( window.tr( "Convert Maze To 3D" ), &window );
	QAction * quitAction = new QAction( window.tr( "Quit" ), &window );
	window.connect( openMazeAction, SIGNAL( triggered() ), editWidget, SLOT( openMaze() ) );
	window.connect( saveAction, SIGNAL( triggered() ), editWidget, SLOT( saveMaze() ) );
	window.connect( resetMazeAction, SIGNAL( triggered() ), editWidget, SLOT( setMazeToDefault() ) );
	window.connect( convertMazeAction, SIGNAL( triggered() ), editWidget, SLOT( convertTo3D() ) );
	window.connect( quitAction, SIGNAL( triggered() ), &application, SLOT( quit() ) );
	editWidget->addAction( openMazeAction );
	editWidget->addAction( saveAction );
	editWidget->addAction( resetMazeAction );
	editWidget->addAction( convertMazeAction );
	editWidget->addAction( quitAction );

	ViewWidget * viewWidget = new ViewWidget;
	QAction * open3DMazeAction = new QAction( window.tr( "Open 3D Maze..." ), &window );
	QAction * replaceFloorTextureAction = new QAction( window.tr( "Replace Floor Texture" ), &window );
	QAction * replaceWallTextureAction = new QAction( window.tr( "Replace Wall Texture" ), &window );
	QAction * reinitializeMazeAction = new QAction( window.tr( "Reinitialize" ), &window );
	window.connect( open3DMazeAction, SIGNAL( triggered() ), viewWidget, SLOT( openMaze() ) );
	window.connect( replaceFloorTextureAction, SIGNAL( triggered() ), viewWidget, SLOT( replaceFloorTexture() ) );
	window.connect( replaceWallTextureAction, SIGNAL( triggered() ), viewWidget, SLOT( replaceWallTexture() ) );
	window.connect( reinitializeMazeAction, SIGNAL( triggered() ), viewWidget, SLOT( reinitializeView() ) );
	viewWidget->addAction( open3DMazeAction );
	viewWidget->addAction( replaceFloorTextureAction );
	viewWidget->addAction( replaceWallTextureAction );
	viewWidget->addAction( reinitializeMazeAction );

	QSplitter * splitter = new QSplitter;
	splitter->addWidget( editWidget );
	splitter->addWidget( viewWidget );

	window.setCentralWidget( splitter );
	window.resize( 900, 600 );
	window.show();

	return application.exec();
}

