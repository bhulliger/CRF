/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#include "Node.h"

#include "Config.h"

using namespace eqOsg;

Node::Node( eq::Config* parent )
    : eq::Node( parent )
{
}

bool Node::configInit(const uint32_t initID)
{
    if( !eq::Node::configInit( initID ) )
        return false;

    Config* config = static_cast<Config*>( getConfig() );
    return config->mapData( initID );
}
