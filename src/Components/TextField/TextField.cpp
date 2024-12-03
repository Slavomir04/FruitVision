//
// Created by Sławomir on 05.11.2024.
//


#include "TextField.h"
TextField::TextField(float fl_size_x, float fl_size_y) : SButton(fl_size_x,fl_size_y,""),
                                                         i_maximum_length(MAXIMUM_LENGTH), i_maxiumum_unicode(MAXIMUM_UNICODE) {
    vFirstInit();
}

TextField::TextField(float fl_size_x, float fl_size_y, int i_maximum_length, int i_maximum_unicode) : SButton(fl_size_x,fl_size_y,""),i_maximum_length(i_maximum_length),i_maxiumum_unicode(i_maximum_unicode){
    vFirstInit();
}

TextField::TextField(float fl_size_x, float fl_size_y, int i_maximum_length, int i_maximum_unicode,
                     std::string &str_font_path) : SButton(fl_size_x,fl_size_y,""),i_maximum_length(i_maximum_length),i_maxiumum_unicode(i_maximum_unicode){
    vFirstInit();
    if (!bLoadFont(str_font_path)) {
        throw std::runtime_error(FONT_CANNOT_LOAD_TEXT + str_font_path);
    }else{
        c_text.setFont(c_font);
    }
}






void TextField::vSetSize(float fl_x, float fl_y) {
    c_shape.setSize(sf::Vector2f(fl_x,fl_y));
}
void TextField::vSetText(const std::string &text){
    c_text.setString(text);
    vAlignText(); //reposition text
    vTrimTextSize(); //resize
    vAlignText(); //again reposition text
}
void TextField::vSetAlign(TextField::TextAlign_type alignType) {
    this->e_text_align =alignType;
    vAlignText();
}



void TextField::vUpdate(const sf::RenderWindow &c_Window) {
    v2f_mouse_position = c_Window.mapPixelToCoords(sf::Mouse::getPosition(c_Window));
    vShape_update();
}

void TextField::vUpdateEvent(sf::Event &c_Event) {
    //mouse
    if(bIsClicked(c_Event)){
        b_is_focused= true;
    }else if(c_Event.type == sf::Event::MouseButtonPressed){
        b_is_focused= false;
    }


    //keyboard
    if(b_is_focused && c_Event.type == sf::Event::KeyPressed){

        if(c_Event.text.unicode <= i_maxiumum_unicode){

            std::string str_new_text = c_text.getString();

            char c_asciiChar = cGetCharFromEvent(c_Event);

            if(c_Event.key.code == sf::Keyboard::BackSpace){
                if(c_Event.key.alt){
                    str_new_text ="";
                }
                if (!str_new_text.empty()) {
                    str_new_text.pop_back();
                }

            }else if(c_Event.key.control && c_Event.key.code == sf::Keyboard::V){
                str_new_text+=sf::Clipboard::getString();
                if(str_new_text.size()>=i_maximum_length)str_new_text = str_new_text.substr(0,i_maximum_length-1);
            }else if(str_new_text.size()<i_maximum_length && c_asciiChar != '\0'){
                    str_new_text.push_back(c_asciiChar);
            }
            vSetText(str_new_text);
        }


    }
}








void TextField::vText_left() {
    float alpha_x = c_text.getCharacterSize();
    float fl_x = c_shape.getPosition().x + c_text.getLetterSpacing()+alpha_x;
    float fl_y = c_shape.getPosition().y + (c_shape.getSize().y - c_text.getGlobalBounds().height)/2.0f;
    c_text.setPosition(fl_x,fl_y);
}

void TextField::vText_right() {

}







char TextField::cGetCharFromEvent(sf::Event &c_Event) {
    sf::Event::KeyEvent keyEvent = c_Event.key;
    switch (keyEvent.code) {
        case sf::Keyboard::A:
            return keyEvent.shift ? 'A' : 'a';
        case sf::Keyboard::B:
            return keyEvent.shift ? 'B' : 'b';
        case sf::Keyboard::C:
            return keyEvent.shift ? 'C' : 'c';
        case sf::Keyboard::D:
            return keyEvent.shift ? 'D' : 'd';
        case sf::Keyboard::E:
            return keyEvent.shift ? 'E' : 'e';
        case sf::Keyboard::F:
            return keyEvent.shift ? 'F' : 'f';
        case sf::Keyboard::G:
            return keyEvent.shift ? 'G' : 'g';
        case sf::Keyboard::H:
            return keyEvent.shift ? 'H' : 'h';
        case sf::Keyboard::I:
            return keyEvent.shift ? 'I' : 'i';
        case sf::Keyboard::J:
            return keyEvent.shift ? 'J' : 'j';
        case sf::Keyboard::K:
            return keyEvent.shift ? 'K' : 'k';
        case sf::Keyboard::L:
            return keyEvent.shift ? 'L' : 'l';
        case sf::Keyboard::M:
            return keyEvent.shift ? 'M' : 'm';
        case sf::Keyboard::N:
            return keyEvent.shift ? 'N' : 'n';
        case sf::Keyboard::O:
            return keyEvent.shift ? 'O' : 'o';
        case sf::Keyboard::P:
            return keyEvent.shift ? 'P' : 'p';
        case sf::Keyboard::Q:
            return keyEvent.shift ? 'Q' : 'q';
        case sf::Keyboard::R:
            return keyEvent.shift ? 'R' : 'r';
        case sf::Keyboard::S:
            return keyEvent.shift ? 'S' : 's';
        case sf::Keyboard::T:
            return keyEvent.shift ? 'T' : 't';
        case sf::Keyboard::U:
            return keyEvent.shift ? 'U' : 'u';
        case sf::Keyboard::V:
            return keyEvent.shift ? 'V' : 'v';
        case sf::Keyboard::W:
            return keyEvent.shift ? 'W' : 'w';
        case sf::Keyboard::X:
            return keyEvent.shift ? 'X' : 'x';
        case sf::Keyboard::Y:
            return keyEvent.shift ? 'Y' : 'y';
        case sf::Keyboard::Z:
            return keyEvent.shift ? 'Z' : 'z';

            // Obsługuje cyfry oraz znaki specjalne
        case sf::Keyboard::Num1:
            return keyEvent.shift ? '!' : '1';
        case sf::Keyboard::Num2:
            return keyEvent.shift ? '@' : '2';
        case sf::Keyboard::Num3:
            return keyEvent.shift ? '#' : '3';
        case sf::Keyboard::Num4:
            return keyEvent.shift ? '$' : '4';
        case sf::Keyboard::Num5:
            return keyEvent.shift ? '%' : '5';
        case sf::Keyboard::Num6:
            return keyEvent.shift ? '^' : '6';
        case sf::Keyboard::Num7:
            return keyEvent.shift ? '&' : '7';
        case sf::Keyboard::Num8:
            return keyEvent.shift ? '*' : '8';
        case sf::Keyboard::Num9:
            return keyEvent.shift ? '(' : '9';
        case sf::Keyboard::Num0:
            return keyEvent.shift ? ')' : '0';

            // Obsługuje znaki specjalne
        case sf::Keyboard::Comma:
            return keyEvent.shift ? '<' : ',';
        case sf::Keyboard::Period:
            return keyEvent.shift ? '>' : '.';
        case sf::Keyboard::Slash:
            return keyEvent.shift ? '?' : '/';
        case sf::Keyboard::Backslash:
            return keyEvent.shift ? '|' : '\\';

            // Obsługuje spację
        case sf::Keyboard::Space:
            return ' ';

            // Obsługuje Enter
        case sf::Keyboard::Enter:
            return '\n';

            // Obsługuje dodatkowe znaki specjalne
        case sf::Keyboard::Semicolon:  // ;
            return keyEvent.shift ? ':' : ';';
        case sf::Keyboard::Quote:  // '
            return keyEvent.shift ? '"' : '\'';
        case sf::Keyboard::LBracket:  // [
            return keyEvent.shift ? '{' : '[';
        case sf::Keyboard::RBracket:  // ]
            return keyEvent.shift ? '}' : ']';


            // Jeśli naciśnięty jest inny klawisz
        default:
            return '\0';  // Zwraca '\0' jeśli klawisz nie jest obsługiwany
    }
}

void TextField::vFirstInit() {
    e_text_align = Left;
    vShape_update();
}

void TextField::vAlignText() {
    switch (e_text_align) {
        case Left:
            vText_left();
            break;
        case Right:
            vText_right();
            break;
        case Center:
            vText_center();
            break;
        default:
            vText_left();
            break;
    }
}































