//
// Created by Sławomir on 05.11.2024.
//



#ifndef FRUITVISION_OBSERVABLE_H
#define FRUITVISION_OBSERVABLE_H

#include <vector>
#include "Observator.h"

class Observable {
public:

    bool addObservator(Observator* pc_observator){
        bool b_Contains = !containsObservator(pc_observator);
        if(b_Contains)
            vec_Observators_contener.push_back(pc_observator);
        return b_Contains;
    }
    bool containsObservator(Observator* pc_observator){
        return itFindElement(pc_observator)!=vec_Observators_contener.end();
    }
    bool removeObservator(Observator* pc_observator){
        auto itFounded = itFindElement(pc_observator);
        if(itFounded != vec_Observators_contener.end()){
            vec_Observators_contener.erase(itFounded);
            return true;
        }else{
            return false;
        }
    }
    void provideCommand(std::string &command){
        for(auto pc_e = vec_Observators_contener.begin(); pc_e!=vec_Observators_contener.end(); pc_e++){
            (*pc_e)->executeCommand(command);
        }
    }

private:

    std::vector<Observator*>::iterator itFindElement(Observator* pc_observator){
        for(auto pc_e = vec_Observators_contener.begin(); pc_e < vec_Observators_contener.end(); pc_e++)
        {
            if((*pc_e) == pc_observator){
                return pc_e;
            }
        }
        return vec_Observators_contener.end();
    }

    std::vector<Observator*> vec_Observators_contener;
};


#endif //FRUITVISION_OBSERVABLE_H
