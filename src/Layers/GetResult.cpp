//
// Created by Sławomir on 27.11.2024.
//

#include "GetResult.h"

GetResult::GetResult(std::string str_return_command) : str_return_command(str_return_command){
    vFirstInit();
}


GetResult::~GetResult() {

}

void GetResult::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Layer::draw(target, states);
    target.draw(rec_image,states);
}

void GetResult::vUpdate(const sf::RenderWindow &c_Window) {
    Layer::vUpdate(c_Window);
}

void GetResult::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
}

bool GetResult::executeCommand(std::string &str_command) {
    return Observator::executeCommand(str_command);
}

void GetResult::vFirstInit() {



}

void GetResult::vSetPositions(float fl_window_size_x, float fl_window_size_y) {
    sf::Vector2f position = {fl_window_size_x/2.0f,fl_window_size_y*0.1f};
    rec_image.setPosition(position.x - rec_image.getSize().x,position.y);
    vec_components[i_index_of_informationField]->vSetPosition(position.x,position.y);
    position+={0,vf_textField_size.y*1.1f};
    vec_components[i_index_of_button_back]->vSetPosition(position.x-vec_components[i_index_of_button_back]->vfGetSize().x/2,position.y);
    vec_components[i_index_of_button_load]->vSetPosition(position.x,position.y);
}

void GetResult::vGetResult() {

}

void GetResult::vReset() {

}
