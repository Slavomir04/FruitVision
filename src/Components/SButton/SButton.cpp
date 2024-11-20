//
// Created by Sławomir on 19.11.2024.
//

#include "SButton.h"
SButton::SButton(float fl_size_x, float fl_size_y, std::string str_text,int i_default_character_size,float
fl_default_thicknes,std::string str_font_path): i_default_character_size(i_default_character_size), fl_outline_thicknes(fl_default_thicknes), str_font_path(str_font_path){
    c_shape.setSize(sf::Vector2f(fl_size_x,fl_size_y));
    c_text.setString(str_text);
    vFirstInit();
}
SButton::SButton(float fl_size_x, float fl_size_y, std::string str_text) : i_default_character_size(DEFAULT_CHARACTER_SIZE),
                                                                           fl_outline_thicknes(DEFAULT_OUTLINE_THICKNES), str_font_path(DEFAULT_FONT_PATH){
    c_shape.setSize(sf::Vector2f(fl_size_x,fl_size_y));
    c_text.setString(str_text);
    vFirstInit();
}
SButton::SButton(float fl_size_x, float fl_size_y, std::string str_text, int i_character_size,
                 float fl_default_thicknes) : i_default_character_size(i_character_size),
                                              fl_outline_thicknes(fl_default_thicknes) {
    c_shape.setSize(sf::Vector2f(fl_size_x,fl_size_y));
    c_text.setString(str_text);
    vFirstInit();
}



bool SButton::bIsMouseOver(float fl_mouse_x, float fl_mouse_y) {
    return c_shape.getGlobalBounds().contains(fl_mouse_x, fl_mouse_y);
}

bool SButton::bIsClicked(sf::Event &event) {
    return bIsMouseOver(event.mouseButton.x, event.mouseButton.y) &&
           (event.type == sf::Event::MouseButtonReleased);
}
void SButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(c_shape,states);
    target.draw(c_text,states);
}
void SButton::vSetSize(float fl_x, float fl_y) {
    c_shape.setSize(sf::Vector2f(fl_x,fl_y));
}

sf::Vector2f SButton::vfGetSize() {
    return  c_shape.getSize();
}

sf::Vector2f SButton::vfGetPosition() {
    return  c_shape.getPosition();
}

void SButton::vUpdate(const sf::RenderWindow &c_Window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(c_Window);
    b_is_focused = bIsMouseOver((float)mousePosition.x,(float )mousePosition.y);
    vShape_update();
}

void SButton::vUpdateEvent(sf::Event &c_Event) {
    //mouse
    if(bIsClicked(c_Event)){
        this->provideCommand(str_command);
    }
}
void SButton::vSetText(const std::string &text) {
    c_text.setString(text);
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
    c_shape.setPosition(fl_x,fl_y);
    vSetPosition_text();
}

std::string SButton::getText() {
    return c_text.getString();
}

void SButton::vFirstInit() {
    str_command = DEFAULT_COMMAND;

    c_shape.setPosition(0,0);
    c_shape.setFillColor(color_default_nofocused);
    c_shape.setOutlineColor(color_outline);
    c_shape.setOutlineThickness(fl_outline_thicknes);
    b_is_focused= false;

    c_text.setFillColor(color_character);
    c_text.setCharacterSize(i_default_character_size);
    vSetPosition_text();


    if (!c_font.loadFromFile(str_font_path)) {
        throw std::runtime_error(FONT_CANNOT_LOAD_TEXT + str_font_path);
    }else{
        c_text.setFont(c_font);
    }

}

void SButton::vShape_update() {
    if(b_is_focused){
        c_shape.setFillColor(color_default_focused);
        c_shape.setOutlineThickness(fl_outline_thicknes);
    }else{
        c_shape.setFillColor(color_default_nofocused);
        c_shape.setOutlineThickness(0);
    }
}

void SButton::vSetPosition_text() {
    float fl_x_move = (c_shape.getSize().x-c_text.getGlobalBounds().width)/2.0f;
    float fl_y_move = (c_shape.getSize().y-c_text.getGlobalBounds().height)/2.0f;
    c_text.setPosition(c_shape.getPosition()+sf::Vector2f(fl_x_move,fl_y_move));
}

void SButton::vText_update() {
    c_text.setCharacterSize(i_default_character_size);
}


























