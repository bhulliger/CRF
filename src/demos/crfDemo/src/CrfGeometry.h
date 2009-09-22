/*
 *  CrfGeometry.h
 *  crfDemo
 *
 *  Created by brige on 5/15/09.
 *  Copyright 2009 BFH TI. All rights reserved.
 *
 */

#include <osg/Material>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Texture2D>
#include <osg/TexMat>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

using namespace osg;
using namespace std;

class CrfGeometry {
public:
	CrfGeometry();
	void prepareMaterial( Material* material );

	PositionAttitudeTransform* createSphere(float size, string texName, bool texRepeat);
	PositionAttitudeTransform* createPlane(float size, string texName, bool texRepeat);
private:
	Material* material;
	Texture2D* createTexture(string texName, bool texRepeat);	
	void clearMaterial();
	
};

