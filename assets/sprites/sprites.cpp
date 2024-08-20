//
//  sprites.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//
#include "sprites.hpp"

// //base class (sprite)
Sprite::Sprite(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : position(position), size(size), skin(new sf::Texture), spriteCreated(new sf::Sprite), visibleState(true) {
    if(!skin->loadFromFile(texturePath)){
        std::cerr << "Erorr in loading sprite texture from: " << texturePath << std::endl;
        return;
    }
    spriteCreated->setTexture(*skin);
    spriteCreated->setPosition(position);
    spriteCreated->setScale(size);
}

Sprite::~Sprite(){
    delete skin;
    delete spriteCreated;
}

void NonStatic::updatePos(){
  if (position.x > GameComponents.screenWidth - 57) {
        position.x = GameComponents.screenWidth - 57;
    } else if (position.x < - 10) {
        position.x = - 10;
    }
    if (position.y > GameComponents.screenHeight + 80) 
        setVisibleState(false); 

    spriteCreated->setPosition(position);
}

void NonStatic::setRects(int animNum){
    spriteCreated->setTextureRect(animationRects[animNum]); 
}

void NonStatic::changeAnimation(float deltaTime){
    elapsedTime += deltaTime;
    if(elapsedTime > changeAnimTime){
        if(currentIndex >= indexMax)
        currentIndex = -1;
    ++currentIndex;
    setRects(currentIndex); 
    }
    
    if(elapsedTime > visibleDuration)
        setVisibleState(false); 
}

// //Player class
void Player::updatePlayer(){
    // if(FlagEvents.aPressed){
    //     position.x -= speed * GameComponents.deltaTime;
    // }
    // if(FlagEvents.dPressed){
    //     position.x += speed * GameComponents.deltaTime;
    // }
    // if(GameEvents.playerDead){
    //     spriteCreated->setColor(sf::Color(200, 0, 0));
    // }
    updatePos();
}

void Obstacle::updateObstacle(){




    updatePos(); 
}



// /Liniear movement ( free fall )
// void Rain::updateRain(){
//     speed += gravity * GameComponents.deltaTime;
//     position.y += speed * GameComponents.deltaTime;
//     updatePos();
// }

