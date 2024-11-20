//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_IMAGERECOGNIZER_H
#define FRUITVISION_IMAGERECOGNIZER_H

#include <string>
#include <vector>

class ImageRecognizer {
public:
    virtual std::vector<std::pair<std::string,double>> vecGetResult();
    virtual bool vLoadModel(std::string str_adres);
    virtual bool vLoadImage(std::string str_adres);

private:

};


#endif //FRUITVISION_IMAGERECOGNIZER_H
