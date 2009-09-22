/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#include "SceneReader.h"
#include "InitData.h"
#include <osgDB/ReadFile>
#include <osg/Notify>
#include <osgUtil/Optimizer>

using namespace crf;

SceneReader::SceneReader()
{
}

SceneReader::~SceneReader(void)
{
}

osg::ref_ptr<osg::Node> SceneReader::readModel( const std::string &filename )
{
	if (filename.size()>=0) {
		osg::ref_ptr<osgDB::ReaderWriter::Options> options =  new osgDB::ReaderWriter::Options();
		options->setObjectCacheHint(osgDB::ReaderWriter::Options::CACHE_NODES);
		osg::ref_ptr<osg::Node> root = osgDB::readNodeFile(filename,options);
		root->setThreadSafeReferenceCounting(true);
		root->setThreadSafeRefUnref(true);
		if  (!root.valid()) {
			std::cout << "Failed to load model!" << std::endl;
			return NULL;
		}

		//Optimize scenegraph
		osgUtil::Optimizer optOSGFile;
		optOSGFile.optimize (root.get());
		return root;
	}
	else{
		std::cout<<"No filename passed"<<std::endl;
		return NULL;
	}
}
