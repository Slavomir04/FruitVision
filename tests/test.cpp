//
// Created by slawe on 17.11.2024.
//
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

#include "../src/Components/TextField/TextField.h"
#include "../src/Interfaces/Observator.h"
#include "../src/Components/SButton/SButton.h"
TEST(firsttest,testing) {
    EXPECT_EQ(1+2,3);
}
class ObservatorTester : public Observator{
public:
    bool executeCommand(std::string &str_command) override {
        vec_commands_contener.push_back(str_command);
        return true;
    }
    bool bContainsCommand(std::string &str_command){
        for(auto& str : vec_commands_contener)if(str == str_command)return true;
        return false;
    }
    void vClear(){
        vec_commands_contener.clear();
    }
private:
    std::vector<std::string> vec_commands_contener;
};

TEST(Components,SButton){
    ObservatorTester observator_tester;
    std::string str_command = "123456789";

    SButton sButton(100, 100, "", 5, 0.0f);
    sButton.vSetPosition(100,100);
    sButton.vSetOnClickCommand(str_command);
    sButton.addObservator(&observator_tester);


    EXPECT_EQ(sButton.bIsMouseOver(100, 150), true);
    EXPECT_EQ(sButton.bIsMouseOver(-100, 150), false);
    EXPECT_EQ(sButton.bIsMouseOver(100, 450), false);



    sf::Event simulatedEvent;

    simulatedEvent.type = sf::Event::MouseButtonReleased;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 150;
    simulatedEvent.mouseButton.y = 150;
    sButton.vUpdateEvent(simulatedEvent);
    EXPECT_EQ(observator_tester.bContainsCommand(str_command), true);

    observator_tester.vClear();

    simulatedEvent.type = sf::Event::MouseButtonReleased;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 0;
    simulatedEvent.mouseButton.y = 0;
    sButton.vUpdateEvent(simulatedEvent);
    EXPECT_EQ(observator_tester.bContainsCommand(str_command), false);
}



TEST(Components,TextField) {
    TextField text_field(100, 300);
    text_field.vSetText("Hello World");
    text_field.vSetPosition(50, 50);
    text_field.vSetOutlineThicknes(0);

    sf::Event simulatedEvent;

    EXPECT_EQ(text_field.bIsMouseOver(0, 0), false);
    simulatedEvent.type = sf::Event::MouseButtonPressed;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 0;
    simulatedEvent.mouseButton.y = 0;
    text_field.vUpdateEvent(simulatedEvent);
    //on defocused
    EXPECT_EQ(text_field.bIsMouseOver(51, 51), true);
    EXPECT_EQ(text_field.bIsMouseOver(0, 0), false);
    EXPECT_EQ(text_field.bIsMouseOver(500, 500), false);
    EXPECT_EQ(text_field.bIsMouseOver(75, 150), true);


    //mouse

    simulatedEvent.type = sf::Event::MouseButtonReleased;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 100;
    simulatedEvent.mouseButton.y = 100;
    EXPECT_EQ(text_field.bIsClicked(simulatedEvent), true);

    simulatedEvent.type = sf::Event::MouseButtonReleased;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 100;
    simulatedEvent.mouseButton.y = 0;
    EXPECT_EQ(text_field.bIsClicked(simulatedEvent), false);

    simulatedEvent.type = sf::Event::MouseButtonReleased;
    simulatedEvent.mouseButton.button = sf::Mouse::Right;
    simulatedEvent.mouseButton.x = 100;
    simulatedEvent.mouseButton.y = 100;
    EXPECT_EQ(text_field.bIsClicked(simulatedEvent), true);




    //Focus text_field
    simulatedEvent.type = sf::Event::MouseButtonReleased;
    simulatedEvent.mouseButton.button = sf::Mouse::Left;
    simulatedEvent.mouseButton.x = 150;
    simulatedEvent.mouseButton.y = 150;
    text_field.vUpdateEvent(simulatedEvent);

    //clearing text
    text_field.vSetText("");

    //keyboard
    simulatedEvent.type = sf::Event::KeyPressed;
    simulatedEvent.key.code = sf::Keyboard::A;
    simulatedEvent.text.unicode = static_cast<sf::Uint32>('A');
    simulatedEvent.mouseButton.x = 150;
    simulatedEvent.mouseButton.y = 150;
    text_field.vUpdateEvent(simulatedEvent);
    EXPECT_EQ(text_field.getText(),"A");

    simulatedEvent.type = sf::Event::KeyPressed;
    simulatedEvent.key.code = sf::Keyboard::B;
    simulatedEvent.text.unicode = static_cast<sf::Uint32>('b');
    simulatedEvent.mouseButton.x = 150;
    simulatedEvent.mouseButton.y = 150;
    text_field.vUpdateEvent(simulatedEvent);
    EXPECT_EQ(text_field.getText(),"Ab");

    simulatedEvent.type = sf::Event::KeyPressed;
    simulatedEvent.key.code = sf::Keyboard::C;
    simulatedEvent.text.unicode = static_cast<sf::Uint32>('c');
    simulatedEvent.mouseButton.x = 150;
    simulatedEvent.mouseButton.y = 150;
    text_field.vUpdateEvent(simulatedEvent);
    EXPECT_EQ(text_field.getText(),"Abc");

    simulatedEvent.type = sf::Event::KeyPressed;
    simulatedEvent.key.code = sf::Keyboard::D;
    simulatedEvent.text.unicode = static_cast<sf::Uint32>('d');
    simulatedEvent.mouseButton.x = 150;
    simulatedEvent.mouseButton.y = 150;
    text_field.vUpdateEvent(simulatedEvent);
    EXPECT_EQ(text_field.getText(),"Abcd");

    simulatedEvent.type = sf::Event::KeyPressed;
    simulatedEvent.key.code = sf::Keyboard::BackSpace;
    simulatedEvent.text.unicode = 8;
    simulatedEvent.mouseButton.x = 150;
    simulatedEvent.mouseButton.y = 150;
    text_field.vUpdateEvent(simulatedEvent);
    EXPECT_EQ(text_field.getText(),"Abc");

    simulatedEvent.type = sf::Event::KeyPressed;
    simulatedEvent.key.code = sf::Keyboard::Y;
    simulatedEvent.text.unicode = static_cast<sf::Uint32>('y');
    simulatedEvent.mouseButton.x = 0;
    simulatedEvent.mouseButton.y = 0;
    text_field.vUpdateEvent(simulatedEvent);
    EXPECT_EQ(text_field.getText(),"Abc");
}

