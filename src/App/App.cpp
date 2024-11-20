//
// Created by Sławomir on 05.11.2024.
//

#include "App.h"



App::App(int i_window_size_x, int i_window_size_y, std::string str_name) {
    this->window = new sf::RenderWindow(sf::VideoMode(i_window_size_x, i_window_size_y), str_name,sf::Style::Titlebar | sf::Style::Close);
    vFirstInit();
}
App::~App() {
    for(auto& e : vec_layer_contener){
        delete e;
    }
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
            if(!vec_layer_contener.empty()){
                vec_layer_contener[i_current_target]->vUpdateEvent(event);
            }
        }
        window->clear();
        if(!vec_layer_contener.empty()){
            vec_layer_contener[i_current_target]->vUpdate(*window);
            window->draw(*vec_layer_contener[i_current_target]);
        }
        window->display();
    }
}

void App::vFirstInit() {


    this->i_current_target=0;

    this->vec_layer_contener.push_back((Layer*)new MenuLayer(*this));
    ((MenuLayer*)vec_layer_contener[0])->vAddSButton("Get Result","result test");
    ((MenuLayer*)vec_layer_contener[0])->vAddSButton("Load image","load image test");
    ((MenuLayer*)vec_layer_contener[0])->vAddSButton("Load model",str_load);

    this->vec_layer_contener.push_back((Layer*)new LoadImage(str_return_to_menu));
    vec_layer_contener[vec_layer_contener.size()-1]->addObservator(this);

}

bool App::executeCommand(std::string &str_command) {
    if(str_command == str_return_to_menu)i_current_target=0;
    else if(str_command == str_load)i_current_target=1;
    printf("App executeCommand %s\n",str_command.c_str());
    return true;
}





