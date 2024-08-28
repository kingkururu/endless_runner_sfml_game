//
//  constants.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//


#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> 

namespace Constants {
    // basic game components
    extern const unsigned int SCREEN_WIDTH;
    extern const unsigned int SCREEN_HEIGHT; 
    extern const unsigned int FRAME_LIMIT;
    extern const char* GAME_TITLE;

    // score components
    extern const int INITIAL_PLAYER_HIT;
    extern const int INITIAL_SCORE;

    // basic animation standards
    extern const float ANIMATION_FRAME_DURATION;
    extern const float ANIMATION_CHANGE_TIME;

    // screen buffers for sprites and texts
    extern const int SPRITE_OUT_OF_BOUNDS_OFFSET;
    extern const int SPRITE_OUT_OF_BOUNDS_ADJUSTMENT;

    // background components (static)
    extern const sf::Vector2f BACKGROUND_POSITION;
    extern const sf::Vector2f BACKGROUND_SCALE;
    extern const char* BACKGROUNDSPRITE_PATH;
    extern std::shared_ptr<sf::Texture> BACKGROUND_TEXTURE;  

    // player components (non-static) / animated 
    extern const sf::Vector2f PLAYER_POSITION;
    extern const sf::Vector2f PLAYER_SCALE;
    extern const std::vector<sf::IntRect> PLAYERSPRITE_RECTS;
    extern const float PLAYER_SPEED;
    extern const sf::Color PLAYER_DEAD_COLOR;
    extern const char* PLAYERSPRITE_PATH;
    extern std::shared_ptr<sf::Texture> PLAYER_TEXTURE;

    // bullet components (non-static) / non-animated
    extern const sf::Vector2f BULLET_POSITION;
    extern const sf::Vector2f BULLET_SCALE;
    extern const std::vector<sf::IntRect> BULLETSPRITES_RECTS;
    extern const float BULLET_SPEED;
    extern const float BULLET_ACCELERATION;
    extern const char* BULLETSPRITE_PATH;
    extern std::shared_ptr<sf::Texture> BULLET_TEXTURE;

    // slime components (non-static) / animated
    extern const sf::Vector2f SLIME_POSITION;
    extern const sf::Vector2f SLIME_SCALE;
    extern const std::vector<sf::IntRect> SLIMESPRITE_RECTS;
    extern const char* SLIMESPRITE_PATH;
    extern std::shared_ptr<sf::Texture> SLIME_TEXTURE;

    extern const float SLIME_SPEED;
    extern const float SLIME_ACCELERATION;

    // bush components (non-static) / non-animated
    extern const sf::Vector2f BUSH_POSITION;
    extern const sf::Vector2f BUSH_SCALE;
    extern const std::vector<sf::IntRect> BUSHSPRITES_RECTS;
    extern const float BUSH_SPEED;
    extern const float BUSH_ACCELERATION;
    extern const char* BUSHSPRITE_PATH;
    extern std::shared_ptr<sf::Texture> BUSH_TEXTURE;

    // text components
    extern const sf::Vector2f TEXT_POSITION;
    extern const unsigned int TEXT_SIZE;
    extern const sf::Color TEXT_COLOR;
    extern const char* TEXT_PATH;
    extern std::shared_ptr<sf::Font> TEXT_FONT; 
    extern const char* TEXT_MESSAGE;

    // paths to sounds & Music
    extern const char* BACKGROUNDMUSIC_PATH;
    extern const char* PLAYERDEADSOUND_PATH;
    extern const char* PLAYERJUMPSOUND_PATH;
    extern const char* BULLETSOUND_PATH;
    extern const char* OBSTHITSOUND_PATH;
    //extern std::shared_ptr<sf::

    extern void loadTextures(); 
}
