#include <iostream>
#include <fstream>
#include "src/App/App.h"
#include <vector>
#include "src/Components/SButton/SButton.h"
#include "src/Components/TextField/TextField.h"
#include "src/Components/SImage/SImage.h"
#include <filesystem>

using namespace std;



int main()
{
    float alpha = 0.80f;
   App app(sf::VideoMode::getDesktopMode().width * alpha,sf::VideoMode::getDesktopMode().height * alpha,"App");
   app.vStart();



    return 0;
}
