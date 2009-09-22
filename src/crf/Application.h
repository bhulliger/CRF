/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "InitData.h"

#include <eq/client/client.h>

/// \namespace eqOsg \brief Very basic functions to display an osg scene graph with equalizer. 
/// Includes EqViewer to be used instead of the std osgViewer::Viewer.
namespace eqOsg {

	///Sets up the whole eqOsg Equalizer application.
	///Contains the Equalizer main loop.
	class Application : public eq::Client
	{
	public:
		///Constructor to pass the init data class
		/// \param initData The destributet init data object
		Application( const InitData& initData );
		
		///Run this equalizer application.
		int run();

	protected:
		/// The equalizer client loop.
		virtual bool clientLoop();

	private:
		///Holds the initalisation data.
		const InitData& mInitData; 		
	};
}
#endif

