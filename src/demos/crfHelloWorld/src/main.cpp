#include <crf/crfStarter.h>

#include <osgDB/ReadFile>
#include <osg/Node>
#include <crf/SceneReader.h>


//1. Create the main method, which calls the crfStart.run() method to start Equalizer and stuff
int main(int argc, char** argv) 
{
    ///create the CRF starter
	crf::crfStarter starter;
	
	std::string model;
	std::string mode;

	model = starter.parseCommandLineForString(argc,argv, "--model=");
	mode = starter.parseCommandLineForString(argc,argv, "--mode=");
	std::cout << model << " --------------------- " << mode << std::endl;
	// if a valid model has been passed, try to load it
	// if mode is set to "pipesafe" the model is loaded only once!
	if (model.size()>0 && mode.compare("pipesafe")==0)	{ 
		
		osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(model);


		///if node loaded
		if (node.valid()) {
			//run the application with a given node (the model is loaded only once to avoid
			//memory abuse on multipipe machines, but therefore shared)!
			//this works well on multipipe machines too, if this node is static
			starter.run(argc,argv,node);
			std::cout<< "Run with model: " << model << " and mode: " << mode << std::endl;
		}
		else{
			starter.run(argc,argv);
			std::cout<< "Run with model: " << model << " and no node" << std::endl;
		}
	}
	else{
		starter.run(argc,argv);
		std::cout<< "Run with model: " << model << " and std mode" << std::endl;
	}
}
