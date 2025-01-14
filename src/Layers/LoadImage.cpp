//
// Created by Sławomir on 27.11.2024.
//

#include "LoadImage.h"

LoadImage::LoadImage(std::string str_return_command,ImageRecognizer* pc_imageRecognizer)  : str_return_command(str_return_command),i_maximum_information_length(50),pc_imageRecognizer(pc_imageRecognizer){
    vFirstInit();
}

LoadImage::LoadImage(std::string str_return_command, ImageRecognizer *pc_imageRecognizer, SettingsReader &settings) : str_return_command(str_return_command),i_maximum_information_length(50),pc_imageRecognizer(pc_imageRecognizer){
    //overriding strings with settings
    std::string key;

    settings.vOverrideValueIfExists(str_load_ok,key=(PREFIX_LOAD_IMAGE+std::to_string(0)));
    settings.vOverrideValueIfExists(str_load_fail,key=(PREFIX_LOAD_IMAGE+std::to_string(1)));
    settings.vOverrideValueIfExists(str_feedback_fail,key=(PREFIX_LOAD_IMAGE+std::to_string(2)));
    settings.vOverrideValueIfExists(str_feedback_ok,key=(PREFIX_LOAD_IMAGE+std::to_string(3)));
    settings.vOverrideValueIfExists(str_button_back_name,key=(PREFIX_LOAD_IMAGE+std::to_string(4)));
    settings.vOverrideValueIfExists(str_button_load_name,key=(PREFIX_LOAD_IMAGE+std::to_string(5)));
    settings.vOverrideValueIfExists(str_button_load_from_file_name,key=(PREFIX_LOAD_IMAGE+std::to_string(6)));
    settings.vOverrideValueIfExists(str_feedback_cannnot_open_file,key=(PREFIX_LOAD_IMAGE+std::to_string(7)));


    vFirstInit();
}

LoadImage::~LoadImage() {
    delete pc_fileDialog;
}


void LoadImage::vUpdate(const sf::RenderWindow &c_Window) {
    Layer::vUpdate(c_Window);
    if(b_resized || b_first_init){
        vSetPositions(c_Window.getSize().x,c_Window.getSize().y);
        b_resized= false;
        b_first_init= false;
    }

    if((clock.getElapsedTime() - time_lasttime).asMilliseconds() > WAIT_TIME){
        vReset();
        time_lasttime = clock.getElapsedTime();
    }
}

void LoadImage::vUpdateEvent(sf::Event &c_Event) {
    Layer::vUpdateEvent(c_Event);
    b_resized = (c_Event.type == sf::Event::Resized);
}

void LoadImage::vFirstInit() {
    b_resized= true;
    b_first_init= true;

    time_lasttime = clock.restart();
    b_is_loaded= false;

    pc_fileDialog = FileDialogFactory::createFileDialog();

    this->addComponent((Component*)new TextField(100,100));
    this->addComponent((Component*)new TextField(100,100));
    this->addComponent((Component*)new SButton(100,100,str_button_back_name));
    this->addComponent((Component*)new SButton(100,100,str_button_load_name));
    this->addComponent((Component*)new SImage(100,100));
    this->addComponent((Component*)new SButton(100,100,str_button_load_from_file_name));

    ((TextField*)vec_components[i_index_of_informationField])->vSetFocusable(false);
    ((TextField*)vec_components[i_index_of_informationField])->vSetText(str_load_fail);
    ((TextField*)vec_components[i_index_of_informationField])->vSetAlign(TextField::TextAlign_type::Center);


    ((SButton*)vec_components[i_index_of_button_back])->vSetOnClickCommand(str_return_command);
    ((SButton*)vec_components[i_index_of_button_load])->vSetOnClickCommand(comm::str_Button_image_load);
    ((SButton*)vec_components[i_index_of_button_load_from_file])->vSetOnClickCommand(comm::str_Button_load_image_from_file);

    ((SImage*)vec_components[i_index_of_image])->vSetBackgroundColor(color_image_background);



    for(auto& e : vec_components)e->addObservator(this);
}

void LoadImage::vSetPositions(float fl_window_size_x, float fl_window_size_y) {
    sf::Vector2f v2f_position = {fl_window_size_x/2.0f,0}; //center x

    float fl_size_image_x = fl_window_size_x*vf_Image_scale_size.x;
    float fl_size_image_y = fl_window_size_y*vf_Image_scale_size.y;
    float fl_shift_image_y = fl_size_image_y*fl_scale_shift;

    float fl_size_textField_x = fl_window_size_x*vf_scale_textField.x;
    float fl_size_textField_y = fl_window_size_y*vf_scale_textField.y;
    float fl_shift_textField_y = fl_size_textField_y*fl_scale_shift;

    float fl_size_button_x = fl_window_size_x*vf_scale_buttons.x;
    float fl_size_button_y = fl_window_size_y*vf_scale_buttons.y;
    float fl_shift_button_x = fl_size_button_x*fl_scale_shift;

    float fl_size_button_load_from_file_x = fl_window_size_x*vf_scale_button_load_from_file.x;
    float fl_size_button_load_from_file_y = fl_window_size_y*vf_scale_button_load_from_file.y;
    float fl_shift_button_load_from_file_y = fl_size_button_load_from_file_y*fl_scale_shift;

    v2f_position+={-fl_size_image_x/2.0f,fl_shift_image_y};
    vec_components[i_index_of_image]->vSetSize(fl_size_image_x,fl_size_image_y);
    vec_components[i_index_of_image]->vSetPosition(v2f_position.x,v2f_position.y);

    v2f_position+={0,fl_size_image_y};
    v2f_position = {fl_window_size_x/2.0f,v2f_position.y}; //recenter x

    v2f_position+={-fl_size_textField_x/2.0f,fl_shift_textField_y};
    vec_components[i_index_of_informationField]->vSetSize(fl_size_textField_x,fl_size_textField_y);
    vec_components[i_index_of_informationField]->vSetPosition(v2f_position.x,v2f_position.y);

    v2f_position+={0,fl_shift_textField_y + fl_size_textField_y};
    vec_components[i_index_of_textField]->vSetSize(fl_size_textField_x,fl_size_textField_y);
    vec_components[i_index_of_textField]->vSetPosition(v2f_position.x,v2f_position.y);


    v2f_position+={fl_shift_button_x,fl_size_textField_y + fl_shift_textField_y};

    vec_components[i_index_of_button_back]->vSetSize(fl_size_button_x,fl_size_button_y);
    vec_components[i_index_of_button_back]->vSetPosition(v2f_position.x,v2f_position.y);

    v2f_position+={fl_size_textField_x - fl_size_button_x - fl_shift_button_x*2.0f,0};
    vec_components[i_index_of_button_load]->vSetSize(fl_size_button_x,fl_size_button_y);
    vec_components[i_index_of_button_load]->vSetPosition(v2f_position.x,v2f_position.y);

    v2f_position={(fl_window_size_x-fl_size_button_load_from_file_x)/2.0f,v2f_position.y+fl_size_button_y+fl_shift_button_load_from_file_y};
    vec_components[i_index_of_button_load_from_file]->vSetSize(fl_size_button_load_from_file_x,fl_size_button_load_from_file_y);
    vec_components[i_index_of_button_load_from_file]->vSetPosition(v2f_position.x,v2f_position.y);

}
void LoadImage::vLoadTexture() {

    std::string str_temp_path = ((TextField*)vec_components[i_index_of_textField])->getText();
    if(pc_imageRecognizer->vLoadImage(str_temp_path)) {
        if (((SImage *) vec_components[i_index_of_image])->bLoadImage(str_temp_path)) {
            ((TextField *) vec_components[i_index_of_informationField])->vSetText(str_feedback_ok);
            str_path = str_temp_path;
            b_is_loaded = true;

        } else {
            ((TextField *) vec_components[i_index_of_informationField])->vSetText(str_feedback_cannnot_open_file);

        }
    }else{
        ((TextField *) vec_components[i_index_of_informationField])->vSetText(str_feedback_fail);
    }

    if (!b_is_loaded)((SImage *) vec_components[i_index_of_image])->vSetBackgroundColor(color_image_background);
    else ((SImage *) vec_components[i_index_of_image])->vSetBackgroundColor(sf::Color::White);
}

void LoadImage::vReset() {
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




bool LoadImage::executeCommand(std::string &str_command) {
    if(str_command == str_return_command){
        provideCommand(str_return_command);
        ((TextField*)vec_components[i_index_of_textField])->vSetText("");
    }
    else if(str_command == comm::str_Button_image_load){
        time_lasttime=clock.getElapsedTime();
        vLoadTexture();
    }else if(str_command == comm::str_Button_load_image_from_file) {

        if(pc_fileDialog!=nullptr) {
            std::string result = pc_fileDialog->strGetFilePath(str_description,vec_supported_extensions);
            if(!result.empty()) {
                ((TextField*)vec_components[i_index_of_textField])->vSetText(result);
            }
        }else std::cerr<<"file dialog is unsupported on this system!\n";

    }
    return true;
}


void LoadImage::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Layer::draw(target, states);
}


