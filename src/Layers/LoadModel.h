//
// Created by Sławomir on 19.11.2024.
//

#ifndef FRUITVISION_LOADMODEL_H
#define FRUITVISION_LOADMODEL_H
#include "../Components/TextField/TextField.h"
#include "../Interfaces/Layer.h"
#include "../Interfaces/ImageRecognizer.h"
#include "../Reader/SettingsReader.h"
#include "../FileDialog/FileDialogFactory.h"

#define WAIT_TIME 1000
#define PREFIX_LOAD_MODEL "LM"
class LoadModel : public Layer{


public:
    LoadModel(std::string str_return_command,ImageRecognizer* imageRecognizer);
    LoadModel(std::string str_return_command,ImageRecognizer* imageRecognizer,SettingsReader& settings);
    ~LoadModel() override;
    void vUpdate(const sf::RenderWindow &c_Window) override;
    void vUpdateEvent(sf::Event &c_Event) override;
    bool executeCommand(std::string &str_command) override;

private:
    void vFirstInit();
    void vSetPositions(float fl_window_size_x,float fl_window_size_y);
    void vLoadModel();
    void vReset();

    FileDialog* pc_fileDialog;
    std::string str_description = "Model files";
    std::vector<std::string> vec_supported_extensions = {"h5"};


    const int i_index_of_informationField=0;
    const int i_index_of_textField=1;
    const int i_index_of_button_back=2;
    const int i_index_of_button_load=3;
    const int i_index_of_button_load_from_file=4;

    //scale
    float fl_scale_shift = 0.1f;
    sf::Vector2f vf_scale_textField={0.3f, 0.1f};
    sf::Vector2f vf_scale_buttons={0.12f, 0.1f};
    sf::Vector2f vf_scale_button_load_from_file={0.2f, 0.05f};


    //default strings
    std::string str_load_ok = "Loaded model";
    std::string str_load_fail = "no model loaded";
    std::string str_feedback_fail = "wrong path!";
    std::string str_feedback_ok = "Correct path!";
    std::string str_button_back_name = "back";
    std::string str_button_load_name = "load";
    std::string str_button_load_from_file_name = "load from file";

    sf::Time time_lasttime;
    sf::Clock clock;
    sf::Text text_load_information;
    std::string str_return_command;
    std::string str_path_actual;

    bool b_is_loaded;
    bool b_resized;
    bool b_first_init;
    const int i_maximum_information_length;

    ImageRecognizer* pc_imageRecognizer;
};


#endif //FRUITVISION_LOADMODEL_H
