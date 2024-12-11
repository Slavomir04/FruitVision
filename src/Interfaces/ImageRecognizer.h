//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_IMAGERECOGNIZER_H
#define FRUITVISION_IMAGERECOGNIZER_H

#include <string>
#include <vector>

class ImageRecognizer {
public:
    enum ProblemType{
        NO_MODEL = -1,
        NO_IMAGE = -2,
    };

    virtual std::vector<std::pair<std::string,double>> vecGetResult(){return {{"",-1}};}
    virtual bool vLoadModel(std::string str_adres){return false;}
    virtual bool vLoadModel(std::wstring str_adres){return false;}
    virtual bool vLoadImage(std::string str_adres){return false;}
    virtual bool vLoadImage(std::wstring str_adres){return false;}

    virtual std::string strGetModelPath(){return {};}
    virtual std::string strGetImagePath(){return {};}

protected:
};


#endif //FRUITVISION_IMAGERECOGNIZERTEST_H
