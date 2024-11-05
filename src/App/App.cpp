//
// Created by Sławomir on 05.11.2024.
//

#include "App.h"
App::App(int i_window_size_x, int i_window_size_y, std::string str_name) {
    this->window = new sf::RenderWindow(sf::VideoMode(i_window_size_x, i_window_size_y), str_name);

}
App::~App() {
    delete window;
}

void App::vStart() {
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->display();
    }
}





