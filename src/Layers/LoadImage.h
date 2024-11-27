//
// Created by Sławomir on 27.11.2024.
//

#ifndef FRUITVISION_LOADIMAGE_H
#define FRUITVISION_LOADIMAGE_H
#include "../Components/TextField/TextField.h"
#include "../Interfaces/Layer.h"
#include <filesystem>
#define LOAD_COMMAND "load command"
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

    const sf::Vector2f vf_textField_size={400,100};
    const sf::Vector2f vf_button_back_size={100,100};
    const sf::Vector2f vf_button_load_size={100,100};
    const sf::Vector2f vf_Image_load_size={100,100};

    const std::string str_load_ok = "Loaded model";
    const std::string str_load_fail = "no Image loaded";
    const std::string str_feedback_fail = "wrong path!";
    const std::string str_feedback_cannnot_open_file = "cannot open file!";
    const std::string str_feedback_ok = "Correct path!";

    sf::Color color_image_background = sf::Color::Green;
    sf::Texture texture_image;
    sf::RectangleShape rec_image;
    sf::Time time_lasttime;
    sf::Clock clock;
    sf::Text text_load_information;
    std::string str_return_command;
    std::string str_path;
    bool b_is_loaded;

    const int i_maximum_information_length;
};


#endif //FRUITVISION_LOADIMAGE_H
