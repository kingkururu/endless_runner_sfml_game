//
//  game.hpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//
#ifndef game_hpp
#define game_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprites.hpp"
#include "sound.hpp"
#include "fonts.hpp"
#include "global.hpp"

class GameManager {
public:
    GameManager();
    ~GameManager();
    void runGame();
    
private:
    void createAssets();
    void countTime();
    void handleEventInput();
    void handleGameEvents();
    void updateSprites();
    void draw();
    void deleteAssets();
    void restartGame();
    void destroyAll();

    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime {};
    float globalTime {}; 
    
    Obstacle* obstacle1; 

    std::vector<Obstacle*> obstacles; 

    Static* background; 

    Player* playerSprite;
    
    TextClass* textSprite; 

    MusicClass* backgroundMusic;

    SoundClass* playerDeadSound;

    const std::string gameTitle{}; 
    const int screenHeight{};
    const int screenWidth{};
    const int frameLimit{};
};

#endif /* game_hpp */
