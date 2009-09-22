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

#include "Universe.h"
#include "Spacewarp.h"

#include <iostream>

using namespace osg;
using namespace std;

//1. Step
///to avoid conflicts with naming, create a own namespace for the concrete demo
namespace crfDemoApp {

	//2. Step
	///We wanna have full control over the scene graph and frame-related updates
	///so we create our own pipe by inheriting from the crfPipe
	class Pipe : public crf::crfPipe {
		public:
			///Our own constructor calls the crfPipe constructor and sets 
			///the universe-pointer to zero
			Pipe(eq::Node* parent) : crf::crfPipe(parent){
				uv =0;
				_sceneGraphCreated=false;
			}
		protected:
			///Our own method to create the scene graph
			void createSceneGraph();

			///Our update function, called everyframe by the crfPipe base classe
			void updateSceneGraph();
		private:
		/// the universe
		 Universe* uv;
	};


	//3. Step
	///Create a custom-nodefactory to create our own custom pipe-object
	class NodeFactory : public crf::crfNodeFactory {
		protected:
			virtual eq::Pipe* createPipe(eq::Node *parent){
				return new crfDemoApp::Pipe(parent);		
			}
	};

}

//4. Create the main method, which calls the crfStart.run() method to start equalizer and stuff
int main(int argc, char** argv) 
{
	//create the demo factory
	crfDemoApp::NodeFactory* fac = new crfDemoApp::NodeFactory();
    //create the CRF starter
	crf::crfStarter starter;
	
	//pass the factory to the starter
	starter.setNodeFactory(fac);

	//run the application
	starter.run(argc,argv);
}

//this function is called every frame in every pipe
void crfDemoApp::Pipe::updateSceneGraph(){
	//call the univers' update function		
	uv->update(_viewer->elapsedTime());
}

//this function is called one time on the initalisation of every pipe
void crfDemoApp::Pipe::createSceneGraph(){
  
	// default: spacewarp on, starfield off
    uv = new Universe();
  
	osg::Node* universe = uv->createUniverse();
    
    Group* root_node = new Group;
    root_node->addChild(universe);
	_viewer = new eqOsg::EqViewer();	    	
	
	_viewer->setSceneData(correctCoordsys(root_node));   	

	Camera* camera = _viewer->getCamera();    	
	
	// set background color to black. fits better in space!   	
	camera->setClearColor(osg::Vec4(0.0, 0.0, 0.0, 0.0));  	

	_sceneGraphCreated = true;	}
