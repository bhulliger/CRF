
#include "KeyboardHandler.h"

using namespace osg;
using namespace std;

//KeyboardHandler::KeyboardHandler(Scenegraph::Scenegraph *sg) : _sg = sg {
KeyboardHandler::KeyboardHandler(Scenegraph::Scenegraph *sg) {
	_sg = sg;
	_key1 = "bunny.osg";
	_key2 = "armadillo.osg";
	_key3 = "buddha.osg";
	_key4 = "dragon.osg";
}

bool KeyboardHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa) {
   switch(ea.getEventType())
   {
   	case(osgGA::GUIEventAdapter::KEYDOWN):
   	{
         	switch(ea.getKey())
         	{
         		case 'r':
            			std::cout << "Toggled rotation" << std::endl;
				_sg->toggleRotation();
            			return false;
            			break;
         		case 'i':
            			std::cout << "Toggled illumination" << std::endl;
				_sg->toggleIllumination();
            			return false;
            			break;
         		case '1':
            			cout << "Loading " << _key1 << " ... ";
				_sg->loadModel(_key1);
				cout << "done!" << endl;
            			return false;
            			break;
         		case '2':
            			cout << "Loading " << _key2 << " ... ";
				_sg->loadModel(_key2);
				cout << "done!" << endl;
            			return false;
            			break;
         		case '3':
            			cout << "Loading " << _key3 << " ... ";
				_sg->loadModel(_key3);
				cout << "done!" << endl;
            			return false;
            			break;
         		case '4':
            			cout << "Loading " << _key4 << " ... ";
				_sg->loadModel(_key4);
				cout << "done!" << endl;
            			return false;
            			break;
         		default:
            			return false;
         	} 
      	}
   	default:
      		return false;
   }
}

