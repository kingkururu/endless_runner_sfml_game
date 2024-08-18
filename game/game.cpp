//
//  game.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "game.hpp"
GameManager::GameManager() : window(sf::VideoMode(GameComponents.screenHeight, GameComponents.screenWidth), "sfml game 2", sf::Style::Titlebar | sf::Style::Close), rainRespawnTime(1.0), coinRespawnTime(3.0), lightningRespawnTime(10.0), playerSetRectTime(0.4), playerCurrentIndex(6) {
    window.setFramerateLimit(60);
    GameScore.score = 0; 
    GameScore.playerHit = 0; 
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

GameManager::~GameManager() {
    destroyAll();
    std::cout << "game destroyed" << std::endl; 
}

void GameManager::destroyAll(){
    if (background != nullptr) {
        delete background;
        background = nullptr;
    }
    
    if (playerSprite != nullptr) {
    delete playerSprite;
    playerSprite = nullptr;
    }

    for (Rain* rain : rainDrops) {
        if(rain != nullptr){
            delete rain;
            rain = nullptr;
        }
    }
    rainDrops.clear();

    for (Coin* coin : coins) {
        if(coin != nullptr){
            delete coin;
            coin = nullptr;
        }
    }
    coins.clear();
  
    for (Lightning* lightning : lightnings) {
        if(lightning != nullptr){
            delete lightning;
            lightning = nullptr;
        }
    }
    lightnings.clear();

    if(heart != nullptr){
        delete heart;
        heart = nullptr; 
    }

    for (TextClass* text : endMessage){
        if(text != nullptr){
            delete text;
            text = nullptr;
        }
    }
    endMessage.clear();

    if(scoreText != nullptr){
        delete scoreText;
        scoreText = nullptr; 
    }
    
    if(backgroundMusic != nullptr){
        delete backgroundMusic;
        backgroundMusic = nullptr;
    }

    if(playerDeadSound != nullptr){
        delete playerDeadSound;
        playerDeadSound = nullptr;
    }

    if(rainSound != nullptr){
        delete rainSound;
        rainSound = nullptr;
    }

    if(lightningSound != nullptr){
        delete lightningSound;
        lightningSound = nullptr;
    }

    if(coinSound != nullptr){
        delete coinSound;
        coinSound = nullptr;
    }
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
    backgroundMusic = new MusicClass("assets/sound/backgroundMusic.mp3");
    backgroundMusic->returnMusic()->play();
    
    playerDeadSound = new SoundClass("assets/sound/dead.wav");
    
    coinSound = new SoundClass("assets/sound/ding.wav");
    
    rainSound = new SoundClass("assets/sound/splash.wav");
    
    lightningSound = new SoundClass("assets/sound/thunder.mp3");

    rainAnimRect.push_back(sf::IntRect{0,28,113,193});
    Rain* rain = new Rain({static_cast<float>(std::rand() % GameComponents.screenWidth),0}, sf::Vector2f{0.2,0.2}, "assets/sprites/raindrop.png");
    rainDrops.push_back(rain);
    rain->setAnimation(rainAnimRect);
    rain->setRects(0); 
    
    Coin* coin = new Coin({static_cast<float>(std::rand() % GameComponents.screenWidth), 0}, sf::Vector2f{0.03, 0.03}, "assets/sprites/coin.png"); 
    coins.push_back(coin);
    
    for(int i = 0; i < 3; ++i){
        lightningAnimRect.push_back(sf::IntRect(40 * i, 0, 40, 209)); 
    }

    for(int i = 0; i < 6; ++i){
        heartAnimRect.push_back(sf::IntRect{0, 78 * i, 389, 78}); 
    }
    heart = new Heart({15, 0}, {0.7,0.7}, "assets/sprites/heart.png");  
    heart->setAnimation(heartAnimRect);
    heart->setRects(0);  

    scoreText = new TextClass({15, 50}, 50, sf::Color::Black, "assets/fonts/pixelFont.ttf", "score: " + std::to_string(GameScore.score));
    
    for(int i = 0; i < 14; ++i){
        playerAnimRect.push_back(sf::IntRect{43 * i, 0, 43, 42}); 
    }
    playerSprite = new Player({static_cast<float>(GameComponents.screenWidth / 2), static_cast<float>(GameComponents.screenHeight) - 65}, sf::Vector2f{1.5f,1.5f}, "assets/sprites/player.png");
    playerSprite->setAnimation(playerAnimRect);
    playerSprite->setRects(playerCurrentIndex); 

    background = new Sprite({0.0f, 0.0f}, {1.0,1.0}, "assets/sprites/background.png");
}

void GameManager::createMoreAssets(){
    if(rainRespawnTime <= 0){
        Rain* rain = new Rain({static_cast<float>(std::rand() % GameComponents.screenWidth),0}, sf::Vector2f{0.2,0.2}, "assets/sprites/raindrop.png");
        rainDrops.push_back(rain);
        rain->setAnimation(rainAnimRect);
        rain->setRects(0); 
        rainRespawnTime = std::max(0.1f, 1.0f - (GameComponents.globalTime / 80.0f));
    }

    if(coinRespawnTime <= 0){
        Coin* coin = new Coin({static_cast<float>(std::rand() % GameComponents.screenWidth),0}, sf::Vector2f{0.03,0.03}, "assets/sprites/coin.png");
        coins.push_back(coin);

        coinRespawnTime = 3.0f; 
    }

    if(lightningRespawnTime <= 0){
        Lightning* lightning = new Lightning({static_cast<float>(std::rand() % GameComponents.screenWidth) - 150, -100}, sf::Vector2f{3.9, 3.9}, "assets/sprites/lightning.png");
        lightnings.push_back(lightning); 
        lightning->setAnimation(lightningAnimRect); 
        lightning->setRects(0); 
        lightningSound->returnSound()->play();

        lightningRespawnTime = std::max(0.5f, 10.0f - (GameComponents.globalTime / 300.0f));
    }
}

void GameManager::countTime(){
    sf::Time frameTime = clock.restart();
    GameComponents.deltaTime = frameTime.asSeconds();
    GameComponents.globalTime += frameTime.asSeconds();
    rainRespawnTime -= GameComponents.deltaTime; 
    coinRespawnTime -= GameComponents.deltaTime;
    lightningRespawnTime -= GameComponents.deltaTime;
    lightningSetRectTime -= GameComponents.deltaTime;
    playerSetRectTime -= GameComponents.deltaTime; 
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
                    backgroundMusic->returnMusic()->stop();
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

void GameManager::checkEvent(){
    for (auto it = rainDrops.begin(); it != rainDrops.end();) {
        sf::FloatRect rainBounds = (*it)->returnSpritesShape().getGlobalBounds();
        if(playerSprite->returnSpritesShape().getGlobalBounds().intersects(rainBounds)) {
            --GameScore.playerHit; 
            delete *it; 
            it = rainDrops.erase(it); 
            rainSound->returnSound()->play();
        } else {
            ++it; 
        }
    }

    for (auto it = coins.begin(); it != coins.end();) {
        sf::FloatRect coinBounds = (*it)->returnSpritesShape().getGlobalBounds();
        if(playerSprite->returnSpritesShape().getGlobalBounds().intersects(coinBounds)) {
            GameScore.score += 100; 
            delete *it; 
            it = coins.erase(it); 
            coinSound->returnSound()->play();
        } else {
            ++it; 
        }
    }

    for (auto it = lightnings.begin(); it != lightnings.end();) {
        sf::FloatRect lightningBounds = (*it)->returnSpritesShape().getGlobalBounds();
        if(playerSprite->returnSpritesShape().getGlobalBounds().intersects(lightningBounds) && (*it)->getFirstIt()) {
            GameScore.playerHit -= 2; 
            (*it)->setFirstIt(false); 
            break;
        } else {
            ++it; 
        }
    }

    if(GameScore.playerHit <= -5){
        GameEvents.playerDead = true;
        std::cout << "final score: " << GameScore.score << std::endl; 
    }

    heart->setRects(GameScore.playerHit * -1);

    if(playerSetRectTime <= 0 && FlagEvents.aPressed){
        if(playerCurrentIndex < 0){
            playerCurrentIndex = 6;
        }
        --playerCurrentIndex; 
        playerSprite->setRects(playerCurrentIndex); 

    } else if(playerSetRectTime <= 0 && FlagEvents.dPressed){
        if(playerCurrentIndex > 13){
            playerCurrentIndex = 7;
        }
        ++playerCurrentIndex;
        playerSprite->setRects(playerCurrentIndex); 

    } else {
        if(playerCurrentIndex == 6){
            playerCurrentIndex = 7; 
            playerSprite->setRects(playerCurrentIndex);
        }
        else{
            playerCurrentIndex = 6;
            playerSprite->setRects(playerCurrentIndex); 
        }
    }
}

void GameManager::handleGameEvents(){
    if(GameEvents.playerDead){
        endingText = "player dead! \ntotal time elapsed:\n";
        playerDeadSound->returnSound()->play();
        GameEvents.gameEnd = true;
    }
    
    if(GameEvents.gameEnd){
        endingText.append(std::to_string(GameComponents.globalTime));
        endingText.append(" seconds\n press B to replay");
        TextClass* endMessage1 = new TextClass({15, static_cast<float>(GameComponents.screenHeight)/3}, 40, sf::Color::Magenta, "assets/fonts/pixelFont.ttf", endingText);
        endMessage.push_back(endMessage1);
        
        backgroundMusic->returnMusic()->stop();
        
        for(const auto& rain : rainDrops){
            rain->setMoveState(false);
        }
        for(const auto& coin : coins){
            coin->setMoveState(false);
        }
        for(const auto& lightning : lightnings){
            lightning->setMoveState(false);
        }

        playerSprite->setMoveState(false); 
    }
}

void GameManager::updateSprites() {
     for (Lightning* lightning : lightnings) {
        lightning->updateLightning();
    }

    for (Rain* rain : rainDrops){
        if(rain->getMoveState())
            rain->updateRain();
    }

    for (Coin* coin : coins){
        if(coin->getMoveState())
            coin->updateCoin();
    }

    if(playerSprite->getMoveState())
        playerSprite->updatePlayer();

    scoreText->updateText("score: " + std::to_string(GameScore.score)); 
}

void GameManager::draw() {
    window.clear();
    window.draw(background->returnSpritesShape());
    
    for (Rain* rain : rainDrops){
        if(rain->getVisibleState())
            window.draw(rain->returnSpritesShape());
    }
     for (Coin* coin : coins){
        if(coin->getVisibleState())
            window.draw(coin->returnSpritesShape());
    }
    for (Lightning* lightning : lightnings){
        if(lightning->getVisibleState())
            window.draw(lightning->returnSpritesShape());
    }
    window.draw(playerSprite->returnSpritesShape());
    
    window.draw(heart->returnSpritesShape()); 

    if(scoreText->getVisibleState())
        window.draw(*scoreText->getText());

    for (TextClass* text : endMessage){
        if(text->getVisibleState())
            window.draw(*text->getText());
    }
    
    window.display();
}

void GameManager::deleteAssets() {
    for (auto it = rainDrops.begin(); it != rainDrops.end();) {
        Rain* rain = *it;
        if(rain->getVisibleState()) {
            ++it;
        } else {
            if(rain != nullptr){
                delete rain;
                rain = nullptr;
                it = rainDrops.erase(it);
            }
        }
    }
    for (auto it = coins.begin(); it != coins.end();) {
        Coin* coin = *it;
        if(coin->getVisibleState()) {
            ++it;
        } else {
            if(coin != nullptr){
                delete coin;
                coin = nullptr;
                it = coins.erase(it);
            }
        }
    }
    for (auto it = lightnings.begin(); it != lightnings.end();) {
        Lightning* lightning = *it;
        if(lightning->getVisibleState()) {
            ++it;
        } else {
            if(lightning != nullptr){
                delete lightning;
                lightning = nullptr;
                it = lightnings.erase(it);
            }
        }
    }
}

void GameManager::restartGame(){
    std::cout << "new game" << std::endl;

    window.clear();
    
    GameEvents.gameEnd = false;
    GameEvents.playerDead = false;
    
    GameComponents.globalTime = 0.0f;
    endMessage.clear();
    endingText = "";

    GameScore.playerHit = 0;
    GameScore.score = 0;

    playerSprite->setMoveState(true);

     for (Rain* rain : rainDrops){
        rain->setMoveState(true); 
    }
    for (Coin* coin : coins){
        coin->setMoveState(true);
    }
    for (Lightning* lightning : lightnings){
        lightning->setMoveState(true);
    }
    backgroundMusic->returnMusic()->play();
}

