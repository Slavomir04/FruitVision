//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_APP_H
#define FRUITVISION_APP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Interfaces/Layer.h"
#include "../Layers/MenuLayer.h"
#include "../Layers/GetResult.h"
#include "../Layers/LoadModel.h"
#include "../Layers/LoadImage.h"
#include "../ImageRecognizer/ImageRecognizer_1.h"

#define FRAME_RATE 60
class App : Observator{
public:
    App(int i_window_size_x,int i_window_size_y,std::string str_name);
    ~App();
    void vStart();
private:
    void vFirstInit();
    bool executeCommand(std::string &str_command) override;

    sf::RenderWindow* window;
    std::string str_name;
    std::vector<Layer*> vec_layer_contener;
    int i_current_target;

    const int i_index_menu=0;
    const int i_index_getresult=1;
    const int i_index_loadimage=2;
    const int i_index_loadmodel=3;

    const std::string str_return_to_menu = "menu";
    const std::string str_get_result = "get result";
    const std::string str_load_model = "load model";
    const std::string str_load_image = "load image";

    ImageRecognizer* imageRecognizer;
};


#endif //FRUITVISION_APP_H
