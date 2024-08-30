//
//  scenes.hpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//
#pragma once

#ifndef scenes_hpp
#define scenes_hpp

#include <iostream>
#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "sprites.hpp"
#include "sound.hpp"
#include "fonts.hpp"


class Scene {
public:
    Scene();

    void createAssets();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void handleInput(const sf::Event& event);
    void handleGameEvents();
    void restart();

private:
    sf::RenderWindow* window;

    // Sprites
    std::unique_ptr<Background> background;
    std::unique_ptr<Player> playerSprite;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Obstacle>> bushes;
    std::vector<std::unique_ptr<Obstacle>> slimes;

    // Music and sounds
    std::unique_ptr<MusicClass> backgroundMusic;
    std::unique_ptr<SoundClass> playerDeadSound;
    std::unique_ptr<SoundClass> playerJumpSound;
    std::unique_ptr<SoundClass> bulletSound;
    std::unique_ptr<SoundClass> obstHitSound;

    // Fonts and texts
    std::unique_ptr<TextClass> endingText;
};


#endif /* scenes_hpp */