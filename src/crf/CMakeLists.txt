CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(CRF)

### Set the module path to find FindEqualizer.cmake and FindOSG.cmake
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

### Look for OpenGL
FIND_PACKAGE(OpenGL REQUIRED)
IF(OPENGL_FOUND)
  MESSAGE(STATUS "Found OpenGL: Includes at ${OPENGL_INCLUDE_DIR}")
  MESSAGE(STATUS "Found OpenGL: Library at ${OPENGL_gl_LIBRARY}")
ELSE(OPENGL_FOUND)
  MESSAGE(FATAL_ERROR "OpenGL was NOT found!")
ENDIF(OPENGL_FOUND)

### Look for Equalizer
FIND_PACKAGE(Equalizer REQUIRED)
IF(Equalizer_FOUND)
  MESSAGE(STATUS "Found Equalizer: Includes at ${Equalizer_INCLUDE_DIR}")
  MESSAGE(STATUS "Found Equalizer: Libraries at ${Equalizer_LIBRARIES}")
ELSE(Equalizer_FOUND)
  MESSAGE(FATAL_ERROR "Equalizer was NOT found!")
ENDIF(Equalizer_FOUND)

### Use OSG debug libraries
#SET( USE_DEBUG_LIBS ON )

SET( FIND_OSG OSG )
IF( USE_DEBUG_LIBS )
	SET( FIND_OSG OSG_DEBUG )
ENDIF( USE_DEBUG_LIBS )

### Look for OpenSceneGraph
#   Taking OSG_DEBUG libs if USE_OSG_DEBUG_LIBS is set
FIND_PACKAGE( ${FIND_OSG} REQUIRED )
IF( OSG_FOUND )
	MESSAGE( STATUS "Found OSG: Includes at ${OSG_INCLUDE_DIR}" )
	MESSAGE( STATUS "Found OSG: Libraries at ${OSG_LIBRARIES}" )
ELSE( OSG_FOUND )
	MESSAGE( FATAL_ERROR "OSG was NOT found!" )
ENDIF( OSG_FOUND ) 

### Add OpenGL, Equalizer and OSG to the include dirctories, so that an #include
#   looks into the correct directory.
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR} ${Equalizer_INCLUDE_DIR} ${OSG_INCLUDE_DIR})

### Reduce amount of warning under MS VC++
IF(WIN32)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1 /EHsc") 
ENDIF(WIN32)

### We default to the debug build type for now
SET(CMAKE_BUILD_TYPE Debug)

### For MS VC++: Add header files to the project tree
FILE(GLOB headers src/*.h)

### Build dynamically linked libraries by default
IF( UNIX )
	SET(BUILD_SHARED_LIBS ON)
ENDIF( UNIX )

### Create CRF library
ADD_LIBRARY( crf
  Application.cpp
  Channel.cpp
  Config.cpp
  EqViewer.cpp
  FrameData.cpp
  InitData.cpp
  Node.cpp
  Pipe.cpp
  SceneReader.cpp
  crfConfig.cpp
  crfPipe.cpp
  crfStarter.cpp
)

# Link all needed libraries to the executable
TARGET_LINK_LIBRARIES( crf
  ${Equalizer_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${OSG_LIBRARIES}
)

### Install equalizer header files
INSTALL( FILES 	
	Application.h 	
	Channel.h 	
	Config.h 	
	EqViewer.h 	
	FrameData.h 	
	InitData.h 	
	NodeFactory.h 	
	Node.h 	
	Pipe.h 	
	Util.h	
	SceneReader.h
	
	DESTINATION include/crf
)


### Install crf header files
INSTALL( FILES 		crfConfig.h 		
					crfNodeFactory.h  		
					crfPipe.h 		
					crfStarter.h 	
DESTINATION include/crf )

### Install libraries
#   .dll files are considered RUNTIME, therefore we have to define it.
#   unused in unix based systems.
INSTALL( TARGETS crf 
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin 
) 
