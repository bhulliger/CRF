#include "Spacewarp.h"

osg::Node* Spacewarp::createSpacewarp(unsigned int noStars, float distance)
{
    
    osg::Geometry* geometry = new osg::Geometry;
    
    // set up vertices
    osg::Vec3Array* vertices = new osg::Vec3Array(noStars*2);
    geometry->setVertexArray(vertices);
    
    float min = -distance;
    float max = distance;
    unsigned int j = 0;
    unsigned int i = 0;
    for(i=0;i<noStars;++i,j+=2)
    {
        (*vertices)[j].set(random(min,max),random(min,max),random(min,max));
        (*vertices)[j+1] = (*vertices)[j]+osg::Vec3(0.0f,0.0f,0.001f);
    }    

    // set up colours
    osg::Vec4Array* colours = new osg::Vec4Array(1);
    geometry->setColorArray(colours);
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    (*colours)[0].set(1.0f,1.0f,1.0f,1.0f);

    // set up the primitive set to draw lines
    geometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,noStars*2));

    // set up the points for the stars.
    osg::DrawElementsUShort* points = new osg::DrawElementsUShort(GL_POINTS,noStars);
    geometry->addPrimitiveSet(points);
    for(i=0;i<noStars;++i)
    {
        (*points)[i] = i*2;
    }

    geometry->setUseDisplayList(false);
    geometry->setDrawCallback(new DrawCallback);
    
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable(geometry);
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    osg::Group* group = new osg::Group;
    group->addChild(geode);        
    
    return group;
}
