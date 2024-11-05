//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_IMAGERECOGNIZER_H
#define FRUITVISION_IMAGERECOGNIZER_H

#include <string>

class ImageRecognizer {
public:
    virtual std::pair<std::string,double>* pcGetResult();
    virtual int iGetSize();
    virtual bool vLoadModel(std::string str_adres);
    virtual bool vLoadImage(std::string str_adres);

private:

};


#endif //FRUITVISION_IMAGERECOGNIZER_H
