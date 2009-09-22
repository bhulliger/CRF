/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef NODE_H
#define NODE_H

namespace eq {
    class Config;
}

#include <eq/client/node.h>

namespace eqOsg {
		
	///A node represents the renderclient.
	///because this part doesn't bother the std-equalizer implementation, we don't need big changes here
	///@sa eq::Node
	class Node : public eq::Node
	{

	public:
		///@sa eq::Node::Node
		Node( eq::Config* parent );

	protected:
		/// Generates "our" ConfigInit object.
		/// @param initID The initID.
		virtual bool configInit( const uint32_t initID );
	};
}
#endif
