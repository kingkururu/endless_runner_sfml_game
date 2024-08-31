//
//  scenes.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "scenes.hpp"

Scene::Scene() : window(), slimeRespTime(Constants::SLIME_INITIAL_RESPAWN_TIME), bushRespTime(Constants::BUSH_INITIAL_RESPAWN_TIME), bulletRespTime(Constants::BULLET_RESPAWN_TIME) {}

void Scene::createAssets() {
    try {
        // Initialize assets
        background = std::make_unique<Background>(Constants::BACKGROUND_POSITION, Constants::BACKGROUND_SCALE, Constants::BACKGROUND_TEXTURE);
        playerSprite = std::make_unique<Player>(Constants::PLAYER_POSITION, Constants::PLAYER_SCALE, Constants::PLAYER_TEXTURE, Constants::PLAYERSPRITE_RECTS, Constants::PLAYERANIM_MAX_INDEX, Constants::PLAYER_BITMASK);
        playerSprite->setRects(0);
        bullets.push_back(std::make_unique<Bullet>(Constants::BULLET_POSITION, Constants::BULLET_SCALE, Constants::BULLET_TEXTURE, Constants::BULLETSPRITES_RECTS, Constants::BULLETANIM_MAX_INDEX, Constants::BULLET_BITMASK));
        bushes.push_back(std::make_unique<Obstacle>(Constants::BUSH_POSITION, Constants::BUSH_SCALE, Constants::BUSH_TEXTURE, Constants::BUSHSPRITES_RECTS, Constants::BUSHANIM_MAX_INDEX, Constants::BUSH_BITMASK));
        slimes.push_back(std::make_unique<Obstacle>(Constants::SLIME_POSITION, Constants::SLIME_SCALE, Constants::SLIME_TEXTURE, Constants::SLIMESPRITE_RECTS, Constants::SLIMEANIM_MAX_INDEX, Constants::SLIME_BITMASK));
        slimes[0]->setRects(0);

        // Initialize sounds and music
        playerDeadSound = std::make_unique<SoundClass>(Constants::PLAYERDEAD_SOUNDBUFF, Constants::PLAYERDEADSOUND_VOLUME);
        playerJumpSound = std::make_unique<SoundClass>(Constants::PLAYERJUMP_SOUNDBUFF, Constants::PLAYERJUMPSOUND_VOLUME);
        bulletSound = std::make_unique<SoundClass>(Constants::BULLET_SOUNDBUFF, Constants::BULLETSOUND_VOLUME);
        obstHitSound = std::make_unique<SoundClass>(Constants::OBSTHIT_SOUNDBUFF, Constants::OBSTHITSOUND_VOLUME);
        backgroundMusic = std::make_unique<MusicClass>(std::move(Constants::BACKGROUNDMUSIC_MUSIC), Constants::BACKGROUNDMUSIC_VOLUME);
        backgroundMusic->returnMusic().play();

        // Initialize text
        endingText = std::make_unique<TextClass>(Constants::TEXT_POSITION, Constants::TEXT_SIZE, Constants::TEXT_COLOR, Constants::TEXT_FONT, Constants::TEXT_MESSAGE);
    } 

    catch (const std::exception& e) {
        std::cerr << "Exception caught in createAssets: " << e.what() << std::endl;
    }
}

void Scene::createMoreAssets(){
    if(slimeRespTime <= 0){
        float newSlimeInterval = Constants::SLIME_INITIAL_RESPAWN_TIME - (globalTime * Constants::SLIME_INTERVAL_DECREMENT);
        slimes.push_back(std::make_unique<Obstacle>(Constants::SLIME_POSITION, Constants::SLIME_SCALE, Constants::SLIME_TEXTURE, Constants::SLIMESPRITE_RECTS, Constants::SLIMEANIM_MAX_INDEX, Constants::SLIME_BITMASK));
        slimes[0]->setRects(0);
        slimeRespTime = std::max(newSlimeInterval, Constants::SLIME_INITIAL_RESPAWN_TIME);
    }
    if(bushRespTime <= 0){
        float newBushInterval = Constants::BUSH_INITIAL_RESPAWN_TIME - (globalTime * Constants::BUSH_INTERVAL_DECREMENT);
        bushes.push_back(std::make_unique<Obstacle>(Constants::BUSH_POSITION, Constants::BUSH_SCALE, Constants::BUSH_TEXTURE, Constants::BUSHSPRITES_RECTS, Constants::BUSHANIM_MAX_INDEX, Constants::BUSH_BITMASK));
        bushRespTime = std::max(newBushInterval, Constants::BUSH_INITIAL_RESPAWN_TIME);
    }
} 

void Scene::setTime(float deltaT, float globalT){
    globalTime = globalT;
    deltaTime = deltaT;  
    slimeRespTime -= deltaTime; 
    bulletRespTime -= deltaTime; 
    bushRespTime -= deltaTime; 
} 

void Scene::draw(sf::RenderWindow& window) {
    try {
        window.clear();

        if (background && background->getVisibleState()) {
            window.draw(background->returnSpritesShape());
        }
        if (playerSprite && playerSprite->getVisibleState()) {
            window.draw(playerSprite->returnSpritesShape());
        }
        for (const auto& bullet : bullets) {
            if (bullet && bullet->getVisibleState()) {
                window.draw(bullet->returnSpritesShape());
            }
        }
        for (const auto& bush : bushes) {
            if (bush && bush->getVisibleState()) {
                window.draw(bush->returnSpritesShape());
            }
        }
        for (const auto& slime : slimes) {
            if (slime && slime->getVisibleState()) {
                window.draw(slime->returnSpritesShape());
            }
        }
        if (endingText && endingText->getVisibleState()) {
            window.draw(endingText->getText());
        }

        window.display(); 

    } 
    
    catch (const std::exception& e) {
        std::cerr << "Exception in draw: " << e.what() << std::endl;
    }
}

void Scene::update() {
    try {
        playerSprite->changeAnimation(deltaTime);
        playerSprite->updatePos(); 

        for (auto& slime : slimes) {
            if (slime->getMoveState()) {
                slime->updateObstacle(physics::moveLeft(deltaTime, Constants::SLIME_SPEED, slime->getSpritePos(), Constants::SLIME_ACCELERATION)); 
                slime->changeAnimation(deltaTime);
                slime->updatePos();
            }
        }

        for (auto& bush : bushes) {
            if (bush->getMoveState()) {
                bush->updateObstacle(physics::moveLeft(deltaTime, Constants::BUSH_SPEED, bush->getSpritePos(), Constants::BUSH_ACCELERATION)); 
                bush->updatePos();
            }
        }

        for (auto& bullet : bullets) {
            if (bullet->getMoveState()) {
               // bullet->updateBullet(); 
                bullet->updatePos();
            }
        }

    } 
    
    catch (const std::exception& e) {
        std::cerr << "Exception in updateSprites: " << e.what() << std::endl;
    }
}

void Scene::handleInput() {

    if(playerSprite->getMoveState()){
        if(FlagEvents.aPressed){
            playerSprite->updatePlayer(physics::moveLeft(deltaTime, Constants::PLAYER_SPEED, playerSprite->getSpritePos())); 
        } 
        if(FlagEvents.sPressed){
            playerSprite->updatePlayer(physics::moveDown(deltaTime, Constants::PLAYER_SPEED, playerSprite->getSpritePos())); 
        }
        if(FlagEvents.wPressed){
            playerSprite->updatePlayer(physics::moveUp(deltaTime, Constants::PLAYER_SPEED, playerSprite->getSpritePos())); 
        }
        if(FlagEvents.dPressed){
            playerSprite->updatePlayer(physics::moveRight(deltaTime, Constants::PLAYER_SPEED, playerSprite->getSpritePos())); 
        }

        if(FlagEvents.spacePressed){

        }
        if(FlagEvents.mouseClicked){

        }
    }

    if(FlagEvents.bPressed){
        restart();
    }
}

void Scene::handleGameEvents() { 
    if(FlagEvents.gameEnd){
       playerSprite->setMoveState(true);
       
       for (auto& slime : slimes) {
            slime->setMoveState(true);
        }

        for (auto& bullet : bullets) {
            bullet->setMoveState(true);
        }

        for (auto& bush : bushes) {
            bush->setMoveState(true);
        }
    }
}

void Scene::restart() {
    playerSprite->setMoveState(true);

    for (auto& slime : slimes) {
        slime->setMoveState(true);
    }

    for (auto& bullet : bullets) {
        bullet->setMoveState(true);
    }

    for (auto& bush : bushes) {
        bush->setMoveState(true);
    }

    FlagEvents.resetFlags(); 
}

void Scene::deleteInvisibleSprites() {
    // Remove invisible slimes
    auto slimeIt = std::remove_if(slimes.begin(), slimes.end(),
                                  [](const std::unique_ptr<Obstacle>& slime) { return !slime->getVisibleState(); });
    slimes.erase(slimeIt, slimes.end());

    // Remove invisible bushes
    auto bushIt = std::remove_if(bushes.begin(), bushes.end(),
                                 [](const std::unique_ptr<Obstacle>& bush) { return !bush->getVisibleState(); });
    bushes.erase(bushIt, bushes.end());

    // Remove invisible bullets
    auto bulletIt = std::remove_if(bullets.begin(), bullets.end(),
                                   [](const std::unique_ptr<Bullet>& bullet) { return !bullet->getVisibleState(); });
    bullets.erase(bulletIt, bullets.end());
}