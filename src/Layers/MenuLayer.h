//
// Created by Sławomir on 19.11.2024.
//

#ifndef FRUITVISION_MENULAYER_H
#define FRUITVISION_MENULAYER_H

#include "../Components/TextField/TextField.h"
#include "../Interfaces/Layer.h"
class MenuLayer : Layer{
public:
    MenuLayer(Observator& pc_return_observator,float fl_button_size_x,float fl_button_size_y);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void vUpdate(const sf::RenderWindow &c_Window) override;
    void vUpdateEvent(sf::Event &c_Event) override;
    bool executeCommand(std::string &str_command) override;
    void vAddSButton(std::string str_label,std::string str_command);
    void vAddSButton(float fl_size_x,float fl_size_y,std::string str_label,std::string str_command);
    void vSetAutoScale(bool b_autoscale);
protected:
    void vFirstInit();
    void vAlignButtons();
    void vUpdateDefaults(float fl_window_size_x,float fl_window_size_y);
    float fl_button_size_x;
    float fl_button_size_y;
    float fl_scale_shift;
    float fl_wide_scale;
    float fl_x_positon;
    int i_character_size;
    sf::Vector2f vf_position_buttons;
    bool b_autoscale;


    const Observator* pc_return_observator;
};


#endif //FRUITVISION_MENULAYER_H
