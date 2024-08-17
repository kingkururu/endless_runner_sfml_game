//
//  sprites.hpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
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
    bool visibleState ;
    bool moveState;
    float speed;
};

class Background : public Sprite{
public:
    Background(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Background( ) override{ };
    void updateBackground();
};

//player class
class Player : public Sprite{
public:
    Player(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Player( ) override{ };
    void updatePlayer();
};

//enemy class
class Rain : public Sprite{
public:
    Rain(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Rain( ) override{ };
    void updateRain();
    
private:
    float speed = 100;
};

class Lightning : public Sprite{
    public:
    Lightning(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Lightning() override{};
    void updateLightning(); 
};

class Coin : public Sprite{
public:
    Coin(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Coin() override{};
    void updateCoin(); 
};

class Heart : public Sprite{
public:
    Heart(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Heart() override{};
    void updateHeart(); 
}; 

#endif /* sprites_hpp */
