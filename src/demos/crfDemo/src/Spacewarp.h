// 
// File:   Spacewarp.h
// Author: stefan
//
// Created on May 16, 2009, 4:04 PM
//

#ifndef _SPACEWARP_H
#define	_SPACEWARP_H

#include <osg/Group>
#include <osg/Geometry>

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>

class Spacewarp {

public:
    osg::Node* createSpacewarp(unsigned int noStars, float distance);
    
private:
    float random(float min,float max) { return min + (max-min)*(float)rand()/(float)RAND_MAX; };
    
};

struct DrawCallback : public osg::Drawable::DrawCallback
{

    DrawCallback():
        _firstTime(true) {}

    virtual void drawImplementation(osg::RenderInfo& renderInfo,const osg::Drawable* drawable) const
    {
        osg::State& state = *renderInfo.getState();
    
        if (!_firstTime)
        {
            _previousModelViewMatrix = _currentModelViewMatrix;
            _currentModelViewMatrix = state.getModelViewMatrix();
            _inverseModelViewMatrix.invert(_currentModelViewMatrix);
            
            osg::Matrix T(_previousModelViewMatrix*_inverseModelViewMatrix);

            osg::Geometry* geometry = dynamic_cast<osg::Geometry*>(const_cast<osg::Drawable*>(drawable));
            osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>(geometry->getVertexArray());
            for(unsigned int i=0;i+1<vertices->size();i+=2)
            {
                (*vertices)[i+1] = (*vertices)[i]*T;
            }
        }
        else
        {
            _currentModelViewMatrix = state.getModelViewMatrix();
        }
                
        _firstTime = false;

        drawable->drawImplementation(renderInfo);
    }
    
    mutable bool _firstTime;
    mutable osg::Matrix _currentModelViewMatrix;
    mutable osg::Matrix _inverseModelViewMatrix;
    mutable osg::Matrix _previousModelViewMatrix;
};

#endif	/* _SPACEWARP_H */

