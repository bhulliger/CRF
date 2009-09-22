/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#include "Config.h"

#include "Util.h"

#include <eq/client/configEvent.h>

#include <osg/Math>

using namespace eqOsg;

static const float maxVerticalAngle = osg::PI;
static const float minVerticalAngle = 0.2;
static const float mouseViewSpeed = 0.005f;
static const float defaultCameraHorizontalAngle( 0.0f );
static const float defaultCameraVerticalAngle( osg::PI / 2.0f );
static const vmml::vec3f defaultCameraViewingDirection( 0., 0., 1. );

Config::Config( eq::base::RefPtr< eq::Server > parent )
    : eq::Config( parent ),
      _moveDirection( 0.0f, 0.0f, 0.0f ),
      _cameraAngleHor( defaultCameraHorizontalAngle ),
      _cameraAngleVer( defaultCameraVerticalAngle ),
      _cameraWalkingVector( 0., 0., 1. ),
      _pointerXDiff( 0.0f ),
      _pointerYDiff( 0.0f ),
	  _camSpeed(0.05f),
	  _camEnabled(true),
	  _FPSSwitch(false),
	  _equalizerStatsSwitch(false),
	  _overlaySwitch(false)
{
}

bool Config::init()
{	registerObject( &_frameData );
    _initData.setFrameDataID( _frameData.getID() );
    registerObject( &_initData );
    return eq::Config::init( _initData.getID() );
}

bool Config::exit()
{
    bool ret = eq::Config::exit();
    _initData.setFrameDataID( EQ_ID_INVALID );
    deregisterObject( &_initData );
    deregisterObject( &_frameData );
    return ret;
}

void Config::updateCamera( float elapsed )
{
    // Update the viewing direction based on the mouse movement
    _cameraAngleHor += mouseViewSpeed * -_pointerXDiff;
    if ( _cameraAngleHor > 2 * osg::PI || _cameraAngleHor < -2 * osg::PI )
        _cameraAngleHor = 0.0f;
    _cameraAngleVer += mouseViewSpeed * _pointerYDiff;
    if ( _cameraAngleVer > maxVerticalAngle )
        _cameraAngleVer = maxVerticalAngle;
    if ( _cameraAngleVer < minVerticalAngle )
        _cameraAngleVer = minVerticalAngle;
    _pointerXDiff = _pointerYDiff = 0.0f;
    vmml::vec3f cameraViewingDirection;
    cameraViewingDirection.x = sin( _cameraAngleHor ) * sin( _cameraAngleVer );
    cameraViewingDirection.z = cos( _cameraAngleHor ) * sin( _cameraAngleVer );
    cameraViewingDirection.y = cos( _cameraAngleVer );
    _cameraWalkingVector = cameraViewingDirection;
    
	// Save camera data to frame data and update the camera position
    _frameData._data.cameraPosition += _moveDirection * elapsed;
    _frameData._data.cameraLookAtPoint = _frameData._data.cameraPosition + cameraViewingDirection;
    _frameData._data.cameraUpVector = vmml::vec3f( 0., 1., 0. );
}

void Config::updateFrameData(){
	_frameData._data.crfFPSSwitch=_FPSSwitch;
	_frameData._data.equalizerStatsSwitch = _equalizerStatsSwitch;
	_frameData._data.crfOverlaySwitch = _overlaySwitch;
	_frameData._data.controlEqCam = _camEnabled;
}

uint32_t Config::startFrame()
{
    float elapsed = _clock.getTimef();
    _clock.reset();
    updateCamera( elapsed );
	updateFrameData();
    const uint32_t version = _frameData.commit();
	return eq::Config::startFrame( version );	
}

void Config::setInitData( const InitData& data )
{
    _initData = data;
}

const InitData& Config::getInitData() const
{
    return _initData;
}

bool Config::mapData( const uint32_t initDataID )
{
    if( _initData.getID() == EQ_ID_INVALID )
    {
        EQCHECK( mapObject( &_initData, initDataID ) );
        unmapObject( &_initData );
    }
    else
        EQASSERT( _initData.getID() == initDataID );

    return true;
}

bool Config::handleEvent( const eq::ConfigEvent* event )
{
	bool eventHandled = false;

	 // Handle events
	switch ( event->data.type ){
        case eq::	Event::KEY_PRESS:
            switch ( event->data.keyPress.key )
            {
				///toggle the eq cam switch
	            case eq::KC_F3:
					_camEnabled = !_camEnabled;
					eventHandled = true;
					break;
				case eq::KC_F4:
					_FPSSwitch = !_FPSSwitch;
					eventHandled = true;
				break;

				case eq::KC_F5:
					_equalizerStatsSwitch = !_equalizerStatsSwitch;
					eventHandled = true;
				break;

				case eq::KC_F6:
					_overlaySwitch = !_overlaySwitch;
					eventHandled = true;
				break;
			}
	}


	///Update the cameras proberties by handling these events
	if (_frameData._data.controlEqCam){
		eventHandled = handleCameraEvents(event);
	}

    // Let Equalizer handle any events we don't handle ourselves here, like the
    // escape key for closing the application.
    if ( !eventHandled )
        return eq::Config::handleEvent( event );
	else{return true;}
}

bool Config::handleCameraEvents(const eq::ConfigEvent* event) {
	const float moveSpeed = _camSpeed;
	bool eventHandled = false;

	eq::Event eventTmp = event->data;

	switch ( event->data.type )
    
	{
		// Set _moveDirection to a null vector after a key is released so that the updating
		// of the camera position stops
		case eq::Event::KEY_RELEASE:
            if ( (event->data.keyPress.key >= 261 && event->data.keyPress.key <= 266) || event->data.keyPress.key =='W' || event->data.keyPress.key =='w' || event->data.keyPress.key =='D' || event->data.keyPress.key =='d' || event->data.keyPress.key =='S' || event->data.keyPress.key =='s' || event->data.keyPress.key =='A' || event->data.keyPress.key =='a')
                _moveDirection = vmml::Vector3<float>( 0, 0, 0 );
        break;

        // Change _moveDirection when the appropriate key is pressed
        case eq::	Event::KEY_PRESS:
            switch ( event->data.keyPress.key )
            {

				case eq::KC_F10:
					_camSpeed *=0.9f;
					eventHandled = true;
					break;
				case eq::KC_F11:
					_camSpeed *=1.1f;
					eventHandled = true;
					break;
	            case eq::KC_LEFT:
				case 'a':
				case 'A':
                    _moveDirection = norm( orthographicVector( _cameraWalkingVector ) ) * moveSpeed;
                    eventHandled = true;
                    break;

                case eq::KC_UP:
				case 'w':
				case 'W':
                    _moveDirection = norm( _cameraWalkingVector ) * moveSpeed;
                    eventHandled = true;
                    break;

                case eq::KC_RIGHT:
				case 'd':
				case 'D':
                    _moveDirection = -norm( orthographicVector( _cameraWalkingVector ) ) * moveSpeed;
				    eventHandled = true;
                    break;

                case eq::KC_DOWN:
				case 's':
				case 'S':
                    _moveDirection = -norm( _cameraWalkingVector ) * moveSpeed;
                    eventHandled = true;
                    break;

                case eq::KC_PAGE_UP:
                    _moveDirection.y = moveSpeed;
                    eventHandled = true;
                    break;

                case eq::KC_PAGE_DOWN:
                    _moveDirection.y = -moveSpeed;
                    eventHandled = true;
                    break;
            }
            break;

        // Turn left and right, up and down with mouse pointer
        case eq::Event::POINTER_MOTION:
			if ( (event->data.pointerMotion.buttons == eq::PTR_BUTTON1) &&
                 event->data.pointerMotion.x<=event->data.context.pvp.w &&
                 event->data.pointerMotion.x>= 0 &&
                 event->data.pointerMotion.y<=event->data.context.pvp.h &&
                 event->data.pointerMotion.y>= 0){
                _pointerXDiff += event->data.pointerMotion.dx;
                _pointerYDiff += event->data.pointerMotion.dy;
                eventHandled = true;
            }
            break;
    }
	return eventHandled;

}

