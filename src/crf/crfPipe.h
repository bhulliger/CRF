/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#ifndef CRFPIPE_H
#define CRFPIPE_H

#ifdef WIN32
#define EQ_IGNORE_GLEW
#endif

#ifndef WIN32
#include <eq/eq.h> // to prevent "gl.h included before glew.h"
#endif

#include "Pipe.h"
namespace crf {
	
	/// The crf pipe inherits from the basic eqOsg pipe, to add more features like event-adapting, scenegraph updates etc. Override this class' functions to create your own dynmaic and event depended scene graph.
	/// If you do so, don't forget to create your own crfNodeFactory and pass it to crfStarter, to force the CRF to use your objects.
	class crfPipe : public eqOsg::Pipe {
		public:
			///Creates a pipe with the empty viewer. Sets _sceneGraphCreated to false!
			///@param parent The pipe's Parent (a node).
			///@sa eqOsg::Pipe
			crfPipe( eq::Node *parent ) : eqOsg::Pipe(parent){_sceneGraphCreated=false;};
			///Creates a pipe with a given viewer.
			///@sa eqOsg::Pipe
			///@param parent The pipe's parent.
			///@param viewer The Pointer to a complete independent eqOsg::EqViewer.
			crfPipe( eq::Node* parent, osg::ref_ptr<eqOsg::EqViewer> viewer );
			///Creates a pipe with a given osg scene node.
			///@sa eqOsg::Pipe
			///@param parent The pipe's parent.
			///@param sceneNode The scene node to display. This osg node is gonna be insereted as sceneData to the EqViewer.
			crfPipe( eq::Node* parent, osg::ref_ptr<osg::Node> sceneNode );
		protected:
			/// Starts the frame and calls converEqEventsToOsg().
			///@sa eqOsg::Pipe::framestart
			virtual void frameStart( const uint32_t frameID, const uint32_t frameNumber);
			/// Called when pipe gets initalised. CreateSceneGraph() is called here if _sceneGraphCreated is still set to false.
			/// @return True if everything worked fine.
			/// @sa eqOsg::configInit
			virtual bool configInit(const uint32_t initID );
			///Take the eq-events out of the _eventQueue in FrameData and pass it to the eqViewer.
			///This function can be OS depended, because eq does not report the same ascii codes for every windowing system!
			///Actually all basic keys and some special keys are forewarded to the osg viewer. In Windows, the pushed ascii codes
			///represent upper case letters.
			virtual void convertEqEventsToOsg();
			///Override this function to create the scene graph. Pass the root node of the scene graph to the 
			///_viewer member, add OSG eventhandlers if desired etc...
			virtual void createSceneGraph();
			///Updates your scenegraph at the end of every frame. Override this function to create your own
			///frame/time related animations. Basic Implementation: empty!
			virtual void updateSceneGraph(){};
			///This functions sets up the viewer. Currently an OSG statshandler is added and listen to the F2 keystroke.
			///Override this function to specify your viewer.
			virtual void setUpViewer();
			///Convert the key press events.
			///@param event The eq event to convert
			virtual void convertKeyPressEvents(eq::Event event);
			///Convert the key release events.
			///@param event The eq event to convert
			virtual void convertKeyReleaseEvents(eq::Event event);
			///Converts the key press events.
			///@param event The eq event to convert
			virtual void convertMouseEvents(eq::Event event);
			///Unref the viewer when closing.
			///@return True if everything worked fine.
			///@sa eqOsg::configExit
			virtual bool configExit();
	};
}
#endif
