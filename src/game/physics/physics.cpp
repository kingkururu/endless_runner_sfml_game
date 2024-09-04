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

    // collisions 
    bool circleCollision(const Sprite& sprite1, float radius1, const Sprite& sprite2, float radius2) {
        // Get the positions of the sprites
        sf::Vector2f pos1 = sprite1.returnSpritesShape().getPosition();
        sf::Vector2f pos2 = sprite2.returnSpritesShape().getPosition(); 

        // Calculate the distance between the centers of the circles
        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;
        float distanceSquared = dx * dx + dy * dy;

        // Calculate the sum of the radii
        float radiusSum = radius1 + radius2;
        float radiusSumSquared = radiusSum * radiusSum;

        // Check if the distance squared is less than or equal to the sum of radii squared
        return distanceSquared <= radiusSumSquared;
    }

    bool boundingBoxCollsion(const sf::Vector2f &position1, 
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

    bool pixelPerfectCollision(const std::shared_ptr<sf::Uint8[]> &bitmask1, 
                               const sf::Vector2f &position1, 
                               const sf::Vector2f &size1,
                               const std::shared_ptr<sf::Uint8[]> &bitmask2, 
                               const sf::Vector2f &position2, 
                               const sf::Vector2f &size2) {

        // Calculate the bounding box of the overlapping area
        float xOverlapStart = std::max(position1.x, position2.x);
        float yOverlapStart = std::max(position1.y, position2.y);
        float xOverlapEnd = std::min(position1.x + size1.x, position2.x + size2.x);
        float yOverlapEnd = std::min(position1.y + size1.y, position2.y + size2.y);

        // If there's no overlap, return false
        if (xOverlapStart >= xOverlapEnd || yOverlapStart >= yOverlapEnd) {
            return false;
        }

        // Iterate over the overlapping area
        for (int y = yOverlapStart; y < yOverlapEnd; ++y) {
            for (int x = xOverlapStart; x < xOverlapEnd; ++x) {
                // Calculate local coordinates within each bitmask
                int x1 = x - static_cast<int>(position1.x);
                int y1 = y - static_cast<int>(position1.y);
                int x2 = x - static_cast<int>(position2.x);
                int y2 = y - static_cast<int>(position2.y);

                // Check the corresponding bits in both bitmasks
                bool pixel1 = bitmask1[y1 * static_cast<int>(size1.x) + x1] != 0;
                bool pixel2 = bitmask2[y2 * static_cast<int>(size2.x) + x2] != 0;

                // If both pixels are set, we have a collision
                if (pixel1 && pixel2) {
                    return true;
                }
            }
        }

        return false; // No collision detected
    }

    //defult (spritve vs sprites)
    bool checkCollisions(const std::unique_ptr<Sprite>& sprite1, 
                     const std::vector<std::unique_ptr<Sprite>>& sprites,
                     const std::function<bool(const Sprite&, const Sprite&)>& collisionFunc) {

    // Iterate over all sprites to check for collisions
    for (const auto& sprite : sprites) {
        // Use the provided collision detection function
        if (collisionFunc(*sprite1, *sprite)) {
            return true; // Collision detected
        }
    }

    return false; // No collision detected
    }

    // player vs obstacles
    bool checkCollisions(const std::unique_ptr<Player>& playerSprite, 
                     const std::vector<std::unique_ptr<Obstacle>>& obstacleSprites,
                     const std::function<bool(const Sprite&, const Sprite&)>& collisionFunc) {

    // Iterate over all sprites to check for collisions
    for (const auto& sprite : obstacleSprites) {
        // Use the provided collision detection function
        if (collisionFunc(*playerSprite, *sprite)) {
            return true; // Collision detected
        }
    }

    return false; // No collision detected
    }

    // bullet vs obstacles













    // Helper function for circle collision
    bool circleCollisionHelper(const Sprite& sprite1, const Sprite& sprite2) {
        float radius1 = sprite1.returnSpritesShape().getGlobalBounds().width / 2.0f;
        float radius2 = sprite2.returnSpritesShape().getGlobalBounds().width / 2.0f;

        return physics::circleCollision(sprite1, radius1, sprite2, radius2);
    }

    bool boundingBoxCollisionHelper(const Sprite& sprite1, const Sprite& sprite2) {    
    sf::FloatRect bounds1 = sprite1.returnSpritesShape().getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.returnSpritesShape().getGlobalBounds(); 

    sf::Vector2f position1(bounds1.left, bounds1.top);
    sf::Vector2f size1(bounds1.width, bounds1.height);
    sf::Vector2f position2(bounds2.left, bounds2.top);
    sf::Vector2f size2(bounds2.width, bounds2.height);

    // Call the existing boundingBoxCollsion
    return boundingBoxCollsion(position1, size1, position2, size2);
    }

    bool pixelPerfectCollisionHelper(const NonStatic& obj1, const NonStatic& obj2) {
    auto bitmask1 = obj1.getBitmask();
    auto bitmask2 = obj2.getBitmask();

    if (!bitmask1 || !bitmask2) {
        std::cerr << "Error: Missing bitmask for one or both sprites in pixel-perfect collision check." << std::endl;
        return false;
    }

    sf::Vector2f pos1 = obj1.returnSpritesShape().getPosition();
    sf::Vector2f size1 = { obj1.returnSpritesShape().getGlobalBounds().width, obj1.returnSpritesShape().getGlobalBounds().height };

    sf::Vector2f pos2 = obj2.returnSpritesShape().getPosition();
    sf::Vector2f size2 = { obj2.returnSpritesShape().getGlobalBounds().width, obj2.returnSpritesShape().getGlobalBounds().height };

    return physics::pixelPerfectCollision(bitmask1, pos1, size1, bitmask2, pos2, size2);
    }

}