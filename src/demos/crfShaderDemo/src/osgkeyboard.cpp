/* OpenSceneGraph example, osgkeyboard.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*  THE SOFTWARE.
*/
#include "keyboard.h"

using namespace keyboard;

void KeyboardModel::keyChange(int key,int value)
{
    osg::notify(osg::INFO) << "key value change, code="<<std::hex << key << "\t value="<< value << std::dec  << std::endl;

    // toggle the keys graphical representation on or off via osg::Swithc
    KeyModelMap::iterator itr = _keyModelMap.find(key);
    if (itr!=_keyModelMap.end())
    {
        itr->second->setSingleChildOn(value);
    }
    
    if (value)
    {
        // when a key is pressed add the new data to the text field
        
        if (key>0 && key<256)
        {
            // just add ascii characters right now...
            _inputText->getText().push_back(key);
            _inputText->update();
        }
        else if (key==osgGA::GUIEventAdapter::KEY_Return)
        {
            _inputText->getText().push_back('\n');
            _inputText->update();
        }
        else if (key==osgGA::GUIEventAdapter::KEY_BackSpace || key==osgGA::GUIEventAdapter::KEY_Delete) 
        {
            if (!_inputText->getText().empty())
            {
                _inputText->getText().pop_back();
                _inputText->update();
            }
        }
        
    }
    
}

osg::Switch* KeyboardModel::addKey(osg::Vec3& pos, int key,const std::string& text,float width, float height)
{

    osg::Geode* geodeUp = new osg::Geode;
    {
        osgText::Text* textUp = new osgText::Text;
        textUp->setFont("fonts/arial.ttf");
        textUp->setColor(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
        textUp->setCharacterSize(height);
        textUp->setPosition(pos);
        textUp->setDrawMode(osgText::Text::TEXT/*|osgText::Text::BOUNDINGBOX*/);
        textUp->setAlignment(osgText::Text::LEFT_CENTER);
        textUp->setAxisAlignment(osgText::Text::XZ_PLANE);
        textUp->setText(text);
        
        geodeUp->addDrawable(textUp);
    }
    
    osg::Geode* geodeDown = new osg::Geode;
    {
        osgText::Text* textDown = new osgText::Text;
        textDown->setFont("fonts/arial.ttf");
        textDown->setColor(osg::Vec4(1.0f,0.0f,1.0f,1.0f));
        textDown->setCharacterSize(height);
        textDown->setPosition(pos);
        textDown->setDrawMode(osgText::Text::TEXT/*||osgText::Text::BOUNDINGBOX*/);
        textDown->setAlignment(osgText::Text::LEFT_CENTER);
        textDown->setAxisAlignment(osgText::Text::XZ_PLANE);
        textDown->setText(text);
        
        geodeDown->addDrawable(textDown);
    }

    osg::Switch* model = new osg::Switch;
    model->addChild(geodeUp,true);
    model->addChild(geodeDown,false);
    
    _scene->addChild(model);

    _keyModelMap[key] = model;
    
    pos.x() += width;
    
    return model;
    
}

osg::Switch* KeyboardModel::addKey(int key,osg::Switch* sw)
{
    _keyModelMap[key] = sw;
    return sw;
}

void KeyboardModel::createKeyboard()
{
    _scene = new osg::Group;
    
    osg::Vec3 origin(0.0f,0.0f,0.0f);
    osg::Vec3 pos=origin;
    
    addKey(pos,osgGA::GUIEventAdapter::KEY_Control_L,"Ctrl",2.0f,0.5f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Super_L,"Super",2.0f,0.5f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Alt_L,"Alt",2.0f,0.5f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Space,"Space",3.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Mode_switch,"Switch",2.0f,0.5f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Super_R,"Super",2.0f,0.5f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Menu,"Menu",2.0f,0.5f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Control_R,"Ctrl",2.0f,0.5f);

    osg::Vec3 middle(pos.x()+1.0f,0.0f,0.0f);
    
    pos.x() = 0.0f;
    pos.z() += 1.0f;

    addKey(pos,osgGA::GUIEventAdapter::KEY_Shift_L,"Shift",2.0f,0.5f);
    addKey(pos,'\\',"\\",1.0f,1.0f);
    addKey('Z',addKey(pos,'z',"Z",1.0f,1.0f));
    addKey('X',addKey(pos,'x',"X",1.0f,1.0f));
    addKey('C',addKey(pos,'c',"C",1.0f,1.0f));
    addKey('V',addKey(pos,'v',"V",1.0f,1.0f));
    addKey('B',addKey(pos,'b',"B",1.0f,1.0f));
    addKey('N',addKey(pos,'n',"N",1.0f,1.0f));
    addKey('M',addKey(pos,'m',"M",1.0f,1.0f));
    addKey('<',addKey(pos,',',",",1.0f,1.0f));
    addKey('>',addKey(pos,'.',".",1.0f,1.0f));
    addKey('?',addKey(pos,'/',"/",1.0f,1.0f));
    addKey(pos,osgGA::GUIEventAdapter::KEY_Shift_R,"Shift",2.0f,0.5f);

    pos.x() = 0.0f;
    pos.z() += 1.0f;
    
    addKey(pos,osgGA::GUIEventAdapter::KEY_Caps_Lock,"Caps",2.0f,0.5f);
    addKey('A',addKey(pos,'a',"A",1.0f,1.0f));
    addKey('S',addKey(pos,'s',"S",1.0f,1.0f));
    addKey('D',addKey(pos,'d',"D",1.0f,1.0f));
    addKey('F',addKey(pos,'f',"F",1.0f,1.0f));
    addKey('G',addKey(pos,'g',"G",1.0f,1.0f));
    addKey('H',addKey(pos,'h',"H",1.0f,1.0f));
    addKey('J',addKey(pos,'j',"J",1.0f,1.0f));
    addKey('K',addKey(pos,'k',"K",1.0f,1.0f));
    addKey('L',addKey(pos,'l',"L",1.0f,1.0f));
    addKey(':',addKey(pos,';',";",1.0f,1.0f));
    addKey('@',addKey(pos,'\'',"'",1.0f,1.0f));
    addKey('~',addKey(pos,'#',"#",1.0f,1.0f));
    addKey(pos,osgGA::GUIEventAdapter::KEY_Return,"Return",4.0f,0.5f);

    pos.x() = 0.0f;
    pos.z() += 1.0f;
    
    addKey(pos,osgGA::GUIEventAdapter::KEY_Tab,"Tab",2.0f,0.5f);
    addKey('Q',addKey(pos,'q',"Q",1.0f,1.0f));
    addKey('W',addKey(pos,'w',"W",1.0f,1.0f));
    addKey('E',addKey(pos,'e',"E",1.0f,1.0f));
    addKey('R',addKey(pos,'r',"R",1.0f,1.0f));
    addKey('T',addKey(pos,'t',"T",1.0f,1.0f));
    addKey('Y',addKey(pos,'y',"Y",1.0f,1.0f));
    addKey('U',addKey(pos,'u',"U",1.0f,1.0f));
    addKey('I',addKey(pos,'i',"I",1.0f,1.0f));
    addKey('O',addKey(pos,'o',"O",1.0f,1.0f));
    addKey('P',addKey(pos,'p',"P",1.0f,1.0f));
    addKey('{',addKey(pos,'[',"[",1.0f,1.0f));
    addKey('}',addKey(pos,']',"]",1.0f,1.0f));

    pos.x() = 0.0f;
    pos.z() += 1.0f;
    
    addKey(pos,'`',"`",1.0f,1.0f);
    addKey(pos,'1',"1",1.0f,1.0f);
    addKey(pos,'2',"2",1.0f,1.0f);
    addKey(pos,'3',"3",1.0f,1.0f);
    addKey(pos,'4',"4",1.0f,1.0f);
    addKey(pos,'5',"5",1.0f,1.0f);
    addKey(pos,'6',"6",1.0f,1.0f);
    addKey(pos,'7',"7",1.0f,1.0f);
    addKey(pos,'8',"8",1.0f,1.0f);
    addKey(pos,'9',"9",1.0f,1.0f);
    addKey(pos,'0',"0",1.0f,1.0f);
    addKey(pos,'-',"-",1.0f,1.0f);
    addKey(pos,'=',"=",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_BackSpace,"Backspace",3.0f,0.5f);

    pos.x() = 0.0f;
    pos.z() += 1.5f;
    
    float F_height = 0.5f;
    addKey(pos,osgGA::GUIEventAdapter::KEY_Escape,"Esc",2.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F1,"F1",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F2,"F2",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F3,"F3",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F4,"F4",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F5,"F5",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F6,"F6",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F7,"F7",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F8,"F8",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F9,"F9",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F10,"F10",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F11,"F11",1.0f,F_height);
    addKey(pos,osgGA::GUIEventAdapter::KEY_F12,"F12",1.0f,F_height);


    
    float cursorMoveHeight=0.35f;

    pos = middle;    
    addKey(pos,osgGA::GUIEventAdapter::KEY_Left,"Left",1.0f,cursorMoveHeight);
    osg::Vec3 down = pos;
    addKey(pos,osgGA::GUIEventAdapter::KEY_Down,"Down",1.0f,cursorMoveHeight);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Right,"Right",1.0f,cursorMoveHeight);
    
    osg::Vec3 keypad = pos;
    keypad.x()+=1.0f;

    pos = down;
    pos.z() += 1.0f;
    
    addKey(pos,osgGA::GUIEventAdapter::KEY_Up,"Up",1.0f,cursorMoveHeight);
    

    float homeHeight = 0.35f;
    pos = middle;
    pos.z() += 3.0;    
    addKey(pos,osgGA::GUIEventAdapter::KEY_Delete,"Delete",1.0f,homeHeight);
    addKey(pos,osgGA::GUIEventAdapter::KEY_End,"End",1.0f,homeHeight);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Page_Down,"Page\nDown",1.0f,homeHeight);
    
    pos = middle;
    pos.z() += 4.0;    
    addKey(pos,osgGA::GUIEventAdapter::KEY_Insert,"Insert",1.0f,homeHeight);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Home,"Home",1.0f,homeHeight);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Page_Up,"Page\nUp",1.0f,homeHeight);

    pos = middle;
    pos.z() += 5.5;    
    addKey(pos,osgGA::GUIEventAdapter::KEY_Print,"PrtScrn\nSysRq",1.0f,homeHeight);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Scroll_Lock,"ScrLk",1.0f,homeHeight);
    addKey(pos,osgGA::GUIEventAdapter::KEY_Pause,"Pause\nBreak",1.0f,homeHeight);
    
    

    pos = keypad;
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Insert,"0",2.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Delete,".",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Enter,"Enter",1.0f,homeHeight);
    
    pos = keypad;
    pos.z() += 1.0f;
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_End,"1",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Down,"2",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Page_Down,"3",1.0f,1.0f);

    pos = keypad;
    pos.z() += 2.0f;
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Left,"4",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Begin,"5",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Right,"6",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Add,"+",1.0f,1.0f);

    pos = keypad;
    pos.z() += 3.0f;
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Home,"7",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Up,"8",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Page_Up,"9",1.0f,1.0f);

    pos = keypad;
    pos.z() += 4.0f;
    addKey(pos,osgGA::GUIEventAdapter::KEY_Num_Lock,"Num\nLock",1.0f,0.3f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Divide,"/",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Multiply,"*",1.0f,1.0f);
    addKey(pos,osgGA::GUIEventAdapter::KEY_KP_Subtract,"-",1.0f,1.0f);
    
    float totalWidth = pos.x()-origin.x();
    pos = origin;
    pos.z() += -1.5f;

    osg::Geode* geodeInput = new osg::Geode;
    {
        _inputText = new osgText::Text;
        _inputText->setFont("fonts/arial.ttf");
        _inputText->setColor(osg::Vec4(1.0f,1.0f,0.0f,1.0f));
        _inputText->setCharacterSize(1.0f);
        _inputText->setMaximumWidth(totalWidth);
        _inputText->setPosition(pos);
        _inputText->setDrawMode(osgText::Text::TEXT/*||osgText::Text::BOUNDINGBOX*/);
        _inputText->setAlignment(osgText::Text::BASE_LINE);
        _inputText->setAxisAlignment(osgText::Text::XZ_PLANE);
        _inputText->setDataVariance(osg::Object::DYNAMIC);
        _inputText->setText("Press some keys...");
        
        geodeInput->addDrawable(_inputText.get());
        
        _scene->addChild(geodeInput);
    }

}