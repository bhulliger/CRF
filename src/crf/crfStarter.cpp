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

#include "Application.h"
#include "InitData.h"
#include "crfNodeFactory.h"

#include <eq/client/init.h>

#include "crfStarter.h"

using namespace eqOsg;

int crf::crfStarter::run(int argc, char** argv){
   
	// 1. parse arguments
    InitData initData;
    if ( !initData.parseCommandLine(argv,argc ) )
        return -1;

    // 2. Equalizer initialization
	crfNodeFactory* nodeFactory = 0;
	if (_nodeFactory !=0) nodeFactory = _nodeFactory;
	else nodeFactory = new crfNodeFactory();
	if( !eq::init(argc, argv, nodeFactory ) )
    {
		std::cout << "Equalizer init failed" << std::endl;
        return EXIT_FAILURE;
    }

    // 3. initialization of local client node
    eq::base::RefPtr<Application> client = new Application( initData );
    if( !client->initLocal(argc,argv))
    {
		std::cout << "Can't init client" << std::endl;
        eq::exit();
        return EXIT_FAILURE;
    }

    // 4. run client
    const int ret = client->run();

    // 5. cleanup and exit
    client->exitLocal();

    client = 0;

    eq::exit();
	
	return ret;
}

int crf::crfStarter::run(int argc, char** argv, osg::ref_ptr<osg::Node> node){
	
	crfNodeFactory* nodefactory = new crf::crfNodeFactory();
	nodefactory->setSceneNode(node);

	setNodeFactory(nodefactory);

	return run(argc,argv);
}

std::string crf::crfStarter::parseCommandLineForString(int argc, char** argv, std::string searchString)
{
	if (searchString.size()<=0)return "";

    for ( int i = 0; i < argc; i++ )
    {
        std::string argument( argv[i] );
        if ( argument.find( searchString ) == 0 )
        {
            return argument.substr( searchString.size(), std::string::npos );
        }
    }
    return "";
}