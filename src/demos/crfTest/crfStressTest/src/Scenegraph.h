/*
 *  Filename: 		Scenegraph.h
 *  Project:		crfStressTest
 *  Author:		Stefan Broder (brods1@bfh.ch)
 *  Creation Date:	29.05.2009
 *  Purpose:		Create a scene graph with (huge) models to test the performance
 *
 */

#ifndef _SCENEGRAPH
#define _SCENEGRAPH

#include <osg/Node>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Light>
#include <osg/LightSource>

#include <osgDB/ReadFile>

#include <iostream>
#include <string>

#include "Model.h"
#include "IlluminatedModel.h"


// the scene class creates, as the name says, a scene graph.
class Scenegraph {
public:
	// con-/destructors
        Scenegraph();
        ~Scenegraph();

	// createScenegrpah returns a node pointer to the
	// scene graph
	osg::Node* createScenegraph(std::string filename);
	// updateScenegraph is used to modify the scene
	// graph from time to time.
	void updateScenegraph();

	// loadModel takes a string with a model name 
	// (*.osg prefered). The model has to reside somewhere
	// in the environment.
	void loadModel(std::string filename);

	// turn on/off rotation
	void toggleRotation();
	// turn on/off illumination
	void toggleIllumination();
        
private:
	// model pointers
	Model::Model *_model_left, *_model_right, *_model_bottom;
	IlluminatedModel::IlluminatedModel *_model_center;

	// variable for rotation
	bool _isRotating;
	
};

#endif
