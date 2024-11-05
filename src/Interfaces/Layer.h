//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_LAYER_H
#define FRUITVISION_LAYER_H
#include "Observator.h"
#include "Observable.h"
#include "Component.h"
#include "Updateable.h"
#include <SFML/Graphics.hpp>
#include <vector>
class Layer :public Observator,public Observable,public sf::Drawable,public Updateable{
public:
    virtual ~Layer(){
        for(auto pc_e : vec_components){
            delete pc_e;
        }
    }
    void addComponent(Component* pc_component){
        vec_components.push_back(pc_component);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        for(auto pc_e : vec_components){
            target.draw(*pc_e,states);
        }
    }

    void update(const sf::RenderWindow &c_Window) override {
        for(auto pc_e : vec_components){
            (*pc_e).update(c_Window);
        }
    }

    void updateEvent(sf::Event &c_Event) override {
        for(auto pc_e : vec_components){
            (*pc_e).updateEvent(c_Event);
        }
    }

private:
    std::vector<Component*> vec_components;
};


#endif //FRUITVISION_LAYER_H
