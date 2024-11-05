//
// Created by Sławomir on 05.11.2024.
//

#ifndef FRUITVISION_OBSERVATOR_H
#define FRUITVISION_OBSERVATOR_H
#include <string>

class Observator {
public:
    virtual bool executeCommand(std::string &str_command){return false;}
};


#endif //FRUITVISION_OBSERVATOR_H
