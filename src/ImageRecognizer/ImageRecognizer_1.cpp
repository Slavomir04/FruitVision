//
// Created by slawe on 01.12.2024.
//

#include "ImageRecognizer_1.h"

ImageRecognizer_1::ImageRecognizer_1() {}

ImageRecognizer_1::~ImageRecognizer_1() {

}

std::vector<std::pair<std::string, double>> ImageRecognizer_1::vecGetResult() {
    if(isLoadedImage && isLoadedModel)return {{"Poprawny wynik1",99.15},{"Poprawny wynik2",15.15}};
    else{
        std::vector<std::pair<std::string, double>> temp;
        if(!isLoadedImage)temp.push_back({"",(double )ImageRecognizer::ProblemType::NO_IMAGE});
        if(!isLoadedModel)temp.push_back({"",(double )ImageRecognizer::ProblemType::NO_MODEL});
        return temp;
    }
}

bool ImageRecognizer_1::vLoadModel(std::string str_adres) {
    bool temp = std::filesystem::exists(str_adres);
    if(temp)str_path_model=str_adres;
    isLoadedModel = (isLoadedModel || temp);
    return temp;
}

bool ImageRecognizer_1::vLoadImage(std::string str_adres) {
    bool temp = std::filesystem::exists(str_adres);
    if(temp)str_path_image=str_adres;
    isLoadedImage = (isLoadedImage || temp);
    return temp;
}

bool ImageRecognizer_1::vLoadModel(std::wstring str_adres) {
    bool temp = std::filesystem::exists(str_adres);

    isLoadedModel = (isLoadedModel || temp);
    return temp;
}

bool ImageRecognizer_1::vLoadImage(std::wstring str_adres) {
    bool temp = std::filesystem::exists(str_adres);

    isLoadedImage = (isLoadedImage || temp);
    return temp;
}

std::string ImageRecognizer_1::strGetModelPath() {
    return str_path_model;
}

std::string ImageRecognizer_1::strGetImagePath() {
    return str_path_image;
}
