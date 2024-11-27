#include <iostream>
#include "src/App/App.h"
#include <vector>
#include "src/Components/SButton/SButton.h"
#include "src/Components/TextField/TextField.h"
#include <filesystem>
using namespace std;
int main()
{

   App app(700,700,"App");
   app.vStart();

    /*
    sf::RectangleShape rec;
    sf::Texture texture;

    rec.setSize(sf::Vector2f(100,100));
    texture.loadFromFile("D:/Programownie/Clion projekty/FruitVision/src/Resources/1.png");
    sf::RenderWindow*  window = new sf::RenderWindow(sf::VideoMode(700, 700), "123",sf::Style::Titlebar | sf::Style::Close);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

        }
        window->clear();

        window->display();
    }
    delete window;
     */
    return 0;
}
