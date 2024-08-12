//
//  game.cpp
//  sfmlgame1
//
//  Created by Sunmyoung Yun on 2024/01/29.
//

#include "game.hpp"
GameManager::GameManager() : window(sf::VideoMode(GameComponents.screenHeight, GameComponents.screenWidth), "sfml game 2"), rainRespawnTime(1.0) {
    window.setFramerateLimit(30);
    GameScore.score = 100; 
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

GameManager::~GameManager() {
    destroyAll();
}

void GameManager::destroyAll(){
    for (Rain* rain : rainDrops) {
        delete rain;
        rain = nullptr;
    }
    rainDrops.clear();
  
    for (TextClass* text : endMessage){
        delete text;
        text = nullptr;
    }
    endMessage.clear();
    delete playerSprite;
    playerSprite = nullptr;
    delete background;
    background = nullptr;
    
    delete backgroundMusic;
    backgroundMusic = nullptr;
    delete playerDeadSound;
    playerDeadSound = nullptr;
    delete victorySound;
    victorySound = nullptr;
}

void GameManager::runGame() {
    createAssets();
    while (window.isOpen()) {
        if(!GameEvents.gameEnd){
            countTime();
            createMoreAssets(); 
            checkEvent();
            handleGameEvents();
            deleteAssets();
        }
        updateSprites();
        handleEventInput();
        draw();
    }
}

void GameManager::createAssets(){
    Rain* rain = new Rain({static_cast<float>(std::rand() % GameComponents.screenWidth),0}, sf::Vector2f{0.2,0.2}, "/Users/student/projects/sfml_game2/assets/sprites/raindrop.png");
    rainDrops.push_back(rain);
    playerSprite = new Player({static_cast<float>(GameComponents.screenWidth / 2), static_cast<float>(GameComponents.screenHeight) - 400}, sf::Vector2f{1.0f,1.0f}, "/Users/student/projects/sfml_game2/assets/sprites/player.png");
    background = new Sprite(sf::Vector2f{0.0f, 0.0f}, sf::Vector2f{1.0,1.0}, "/Users/student/projects/sfml_game2/assets/sprites/background.png");
    backgroundMusic = new MusicClass("/Users/student/projects/sfmlgame1/sfmlgame1/assets/sound/backgroundMusic.ogg");
    backgroundMusic->returnMusic()->play();
    playerDeadSound = new SoundClass("/Users/student/projects/sfmlgame1/sfmlgame1/assets/sound/playerDead.wav");
    victorySound = new SoundClass("/Users/student/projects/sfmlgame1/sfmlgame1/assets/sound/victorySound.wav");
}

void GameManager::createMoreAssets(){
    if(rainRespawnTime <= 0){
        Rain* rain = new Rain({static_cast<float>(std::rand() % GameComponents.screenWidth),0}, sf::Vector2f{0.2,0.2}, "/Users/student/projects/sfml_game2/assets/sprites/raindrop.png");
        rainDrops.push_back(rain);

        rainRespawnTime = 1.0f; 
    }

    if(!(GameScore.score % 500) && GameScore.firstIt){
        ++GameScore.itNum;
        GameScore.firstIt = false; 
        rainRespawnTime -= GameScore.itNum * 0.1; 
    }
}

void GameManager::countTime(){
    sf::Time frameTime = clock.restart();
    GameComponents.deltaTime = frameTime.asSeconds();
    GameComponents.globalTime += frameTime.asSeconds();
    rainRespawnTime -= GameComponents.deltaTime; 
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
                    destroyAll();
                    restartGame();
                    break;
                default:
                    break;
            }
        }
        else if (event.type == sf::Event::KeyReleased){
            FlagEvents.dPressed = false;
            FlagEvents.aPressed = false;
        }
    }
}

void GameManager::checkEvent(){
    for (auto it = rainDrops.begin(); it != rainDrops.end(); /* no increment here */) {
        sf::FloatRect rainBounds = (*it)->returnSpritesShape().getGlobalBounds();
        if(playerSprite->returnSpritesShape().getGlobalBounds().intersects(rainBounds)) {
            GameScore.score -= 100; 
            it = rainDrops.erase(it); 
        } else {
            ++it; 
        }
    }

    if(GameScore.score <= -500){
        GameEvents.playerDead = true;
        std::cout << GameScore.score; 
    }
}

void GameManager::handleGameEvents(){
    if(GameEvents.playerWin){
        endingText = "player wins! time elapsed:\n";
        victorySound->returnSound()->play();
        GameEvents.gameEnd = true;
    }
    else if(GameEvents.playerDead){
        endingText = "player lose! time elapsed:\n";
        playerDeadSound->returnSound()->play();
        GameEvents.gameEnd = true;
    }
    
    if(GameEvents.gameEnd){
        endingText.append(std::to_string(GameComponents.globalTime));
        endingText.append(" seconds");
        TextClass* endMessage1 = new TextClass(sf::Vector2f{0.0f, 0.0f}, 20, sf::Color::White, "/Users/student/projects/sfmlgame1/sfmlgame1/assets/fonts/arial.ttf", endingText);
        endMessage.push_back(endMessage1);
        
        backgroundMusic->returnMusic()->stop();
        
        for(const auto& rain : rainDrops){
            rain->setMoveState(false);
        }

        playerSprite->setMoveState(false); 
    }
}

void GameManager::updateSprites() {
    for (Rain* rain : rainDrops){
        if(rain->getMoveState())
            rain->updateRain(playerSprite->getSpritePos());
    }
    if(playerSprite->getMoveState())
        playerSprite->updatePlayer();
}

void GameManager::draw() {
    window.clear();
    window.draw(background->returnSpritesShape());
    
    for (TextClass* text : endMessage){
        if(text->getVisibleState())
            window.draw(*text->getText());
    }
    for (Rain* rain : rainDrops){
        if(rain->getVisibleState())
            window.draw(rain->returnSpritesShape());
    }
    window.draw(playerSprite->returnSpritesShape());
    
    window.display();
}

void GameManager::deleteAssets() {
    for (auto it = rainDrops.begin(); it != rainDrops.end();) {
        Rain* rain = *it;
        if(rain->getVisibleState()) {
            ++it;
        } else {
            delete rain;
            rain = nullptr;
            it = rainDrops.erase(it);
        }
    }
}

void GameManager::restartGame(){
    window.clear();
    std::cout << "new game" << std::endl;
    createAssets();
    
    GameEvents.gameEnd = false;
    GameEvents.playerWin = false;
    GameEvents.playerDead = false;
    
    GameComponents.globalTime = 0.0f;
    endMessage.clear();
    endingText = "";
}
