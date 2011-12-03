/*
   Project     : 3DMaze
   File        : view3DMaze.h
   Author      : Jacob Enget  (jacob.enget@gmail.com)

   Description : Main function for viewing a 3D-maze
   				 after applying textures to its walls and floors
   				 
   				 
   				 command line syntax:
   				 
   				 view3DMaze [ 3DMazeFileName [ floorTexture.ppm [ wallTexture.ppm ] ] ]
*/


#ifndef VIEW3DMAZE_H_
#define VIEW3DMAZE_H_

#include <QtOpenGL>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Maze3D.h"
#include "PPMTexture.h"
#include "ProjectionState.h"
#include "UserInteractionState.h"
#include "TransformationState.h"
#include "LoadFile.h"
#include "RegisterTexture.h"
#include "UserWishesToExitException.h"

class ViewWidget : public QGLWidget
{
	Q_OBJECT

	public:
		ViewWidget( QWidget * parent = NULL );

	protected:
		virtual void initializeGL();
		virtual void resizeGL( int width, int height );
		virtual void paintGL();
		virtual void mousePressEvent( QMouseEvent * event );
		virtual void mouseReleaseEvent( QMouseEvent * event );
		virtual void mouseMoveEvent( QMouseEvent * event );
		virtual void keyPressEvent( QKeyEvent * event );

	public slots:
		void openMaze();
		void replaceFloorTexture();
		void replaceWallTexture();
		void reinitializeView();
		void exploreMaze();

	private:
		void computeFrustum();

		PPMTexture floorTexture;
		PPMTexture wallsTexture;

		GLuint floorTextureNumber;
		GLuint wallsTextureNumber;

		Maze3D maze;
		ProjectionState stateOfProjection;
		TransformationState stateOfTransformation;
		UserInteractionState stateOfUserInteraction;

		static const QColor bkgrnd_color;

		static const double max_x_translation;
		static const double max_y_translation;

		static const double max_scale;
		static const double min_scale;

		static const double rotation_increment;
		static const double translation_increment;
		static const double scale_multiplier;

		static const double fovy_angle_ratio_change;
		static const double initial_fovy_angle;
		static const double initial_z_coord_of_camera;

		static const int z_value_of_far_clipping_plane = -1000;
		static const int distance_between_camera_and_near_clipping_plane = 1;
		static const int min_z_coord_of_camera = 200;
		static const int max_z_coord_of_camera = 10000;

		static const QString default_floor_texture_file_name;
		static const QString default_walls_texture_file_name;
};


#endif /*VIEW3DMAZE_H_*/
