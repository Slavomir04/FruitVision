//
// Created by Sławomir on 05.11.2024.
//


#include "TextField.h"
TextField::TextField(float fl_size_x, float fl_size_y) : SButton(fl_size_x,fl_size_y,""),
                                                         i_maximum_length(MAXIMUM_LENGTH), i_maxiumum_unicode(MAXIMUM_UNICODE) {
    vFirstInit();
}

TextField::TextField(float fl_size_x, float fl_size_y, int i_maximum_length, int i_maximum_unicode) : SButton(fl_size_x,fl_size_y,""),i_maximum_length(i_maximum_length),i_maxiumum_unicode(i_maximum_unicode){
    vFirstInit();
}

TextField::TextField(float fl_size_x, float fl_size_y, int i_maximum_length, int i_maximum_unicode,
                     std::string &str_font_path) : SButton(fl_size_x,fl_size_y,""),i_maximum_length(i_maximum_length),i_maxiumum_unicode(i_maximum_unicode){
    vFirstInit();
    if (!bLoadFont(str_font_path)) {
        throw std::runtime_error(FONT_CANNOT_LOAD + str_font_path);
    }else{
        c_text.setFont(c_font);
    }
}






void TextField::vSetSize(float fl_x, float fl_y) {
    c_shape.setSize(sf::Vector2f(fl_x,fl_y));
}
void TextField::vSetText(const std::string &text){
    wstr_text =  std::wstring(text.begin(), text.end());
    c_text.setString(text);
    vAlignText(); //reposition text
    vTrimTextSize(); //resize
    vAlignText(); //again reposition text
}
void TextField::vSetText(const std::wstring &text) {
    wstr_text=text;
    c_text.setString(text);
    vAlignText(); //reposition text
    vTrimTextSize(); //resize
    vAlignText(); //again reposition text
}

void TextField::vSetAlign(TextField::TextAlign_type alignType) {
    this->e_text_align =alignType;
    vAlignText();
}



void TextField::vUpdate(const sf::RenderWindow &c_Window) {
    v2f_mouse_position = c_Window.mapPixelToCoords(sf::Mouse::getPosition(c_Window));
    vShape_update();
}

void TextField::vUpdateEvent(sf::Event &c_Event) {
    //mouse
    if(bIsClicked(c_Event)){
        b_is_focused= true;
    }else if(c_Event.type == sf::Event::MouseButtonPressed){
        b_is_focused= false;
    }

    if(b_is_focused) {

        if (c_Event.type == sf::Event::KeyPressed) {
            if (c_Event.key.code == sf::Keyboard::BackSpace) {
                if (c_Event.key.alt) {
                    wstr_text = std::wstring();
                }
                if (!wstr_text.empty()) {
                    wstr_text.pop_back();
                }
            } else if (c_Event.key.control && c_Event.key.code == sf::Keyboard::V) {
                wstr_text += sf::Clipboard::getString();
                if (wstr_text.size() >= i_maximum_length)wstr_text = wstr_text.substr(0, i_maximum_length - 1);
            }
        }else if (c_Event.type == sf::Event::TextEntered && bValidChar(c_Event.text.unicode)) {
            wchar_t c_asciiChar =  c_Event.text.unicode;
            wstr_text.push_back(c_asciiChar);
        }
        vSetText(wstr_text);
    }
}


std::wstring TextField::getTextW() {
    return wstr_text;
}


void TextField::vText_left() {
    float alpha_x = c_text.getCharacterSize();
    float fl_x = c_shape.getPosition().x + c_text.getLetterSpacing()+alpha_x;
    float fl_y = c_shape.getPosition().y + (c_shape.getSize().y - c_text.getGlobalBounds().height)/2.0f;
    c_text.setPosition(fl_x,fl_y);
}

void TextField::vText_right() {
    float alpha_x = c_text.getCharacterSize();
    float fl_x = c_shape.getPosition().x +c_shape.getSize().x - c_text.getLetterSpacing()+alpha_x - c_text.getGlobalBounds().width;
    float fl_y = c_shape.getPosition().y + (c_shape.getSize().y - c_text.getGlobalBounds().height)/2.0f;
    c_text.setPosition(fl_x,fl_y);
}



bool TextField::bValidChar(wchar_t c) {
    return 31<c;
}



void TextField::vFirstInit() {
    e_text_align = Left;
    vShape_update();
}

void TextField::vAlignText() {
    switch (e_text_align) {
        case Left:
            vText_left();
            break;
        case Right:
            vText_right();
            break;
        case Center:
            vText_center();
            break;
        default:
            vText_left();
            break;
    }
}




































