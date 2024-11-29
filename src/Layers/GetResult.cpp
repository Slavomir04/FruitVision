//
// Created by Sławomir on 27.11.2024.
//

#include "GetResult.h"

GetResult::GetResult(std::string str_return_command,ImageRecognizer* pc_imageRecognizer) : str_return_command(str_return_command), pc_imageRecognizer(pc_imageRecognizer){
    if(pc_imageRecognizer== nullptr)throw std::runtime_error("image recognizer is nullptr");
    vFirstInit();
}


GetResult::~GetResult() {
    delete pc_imageRecognizer;
}

void GetResult::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Layer::draw(target, states);
}

void GetResult::vUpdate(const sf::RenderWindow &c_Window) {
    Layer::vUpdate(c_Window);
    vSetPositions((float)c_Window.getPosition().x,(float)c_Window.getPosition().y);
}

void GetResult::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
}

bool GetResult::executeCommand(std::string &str_command) {
    if(str_command == GET_RESULT_COMMAND)vGetResult();
    return true;
}
bool GetResult::setImagePath(std::string &str_image_path) {
    b_is_image_loaded = pc_imageRecognizer->vLoadImage(str_image_path);
    return b_is_image_loaded;
}

bool GetResult::setModelPath(std::string &str_model_path) {
    b_is_model_loaded = pc_imageRecognizer->vLoadImage(str_model_path);
    return b_is_model_loaded;
}

void GetResult::vFirstInit() {
    pc_imageRecognizer = nullptr;
    vec_components.push_back((Component*)new TextField(vf_informationField_size.x,vf_informationField_size.y));
    vec_components.push_back((Component*)new SButton(vf_button_back_size.x,vf_button_back_size.y,"Back"));
    vec_components.push_back((Component*)new SButton(vf_button_get_size.x,vf_button_get_size.y,"Get"));
    vec_components.push_back((Component*)new SImage(vf_image_size.x,vf_image_size.y));


    ((TextField*)vec_components[i_index_of_informationField])->vSetFocusable(false);
    ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_image_fail);
    ((TextField*)vec_components[i_index_of_informationField])->vSetAlign(TextField::TextAlign_type::Center);


    ((SButton*)vec_components[i_index_of_button_back])->vSetOnClickCommand(str_return_command);
    ((SButton*)vec_components[i_index_of_button_get])->vSetOnClickCommand(GET_RESULT_COMMAND);
    ((SImage*)vec_components[i_index_of_image])->vSetBackgroundColor(color_image_background);

    b_is_image_loaded= false;
    b_is_model_loaded= false;

    for(auto& e : vec_components)e->addObservator(this);
}

void GetResult::vSetPositions(float fl_window_size_x, float fl_window_size_y) {
    float alpha = 1.1f;
    sf::Vector2f position = {fl_window_size_x/2.0f,fl_window_size_y*0.1f};
    vec_components[i_index_of_image]->vSetPosition(position.x - vec_components[i_index_of_image]->vfGetSize().x/2.0f,position.y);
    vec_components[i_index_of_informationField]->vSetPosition(position.x+vec_components[i_index_of_image]->vfGetSize().x/2.0f,position.y);
    float fl_max_x = (vec_components[i_index_of_image]->vfGetSize().x > vec_components[i_index_of_informationField]->vfGetSize().x) ? vec_components[i_index_of_image]->vfGetSize().x : vec_components[i_index_of_informationField]->vfGetSize().x;
    position+={fl_max_x*alpha, 0};
    vec_components[i_index_of_button_get]->vSetPosition(position.x - vec_components[i_index_of_button_get]->vfGetSize().x,position.y);
    vec_components[i_index_of_button_back]->vSetPosition(position.x,position.y);
}

void GetResult::vGetResult() {

}

void GetResult::vReset() {

}

