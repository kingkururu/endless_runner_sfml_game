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
        if(animNum < 0 || animNum >= indexMax){
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

// Player class
void Player::updatePlayer() {
    updatePos();
}

//obstacle class
void Obstacle::updateObstacle(){
    updatePos();
}

//bullet class
void Bullet::updateBullet(){
    updatePos();
}