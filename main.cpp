#include <iostream>
#include "src/App/App.h"
#include <vector>
#include "src/Components/SButton/SButton.h"
#include "src/Components/TextField/TextField.h"
#include "src/Components/SImage/SImage.h"
#include <filesystem>
using namespace std;
int main()
{

   App app(700,700,"App");
   app.vStart();



    /*
    SImage sImage(150,150);
    sImage.bLoadImage("D:\\Programownie\\Clion projekty\\FruitVision\\src\\Resources\\mango-szt.png");
    sImage.vSetPosition(200,200);
    sImage.vSetBackgroundColor(sf::Color::Yellow);
    sf::RenderWindow*  window = new sf::RenderWindow(sf::VideoMode(700, 700), "123",sf::Style::Titlebar | sf::Style::Close);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            sImage.vUpdateEvent(event);
        }
        sImage.vUpdate(*window);
        window->clear();
        window->draw(sImage);
        window->display();
    }
    delete window;

     */
    return 0;
}
