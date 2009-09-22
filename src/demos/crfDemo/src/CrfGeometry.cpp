/*
 *  CrfGeometry.cpp
 *  crfDemo
 *
 *  Created by brige on 5/15/09.
 *  Copyright 2009 BFH TI. All rights reserved.
 *
 */

#include "CrfGeometry.h"

CrfGeometry::CrfGeometry() {
	clearMaterial();
}

/**
 * clears the material properties
 */
void CrfGeometry::clearMaterial() {
	this->material = new Material();
}

/**
 * initlaizes a new material
 */
void CrfGeometry::prepareMaterial(Material* newMaterial) {
	this->material = newMaterial;
}

/**
 * Create a texture with the given picture 
 */
Texture2D* CrfGeometry::createTexture(string texName, bool texRepeat) {
	// load texture file
	Image *image = osgDB::readImageFile(texName);
	if (!image) {
		throw "Couldn't load texture.";
	}
	
	// create texture
	Texture2D *texture = new Texture2D;
	texture->setDataVariance(Object::DYNAMIC);
	texture->setFilter(Texture::MIN_FILTER, Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(Texture::MAG_FILTER, Texture::LINEAR);
	
	// handle repeat
	if (texRepeat) {
		texture->setWrap(Texture::WRAP_S, Texture::REPEAT);
		texture->setWrap(Texture::WRAP_T, Texture::REPEAT);
	} else {
		texture->setWrap(Texture::WRAP_S, Texture::CLAMP);
		texture->setWrap(Texture::WRAP_T, Texture::CLAMP);
	}
	texture->setImage(image);
	
	return texture;	
}

/**
 * create a sphere with the given texture
 */
PositionAttitudeTransform* CrfGeometry::createSphere(float size, string texName, bool texRepeat) {
	Geode *sphere = new Geode();
	sphere->addDrawable(new ShapeDrawable(new Sphere(Vec3(0, 0, 4), size)));
	
	// assign the material to the sphere
	StateSet *sphereStateSet = sphere->getOrCreateStateSet();
	sphereStateSet->ref();
	sphereStateSet->setAttribute(material);
	
	if (texName.length() > 0) {
		try {
			sphereStateSet->setTextureAttributeAndModes(0, createTexture(texName, texRepeat), StateAttribute::ON);
		} catch (char *e) {
			throw e;
		}
	}
	
	PositionAttitudeTransform *sphereTransform = new PositionAttitudeTransform();
	sphereTransform->addChild(sphere);
	return sphereTransform;
}

/**
 * creates a plane with a given texture and a given size
 */
PositionAttitudeTransform* CrfGeometry::createPlane(float size, string texName, bool texRepeat) {
	// vertex array
	Vec3Array *vertexArray = new Vec3Array();
	
	vertexArray->push_back(Vec3(-size, -size, 0));
	vertexArray->push_back(Vec3(size, -size, 0));
	vertexArray->push_back(Vec3(size, size, 0));
	vertexArray->push_back(Vec3(-size, size, 0));
	
	// face array
	DrawElementsUInt *faceArray = new DrawElementsUInt(PrimitiveSet::TRIANGLES, 0);
	
	faceArray->push_back(0); // face 1
	faceArray->push_back(1);
	faceArray->push_back(2);
	faceArray->push_back(2); // face 2
	faceArray->push_back(3);
	faceArray->push_back(0);
	
	// normal array
	Vec3Array *normalArray = new Vec3Array();
	normalArray->push_back(Vec3(0, 0, 1));
	
	// normal index
	TemplateIndexArray<unsigned int, Array::UIntArrayType, 24, 4> *normalIndexArray;
	normalIndexArray = new TemplateIndexArray<unsigned int, Array::UIntArrayType, 24, 4>();
	
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);
	
	// texture coordinates
	osg::Vec2Array *texCoords = new osg::Vec2Array();
	texCoords->push_back(Vec2(0.0, 0.0));
	texCoords->push_back(Vec2(4.0, 0.0));
	texCoords->push_back(Vec2(4.0, 4.0));
	texCoords->push_back(Vec2(0.0, 4.0));
	
	Geometry *geometry = new Geometry();
	geometry->setVertexArray(vertexArray);
	geometry->setNormalArray(normalArray);
	geometry->setNormalIndices(normalIndexArray);
	geometry->setNormalBinding(Geometry::BIND_PER_VERTEX);
	geometry->setTexCoordArray(0, texCoords);
	geometry->addPrimitiveSet(faceArray);
	
	Geode *plane = new Geode();
	plane->addDrawable(geometry);
	
	// assign the material to the sphere
	StateSet *planeStateSet = plane->getOrCreateStateSet();
	planeStateSet->ref();
	planeStateSet->setAttribute(material);
	
	if (texName.length() > 0) {
		try {
			planeStateSet->setTextureAttributeAndModes(0, createTexture(texName, texRepeat), StateAttribute::ON);
		} catch (char *e) {
			throw e;
		}
	}
	
	PositionAttitudeTransform *planeTransform = new PositionAttitudeTransform();
	planeTransform->addChild(plane);
	return planeTransform;
}

