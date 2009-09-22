/*
 *  Filename: 		main.cpp
 *  Project:		crfStressTest
 *  Author:		Stefan Broder (brods1@bfh.ch)
 *  Creation Date:	29.05.2009
 *  Purpose:		Main program for stress test
 *
 */

#include <crf/crfPipe.h>
#include <crf/crfNodeFactory.h>
#include <crf/crfStarter.h>
#include <crf/Util.h>

#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>

#include "Scenegraph.h"
#include "KeyboardHandler.h"

#include <iostream>

using namespace osg;
using namespace std;

namespace crfStressTest {
	
	// defining pipe class, inherited form crfPipe
	class Pipe : public crf::crfPipe {
		public:
			Pipe(eq::Node* parent) : crf::crfPipe(parent){
				_sceneGraphCreated=false;
			}
			~Pipe();

		protected:
			// the two vital methods
			void createSceneGraph();
			void updateSceneGraph();

			Scenegraph::Scenegraph* _sg;
			osg::ref_ptr<osgViewer::StatsHandler> _stats;
		 
	};

	class NodeFactory : public crf::crfNodeFactory {
		protected:
			virtual eq::Pipe* createPipe(eq::Node *parent){
				return new crfStressTest::Pipe(parent);		
			}
	};

}

crfStressTest::Pipe::~Pipe() {
	delete _sg;
}

int main(int argc, char** argv) {

	cout << "Press 'r' to toggle rotation" << endl;
	cout << "Press 'i' to toggle illumination" << endl;
	cout << "Press '1' - '4' to load models (1:bunny, 2:armadillo, 3:buddha, 4:dragon)" << endl;

	//create the demo factory
	crfStressTest::NodeFactory* fac = new crfStressTest::NodeFactory();
	
	//create the CRF starter
	crf::crfStarter starter;

	//pass the factory to the starter
	starter.setNodeFactory(fac);

	//run the application
	starter.run(argc,argv);
}

void crfStressTest::Pipe::updateSceneGraph(){
	
	_sg->updateScenegraph();
}

void crfStressTest::Pipe::createSceneGraph(){
  
	_sg = new Scenegraph::Scenegraph;
	// default model to load
	// (has to be in environment or in same path like executable)
	std::string filename = "bunny.osg";
	Node *root = _sg->createScenegraph(filename);

	// add scene data to viewer
	_viewer->setSceneData(root);
  
  	// osg stats
	_stats = new osgViewer::StatsHandler();
	_stats->setKeyEventTogglesOnScreenStats(osgGA::GUIEventAdapter::KEY_F2);
	_viewer->addEventHandler(_stats.get());

	// keyboard handler
	ref_ptr<KeyboardHandler> kbh = new KeyboardHandler(_sg);
	_viewer->addEventHandler(kbh.get());
}
