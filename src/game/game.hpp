// //
// //  game.hpp
// //  sfmlgame3
// //
// //  Created by Sunmyoung Yun on 2024/08

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "scenes.hpp"
#include "constants.hpp"
#include "flags.hpp"

class GameManager {
public:
    GameManager();
    void runGame();

private:
    void countTime();
    void handleEventInput();

    //game components (not accesible from anywhere else otherthan game manager)
    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime {};
    float globalTime {};
    
    sf::Vector2i mouseClickedPos {};
    unsigned int score = Constants::INITIAL_SCORE;

    // Scene
    std::unique_ptr<Scene> scene;
};

#endif // GAME_HPP
