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

    this->vec_layer_contener.push_back((Layer*)new MenuLayer(*this,window->getSize().x*0.2,window->getSize().x*0.1));
    ((MenuLayer*)vec_layer_contener[i_index_menu])->vAddSButton("Get Result",str_get_result);
    ((MenuLayer*)vec_layer_contener[i_index_menu])->vAddSButton("Load image",str_load_image);
    ((MenuLayer*)vec_layer_contener[i_index_menu])->vAddSButton("Load model", str_load_model);

    this->vec_layer_contener.push_back((Layer*)new LoadModel(str_return_to_menu));
    vec_layer_contener[i_index_getresult]->addObservator(this);

    this->vec_layer_contener.push_back((Layer*)new LoadImage(str_return_to_menu));
    vec_layer_contener[i_index_loadimage]->addObservator(this);

    this->vec_layer_contener.push_back((Layer*)new LoadModel(str_return_to_menu));
    vec_layer_contener[i_index_loadmodel]->addObservator(this);
}


bool App::executeCommand(std::string &str_command) {
    if(str_command == str_return_to_menu)i_current_target=i_index_menu;
    else if(str_command == str_load_model)i_current_target=i_index_loadmodel;
    else if(str_command == str_load_image)i_current_target=i_index_loadimage;
    else if(str_command == str_get_result)i_current_target=i_index_getresult;
    printf("App executeCommand %s\n",str_command.c_str());
    return true;
}







