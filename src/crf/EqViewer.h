/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef EQVIEWER_H
#define EQVIEWER_H

namespace eq {
    class Channel;
}

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

namespace eqOsg {

	/// A Viewer which can be used with Equalizer.
	///
	/// A normal Viewer from OSG would try to create its own windows, which
	/// we don't want to, since they are set up by Equalizer for us.
	///
	/// The EqViewer solves this by setting the correct context and viewport.
	///
	/// Call setViewport() in your frameDraw() method.
	class EqViewer : public osgViewer::Viewer
	{
	public:
		/// Default constructor. Sets the threading model to "Single" because embedded window viewers need this.
		EqViewer();

		/// Sets the viewport of the Camara of the scene so that it matches
		/// the viewport of the given Equalizer channel.
		/// @param channel The channel with the Equalizer set viewport.
		void setViewport(eq::Channel *channel);
	};
}
#endif