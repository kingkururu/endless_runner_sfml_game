//
//  sprites.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "sprites.hpp"

// base class (sprite)
// Sprite::Sprite(sf::Vector2f position, sf::Vector2f scale, const sf::Texture texture) 
//     : position(position), scale(scale), texture(texture), spriteCreated(new sf::Sprite), visibleState(true) {
//     try {

//         sf::Vector2u textureSize = texture->getSize();
//         if (!textureSize.x || !textureSize.y) {
//             throw std::runtime_error("Loaded texture has size 0");
//         }
    
//         spriteCreated->setTexture(*texture);
//         spriteCreated->setPosition(position);
//         spriteCreated->setScale(scale);
//     }
//     catch (const std::exception& e) {
//         std::cerr << e.what() << std::endl;
//         visibleState = false;
//     }
// }
Sprite::Sprite(sf::Vector2f position, sf::Vector2f scale, std::shared_ptr<sf::Texture> texture)
    : position(position), scale(scale), texture(texture), spriteCreated(std::make_unique<sf::Sprite>()), visibleState(true) {
    try {
        if (texture) { 
            sf::Vector2u textureSize = texture->getSize();
            if (!textureSize.x || !textureSize.y) {
                throw std::runtime_error("Loaded texture has size 0");
            }

            spriteCreated->setTexture(*texture);
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

void NonStatic::updatePos() {
    try {
        if (position.x > Constants::SCREEN_WIDTH) {
            position.x = Constants::SCREEN_WIDTH;
        } else if (position.x < -Constants::SPRITE_OUT_OF_BOUNDS_OFFSET) {
            position.x = -Constants::SPRITE_OUT_OF_BOUNDS_OFFSET;
        }
        if (position.y > Constants::SCREEN_HEIGHT + Constants::SPRITE_OUT_OF_BOUNDS_ADJUSTMENT) {
            setVisibleState(false);
        }
        spriteCreated->setPosition(position);
    }
    catch (const std::exception& e) {
        std::cerr << "Error in updating position: " << e.what() << std::endl;
    }
}

void NonStatic::setRects(int animNum){
    try{
        if(animNum < 0 || animNum >= animationRects.size()){
            throw std::out_of_range("Animation index out of range. ");
        }

        spriteCreated->setTextureRect(animationRects[animNum]);    
    }
    
    catch(const std::exception& e){
        std::cerr << "error in setting texture rectangle: " << e.what() << std::endl;
    }
    
}

void NonStatic::changeAnimation(float deltaTime) {
    try {
        elapsedTime += deltaTime;
        if (elapsedTime > Constants::ANIMATION_CHANGE_TIME) {
            if (currentIndex >= indexMax) {
                currentIndex = -1;
            }
            ++currentIndex;
            setRects(currentIndex);
        }
        
        if (elapsedTime > visibleDuration) {
            setVisibleState(false);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in changing animation: " << e.what() << std::endl;
    }
}

// Player class
void Player::updatePlayer() {
    try {
        updatePos();
    }
    catch (std::exception& e) {
        std::cerr << "Error in updating player: " << e.what() << std::endl;
    }
}

//obstacle class
void Obstacle::updateObstacle(){
    try{
        updatePos();
    }

    catch(std::exception& e){
        std::cerr << "error in updating obstacle: " << e.what() << std::endl;
    }
}

//bullet class
void Bullet::updateBullet(){
    try{
        updatePos();
    }

    catch(std::exception& e){
        std::cerr << "error in updating obstacle: " << e.what() << std::endl;
    }
}

// /Liniear movement ( free fall )
// void Rain::updateRain(){
//     speed += gravity * GameComponents.deltaTime;
//     position.y += speed * GameComponents.deltaTime;
//     updatePos();
// }

