//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_TEXTFIELD_H
#define FRUITVISION_TEXTFIELD_H
#include "../Button.h"

class TextField : public Button{
public:
    TextField(float fl_size_x,float fl_size_y);
    ~TextField() override;

    bool isMouseOver(float fl_mouse_x,float fl_mouse_y) override;
    bool isClicked(sf::Event &event) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setPosition(float fl_x, float fl_y) override;
    void setSize(float fl_x, float fl_y) override;
    sf::Vector2f pGetSize() override;
    sf::Vector2f pGetPosition() override;
    void update(const sf::RenderWindow &c_Window) override;
    void updateEvent(sf::Event &c_Event) override;

private:
    void vText_center();
    sf::RectangleShape c_shape;
    sf::Text c_text;
};


#endif //FRUITVISION_TEXTFIELD_H
