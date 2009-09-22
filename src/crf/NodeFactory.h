/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include "Channel.h"
#include "Config.h"
#include "Node.h"
#include "Pipe.h"

#include <eq/client/nodeFactory.h>

namespace eqOsg {

	///Our eq node factory to create the eqOsg objects.
	///If you create your own objects, this factory has to be overriden and passed when calling eq::init.
	///@sa eq::NodeFactory
	class NodeFactory : public eq::NodeFactory
	{
	public:
		///creates the eqOsg::Channel object
		///@param parent The channel's parent window.
		///@return The eqOsg::Channel.
		virtual eq::Channel* createChannel( eq::Window* parent )
		{ return new eqOsg::Channel( parent ); }

		///creates the eqOsg::Config object
		///@param parent The config's parent server.
		///@return The eqOsg::Config.
		virtual eq::Config* createConfig( eq::ServerPtr parent )
		{ return new eqOsg::Config( parent ); }
		
		///creates the eqOsg::Node object
		///@param parent The node's parent config.
		///@return The eqOsg::Node.
		virtual eq::Node* createNode( eq::Config* parent )
		{ return new eqOsg::Node( parent ); }
		
		///creates the eqOsg::Pipe object
		///@param parent The pipe's parent node.
		///@return The eqOsg::Pipe.
		virtual eq::Pipe* createPipe( eq::Node* parent )
		{ return new eqOsg::Pipe( parent ); }
	};
}
#endif
