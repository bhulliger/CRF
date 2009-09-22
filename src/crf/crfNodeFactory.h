/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef CRFNODEFACTORY_H
#define CRFNODEFACTORY_H

#include "NodeFactory.h"
#include "crfPipe.h"
#include "crfConfig.h"

namespace crf {

	/// This class generates the crf Equalizer objects.
	/// @sa eqOsg::NodeFactory
	class crfNodeFactory : public eqOsg::NodeFactory {

	public:
		/// Sets the sceneNode pointer to zero.
		crfNodeFactory(){
			_sceneNode =0;
		}

		/// Creates the crfPipe objects.
		/// If a osg::Node is set, the node will be passed to the new pipe.
		/// @sa eqOsg::NodeFactory::createPipe
		virtual eq::Pipe* createPipe( eq::Node* parent )
		{ 
			if (_sceneNode.valid()) return new crfPipe(parent,_sceneNode);
			else return new crfPipe(parent);
		}

		///Initialises the crfConfig 
		///@sa eqOsg::Nodefactory::createConfig
		virtual eq::Config* createConfig(eq::ServerPtr parent){
			return new crfConfig(parent);
		}
		
		///Sets the pipes root node. If this node is set, this node will be passed to the pipe.
		///@param node The to set osg scene node
		void setSceneNode(osg::ref_ptr<osg::Node> node){_sceneNode=node;}

	private:	
		///The sceneNode
		osg::ref_ptr<osg::Node> _sceneNode;
	};
}
#endif
