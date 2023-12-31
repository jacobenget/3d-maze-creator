/*
   Project     : 3DMaze
   File        : explore3DMaze.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : contains the declaration for ExploreWidget,
				 which is used for exploring a 3D maze in first-person view
				 with basic WASD move controls and mouse-look
*/


#ifndef EXPLOREDMAZE_H_
#define EXPLOREDMAZE_H_

#include <QtOpenGL>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctime>

#include "Maze3D.h"
#include "ProjectionState.h"
#include "TransformationStateFP.h"
#include "UserInteractionStateFP.h"
#include "FramesPerSecondController.h"

class ExploreWidget : public QGLWidget
{
	Q_OBJECT

	public:
		ExploreWidget( const Maze3D & maze, const QImage & floorTexture_, const QImage & wallsTexture_, QWidget * parent = NULL );
		virtual ~ExploreWidget();

	signals:
		void stealMyFocus();

	protected:
		virtual void initializeGL();

		// change size handler...
		// lets the user resize  the window
		// but keeps everything in the correct perspective
		virtual void resizeGL( int width, int height );

		// compute the placement of the player based on current movement,
		// and then draw the textured maze
		virtual void paintGL();

		// rotates the world based on user input with the mouse
		virtual void mouseMoveEvent( QMouseEvent * event );

		// keyboard input handler for pressing a key
		// responds to key commands for movement,
		// changing perspective, and quiting
		virtual void keyPressEvent( QKeyEvent * event );

		// keyboard input handler for letting up on a key
		// responds to key commands for movement,
		// and changing perspective
		virtual void keyReleaseEvent( QKeyEvent * event );

		// hide the cursor when focus is received, show the cursor otherwise
		virtual void focusInEvent( QFocusEvent * event );

	private:
		// computes the viewing frustum
		// given the current state of affairs
		void computeFrustum();

		// hide the cursor, even if it's already hidden
		void hideCursor();
		// undo all the times we've hid the cursor
		void stopHidingCursor();

		const Maze3D & maze;

		const QImage & floorTexture;
		const QImage & wallsTexture;

		GLuint floorTextureNumber;
		GLuint wallsTextureNumber;

		ProjectionState stateOfProjection;
		TransformationStateFP stateOfTransformationFP;
		UserInteractionStateFP stateOfUserInteractionFP;

		int timesCursorHidden;

		static const int initial_window_width = 900;
		static const int initial_window_height = 900;
		static const int initial_window_x_position = 300;
		static const int initial_window_y_position = 200;

		static const QColor bkgrnd_color;

		static const double global_x_tilt;

		static const double fovy_angle_ratio_change;
		static const double initial_fovy_angle;
		static const double initial_z_coord_of_camera;

		static const int z_value_of_far_clipping_plane = -1000;
		static const double distance_between_camera_and_near_clipping_plane;
		static const int min_z_coord_of_camera = -200;
		static const int max_z_coord_of_camera = 10000;

		static const double incremental_angle_change;  //in degrees
		static const double incremental_position_change;
		static const double jump_velocity;

		//buffer between player and walls, so the walls don't clip when the user collids with them
		//should NOT be larger than the width of the walls divided by incremental_position_change
		static const double buffer_distance;

		static const int frames_per_second = 60;

		static const Qt::Key quit_button;
		static const Qt::Key release_focus_button;
		static const Qt::Key move_forward_button;
		static const Qt::Key move_backward_button;
		static const Qt::Key strafe_right_button;
		static const Qt::Key strafe_left_button;
		static const Qt::Key jump_button;
		static const Qt::Key zoom_in_button;
		static const Qt::Key zoom_out_button;
};

#endif /*EXPLOREDMAZE_H_*/
