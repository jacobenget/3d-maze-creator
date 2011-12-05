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
		bool saveFile();
		bool saveAsFile();
		void respondToMazeChange( const Maze2D & maze2D );
		void wallWidthChanged( int newWidth );
		void wallHeightChanged( int newHeight );
		void replaceWallTexture();
		void replaceFloorTexture();
		void exploreMazeInFirstPerson();

	signals:
		void maze3DChanged( const Maze3D * maze3D, const QImage & floorTexture, const QImage & wallTexture );

	protected:
		virtual void closeEvent( QCloseEvent * event );

	private:
		void setCurrentFileName( const QString & fileName );
		void update3DMaze( const Maze2D & maze2D );
		bool okToLoseChangesThatExist();

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
