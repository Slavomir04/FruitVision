
cmake_minimum_required(VERSION 3.26)
project(FruitVision)

set(CMAKE_CXX_STANDARD 17)

add_executable(FruitVision main.cpp
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
        src/Components/TextField/TextField.h)
set(SFML_STATIC_LIBRARIES TRUE)



set(WHERE_SFML D:/Programownie/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1)

set(SFML_DIR ${WHERE_SFML}/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(${WHERE_SFML}/include/SFML)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)