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
    if (position.x > GameComponents.screenWidth - 930) {
        position.x = GameComponents.screenWidth - 930;
    } else if (position.x < - 10) {
        position.x = - 10;
    }
    if (position.y > GameComponents.screenHeight - 430) {
        position.y = GameComponents.screenHeight - 430;
    } else if (position.y < 0) {
        position.y = 0;
    }
    spriteCreated->setPosition(position);
}

//Player class
void Player::updatePlayer(){
    if(FlagEvents.wPressed){
        position.y -= speed * GameComponents.deltaTime;
    }
    if(FlagEvents.aPressed){
        position.x -= speed * GameComponents.deltaTime;
    }
    if(FlagEvents.sPressed){
        position.y += speed * GameComponents.deltaTime;
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
void Enemy::updateEnemy(sf::Vector2f playerPos){
    sf::Vector2f enemyToPlayer = playerPos - position;
    float length = sqrt(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.y * enemyToPlayer.y);
    enemyToPlayer /= length;
    position += enemyToPlayer * speed * GameComponents.deltaTime;
    updatePos();
}

//Bullet class
void Bullet::calculateDirVec(){
    sf::Vector2f direction = static_cast<sf::Vector2f>(GameComponents.mouseClickedPos) - position;
    directionUnit = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
}

void Bullet::updateBullet(){
    position += directionUnit * speed * GameComponents.deltaTime;

    if (position.x > GameComponents.screenWidth || position.x < 0 || position.y > GameComponents.screenHeight || position.y < 0) {
        setVisibleState(false); 
    }
    spriteCreated->setPosition(position);
}



