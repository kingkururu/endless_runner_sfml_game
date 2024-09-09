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
#include "flags.hpp" 

class Sprite{
public:
    explicit Sprite(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture);

    virtual ~Sprite() = default;
    sf::Vector2f const getSpritePos() const { return position; };
    sf::Sprite& returnSpritesShape() const { return *spriteCreated; }
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
   explicit Background(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture); 
    ~Background() override{};
    void updateBackground(float deltaTime, float backgroundSpeed); 
    sf::Sprite& returnSpritesShape2() { return *spriteCreated2; }
    bool getBackgroundMoveState() { return backgroundMoveState; } 
    void setBackgroundMoveState(bool newState) { backgroundMoveState = newState; }

private:
    std::unique_ptr<sf::Sprite> spriteCreated2;
    bool backgroundMoveState = true; 
};

class NonStatic : public Sprite{
public:
   explicit NonStatic(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture, const std::vector<sf::IntRect> animationRects, unsigned const int indexMax, const std::vector<std::weak_ptr<sf::Uint8[]>>& bitMask)
    : Sprite(position, scale, texture), animationRects(animationRects), indexMax(indexMax), bitMask(bitMask) {}
    ~NonStatic() override{}; 
    void updatePos(); 
    bool const getMoveState() const { return moveState; }
    void setMoveState(bool newState) { moveState = newState; }
    std::vector<sf::IntRect> getAnimationRects() const { return animationRects; } 
    void setAnimation(std::vector<sf::IntRect> AnimationRects) { animationRects = AnimationRects; } 
    sf::IntRect getRects() const;
    void setRects(int animNum); 
    int getCurrIndex() const { return currentIndex; } 
    void changeAnimation(float deltaTime); 
    void changePosition(sf::Vector2f newPos) { position = newPos; }  
    std::shared_ptr<sf::Uint8[]> const getBitmask(size_t index) const ; 
    void setAnimChangeState(bool newState) { animChangeState = newState; }
    virtual const sf::Vector2f getDirectionVector() const { return directionVector; }
    virtual void setDirectionVector( sf::Vector2f dir) {directionVector = dir; } 
    virtual const float getSpeed() const { return speed; }
    void setSpeed(float newSpeed) { speed = newSpeed; } 

protected:
    bool moveState = true;
    std::vector<sf::IntRect> animationRects{}; 
    int animNum {}; 
    int currentIndex {};
    int indexMax {}; 
    float elapsedTime {};
    bool animChangeState = true; 
    std::vector<std::weak_ptr<sf::Uint8[]>> bitMask{}; 
    sf::Vector2f directionVector{}; 
    float speed {}; 

};

class Player : public NonStatic{
public:
   explicit Player(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture, const std::vector<sf::IntRect> animationRects, unsigned const int indexMax, const std::vector<std::weak_ptr<sf::Uint8[]>>& bitMask) : NonStatic(position, scale, texture, animationRects, indexMax, bitMask) {}
   ~Player() override {}; 
    void updatePlayer(sf::Vector2f newPos); 
    const float getSpeed() const override { return Constants::PLAYER_SPEED; }

};

class Obstacle : public NonStatic{
public:
    explicit Obstacle(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture> texture, const std::vector<sf::IntRect> animationRects, unsigned const int indexMax, const std::vector<std::weak_ptr<sf::Uint8[]>>& bitMask) : NonStatic(position, scale, texture, animationRects, indexMax, bitMask) {}
    ~Obstacle() override {}; 
    const sf::Vector2f getDirectionVector() const override { return directionVector; }
    const float getSpeed() const override { return Constants::SLIME_SPEED; }
    using NonStatic::setDirectionVector;
    void setDirectionVector(float angle);
private:
};

class Bullet : public NonStatic{
public:
    explicit Bullet(sf::Vector2f position, sf::Vector2f scale, std::weak_ptr<sf::Texture>texture, const std::vector<sf::IntRect> animationRects, unsigned const int indexMax, const std::vector<std::weak_ptr<sf::Uint8[]>>& bitMask) : NonStatic(position, scale, texture, animationRects, indexMax, bitMask) {}
    ~Bullet() override {}; 
    const sf::Vector2f getDirectionVector() const override { return directionVector; } 
    const float getSpeed() const override { return Constants::BULLET_SPEED; }
    using NonStatic::setDirectionVector;
    void setDirectionVector(sf::Vector2i projectionPos);

private:
};



#endif /* sprites_hpp */
