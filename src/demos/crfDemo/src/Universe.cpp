/*
 *  Universe.cpp
 *  crfDemo
 *
 *  Created by brige on 5/15/09.
 *  Copyright 2009 BFH TI. All rights reserved.
 *
 */

#include "Universe.h"
#include "Spacewarp.h"

int uniqueLightNumber = 0;

// default constructor
Universe::Universe() : 
    _diameter(20000), 
    _amount_stars(_diameter/2),
    _spacewarp_enabled(true),
    _starfield_enabled(false)
{}

// full constructor
Universe::Universe(int diameter, int amount_stars, 
        bool spacewarp_enabled, bool starfield_enabled) : 
    _diameter(diameter), 
    _amount_stars(amount_stars),
    _spacewarp_enabled(spacewarp_enabled),
    _starfield_enabled(starfield_enabled)
{}

/**
 * Creates a box with stars... the universe seems to be finite after all ;-)
 */
void Universe::positionStarField() {
     
            Quat rotate;
	
            // top 
            starField[0]->setPosition(Vec3(0, 0, _diameter));
//            starField[0]->setScale(Vec3(_scale, _scale, 0));

            // bottom
            starField[1]->setPosition(Vec3(0, 0, -_diameter));
//            starField[1]->setScale(Vec3(_scale, _scale, 0));

            // left
            rotate.makeRotate( DegreesToRadians(90.0), 0, 1, 0);
            starField[2]->setAttitude(rotate);
            starField[2]->setPosition(Vec3(-_diameter, 0, 0));
//            starField[2]->setScale(Vec3(_scale, _scale, 0));

            // right
            rotate.makeRotate( DegreesToRadians(90.0), 0, 1, 0);
            starField[3]->setAttitude(rotate);
            starField[3]->setPosition(Vec3(_diameter, 0, 0));
//            starField[3]->setScale(Vec3(_scale, _scale, 0));

            // front
            rotate.makeRotate( DegreesToRadians(90.0), 1, 0, 0);
            starField[4]->setAttitude(rotate);
            starField[4]->setPosition(Vec3(0, -_diameter, 0));
//            starField[4]->setScale(Vec3(_scale, _scale, 0));

            // back
            rotate.makeRotate( DegreesToRadians(90.0), 1, 0, 0);
            starField[5]->setAttitude(rotate);
            starField[5]->setPosition(Vec3(0, _diameter, 0));
//            starField[5]->setScale(Vec3(_scale, _scale, 0));
}

/**
 * create a space warp. points in space that look like star trek.
 */
Node* Universe::createSpacewarp() {
    return Spacewarp().createSpacewarp(_amount_stars, _diameter);
}

Node* Universe::createUniverse() {
	// we need the scene's state set to enable the light for the entire scene
	Group *scene = new Group();
	lightStateSet = scene->getOrCreateStateSet();
	lightStateSet->ref();
	
	// create a light
	LightSource *lightSource = new LightSource();
	lightSource->setLight(createLight(Vec4(0.9, 0.9, 0.9, 1.0)));
	// enable the light for the entire scene
	lightSource->setLocalStateSetModes(StateAttribute::ON);
	lightSource->setStateSetModes(*lightStateSet, StateAttribute::ON);
	
	lightTransform = new PositionAttitudeTransform();
	lightTransform->addChild(lightSource);
	lightTransform->setPosition(Vec3(3, 0, 0));
	
	// create objects
	try {
		CrfGeometry* crfGeometry = new CrfGeometry();
		
               
                    // Stars
                    Material *material = new Material();
                    material->setEmission(Material::FRONT, Vec4(1.0, 1.0, 1.0, 1.0));
                    material->setAmbient(Material::FRONT,  Vec4(1.0, 1.0, 1.0, 1.0));
                    material->setShininess(Material::FRONT, 25.0);

                    crfGeometry->prepareMaterial(material);
                
                if(_starfield_enabled) {
                    for (int i = 0; i < 6; i++) {
                            starField[i] = crfGeometry->createPlane(_diameter, "./textures/stars.jpg", true);
                            scene->addChild(starField[i]);
                    }
                    
                    this->positionStarField();
                }
                
                if(_spacewarp_enabled) 
                    scene->addChild(this->createSpacewarp());
                    
		// sun
		crfGeometry->prepareMaterial(material);
		sun = crfGeometry->createSphere(300, "./textures/sunmap.jpg", false);
		
		// planets
		Material *material2 = new Material();
		material2->setEmission(Material::FRONT, Vec4(0.1, 0.1, 0.1, 1.0));
		crfGeometry->prepareMaterial(material2);
		mercury= crfGeometry->createSphere(3.8, "./textures/mercurymap.jpg", false);
		venus = crfGeometry->createSphere(9.5, "./textures/venusmap.jpg", false);
		earth = crfGeometry->createSphere(10, "./textures/earthmap1k.jpg", false);
		emoon = crfGeometry->createSphere(2, "./textures/moonmap1k.jpg", false);
		mars = crfGeometry->createSphere(5.3, "./textures/mars_1k_color.jpg", false);
		jupiter = crfGeometry->createSphere(109, "./textures/jupitermap.jpg", false);
		saturn = crfGeometry->createSphere(91, "./textures/saturnmap.jpg", false);
	} catch (char *e) {
		std::cerr << e;
	}
        
        
	
	lightTransform->addChild(sun);
	scene->addChild(lightTransform);
	scene->addChild(mercury);
	scene->addChild(venus);
	earth->addChild(emoon);
	scene->addChild(earth);
	scene->addChild(mars);
	scene->addChild(jupiter);
	scene->addChild(saturn);
	
	return scene;
}

Light* Universe::createLight(Vec4 color)
{	
	Light *light = new Light();
	// each light must have a unique number
	light->setLightNum(uniqueLightNumber++);
	// we set the light's position via a PositionAttitudeTransform object
	light->setPosition(Vec4(0.0, 0.0, 0.0, 1.0));
	light->setDiffuse(color);
	light->setSpecular(Vec4(1.0, 1.0, 1.0, 1.0));
	light->setAmbient( Vec4(0.0, 0.0, 0.0, 1.0));
	
	return light;
}

/*
AnimationPath* Universe::createAnimationPath(const Vec3& center, float radius, double looptime) {
	
	AnimationPath* animationPath = new AnimationPath;
	animationPath->setLoopMode(AnimationPath::LOOP);
	
	int numSamples = 40;
	float yaw = 0.0f;
	float yaw_delta = 2.0f * PI / ((float) numSamples - 1.0f);
	float roll = inDegrees(30.0f);
	
	double time = 0.0f;
	double time_delta = loopTime / (double) numSamples;
	for (int i = 0; i < numSamples; ++i ) {
		Vec3 position(center + Vec3(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f));
		Quat rotation(Quat(roll, Vec3(0.0,1.0,0.0)) * Quat(-(yaw+inDegrees(90.0f)), Vec3(0.0,0.0,1.0)));
		animationPath->insert(time, AnimationPath::ControlPoint(position, ratation));
		
		yaw+= yaw_delta;
		time += time_delta;
	}
	return animationPath;
	
}*/

void Universe::update(double time) {
	
	const float ANIMATION_SPEED = 10.0;
	time *= ANIMATION_SPEED;
	const float SUN_DISTANCE = 1500;
	const float BASE_PERIOD = -time / 50;
	const float BASE_ROTATION = time / 2;
	Quat rotate;
	
	rotate.makeRotate(-time/100, 0, 0, 1);
	sun->setAttitude(rotate);
	
	rotate.makeRotate(BASE_ROTATION / 58, 0, 0, 1);
	mercury->setAttitude(rotate);
	mercury->setPosition(Vec3(sin(BASE_PERIOD / 0.24), cos(BASE_PERIOD / 0.24), 0) * SUN_DISTANCE * 0.38);
	
	rotate.makeRotate(BASE_ROTATION / -243, 0, 0, 1);
	venus->setAttitude(rotate);
	venus->setPosition(Vec3(sin(BASE_PERIOD / 0.61), cos(BASE_PERIOD / 0.61), 0) * SUN_DISTANCE * 0.72);
	
	rotate.makeRotate(BASE_ROTATION, 0, 0, 1);
	earth->setAttitude(rotate);
	earth->setPosition(Vec3(sin(BASE_PERIOD), cos(BASE_PERIOD), 0) * SUN_DISTANCE);
	emoon->setPosition(Vec3(-sin(time), cos(time), 0) * 20);
	
	rotate.makeRotate(BASE_ROTATION / 1.02, 0, 0, 1);
	mars->setAttitude(rotate);
	mars->setPosition(Vec3(sin(BASE_PERIOD / 1.88), cos(BASE_PERIOD / 1.88), 0) * SUN_DISTANCE * 1.52);
	
	rotate.makeRotate(BASE_ROTATION / 0.41, 0, 0, 1);
	jupiter->setAttitude(rotate);
	jupiter->setPosition(Vec3(sin(BASE_PERIOD / 11.86), cos(BASE_PERIOD / 11.86), 0) * SUN_DISTANCE * 5.20);
	
	rotate.makeRotate(BASE_ROTATION / 0.44, 0, 0, 1);
	saturn->setAttitude(rotate);
	saturn->setPosition(Vec3(sin(BASE_PERIOD / 29.44), cos(BASE_PERIOD / 29.44), 0) * SUN_DISTANCE * 9.53);
}
