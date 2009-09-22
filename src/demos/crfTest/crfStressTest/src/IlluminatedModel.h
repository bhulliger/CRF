/*
 *  Filename: 		IlluminatedModel.h
 *  Project:		crfStressTest
 *  Author:		Stefan Broder (brods1@bfh.ch)
 *  Creation Date:	05.06.2009
 *  Purpose:		Container class for a model with two rotating lights
 *
 */

#ifndef _ILLUMINATED_MODEL
#define _ILLUMINATED_MODEL

#include <osg/Node>
#include <osg/Vec3d>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Shape>

#include <osg/Light>
#include <osg/LightSource>
#include <osg/StateSet>

#include <osgDB/ReadFile>

#include <iostream>
#include <string>

#include "Model.h"

// container class for a illuminated model. inherits from a model.
class IlluminatedModel : public Model::Model {
public:
	// con-/destructors
	// takes either a string of a model or a pointer to a model
	// and a state set pointer.
        IlluminatedModel(std::string filename, osg::StateSet *ss);
        IlluminatedModel(osg::Node* model, osg::StateSet *ss);
        ~IlluminatedModel();

	// rotate the lights around the model. (rotation angle is 
	// fix so far)
	void rotateLights();
	// turn on/off lights
	void toggleLights();
	
private:
	// instance vars
	osg::ref_ptr<osg::PositionAttitudeTransform> _patLight1, _patLight2;
	void createLight(int lightNum, osg::PositionAttitudeTransform *patLight, osg::StateSet *ss, osg::Vec3d position, 
				osg::Vec3d ambient, osg::Vec3d diffuse, osg::Vec3d specular);
	bool isIlluminated;
	
};
#endif

