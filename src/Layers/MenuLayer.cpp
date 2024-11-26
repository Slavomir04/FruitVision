//
// Created by Sławomir on 19.11.2024.
//

#include "MenuLayer.h"

MenuLayer::MenuLayer(Observator& pc_return_observator,float fl_button_size_x,float fl_button_size_y) : pc_return_observator(&pc_return_observator) {
    vFirstInit();
    this->fl_button_size_x=fl_button_size_x;
    this->fl_button_size_y=fl_button_size_y;
}

void MenuLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Layer::draw(target, states);
}

void MenuLayer::vUpdate(const sf::RenderWindow &c_Window) {
    Layer::vUpdate(c_Window);
    vUpdateDefaults((float)c_Window.getSize().x,(float)c_Window.getSize().y);
    vAlignButtons();
}
void MenuLayer::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
}


bool MenuLayer::executeCommand(std::string &str_command) {
    return const_cast<Observator *>(pc_return_observator)->executeCommand(str_command);
}

void MenuLayer::vAddSButton(std::string str_label,std::string str_command) {
    this->addComponent(new SButton(100,100,str_label));
    ((SButton*)vec_components[vec_components.size()-1])->vSetOnClickCommand(str_command);
    ((SButton*)vec_components[vec_components.size()-1])->addObservator(this);
}
void MenuLayer::vAddSButton(float fl_size_x, float fl_size_y, std::string str_label, std::string str_command) {
    this->addComponent(new SButton(fl_size_x,fl_size_y,str_label));
    ((SButton*)vec_components[vec_components.size()-1])->vSetOnClickCommand(str_command);
    ((SButton*)vec_components[vec_components.size()-1])->addObservator(this);
}

void MenuLayer::vFirstInit() {
    fl_button_size_x = 100;
    fl_button_size_y = 100;
    fl_scale_shift=0.1;
    fl_wide_scale = 0.1;
    fl_x_positon = 0;
    i_character_size=15;
    vf_position_buttons = sf::Vector2f(0,0);
    b_autoscale= false;
}


void MenuLayer::vAlignButtons() {
    sf::Vector2f vf_position = sf::Vector2f(fl_x_positon,0);
    for(auto & vec_button : this->vec_components){
        vf_position+= {0, (1+fl_scale_shift) * fl_button_size_y};
        ((SButton*)vec_button)->vSetPosition(vf_position.x,vf_position.y);
        ((SButton*)vec_button)->vSetCharacterSize(i_character_size);
        ((SButton*)vec_button)->vSetSize(fl_button_size_x,fl_button_size_y);
    }
}

void MenuLayer::vUpdateDefaults(float fl_window_size_x,float fl_window_size_y) {
    if(!vec_components.empty()){
        if(b_autoscale) {
            fl_button_size_x = fl_window_size_x / (float) vec_components.size();
            fl_button_size_y = fl_window_size_y * fl_wide_scale;
        }
        fl_x_positon=   (fl_window_size_x - fl_button_size_x)/2;
    }
}

void MenuLayer::vSetAutoScale(bool b_autoscale) {
    this->b_autoscale=b_autoscale;
}














