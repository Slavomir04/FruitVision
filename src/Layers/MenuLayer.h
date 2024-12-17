//
// Created by Sławomir on 19.11.2024.
//

#ifndef FRUITVISION_MENULAYER_H
#define FRUITVISION_MENULAYER_H

#include "../Components/TextField/TextField.h"
#include "../Interfaces/Layer.h"
#define PREFIX_MENU "M"
class MenuLayer : Layer{
public:
    MenuLayer();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void vUpdate(const sf::RenderWindow &c_Window) override;
    void vUpdateEvent(sf::Event &c_Event) override;
    bool executeCommand(std::string &str_command) override;
    void vAddSButton(std::string str_label,std::string str_command);
    void vAddSButton(Button* button);

protected:
    void vFirstInit();
    void vSetPositions(float fl_window_size_x,float fl_window_size_y);

    //scale
    float fl_scale_shift = 0.1f;
    float fl_wide_scale = 0.2f;
    float fl_height_scale = 0.1f;

    bool b_resized;
    bool b_first_init;

};


#endif //FRUITVISION_MENULAYER_H
