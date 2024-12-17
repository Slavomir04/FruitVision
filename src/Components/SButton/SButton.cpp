//
// Created by Sławomir on 19.11.2024.
//

#include "SButton.h"
SButton::SButton(float fl_size_x, float fl_size_y, std::string str_text,int i_default_character_size,float
fl_default_thicknes,std::string str_font_path): i_default_character_size(i_default_character_size), fl_outline_thicknes(fl_default_thicknes), str_font_path(str_font_path){
    vFirstInit();
    c_shape.setSize(sf::Vector2f(fl_size_x,fl_size_y));
    vSetText(str_text);

}
SButton::SButton(float fl_size_x, float fl_size_y, std::string str_text) : i_default_character_size(DEFAULT_CHARACTER_SIZE),
                                                                           fl_outline_thicknes(DEFAULT_OUTLINE_THICKNES), str_font_path(DEFAULT_FONT_PATH){
    vFirstInit();
    c_shape.setSize(sf::Vector2f(fl_size_x,fl_size_y));
    vSetText(str_text);

}
SButton::SButton(float fl_size_x, float fl_size_y, std::string str_text, int i_character_size,
                 float fl_default_thicknes) : i_default_character_size(i_character_size),
                                              fl_outline_thicknes(fl_default_thicknes),str_font_path(DEFAULT_FONT_PATH) {
    vFirstInit();
    c_shape.setSize(sf::Vector2f(fl_size_x,fl_size_y));
    vSetText(str_text);

}



bool SButton::bIsMouseOver(float fl_mouse_x, float fl_mouse_y) {
    return c_shape.getGlobalBounds().contains(fl_mouse_x, fl_mouse_y);
}

bool SButton::bIsClicked(sf::Event &event) {
    return bIsMouseOver(v2f_mouse_position.x,v2f_mouse_position.y) &&
           (event.type == sf::Event::MouseButtonReleased);
}
void SButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(c_shape,states);
    target.draw(c_text,states);
}
void SButton::vSetSize(float fl_x, float fl_y) {
    c_shape.setSize(sf::Vector2f(fl_x,fl_y));
    vTrimTextSize();
    vText_center();
}

sf::Vector2f SButton::vfGetSize() {
    return  c_shape.getSize();
}

sf::Vector2f SButton::vfGetPosition() {
    return  c_shape.getPosition();
}

void SButton::vUpdate(const sf::RenderWindow &c_Window) {

    v2f_mouse_position = c_Window.mapPixelToCoords(sf::Mouse::getPosition(c_Window));
    b_is_focused = bIsMouseOver((float)v2f_mouse_position.x,(float )v2f_mouse_position.y);
    vShape_update();
}

void SButton::vUpdateEvent(sf::Event &c_Event) {
    //mouse
    if(bIsClicked(c_Event)){
        this->provideCommand(str_command);
    }
}
void SButton::vSetFont(const sf::Font &newFont) {
    this->c_font = newFont;
    this->c_text.setFont(c_font);
}
void SButton::vSetFocusable(bool b_focusable) {
    this->b_focusable=b_focusable;
}

void SButton::vSetText(const std::string &text) {
    c_text.setString(text);
    vTrimTextSize();
    vText_center();
}
void SButton::vSetOutlineThicknes(float fl_thicknes) {
    if(fl_thicknes>=0) {
        this->fl_outline_thicknes = fl_thicknes;
    }
}
void SButton::vSetOnClickCommand(const std::string &str_command) {
    this->str_command = str_command;
}
void SButton::vSetCharacterSize(int i_character_size) {
    c_text.setCharacterSize(i_character_size);
}
void SButton::vSetPosition(float fl_x, float fl_y) {
    float fl_div_x = fl_x - c_shape.getPosition().x;
    float fl_div_y = fl_y - c_shape.getPosition().y;
    vMoveText(fl_div_x,fl_div_y);
    c_shape.setPosition(fl_x,fl_y);
}

std::string SButton::getText() {
    return c_text.getString();
}
void SButton::vSetColorPressed(const sf::Color &color) {
    this->color_default_pressed = color;
}

void SButton::vSetColorFocused(const sf::Color &color) {
    this->color_default_pressed = color;
}

void SButton::vSetColorNoFocused(const sf::Color &color) {
    this->color_default_nofocused = color;
}

void SButton::vSetColorOutline(const sf::Color &color) {
    this->color_outline = color;
}

void SButton::vSetColorCharacter(const sf::Color &color) {
    this->color_character = color;
}
void SButton::vSetMousePosition(sf::Vector2f v2f_mouse_pos) {
    this->v2f_mouse_position = v2f_mouse_pos;
}
void SButton::vFirstInit() {
    str_command = DEFAULT_COMMAND;

    c_shape.setPosition(0,0);
    c_shape.setFillColor(color_default_nofocused);
    c_shape.setOutlineColor(color_outline);
    c_shape.setOutlineThickness(fl_outline_thicknes);
    b_is_focused= false;
    b_focusable= true;

    c_text.setFillColor(color_character);
    c_text.setCharacterSize(i_default_character_size);
    c_text.setPosition(0,0);
    vText_center();

    if (!bLoadFont(str_font_path)) {
        throw std::runtime_error(FONT_CANNOT_LOAD + str_font_path);
    }else{
        c_text.setFont(c_font);
    }

}

void SButton::vShape_update() {
    if(b_is_focused && b_focusable){
        c_shape.setFillColor(color_default_focused);
        c_shape.setOutlineThickness(fl_outline_thicknes);
    }else{
        c_shape.setFillColor(color_default_nofocused);
        c_shape.setOutlineThickness(0);
    }
}

void SButton::vMoveText(float fl_div_x, float fl_div_y) {
    float fl_new_x = fl_div_x + c_text.getPosition().x;
    float fl_new_y = fl_div_y + c_text.getPosition().y;
    c_text.setPosition(fl_new_x,fl_new_y);
}
void SButton::vSetPositionText(float fl_x, float fl_y) {
    c_text.setPosition(fl_x,fl_y);
}
void SButton::vText_center() {
   float fl_x = c_shape.getPosition().x + (c_shape.getSize().x - c_text.getGlobalBounds().width)/2.0f;
   float fl_y = c_shape.getPosition().y + (c_shape.getSize().y - c_text.getGlobalBounds().height)/2.0f;
   c_text.setPosition(fl_x,fl_y);
}



bool SButton::bLoadFont(std::string str_path) {
    return  c_font.loadFromFile(str_font_path);
}

void SButton::vTrimTextSize() {
    float fl_alpha = 1.1; //size of the text cannont be as big as the background some space must be there
    float fl_minimum_size = 1.0f;
    float fl_decrease_value=1.0f;
    float fl_fontSize = (float)i_default_character_size;
    c_text.setCharacterSize(fl_fontSize);
    //  Checking if the text fits in a rectangle
    sf::FloatRect textBounds = c_text.getGlobalBounds();
    while (textBounds.width*fl_alpha > c_shape.getSize().x || textBounds.height*fl_alpha > c_shape.getSize().y) {
        fl_fontSize -= fl_decrease_value;
        if (fl_fontSize <= fl_minimum_size) {
            break;
        }
        c_text.setCharacterSize(static_cast<unsigned int>(fl_fontSize));
        textBounds = c_text.getGlobalBounds();
    }
}








































