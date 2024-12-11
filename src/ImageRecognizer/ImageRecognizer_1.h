//
// Created by slawe on 01.12.2024.
//


#ifndef FRUITVISION_IMAGERECOGNIZER_1_H
#define FRUITVISION_IMAGERECOGNIZER_1_H
#include "../Interfaces/ImageRecognizer.h"
#include <filesystem>


class ImageRecognizer_1 : ImageRecognizer{
public:
    ImageRecognizer_1();
    ~ImageRecognizer_1();

    std::string strGetModelPath() override;
    std::string strGetImagePath() override;
    std::vector<std::pair<std::string, double>> vecGetResult() override;
    bool vLoadModel(std::string str_adres) override;
    bool vLoadImage(std::string str_adres) override;
    bool vLoadModel(std::wstring str_adres) override;
    bool vLoadImage(std::wstring str_adres) override;

private:
    std::string str_path_model;
    std::string str_path_image;
    bool isLoadedModel = false;
    bool isLoadedImage = false;
};



#endif //IMAGERECOGNIZERTEST_H
