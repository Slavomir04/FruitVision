//
// Created by Sławomir on 27.11.2024.
//

#ifndef FRUITVISION_GETRESULT_H
#define FRUITVISION_GETRESULT_H
#include "../Components/TextField/TextField.h"
#include "../Components/SImage/SImage.h"
#include "../Interfaces/Layer.h"
#include "../Interfaces/ImageRecognizer.h"
#include <algorithm>
#include <filesystem>



class GetResult : public Layer{
public:
    GetResult(std::string str_return_command,ImageRecognizer* pc_imageRecognizer);
    ~GetResult() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void vUpdate(const sf::RenderWindow &c_Window) override;

    void vUpdateEvent(sf::Event &c_Event) override;

    bool executeCommand(std::string &str_command) override;



private:
    void vFirstInit();
    void vSetPositions(float fl_window_size_x,float fl_window_size_y);
    void vGetResult();
    void vReset();
    void vCheckResult(std::vector<std::pair<std::string, double>>& vec_result);

    const int i_index_of_informationField=0;
    const int i_index_of_button_back=1;
    const int i_index_of_button_get=2;
    const int i_index_of_image=3;


    float fl_scale_shift = 0.1f;
    sf::Vector2f vf_scale_image={0.3f, 0.3f};
    sf::Vector2f vf_scale_informationField={0.3f, 0.1f};
    sf::Vector2f vf_scale_buttons={0.1f,0.1f};


    bool b_is_image_loaded;
    bool b_is_model_loaded;
    bool b_unknown_error_occur = "unknown error";
    std::string str_get_result_prefix="Results:";
    std::string str_unknown_error="unknown error";
    std::string str_load_image_fail="no image loaded";
    std::string str_load_model_fail="no model loaded";
    std::string str_load_image_ok="image loaded";
    std::string str_load_model_ok="model loaded";
    std::string str_text_button_back = "back";
    std::string str_text_button_get = "get";


    sf::Color color_image_background = sf::Color::Green;
    std::string str_return_command;

    bool b_resized;
    bool b_first_init;
    ImageRecognizer* pc_imageRecognizer;
};


#endif //FRUITVISION_GETRESULT_H
