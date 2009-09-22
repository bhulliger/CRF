#include <crf/crfPipe.h>
#include <crf/crfNodeFactory.h>
#include <crf/crfStarter.h>

#include "keyboard.h"

using namespace osg;
using namespace std;

///////////////////////////////////////////////////////////////////////////
//1. Step
///to avoid conflicts with naming, create a own namespace for the concrete demo
namespace crfDemoApp {

	//2. Step
	///We wanna have full control over the scene graph and frame-related updates
	///so we create our own pipe by inheriting from the crfPipe
	class Pipe : public crf::crfPipe {
		public:
			///Our own constructor calls the crfPipe constructor and sets 
			Pipe(eq::Node* parent) : crf::crfPipe(parent){
				_sceneGraphCreated=false;
			}
		protected:
			///Our own method to create the scene graph
			void createSceneGraph();
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

//this function is called one time on the initalisation of every pipe
void crfDemoApp::Pipe::createSceneGraph(){
     
	osg::ref_ptr<keyboard::KeyboardModel> keyboardModel = new keyboard::KeyboardModel;

	_viewer->addEventHandler(new keyboard::KeyboardEventHandler(keyboardModel.get()));    _viewer->setSceneData( correctCoordsys(keyboardModel->getScene()));
	_sceneGraphCreated=true;
}
