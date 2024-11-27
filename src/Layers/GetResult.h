//
// Created by Sławomir on 27.11.2024.
//

#ifndef FRUITVISION_GETRESULT_H
#define FRUITVISION_GETRESULT_H
#include "../Components/TextField/TextField.h"
#include "../Interfaces/Layer.h"
#include "../Interfaces/ImageRecognizer.h"
#include <filesystem>


class GetResult : public Layer{
public:
    GetResult(std::string str_return_command);
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

    sf::Vector2f vf_textField_size={200,200};
    sf::Vector2f vf_button_back_size={100,100};
    sf::Vector2f vf_button_load_size={100,100};
    sf::Vector2f vf_Image_load_size={100,100};

    ImageRecognizer* pc_imageRecognizer;
    sf::Color color_image_background = sf::Color::Green;
    sf::Texture texture_image;
    sf::RectangleShape rec_image;
    const int i_index_of_informationField=0;
    const int i_index_of_button_back=2;
    const int i_index_of_button_load=3;

    std::string str_return_command;


};


#endif //FRUITVISION_GETRESULT_H
