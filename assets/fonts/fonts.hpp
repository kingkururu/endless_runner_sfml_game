//
//  fonts.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#ifndef fonts_hpp
#define fonts_hpp

#include <stdio.h>
#include <string>
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <stdexcept>

class TextClass{
public:
    explicit TextClass(sf::Vector2f position, unsigned int size, sf::Color color, const std::string& fontPath, const std::string& testMessage);
    sf::Text* const getText() const { return text; }
    ~TextClass();
    bool const getVisibleState() const { return visibleState; }
    void setVisibleState(bool VisibleState){ visibleState = VisibleState; }
    void updateText(const std::string& newText); 

private:
    sf::Vector2f position;
    unsigned const int size;
    sf::Color color;
    sf::Font* font = nullptr; 
    sf::Text* text = nullptr;
    bool visibleState = true;
};


#endif /* fonts_hpp */
