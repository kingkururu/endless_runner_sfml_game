#pragma once

#include <SFML/Graphics.hpp>

namespace Constants {
    constexpr unsigned int SCREEN_WIDTH = 600;
    constexpr unsigned int SCREEN_HEIGHT = 600; 
    constexpr unsigned int FRAME_LIMIT = 60;

    constexpr float ANIMATION_FRAME_DURATION = 0.1f;
    constexpr float ANIMATION_CHANGE_TIME = 0.5f; 

    constexpr float PLAYER_SPEED = 200.0f;
    constexpr float PLAYER_ACCELERATION = 100.0f;

    constexpr int INITIAL_PLAYER_HIT = 0;
    constexpr int INITIAL_SCORE = 0;

    constexpr int SPRITE_OUT_OF_BOUNDS_OFFSET = 10;
    constexpr int SPRITE_OUT_OF_BOUNDS_ADJUSTMENT = 80;

    const sf::Color PLAYER_DEAD_COLOR = sf::Color(200,0,0);
}