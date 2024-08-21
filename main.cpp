//
//  main.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "game.hpp"

int main( ){
    GameManager makeGame("title", 600, 600, 60);

    makeGame.runGame();
    
    return 0; 
}
