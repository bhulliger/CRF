/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#ifdef WIN32
#define EQ_IGNORE_GLEW
#endif

#ifndef WIN32
#include <eq/eq.h> // to prevent "gl.h included before glew.h"
#endif

#include "Pipe.h"

#include "Config.h"
#include "SceneReader.h"

#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <eq/client/configEvent.h>

using namespace eqOsg;

Pipe::Pipe( eq::Node* parent )
    : eq::Pipe( parent )
{
	_viewer = new EqViewer();
	_sceneGraphCreated = false;
}

Pipe::~Pipe()
{
}

const FrameData& Pipe::getFrameData()const
{
    return _frameData;
}

osg::ref_ptr<EqViewer> Pipe::getViewer() const
{
    return _viewer;
}

bool Pipe::configInit( const uint32_t initID )
{
    if( !eq::Pipe::configInit( initID ) )
        return false;

    // Get InitData and map FrameData
    Config* config = static_cast<Config*>( getConfig() );
    const InitData& initData = config->getInitData();
    const uint32_t frameDataID = initData.getFrameDataID();

	const bool mapped = config->mapObject( &_frameData, frameDataID );
    EQASSERT( mapped );

	_usesModel = initData.getLoadModel();
    _modelFile = initData.getModelFileName();

	if (_usesModel && !_sceneGraphCreated){
		createSceneGraph(_modelFile);
	}

	return mapped;
}

void Pipe::createSceneGraph(std::string modelFileName){
	crf::SceneReader sceneReader;
	osg::ref_ptr<osg::Node> geometryChild = sceneReader.readModel(modelFileName);
	
	geometryChild->setThreadSafeReferenceCounting(true);
	geometryChild->setThreadSafeRefUnref(true);
	geometryChild->setDataVariance(osg::Object::STATIC);
    if ( !geometryChild.valid() ) {
        std::cout << "Model " << modelFileName <<" not found. Empty viewer!" << std::endl;
    }
	else{
		_viewer->setSceneData(correctCoordsys(geometryChild.get()));
		_sceneGraphCreated = true;
	}
}

osg::ref_ptr<osg::Node> Pipe::correctCoordsys(osg::ref_ptr<osg::Node> nodeToRotate){
	// Rotate the object 90 degree around the X axis and afterwards 180 around the Y axis to match the coordinate system
    // Equalizer uses
    osg::Matrix matrixX;
	osg::Matrix matrixY;
    osg::ref_ptr<osg::MatrixTransform> staticRotationNodeX = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform> staticRotationNodeY = new osg::MatrixTransform;
    matrixX.makeRotate( osg::PI_2, osg::Vec3( 1., 0., 0. ) );
	matrixY.makeRotate( osg::PI, osg::Vec3( 0., 1., 0. ) );
    staticRotationNodeX->setMatrix( matrixX );
	staticRotationNodeY->setMatrix(matrixY);
	staticRotationNodeY->addChild(nodeToRotate.get());
	staticRotationNodeY->setDataVariance( osg::Object::STATIC );
	staticRotationNodeX->addChild(staticRotationNodeY.get());
	staticRotationNodeX->setDataVariance( osg::Object::STATIC );
	return staticRotationNodeX.get();
}

osg::ref_ptr<osg::Node> Pipe::correctCoordsys(osg::ref_ptr<osg::Node> nodeToRotate,osg::Matrix matrix){
    osg::ref_ptr<osg::MatrixTransform> staticRotationNode = new osg::MatrixTransform;
    staticRotationNode->setMatrix( matrix );
	staticRotationNode->addChild(nodeToRotate.get());
	staticRotationNode->setDataVariance( osg::Object::STATIC );
	return staticRotationNode.get();
}

bool Pipe::configExit()
{
    getConfig()->unmapObject( &_frameData );
	// deref the viewer
	if (_viewer.valid())_viewer=0;
    return eq::Pipe::configExit();
}

void Pipe::frameStart( const uint32_t frameID,
                       const uint32_t frameNumber )
{
    eq::Pipe::frameStart( frameID, frameNumber );
	_frameData.sync( frameID );
}
