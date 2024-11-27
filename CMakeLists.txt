
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
)
set(SFML_STATIC_LIBRARIES TRUE)




set(WHERE_SFML D:/Programownie/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1)

set(SFML_DIR ${WHERE_SFML}/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(${WHERE_SFML}/include/SFML)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)


include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)


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
        src/Components/SImage/SImage.cpp
        src/Components/SImage/SImage.h
)


target_link_libraries(test gtest_main)
target_link_libraries(test sfml-system sfml-window sfml-graphics sfml-audio)
add_test(NAME test COMMAND test)