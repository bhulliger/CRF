/*
 *  Filename: 		Model.cpp
 *  Project:		crfStressTest
 *  Author:		Stefan Broder (brods1@bfh.ch)
 *  Creation Date:	01.06.2009
 *  Purpose:		Container class for a model
 *
 */

#include "Model.h"

using namespace osg;
using namespace std;

Model::Model(std::string filename) {
        
	_model = osgDB::readNodeFile(filename);
	_group = new Group;
	_pat = new PositionAttitudeTransform;
	
	if(_model!=NULL) {
		_pat->addChild(_model.get());
		_group->addChild(_pat.get());
	} else {
		cerr<< "Could not load model! File " << filename << " not found." << endl;
	}
}

Model::Model(Node* model) {
        
	_model = model;
	ref_ptr<Group> _group = new Group;
	ref_ptr<PositionAttitudeTransform> _pat = new PositionAttitudeTransform;
	_pat->addChild(_model.get());
	_group->addChild(_pat.get());
}

Model::~Model() {
}

void Model::rotate_x(double angle) {
	_pat->setAttitude( 
		Quat( osg::DegreesToRadians(angle), osg::Vec3d(1.0, 0.0, 0.0) )
	);
}

void Model::rotate_y(double angle) {
	_pat->setAttitude( 
		Quat( osg::DegreesToRadians(angle), osg::Vec3d(0.0, 1.0, 0.0) )
	);
}

void Model::rotate_z(double angle) {
	_pat->setAttitude( 
		Quat( osg::DegreesToRadians(angle), osg::Vec3d(0.0, 0.0, 1.0) )
	);
}

void Model::rotate_rel_x(double angle) {
	rotate_rel(angle, Vec3d(1.0, 0.0, 0.0));
}

void Model::rotate_rel_y(double angle) {
	rotate_rel(angle, Vec3d(0.0, 1.0, 0.0));
}

void Model::rotate_rel_z(double angle) {
	rotate_rel(angle, Vec3d(0.0, 0.0, 1.0));
}

void Model::rotate_rel(double angle, Vec3d axis) {
	// Multiplying actual quaternion with rotation quaternion
	_pat->setAttitude(_pat->getAttitude() * Quat(angle, axis));
}

void Model::setPosition(Vec3d transl) {
	if(_pat!=NULL)
		_pat->setPosition(transl);
	else
		cerr << "_pat is null" << endl;
}

void Model::setModel(Node *model) {
	_pat->removeChild(_model.get());
	_model = model;
	_pat->addChild(_model.get());
}

Group* Model::getModel() {
	return _group.get();
}
