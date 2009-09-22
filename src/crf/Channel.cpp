/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#include "Channel.h"

#include "EqViewer.h"
#include "Pipe.h"
#include "Util.h"

#include <osg/ref_ptr>
#include <osgViewer/ViewerEventHandlers>

using namespace eqOsg;

Channel::Channel( eq::Window* parent )
    : eq::Channel( parent )
{
	
}

bool Channel::configInit( const uint32_t initID )
{
    if( !eq::Channel::configInit( initID )) return false;
	
	const eq::Viewport& viewport = getViewport();
	Pipe *pipe = static_cast<Pipe*>( getPipe() );
    osg::ref_ptr<EqViewer> viewer = pipe->getViewer();
	_window = viewer->setUpViewerAsEmbeddedInWindow(viewport.x,viewport.y,viewport.w,viewport.h);
     
    return true;
}

osg::Matrix Channel::setPlainViewMatrix( const Pipe *pipe ) const
{	 const FrameData::Data &data = pipe->getFrameData()._data;
	  const osg::Vec3f pos = osg::Vec3f( data.cameraPosition.x,
						data.cameraPosition.y,
						data.cameraPosition.z );
	  const osg::Vec3f view = osg::Vec3f( data.cameraLookAtPoint.x,
						 data.cameraLookAtPoint.y,
						 data.cameraLookAtPoint.z );
	  const osg::Vec3f up = osg::Vec3f( data.cameraUpVector.x,
					   data.cameraUpVector.y,
					   data.cameraUpVector.z );

	  pipe->getViewer()->getCamera()->setViewMatrixAsLookAt( pos, view, up );
  return pipe->getViewer()->getCamera()->getViewMatrix();
}

void Channel::frameDraw( const uint32_t frameID )
{
	// setup OpenGL State
    eq::Channel::frameDraw( frameID );

    // get the pipe and the viewer
    Pipe *pipe = static_cast<Pipe*>( getPipe() );
    osg::ref_ptr<EqViewer> viewer = pipe->getViewer();
  
	const FrameData::Data &data = pipe->getFrameData()._data;
	const eq::PixelViewport& viewport = getPixelViewport();
	
	//update the viewers embedded window's size.
	if (_window.valid()){
		_window->resized(viewport.x,viewport.y, viewport.w, viewport.h);
		// push the modification as event.
		_window->getEventQueue()->windowResize(viewport.x,viewport.y,viewport.w, viewport.h);
	}

	// set the correct viewport (which can change each frame)
    viewer->setViewport( this );

    // set a view matrix and make sure it is multiplied with the head
    // matrix of Equalizer
    osg::Matrix headView = setPlainViewMatrix( pipe );
    headView.postMult( vmmlToOsg( getHeadTransform() ) );
	//set the channels correct view matrix to the osgViewer's camera
    viewer->getCamera()->setViewMatrix( headView );

    // render the scene graph
	if (viewer.valid()) viewer->frame();

	if (data.crfFPSSwitch) drawFPS();
	//draw the fance eq-implemented stats
	if (data.equalizerStatsSwitch) drawStatistics();
	//draw info txt
	if (data.crfOverlaySwitch)drawInfoText("BFH-TI Cave Rendering Framework");
}
void Channel::drawFPS(){
	//get the font-object
	const eq::util::BitmapFont& font = getWindow()->getObjectManager()->getDefaultFont();
	
	_fpsData.fpsFrames++;
	_fpsData.fpsCurrentTime = getConfig()->getTime();
	_fpsData.fpsElapsedTime = _fpsData.fpsCurrentTime  - _fpsData.fpsLastUpdateTime;

	
	if (_fpsData.fpsElapsedTime>1000){
		//calc the fps number
		_fpsData.currentFPS = (_fpsData.fpsFrames / _fpsData.fpsElapsedTime*1000);

		_fpsData.fpsFrames = 0;
		_fpsData.fpsLastUpdateTime = _fpsData.fpsCurrentTime;
	}

	//write the result to a buffer
	std::ostringstream fpsString;
	fpsString << "FPS: " << _fpsData.currentFPS;

	//create a opengl state to draw text on the screen
	EQ_GL_CALL( applyBuffer( ));
	EQ_GL_CALL( applyViewport( ));
	EQ_GL_CALL( setupAssemblyState( ));
	//draw the number
	
	eq::PixelViewport pvp    = getWindow()->getPixelViewport();
	pvp.x = 0;
	pvp.y = 0;

	glColor3f( 1.f, 1.f, 1.f );
	glRasterPos3f( 10.f, pvp.getYEnd()-20, 0.99f );
	font.draw( fpsString.str());
	//reset opengl state
	EQ_GL_CALL( resetAssemblyState( ));
}

void Channel::drawInfoText(std::string txt){
	if (txt.length()>0){
		//get the font-object
		const eq::util::BitmapFont& font = getWindow()->getObjectManager()->getDefaultFont();

		//set a opengl state to draw text on the screen
		EQ_GL_CALL( applyBuffer( ));
		EQ_GL_CALL( applyViewport( ));
		EQ_GL_CALL( setupAssemblyState( ));

		glColor3f( .3f, 1.f, 0.3f );
		glRasterPos3f( 10.f, 3.f, 0.99f );
		font.draw(txt);

		EQ_GL_CALL( resetAssemblyState( ));
	}
}

