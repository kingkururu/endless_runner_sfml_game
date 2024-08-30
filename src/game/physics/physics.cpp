//
//  physics.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "physics.hpp"

namespace physics{
    
    // collisions 
    bool circleCollision(const sf::Sprite& sprite1, float radius1, const sf::Sprite& sprite2, float radius2) {
        // Get the positions of the sprites
        sf::Vector2f pos1 = sprite1.getPosition();
        sf::Vector2f pos2 = sprite2.getPosition();

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
}