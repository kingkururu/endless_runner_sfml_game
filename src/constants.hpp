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
    constexpr unsigned int SCREEN_WIDTH = 600;
    constexpr unsigned int SCREEN_HEIGHT = 600; 
    constexpr unsigned int FRAME_LIMIT = 60;
    constexpr const char* GAME_TITLE = "SFML game 3"; 

    //basic animation standards
    constexpr float ANIMATION_FRAME_DURATION = 0.1f;
    constexpr float ANIMATION_CHANGE_TIME = 0.5f; 

    //score components
    constexpr int INITIAL_PLAYER_HIT = 0;
    constexpr int INITIAL_SCORE = 0;

    //sprite components
    constexpr float PLAYER_SPEED = 200.0f;
    constexpr float PLAYER_ACCELERATION = 100.0f;

    const sf::Color PLAYER_DEAD_COLOR = sf::Color(200,0,0);

    //text components
    constexpr float TEXT_SIZE = 0.1f;
    const sf::Color ENDINGTEXT_COLOR = sf::Color::White; 

    //screen buffers for sprites and texts
    constexpr const int SPRITE_OUT_OF_BOUNDS_OFFSET = 10;
    constexpr const int SPRITE_OUT_OF_BOUNDS_ADJUSTMENT = 80;

    //paths to sprites
    constexpr const char* PLAYERSPRITE_PATH = "";

    //paths to sounds&Music
    constexpr const char* BACKGROUNDMUSIC_PATH = ""; 

    //paths to fonts 
    constexpr const char* FORNTS_PATH = ""; 

}