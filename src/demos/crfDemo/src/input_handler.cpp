#include "input_handler.h"

InputHandler::InputHandler(Movable::Movable& movable) :
    _movable(&movable)
{
    
}

bool InputHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
    switch(ea.getEventType()) {
        case(osgGA::GUIEventAdapter::KEYDOWN): {
            switch(ea.getKey()) {
                case osgGA::GUIEventAdapter::KEY_Left:
                    _movable->rotate_z(1.0);
                    std::cout << "left arrow key pressed" << std::endl;
                    return false;
                    break;
                case osgGA::GUIEventAdapter::KEY_Right:
                    _movable->rotate_z(-1.0);
                    std::cout << "right arrow key pressed" << std::endl;
                    return false;
                    break;
                case osgGA::GUIEventAdapter::KEY_Up:
                    _movable->rotate_x(1.0);
                    std::cout << "upper arrow key pressed" << std::endl;
                    return false;
                    break;
                case osgGA::GUIEventAdapter::KEY_Down:
                    _movable->rotate_x(-1.0);
                    std::cout << "lower arrow key pressed" << std::endl;
                    return false;
                    break;
                case 'q':
                    _movable->translate_z(-1.0);
                    std::cout << "q key pressed" << std::endl;
                    return false;
                    break;
                case 'a':
                    _movable->translate_z(-1.0);
                    std::cout << "a key pressed" << std::endl;
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
