
cmake_minimum_required(VERSION 3.26)
project(FruitVision)

set(CMAKE_CXX_STANDARD 20)



if(WIN32)
    add_definitions(-D_WIN32)
    set(SOURCES
            src/FileDialog/FileDialogWindows.cpp
            src/FileDialog/FileDialogWindows.h
    )
elseif(UNIX AND NOT APPLE)
    add_definitions(-D__linux__)
    #set(SOURCES FileDialogLinux.h FileDialogLinux.cpp)
elseif(APPLE)
    add_definitions(-D__APPLE__)
    #set(SOURCES FileDialogMac.h FileDialogMac.cpp)
endif()


add_executable(FruitVision main.cpp
        src/App/App.cpp
        src/App/App.h

        src/Interfaces/Observator.h
        src/Interfaces/Observable.h
        src/Interfaces/Component.h
        src/Interfaces/Layer.h
        src/Interfaces/ImageRecognizer.h
        src/Interfaces/Updateable.h
        src/Interfaces/Commands.h

        src/Components/Button.h
        src/Components/TextField/TextField.cpp
        src/Components/TextField/TextField.h
        src/Components/SButton/SButton.cpp
        src/Components/SButton/SButton.h

        src/Layers/MenuLayer.cpp
        src/Layers/MenuLayer.h
        src/Layers/LoadModel.cpp
        src/Layers/LoadModel.h
        src/Layers/LoadImage.cpp
        src/Layers/LoadImage.h
        src/Layers/GetResult.cpp
        src/Layers/GetResult.h

        src/Components/SImage/SImage.cpp
        src/Components/SImage/SImage.h

        src/ImageRecognizer/ImageRecognizer_1.cpp
        src/ImageRecognizer/ImageRecognizer_1.h
        src/Reader/SettingsReader.cpp
        src/Reader/SettingsReader.h


        src/Interfaces/FileDialog.h
        src/FileDialog/FileDialogFactory.h
)
add_executable(unit_tests tests/test.cpp

        src/Interfaces/Observator.h
        src/Interfaces/Observable.h
        src/Interfaces/Component.h
        src/Interfaces/Layer.h
        src/Interfaces/ImageRecognizer.h
        src/Interfaces/Updateable.h
        src/Interfaces/Commands.h

        src/Components/Button.h
        src/Components/TextField/TextField.cpp
        src/Components/TextField/TextField.h

        src/Components/SButton/SButton.cpp
        src/Components/SButton/SButton.h

        src/Components/SImage/SImage.cpp
        src/Components/SImage/SImage.h
)
target_sources(FruitVision PRIVATE ${SOURCES})
target_sources(unit_tests PRIVATE ${SOURCES})
set(BUILD_SHARED_LIBS OFF)
include(FetchContent)

#sfml
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio network QUIET)

if (NOT SFML_FOUND)
    message(STATUS "SFML not found, fetching from GitHub...")
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG       2.6.1
    )
    FetchContent_MakeAvailable(SFML)

endif()
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)








#python
find_package(Python3 3.10 EXACT REQUIRED COMPONENTS Interpreter Development)

include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES})

add_custom_target(InstallPythonPackages ALL
        COMMAND ${Python3_EXECUTABLE} -m pip install --upgrade pip
        COMMAND ${Python3_EXECUTABLE} -m pip install python-dev-tools tensorflow==2.18.0 pillow==11.0.0 numpy==2.0.2
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Installing Python dependencies..."
)




#find_package(PythonLibs REQUIRED)
#include_directories(${PYTHON_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})


#google test

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

#tests
enable_testing()
target_link_libraries(unit_tests PRIVATE gtest_main)
target_link_libraries(unit_tests PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(unit_tests PRIVATE ${PYTHON_LIBRARIES})
add_test(
        NAME unit_tests
        COMMAND unit_tests
)



