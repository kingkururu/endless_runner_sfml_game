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
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "constants.hpp"

class Sprite{
public:
    explicit Sprite(sf::Vector2f position, sf::Vector2f scale = {1.0f, 1.0f}, std::shared_ptr<sf::Texture> texture = nullptr);

    virtual ~Sprite() = default;
    sf::Vector2f const getSpritePos() const { return position; };
   // sf::Sprite& returnSpritesShape() const { return *spriteCreated; }
    sf::Sprite& returnSpritesShape() { return *spriteCreated; }
    bool const getVisibleState() const { return visibleState; }
    void setVisibleState(bool VisibleState){ visibleState = VisibleState; }

protected:
    sf::Vector2f position {};
    sf::Vector2f scale {};
    std::shared_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> spriteCreated;
    bool visibleState {};
};

class Static : public Sprite{
public:
    explicit Static(sf::Vector2f position, sf::Vector2f scale, std::shared_ptr<sf::Texture> texture) : Sprite(position, scale, texture) {}
    ~Static() override{};
};

class Background : public Static{
public:
    explicit Background(sf::Vector2f position, sf::Vector2f scale, std::shared_ptr<sf::Texture> texture) : Static(position, scale, texture) {}
    ~Background() override{};
};

class NonStatic : public Sprite{
public:
   explicit NonStatic(sf::Vector2f position, sf::Vector2f scale, std::shared_ptr<sf::Texture> texture, float speed, const std::vector<sf::IntRect> animationRects) : Sprite(position, scale, texture), speed(speed), animationRects(animationRects) {}
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
   explicit Player(sf::Vector2f position, sf::Vector2f scale, std::shared_ptr<sf::Texture> texture, const std::vector<sf::IntRect> animationRects, float speed) : NonStatic(position, scale, texture, speed, animationRects) {}
   ~Player() override {}; 
    void updatePlayer(); 
};

class Obstacle : public NonStatic{
public:
    explicit Obstacle(sf::Vector2f position, sf::Vector2f scale, std::shared_ptr<sf::Texture> texture, const std::vector<sf::IntRect> animationRects, float speed) : NonStatic(position, scale, texture, speed, animationRects) {}
    ~Obstacle() override {}; 
    void updateObstacle();
};

class Bullet : public NonStatic{
   public:
    explicit Bullet(sf::Vector2f position, sf::Vector2f scale, std::shared_ptr<sf::Texture>texture, const std::vector<sf::IntRect> animationRects, float speed) : NonStatic(position, scale, texture, speed, animationRects) {}
    ~Bullet() override {}; 
    void updateBullet();  
};



#endif /* sprites_hpp */
