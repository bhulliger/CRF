/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef SCENEREADER_H
#define SCENEREADER_H

#include <osg/ref_ptr>
#include <osg/Node>
///This namespace provides additional functions for scene graph rendering, eventhandling and more.
namespace crf {
	///This class provides an advanced *.osg file load mechanism.
	///IMPORTANT: osg-file-file loading can end up in memory abuse when used multiple times with
	///one running instance of the application.
	class SceneReader
	{
	public:
		/// Default constructor
		SceneReader();
		/// Destructor
		~SceneReader();

		///Reads the model by a passed filename
		///@param filename The filename of the Model.
		///@return The returned OSG Node.
		osg::ref_ptr<osg::Node> readModel( const std::string &filename );
	};

	#endif
}