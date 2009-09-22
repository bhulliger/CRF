/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#ifndef CHANNEL_H
#define CHANNEL_H

#ifdef WIN32
#define EQ_IGNORE_GLEW
#endif

#include <eq/client/channel.h>
#include <osg/Matrix>
#include <osgViewer/Viewer>

namespace eqOsg {

	class FrameData;
	class Pipe;

	 /// The Channel renders the frames in frameDraw().
	 /// This is done by querying the pipe for the viewer and then asking the viewer
	 /// to render the scene.
	class Channel : public eq::Channel
	{
	public:
		/// Creates a channel and sets its parent window.
		/// @param parent The equalizer parent window.
		Channel( eq::Window* parent );

	protected:
		///Renders the scene graph.
		///Draw the frame. Calls drawFPS(), drawInfoText() and eq::Channel::drawStatistics().
		///@param frameID The frame's id to render.
		virtual void frameDraw( const uint32_t frameID );
		
		///Config initialisation.
		///@param initID The initID of the config.
		///@return True if succeed.
		virtual bool configInit( const uint32_t initID );

		/// This function gets the camera position and viewing direction information out of the
		/// frame data and sets the view matrix of the camera of the viewer of the pipe based
		/// on this information.
		/// This view matrix is then also returned.
		/// @param frameData The pipe which holds the FrameData Object to get the camera's position.
		/// @return The newly calculated matrix
		osg::Matrix setPlainViewMatrix( const Pipe* frameData ) const;

		///Prints the self calculated FPS value.
		virtual void drawFPS();
		
		///Prints the channel's info Text.
		virtual void drawInfoText(std::string txt);

	private:
		///The virtual osg window, produced by the EqViewer.
		osg::observer_ptr<osgViewer::GraphicsWindow> _window;  

		///framecounter stuff
		struct fpsData {
			int fpsFrames;
			float currentFPS;
			int fpsCurrentTime;
			float fpsLastUpdateTime;
			float fpsElapsedTime;
		};
		fpsData _fpsData;
		///small info txt on bottom of screen
		std::string _infoText;
	};
}
#endif
