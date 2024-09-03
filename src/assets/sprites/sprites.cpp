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

// const sf::Vector2f Sprite::getSpriteSize(){
//     try {
//         if (auto tex = texture.lock()) {  
//             sf::Vector2u textureSize = tex->getSize(); 
//             sf::Vector2f scale = spriteCreated->getScale();
//             sf::Vector2f spriteSize(textureSize.x * scale.x, textureSize.y * scale.y);

//             std::cout << "size is: " << spriteSize.x << "and " << spriteSize.y << std::endl; 
//             return spriteSize;
//         }
//     }

//     catch (const std::exception& e){
//         std::cerr << "failed getting size" << e.what() << std::endl;
//         return {0.0f, 0.0f}; 
//     }
// }

Background::Background(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture) : Static(position, scale, texture) {
    if (auto tex = texture.lock()) {
        spriteCreated2 = std::make_unique<sf::Sprite>(*tex);
        spriteCreated2->setScale(scale);
        spriteCreated2->setPosition(position.x + tex->getSize().x * scale.x, position.y);
    }
}

void Background::updateBackground(float deltaTime, float speed) {
        // Move both background sprites to the left
        spriteCreated->move(-speed * deltaTime, 0);
        spriteCreated2->move(-speed * deltaTime, 0);

        // Reposition sprites when they go off screen
        if (spriteCreated->getPosition().x + spriteCreated->getGlobalBounds().width < 0) {
            spriteCreated->setPosition(spriteCreated2->getPosition().x + spriteCreated2->getGlobalBounds().width, spriteCreated->getPosition().y);
        }
        if (spriteCreated2->getPosition().x + spriteCreated2->getGlobalBounds().width < 0) {
            spriteCreated2->setPosition(spriteCreated->getPosition().x + spriteCreated->getGlobalBounds().width, spriteCreated2->getPosition().y);
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
    if (FlagEvents.sPressed && newPos.y > Constants::SCREEN_HEIGHT - Constants::SPRITE_OUT_OF_BOUNDS_OFFSET){
        newPos.y = Constants::SCREEN_HEIGHT - Constants::SPRITE_OUT_OF_BOUNDS_ADJUSTMENT; 
    }
    if (FlagEvents.wPressed && newPos.y < (Constants::SCREEN_HEIGHT + Constants::SPRITE_OUT_OF_BOUNDS_OFFSET) / 2 ){
        newPos.y = (Constants::SCREEN_HEIGHT + Constants::SPRITE_OUT_OF_BOUNDS_OFFSET) / 2 ; 
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