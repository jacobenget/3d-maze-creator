CC = g++

#Mac OSX flags
CFLAGS = -Wall -O2 -DHOST_OS_MACOSX
OPENGL_FLAGS = -framework GLUT -framework OpenGL


#GNU/Linux flags
#CFLAGS = -Wall -O2 -DHOST_OS_LINUX
#OPENGL_FLAGS = -I/usr/openwin/include -L/user/openwin/lib -lGL -lglut -lGLU -lm

#defining some shorthand for folder names
LIB = Library

2D = $(LIB)/2DStructures
3D = $(LIB)/3DStructures
IO = $(LIB)/IOControl
UI = $(LIB)/UserInteraction
TL = $(LIB)/Util

2DSOURCE = $(2D)/LineSegment2D.cpp $(2D)/Maze2D.cpp $(2D)/Point2D.cpp $(2D)/Vector2D.cpp
2DHEADER = $(2DSOURCE:.cpp=.h)
2DOBJECT = $(2DSOURCE:.cpp=.o)

3DSOURCE = $(3D)/Wall.cpp $(3D)/Maze3D.cpp $(3D)/Point3D.cpp $(3D)/Quad.cpp $(3D)/TexturedQuad.cpp
3DHEADER = $(3DSOURCE:.cpp=.h)
3DOBJECT = $(3DSOURCE:.cpp=.o)

IOSOURCE = $(IO)/FileHandler.cpp $(IO)/WriteFile.cpp $(IO)/LoadFile.cpp
IOHEADER = $(IOSOURCE:.cpp=.h) $(IO)/IOError.h $(IO)/Serializable.h $(IO)/UserWishesToExitException.h
IOOBJECT = $(IOSOURCE:.cpp=.o)

UISOURCE = $(UI)/ProjectionState.cpp $(UI)/TransformationMatrix.cpp $(UI)/TransformationState.cpp $(UI)/TransformationStateFP.cpp $(UI)/UserInteractionState.cpp $(UI)/UserInteractionStateFP.cpp
UIHEADER = $(UISOURCE:.cpp=.h)
UIOBJECT = $(UISOURCE:.cpp=.o)

TLSOURCE = $(TL)/ConversionFunctions.cpp $(TL)/FramesPerSecondController.cpp $(TL)/PPMTexture.cpp $(TL)/RegisterTexture.cpp
TLHEADER = $(TLSOURCE:.cpp=.h) $(TL)/BoundsCheckingContainer.h
TLOBJECT = $(TLSOURCE:.cpp=.o)

MAINSOURCE = $(EDIT)/edit2DMaze.cpp $(CONV)/convertMazeTo3D.cpp $(VIEW)/view3DMaze.cpp $(EXPL)/explore3DMaze.cpp
MAINHEADER = $(MAINSOURCE:.cpp=.h)
MAINOBJECT = $(MAINSOURCE:.cpp=.o)

EDIT = Edit
CONV = Convert
VIEW = View
EXPL = Explore

INCPATH = -I$(2D) -I$(3D) -I$(IO) -I$(UI) -I$(TL)


all: edit2DMaze convertMazeTo3D view3DMaze explore3DMaze

edit2DMaze: $(EDIT)/edit2DMaze.o $(2DOBJECT) $(IOOBJECT) $(2DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -o edit2DMaze $(EDIT)/edit2DMaze.o $(2DOBJECT) $(IOOBJECT) $(INCPATH) $(OPENGL_FLAGS)

convertMazeTo3D: $(CONV)/convertMazeTo3D.o $(3DOBJECT) $(2DOBJECT) $(IOOBJECT) $(3DHEADER) $(2DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -o convertMazeTo3D $(CONV)/convertMazeTo3D.o $(3DOBJECT) $(2DOBJECT) $(IOOBJECT) $(INCPATH) $(OPENGL_FLAGS)

view3DMaze: $(VIEW)/view3DMaze.o $(3DOBJECT) $(2DOBJECT) $(IOOBJECT) $(UIOBJECT) $(TLOBJECT) $(3DHEADER) $(2DHEADER) $(IOHEADER) $(UIHEADER) $(TLHEADER)
	$(CC) $(CFLAGS) -o view3DMaze $(VIEW)/view3DMaze.o $(3DOBJECT) $(2DOBJECT) $(IOOBJECT) $(UIOBJECT) $(TLOBJECT) $(INCPATH) $(OPENGL_FLAGS)

explore3DMaze: $(EXPL)/explore3DMaze.o $(3DOBJECT) $(2DOBJECT) $(IOOBJECT) $(UIOBJECT) $(TLOBJECT) $(3DHEADER) $(2DHEADER) $(IOHEADER) $(UIHEADER) $(TLHEADER)
	$(CC) $(CFLAGS) -o explore3DMaze $(EXPL)/explore3DMaze.o $(3DOBJECT) $(2DOBJECT) $(IOOBJECT) $(UIOBJECT) $(TLOBJECT) $(INCPATH) $(OPENGL_FLAGS)
	
$(EDIT)/edit2DMaze.o: $(EDIT)/edit2DMaze.cpp $(EDIT)/edit2DMaze.h $(2DHEADER) $(IOHEADER)
	$(CC) $(CFLAGS) -c -o $(EDIT)/edit2DMaze.o $(EDIT)/edit2DMaze.cpp $(INCPATH)
	
$(CONV)/convertMazeTo3D.o: $(CONV)/convertMazeTo3D.cpp $(CONV)/convertMazeTo3D.h $(3DHEADER) $(2DHEADER) $(IOHEADER)
	$(CC) $(CFLAGS) -c -o $(CONV)/convertMazeTo3D.o $(CONV)/convertMazeTo3D.cpp $(INCPATH)
	
$(VIEW)/view3DMaze.o: $(VIEW)/view3DMaze.cpp $(VIEW)/view3DMaze.h $(3DHEADER) $(2DHEADER) $(IOHEADER) $(UIHEADER) $(TLHEADER)
	$(CC) $(CFLAGS) -c -o $(VIEW)/view3DMaze.o $(VIEW)/view3DMaze.cpp $(INCPATH)
	
$(EXPL)/explore3DMaze.o: $(EXPL)/explore3DMaze.cpp $(EXPL)/explore3DMaze.h $(3DHEADER) $(2DHEADER) $(IOHEADER) $(UIHEADER) $(TLHEADER)
	$(CC) $(CFLAGS) -c -o $(EXPL)/explore3DMaze.o $(EXPL)/explore3DMaze.cpp $(INCPATH)

$(UI)/TransformationStateFP.o: $(UI)/TransformationStateFP.cpp $(UIHEADER) $(3DHEADER) $(2DHEADER)
	$(CC) $(CFLAGS) -c -o $(UI)/TransformationStateFP.o $(UI)/TransformationStateFP.cpp $(INCPATH)

$(UI)/UserInteractionStateFP.o: $(UI)/UserInteractionStateFP.cpp $(UIHEADER) $(2DHEADER)
	$(CC) $(CFLAGS) -c -o $(UI)/UserInteractionStateFP.o $(UI)/UserInteractionStateFP.cpp $(INCPATH)

$(UI)/TransformationState.o: $(UI)/TransformationState.cpp $(UIHEADER) $(TLHEADER)
	$(CC) $(CFLAGS) -c -o $(UI)/TransformationState.o $(UI)/TransformationState.cpp $(INCPATH)

$(UI)/UserInteractionState.o: $(UI)/UserInteractionState.cpp $(UIHEADER) $(2DHEADER)
	$(CC) $(CFLAGS) -c -o $(UI)/UserInteractionState.o $(UI)/UserInteractionState.cpp $(INCPATH)

$(UI)/ProjectionState.o: $(UI)/ProjectionState.cpp $(UIHEADER) $(TLHEADER)
	$(CC) $(CFLAGS) -c -o $(UI)/ProjectionState.o $(UI)/ProjectionState.cpp $(INCPATH)

$(UI)/TransformationMatrix.o: $(UI)/TransformationMatrix.cpp $(3DHEADER)
	$(CC) $(CFLAGS) -c -o $(UI)/TransformationMatrix.o $(UI)/TransformationMatrix.cpp $(INCPATH)

$(3D)/Maze3D.o: $(3D)/Maze3D.cpp $(3DHEADER) $(2DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(3D)/Maze3D.o $(3D)/Maze3D.cpp $(INCPATH)

$(3D)/Wall.o: $(3D)/Wall.cpp $(3DHEADER) $(2DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(3D)/Wall.o $(3D)/Wall.cpp $(INCPATH)

$(3D)/TexturedQuad.o: $(3DHEADER) $(2DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(3D)/TexturedQuad.o $(3D)/TexturedQuad.cpp $(INCPATH)

$(3D)/Quad.o: $(3D)/Quad.cpp $(3DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(3D)/Quad.o $(3D)/Quad.cpp $(INCPATH)

$(3D)/Point3D.o: $(3D)/Point3D.cpp $(3DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(3D)/Point3D.o $(3D)/Point3D.cpp $(INCPATH)

$(2D)/Vector2D.o: $(2D)/Vector2D.cpp $(2DHEADER)
	$(CC) $(CFLAGS) -c -o $(2D)/Vector2D.o $(2D)/Vector2D.cpp $(INCPATH)

$(2D)/Maze2D.o: $(2D)/Maze2D.cpp $(2DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(2D)/Maze2D.o $(2D)/Maze2D.cpp $(INCPATH)

$(2D)/LineSegment2D.o: $(2D)/LineSegment2D.cpp $(2DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(2D)/LineSegment2D.o $(2D)/LineSegment2D.cpp $(INCPATH)

$(2D)/Point2D.o: $(2D)/Point2D.cpp $(2DHEADER) $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(2D)/Point2D.o $(2D)/Point2D.cpp $(INCPATH)

$(TL)/RegisterTexture.o: $(TL)/RegisterTexture.cpp $(TL)/RegisterTexture.h
	$(CC) $(CFLAGS) -c -o $(TL)/RegisterTexture.o $(TL)/RegisterTexture.cpp $(INCPATH)

$(TL)/FramesPerSecondController.o: $(TL)/FramesPerSecondController.cpp $(TL)/FramesPerSecondController.h
	$(CC) $(CFLAGS) -c -o $(TL)/FramesPerSecondController.o $(TL)/FramesPerSecondController.cpp $(INCPATH)

$(TL)/PPMTexture.o: $(TL)/PPMTexture.cpp $(TL)/PPMTexture.h
	$(CC) $(CFLAGS) -c -o $(TL)/PPMTexture.o $(TL)/PPMTexture.cpp $(INCPATH)

$(TL)/ConversionFunctions.o: $(TL)/ConversionFunctions.cpp $(TL)/ConversionFunctions.h
	$(CC) $(CFLAGS) -c -o $(TL)/ConversionFunctions.o $(TL)/ConversionFunctions.cpp $(INCPATH)

$(IO)/FileHandler.o: $(IO)/FileHandler.cpp $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(IO)/FileHandler.o $(IO)/FileHandler.cpp $(INCPATH)

$(IO)/WriteFile.o: $(IO)/WriteFile.cpp $(IO)/WriteFile.h $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(IO)/WriteFile.o $(IO)/WriteFile.cpp $(INCPATH)

$(IO)/LoadFile.o: $(IO)/LoadFile.cpp $(IO)/LoadFile.h $(IOHEADER) 
	$(CC) $(CFLAGS) -c -o $(IO)/LoadFile.o $(IO)/LoadFile.cpp $(INCPATH)



clean:
	rm -rf $(2DOBJECT) $(3DOBJECT) $(IOOBJECT) $(UIOBJECT) $(TLOBJECT) $(MAINOBJECT)
	rm -f edit2DMaze convertMazeTo3D view3DMaze explore3DMaze