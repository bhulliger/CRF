#include <iostream>
#include <osgGA/GUIEventHandler>

#include "movable.h"

class InputHandler : public osgGA::GUIEventHandler {
public:
    InputHandler(Movable::Movable& movable); 
    
    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&);
    virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
    
private:
    Movable::Movable * _movable;
};
