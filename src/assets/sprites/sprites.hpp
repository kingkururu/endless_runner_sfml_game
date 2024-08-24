//
//  sprites.hpp
//  sfmlgame3
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
#include <stdexcept>

class Sprite{
public:
    explicit Sprite(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath);
    virtual ~Sprite() = default;
    sf::Vector2f const getSpritePos() const { return position; };
   // sf::Sprite& returnSpritesShape() const { return *spriteCreated; }
    sf::Sprite& returnSpritesShape() { return *spriteCreated; }
    bool const getVisibleState() const { return visibleState; }
    void setVisibleState(bool VisibleState){ visibleState = VisibleState; }

protected:
    sf::Vector2f position {};
    sf::Vector2f size {};
    std::unique_ptr<sf::Texture> skin;
    std::unique_ptr<sf::Sprite> spriteCreated;
    bool visibleState {};
};

class Static : public Sprite{
public:
    explicit Static(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Sprite(position, size, texturePath) {}
    ~Static() override{};
};

class Background : public Static{
public:
    explicit Background(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) : Static(position, size, texturePath) {}
    ~Background() override{};
};

class NonStatic : public Sprite{
public:
   explicit NonStatic(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath, const std::vector<sf::IntRect> animationRects, float speed) : Sprite(position, size, texturePath), animationRects(animationRects), speed(speed) {}
    ~NonStatic() override{}; 
    void updatePos(); 
    bool const getMoveState() const { return moveState; }
    void setMoveState(bool newState) { moveState = newState; }
    float getAcceleration() { return acceleration; }
    void setAcceleration(float Acceleration) { acceleration = Acceleration; }
    std::vector<sf::IntRect> getAnimation() const { return animationRects; } 
    void setAnimation(std::vector<sf::IntRect> AnimationRects) { animationRects = AnimationRects; } 
    sf::IntRect getRects() const { return animationRects[currentIndex]; }
    void setRects(int animNum); 
    void changeAnimation(float deltaTime); 

protected:
    bool moveState {};
    float speed {};
    float acceleration {}; 
    std::vector<sf::IntRect> animationRects{}; 
    int animNum {}; 
    int currentIndex {};
    int indexMax {}; 
    float elapsedTime {};
    float animFrameDuration {};
    float changeAnimTime {}; 
    float visibleDuration {};
};

class Player : public NonStatic{
public:
    explicit Player(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath, const std::vector<sf::IntRect> animationRects, float speed) : NonStatic(position, size, texturePath, animationRects, speed) {}
    ~Player() override {}; 
    void updatePlayer(); 
};

class Obstacle : public NonStatic{
public:
    explicit Obstacle(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath, const std::vector<sf::IntRect> animationRects, float speed) : NonStatic(position, size, texturePath, animationRects, speed) {}
    ~Obstacle() override {}; 
    void updateObstacle();
};

#endif /* sprites_hpp */
