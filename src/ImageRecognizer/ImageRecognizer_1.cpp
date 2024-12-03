//
// Created by slawe on 01.12.2024.
//

#include "ImageRecognizer_1.h"

ImageRecognizer_1::ImageRecognizer_1() {}

ImageRecognizer_1::~ImageRecognizer_1() {

}

std::vector<std::pair<std::string, double>> ImageRecognizer_1::vecGetResult() {
    return {{"tu powinien byc wynik z pythona",99.9}};
}

bool ImageRecognizer_1::vLoadModel(std::string str_adres) {
    return true;
}

bool ImageRecognizer_1::vLoadImage(std::string str_adres) {
    return true;
}
