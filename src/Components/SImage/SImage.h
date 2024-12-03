//
// Created by Sławomir on 27.11.2024.
//

#ifndef FRUITVISION_SIMAGE_H
#define FRUITVISION_SIMAGE_H
#include "../../Interfaces/Component.h"

class SImage : public Component{
public:
    SImage(float fl_size_x,float fl_size_y);
    ~SImage() override;

    bool bLoadImage(const std::string &str_path);
    bool bLoadImage(const std::wstring &str_path);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void vSetPosition(float fl_x, float fl_y) override;

    void vSetSize(float fl_x, float fl_y) override;

    sf::Vector2f vfGetSize() override;

    sf::Vector2f vfGetPosition() override;

    void vUpdate(const sf::RenderWindow &c_Window) override;

    void vUpdateEvent(sf::Event &c_Event) override;

    void vSetBackgroundColor(sf::Color color);
private:
    void vFirstInit();
    sf::RectangleShape* pc_Shape;
    sf::Texture* pc_Texture;
};


#endif //FRUITVISION_SIMAGE_H
