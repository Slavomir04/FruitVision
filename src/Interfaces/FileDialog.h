//
// Created by slawe on 02.01.2025.
//

#ifndef FILEDIALOG_H
#define FILEDIALOG_H
#include <string>
#include <vector>

class FileDialog{
    public:
    ///
    /// @param str_description this is prefix of current filter
    /// @param vec_extensions this is vector of strings, all of strings are only name of extension, example: *.extension -> string = "extension"
    /// @return
    virtual std::string strGetFilePath(std::string& str_description,std::vector<std::string>& vec_extensions){return {};};
};


#endif //FILEDIALOG_H
