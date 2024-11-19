//
// Created by slawe on 17.11.2024.
//
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

#include "../src/Components/TextField/TextField.h"

TEST(firsttest,testing) {
    EXPECT_EQ(1+2,3);
}

TEST(Components,TextField) {
    TextField text_field(100,300);
    text_field.setText("Hello World");
    text_field.setPosition(50,50);

    EXPECT_EQ(text_field.isMouseOver(51,51),true);
    EXPECT_EQ(text_field.isMouseOver(50,50),true);
    EXPECT_EQ(text_field.isMouseOver(50,49),false);
    EXPECT_EQ(text_field.isMouseOver(49,50),false);
    EXPECT_EQ(text_field.isMouseOver(49,49),false);

    EXPECT_EQ(text_field.isMouseOver(149,349),true);
    EXPECT_EQ(text_field.isMouseOver(151,349),false);
    EXPECT_EQ(text_field.isMouseOver(149,351),false);
    EXPECT_EQ(text_field.isMouseOver(151,351),false);


    EXPECT_EQ(text_field.isMouseOver(75,150),true);


    sf::Event simulatedEvent;
    simulatedEvent.type = sf::Event::MouseButtonPressed;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 100;
    simulatedEvent.mouseButton.y = 100;
    EXPECT_EQ(text_field.isClicked(simulatedEvent),true);

    simulatedEvent.type = sf::Event::MouseButtonPressed;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 100;
    simulatedEvent.mouseButton.y = 0;
    EXPECT_EQ(text_field.isClicked(simulatedEvent),false);

    simulatedEvent.type = sf::Event::MouseButtonPressed;
    simulatedEvent.mouseButton.button = sf::Mouse::Right;
    simulatedEvent.mouseButton.x = 100;
    simulatedEvent.mouseButton.y = 100;
    EXPECT_EQ(text_field.isClicked(simulatedEvent),true);

    simulatedEvent.type = sf::Event::MouseButtonReleased;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 100;
    simulatedEvent.mouseButton.y = 100;
    EXPECT_EQ(text_field.isClicked(simulatedEvent),true);


    simulatedEvent.mouseButton.x = 150;
    simulatedEvent.mouseButton.y = 150;

    simulatedEvent.type = sf::Event::KeyPressed;
    simulatedEvent.key.code = sf::Keyboard::A;
    text_field.updateEvent(simulatedEvent);
    simulatedEvent.key.code = sf::Keyboard::B;
    text_field.updateEvent(simulatedEvent);
    simulatedEvent.key.code = sf::Keyboard::C;
    text_field.updateEvent(simulatedEvent);
    simulatedEvent.key.code = sf::Keyboard::D;
    text_field.updateEvent(simulatedEvent);

    EXPECT_EQ(text_field.getText(),"abcd");
    simulatedEvent.key.code = sf::Keyboard::BackSpace;
    text_field.updateEvent(simulatedEvent);
    EXPECT_EQ(text_field.getText(),"abc");

    simulatedEvent.mouseButton.x = 0;
    simulatedEvent.mouseButton.y = 0;
    text_field.updateEvent(simulatedEvent);
    EXPECT_EQ(text_field.getText(),"abc");




}
