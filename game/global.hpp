//
//  global.hpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#ifndef global_hpp
#define global_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

extern struct flagEvents{
    bool aPressed;
    bool dPressed;
    bool mouseClicked;
    
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
    
    gameComponents() : screenWidth(1000), screenHeight(1000), deltaTime(0), globalTime(0) {}
} GameComponents;

extern struct gameScore{
    unsigned int itNum;
    bool firstIt;
    int playerHit; 
    int score;

    gameScore() : itNum(0), firstIt(true), playerHit(0), score(0) {}
} GameScore; 








#endif /* global_hpp */
