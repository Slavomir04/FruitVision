//
// Created by Sławomir on 19.11.2024.
//

#include "MenuLayer.h"

MenuLayer::MenuLayer() {
    vFirstInit();
}

void MenuLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Layer::draw(target, states);
}

void MenuLayer::vUpdate(const sf::RenderWindow &c_Window) {
    Layer::vUpdate(c_Window);
    if(b_resized || b_first_init) {
        vSetPositions((float)c_Window.getSize().x,(float)c_Window.getSize().y);
        b_resized= false;
        b_first_init= false;
    }
}
void MenuLayer::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
    b_resized = (c_Event.type == sf::Event::Resized);
}


bool MenuLayer::executeCommand(std::string &str_command) {
    provideCommand(str_command);
    return true;
}

void MenuLayer::vAddSButton(std::string str_label,std::string str_command) {
    this->addComponent(new SButton(100,100,str_label));
    ((SButton*)vec_components[vec_components.size()-1])->vSetOnClickCommand(str_command);
    ((SButton*)vec_components[vec_components.size()-1])->addObservator(this);
    b_resized= true;
}
void MenuLayer::vAddSButton(Button *button) {
    if(button!= nullptr){
        this->addComponent(button);
    }
    b_resized= true;
}

void MenuLayer::vFirstInit() {
    b_resized = true;
    b_first_init= true;
}
void MenuLayer::vSetPositions(float fl_window_size_x, float fl_window_size_y) {
    sf::Vector2f v2f_position = {fl_window_size_x/2.0f,fl_window_size_y/2.0f}; //center

    float fl_button_size_x = fl_window_size_x*fl_wide_scale;
    float fl_button_size_y = fl_window_size_x*fl_height_scale;

    float fl_button_shift_y = fl_button_size_y * fl_scale_shift;

    float fl_shift_x = -1*fl_button_size_x/2.0f;
    float fl_shift_y = -1 * ((float)vec_components.size() * (fl_button_size_y + fl_button_shift_y)) / 2.0f;

    v2f_position+={fl_shift_x,fl_shift_y};

    for(auto& buttons : vec_components){
        buttons->vSetSize(fl_button_size_x,fl_button_size_y);
        buttons->vSetPosition(v2f_position.x,v2f_position.y);
        v2f_position+={0, fl_button_size_y + fl_button_shift_y};
    }
}





















