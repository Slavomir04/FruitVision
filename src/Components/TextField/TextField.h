//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_TEXTFIELD_H
#define FRUITVISION_TEXTFIELD_H

#define MAXIMUM_UNICODE  127
#define MAXIMUM_LENGTH 260
#include "../SButton/SButton.h"


class TextField : public SButton{
public:
    TextField(float fl_size_x,float fl_size_y); //override
    TextField(float fl_size_x, float fl_size_y,int i_maximum_length,int i_maximum_unicode);
    TextField(float fl_size_x, float fl_size_y,int i_maximum_length,int i_maximum_unicode,std::string &str_font_path);




    enum TextAlign_type{
        Left,
        Right,
        Center
    };




    void vSetSize(float fl_x, float fl_y) override; //override
    void vSetText(const std::string &text) override;
    void vSetAlign(TextAlign_type alignType);


    void vUpdate(const sf::RenderWindow &c_Window) override; //override
    void vUpdateEvent(sf::Event &c_Event) override; //override




    const sf::Color color_default_focused = sf::Color::Yellow;
    const sf::Color color_default_nofocused = sf::Color::White;
    const sf::Color color_outline = sf::Color::Cyan;
    const sf::Color color_character = sf::Color::Black;

private:

    void vAlignText();
    void vText_left();
    void vText_right();



    char cGetCharFromEvent(sf::Event &c_Event);

protected:
    void vFirstInit() override;



private:

    TextAlign_type e_text_align;

    const int i_maximum_length;
    const int i_maxiumum_unicode;


};


#endif //FRUITVISION_TEXTFIELD_H
