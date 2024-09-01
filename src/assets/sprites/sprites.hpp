//
//  sprites.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//
#pragma once

#ifndef sprites_hpp
#define sprites_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <map>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "physics.hpp"

class Sprite{
public:
    explicit Sprite(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture);

    virtual ~Sprite() = default;
    sf::Vector2f const getSpritePos() const { return position; };
    sf::Sprite& returnSpritesShape() { return *spriteCreated; }
    bool const getVisibleState() const { return visibleState; }
    void setVisibleState(bool VisibleState){ visibleState = VisibleState; }

protected:
    sf::Vector2f position {};
    sf::Vector2f scale {};
    std::weak_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> spriteCreated;
    bool visibleState {};
};

class Static : public Sprite{
public:
    explicit Static(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture) : Sprite(position, scale, texture) {}
    ~Static() override{};
};

class Background : public Static{
public:
   // explicit Background(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture) : Static(position, scale, texture) {}
   explicit Background(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture); 
    ~Background() override{};
    void updateBackground(float deltaTime, float backgroundSpeed); 
    sf::Sprite& returnSpritesShape2() { return *spriteCreated2; }

private:
    std::unique_ptr<sf::Sprite> spriteCreated2;
};

class NonStatic : public Sprite{
public:
   explicit NonStatic(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture, const std::vector<sf::IntRect> animationRects, unsigned const int indexMax, std::weak_ptr<sf::Uint8[]> bitMask)
    : Sprite(position, scale, texture), animationRects(animationRects), indexMax(indexMax), bitMask(bitMask) {}
    ~NonStatic() override{}; 
    void updatePos(); 
    bool const getMoveState() const { return moveState; }
    void setMoveState(bool newState) { moveState = newState; }
    std::vector<sf::IntRect> getAnimation() const { return animationRects; } 
    void setAnimation(std::vector<sf::IntRect> AnimationRects) { animationRects = AnimationRects; } 
    sf::IntRect getRects() const { return animationRects[currentIndex]; }
    void setRects(int animNum); 
    void changeAnimation(float deltaTime); 
    void changePosition(sf::Vector2f newPos); 

protected:
    bool moveState = true;
    std::vector<sf::IntRect> animationRects{}; 
    int animNum {}; 
    int currentIndex {};
    int indexMax {}; 
    float elapsedTime {};
    std::weak_ptr<sf::Uint8[]> bitMask{}; 
};

class Player : public NonStatic{
public:
   explicit Player(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture, const std::vector<sf::IntRect> animationRects, unsigned const int indexMax, std::weak_ptr<sf::Uint8[]> bitMask) : NonStatic(position, scale, texture, animationRects, indexMax, bitMask) {}
   ~Player() override {}; 
    void updatePlayer(sf::Vector2f newPos); 
};

class Obstacle : public NonStatic{
public:
    explicit Obstacle(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture, const std::vector<sf::IntRect> animationRects, unsigned const int indexMax, std::weak_ptr<sf::Uint8[]> bitMask) : NonStatic(position, scale, texture, animationRects, indexMax, bitMask) {}
    ~Obstacle() override {}; 
   // void updateObstacle(sf::Vector2f newPos); 
    void setDirectionVector(float angle);
    const sf::Vector2f getDirectionVector() const { return directionVector; }

private:
    sf::Vector2f directionVector{}; 
};

class Bullet : public NonStatic{
public:
    explicit Bullet(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture>texture, const std::vector<sf::IntRect> animationRects, unsigned const int indexMax, std::weak_ptr<sf::Uint8[]> bitMask) : NonStatic(position, scale, texture, animationRects, indexMax, bitMask) {}
    ~Bullet() override {}; 
    //void updateBullet(sf::Vector2f newPos);  
    void setDirectionVector(sf::Vector2i projectionPos);
    const sf::Vector2f getDirectionVector() const { return directionVector; } 

private:
    sf::Vector2f directionVector{};
};



#endif /* sprites_hpp */
