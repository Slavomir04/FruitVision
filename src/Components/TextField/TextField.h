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


    void vSetSize(float fl_x, float fl_y) override;
    void vSetText(const std::string &text) override;
    void vSetText(const std::wstring &text);
    void vSetAlign(TextAlign_type alignType);


    void vUpdate(const sf::RenderWindow &c_Window) override;
    void vUpdateEvent(sf::Event &c_Event) override;

    std::wstring getTextW();

    const sf::Color color_default_focused = sf::Color::Yellow;
    const sf::Color color_default_nofocused = sf::Color::White;
    const sf::Color color_outline = sf::Color::Cyan;
    const sf::Color color_character = sf::Color::Black;

private:

    void vAlignText();
    void vText_left();
    void vText_right();
    bool bValidChar(wchar_t c);

protected:
    void vFirstInit() override;

private:
    std::wstring wstr_text;
    TextAlign_type e_text_align;

    const int i_maximum_length;
    const int i_maxiumum_unicode;

};


#endif //FRUITVISION_TEXTFIELD_H
