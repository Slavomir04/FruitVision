//
// Created by Sławomir on 19.11.2024.
//

#ifndef FRUITVISION_LOADIMAGE_H
#define FRUITVISION_LOADIMAGE_H
#include "../Components/TextField/TextField.h"
#include "../Interfaces/Layer.h"

class LoadImage : public Layer{
public:
    LoadImage(std::string str_return_command);
    void vUpdate(const sf::RenderWindow &c_Window) override;
    void vUpdateEvent(sf::Event &c_Event) override;

    bool executeCommand(std::string &str_command) override;

private:
    void vFirstInit();
    void vSetPositions(float fl_window_size_x,float fl_window_size_y);
    std::string str_return_command;
    const int i_index_of_textField=0;
    const int i_index_of_button_back=1;
    const int i_index_of_button_load=2;

    const sf::Vector2f vf_textField_size={400,100};
    const sf::Vector2f vf_button_back_size={100,100};
    const sf::Vector2f vf_button_load_size={100,100};
};


#endif //FRUITVISION_LOADIMAGE_H
