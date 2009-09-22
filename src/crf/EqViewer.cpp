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
#include <eq/client/channel.h>

#include "EqViewer.h"

#include <vmmlib/matrix4.h>
#include <vmmlib/frustum.h>

using namespace eqOsg;

EqViewer::EqViewer()
{
	//make the viewer single threaded
    setThreadingModel(osgViewer::Viewer::SingleThreaded);
}

void EqViewer::setViewport(eq::Channel *channel)
{
    //Set the Frustum of the Channel
    const vmml::Frustumf& channelfrustum = channel->getFrustum();
    getCamera()->setProjectionMatrixAsFrustum( channelfrustum.left, channelfrustum.right,
                                               channelfrustum.bottom, channelfrustum.top,
                                               channelfrustum.nearPlane, channelfrustum.farPlane );

    //Set absolute pixelvalues for Viewport
    const eq::PixelViewport& channelviewport = channel->getPixelViewport();
    getCamera()->setViewport( channelviewport.x,channelviewport.y,
                              channelviewport.w,channelviewport.h );

	if (isRealized()==false)this->realize();
}
