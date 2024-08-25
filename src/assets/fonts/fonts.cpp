//
//  fonts.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "fonts.hpp"

TextClass::TextClass(sf::Vector2f position, unsigned int size, sf::Color color, const std::string& fontPath, const std::string& testMessage)
    : position(position), size(size), color(color), font(std::make_unique<sf::Font>()), text(std::make_unique<sf::Text>()) {

    try{   
        if (!font->loadFromFile(fontPath)) {
            throw std::runtime_error("error loading font from file: " + fontPath);
        }
        text->setFont(*font);
        text->setCharacterSize(size);
        text->setFillColor(color);
        text->setPosition(position);
        text->setString(testMessage);
    }

    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        visibleState = false;
    }
}

void TextClass::updateText(const std::string& newText){
    if(text){
        text->setString(newText); 
    } else {
        std::cerr << "text not initialized" << std::endl; 
    }
}