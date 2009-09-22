
#ifndef _KEYBOARDHANDLER
#define _KEYBOARDHANDLER

#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>

#include <iostream>
#include <string>

#include "Scenegraph.h"

class KeyboardHandler : public osgGA::GUIEventHandler
{
	public:
		// con-/destructor
		// constructor takes a scene graph pointer to manipulate the
		// scene graph when pressing keys.
		KeyboardHandler(Scenegraph::Scenegraph *sg);
		~KeyboardHandler() {};

		// handle key events
		// 1-4: loading models
		// r: start/stop rotation
		// i: start/stop illumination
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
		// unused so far
		virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };

	private:
		// instance vars
		Scenegraph::Scenegraph *_sg;
		// model <-> key association
		std::string _key1;
		std::string _key2;
		std::string _key3;
		std::string _key4;
};

#endif

