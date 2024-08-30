//
//  game.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//
#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "sprites.hpp"
#include "sound.hpp"
#include "fonts.hpp"
#include "constants.hpp"
#include "physics.hpp"
#include "flags.hpp"

class GameManager {
public:
    GameManager();
    void runGame();
    
private:
    void createAssets();
    void countTime();
    void handleEventInput();
    void handleGameEvents();
    void updateSprites();
    void draw();
    void restartGame();

    //Game components
    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime {};
    float globalTime {}; 
    
    sf::Vector2i mouseClickedPos {}; 
    unsigned int score = Constants::INITIAL_SCORE;

    //Sprites 
    std::unique_ptr<Background> background; 
    std::unique_ptr<Player> playerSprite;
    std::vector<std::unique_ptr<Bullet>> bullets; 
    std::vector<std::unique_ptr<Obstacle>> bushes; 
    std::vector<std::unique_ptr<Obstacle>> slimes; 

    //Music and sounds
    std::unique_ptr<MusicClass> backgroundMusic;

    std::unique_ptr<SoundClass> playerDeadSound;
    std::unique_ptr<SoundClass> playerJumpSound;
    std::unique_ptr<SoundClass> bulletSound;
    std::unique_ptr<SoundClass> obstHitSound;

    //Fonts and texts
    std::unique_ptr<TextClass> endingText;
};

#endif /* game_hpp */
