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
#include <stdexcept>

class Sprite{
public:
    explicit Sprite(sf::Vector2f position, sf::Vector2f scale = {1.0f, 1.0f}, const std::string& texturePath = "");
    virtual ~Sprite() = default;
    sf::Vector2f const getSpritePos() const { return position; };
   // sf::Sprite& returnSpritesShape() const { return *spriteCreated; }
    sf::Sprite& returnSpritesShape() { return *spriteCreated; }
    bool const getVisibleState() const { return visibleState; }
    void setVisibleState(bool VisibleState){ visibleState = VisibleState; }

protected:
    sf::Vector2f position {};
    sf::Vector2f scale {};
    std::unique_ptr<sf::Texture> skin;
    std::unique_ptr<sf::Sprite> spriteCreated;
    bool visibleState {};
};

class Static : public Sprite{
public:
    explicit Static(sf::Vector2f position, sf::Vector2f scale, const std::string& texturePath) : Sprite(position, scale, texturePath) {}
    ~Static() override{};
};

class Background : public Static{
public:
    explicit Background(sf::Vector2f position, sf::Vector2f scale, const std::string& texturePath) : Static(position, scale, texturePath) {}
    ~Background() override{};
};

class NonStatic : public Sprite{
public:
   explicit NonStatic(sf::Vector2f position, sf::Vector2f scale, const std::string& texturePath, float speed, const std::vector<sf::IntRect> animationRects) : Sprite(position, scale, texturePath),speed(speed), animationRects(animationRects) {}
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
    explicit Player(sf::Vector2f position, sf::Vector2f scale, const std::string& texturePath, const std::vector<sf::IntRect> animationRects, float speed) : NonStatic(position, scale, texturePath, speed, animationRects) {}
    ~Player() override {}; 
    void updatePlayer(); 
};

class Obstacle : public NonStatic{
public:
    explicit Obstacle(sf::Vector2f position, sf::Vector2f scale, const std::string& texturePath, const std::vector<sf::IntRect> animationRects, float speed) : NonStatic(position, scale, texturePath, speed, animationRects) {}
    ~Obstacle() override {}; 
    void updateObstacle();
};

class Bullet : public NonStatic{
   public:
    explicit Bullet(sf::Vector2f position, sf::Vector2f scale, const std::string& texturePath, const std::vector<sf::IntRect> animationRects, float speed) : NonStatic(position, scale, texturePath, speed, animationRects) {}
    ~Bullet() override {}; 
    void updateBullet();  
};

#endif /* sprites_hpp */
