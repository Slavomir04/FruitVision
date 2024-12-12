
cmake_minimum_required(VERSION 3.26)
project(FruitVision)

set(CMAKE_CXX_STANDARD 17)


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
)
add_executable(test
        tests/test.cpp
        src/Interfaces/Observator.h
        src/Interfaces/Observable.h
        src/App/App.cpp
        src/App/App.h
        src/Interfaces/Component.h
        src/Interfaces/Layer.h
        src/Interfaces/ImageRecognizer.h
        src/Interfaces/Updateable.h
        src/Components/Button.h
        src/Components/TextField/TextField.cpp
        src/Components/TextField/TextField.h
        src/Components/SButton/SButton.cpp
        src/Components/SButton/SButton.h
        src/Interfaces/Commands.h
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
)

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



#google test

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)
target_link_libraries(test PRIVATE gtest_main)
target_link_libraries(test PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
add_test(NAME test COMMAND test)


#python

#find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
#include_directories(${Python3_INCLUDE_DIRS})
#link_directories(${Python3_LIBRARY_DIRS})
#target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES})

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})



