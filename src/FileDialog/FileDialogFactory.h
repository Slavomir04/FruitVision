//
// Created by slawe on 04.01.2025.
//

#ifndef FILEDIALOGFACTORY_H
#define FILEDIALOGFACTORY_H

#include "../Interfaces/FileDialog.h"

#if defined(_WIN32)
    #include "FileDialogWindows.h"
#elif defined(__linux__)
   // #include "FileDialogLinux.h"
#elif defined(__APPLE__)

#endif

class FileDialogFactory {
public:
    static FileDialog* createFileDialog() {
        #if defined(_WIN32)
         return new FileDialogWindows();
        #elif defined(__linux__)
          return nullptr;
        #elif defined(__APPLE__)
          return nullptr;
        #else
           return nullptr;
        #endif
    }

};

#endif //FILEDIALOGFACTORY_H
