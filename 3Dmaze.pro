#-------------------------------------------------
#
# Project created by QtCreator 2011-11-19T14:04:17
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG   += warn_on

RESOURCES = application.qrc

DEFINES += NOMINMAX

TARGET = 3Dmaze
TEMPLATE = app
INCLUDEPATH += Library/2DStructures/ \
	Library/3DStructures/ \
	Library/IOControl/ \
	Library/UserInteraction/ \
	LIbrary/Util/

SOURCES +=\
    Library/2DStructures/Vector2D.cpp \
    Library/2DStructures/Point2D.cpp \
    Library/2DStructures/Maze2D.cpp \
    Library/2DStructures/LineSegment2D.cpp \
    Library/3DStructures/Wall.cpp \
    Library/3DStructures/TexturedQuad.cpp \
    Library/3DStructures/Quad.cpp \
    Library/3DStructures/Point3D.cpp \
    Library/3DStructures/Maze3D.cpp \
    Library/IOControl/FileHandler.cpp \
    Library/UserInteraction/UserInteractionStateFP.cpp \
    Library/UserInteraction/UserInteractionState.cpp \
    Library/UserInteraction/TransformationStateFP.cpp \
    Library/UserInteraction/TransformationState.cpp \
    Library/UserInteraction/TransformationMatrix.cpp \
    Library/UserInteraction/ProjectionState.cpp \
    Library/Util/FramesPerSecondController.cpp \
	Library/Util/ConversionFunctions.cpp \
    Edit/edit2DMaze.cpp \
	View/view3DMaze.cpp \
    main.cpp \
    Explore/explore3DMaze.cpp \
    MainWindow/MainWindow.cpp

HEADERS  += \
    Library/2DStructures/Vector2D.h \
    Library/2DStructures/Point2D.h \
    Library/2DStructures/Maze2D.h \
    Library/2DStructures/LineSegment2D.h \
    Library/3DStructures/Wall.h \
    Library/3DStructures/TexturedQuad.h \
    Library/3DStructures/Quad.h \
    Library/3DStructures/Point3D.h \
    Library/3DStructures/Maze3D.h \
    Library/IOControl/Serializable.h \
    Library/IOControl/IOError.h \
    Library/IOControl/FileHandler.h \
    Library/UserInteraction/UserInteractionStateFP.h \
    Library/UserInteraction/UserInteractionState.h \
    Library/UserInteraction/TransformationStateFP.h \
    Library/UserInteraction/TransformationState.h \
    Library/UserInteraction/TransformationMatrix.h \
    Library/UserInteraction/ProjectionState.h \
    Library/Util/FramesPerSecondController.h \
    Library/Util/ConversionFunctions.h \
	Library/Util/BoundsCheckingContainer.h \
    Edit/edit2DMaze.h \
	View/view3DMaze.h \
    Explore/explore3DMaze.h \
    MainWindow/MainWindow.h
