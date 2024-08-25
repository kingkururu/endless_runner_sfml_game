//
//  sprites.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#pragma once

#include <SFML/Graphics.hpp>

namespace Constants {
    //basic game components
    constexpr unsigned int SCREEN_WIDTH = 960;
    constexpr unsigned int SCREEN_HEIGHT = 540; 
    constexpr unsigned int FRAME_LIMIT = 60;
    constexpr const char* GAME_TITLE = "SFML game 3"; 

    //score components
    constexpr int INITIAL_PLAYER_HIT = 0;
    constexpr int INITIAL_SCORE = 0;

    //basic animation standards
    constexpr float ANIMATION_FRAME_DURATION = 0.1f;
    constexpr float ANIMATION_CHANGE_TIME = 0.5f; 

    //screen buffers for sprites and texts
    constexpr const int SPRITE_OUT_OF_BOUNDS_OFFSET = 10;
    constexpr const int SPRITE_OUT_OF_BOUNDS_ADJUSTMENT = 80;

    //background components (static)
    constexpr const char* BACKGROUNDSPRITE_PATH = "src/assets/sprites/png/background.png"; 
    const sf::Vector2f BACKGROUND_POSITION = {0.0, 0.0};
    const sf::Vector2f BACKGROUND_SCALE = {.5, .5}; 

    //player components (non-static) / animated 
    constexpr const char* PLAYERSPRITE_PATH = "src/assets/sprites/png/player_run.png";
    const sf::Vector2f PLAYER_POSITION = {0.0, 0.0};
    const sf::Vector2f PLAYER_SCALE = {.5, .5}; 
    const std::vector<sf::IntRect> PLAYERSPRITE_RECTS = {sf::IntRect{0, 0, 0,0 }}; 
    constexpr float PLAYER_SPEED = 200.0f;
    const sf::Color PLAYER_DEAD_COLOR = sf::Color(200,0,0);

    //bullet components (non-static) / non-animated
    constexpr const char* BULLETSPRITE_PATH = "src/assets/sprites/png/bullet.png";
    const sf::Vector2f BULLET_POSITION = {0.0, 0.0};
    const sf::Vector2f BULLET_SCALE = {.5, .5}; 
    constexpr float BULLET_SPEED = 200.0f;
    constexpr float BULLET_ACCELERATION = -20.0f;

    //slime components (non-static) / animated 
    constexpr const char* SLIMESPRITE_PATH = "src/assets/sprites/png/slime.png";
    const sf::Vector2f SLIME_POSITION = {0.0, 0.0};
    const sf::Vector2f SLIME_SCALE = {.5, .5}; 
    std::vector<sf::IntRect> SLIMESPRITE_RECTS = {sf::IntRect{0, 0, 0, 0}};

    constexpr float SLIME_SPEED = 200.0f;
    constexpr float SLIME_ACCELERATION = -20.0f;

    //bush components (non-static) / non-animated
    constexpr const char* BUSHSPRITE_PATH = "src/assets/sprites/png/bush1.png";
    const sf::Vector2f BUSH_POSITION = {0.0, 0.0};
    std::vector<sf::IntRect> BUSHSPRITES_RECTS = {sf::IntRect{0, 0, 0, 0}};
    const sf::Vector2f BUSH_SCALE = {.5, .5}; 
    constexpr float BUSH_SPEED = 200.0f;
    constexpr float BUSH_ACCELERATION = -20.0f;

    //text components
    constexpr const char* FONTS_PATH = "src/assets/fonts/ttf/font1.ttf"; 
    constexpr float TEXT_SCALE = 0.1f;
    const sf::Color ENDINGTEXT_COLOR = sf::Color::White; 

    //paths to sounds&Music
    constexpr const char* BACKGROUNDMUSIC_PATH = "src/assets/sound/mp3,flac,wav/bgm.mp3"; 
    constexpr const char* PLAYERDEADSOUND_PATH = "src/assets/sound/mp3,flac,wav/gameEnd.flac"; 
    constexpr const char* PLAYERJUMPSOUND_PATH = "src/assets/sound/mp3,flac,wav/jump.wav"; 
    constexpr const char* BULLETSOUND_PATH = "";
    constexpr const char* OBSTHITSOUND_PATH = "";
}