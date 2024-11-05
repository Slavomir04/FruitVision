//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_APP_H
#define FRUITVISION_APP_H

#include <SFML/Graphics.hpp>
#include <vector>
class App {
public:
    App(int i_window_size_x,int i_window_size_y,std::string str_name);
    ~App();
    void vStart();
private:
    sf::RenderWindow* window;
    std::string str_name;
};


#endif //FRUITVISION_APP_H
