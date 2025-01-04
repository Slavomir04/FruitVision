//
// Created by slawe on 02.01.2025.
//

#include "FileDialogWindows.h"
#include <windows.h>
#include <commdlg.h>
#include <thread>
#include <sstream>
std::string FileDialogWindows::strGetFilePath(std::string& str_description, std::vector<std::string> &vec_extensions) {
    std::string str_result;
    std::thread t(FileDialogWindows::vFun,&str_result,str_description, vec_extensions);
    t.join();
    return str_result;
}

std::wstring CreateFileFilter(const std::wstring& description, const std::vector<std::wstring>& extensions) {
    std::wstringstream filterStream;

    // Dodaj opis
    filterStream << description << L" (";
    for (size_t i = 0; i < extensions.size(); ++i) {
        filterStream << L"*." << extensions[i];
        if (i + 1 < extensions.size()) {
            filterStream << L";";
        }
    }
    filterStream << L")\0";

    // Dodaj rozszerzenia do filtru
    for (const auto& ext : extensions) {
        filterStream << L"*." << ext << L";";
    }
    filterStream.seekp(-1, std::ios_base::end); // Usuń ostatni średnik
    filterStream << L"\0";

    return filterStream.str();
}

void FileDialogWindows::vFun(std::string* memory, std::string str_description, std::vector<std::string> vec_extensions) {
    char fileName[MAX_PATH] = "";
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = sizeof(fileName);
    ofn.lpstrFilter = FileDialogWindows::generateFillter(str_description,vec_extensions).c_str();
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    *memory = GetOpenFileName(&ofn) ? fileName : "";
}


std::string FileDialogWindows::generateFillter(std::string& str_description, std::vector<std::string> &vec_extensions) {
    std::stringstream ss;
    ss<<str_description;
    if(!vec_extensions.empty()) {
        ss<<'(';
        for(auto& e : vec_extensions)ss<<"*."<<e<<' ';
        ss<<')';
        ss<<'\0';

        for(int i=0; i<vec_extensions.size(); i++) {
            if(i<vec_extensions.size()-2) {
                ss<<"*."<<vec_extensions[i]<<';';
            }else ss<<"*."<<vec_extensions[i];
        }
    }else ss<<'\0'<<"*.*";
    ss<<'\0';
    return ss.str();
}


