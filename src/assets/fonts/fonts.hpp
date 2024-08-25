//
//  fonts.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#ifndef fonts_hpp
#define fonts_hpp

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <iostream> 
#include <stdexcept>

class TextClass{
public:
    explicit TextClass(sf::Vector2f position, unsigned int size, sf::Color color, const std::string& fontPath, const std::string& testMessage);
    sf::Text& getText() { return *text; }
    const sf::Text& getText() const { return *text; }

    ~TextClass() = default;
    bool const getVisibleState() const { return visibleState; }
    void setVisibleState(bool VisibleState){ visibleState = VisibleState; }
    void updateText(const std::string& newText); 

private:
    sf::Vector2f position {};
    unsigned const int size {};
    sf::Color color {};
    std::unique_ptr<sf::Font> font; 
    std::unique_ptr<sf::Text> text;
    bool visibleState = true;
};


#endif /* fonts_hpp */
