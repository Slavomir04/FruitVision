//
// Created by Sławomir on 27.11.2024.
//

#ifndef FRUITVISION_GETRESULT_H
#define FRUITVISION_GETRESULT_H
#include "../Components/TextField/TextField.h"
#include "../Components/SImage/SImage.h"
#include "../Interfaces/Layer.h"
#include "../Interfaces/ImageRecognizer.h"
#include <filesystem>

#define GET_RESULT_COMMAND "get result"

class GetResult : public Layer{
public:
    GetResult(std::string str_return_command,ImageRecognizer* pc_imageRecognizer);
    ~GetResult() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void vUpdate(const sf::RenderWindow &c_Window) override;

    void vUpdateEvent(sf::Event &c_Event) override;

    bool executeCommand(std::string &str_command) override;

    bool setImagePath(std::string &str_image_path);
    bool setModelPath(std::string &str_model_path);

private:
    void vFirstInit();
    void vSetPositions(float fl_window_size_x,float fl_window_size_y);
    void vGetResult();
    void vReset();

    sf::Vector2f vf_image_size={200,200};
    sf::Vector2f vf_informationField_size={200,200};
    sf::Vector2f vf_button_back_size={100,100};
    sf::Vector2f vf_button_get_size={100,100};

    bool b_is_image_loaded;
    bool b_is_model_loaded;

    std::string str_load_image_fail="no model loaded";
    std::string str_load_model_fail="no image loaded";
    std::string str_load_image_ok="image loaded";
    std::string str_load_model_ok="image loaded";


    ImageRecognizer* pc_imageRecognizer;
    sf::Color color_image_background = sf::Color::Green;
    const int i_index_of_informationField=0;
    const int i_index_of_button_back=1;
    const int i_index_of_button_get=2;
    const int i_index_of_image=3;



    std::string str_return_command;


};


#endif //FRUITVISION_GETRESULT_H
