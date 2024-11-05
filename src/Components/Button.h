//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_BUTTON_H
#define FRUITVISION_BUTTON_H
#include "../Interfaces/Component.h"

class Button :public Component{
public:
    virtual bool isMouseOver(float fl_mouse_x,float fl_mouse_y){return false;}
    virtual bool isClicked(sf::Event &event){return false;}
};


#endif //FRUITVISION_BUTTON_H
