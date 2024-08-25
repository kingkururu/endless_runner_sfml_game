//
//  game.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "game.hpp"
using namespace GameData;

GameManager::GameManager(const std::string& title, unsigned int height, unsigned int width, unsigned int frameRate) : window(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close), gameTitle(title), screenHeight(height), screenWidth(width),  frameLimit(frameRate) {
    window.setFramerateLimit(frameLimit);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void GameManager::runGame() {
    try{
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

    catch(const std::exception& e){
        std::cerr << "exception in runGame: " << e.what() << std::endl; 
    }
}

void GameManager::createAssets(){
   try {
        background = std::make_unique<Background>(Constants::BACKGROUND_POSITION, Constants::BACKGROUND_SCALE, Constants::BACKGROUND_PATH);
        backgroundMusic = std::make_unique<MusicClass>(Constants::BACKGROUNDMUSIC_PATH);
    } 
    
    catch (const std::exception& e) {
        std::cerr << "Exception caught in createAssets: " << e.what() << std::endl;
    }
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
    window.clear();
    if (background) {
        window.draw(background->returnSpritesShape());
    }
    if (playerSprite) {
      //  window.draw(*playerSprite->returnSpritesShape());
    }
    if (textSprite) {
    //    window.draw(*textSprite->getText());
    }
}
