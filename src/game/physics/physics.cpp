//
//  physics.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "physics.hpp"

namespace physics{
    //falling objects 
    sf::Vector2f freeFall(float deltaTime, float speed, sf::Vector2f originalPos){
        return { originalPos.x, originalPos.y += speed * deltaTime * gravity };
    }

    //object moving in a direction vector
    sf::Vector2f follow(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration, const sf::Vector2f& direction){
         sf::Vector2f movement(direction.x * speed * deltaTime * acceleration, direction.y * speed * deltaTime * acceleration);
        return originalPos + movement;
    }

    //moving x or y positions based on directions
    sf::Vector2f moveLeft(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration){
        return { originalPos.x -= speed * deltaTime * acceleration, originalPos.y };
    }
    sf::Vector2f moveRight(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration){
        return { originalPos.x += speed * deltaTime * acceleration, originalPos.y };
    }
    sf::Vector2f moveUp(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration){
        return { originalPos.x, originalPos.y -= speed * deltaTime * acceleration};
    }
    sf::Vector2f moveDown(float deltaTime, float speed, sf::Vector2f originalPos, float acceleration){
        return { originalPos.x, originalPos.y += speed * deltaTime * acceleration};
    }


    // collisions (circle collision)
    // bool circleCollision(sf::Vector2f pos1, float radius1, sf::Vector2f pos2, float radius2) {
    //     // Calculate the distance between the centers of the circles
    //     float dx = pos1.x - pos2.x;
    //     float dy = pos1.y - pos2.y;
    //     float distanceSquared = dx * dx + dy * dy;

    //     // Calculate the sum of the radii
    //     float radiusSum = radius1 + radius2;
    //     float radiusSumSquared = radiusSum * radiusSum;

    //     // Check if the distance squared is less than or equal to the sum of radii squared
    //     return distanceSquared <= radiusSumSquared;
    // }

    // bounding box collision
    bool boundingBoxCollision(const sf::Vector2f &position1, 
                               const sf::Vector2f &size1,
                               const sf::Vector2f &position2, 
                               const sf::Vector2f &size2) {

        float xOverlapStart = std::max(position1.x, position2.x);
        float yOverlapStart = std::max(position1.y, position2.y);
        float xOverlapEnd = std::min(position1.x + size1.x, position2.x + size2.x);
        float yOverlapEnd = std::min(position1.y + size1.y, position2.y + size2.y);

        if (xOverlapStart >= xOverlapEnd || yOverlapStart >= yOverlapEnd) {
            return false;
        }
        return true; 
    }

    // pixel perfect collition
    bool pixelPerfectCollision(
        const std::shared_ptr<sf::Uint8[]>& bitmask1, const sf::Vector2f& position1, const sf::Vector2f& size1,
        const std::shared_ptr<sf::Uint8[]>& bitmask2, const sf::Vector2f& position2, const sf::Vector2f& size2) {

        // Helper function to get the pixel index in the bitmask
        auto getPixelIndex = [](const sf::Vector2f& size, int x, int y) -> int {
            return (y * static_cast<int>(size.x) + x) * 4; // Each pixel has 4 bytes (RGBA)
        };

        // Calculate the overlapping area between the two objects
        float left = std::max(position1.x, position2.x);
        float top = std::max(position1.y, position2.y);
        float right = std::min(position1.x + size1.x, position2.x + size2.x);
        float bottom = std::min(position1.y + size1.y, position2.y + size2.y);

        // If there is no overlap, return false
        if (left >= right || top >= bottom) {
            return false;
        } 

        // Check each pixel in the overlapping area
        for (int y = static_cast<int>(top); y < static_cast<int>(bottom); ++y) {
            for (int x = static_cast<int>(left); x < static_cast<int>(right); ++x) {
                // Calculate the position in each bitmask
                int x1 = x - static_cast<int>(position1.x);
                int y1 = y - static_cast<int>(position1.y);
                int x2 = x - static_cast<int>(position2.x);
                int y2 = y - static_cast<int>(position2.y);

                // Get the index of the pixel in each bitmask
                int index1 = getPixelIndex(size1, x1, y1);
                int index2 = getPixelIndex(size2, x2, y2);

                // Check if the pixels' values are non-zero (i.e., not transparent)
                if (bitmask1[index1] == 1 && bitmask2[index2] == 1) {
                   // std::cout << "Collision detected at pixel (" << x << ", " << y << ")" << std::endl;
                    return true; // Collision detected
                }
            }
        }
        return false; 
    }

    //bounding box collision helper
    bool boundingBoxCollisionHelper(const NonStatic& sprite1, const NonStatic& sprite2) {    
        // Retrieve global bounds of the entire sprite
        sf::FloatRect bounds1 = sprite1.returnSpritesShape().getGlobalBounds();
        sf::FloatRect bounds2 = sprite2.returnSpritesShape().getGlobalBounds(); 

        // Retrieve the current animation frame (IntRect) for each sprite
        sf::IntRect rect1 = sprite1.getRects();
        sf::IntRect rect2 = sprite2.getRects();

        // Adjust the position using the left and top of the current frame
        sf::Vector2f position1(bounds1.left + rect1.left, bounds1.top + rect1.top);
        sf::Vector2f position2(bounds2.left + rect2.left, bounds2.top + rect2.top);

        // Adjust the size using the width and height of the current frame
        sf::Vector2f size1(static_cast<float>(rect1.width), static_cast<float>(rect1.height));
        sf::Vector2f size2(static_cast<float>(rect2.width), static_cast<float>(rect2.height));

        // Call the existing boundingBoxCollision function with adjusted values
        return boundingBoxCollision(position1, size1, position2, size2);
    }

    //pixel perfect collision helper
    bool pixelPerfectCollisionHelper(const NonStatic& obj1, const NonStatic& obj2) {
        // Retrieve bitmasks for the current animation frame
        auto bitmask1 = obj1.getBitmask(obj1.getCurrIndex());
        auto bitmask2 = obj2.getBitmask(obj2.getCurrIndex());

        // Check if bitmasks are available
        if (!bitmask1 || !bitmask2) {
            std::cerr << "Error: Missing bitmask for one or both sprites in pixel-perfect collision check." << std::endl;
            return false;
        }

        // Retrieve positions and sizes of both objects
        sf::Vector2f position1 = obj1.getSpritePos();
        sf::Vector2f size1 = { static_cast<float>(obj1.getRects().width), static_cast<float>(obj1.getRects().height) }; 
        sf::Vector2f position2 = obj2.getSpritePos();
        sf::Vector2f size2 = { static_cast<float>(obj2.getRects().width), static_cast<float>(obj2.getRects().height) }; 

        // Perform pixel-perfect collision detection
        return pixelPerfectCollision(bitmask1, position1, size1, bitmask2, position2, size2);
    }

}