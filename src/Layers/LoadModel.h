//
// Created by Sławomir on 19.11.2024.
//

#ifndef FRUITVISION_LOADMODEL_H
#define FRUITVISION_LOADMODEL_H
#include "../Components/TextField/TextField.h"
#include "../Interfaces/Layer.h"
#include <filesystem>
#define LOAD_COMMAND "load command"
#define WAIT_TIME 1000

class LoadModel : public Layer{
public:
    LoadModel(std::string str_return_command);
    void vUpdate(const sf::RenderWindow &c_Window) override;
    void vUpdateEvent(sf::Event &c_Event) override;

    bool executeCommand(std::string &str_command) override;

private:
    void vFirstInit();
    void vSetPositions(float fl_window_size_x,float fl_window_size_y);
    void vLoadModel();
    void vReset();

    const int i_index_of_informationField=0;
    const int i_index_of_textField=1;
    const int i_index_of_button_back=2;
    const int i_index_of_button_load=3;

    const sf::Vector2f vf_textField_size={400,100};
    const sf::Vector2f vf_button_back_size={100,100};
    const sf::Vector2f vf_button_load_size={100,100};

    const std::string str_load_ok = "Loaded model";
    const std::string str_load_fail = "no model loaded";
    const std::string str_feedback_fail = "wrong path!";
    const std::string str_feedback_ok = "Correct path!";

    sf::Time time_lasttime;
    sf::Clock clock;
    sf::Text text_load_information;
    std::string str_return_command;
    std::string str_path;
    bool b_is_loaded;

    const int i_maximum_information_length;
};


#endif //FRUITVISION_LOADMODEL_H
