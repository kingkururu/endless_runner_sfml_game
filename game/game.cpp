//
//  game.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "game.hpp"
GameManager::GameManager() : window(sf::VideoMode(screenHeight, screenWidth), gameTitle, sf::Style::Titlebar | sf::Style::Close) {
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void GameManager::runGame() {
    createAssets();
    while (window.isOpen()) {
        if(!GameEvents.gameEnd){
            countTime();
            handleEventInput();
            handleGameEvents();            
        }
        updateSprites();
        handleEventInput();
        draw();
    }
}

void GameManager::createAssets(){
   

}

void GameManager::countTime(){
    sf::Time frameTime = clock.restart();
    deltaTime = frameTime.asSeconds();
    globalTime += frameTime.asSeconds();
}

void GameManager::handleEventInput(){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
            window.close();
        }
        if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::D:
                    FlagEvents.dPressed = true;
                    break;
                case sf::Keyboard::A:
                    FlagEvents.aPressed = true;
                    break;
                case sf::Keyboard::B:
                    //backgroundMusic->returnMusic()->stop();
                    restartGame();
                    break;
                default:
                    break;
            }
        }
        if (event.type == sf::Event::KeyReleased){
            FlagEvents.dPressed = false;
            FlagEvents.aPressed = false;
        }
    }
}

void GameManager::handleGameEvents(){
       
}

void GameManager::updateSprites() {
    
    window.display();
}

void GameManager::restartGame(){
  
}

void GameManager::draw(){

}
