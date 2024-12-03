//
// Created by slawe on 01.12.2024.
//

#ifndef IMAGERECOGNIZERTEST_H
#define IMAGERECOGNIZERTEST_H
#include "../Interfaces/ImageRecognizer.h"


class ImageRecognizerTest : public ImageRecognizer {
public:
    ImageRecognizerTest() = default;
    std::vector<std::pair<std::string, double>> vecGetResult() override;
    bool vLoadModel(std::string str_adres) override;
    bool vLoadImage(std::string str_adres) override;
private:
};



#endif //IMAGERECOGNIZERTEST_H
