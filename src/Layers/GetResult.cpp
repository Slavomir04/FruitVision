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
    if(b_resized || b_first_init){
        vSetPositions((float)c_Window.getSize().x,(float)c_Window.getSize().y);
        b_resized= false;
        b_first_init= false;
    }
}

void GetResult::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
    b_resized = (c_Event.type == sf::Event::Resized);
}

bool GetResult::executeCommand(std::string &str_command) {
    if(str_command == comm::str_Button_get)vGetResult();
    else if(str_command == str_return_command)provideCommand(str_return_command);
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
    b_resized= true;
    b_first_init= true;

    vec_components.push_back((Component*)new TextField(100, 100));
    vec_components.push_back((Component*)new SButton(100, 100, str_text_button_back));
    vec_components.push_back((Component*)new SButton(100,100,str_text_button_get));
    vec_components.push_back((Component*)new SImage(100, 100));


    ((TextField*)vec_components[i_index_of_informationField])->vSetFocusable(false);
    ((TextField*)vec_components[i_index_of_informationField])->vSetAlign(TextField::TextAlign_type::Center);
    ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_image_fail);


    ((SButton*)vec_components[i_index_of_button_back])->vSetOnClickCommand(str_return_command);
    ((SButton*)vec_components[i_index_of_button_get])->vSetOnClickCommand(comm::str_Button_get);
    ((SImage*)vec_components[i_index_of_image])->vSetBackgroundColor(color_image_background);

    b_is_image_loaded= false;
    b_is_model_loaded= false;

    for(auto& e : vec_components)e->addObservator(this);
}

void GetResult::vSetPositions(float fl_window_size_x, float fl_window_size_y) {


    float fl_size_image_x = fl_window_size_x*vf_scale_image.x;
    float fl_size_image_y = fl_window_size_y*vf_scale_image.y;
    float fl_shift_image_y = fl_size_image_y*fl_scale_shift;

    float fl_size_textField_x = fl_window_size_x*vf_scale_informationField.x;
    float fl_size_textField_y = fl_window_size_y*vf_scale_informationField.y;
    float fl_shift_textField_y = fl_size_textField_y*fl_scale_shift;

    float fl_size_button_x = fl_window_size_x*vf_scale_buttons.x;
    float fl_size_button_y = fl_window_size_y*vf_scale_buttons.y;
    float fl_shift_button_x = fl_size_button_x*fl_scale_shift;

    sf::Vector2f v2f_position = {fl_window_size_x/2.0f,fl_window_size_y/2.0f}; //center
    float fl_start_shift = (fl_size_image_y + fl_shift_textField_y +fl_size_textField_y+fl_shift_textField_y+fl_size_button_y)/2.0f;
    v2f_position+={0,-fl_start_shift};
    vec_components[i_index_of_image]->vSetSize(fl_size_image_x,fl_size_image_y);
    vec_components[i_index_of_image]->vSetPosition(v2f_position.x - fl_size_image_x/2.0f,v2f_position.y);
    v2f_position+={0,fl_size_image_y+fl_shift_image_y};

    vec_components[i_index_of_informationField]->vSetSize(fl_size_textField_x,fl_size_textField_y);
    vec_components[i_index_of_informationField]->vSetPosition(v2f_position.x - fl_size_textField_x/2.0f,v2f_position.y);
    v2f_position+={0,fl_size_textField_y+fl_shift_textField_y};

    vec_components[i_index_of_button_back]->vSetSize(fl_size_button_x,fl_size_button_y);
    vec_components[i_index_of_button_back]->vSetPosition(v2f_position.x - fl_size_button_x - fl_shift_button_x,v2f_position.y);

    vec_components[i_index_of_button_get]->vSetSize(fl_size_button_x,fl_size_button_y);
    vec_components[i_index_of_button_get]->vSetPosition(v2f_position.x + fl_shift_button_x,v2f_position.y);
}

void GetResult::vGetResult() {
    if(b_is_model_loaded && b_is_model_loaded){

    }else if(b_is_image_loaded)((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_image_fail);
    else if(b_is_model_loaded)((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_model_fail);
    else ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_image_fail +" "+str_load_model_fail);

}

void GetResult::vReset() {

}

