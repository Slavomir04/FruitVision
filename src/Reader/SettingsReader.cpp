//
// Created by slawe on 17.12.2024.
//

#include "SettingsReader.h"

#include <map>


SettingsReader::SettingsReader() {
}

SettingsReader::SettingsReader(std::map<std::string, std::string> &map) :map(map){
}

SettingsReader::~SettingsReader() {
}

void SettingsReader::read(std::string &path) {
    std::ifstream file(path);
    if(file.is_open()) {
        std::string line;
        while(std::getline(file, line)) {
            std::pair<std::string, std::string> pair_from_line = parse(line);
            if(!pair_from_line.first.empty() && !pair_from_line.second.empty())
                map[pair_from_line.first] = pair_from_line.second;
        }
    }else throw std::runtime_error("Could not open file "+path);
}

void SettingsReader::vOverrideValueIfExists(std::string &str, std::string &key) {
    if(map.find(key) != map.end())str=map[key];
}

std::string SettingsReader::getValue(const std::string &key) {
    if(map.find(key) != map.end())return map[key];
    else return "";
}

std::pair<std::string, std::string> SettingsReader::parse(std::string line) {
    std::stringstream ss;
    std::pair<std::string, std::string> result;
    bool first = false;
    int index=0;
    while(index < line.size() && line[index] == ' ')index++;
    while(index<line.size()){
        if(!first && line[index]!=' ') {
            ss<<line[index];
        }else {
            if(!first) {
                result.first = result.first = ss.str();
                ss = std::stringstream();
                first = true;
            }else{
                ss<<line[index];
            }
        }
        index++;
    }
    if(!ss.str().empty()) {
        result.second = ss.str();
    }

    return result;
}
