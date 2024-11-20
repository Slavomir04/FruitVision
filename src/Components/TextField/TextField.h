//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_TEXTFIELD_H
#define FRUITVISION_TEXTFIELD_H

#define MAXIMUM_UNICODE  127
#define MAXIMUM_LENGTH 30
#include "../SButton/SButton.h"


class TextField : public SButton{
public:
    TextField(float fl_size_x,float fl_size_y); //override
    TextField(float fl_size_x,float fl_size_y,std::string str_font_path);//override
    TextField(float fl_size_x, float fl_size_y, std::string str_font_path,int i_maximum_length,int i_maximum_unicode);
    TextField(float fl_size_x, float fl_size_y, std::string str_text,int i_default_character_size,
              float fl_default_thicknes,std::string str_font_path,int i_maximum_length,int i_maximum_unicode);



    enum TextAlign_type{
        Left,
        Right,
        Center
    };




    void vSetSize(float fl_x, float fl_y) override; //override
    void vSetText(const std::string &text);
    void vSetAlign(TextAlign_type alignType);


    void vUpdate(const sf::RenderWindow &c_Window) override; //override
    void vUpdateEvent(sf::Event &c_Event) override; //override




    const sf::Color color_default_focused = sf::Color::Yellow;
    const sf::Color color_default_nofocused = sf::Color::White;
    const sf::Color color_outline = sf::Color::Cyan;
    const sf::Color color_character = sf::Color::Black;

private:

    void vText_update();
    void vText_center();
    void vText_left();
    void vText_right();
    void vTrimTextSize();


    char cGetCharFromEvent(sf::Event &c_Event);

protected:
    void vFirstInit() override;

    void vSetPosition_text() override;

private:

    TextAlign_type e_text_align;

    const int i_maximum_length;
    const int i_maxiumum_unicode;


};


#endif //FRUITVISION_TEXTFIELD_H
