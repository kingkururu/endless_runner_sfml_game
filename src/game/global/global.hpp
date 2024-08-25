//
//  global.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#pragma once
#include "constants.hpp" 

namespace GameData{
    extern struct flagEvents{
        bool aPressed;
        bool dPressed;
        
        flagEvents() : aPressed(false), dPressed(false){}
    } FlagEvents;

    extern struct gameEvents{
        bool playerDead;
        bool gameEnd;
        
        gameEvents() : playerDead(false), gameEnd(false){}
    } GameEvents;

    extern struct gameComponents{
        int screenWidth, screenHeight;
        float deltaTime;
        float globalTime;
        
        gameComponents() : screenWidth(Constants::SCREEN_WIDTH), screenHeight(Constants::SCREEN_HEIGHT), deltaTime(0), globalTime(0) {}
    } GameComponents;

    extern struct gameScore{
        int playerHit; 
        int score;

        gameScore() : playerHit(Constants::INITIAL_PLAYER_HIT), score(Constants::INITIAL_SCORE) {}
    } GameScore; 

}








