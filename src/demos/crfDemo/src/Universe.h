/*
 *  Universe.h
 *  crfDemo
 *
 *  Created by brige on 5/15/09.
 *  Copyright 2009 BFH TI. All rights reserved.
 *
 */

#include <osg/Light>
#include <osg/LightSource>
#include <iostream>

#include "CrfGeometry.h"

using namespace osg;

class Universe {
public:
        Universe();
        Universe(int distance, int scale, bool spacewarp_enabled, 
                bool starfield_enabled);
        ~Universe();
	Node* createUniverse();
	void update(double time);
        
        // getters & setters
        void setDiamter(int diameter) { _diameter = diameter; };
        int getDiameter() { return _diameter; };
        
        void setAmountStars(int amount_stars) { _amount_stars = amount_stars; };
        int getAmountStars() { return _amount_stars; };
        
        void toggleSpacewarp() { _spacewarp_enabled = !(_spacewarp_enabled); };
        int getSpacewarpEnabled() { return _spacewarp_enabled; };
        
        void toggleStarfield() { _starfield_enabled = !(_starfield_enabled); };
        int getStarfieldEnabled() { return _starfield_enabled; };
        
private:
	PositionAttitudeTransform *starField[6];
	PositionAttitudeTransform *lightTransform;
	StateSet *lightStateSet;
	PositionAttitudeTransform* sun;
	PositionAttitudeTransform* mercury;
	PositionAttitudeTransform* venus;
	PositionAttitudeTransform* earth;
	PositionAttitudeTransform* emoon;
	PositionAttitudeTransform* mars;
	PositionAttitudeTransform* jupiter;
	PositionAttitudeTransform* saturn;
	PositionAttitudeTransform* uranus;
	PositionAttitudeTransform* neptun;
	PositionAttitudeTransform* pluto;
	
	void positionStarField();
	Light* createLight(Vec4 color);
        Node* createSpacewarp();
        
        int _diameter;
        int _amount_stars;
        
        bool _spacewarp_enabled;
        bool _starfield_enabled;
};

