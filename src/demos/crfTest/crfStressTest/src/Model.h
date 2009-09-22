/*
 *  Filename: 		Model.h
 *  Project:		crfStressTest
 *  Author:		Stefan Broder (brods1@bfh.ch)
 *  Creation Date:	01.062009
 *  Purpose:		Container class for a model
 *
 */

#ifndef _MODEL
#define _MODEL

#include <osg/Node>
#include <osg/Vec3d>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>

#include <iostream>
#include <string>

// container class for a model
class Model {
public:
	// con-/destructors
	// constructor takes either a string of the filename
	// to a model or a pointer to a model.
        Model(std::string filename);
        Model(osg::Node* model);
        ~Model();

	// change the model
	void setModel(osg::Node* model);
	// returns pointer to the model
	osg::Group* getModel();

	// absolute rotations of the model
	void rotate_x(double angle);
	void rotate_y(double angle);
	void rotate_z(double angle);

	// relative rotations from the actual angle of the model
	void rotate_rel_x(double angle);
	void rotate_rel_y(double angle);
	void rotate_rel_z(double angle);

	// set the position of the model
	void setPosition(osg::Vec3d transl);
        
protected:
	// instance vars
	osg::ref_ptr<osg::Node> _model;
	osg::ref_ptr<osg::Group> _group;
	osg::ref_ptr<osg::PositionAttitudeTransform> _pat;

	// called from rotate_rel_{x,y,z}
	void rotate_rel(double angle, osg::Vec3d axis);
	
};

#endif

