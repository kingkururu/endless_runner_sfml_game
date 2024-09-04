//
//  physics.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//
#pragma once

#ifndef physics_hpp
#define physics_hpp

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <functional> 
#include "sprites.hpp"

namespace physics{

    constexpr float gravity = 9.8;

    // falling objects
    sf::Vector2f freeFall(float deltaTime, float speed, sf::Vector2f originalPo);
    sf::Vector2f follow(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration, const sf::Vector2f& direction); 

    // moving player
    sf::Vector2f moveLeft(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration = 1.0); 
    sf::Vector2f moveRight(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration = 1.0);
    sf::Vector2f moveUp(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration = 1.0);
    sf::Vector2f moveDown(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration = 1.0);
    sf::Vector2f jump(); 

    // collisions
        //circle-shaped sprite 
    bool circleCollision(const Sprite& sprite1, float radius1, const Sprite& sprite2, float radius2);
        //axis aligned bounding box
    bool boundingBoxCollsion(const sf::Vector2f &position1, const sf::Vector2f &size1, const sf::Vector2f &position2, const sf::Vector2f &size2);
        //pixel perfect 
    bool pixelPerfectCollision(const std::shared_ptr<sf::Uint8[]> &bitmask1, const sf::Vector2f &position1, const sf::Vector2f &size1, const std::shared_ptr<sf::Uint8[]> &bitmask2, const sf::Vector2f &position2, const sf::Vector2f &size2);  
    
    bool circleCollisionHelper(const Sprite& sprite1, const Sprite& sprite2);
    bool boundingBoxCollisionHelper(const Sprite& sprite1, const Sprite& sprite2);  
    bool pixelPerfectCollisionHelper(const NonStatic& sprite1, const NonStatic& sprite2);

    //check templates 
    template<typename SpriteType1, typename SpriteType2, typename CollisionFunc>
    bool checkCollisions(const std::vector<std::unique_ptr<SpriteType1>>& firstGroup, 
                         const std::vector<std::unique_ptr<SpriteType2>>& secondGroup,
                         const CollisionFunc& collisionFunc) {
        // Iterate over each sprite in the first group
        for (const auto& item1 : firstGroup) {
            // Iterate over each sprite in the second group
            for (const auto& item2 : secondGroup) {
                // Check for collision using the provided function
                if (collisionFunc(*item1, *item2)) {
                    return true; // Collision detected
                }
            }
        }
        return false; // No collisions detected
    }

    template<typename SpriteType1, typename SpriteType2, typename CollisionFunc>
    bool checkCollisions(const std::unique_ptr<SpriteType1>& firstGroup, 
                         const std::vector<std::unique_ptr<SpriteType2>>& Group,
                         const CollisionFunc& collisionFunc) {
        
            for (const auto& item2 : Group) {
                if (collisionFunc(*firstGroup, *item2)) {
                    return true; // Collision detected
                }
            }
        return false; // No collisions detected
    }
                
    }

#endif /* game_hpp */
