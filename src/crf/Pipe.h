/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef PIPE_H
#define PIPE_H

#include "EqViewer.h"
#include "FrameData.h"

#include <eq/client/pipe.h>
#include <osg/MatrixTransform>
#include <osg/Node>

#include <eq/client/configEvent.h>

namespace eqOsg {

	/// The Pipe holds the viewer and the frame data.
	/// Each frame, it updates the scene graph of the viewer with the
	/// new data of the frame data. The frame data is synced with the server.
	/// @sa eq::Pipe
	class Pipe : public eq::Pipe
	{
	public:
		///@sa eq::Pipe::Pipe
		Pipe( eq::Node* parent );
		
		/// Returns the pipe's FrameData object.
		/// @return The FrameData of this pipe.
		const FrameData& getFrameData() const;

		/// Returns the pipe's EqViewer.
		/// @return The Eqviewer of this pipe.
		osg::ref_ptr<eqOsg::EqViewer> getViewer() const;

	protected:
		virtual ~Pipe();

		/// Registers the frame data, so it can be synced with the server later.
		/// @param initID The Equalizer initID.
		/// @return True if everything worked fine.
		virtual bool configInit( const uint32_t initID );

		///Deregisters the frame data.
		/// @return True if everything worked fine.
		virtual bool configExit();

		///Syncs the frame data with the server and calls updateSceneGraph().
		///@sa eq::Pipe::frameStart
		virtual void frameStart( const uint32_t frameID,
								 const uint32_t frameNumber );

		///Creates a scene graph with a model by filename.
		///@param modelFileName The filename of the model. 
		virtual void createSceneGraph(std::string modelFileName);

		///Corrects the coordination system from osg to eq. Rotates the whole scene 90° around the X-axis and 180 around Y to fit 
		///the commonly used Equalizer schema.
		///@param nodeToRotate The node, which should be rotated
		///@return The rotated node
		virtual osg::ref_ptr<osg::Node> correctCoordsys(osg::ref_ptr<osg::Node> nodeToRotate);

		///Transform a desired node around a passed matrix.
		///@param nodeToTransform The node, which should be transformed.
		///@param matrix The transformation matrix.
		///@return The transformed node.
		osg::ref_ptr<osg::Node> correctCoordsys(osg::ref_ptr<osg::Node> nodeToTransform,osg::Matrix matrix);

		///The FrameData object.
		FrameData _frameData;

		///The pipe's EqViewer. 
		osg::ref_ptr<eqOsg::EqViewer> _viewer;	

		bool _sceneGraphCreated; ///< Set to true if the scene graph has been created and added to the viewer.

		bool _usesModel; ///< Set to true if a simple model shoudl be load.
		std::string _modelFile; ///< The filename of the to-load model.
	};
}
#endif