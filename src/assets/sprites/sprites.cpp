//
//  sprites.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "sprites.hpp"

Sprite::Sprite(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture)
    : position(position), scale(scale), texture(texture), spriteCreated(std::make_unique<sf::Sprite>()), visibleState(true) {
    try {
        if (auto tex = texture.lock()) {  
            sf::Vector2u textureSize = tex->getSize(); 
            if (!textureSize.x || !textureSize.y) {
                throw std::runtime_error("Loaded texture has size 0");
            }

            spriteCreated->setTexture(*tex); 
            spriteCreated->setPosition(position);
            spriteCreated->setScale(scale);
        } else {
            throw std::runtime_error("Texture is no longer available");
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        visibleState = false;
    }
}

void NonStatic::setRects(int animNum){
    try{
        if(animNum < 0 || animNum > indexMax){
            throw std::out_of_range("Animation index out of range. ");
        }

        spriteCreated->setTextureRect(animationRects[animNum]);    
    }
    
    catch(const std::exception& e){
        std::cerr << "error in setting texture: " << e.what() << "the indexmax is: "<< indexMax << "the current index is "<< animNum << std::endl;
    }
}

void NonStatic::changeAnimation(float deltaTime) {
    try {
        elapsedTime += deltaTime;
        if (elapsedTime > Constants::ANIMATION_CHANGE_TIME) {
            ++currentIndex; 

            if (currentIndex >= indexMax) {
                currentIndex = 0; 
            }
            setRects(currentIndex); 
            elapsedTime = 0.0;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in changing animation, current index: " << currentIndex << " - " << e.what() << std::endl;
    }
}

void NonStatic::updatePos() {
    try {
        if (position.y > Constants::SCREEN_HEIGHT + Constants::SPRITE_OUT_OF_BOUNDS_OFFSET 
        || position.x > Constants::SCREEN_WIDTH + Constants::SPRITE_OUT_OF_BOUNDS_OFFSET 
        || position.y < 0 - Constants::SPRITE_OUT_OF_BOUNDS_OFFSET
        || position.x < 0 - Constants::SPRITE_OUT_OF_BOUNDS_OFFSET) {
            setVisibleState(false);
        }

        spriteCreated->setPosition(position); 
    }
    catch (const std::exception& e) {
        std::cerr << "Error in updating position: " << e.what() << std::endl;
    }
}

void NonStatic::changePosition(sf::Vector2f newPos){
    position = newPos; 
}

// Player class
void Player::updatePlayer(sf::Vector2f newPos) {
    if (position.x > Constants::SCREEN_WIDTH) {
        position.x = Constants::SCREEN_WIDTH - Constants::SPRITE_OUT_OF_BOUNDS_ADJUSTMENT;
    } else if (position.x < -Constants::SPRITE_OUT_OF_BOUNDS_OFFSET) {
        position.x = -Constants::SPRITE_OUT_OF_BOUNDS_OFFSET;
    }

    changePosition(newPos); 
}

// void Obstacle::updateObstacle(sf::Vector2f newPos){
//     position = newPos;  
// }

void Obstacle::setDirectionVector(float angle){
    float angleRad = angle * (3.14f / 180.f);
    directionVector.x = std::cos(angleRad);
    directionVector.y = std::sin(angleRad);

    std::cout << directionVector.x << " and " << directionVector.y << std::endl; 
}

//bullet class
// void Bullet::updateBullet(sf::Vector2f newPos){
//     position = newPos;  
// }

void Bullet::setDirectionVector(sf::Vector2i projectionPos){
    directionVector = static_cast<sf::Vector2f>(projectionPos) - position;
        
        // Calculate the length of the direction vector (distance to the target)
        float length = std::sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
    
         if (length == 0) 
            return; 

        directionVector.x /= length;
        directionVector.y /= length;
}