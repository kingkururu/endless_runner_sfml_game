//
//  constants.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "constants.hpp"

namespace Constants {
    const unsigned int SCREEN_WIDTH = 960;
    const unsigned int SCREEN_HEIGHT = 540;
    const unsigned int FRAME_LIMIT = 60;
    const char* GAME_TITLE = "SFML game 3";

    const int INITIAL_PLAYER_HIT = 0;
    const int INITIAL_SCORE = 0;

    const float ANIMATION_FRAME_DURATION = 0.1f;
    const float ANIMATION_CHANGE_TIME = 0.5f;

    const int SPRITE_OUT_OF_BOUNDS_OFFSET = 10;
    const int SPRITE_OUT_OF_BOUNDS_ADJUSTMENT = 80;

    const sf::Vector2f BACKGROUND_POSITION = {0.0, 0.0};
    const sf::Vector2f BACKGROUND_SCALE = {0.5, 0.5};
    const char* BACKGROUNDSPRITE_PATH = "src/assets/sprites/png/background.png";

    const sf::Vector2f PLAYER_POSITION = {0.0, SCREEN_HEIGHT - 120};
    const sf::Vector2f PLAYER_SCALE = {3.0, 3.0};
    const std::vector<sf::IntRect> PLAYERSPRITE_RECTS = {sf::IntRect{0, 0, 0, 0}};
    const float PLAYER_SPEED = 200.0f;
    const sf::Color PLAYER_DEAD_COLOR = sf::Color(200, 0, 0);
    const char* PLAYERSPRITE_PATH = "src/assets/sprites/png/player_run.png";

    const sf::Vector2f BULLET_POSITION = {0.0, 0.0};
    const sf::Vector2f BULLET_SCALE = {0.5, 0.5};
    const std::vector<sf::IntRect> BULLETSPRITES_RECTS = {sf::IntRect{0, 0, 0, 0}};
    const float BULLET_SPEED = 200.0f;
    const float BULLET_ACCELERATION = -20.0f;
    const char* BULLETSPRITE_PATH = "src/assets/sprites/png/bullet.png";

    const sf::Vector2f SLIME_POSITION = {SCREEN_WIDTH - 90, static_cast<float>(std::rand() % SCREEN_HEIGHT) - 60};
    const sf::Vector2f SLIME_SCALE = {0.35, 0.35};
    const std::vector<sf::IntRect> SLIMESPRITE_RECTS = {sf::IntRect{0, 0, 0, 0}};
    const char* SLIMESPRITE_PATH = "src/assets/sprites/png/slime.png";

    const float SLIME_SPEED = 200.0f;
    const float SLIME_ACCELERATION = -20.0f;

    const sf::Vector2f BUSH_POSITION = {SCREEN_WIDTH - 100, SCREEN_HEIGHT - 130};
    const sf::Vector2f BUSH_SCALE = {3.0, 3.0};
    const std::vector<sf::IntRect> BUSHSPRITES_RECTS = {sf::IntRect{0, 0, 0, 0}};
    const float BUSH_SPEED = 200.0f;
    const float BUSH_ACCELERATION = -20.0f;
    const char* BUSHSPRITE_PATH = "src/assets/sprites/png/bush1.png";

    const sf::Vector2f TEXT_POSITION = {0.0, 0.0};
    const unsigned int TEXT_SIZE = 40;
    const sf::Color TEXT_COLOR = sf::Color::White;
    const char* TEXT_PATH = "src/assets/fonts/ttf/font1.ttf";
    const char* TEXT_MESSAGE = "blank message in text";

    const char* BACKGROUNDMUSIC_PATH = "src/assets/sound/mp3,flac,wav/bgm.mp3";
    const char* PLAYERDEADSOUND_PATH = "src/assets/sound/mp3,flac,wav/gameEnd.flac";
    const char* PLAYERJUMPSOUND_PATH = "src/assets/sound/mp3,flac,wav/jump.wav";
    const char* BULLETSOUND_PATH = "";
    const char* OBSTHITSOUND_PATH = "";
}
