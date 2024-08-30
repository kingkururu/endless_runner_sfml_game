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
    bool aPressed;
    bool dPressed;
    
    flagEvents() : aPressed(false), dPressed(false){}
} FlagEvents;



#endif /* flags_hpp */