/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#include "crfConfig.h"

bool crf::crfConfig::handleEvent(const eq::ConfigEvent* event){
	eq::Event eventTmp = event->data;

	///Pass the mouse and keyboard events to framedata
	if (eventTmp.type == eq::Event::KEY_PRESS || eventTmp.type == eq::Event::KEY_RELEASE){
		//push the event at the back of the queue
	   _frameData._eventQueue.push_back(eventTmp);
	}
	///Mouse events
	else if (eventTmp.type == eq::Event::POINTER_BUTTON_PRESS || eventTmp.type == eq::Event::POINTER_BUTTON_RELEASE || eventTmp.type == eq::Event::POINTER_MOTION){
		//push the event at the back of the queue
		_frameData._eventQueue.push_back(eventTmp);
	}

	return eqOsg::Config::handleEvent(event);
}

uint32_t crf::crfConfig::finishFrame(){
	_frameData._eventQueue.clear();
	return eq::Config::finishFrame();
}