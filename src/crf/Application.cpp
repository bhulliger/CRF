/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/
#include "Application.h"
#include "Config.h"

#include <eq/client/server.h>
#include <eq/client/configParams.h>

using namespace eqOsg;

Application::Application( const InitData& initData )
    : mInitData( initData )
{
}

int Application::run()
{
    // 1. connect to server
    eq::ServerPtr server = new eq::Server;
    if( !connectServer( server ) )
    {
		std::cout << "Can't open server" << std::endl;
        return EXIT_FAILURE;
    }

    // 2. choose config
    eq::ConfigParams configParams;
    Config* config = static_cast<Config*>( server->chooseConfig( configParams ) );

    if( !config )
    {
		std::cout << "No matching config on server" << std::endl;
        disconnectServer( server );
        return EXIT_FAILURE;
    }

    config->setInitData( mInitData );
    if( !config->init() )
    {
        std::cout << "Config initialization failed: " << config->getErrorMessage() << std::endl;
        server->releaseConfig( config );
        disconnectServer( server );
        return EXIT_FAILURE;
    }

    // 4. run main loop
    while( config->isRunning() )
    {
        config->startFrame();
        config->finishFrame();
    }
    config->finishAllFrames();

    // 5. exit config
    config->exit();

    // 6. cleanup and exit
    server->releaseConfig( config );
    if( !disconnectServer( server )) {
		std::cout << "Client::disconnectServer failed" << std::endl;
    }

    server = 0;

    return EXIT_SUCCESS;
}

bool Application::clientLoop()
{
    while( true )
    {
        if( !eq::Client::clientLoop() )
            return false;
    }
    return true;
}
