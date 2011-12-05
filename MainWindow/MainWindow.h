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
		void newMaze();
		void openFile();
		void saveFile();
		void saveAsFile();
		void respondToMazeChange( const Maze2D & maze2D );
		void wallWidthChanged( int newWidth );
		void wallHeightChanged( int newHeight );

	signals:
		void maze3DChanged( const Maze3D * maze3D );

	private:
		void setCurrentFileName( const QString & fileName );
		void update3DMaze( const Maze2D & maze2D );

		EditWidget * editWidget;
		Maze3D maze3D;
		int wallWidth;
		int wallHeight;

		QString currentFileName;

	protected:
		static const int min_wall_width;
		static const int max_wall_width;
		static const int min_wall_height;
		static const int max_wall_height;

		static const int default_wall_width;
		static const int default_wall_height;

		static const QString mazeFileExtension;
};

#endif // MAINWINDOW_H
