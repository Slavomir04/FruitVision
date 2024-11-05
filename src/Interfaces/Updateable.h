//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_UPDATEABLE_H
#define FRUITVISION_UPDATEABLE_H
#include <SFML/Graphics.hpp>

class Updateable {
public:
    virtual void update(const sf::RenderWindow &c_Window){}
    virtual void updateEvent(sf::Event &c_Event){}
};


#endif //FRUITVISION_UPDATEABLE_H
