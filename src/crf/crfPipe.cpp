/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#include "crfPipe.h"
#include "SceneReader.h"
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>

#include <iostream>

using namespace crf;

//Constructor with its own viewer
crfPipe::crfPipe(eq::Node* parent,osg::ref_ptr<eqOsg::EqViewer> viewer)
	: eqOsg::Pipe( parent )
{	_viewer = 0;
	_viewer = viewer.get();
	_sceneGraphCreated=true;
}

crfPipe::crfPipe(eq::Node* parent,osg::ref_ptr<osg::Node> rootNode)
: eqOsg::Pipe( parent )
{
	_viewer->setSceneData(correctCoordsys(rootNode.get()));
	_sceneGraphCreated = true;
}

void crfPipe::setUpViewer(){
	osg::ref_ptr<osgViewer::StatsHandler> stats = new osgViewer::StatsHandler();
	stats->setKeyEventTogglesOnScreenStats(osgGA::GUIEventAdapter::KEY_F2);
	if (_viewer.valid()) _viewer->addEventHandler(stats.get());
}


bool crfPipe::configInit(const uint32_t initID ){
	
	bool ret = eqOsg::Pipe::configInit(initID);
	setUpViewer();
	
	if (!_sceneGraphCreated){
		createSceneGraph();
	}
	return ret;
}

void crfPipe::createSceneGraph(){
	//if this function isn't overriden, try to load osgcool
	eqOsg::Pipe::createSceneGraph("osgcool.osg");
}

bool crfPipe::configExit(){
	
	return Pipe::configExit();
}

void crfPipe::frameStart( const uint32_t frameID,
                       const uint32_t frameNumber )
{
	//call the std eqOsg frame start
    eqOsg::Pipe::frameStart( frameID, frameNumber );

	//convert the events
	convertEqEventsToOsg();

	//update the scene graph
	updateSceneGraph();
}

///Basic implementation, converts only basic keys yet
void crfPipe::convertEqEventsToOsg(){
	osg::ref_ptr<eqOsg::EqViewer> viewer = getViewer();

	int queueSize = _frameData._eventQueue.size();

	for (int i=0;i<queueSize;i++){
		eq::Event eventTmp = _frameData._eventQueue.at(i);
		switch (eventTmp.type){
			
			///////////////key press ////////////////////////////
			case (eq::Event::KEY_PRESS):
				convertKeyPressEvents(eventTmp);
				break;

			///////////////////// key release  /////////////////////////////////
			case (eq::Event::KEY_RELEASE):
				convertKeyReleaseEvents(eventTmp);
				break;
			case (eq::Event::POINTER_BUTTON_PRESS):
			case (eq::Event::POINTER_BUTTON_RELEASE):
			case (eq::Event::POINTER_MOTION):
				convertMouseEvents(eventTmp);
				break;
		}
	}
}

///Convert the key press events
void crfPipe::convertKeyPressEvents(eq::Event eventTmp){
	
	osg::ref_ptr<eqOsg::EqViewer> viewer = getViewer();

	switch (eventTmp.keyPress.key ){
		case(eq::KC_SHIFT_L):{
			viewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Shift_L);
			break;
			}
		case(eq::KC_SHIFT_R):{
			viewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Shift_R);
			break;
			}
		case(eq::KC_F2):{
			viewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_F2);
			break;
			}
		case(eq::KC_LEFT):{
			viewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Left);
			break;
			}
		case(eq::KC_RIGHT):{
			viewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Right);
			break;
			}
		case(eq::KC_UP):{
			viewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Up);
			break;
			}
		case(eq::KC_DOWN):{
			viewer->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Down);
			break;
			}
		default:{
			viewer->getEventQueue()->keyPress(eventTmp.keyPress.key);
			break;
		}
	}
}

///convert the key release events
void crfPipe::convertKeyReleaseEvents(eq::Event eventTmp){
	osg::ref_ptr<eqOsg::EqViewer> viewer = getViewer();

	switch (eventTmp.keyRelease.key ){
		case(eq::KC_SHIFT_L):{
			viewer->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KEY_Shift_L);
			break;
			}
		case(eq::KC_SHIFT_R):{
			viewer->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KEY_Shift_R);
			break;
			}
		case(eq::KC_LEFT):{
			viewer->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KEY_Left);
			break;
			}
		case(eq::KC_RIGHT):{
			viewer->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KEY_Right);
			break;
			}
		case(eq::KC_UP):{
			viewer->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KEY_Up);
			break;
			}
		case(eq::KC_DOWN):{
			viewer->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KEY_Down);
			break;
			}
		default:{
			viewer->getEventQueue()->keyRelease(eventTmp.keyPress.key);
			break;
		}
	}

}

///convert the mouse events
void crfPipe::convertMouseEvents(eq::Event eventTmp){
	uint32_t buttonNr =0;
	switch (eventTmp.pointer.button){
		case (eq::PTR_BUTTON1):
			buttonNr=1;
		break;
		case (eq::PTR_BUTTON2):
			buttonNr=3;
		break;
		case (eq::PTR_BUTTON3):
			buttonNr=2;
		break;
		case (eq::PTR_BUTTON4):
			buttonNr=4;
		break;
	}
	switch (eventTmp.type){
		case (eq::Event::POINTER_BUTTON_PRESS):
			_viewer->getEventQueue()->mouseButtonPress(eventTmp.pointerButtonPress.x,eventTmp.pointerButtonPress.y,buttonNr);
			break;
		case (eq::Event::POINTER_BUTTON_RELEASE):
			_viewer->getEventQueue()->mouseButtonRelease(eventTmp.pointerButtonRelease.x,eventTmp.pointerButtonRelease.y,buttonNr);
			break;
		case (eq::Event::POINTER_MOTION):
			_viewer->getEventQueue()->mouseMotion(eventTmp.pointerMotion.x,eventTmp.pointerMotion.y);
			break;
	}
}
