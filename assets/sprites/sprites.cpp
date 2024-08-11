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

//Player class
void Player::updatePlayer(){
    if(FlagEvents.aPressed){
        position.x -= speed * GameComponents.deltaTime;
    }
    if(FlagEvents.dPressed){
        position.x += speed * GameComponents.deltaTime;
    }
    
    if(GameEvents.playerWin){
        spriteCreated->setScale(sf::Vector2f{1.0f, 1.0f});
        spriteCreated->rotate(1.0f);
        
        unsigned int color[3];
        for (int i = 0; i < 3; i ++){
            color[i] = rand() % 255;
        }
        spriteCreated->setColor(sf::Color(color[0],color[1],color[2]));
        
    } else if(GameEvents.playerDead){
        spriteCreated->setColor(sf::Color(200, 0, 0));
    }
    updatePos();
}

//Enemy class
void Rain::updateRain(sf::Vector2f playerPos){
    position.y += speed * GameComponents.deltaTime;
    updatePos();
}
