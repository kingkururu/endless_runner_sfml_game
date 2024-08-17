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
    void createMoreAssets();
    void handleEventInput();
    void handleGameEvents();
    void checkEvent();
    void countTime();
    void updateSprites();
    void draw();
    void deleteAssets();
    void restartGame();
    void destroyAll();

    sf::RenderWindow window;
    sf::Clock clock;
    
    Sprite* background; 

    Player* playerSprite;

    std::vector<Rain*> rainDrops;
    float rainRespawnTime; 

    std::vector<Coin*> coins;
    float coinRespawnTime;

    std::vector<Lightning*> lightnings;
    float lightningRespawnTime; 

    std::vector<TextClass*> endMessage;
    std::string endingText;

    TextClass* scoreText; 

    // const int heartsNum = 5;
    Heart* hearts[5]; 

    MusicClass* backgroundMusic;
    SoundClass* playerDeadSound;
    SoundClass* coinSound;
    SoundClass* rainSound;
    SoundClass* lightningSound; 
};

#endif /* game_hpp */
