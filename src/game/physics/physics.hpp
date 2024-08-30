//
//  physics.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//
#ifndef physics_hpp
#define physics_hpp

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <SFML/Graphics.hpp>

namespace physics{
    constexpr float gravity = 9.8;

    void freeFall();
    void rightToLeftFall(); 

    // moving player
    void moveLeft();
    void moveRight();

    // collisions
        //circle-shaped sprite 
    bool circleCollision(const sf::Sprite& sprite1, float radius1, const sf::Sprite& sprite2, float radius2);
        //axis aligned bounding box
    bool boundingBoxCollsion(const sf::Vector2f &position1, const sf::Vector2f &size1, const sf::Vector2f &position2, const sf::Vector2f &size2);
        //pixel perfect 
    bool pixelPerfectCollision(const std::shared_ptr<sf::Uint8[]> &bitmask1, const sf::Vector2f &position1, const sf::Vector2f &size1, const std::shared_ptr<sf::Uint8[]> &bitmask2, const sf::Vector2f &position2, const sf::Vector2f &size2);  
}

#endif /* game_hpp */
