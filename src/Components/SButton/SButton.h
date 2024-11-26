//
// Created by Sławomir on 19.11.2024.
//

#ifndef FRUITVISION_SBUTTON_H
#define FRUITVISION_SBUTTON_H
#include "../Button.h"
#define DEFAULT_OUTLINE_THICKNES 4
#define DEFAULT_CHARACTER_SIZE 30

#define DEFAULT_FONT_PATH "../src/Resources/font.otf"
#define FONT_CANNOT_LOAD_TEXT "nie mozna zaladowac czcionki! "
#define DEFAULT_COMMAND "clicked"
class SButton : public Button{
public:
    SButton(float fl_size_x, float fl_size_y, std::string str_text,int i_default_character_size,float
    fl_default_thicknes,std::string str_font_path);
    SButton(float fl_size_x,float fl_size_y,std::string str_text);
    SButton(float fl_size_x,float fl_size_y,std::string str_text,int i_character_size,float fl_default_thicknes);

    bool bIsMouseOver(float fl_mouse_x, float fl_mouse_y) override;
    bool bIsClicked(sf::Event &event) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void vSetPosition(float fl_x, float fl_y) override;
    void vSetSize(float fl_x, float fl_y) override;
    virtual void vSetText(const std::string &text);
    void vSetOutlineThicknes(float fl_thicknes);
    void vSetOnClickCommand(const std::string &str_command);
    void vSetCharacterSize(int i_character_size);
    sf::Vector2f vfGetSize() override;
    sf::Vector2f vfGetPosition() override;
    std::string getText();
    void vUpdate(const sf::RenderWindow &c_Window) override;
    void vUpdateEvent(sf::Event &c_Event) override;
    void vSetFont(const sf::Font& newFont);
    void vSetFocusable(bool b_focusable);
    void vSetColorPressed(const sf::Color &color);
    void vSetColorFocused(const sf::Color &color);
    void vSetColorNoFocused(const sf::Color &color);
    void vSetColorOutline(const sf::Color &color);
    void vSetColorCharacter(const sf::Color &color);


     sf::Color color_default_pressed = sf::Color::Green;
     sf::Color color_default_focused = sf::Color(128,64,255);
     sf::Color color_default_nofocused = sf::Color::White;
     sf::Color color_outline = sf::Color::Cyan;
     sf::Color color_character = sf::Color::Black;

protected:

    virtual void vFirstInit();
    void vShape_update();
    virtual void vMoveText(float fl_div_x, float fl_div_y);
    void vSetPositionText(float fl_x, float fl_y);
    void vText_center();
    bool bLoadFont(std::string str_path);
    void vTrimTextSize();

    sf::RectangleShape c_shape;
    sf::Text c_text;
    sf::Font c_font;
    bool b_is_focused;
    bool b_focusable;
    const std::string str_font_path;
    const int i_default_character_size;
    float fl_outline_thicknes;
    std::string str_command;
};


#endif //FRUITVISION_SBUTTON_H
