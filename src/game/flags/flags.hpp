//
//  flags.hpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#pragma once

#ifndef flags_hpp
#define flags_hpp

#include <stdio.h>

extern struct flagEvents{
    // game states
    bool gameEnd = false; 

    //keyboard inputs
    bool wPressed;
    bool aPressed;
    bool sPressed;
    bool dPressed;
    bool spacePressed = false; 
    bool mouseClicked = false;

    flagEvents() : wPressed(false), aPressed(false), sPressed(false), dPressed(false), spacePressed(false), mouseClicked(false) {}
} FlagEvents;



#endif /* flags_hpp */