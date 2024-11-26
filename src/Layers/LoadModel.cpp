//
// Created by Sławomir on 19.11.2024.
//

#include "LoadModel.h"

LoadModel::LoadModel(std::string str_return_command) : str_return_command(str_return_command),i_maximum_information_length(50){
    vFirstInit();
}

void LoadModel::vUpdate(const sf::RenderWindow &c_Window) {
    Layer::vUpdate(c_Window);
    vSetPositions(c_Window.getSize().x,c_Window.getSize().y);
    if((clock.getElapsedTime() - time_lasttime).asMilliseconds() > WAIT_TIME){
        vReset();
        time_lasttime = clock.getElapsedTime();
    }
}

void LoadModel::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
}

void LoadModel::vFirstInit() {
    time_lasttime = clock.restart();
    b_is_loaded= false;

    this->addComponent((Component*)new TextField(vf_textField_size.x,vf_textField_size.y));
    this->addComponent((Component*)new TextField(vf_textField_size.x,vf_textField_size.y));
    this->addComponent((Component*)new SButton(vf_button_back_size.x,vf_button_back_size.x,"back"));
    this->addComponent((Component*)new SButton(vf_button_load_size.x,vf_button_load_size.x,"load"));

    ((TextField*)vec_components[i_index_of_informationField])->vSetFocusable(false);
    ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_fail);
    ((TextField*)vec_components[i_index_of_informationField])->vSetAlign(TextField::TextAlign_type::Center);


    ((SButton*)vec_components[i_index_of_button_back])->vSetOnClickCommand(str_return_command);
    ((SButton*)vec_components[i_index_of_button_load])->vSetOnClickCommand(LOAD_COMMAND);


    for(auto& e : vec_components)e->addObservator(this);

}

void LoadModel::vSetPositions(float fl_window_size_x, float fl_window_size_y) {
    sf::Vector2f position = {fl_window_size_x/2.0f,fl_window_size_y*0.1f};
    vec_components[i_index_of_informationField]->vSetPosition(position.x-vec_components[i_index_of_textField]->vfGetSize().x/2,position.y);
    position+={0,vec_components[i_index_of_informationField]->vfGetSize().y*1.1f};
    vec_components[i_index_of_textField]->vSetPosition(position.x-vec_components[i_index_of_textField]->vfGetSize().x/2,position.y);
    position+={0,vec_components[i_index_of_textField]->vfGetSize().y*1.1f};
    vec_components[i_index_of_button_back]->vSetPosition(position.x-vec_components[i_index_of_button_back]->vfGetSize().x,position.y);
    vec_components[i_index_of_button_load]->vSetPosition(position.x,position.y);
}
void LoadModel::vLoadModel() {

    std::string str_curr_path = ((TextField*)vec_components[i_index_of_textField])->getText();
    if(std::filesystem::exists(str_curr_path)){
        ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_feedback_ok);
        str_path = str_curr_path;
        b_is_loaded = true;
    }else{
        ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_feedback_fail);
    }
}
void LoadModel::vReset() {
    if(b_is_loaded){
        std::string str_loaded_text = str_path;
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
    else if(str_command == LOAD_COMMAND)vLoadModel();
    return true;
}












