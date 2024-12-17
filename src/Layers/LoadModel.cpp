//
// Created by Sławomir on 19.11.2024.
//

#include "LoadModel.h"

LoadModel::LoadModel(std::string str_return_command,ImageRecognizer* imageRecognizer) : str_return_command(str_return_command),i_maximum_information_length(50),pc_imageRecognizer(imageRecognizer){
    vFirstInit();
}

LoadModel::LoadModel(std::string str_return_command, ImageRecognizer *imageRecognizer, SettingsReader &settings): str_return_command(str_return_command),i_maximum_information_length(50),pc_imageRecognizer(imageRecognizer){
    //overriding strings with settings
    std::string key;

    settings.vOverrideValueIfExists(str_load_ok,key=(PREFIX_LOAD_MODEL+std::to_string(0)));
    settings.vOverrideValueIfExists(str_load_fail,key=(PREFIX_LOAD_MODEL+std::to_string(1)));
    settings.vOverrideValueIfExists(str_feedback_fail,key=(PREFIX_LOAD_MODEL+std::to_string(2)));
    settings.vOverrideValueIfExists(str_feedback_ok,key=(PREFIX_LOAD_MODEL+std::to_string(3)));
    settings.vOverrideValueIfExists(str_button_back_name,key=(PREFIX_LOAD_MODEL+std::to_string(4)));
    settings.vOverrideValueIfExists(str_button_load_name,key=(PREFIX_LOAD_MODEL+std::to_string(5)));


    vFirstInit();
}

void LoadModel::vUpdate(const sf::RenderWindow &c_Window) {
    Layer::vUpdate(c_Window);
    if(b_resized || b_first_init) {
        vSetPositions(c_Window.getSize().x, c_Window.getSize().y);
        b_resized= false;
        b_first_init= false;
    }
    if((clock.getElapsedTime() - time_lasttime).asMilliseconds() > WAIT_TIME){
        vReset();
        time_lasttime = clock.getElapsedTime();
    }
}

void LoadModel::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
    b_resized = (c_Event.type == sf::Event::Resized);
}

void LoadModel::vFirstInit() {
    b_resized= true;
    b_first_init= true;
    b_is_loaded= false;
    time_lasttime = clock.restart();

    this->addComponent((Component*)new TextField(100, 100));
    this->addComponent((Component*)new TextField(100, 100));
    this->addComponent((Component*)new SButton(100, 100, str_button_back_name));
    this->addComponent((Component*)new SButton(100,100,str_button_load_name));

    ((TextField*)vec_components[i_index_of_informationField])->vSetFocusable(false);
    ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_fail);
    ((TextField*)vec_components[i_index_of_informationField])->vSetAlign(TextField::TextAlign_type::Center);


    ((SButton*)vec_components[i_index_of_button_back])->vSetOnClickCommand(str_return_command);
    ((SButton*)vec_components[i_index_of_button_load])->vSetOnClickCommand(comm::str_Button_model_load);


    for(auto& e : vec_components)e->addObservator(this);
}

void LoadModel::vSetPositions(float fl_window_size_x, float fl_window_size_y) {
    sf::Vector2f v2f_position = {fl_window_size_x/2.0f,0}; //center x

    float fl_textField_size_x = fl_window_size_x*vf_scale_textField.x;
    float fl_textField_size_y = fl_window_size_x*vf_scale_textField.y;
    float fl_textField_shift_y = fl_textField_size_y*fl_scale_shift;

    float fl_button_size_x = fl_window_size_x*vf_scale_buttons.x;
    float fl_button_size_y = fl_window_size_x*vf_scale_buttons.y;
    float fl_button_shift_x = fl_button_size_x*fl_scale_shift;

    v2f_position += {-fl_textField_size_x/2.0f,fl_textField_shift_y};

    vec_components[i_index_of_informationField]->vSetSize(fl_textField_size_x,fl_textField_size_y);
    vec_components[i_index_of_informationField]->vSetPosition(v2f_position.x,v2f_position.y);
    v2f_position += {0,fl_textField_size_y+fl_textField_shift_y};

    vec_components[i_index_of_textField]->vSetSize(fl_textField_size_x,fl_textField_size_y);
    vec_components[i_index_of_textField]->vSetPosition(v2f_position.x,v2f_position.y);
    v2f_position += {0,fl_textField_size_y+fl_textField_shift_y};

    v2f_position = {fl_window_size_x/2.0f,v2f_position.y}; //recenter x
    v2f_position += {-fl_textField_size_x/2.0f + fl_button_shift_x,0};
    vec_components[i_index_of_button_back]->vSetSize(fl_button_size_x,fl_button_size_y);
    vec_components[i_index_of_button_back]->vSetPosition(v2f_position.x,v2f_position.y);

    v2f_position = {fl_window_size_x/2.0f,v2f_position.y}; //recenter x
    v2f_position += {fl_textField_size_x/2.0f - fl_button_size_x - fl_button_shift_x,0};
    vec_components[i_index_of_button_load]->vSetSize(fl_button_size_x,fl_button_size_y);
    vec_components[i_index_of_button_load]->vSetPosition(v2f_position.x,v2f_position.y);


}
void LoadModel::vLoadModel() {

    std::string str_temp_path = ((TextField*)vec_components[i_index_of_textField])->getText();
    if(pc_imageRecognizer->vLoadModel(str_temp_path)){
        ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_feedback_ok);
        str_path_actual = str_temp_path;
        b_is_loaded = true;
    }else{
        ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_feedback_fail);
    }
}
void LoadModel::vReset() {

    if(b_is_loaded){
        std::string str_loaded_text =std::string(str_path_actual.begin(), str_path_actual.end());
        std::string str_result;
        if(str_loaded_text.size() + str_load_ok.size() >= i_maximum_information_length){
            int first_pos = str_loaded_text.size() - (i_maximum_information_length - str_load_ok.size()-3);
            str_result= str_load_ok +" ..."+ str_loaded_text.substr(first_pos,str_loaded_text.size()-1);
        }else{
            str_result= str_load_ok +" "+ str_loaded_text;
        }
        ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_result);
    }else{
        ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_fail);
    }

}


bool LoadModel::executeCommand(std::string &str_command) {
    if(str_command == str_return_command){
        provideCommand(str_return_command);
        ((TextField*)vec_components[i_index_of_textField])->vSetText("");
    }
    else if(str_command == comm::str_Button_model_load){
        time_lasttime = clock.getElapsedTime();
        vLoadModel();
    }
    return true;
}












