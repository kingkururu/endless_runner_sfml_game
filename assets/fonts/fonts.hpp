//
//  fonts.hpp
//  sfmlgame1
//
//  Created by Sunmyoung Yun on 2024/02/03.
//

#ifndef fonts_hpp
#define fonts_hpp

#include <stdio.h>
#include <string>
#include <iostream> 
#include <SFML/Graphics.hpp>

class TextClass{
public:
    TextClass(sf::Vector2f position, unsigned int size, sf::Color color, const std::string& fontPath, const std::string& testMessage);
    sf::Text* const getText() const { return text; }
    ~TextClass();
    bool const getVisibleState() const { return visibleState; }
    void setVisibleState(bool VisibleState){ visibleState = VisibleState; }

private:
    sf::Vector2f position;
    unsigned const int size;
    sf::Color color;
    sf::Font* font = nullptr; 
    sf::Text* text = nullptr;
    bool visibleState = true;
};


#endif /* fonts_hpp */
