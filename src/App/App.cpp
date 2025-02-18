//
// Created by Sławomir on 05.11.2024.
//

#include "App.h"



App::App(int i_window_size_x, int i_window_size_y, std::string str_name) {
    this->window = new sf::RenderWindow(sf::VideoMode(i_window_size_x, i_window_size_y), str_name);
    this->window->setFramerateLimit(FRAME_RATE);
    bool flag_init = true;
    this->window->setActive(false);
    std::thread t_load_screen([&flag_init,this]() {
        animateWhileFlag(window,flag_init);
    });
    vFirstInit();
    flag_init = false;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    t_load_screen.join();
    this->window->setActive(true);
}
App::~App() {
    for(auto& e : vec_layer_contener){
        delete e;
    }
    delete window;
    delete imageRecognizer;
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
    SettingsReader reader;
    std::string path = SETTINGS_PATH;

    reader.read(path);

    imageRecognizer = nullptr;

    window->setVisible(false);
    bool b_flag = true;
    std::thread t([&b_flag]() {
        while(b_flag) {
            std::cout<<"Loading ... Be Patience"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        std::cout<<"Done"<<std::endl;
    });
    imageRecognizer = (ImageRecognizer*)new ImageRecognizer_1();
    b_flag = false;
    t.join();
    window->setVisible(true);

    this->i_current_target=0;

    this->vec_layer_contener.push_back((Layer*)new MenuLayer());
    vec_layer_contener[i_index_menu]->addObservator(this);
    std::string str_key;
    std::string str_get_result = "Get Result"; reader.vOverrideValueIfExists(str_get_result,(str_key=PREFIX_MENU+std::to_string(0)));
    std::string str_load_image = "Load image"; reader.vOverrideValueIfExists(str_load_image,(str_key=PREFIX_MENU+std::to_string(1)));
    std::string str_load_model = "Load model"; reader.vOverrideValueIfExists(str_load_model,(str_key=PREFIX_MENU+std::to_string(2)));

    ((MenuLayer*)vec_layer_contener[i_index_menu])->vAddSButton(str_get_result,comm::str_go_get_result);
    ((MenuLayer*)vec_layer_contener[i_index_menu])->vAddSButton(str_load_image,comm::str_go_load_image);
    ((MenuLayer*)vec_layer_contener[i_index_menu])->vAddSButton(str_load_model, comm::str_go_load_model);

    this->vec_layer_contener.push_back((Layer*)new GetResult(comm::str_return_to_menu,imageRecognizer,reader));
    vec_layer_contener[i_index_getresult]->addObservator(this);

    this->vec_layer_contener.push_back((Layer*)new LoadImage(comm::str_return_to_menu,imageRecognizer,reader));
    vec_layer_contener[i_index_loadimage]->addObservator(this);

    this->vec_layer_contener.push_back((Layer*)new LoadModel(comm::str_return_to_menu,imageRecognizer,reader));
    vec_layer_contener[i_index_loadmodel]->addObservator(this);
}


bool App::executeCommand(std::string &str_command) {
    if(str_command == comm::str_return_to_menu)i_current_target=i_index_menu;
    else if(str_command == comm::str_go_load_model)i_current_target=i_index_loadmodel;
    else if(str_command == comm::str_go_load_image)i_current_target=i_index_loadimage;
    else if(str_command == comm::str_go_get_result)i_current_target=i_index_getresult;
    return true;
}

void App::animateWhileFlag(sf::RenderWindow* window,bool& flag) {
    window->setActive(true);
    float fl_size_ratio = 1;
    TextField text_field(window->getSize().x*fl_size_ratio,window->getSize().y*fl_size_ratio);
    text_field.vSetFocusable(false);
    text_field.vSetAlign(TextField::Center);
    text_field.vSetCharacterSize(80);
    float fl_pos_x = (window->getSize().x - text_field.vfGetSize().x)/2;
    float fl_pos_y = (window->getSize().y - text_field.vfGetSize().y)/2;
    text_field.vSetPosition(fl_pos_x,fl_pos_y);

    std::string str_prefix = "Loading";
    std::string str_suffix = "";

    sf::Clock clock;
    sf::Time last_time = clock.restart();

    while (window->isOpen() && flag) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        if (clock.getElapsedTime()-last_time >= sf::seconds(0.3)) {
            str_suffix+=".";
            if (str_suffix.length()>3)str_suffix="";
            last_time = clock.getElapsedTime();
        }
        text_field.vSetText(str_prefix+str_suffix);
        window->clear(sf::Color::Black);
        window->draw(text_field);
        window->display();
    }


    window->setActive(false);
}







