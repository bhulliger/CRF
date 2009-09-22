/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef CRFSTARTER_H
#define CRFSTARTER_H

#ifdef WIN32
#define EQ_IGNORE_GLEW
#endif

#ifndef WIN32
#include <eq/eq.h> // to prevent "gl.h included before glew.h"
#endif

#include "crfNodeFactory.h"
#include <osg/Node>

namespace crf {
	/// This class provides easly handable run() methods to start an equalizer application with OSG scene data.
	/// Actually these modes are supported:
	///			<ul><li>Pass an osg::node as 3rd argument. This node will be the scene graph's root node
	///			<li>Override crfPipe and other crf classes to create your more specific scene. Create a 
	///				crf::crfNodeFactory which generates the overriden classes and pass it with crfStarter::setNodeFactory() to 
	///				this starter class.
	///			<li>Do nothing: The "HelloWorld" scene will be rendered.</ul>
	///
	class crfStarter {
	
	public:
		///Default constructor. Sets the viewer- and nodefactorypointer to zero.
		crfStarter(){
			_nodeFactory =0;
		}

		///Initialize with arguments.
		///@param argc CmdLine Argument Counter.
		///@param argv CmdLine Arguments.
		///@return The cpp default main return value.
		virtual int run(int argc, char** argv);

		///Initialises with arguments and the osg-node which should be displayed with equalizer.
		///@param argc CmdLine Argument Counter
		///@param argv CmdLine Arguments
		///@param node OSG Node
		///@return The cpp default main return value.
		virtual int run(int argc, char** argv, osg::ref_ptr<osg::Node> node);
	
		///Sets the custom node factory to provide the overriden crf classes.
		///@param fac The custom node factory.
		void setNodeFactory(crfNodeFactory* fac){_nodeFactory = fac;}

		/// returns a string minus the passed prefix, if the prefix could be found
		/// @param argc argument counter
		/// @param argv command line arguments
		/// @param prefix the specified prefix
		/// @returns the to found string withou prefix
		std::string parseCommandLineForString(int argc, char** argv, std::string prefix);

		///Gets the custom node factory.
		///@return The starter's viewer factory.
		crf::crfNodeFactory* getNodeFactory(){return _nodeFactory;}

	private:
		/// member which holds the factory to create the desired eq-objects
		crf::crfNodeFactory* _nodeFactory;
	};
}
#endif

