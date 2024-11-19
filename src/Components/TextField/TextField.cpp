//
// Created by Sławomir on 05.11.2024.
//

#include "TextField.h"
TextField::TextField(float fl_size_x, float fl_size_y) {
        c_shape.setSize(sf::Vector2f(fl_size_x,fl_size_y));
        FirstInit();
}

TextField::~TextField() = default;

bool TextField::isMouseOver(float fl_mouse_x,float fl_mouse_y) {
    return c_shape.getGlobalBounds().contains(fl_mouse_x, fl_mouse_y);
}

bool TextField::isClicked(sf::Event &event) {
    return isMouseOver(event.mouseButton.x,event.mouseButton.y)&&
    (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased);
}

void TextField::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(c_shape,states);
    target.draw(c_text,states);
}

void TextField::setPosition(float fl_x, float fl_y) {
    float fl_shift_x = c_shape.getPosition().x-c_text.getPosition().x;
    float fl_shift_y = c_shape.getPosition().y-c_text.getPosition().y;
    c_shape.setPosition(sf::Vector2f(fl_x,fl_y));
    c_text.setPosition(sf::Vector2f(fl_x+fl_shift_x,fl_y+fl_shift_y));
}

void TextField::setSize(float fl_x, float fl_y) {
    Component::setSize(fl_x, fl_y);
}

sf::Vector2f TextField::pGetSize() {
    return Component::pGetSize();
}

sf::Vector2f TextField::pGetPosition() {
    return Component::pGetPosition();
}

void TextField::update(const sf::RenderWindow &c_Window) {
    Updateable::update(c_Window);
}

void TextField::updateEvent(sf::Event &c_Event) {
    Updateable::updateEvent(c_Event);
}

void TextField::setText(const std::string &text) {
    this->c_text.setString(text);
}

void TextField::FirstInit() {
    c_shape.setPosition(0,0);
    c_shape.setFillColor(sf::Color::White);
    c_shape.setOutlineColor(sf::Color::Black);

    c_text.setFillColor(sf::Color::Black);

    vText_center();
}

void TextField::vText_center() {
    sf::FloatRect rectBounds = c_shape.getGlobalBounds();
    sf::FloatRect textBounds = c_text.getLocalBounds();
    float x = rectBounds.left + (rectBounds.width / 2.0f) - (textBounds.width / 2.0f) - textBounds.left;
    float y = rectBounds.top + (rectBounds.height / 2.0f) - (textBounds.height / 2.0f) - textBounds.top;
    c_text.setPosition(x, y);
}




