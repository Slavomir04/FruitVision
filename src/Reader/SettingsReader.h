//
// Created by slawe on 17.12.2024.
//

#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
class SettingsReader {
public:
    SettingsReader();
    SettingsReader(std::map<std::string,std::string> &map);
    ~SettingsReader();
    void read(std::string &path);
    void vOverrideValueIfExists(std::string& str,std::string& key);
    std::string getValue(const std::string &key);

private:
    std::pair<std::string,std::string> parse(std::string line);

    std::map<std::string, std::string> map;
    std::vector<std::string> tokens;

};



#endif //SETTINGSREADER_H
