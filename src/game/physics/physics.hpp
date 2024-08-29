//
//  physics.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//
#ifndef physics_hpp
#define physics_hpp

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

namespace physics{
    constexpr float gravity = 9.8;

    void freeFall();
    void rightToLeftFall(); 

    void moveLeft();
    void moveRight();
    
    void collision(); 

    void aabbColision();
    void pixelperfect();     
}

#endif /* game_hpp */
