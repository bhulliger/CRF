/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef FRAMEDATA_H
#define FRAMEDATA_H

#include <eq/net/object.h>
#include <vmmlib/vector3.h>
#include <eq/client/configEvent.h>

namespace eqOsg {

	///	FrameData holds all data which is updated each frame.
	/// It is sent by the server to all render clients.
	class FrameData : public eq::net::Object
	{

	public:
		/// Initialises everything to zero.
		FrameData();

		/// The FrameData's struct to hold members.
		struct Data
		{
			///eq-camera switch
			bool controlEqCam;

			/// The position of the camrra, in world coordinates
			vmml::Vector3f cameraPosition;

			/// The point the camera is looking at, in world coordinates
			vmml::Vector3f cameraLookAtPoint;

			/// The up vector of the camera
			vmml::Vector3f cameraUpVector;

			/// Enable osg Trackball Manipulator
			bool osgTrackBallSwitch;

			/// Enable eq stats
			bool equalizerStatsSwitch;
			
			/// Enable crfOverlay
			bool crfOverlaySwitch;

			///show crf FPS
			bool crfFPSSwitch;
		};
		
		///our data struct
		Data _data;
		
		///save the eq events to pass it to the pipe
		std::vector<eq::Event> _eventQueue;

	protected:

		/// Change type is set to INSTANCE
		/// @return The Equalizer change type.
		virtual eq::net::Object::ChangeType getChangeType() const;

		/// Passes the FrameData's data to the stream.
		/// @param stream The Equalizer stream to write.
		virtual void getInstanceData( eq::net::DataOStream& stream );

		/// Gets the data out of the stream.
		/// @param stream The Equalizer stream to read.
		virtual void applyInstanceData( eq::net::DataIStream& stream );
	};
}
#endif
