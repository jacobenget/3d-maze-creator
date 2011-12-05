/*
   Project     : 3DMaze
   File        : edit2DMaze.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for reading in, editing, and
   				 writing back out a file for a 2D maze
   				 
   				 
   				 command line syntax:
   				 
   				 edit2DMaze [ 2DMazeFileName ]
*/


#ifndef EDIT2DMAZE_H_
#define EDIT2DMAZE_H_

#include <QtOpenGL>

#include <iostream>

#include "Point2D.h"
#include "LineSegment2D.h"
#include "Maze2D.h"
#include "FileHandler.h" 
#include "LoadFile.h"  
#include "WriteFile.h"

class EditWidget : public QGLWidget
{
	Q_OBJECT

	public:
		EditWidget( QWidget * parent = NULL );
		const Maze2D & getMaze() { return maze; }

	protected:
		virtual void initializeGL();
		virtual void resizeGL( int width, int height );
		virtual void paintGL();
		virtual void mousePressEvent( QMouseEvent * event );
		virtual void mouseMoveEvent( QMouseEvent * event );
		virtual void keyPressEvent( QKeyEvent * event );

	public slots:
		void openMaze( const QString & fileName );
		void saveMaze( const QString & fileName );
		void setMazeToDefault();

	signals:
		void mazeEdited( const Maze2D & maze );

	private:
		Point2D convertPointToCoordinatesSystem( int x, int y );

		Maze2D maze;
		Point2D lastPointClicked;
		Point2D mouseCursor;
		bool drawLineToCursor;
		double lineWidth;

		static const QColor walls_color;
		static const QColor bkgrd_color;
		static const QColor inside_maze_color;
		static const QColor figure_color;

		static const float maxMazeToAllScreenRatio;
};

#endif /*EDIT2DMAZE_H_*/
