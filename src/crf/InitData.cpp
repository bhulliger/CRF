/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#include "InitData.h"

#include <eq/eq.h>

using namespace eqOsg;

InitData::InitData(){
	_loadModel=false;
	_modelFileName ="";
}

InitData::~InitData()
{
    setFrameDataID( EQ_ID_INVALID );
}

void InitData::setFrameDataID( const uint32_t id )
{
    _frameDataID = id;
}

uint32_t InitData::getFrameDataID() const
{
    return _frameDataID;
}

void InitData::getInstanceData( eq::net::DataOStream& stream )
{
	stream << _frameDataID << _modelFileName << _loadModel;
}

void InitData::applyInstanceData( eq::net::DataIStream& stream )
{
	stream >> _frameDataID >> _modelFileName >> _loadModel;
    EQASSERT( _frameDataID != EQ_ID_INVALID );
}


bool InitData::parseCommandLine( char **argv, int argc )
{
    for ( int i = 0; i < argc; i++ )
    {
        std::string argument( argv[i] );
        std::string modelPrefix( "--model=" );
        if ( argument.find( modelPrefix ) == 0 )
        {
            std::string modelFile = argument.substr( modelPrefix.size(), std::string::npos );
            setModelFileName( modelFile );
            setLoadModel( true );
        }
    }

    return true;
}
