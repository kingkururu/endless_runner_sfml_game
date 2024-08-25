//
//  game.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "game.hpp"

GameManager::GameManager()
    : window(sf::VideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT), Constants::GAME_TITLE, sf::Style::Titlebar | sf::Style::Close) 
{
    window.setFramerateLimit(Constants::FRAME_LIMIT);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    gameEnd = false; 
}

void GameManager::runGame() {
    try{
        createAssets();
        while (window.isOpen()) {
            if(!gameEnd){
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
        //sprites
        background = std::make_unique<Background>(Constants::BACKGROUND_POSITION, Constants::BACKGROUND_SCALE, Constants::BACKGROUNDSPRITE_PATH);
        playerSprite = std::make_unique<Player>(Constants::PLAYER_POSITION, Constants::PLAYER_SCALE, Constants::PLAYERSPRITE_PATH, Constants::PLAYERSPRITE_RECTS, Constants::PLAYER_SPEED);
        bullets.push_back(std::make_unique<Bullet>(Constants::BULLET_POSITION, Constants::BULLET_SCALE, Constants::BULLETSPRITE_PATH, Constants::BULLETSPRITES_RECTS, Constants::BULLET_SPEED)); 
        bushes.push_back(std::make_unique<Obstacle>(Constants::BUSH_POSITION, Constants::BUSH_SCALE, Constants::BUSHSPRITE_PATH, Constants::BUSHSPRITES_RECTS, Constants::BUSH_SPEED)); 
        slimes.push_back(std::make_unique<Obstacle>(Constants::SLIME_POSITION, Constants::SLIME_SCALE, Constants::SLIMESPRITE_PATH, Constants::SLIMESPRITE_RECTS, Constants::SLIME_SPEED));

        //sounds and music
        playerDeadSound = std::make_unique<SoundClass>(Constants::PLAYERDEADSOUND_PATH);
        playerJumpSound = std::make_unique<SoundClass>(Constants::PLAYERJUMPSOUND_PATH);
        bulletSound = std::make_unique<SoundClass>(Constants::BULLETSOUND_PATH);
        obstHitSound = std::make_unique<SoundClass>(Constants::OBSTHITSOUND_PATH);    
        backgroundMusic = std::make_unique<MusicClass>(Constants::BACKGROUNDMUSIC_PATH);
        backgroundMusic->returnMusic()->play(); 
        
        //text
        endingText = std::make_unique<TextClass>(Constants::TEXT_POSITION, Constants::TEXT_SIZE, Constants::TEXT_COLOR, Constants::TEXT_PATH, Constants::TEXT_MESSAGE); 
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
                case sf::Keyboard::Space: 
                    spaceBpressed = true;
                    break;
                case sf::Keyboard::B:
                    backgroundMusic->returnMusic()->stop();
                    restartGame();
                    break;
                default:
                    break;
            }
        }
        if (event.type == sf::Event::KeyReleased){
            spaceBpressed = false;
        }
        if (event.type == sf::Event::MouseButtonPressed){
           mouseClickedPos = sf::Mouse::getPosition(window); 
           mouseClicked = true; 
        }
        if (event.type == sf::Event::MouseButtonReleased){
            mouseClicked = false;
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

    if (background->getVisibleState()) {
        window.draw(background->returnSpritesShape());
    }
    if (playerSprite->getVisibleState()) {
        window.draw(playerSprite->returnSpritesShape());
    }
    for (const auto& bullet : bullets) {
        if (bullet->getVisibleState()) {
            window.draw(bullet->returnSpritesShape());
        }
    }
    for (const auto& bush : bushes) {
        if (bush->getVisibleState()) {
            window.draw(bush->returnSpritesShape());
        }
    }
    for (const auto& slime : slimes) {
        if (slime->getVisibleState()) {
            window.draw(slime->returnSpritesShape());
        }
    }
    if(endingText->getVisibleState()){
        window.draw(endingText->getText()); 
    }
}
