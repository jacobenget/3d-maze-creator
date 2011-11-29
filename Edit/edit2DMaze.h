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

	protected:
		virtual void initializeGL();
		virtual void resizeGL( int width, int height );
		virtual void paintGL();
		virtual void mousePressEvent( QMouseEvent * event );
		virtual void mouseMoveEvent( QMouseEvent * event );
		virtual void keyPressEvent( QKeyEvent * event );
		virtual void contextMenuEvent( QContextMenuEvent * event );

	public slots:
		void openMaze();
		void setMazeToDefault();
		void saveMaze();
		void convertTo3D();

	private:
		Point2D convertPointToCoordinatesSystem( int x, int y );

		Maze2D maze;
		Point2D lastPointClicked;
		Point2D mouseCursor;
		bool drawLineToCursor;
		QString maze2DfileName;
		double lineWidth;

		static const QColor walls_color;
		static const QColor bkgrd_color;
		static const QColor inside_maze_color;
		static const QColor figure_color;

		static const float maxMazeToAllScreenRatio;

		static const QString mazeFileExtension;
		static const QString default_maze_file_name;
};


/* Dialog for asking the user for input in what wall width and height
 * they want to use when exporting a 2D maze to 3D
 */
class WidthHeightDialog : public QDialog
{
	Q_OBJECT

	public:
		WidthHeightDialog( int default_width_, int default_height_, QWidget * parent = NULL );

		int getSelectedWidth();
		int getSelectedHeight();

	public slots:
		void checkLineEdits();

	signals:
		void testSignal();

	private:
		int default_wall_width;
		int default_wall_height;

		QLabel * widthLabel;
		QLineEdit * widthEdit;
		QLabel * heightLabel;
		QLineEdit * heightEdit;
		QPushButton * okButton;
		QPushButton * cancelButton;

		QGridLayout * gridLayout;
		QHBoxLayout * horizontalLayout;
		QVBoxLayout * verticalLayout;
};

const  int exit_success = 0;

const Qt::Key quit_button = Qt::Key_Q;
const Qt::Key lift_up_pen_button = Qt::Key_Space;


#endif /*EDIT2DMAZE_H_*/
