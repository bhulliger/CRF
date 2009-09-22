/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#ifndef CRFCONFIG_H
#define CRFCONFIG_H

#include "Config.h"

namespace crf {
	/// This class extends the basic eqOsg config class with support vor event forwarding to the pipe's viewer.
	/// @sa eqOsg::Config
	class crfConfig : public eqOsg::Config{

	public:
		/// @sa eqOsg::Config
		crfConfig(eq::ServerPtr parent) : eqOsg::Config(parent){};

		/// Passes the desired events to the FrameData's event queue and calls the eqOsg::Config::handleEvents function.
		/// @param event The to handle event.
		/// @return True if the an event has been handled.
		/// @sa eqOsg::Config::hanleEvent()
		virtual bool handleEvent(const eq::ConfigEvent* event);

		/// Clears the eventlist in FrameData and calls the base eq::Config::frameFinish().
		/// @return The finished frame's number.
		/// @sa eq::Config::finishFrame
		virtual uint32_t finishFrame();
	};
}
#endif

