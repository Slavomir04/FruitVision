//
// Created by Sławomir on 19.11.2024.
//

#include "LoadImage.h"

LoadImage::LoadImage(std::string str_return_command) : str_return_command(str_return_command){
    vFirstInit();
}

void LoadImage::vUpdate(const sf::RenderWindow &c_Window) {
    Layer::vUpdate(c_Window);
    vSetPositions(c_Window.getSize().x,c_Window.getSize().y);
}

void LoadImage::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
}

void LoadImage::vFirstInit() {
    this->addComponent((Component*)new TextField(vf_textField_size.x,vf_textField_size.y));
    this->addComponent((Component*)new SButton(vf_button_back_size.x,vf_button_back_size.x,"back"));
    this->addComponent((Component*)new SButton(vf_button_load_size.x,vf_button_load_size.x,"load"));

    ((SButton*)vec_components[i_index_of_button_back])->vSetOnClickCommand(str_return_command);
    ((SButton*)vec_components[i_index_of_button_load])->vSetOnClickCommand("load command");

    for(auto& e : vec_components)e->addObservator(this);
}

void LoadImage::vSetPositions(float fl_window_size_x, float fl_window_size_y) {
    sf::Vector2f position = {fl_window_size_x/2.0f,fl_window_size_y*0.1f};
    vec_components[i_index_of_textField]->vSetPosition(position.x-vec_components[i_index_of_textField]->vfGetSize().x/2,position.y);
    position+={0,vec_components[i_index_of_textField]->vfGetSize().y*1.1f};
    vec_components[i_index_of_button_back]->vSetPosition(position.x-vec_components[i_index_of_button_back]->vfGetSize().x,position.y);
    vec_components[i_index_of_button_load]->vSetPosition(position.x,position.y);
}

bool LoadImage::executeCommand(std::string &str_command) {
    if(str_command == str_return_command)provideCommand(str_return_command);
    return true;
}

