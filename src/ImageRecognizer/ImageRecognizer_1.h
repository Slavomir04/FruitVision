//
// Created by slawe on 01.12.2024.
//


#ifndef FRUITVISION_IMAGERECOGNIZER_1_H
#define FRUITVISION_IMAGERECOGNIZER_1_H
#include "../Interfaces/ImageRecognizer.h"



class ImageRecognizer_1 : ImageRecognizer{
public:
    ImageRecognizer_1();

    ~ImageRecognizer_1();

private:
    std::vector<std::pair<std::string, double>> vecGetResult() override;

    bool vLoadModel(std::string str_adres) override;

    bool vLoadImage(std::string str_adres) override;


};



#endif //IMAGERECOGNIZERTEST_H
