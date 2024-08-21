//
//  game.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "game.hpp"
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
        // background = std::make_unique<Background>(sf::Vector2f(0, 0), sf::Vector2f(screenWidth, screenHeight), "path/to/background.png");
        // playerSprite = std::make_unique<Player>(sf::Vector2f(100, 100), sf::Vector2f(50, 50), "path/to/player.png", {}, 5.0f);
        // textSprite = std::make_unique<TextClass>(sf::Vector2f(10, 10), 24, sf::Color::White, "path/to/font.ttf", "Hello World");
        backgroundMusic = std::make_unique<MusicClass>("path/to/music.ogg");
        playerDeadSound = std::make_unique<SoundClass>("path/to/sound.wav");
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
       // window.draw(*background->returnSpritesShape());
    }
    if (playerSprite) {
      //  window.draw(*playerSprite->returnSpritesShape());
    }
    if (textSprite) {
    //    window.draw(*textSprite->getText());
    }
}
