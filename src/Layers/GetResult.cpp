//
// Created by Sławomir on 27.11.2024.
//

#include "GetResult.h"

GetResult::GetResult(std::string str_return_command,ImageRecognizer* pc_imageRecognizer) : str_return_command(str_return_command), pc_imageRecognizer(pc_imageRecognizer){
    if(pc_imageRecognizer== nullptr)throw std::runtime_error("image recognizer is nullptr");
    vFirstInit();
}

GetResult::GetResult(std::string str_return_command, ImageRecognizer *pc_imageRecognizer, SettingsReader &settings) : str_return_command(str_return_command), pc_imageRecognizer(pc_imageRecognizer){
    if(pc_imageRecognizer== nullptr)throw std::runtime_error("image recognizer is nullptr");

    std::string key;

    settings.vOverrideValueIfExists(str_get_result_prefix,key=(PREFIX_GET_RESULT+std::to_string(0)));
    settings.vOverrideValueIfExists(str_unknown_error,key=(PREFIX_GET_RESULT+std::to_string(1)));
    settings.vOverrideValueIfExists(str_load_image_fail,key=(PREFIX_GET_RESULT+std::to_string(2)));
    settings.vOverrideValueIfExists(str_load_model_fail,key=(PREFIX_GET_RESULT+std::to_string(3)));
    settings.vOverrideValueIfExists(str_load_image_ok,key=(PREFIX_GET_RESULT+std::to_string(4)));
    settings.vOverrideValueIfExists(str_load_model_ok,key=(PREFIX_GET_RESULT+std::to_string(5)));
    settings.vOverrideValueIfExists(str_text_button_back,key=(PREFIX_GET_RESULT+std::to_string(6)));
    settings.vOverrideValueIfExists(str_text_button_get,key=(PREFIX_GET_RESULT+std::to_string(7)));

    vFirstInit();
}


GetResult::~GetResult() {
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
    else if(str_command == str_return_command){
        vReset();
        provideCommand(str_return_command);
    }
    return true;
}
void GetResult::vFirstInit() {
    b_resized= true;
    b_first_init= true;

    vec_components.push_back((Component*)new TextField(100, 100));
    vec_components.push_back((Component*)new SButton(100, 100, str_text_button_back));
    vec_components.push_back((Component*)new SButton(100,100,str_text_button_get));
    vec_components.push_back((Component*)new SImage(100, 100));


    ((TextField*)vec_components[i_index_of_informationField])->vSetFocusable(false);
    ((TextField*)vec_components[i_index_of_informationField])->vSetAlign(TextField::TextAlign_type::Center);
    ((TextField*)vec_components[i_index_of_informationField])->vSetText("");


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
    std::vector<std::pair<std::string, double>> vec_result = pc_imageRecognizer->vecGetResult();
    vCheckResult(vec_result);
    std::stringstream stream;
    if(b_is_model_loaded && b_is_image_loaded){
        stream<<str_get_result_prefix;

        std::sort(vec_result.begin(),vec_result.end(),[](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
            return a.second>b.second;
        });
        //for testing is limited to PREDICTIONS_LIMIT
        for(int i=0; i<(PREDICTIONS_LIMIT<vec_result.size() ? PREDICTIONS_LIMIT : vec_result.size()); i++) {
            auto& pair = vec_result[i];
            stream<<'{'<<pair.first<<",\t"<<pair.second<<"%}"<<'\n';
        }


    }else{
        if(!b_is_image_loaded)stream<<str_load_image_fail;
        else stream<<str_load_image_ok;
        stream<<' ';

        if(!b_is_model_loaded)stream<<str_load_model_fail;
        else stream<<str_load_model_ok;
        stream<<' ';

        if(b_unknown_error_occur)stream<<b_unknown_error_occur;
    }

    if(b_is_image_loaded) {
        ((SImage*)vec_components[i_index_of_image])->bLoadImage(pc_imageRecognizer->strGetImagePath());
        ((SImage*)vec_components[i_index_of_image])->vSetBackgroundColor(sf::Color::White);
    }else ((SImage*)vec_components[i_index_of_image])->vSetBackgroundColor(color_image_background);

    ((TextField*)vec_components[i_index_of_informationField])->vSetText(stream.str());
}

void GetResult::vReset() {
    ((TextField*)vec_components[i_index_of_informationField])->vSetText("");
}
void GetResult::vCheckResult(std::vector<std::pair<std::string, double>> &vec_result) {
    b_is_image_loaded= true;
    b_is_model_loaded= true;
    b_unknown_error_occur= false;
    if(!vec_result.empty()) {
        for (auto &pair: vec_result) {
            if(pair.second < 0){
                switch ((int)pair.second) {
                    case ImageRecognizer::ProblemType::NO_MODEL:
                        b_is_model_loaded= false;
                    break;
                    case ImageRecognizer::ProblemType::NO_IMAGE:
                        b_is_image_loaded= false;
                        break;
                    default:
                        b_unknown_error_occur= true;
                }
            }
        }
    }else{
        throw std::runtime_error("ImageRecognizer doesnt work properly");
    }
}


