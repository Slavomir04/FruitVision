//
// Created by Sławomir on 27.11.2024.
//

#ifndef FRUITVISION_LOADIMAGE_H
#define FRUITVISION_LOADIMAGE_H
#include "../Components/TextField/TextField.h"
#include "../Components/SImage/SImage.h"
#include "../Interfaces/Layer.h"
#include <filesystem>
#define WAIT_TIME 1000
class LoadImage : public Layer{
public:
    LoadImage(std::string str_return_command);

    void vUpdate(const sf::RenderWindow &c_Window) override;
    void vUpdateEvent(sf::Event &c_Event) override;

    bool executeCommand(std::string &str_command) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void vFirstInit();
    void vSetPositions(float fl_window_size_x,float fl_window_size_y);
    void vLoadTexture();
    void vReset();


    const int i_index_of_informationField=0;
    const int i_index_of_textField=1;
    const int i_index_of_button_back=2;
    const int i_index_of_button_load=3;
    const int i_index_of_image=4;

    float fl_scale_shift = 0.1f;
    sf::Vector2f vf_scale_textField={0.3f, 0.1f};
    sf::Vector2f vf_scale_buttons={0.1f, 0.1f};
    const sf::Vector2f vf_Image_scale_size={0.5f,0.5f};

    std::string str_load_ok = "Loaded image";
    std::string str_load_fail = "no Image loaded";
    std::string str_feedback_fail = "wrong path!";
    std::string str_feedback_cannnot_open_file = "cannot open file!";
    std::string str_feedback_ok = "Correct path!";
    std::string str_button_back_name = "back";
    std::string str_button_load_name = "load";

    sf::Color color_image_background = {sf::Color::Blue};
    sf::Time time_lasttime;
    sf::Clock clock;
    sf::Text text_load_information;
    std::string str_return_command;
    std::string str_path;
    bool b_is_loaded;

    bool b_resized;
    bool b_first_init;
    const int i_maximum_information_length;
};


#endif //FRUITVISION_LOADIMAGE_H
