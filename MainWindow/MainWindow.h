/*
   Project     : 3DMaze
   File        : MainWindow.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : contains the declaration for MainWindow,
				 which is a main window that contains widgets for editing, viewing, and exploring a 3dmaze
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Maze2D.h"
#include "Maze3D.h"
#include "../Edit/edit2DMaze.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow();

	public slots:
		// create a new maze that's empty and untitled
		void newMaze();

		// open a file conaining a 2D maze definition
		void openFile();

		// returns true only if the file was actually saved
		bool saveFile();

		// returns true only if the file was actually saved
		bool saveAsFile();

		// update the 3D maze when the 2D maze is edited
		void respondToMazeChange( const Maze2D & maze2D );

		// respond to a change in the wall width
		void wallWidthChanged( int newWidth );

		// respond to a chanad in the wall height
		void wallHeightChanged( int newHeight );

		// let the user replace the texture that's being used for the walls
		void replaceFloorTexture();

		// let the user replace the texture that's being used for the floor
		void replaceWallTexture();

		// open up a dialog that lets the user explore the maze in first person
		void exploreMazeInFirstPerson();

	signals:
		// emitted wheneve the 3D maze changes
		void maze3DChanged( const Maze3D * maze3D, const QImage & floorTexture, const QImage & wallTexture );

	protected:
		virtual void closeEvent( QCloseEvent * event );

	private:
		// store the currently open file's name and
		// update the application's title bar to match
		void setCurrentFileName( const QString & fileName );

		// update the 3D maze based on the 2D maze and other maze settings
		void update3DMaze( const Maze2D & maze2D );

		// returns true if either there are not modifications to the current maze
		// or the user doesn't mind losing the modifications that exist
		bool okToLoseChangesThatExist();

		// allows the user to select an image file to open, permitting any file formats that QImageReader supports
		static QString getOpenImageFileName( QWidget * parent = NULL );

		EditWidget * editWidget;
		Maze3D maze3D;

		int wallWidth;
		int wallHeight;

		QImage floorTexture;
		QImage wallsTexture;

		QString currentFileName;

	protected:
		static const int min_wall_width;
		static const int max_wall_width;
		static const int min_wall_height;
		static const int max_wall_height;

		static const int default_wall_width;
		static const int default_wall_height;

		static const QString mazeFileExtension;
		static const QString default_floor_texture_file_name;
		static const QString default_walls_texture_file_name;
};

#endif // MAINWINDOW_H
