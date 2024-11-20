//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_COMPONENT_H
#define FRUITVISION_COMPONENT_H
#include <SFML/Graphics.hpp>
#include "Observable.h"
#include "Updateable.h"
class Component : public sf::Drawable, public Observable,public Updateable{

public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}
    virtual void vSetPosition(float fl_x, float fl_y){}
    virtual void vSetSize(float fl_x, float fl_y){}
    virtual sf::Vector2f vfGetSize(){return sf::Vector2f(0, 0);}
    virtual sf::Vector2f vfGetPosition(){return sf::Vector2f(0, 0);}

private:




};


#endif //FRUITVISION_COMPONENT_H
