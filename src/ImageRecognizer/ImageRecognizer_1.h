//
// Created by slawe on 01.12.2024.
//


#ifndef FRUITVISION_IMAGERECOGNIZER_1_H
#define FRUITVISION_IMAGERECOGNIZER_1_H
#include "../Interfaces/ImageRecognizer.h"
#include <filesystem>
#include <Python.h>
#define IMAGE_RECOGNIZER_PATH "./Resources/"
#define IMAGE_RECOGNIZER_SCRIPT_NAME "fruitRecognizer3.py"
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
    PyObject* callPythonFunction(const std::string& funcName, const std::string& arg1, const std::string& arg2);
    PyObject* callPythonFunction(const std::string& funcName, const std::string& arg1);
    PyObject* callPythonFunctionInternal(const std::string& funcName, const std::vector<std::string>& args);
    std::string str_path_model;
    std::string str_path_image;
    bool isLoadedModel = false;
    bool isLoadedImage = false;
};



#endif //IMAGERECOGNIZERTEST_H
