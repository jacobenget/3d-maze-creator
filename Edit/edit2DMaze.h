/*
   Project     : 3DMaze
   File        : edit2DMaze.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : contains the declaration for EditWidget, which is used for editing a 2D maze
*/


#ifndef EDIT2DMAZE_H_
#define EDIT2DMAZE_H_

#include <QtOpenGL>

#include <iostream>

#include "Point2D.h"
#include "LineSegment2D.h"
#include "Maze2D.h"
#include "FileHandler.h"

class EditWidget : public QGLWidget
{
	Q_OBJECT

	public:
		EditWidget( QWidget * parent = NULL );
		const Maze2D & getMaze() { return maze; }

	protected:
		virtual void initializeGL();

		// change size handler...
		// recomputes the orthographic projection so the maze stays square but is as large in the window as possible
		virtual void resizeGL( int width, int height );

		// color in the background, draw and color the 2-D maze,
		// and draw a small "you will be here" triangle
		virtual void paintGL();

		// consecutive mouse presses allow the user to add walls to the maze
		virtual void mousePressEvent( QMouseEvent * event );

		// update the cached position of the last place where moust was
		// and if the redraw the window if the user is creating a wall
		virtual void mouseMoveEvent( QMouseEvent * event );

		// allows the user to lift up their drawing pen
		virtual void keyPressEvent( QKeyEvent * event );

	public slots:
		// open a maze file
		// return true if the open was succeessful
		bool openMaze( const QString & fileName );

		// save the 2D maze out to a file
		// return true if the save was succeessful
		bool saveMaze( const QString & fileName );

		// erase all walls in the maze except the bounding walls
		void setMazeToDefault();

	signals:
		// emitted whenever the user makes an edit to the maze (e.g. adding a wall or removing all walls)
		void mazeEdited( const Maze2D & maze );

	private:
		// map a window coordinate point (relative to the top left of the screen)
		// to world coordinates
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
