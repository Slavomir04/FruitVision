//
// Created by slawe on 02.01.2025.
//

#ifndef FILEDIALOGWINDOWS_H
#define FILEDIALOGWINDOWS_H

#include "../Interfaces/FileDialog.h"


class FileDialogWindows : public FileDialog {
public:
    std::string strGetFilePath(std::string& str_description, std::vector<std::string> &vec_extensions) override;
private:
    static void vFun(std::string* memory,std::string str_description,std::vector<std::string> vec_extensions);
    static std::string generateFillter(std::string& str_description,std::vector<std::string>& vec_extensions);


};



#endif //FILEDIALOGWINDOWS_H
