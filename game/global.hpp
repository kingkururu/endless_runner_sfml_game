//
//  global.hpp
//  sfmlgame1
//
//  Created by Sunmyoung Yun on 2024/03/11.
//

#ifndef global_hpp
#define global_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

extern struct flagEvents{
    bool wPressed;
    bool aPressed;
    bool sPressed;
    bool dPressed;
    bool mouseClicked;
    
    flagEvents() : wPressed(false), aPressed(false), sPressed(false), dPressed(false), mouseClicked(false){}
} FlagEvents;

extern struct gameEvents{
    bool playerDead;
    bool playerWin;
    bool gameEnd;
    
    gameEvents() : playerWin(false), playerDead(false), gameEnd(false){}
} GameEvents;

extern struct gameComponents{
    int screenWidth, screenHeight;
    float deltaTime;
    float globalTime;
    sf::Vector2i mouseClickedPos;
    const int enemyNum = 7;
    
    gameComponents() : screenWidth(1920), screenHeight(1080), deltaTime(0), globalTime(0), mouseClickedPos(0,0){}
} GameComponents;











#endif /* global_hpp */
