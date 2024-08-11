//
//  sprites.hpp
//  sfmlgame1
//
//  Created by Sunmyoung Yun on 2024/01/07.
//

#ifndef sprites_hpp
#define sprites_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "global.hpp"
#include <ctime>

class Sprite{
public:
    Sprite(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath);
    virtual ~Sprite();
    void updatePos();
    sf::Vector2f const getSpritePos() const { return position; };
    sf::Sprite const returnSpritesShape(){ return *spriteCreated; }
    bool const getVisibleState() const { return visibleState; }
    void setVisibleState(bool VisibleState){ visibleState = VisibleState; }
    bool const getMoveState() const { return moveState; }
    void setMoveState(bool newState) { moveState = newState; }

protected:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Texture* skin = nullptr;
    sf::Sprite* spriteCreated;
    bool visibleState = true;
    bool moveState = true;
    float speed = 200;
};

//player class
class Player : public Sprite{
public:
    Player(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Player( ) override{ };
    void updatePlayer();
};

//enemy class
class Enemy : public Sprite{
public:
    Enemy(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Enemy( ) override{ };
    void updateEnemy(sf::Vector2f playerPos);
    
private:
    float speed = 100;
};

//bullet class
class Bullet : public Sprite{
public:
    Bullet(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) { calculateDirVec(); }
    ~Bullet( ) override{ };
    void updateBullet();
    
private:
    void calculateDirVec();
    sf::Vector2f directionUnit;
    float speed = 500;
};



#endif /* sprites_hpp */
