/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#include "FrameData.h"

#include <eq/eq.h>

using namespace eqOsg;

FrameData::FrameData()
{
	///camera base setup
    _data.cameraPosition = vmml::Vector3f::ZERO;
    _data.cameraPosition.z -= 4.0f;
    _data.cameraLookAtPoint = vmml::Vector3f::ZERO;
    _data.cameraUpVector = vmml::Vector3f::ZERO;
	_data.controlEqCam=true;
	_data.equalizerStatsSwitch = false;
	_data.crfFPSSwitch=false;
	_data.crfOverlaySwitch=false;
}

eq::net::Object::ChangeType FrameData::getChangeType() const
{
    return INSTANCE;
}

void FrameData::getInstanceData( eq::net::DataOStream& stream )
{
	///write the framedata to the stream
	stream<<_data<<_eventQueue;
}

void FrameData::applyInstanceData( eq::net::DataIStream& stream )
{
	///get the framedata out of the stream
	stream>>_data>>_eventQueue;

}
