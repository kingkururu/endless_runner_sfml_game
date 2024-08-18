//
//  global.hpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#pragma once

#ifndef global_hpp
#define global_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

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
    
    gameComponents() : screenWidth(600), screenHeight(600), deltaTime(0), globalTime(0) {}
} GameComponents;

extern struct gameScore{
    int playerHit; 
    int score;

    gameScore() : playerHit(0), score(0) {}
} GameScore; 








#endif /* global_hpp */
