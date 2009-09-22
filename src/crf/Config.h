/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include "FrameData.h"
#include "InitData.h"

#include <eq/base/clock.h>
#include <eq/client/config.h>

namespace eqOsg {

	/// This class handles the eqOsg basic config for Equalizer. The Equalizer related event handling is
	/// done here. The eqOsg basic camera calculations are done here as well.
	/// @sa eq::Config
	class Config : public eq::Config
	{
	public:

		/// Calls the base constructor and initialises the camera.
		/// @sa eq::Config::Config
		Config( eq::base::RefPtr< eq::Server > parent );

		/// Initialises our distributet data and calls the eq::Config::init().
		///	@return True if everything succeed.
		virtual bool init();

		/// When exiting the configuration, the distributed data gets deregistered after the
		/// base eq::Config::exit() was called.
		/// @return True if everything worked fine.
		virtual bool exit();

		/// Starts the new frame for rendering.
		/// Camera gets updated with the elapsed time, the frameData gets commited and the base startFrame function gets called.
		/// @return Returns the frames ID
		virtual uint32_t startFrame();

		/// Reimplemented for camera controls.
		/// Handles the Equalizer events. If camera is enabled handleCameraEvents gets called
		/// @param event The event passed by Equalizer.
		/// @return True, if the event has been handled
		virtual bool handleEvent( const eq::ConfigEvent* event );

		/// Reimplemented to register the framedata object
		/// @param data The init data object.
		virtual void setInitData( const InitData& data );

		/// Returns the initData
		/// @return The initData object.
		const InitData& getInitData() const;

		/// Maps our initData
		/// @param initDataID The initData's ID.
		/// @return True if everything worked fine.
		bool mapData( const uint32_t initDataID );

	protected:
		///calculates the new properties for the camera
		///@param elapsed The elapsed time of th clock to create frame independent movement.
		virtual void updateCamera( float elapsed );

		///adds the new properties for framedata
		virtual void updateFrameData();

		/// If a keypress happens, this function updates _moveDirection, so that the new camera
		/// position can be calculated in updateCamera().
		/// If a mouse move event happens, this function updates _pointerXDiff and _pointerYDiff,
		/// so that the new camera viewing direction can be calculated in updateCamera().
		/// @param event The Equalizer event.
		/// @return True if the event has been handled.
		virtual bool handleCameraEvents(const eq::ConfigEvent* event);

		///The distributed frame data
		FrameData _frameData;

	private:

		///Eq-Camera manipulator switch
		bool _camEnabled;

		///cam move speed
		float _camSpeed;

		/// Enable osg Trackball Manipulator
		bool _osgTrackBallSwitch;

		/// Enable eq stats
		bool _equalizerStatsSwitch;
		
		/// Enable crfOverlay
		bool _overlaySwitch;
		
		/// Enable crfOverlay
		std::string _overlayText;


		///show crf FPS
		bool _FPSSwitch;

		// The vector of the camera movement in the current frame. This value is computed in
		// handleEvent() and then later in updateFrameData(), the camera position is updated
		// based on this.
		vmml::Vector3f _moveDirection;

		// Same as the camera viewing direction, only that the y component is always zero.
		// Used in handleEvent() to calculate mMoveDirection.
		vmml::Vector3f _cameraWalkingVector;

		// The differences of the mouse pointer position of this and the last frame, in pixels.
		// Used to calculate the new viewing direction
		int32_t _pointerXDiff;
		int32_t _pointerYDiff;

		// The current angles of the camera. The current camera viewing direction is calculated
		// based on this.
		float _cameraAngleHor;
		float _cameraAngleVer;

		// Distributed objects
		InitData _initData;
		

		// Clock used to measure the amount of time the last frame took, to make it
		// possible to have a framerate-independent rotation
		eq::base::Clock _clock;
	};
}
#endif
