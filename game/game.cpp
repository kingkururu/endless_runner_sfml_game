//
//  game.cpp
//  sfmlgame1
//
//  Created by Sunmyoung Yun on 2024/01/29.
//

#include "game.hpp"
GameManager::GameManager() : window(sf::VideoMode(GameComponents.screenHeight, GameComponents.screenWidth), "sfml game tut") {
    window.setFramerateLimit(30);
}

GameManager::~GameManager() {
    destroyAll();
}

void GameManager::destroyAll(){
    for (Enemy* enemy : enemySprite) {
        delete enemy;
        enemy = nullptr;
    }
    enemySprite.clear();
    for (Bullet* bullet : bullets) {
        delete bullet;
        bullet = nullptr;
    }
    bullets.clear();
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
    delete bulletSound;
    bulletSound = nullptr;
    delete enemyDeadSound;
    enemyDeadSound = nullptr;
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
            checkEvent();
            handleGameEvents();
            deleteAssets();
        }
        updateSprites();
        handleEventInput();
        draw();
    }
}

void GameManager::createAssets( ){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

   for (int i = 0; i< GameComponents.enemyNum; i++){
        Enemy* enemy = new Enemy( sf::Vector2f{
            static_cast<float>(GameComponents.screenWidth - 900),
            static_cast<float>(rand() % GameComponents.screenHeight)
        }, sf::Vector2f{0.2,0.2}, "/Users/student/projects/sfmlgame1/sfmlgame1/assets/sprites/3.png");
        enemySprite.push_back(enemy);
   }
    playerSprite = new Player(sf::Vector2f{0.0f, 50.0f}, sf::Vector2f{0.2,0.2}, "/Users/student/projects/sfmlgame1/sfmlgame1/assets/sprites/1.png");
    background = new Sprite(sf::Vector2f{0.0f, 0.0f}, sf::Vector2f{1.0,1.0}, "/Users/student/projects/sfmlgame1/sfmlgame1/assets/sprites/4.png");
    backgroundMusic = new MusicClass("/Users/student/projects/sfmlgame1/sfmlgame1/assets/sound/backgroundMusic.ogg");
    backgroundMusic->returnMusic()->play();
    bulletSound = new SoundClass("/Users/student/projects/sfmlgame1/sfmlgame1/assets/sound/bulletSound.wav");
    enemyDeadSound = new SoundClass("/Users/student/projects/sfmlgame1/sfmlgame1/assets/sound/enemyDead.wav");
    playerDeadSound = new SoundClass("/Users/student/projects/sfmlgame1/sfmlgame1/assets/sound/playerDead.wav");
    victorySound = new SoundClass("/Users/student/projects/sfmlgame1/sfmlgame1/assets/sound/victorySound.wav");
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
                case sf::Keyboard::W:
                    FlagEvents.wPressed = true;
                    break;
                case sf::Keyboard::S:
                    FlagEvents.sPressed = true;
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
            FlagEvents.wPressed = false;
            FlagEvents.sPressed = false;
        }
        if (event.type == sf::Event::MouseButtonPressed){
            GameComponents.mouseClickedPos = sf::Mouse::getPosition(window);
            FlagEvents.mouseClicked = true;
        }
        if (event.type == sf::Event::MouseButtonReleased){
            FlagEvents.mouseClicked = false;
        }
    }
}

void GameManager::checkEvent(){
    for (const auto& enemy : enemySprite) {
           sf::FloatRect enemyBounds = enemy->returnSpritesShape().getGlobalBounds();
           if(playerSprite->returnSpritesShape().getGlobalBounds().intersects(enemyBounds)) {
               GameEvents.playerDead = true;
           }
       }
    for (auto bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter) {
            for (auto enemy : enemySprite) {
                sf::FloatRect bulletBounds = (*bulletIter)->returnSpritesShape().getGlobalBounds();
                sf::FloatRect enemyBounds = enemy->returnSpritesShape().getGlobalBounds();

                if (bulletBounds.intersects(enemyBounds)) {
                    (*bulletIter)->setVisibleState(false);
                    enemy->setVisibleState(false);
                    enemyDeadSound->returnSound()->play();
                    break;
                }
            }
    }
    
    if(!enemySprite.size())
        GameEvents.playerWin = true;
}

void GameManager::handleGameEvents(){
   if(FlagEvents.mouseClicked){
        Bullet* bullet = new Bullet(playerSprite->getSpritePos(),sf::Vector2f{0.03,0.03}, "/Users/student/projects/sfmlgame1/sfmlgame1/assets/sprites/2.png");
            bullets.push_back(bullet);
        bulletSound->returnSound()->play();
    }
    
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
        
        for(const auto& enemy : enemySprite){
            enemy->setMoveState(false);
        }
    }
}

void GameManager::countTime(){
    sf::Time frameTime = clock.restart();
    GameComponents.deltaTime = frameTime.asSeconds();
    GameComponents.globalTime += frameTime.asSeconds();
}

void GameManager::updateSprites() {
    for (Enemy* enemy : enemySprite){
        if(enemy->getMoveState())
            enemy->updateEnemy(playerSprite->getSpritePos());
    }
    for (Bullet* bullet : bullets){
        if(bullet->getMoveState())
            bullet->updateBullet();
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
    for (Enemy* enemy : enemySprite){
        if(enemy->getVisibleState())
            window.draw(enemy->returnSpritesShape());
    }
    for (Bullet* bullet : bullets){
        if(bullet->getVisibleState())
            window.draw(bullet->returnSpritesShape());
    }
    window.draw(playerSprite->returnSpritesShape());
    
    window.display();
}

void GameManager::deleteAssets() {
    for (auto it = enemySprite.begin(); it != enemySprite.end();) {
        Enemy* enemy = *it;
        if(enemy->getVisibleState()) {
            ++it;
        } else {
            delete enemy;
            enemy = nullptr;
            it = enemySprite.erase(it);
        }
    }
    for (auto it = bullets.begin(); it != bullets.end();) {
        Bullet* bullet = *it;
        if(bullet->getVisibleState()) {
            ++it;
        } else {
            delete bullet;
            bullet = nullptr;
            it = bullets.erase(it);
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
