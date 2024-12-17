//
// Created by Sławomir on 27.11.2024.
//

#include "SImage.h"
SImage::SImage(float fl_size_x,float fl_size_y) {
    vFirstInit();
    pc_Shape->setSize(sf::Vector2f(fl_size_x, fl_size_y));
}
SImage::~SImage() {
    delete pc_Shape;
    delete pc_Texture;
}
bool SImage::bLoadImage(const std::string &str_path) {

    try{
        this->pc_Texture->loadFromFile(str_path);
        pc_Shape->setTexture(pc_Texture);
        return true;
    }catch(...){
        return false;
    }
}
bool SImage::bLoadImage(const std::wstring &str_path) {
    try{
        pc_Shape->setTexture(pc_Texture);
        return true;
    }catch(...){
        return false;
    }
}
void SImage::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*pc_Shape);
}

void SImage::vSetPosition(float fl_x, float fl_y) {
    pc_Shape->setPosition(sf::Vector2f(fl_x,fl_y));
}

void SImage::vSetSize(float fl_x, float fl_y) {
    pc_Shape->setSize(sf::Vector2f(fl_x,fl_y));
}

sf::Vector2f SImage::vfGetSize() {
    return pc_Shape->getSize();
}

sf::Vector2f SImage::vfGetPosition() {
    return pc_Shape->getPosition();
}

void SImage::vUpdate(const sf::RenderWindow &c_Window) {}
void SImage::vUpdateEvent(sf::Event &c_Event) {}
void SImage::vFirstInit() {
    pc_Shape = new sf::RectangleShape();
    pc_Texture = new sf::Texture();
    pc_Shape->setFillColor(sf::Color::White);
}
void SImage::vSetBackgroundColor(sf::Color color) {
    this->pc_Shape->setFillColor(color);
}













