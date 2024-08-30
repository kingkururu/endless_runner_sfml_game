//
//  game.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "game.hpp"

GameManager::GameManager()
    : window(sf::VideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT), Constants::GAME_TITLE, sf::Style::Titlebar | sf::Style::Close) {
    Constants::initialize();
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
                handleGameEvents();  
                updateSprites();           
            }
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
        background = std::make_unique<Background>(Constants::BACKGROUND_POSITION, Constants::BACKGROUND_SCALE, Constants::BACKGROUND_TEXTURE);
        playerSprite = std::make_unique<Player>(Constants::PLAYER_POSITION, Constants::PLAYER_SCALE, Constants::PLAYER_TEXTURE, Constants::PLAYERSPRITE_RECTS, Constants::PLAYER_SPEED, Constants::PLAYERANIM_MAX_INDEX, Constants::PLAYER_BITMASK);
        playerSprite->setRects(0); 
        bullets.push_back(std::make_unique<Bullet>(Constants::BULLET_POSITION, Constants::BULLET_SCALE, Constants::BULLET_TEXTURE, Constants::BULLETSPRITES_RECTS, Constants::BULLET_SPEED, Constants::BULLETANIM_MAX_INDEX, Constants::BULLET_BITMASK));
        bushes.push_back(std::make_unique<Obstacle>(Constants::BUSH_POSITION, Constants::BUSH_SCALE, Constants::BUSH_TEXTURE, Constants::BUSHSPRITES_RECTS, Constants::BUSH_SPEED, Constants::BUSHANIM_MAX_INDEX, Constants::BUSH_BITMASK)); 
        slimes.push_back(std::make_unique<Obstacle>(Constants::SLIME_POSITION, Constants::SLIME_SCALE, Constants::SLIME_TEXTURE, Constants::SLIMESPRITE_RECTS, Constants::SLIME_SPEED, Constants::SLIMEANIM_MAX_INDEX, Constants::SLIME_BITMASK));
        slimes[0]->setRects(0); 

        //sounds and music
        playerDeadSound = std::make_unique<SoundClass>(Constants::PLAYERDEAD_SOUNDBUFF, Constants::PLAYERDEADSOUND_VOLUME);
        playerJumpSound = std::make_unique<SoundClass>(Constants::PLAYERJUMP_SOUNDBUFF, Constants::PLAYERJUMPSOUND_VOLUME);
        bulletSound = std::make_unique<SoundClass>(Constants::BULLET_SOUNDBUFF, Constants::BULLETSOUND_VOLUME);
        obstHitSound = std::make_unique<SoundClass>(Constants::OBSTHIT_SOUNDBUFF, Constants::OBSTHITSOUND_VOLUME);    
        backgroundMusic = std::make_unique<MusicClass>(Constants::BACKGROUNDMUSIC_MUSIC, Constants::BACKGROUNDMUSIC_VOLUME);
        backgroundMusic->returnMusic().play(); 
        
        //text
        endingText = std::make_unique<TextClass>(Constants::TEXT_POSITION, Constants::TEXT_SIZE, Constants::TEXT_COLOR, Constants::TEXT_FONT, Constants::TEXT_MESSAGE); 
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
                    backgroundMusic->returnMusic().stop();
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
    //run game states
    if(!gameEnd){
        //respawn objects here later
    }
    else {
        playerSprite->setMoveState(false);

        for(auto& slime : slimes)
            slime->setMoveState(false);

        for(auto& bullet : bullets)
            bullet->setMoveState(false);

        for(auto& bush : bushes)
            bush->setMoveState(false);
    }

    //run game events
    if(mouseClicked){

    }
    if(spaceBpressed){

    }       
}

void GameManager::updateSprites() {
    try {
        if (playerSprite->getMoveState()) {
            playerSprite->changeAnimation(deltaTime);  
            playerSprite->updatePlayer();   
        }

        for (auto& slime : slimes) {
            if (slime->getMoveState()) {
                slime->changeAnimation(deltaTime);  
                slime->updateObstacle();
            }
        }

        for (auto& bush : bushes) {
            if (bush->getMoveState()) {
                bush->updateObstacle();
            }
        }

        for (auto& bullet : bullets) {
            if (bullet->getMoveState()) {
                bullet->updateBullet();
            }
        }

        window.display();
    } 
    
    catch (const std::exception& e) {
        std::cerr << "Exception in updateSprites: " << e.what() << std::endl;
    }
}

void GameManager::restartGame(){
    playerSprite->setMoveState(true);

    for(auto& slime : slimes)
        slime->setMoveState(true);

    for(auto& bullet : bullets)
        bullet->setMoveState(true);

    for(auto& bush : bushes)
        bush->setMoveState(true); 
    
    gameEnd = false; 
}

void GameManager::draw(){
    try {
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
    } catch(const std::exception& e) {
        std::cerr << "Exception in draw: " << e.what() << std::endl;
    }
}

