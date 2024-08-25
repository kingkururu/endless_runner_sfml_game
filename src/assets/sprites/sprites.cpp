//
//  sprites.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "sprites.hpp"
#include "constants.hpp"

using namespace GameData;

// base class (sprite)
Sprite::Sprite(sf::Vector2f position, sf::Vector2f scale, const std::string& texturePath) 
    : position(position), scale(scale), skin(new sf::Texture), spriteCreated(new sf::Sprite), visibleState(true) {
    try {
        if (!skin->loadFromFile(texturePath)) {
            throw std::runtime_error("Error in loading sprite texture from: " + texturePath);
        }

        sf::Vector2u textureSize = skin->getSize();
        if (!textureSize.x || !textureSize.y) {
            throw std::runtime_error("Loaded texture has size 0: " + texturePath);
        }
    
        spriteCreated->setTexture(*skin);
        spriteCreated->setPosition(position);
        spriteCreated->setScale(scale);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        visibleState = false;
    }
}

void NonStatic::updatePos() {
    try {
        if (position.x > GameComponents.screenWidth) {
            position.x = GameComponents.screenWidth;
        } else if (position.x < -Constants::SPRITE_OUT_OF_BOUNDS_OFFSET) {
            position.x = -Constants::SPRITE_OUT_OF_BOUNDS_OFFSET;
        }
        if (position.y > GameComponents.screenHeight + Constants::SPRITE_OUT_OF_BOUNDS_ADJUSTMENT) {
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
        if (FlagEvents.aPressed) {
            position.x -= Constants::PLAYER_SPEED * GameComponents.deltaTime;
        }
        if (FlagEvents.dPressed) {
            position.x += Constants::PLAYER_SPEED * GameComponents.deltaTime;
        }
        if (GameEvents.playerDead) {
            spriteCreated->setColor(Constants::PLAYER_DEAD_COLOR);
        }
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



// /Liniear movement ( free fall )
// void Rain::updateRain(){
//     speed += gravity * GameComponents.deltaTime;
//     position.y += speed * GameComponents.deltaTime;
//     updatePos();
// }

