//
// Created by Sławomir on 05.11.2024.
//


#include "TextField.h"
TextField::TextField(float fl_size_x, float fl_size_y) : SButton(fl_size_x,fl_size_y,""),
                                                         i_maximum_length(MAXIMUM_LENGTH), i_maxiumum_unicode(MAXIMUM_UNICODE) {}
TextField::TextField(float fl_size_x, float fl_size_y, std::string str_font_path) : SButton(fl_size_x,fl_size_y,""),
                                                                                    i_maximum_length(MAXIMUM_LENGTH), i_maxiumum_unicode(MAXIMUM_UNICODE) {}

TextField::TextField(float fl_size_x, float fl_size_y, std::string str_font_path,int i_maximum_length,int i_maximum_unicode):SButton(fl_size_x,fl_size_y,""),
i_maximum_length(i_maximum_length), i_maxiumum_unicode(i_maximum_unicode){}

TextField::TextField(float fl_size_x, float fl_size_y, std::string str_text,int i_default_character_size,
          float fl_default_thicknes,std::string str_font_path,int i_maximum_length,int i_maximum_unicode) : SButton(fl_size_x,fl_size_y,"",i_default_character_size,fl_default_thicknes,str_font_path),
i_maximum_length(i_maximum_length), i_maxiumum_unicode(i_maxiumum_unicode){}





void TextField::vSetSize(float fl_x, float fl_y) {
    c_shape.setSize(sf::Vector2f(fl_x,fl_y));
}
void TextField::vSetText(const std::string &text) {
    SButton::vSetText(text);
    vTrimTextSize();
}
void TextField::vSetAlign(TextField::TextAlign_type alignType) {
    this->e_text_align =alignType;
}



void TextField::vUpdate(const sf::RenderWindow &c_Window) {
    vShape_update();
    vText_update();
}

void TextField::vUpdateEvent(sf::Event &c_Event) {
    //mouse
    if(bIsClicked(c_Event)){
        b_is_focused= true;
    }else if(c_Event.type == sf::Event::MouseButtonPressed){
        b_is_focused= false;
    }


    //keyboard
    if(b_is_focused && c_Event.type == sf::Event::KeyPressed){
        if(c_Event.text.unicode <= i_maxiumum_unicode){
           // printf("%i",(int)c_Event.text.unicode);
            std::string str_new_text = c_text.getString();
            char c_asciiChar = cGetCharFromEvent(c_Event);
            if(c_Event.key.code == sf::Keyboard::BackSpace){
                if(!str_new_text.empty())
                    str_new_text.pop_back();
            }else if(str_new_text.size()<i_maximum_length){
                str_new_text.push_back(c_asciiChar);
            }
            vSetText(str_new_text);

        }
    }
}





void TextField::vText_update() {
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
    }


}

void TextField::vText_center() {
    c_text.setPosition(c_shape.getPosition());
    float fl_x_move = (c_shape.getSize().x - c_text.getGlobalBounds().getSize().x)/2.0f;
    float fl_y_move = (c_shape.getSize().y - c_text.getGlobalBounds().getSize().y)/2.0f;
    c_text.move(-fl_x_move,-fl_y_move);
}
void TextField::vText_left() {
    c_text.setPosition(c_shape.getPosition());
    float fl_x_move = c_text.getLetterSpacing();
    float fl_y_move = (c_shape.getSize().y - c_text.getGlobalBounds().getSize().y)/2.0f;
    c_text.move(fl_x_move,fl_y_move);
}

void TextField::vText_right() {
    c_text.setPosition(c_shape.getPosition());
    float fl_x_move = c_text.getLetterSpacing();
    float fl_y_move = c_shape.getSize().y - c_text.getGlobalBounds().getSize().y;
    c_text.move(-fl_x_move,-fl_y_move);
}


void TextField::vTrimTextSize() {

}



char TextField::cGetCharFromEvent(sf::Event &c_Event) {
    if(c_Event.text.unicode < 'z'-'a'){
        return (char)('a'+c_Event.text.unicode);
    }else if(c_Event.text.unicode == 58){
        return '\n';
    }else return '?';
}

void TextField::vFirstInit() {
    SButton::vFirstInit();
    e_text_align = Left;
    vShape_update();
    vText_update();
}

void TextField::vSetPosition_text() {
    float fl_shift_x = c_shape.getPosition().x-c_text.getPosition().x;
    float fl_shift_y = c_shape.getPosition().y-c_text.getPosition().y;
    c_text.setPosition(sf::Vector2f(c_shape.getPosition().x+fl_shift_x,c_shape.getPosition().x+fl_shift_y));
}

























