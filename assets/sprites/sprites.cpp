//
//  sprites.cpp
//  sfmlgame1
//
//  Created by Sunmyoung Yun on 2024/01/07.
//
#include "sprites.hpp"

//base class (sprite)
Sprite::Sprite(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : position(position), size(size), skin(new sf::Texture), spriteCreated(new sf::Sprite){
    
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

void Sprite::updatePos(){
    if (position.x > GameComponents.screenWidth + 80) {
        position.x = GameComponents.screenWidth + 80;
    } else if (position.x < - 10) {
        position.x = - 10;
    }
    if (position.y > GameComponents.screenHeight + 80) 
        setVisibleState(false); 

    spriteCreated->setPosition(position);
}

void Background::updateBackground(){

}

//Player class
void Player::updatePlayer(){
    if(FlagEvents.aPressed){
        position.x -= speed * GameComponents.deltaTime;
    }
    if(FlagEvents.dPressed){
        position.x += speed * GameComponents.deltaTime;
    }
    if(GameEvents.playerDead){
        spriteCreated->setColor(sf::Color(200, 0, 0));
    }
    updatePos();
}

//Enemy class
void Rain::updateRain(){
    position.y += speed * GameComponents.deltaTime;
    updatePos();
}

void Coin::updateCoin(){
    position.y += speed * GameComponents.deltaTime;
    updatePos();
}

void Lightning::updateLightning(){
    
}

// void Heart::updateHeart(){
//     if(GameScore.playerHit == )
// }