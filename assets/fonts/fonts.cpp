//
//  fonts.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "fonts.hpp"

TextClass::TextClass(sf::Vector2f position, unsigned int size, sf::Color color, const std::string& fontPath, const std::string& testMessage)
    : position(position), size(size), color(color), font(new sf::Font), text(new sf::Text) {
            
        if (!font->loadFromFile(fontPath)) {
            // Handle error loading font
            std::cerr << "Error loading font from file: " << fontPath << std::endl;
            return;
        }
    text->setFont(*font);
    text->setCharacterSize(size);
    text->setFillColor(color);
    text->setPosition(position);
    text->setString(testMessage);
}

TextClass::~TextClass() {
    delete font;
    font = nullptr;
    delete text;
    text = nullptr;
}

void TextClass::updateText(const std::string& newText){
    text->setString(newText); 
}