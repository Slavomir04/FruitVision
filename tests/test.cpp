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
    std::string comm = "command";

    ObservatorTester observatorTester;
    SButton button(100,100,"123");
    button.vSetPosition(0,0);
    button.vSetOnClickCommand(comm);
    button.addObservator(&observatorTester);
    button.vSetOutlineThicknes(0);
    sf::Event event;

    event.mouseButton.x=0;
    event.mouseButton.y=0;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({0,0});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), true);

    observatorTester.vClear();

    event.mouseButton.x=99;
    event.mouseButton.y=99;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({99,99});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), true);
    observatorTester.vClear();

    event.mouseButton.x=110;
    event.mouseButton.y=110;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({110,110});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), false);
    observatorTester.vClear();

    event.mouseButton.x=80;
    event.mouseButton.y=110;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({110,110});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), false);
    observatorTester.vClear();

    event.mouseButton.x=110;
    event.mouseButton.y=80;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({110,110});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), false);
    observatorTester.vClear();

    event.mouseButton.x=-5;
    event.mouseButton.y=-5;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({-5,-5});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), false);
    observatorTester.vClear();

    event.mouseButton.x=-5;
    event.mouseButton.y=10;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({-5,-5});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), false);
    observatorTester.vClear();

    event.mouseButton.x=10;
    event.mouseButton.y=-5;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({-5,-5});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), false);
    observatorTester.vClear();


    button.vSetPosition(250,250);
    button.vSetSize(50,50);

    event.mouseButton.x=260;
    event.mouseButton.y=260;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({260,260});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), true);
    observatorTester.vClear();


    event.mouseButton.x=310;
    event.mouseButton.y=260;
    event.type = sf::Event::MouseButtonReleased;
    button.vSetMousePosition({310,260});
    button.vUpdateEvent(event);
    ASSERT_EQ(observatorTester.bContainsCommand(comm), false);
    observatorTester.vClear();


    SUCCEED()<<"SBUTTON clicking test positive";
}

TEST(Components,TextField){

    TextField textField(100,100);
    textField.vSetPosition(0,0);
    textField.vSetText("");
    sf::Event event;


    event.mouseButton.x=50;
    event.mouseButton.y=50;
    event.type = sf::Event::MouseButtonPressed;
    textField.vSetMousePosition({50,50});
    textField.vSetMousePosition({50,50});
    textField.vUpdateEvent(event);
    event.type = sf::Event::MouseButtonReleased;
    textField.vUpdateEvent(event);



    event.type =sf::Event::TextEntered;
    event.key.code = sf::Keyboard::A;
    event.key.shift= false;
    event.text.unicode = 'a';
    textField.vUpdateEvent(event);
    ASSERT_EQ(textField.getText(),"a");
    textField.vSetText("");


    event.type =sf::Event::TextEntered;
    event.key.code = sf::Keyboard::B;
    event.key.shift= true;
    event.text.unicode = 'B';
    textField.vUpdateEvent(event);
    ASSERT_EQ(textField.getText(),"B");
    textField.vSetText("");

    event.type =sf::Event::TextEntered;
    event.key.shift= true;
    event.key.code = sf::Keyboard::B;
    event.text.unicode = 'B';
    textField.vUpdateEvent(event);
    event.key.code = sf::Keyboard::A;
    event.text.unicode = 'A';
    textField.vUpdateEvent(event);
    event.key.shift= false;
    event.key.code = sf::Keyboard::T;
    event.text.unicode = 't';
    textField.vUpdateEvent(event);
    ASSERT_EQ(textField.getText(),"BAt");
    textField.vSetText("");




    event.type =sf::Event::TextEntered;
    event.key.code = sf::Keyboard::Comma;
    event.key.shift= false;
    event.text.unicode = ',';
    textField.vUpdateEvent(event);
    ASSERT_EQ(textField.getText(),",");
    textField.vSetText("");

    event.type =sf::Event::TextEntered;
    event.key.code = sf::Keyboard::Comma;
    event.key.shift= true;
    event.text.unicode = '<';
    textField.vUpdateEvent(event);
    ASSERT_EQ(textField.getText(),"<");
    textField.vSetText("");

    event.type =sf::Event::TextEntered;
    event.key.code = sf::Keyboard::Period;
    event.key.shift= false;
    event.text.unicode = '.';
    textField.vUpdateEvent(event);
    ASSERT_EQ(textField.getText(),".");
    textField.vSetText("");

    event.type =sf::Event::TextEntered;
    event.key.code = sf::Keyboard::BackSlash;
    event.key.shift= false;
    event.text.unicode = '\\';
    textField.vUpdateEvent(event);
    ASSERT_EQ(textField.getText(),"\\");
    textField.vSetText("");

    SUCCEED()<<"TextField typing test positive";
}






