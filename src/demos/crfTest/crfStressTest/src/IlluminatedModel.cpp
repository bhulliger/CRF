/*
 *  Filename: 		IlluminatedIlluminatedModel.cpp
 *  Project:		crfStressTest
 *  Author:		Stefan Broder (brods1@bfh.ch)
 *  Creation Date:	05.06.2009
 *  Purpose:		Container class for a model with two rotating lights
 *
 */

#include "IlluminatedModel.h"

using namespace osg;
using namespace std;

IlluminatedModel::IlluminatedModel(std::string filename, StateSet *ss) : Model::Model(filename) {

	_patLight1 = new PositionAttitudeTransform;
	_patLight2 = new PositionAttitudeTransform;

//void createLight(int lightNum, PositionAttitudeTransform *patLight, StateSet *ss, Vec3d position, 
//			Vec3d ambient, Vec3d diffuse, Vec3d specular) {

	createLight(0, _patLight1.get(), ss, Vec3d(0.0,-2.5,3.0),
			Vec3d(0.0,0.0,0.0), Vec3d(0.2,0.8,0.1), Vec3d(0.2,0.8,0.1));
	createLight(1, _patLight2.get(), ss, Vec3d(0.0,2.5,0.0),
			Vec3d(0.0,0.0,0.0), Vec3d(0.7,0.1,0.1), Vec3d(0.7,0.1,0.1));
	
	isIlluminated = false;
}

IlluminatedModel::IlluminatedModel(Node* model,  StateSet *ss) : Model::Model(model) {
        
}

IlluminatedModel::~IlluminatedModel() {
}

void IlluminatedModel::toggleLights() {

	if(isIlluminated) {
	
		_group->removeChild(_patLight1.get());
		_group->removeChild(_patLight2.get());
	} else {
	
		_group->addChild(_patLight1.get());
		_group->addChild(_patLight2.get());
	}

	isIlluminated = !isIlluminated;
}

void IlluminatedModel::rotateLights() {
	Quat rotate1( DegreesToRadians(0.5), Vec3d(1.0, 1.0, 0.0) );
	Quat rotate2( DegreesToRadians(0.3), Vec3d(0.0, 1.0, 1.0) );
	_patLight1->setAttitude(_patLight1->getAttitude() * rotate1);
	_patLight2->setAttitude(_patLight2->getAttitude() * rotate2);
}

void IlluminatedModel::createLight(int lightNum, PositionAttitudeTransform *patLight, StateSet *ss, Vec3d position, 
			Vec3d ambient, Vec3d diffuse, Vec3d specular) {

	ref_ptr<Group> lightGroup = new Group;

        ref_ptr<StateSet> lightSS (ss);
	ref_ptr<LightSource> lightSource = new LightSource;
	ref_ptr<Light> light = new Light;
	
        Vec4d lightPosition (Vec4d(position,1.0));
	light->setLightNum(lightNum);
	light->setPosition(lightPosition);
	light->setAmbient(Vec4(ambient,1.0));
	light->setDiffuse(Vec4(diffuse,1.0));
	light->setSpecular(Vec4(specular,1.0));
	light->setConstantAttenuation(1.0);
//	light->setSpotCutoff(80.0); 
	
	lightSource->setLight(light.get());
	lightSource->setLocalStateSetModes(StateAttribute::ON);
	lightSource->setStateSetModes(*lightSS,StateAttribute::ON);

	ref_ptr<Geode> lightMarkerGeode (new Geode);
	lightMarkerGeode->addDrawable(new ShapeDrawable(new Sphere(position,0.1)));

	lightGroup->addChild(lightSource.get());	
	lightGroup->addChild(lightMarkerGeode.get());
	
	patLight->addChild(lightGroup.get());
}
