//
//  main.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "game.hpp"

int main( ){
    GameManager makeGame(Constants::GAME_TITLE, Constants::SCREEN_HEIGHT, Constants::SCREEN_WIDTH, Constants::FRAME_LIMIT);

    makeGame.runGame();
    
    return 0; 
}

///idk wrote a comment for testing coderabbit