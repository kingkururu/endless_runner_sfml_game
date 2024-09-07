//
//  scenes.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "scenes.hpp"

Scene::Scene() : slimeRespTime(Constants::SLIME_INITIAL_RESPAWN_TIME), bushRespTime(Constants::BUSH_INITIAL_RESPAWN_TIME), bulletRespTime(Constants::BULLET_RESPAWN_TIME){}

void Scene::createAssets() {
    try {
        // Initialize assets
        background = std::make_unique<Background>(Constants::BACKGROUND_POSITION, Constants::BACKGROUND_SCALE, Constants::BACKGROUND_TEXTURE);
        playerSprite = std::make_unique<Player>(Constants::PLAYER_POSITION, Constants::PLAYER_SCALE, Constants::PLAYER_TEXTURE, Constants::PLAYERSPRITE_RECTS, Constants::PLAYERANIM_MAX_INDEX, utils::convertToWeakPtrVector(Constants::PLAYER_BITMASKS));
        playerSprite->setRects(0);
        bullets.push_back(std::make_unique<Bullet>(Constants::BULLET_POSITION, Constants::BULLET_SCALE, Constants::BULLET_TEXTURE, Constants::BULLETSPRITES_RECTS, Constants::BULLETANIM_MAX_INDEX, utils::convertToWeakPtrVector(Constants::BULLET_BITMASKS)));
        bullets[0]->setVisibleState(false); 
        bushes.push_back(std::make_unique<Obstacle>(Constants::BUSH_POSITION, Constants::BUSH_SCALE, Constants::BUSH_TEXTURE, Constants::BUSHSPRITES_RECTS, Constants::BUSHANIM_MAX_INDEX, utils::convertToWeakPtrVector(Constants::BUSH_BITMASKS)));
        slimes.push_back(std::make_unique<Obstacle>(Constants::makeSlimePosition(), Constants::SLIME_SCALE, Constants::SLIME_TEXTURE, Constants::SLIMESPRITE_RECTS, Constants::SLIMEANIM_MAX_INDEX, utils::convertToWeakPtrVector(Constants::SLIME_BITMASKS)));
        slimes[0]->setRects(0);
        slimes[0]->setDirectionVector(Constants::SLIME_FALL_ANGLE);

        // Initialize sounds and music
        playerDeadSound = std::make_unique<SoundClass>(Constants::PLAYERDEAD_SOUNDBUFF, Constants::PLAYERDEADSOUND_VOLUME);
        playerJumpSound = std::make_unique<SoundClass>(Constants::PLAYERJUMP_SOUNDBUFF, Constants::PLAYERJUMPSOUND_VOLUME);
        bulletSound = std::make_unique<SoundClass>(Constants::BULLET_SOUNDBUFF, Constants::BULLETSOUND_VOLUME);
        obstHitSound = std::make_unique<SoundClass>(Constants::OBSTHIT_SOUNDBUFF, Constants::OBSTHITSOUND_VOLUME);
        backgroundMusic = std::make_unique<MusicClass>(std::move(Constants::BACKGROUNDMUSIC_MUSIC), Constants::BACKGROUNDMUSIC_VOLUME);
        if(backgroundMusic)
            backgroundMusic->returnMusic().play();

        // Initialize text
        endingText = std::make_unique<TextClass>(Constants::TEXT_POSITION, Constants::TEXT_SIZE, Constants::TEXT_COLOR, Constants::TEXT_FONT, Constants::TEXT_MESSAGE);
        } 

    catch (const std::exception& e) {
        std::cerr << "Exception caught in createAssets: " << e.what() << std::endl;
    }
}

void Scene::respawnAssets(){
    if(slimeRespTime <= 0){
        float newSlimeInterval = Constants::SLIME_INITIAL_RESPAWN_TIME - (globalTime * Constants::SLIME_INTERVAL_DECREMENT);
        slimes.push_back(std::make_unique<Obstacle>(Constants::makeSlimePosition(), Constants::SLIME_SCALE, Constants::SLIME_TEXTURE, Constants::SLIMESPRITE_RECTS, Constants::SLIMEANIM_MAX_INDEX, utils::convertToWeakPtrVector(Constants::SLIME_BITMASKS)));
        slimes[slimes.size() - 1]->setRects(0);
        slimes[slimes.size() - 1]->setDirectionVector(Constants::SLIME_FALL_ANGLE);

        slimeRespTime = std::max(newSlimeInterval, Constants::SLIME_INITIAL_RESPAWN_TIME);
    }
    if(bushRespTime <= 0){
        float newBushInterval = Constants::BUSH_INITIAL_RESPAWN_TIME - (globalTime * Constants::BUSH_INTERVAL_DECREMENT);
        bushes.push_back(std::make_unique<Obstacle>(Constants::BUSH_POSITION, Constants::BUSH_SCALE, Constants::BUSH_TEXTURE, Constants::BUSHSPRITES_RECTS, Constants::BUSHANIM_MAX_INDEX, utils::convertToWeakPtrVector(Constants::BUSH_BITMASKS)));
        bushRespTime = std::max(newBushInterval, Constants::BUSH_INITIAL_RESPAWN_TIME);
    }
} 

void Scene::spawnBullets(){
    if (bulletRespTime <= 0){
        bullets.push_back(std::make_unique<Bullet>(playerSprite->getSpritePos() + Constants::BULLET_POS_OFFSET, Constants::BULLET_SCALE, Constants::BULLET_TEXTURE, Constants::BULLETSPRITES_RECTS, Constants::BULLETANIM_MAX_INDEX, utils::convertToWeakPtrVector(Constants::BULLET_BITMASKS)));
        bullets[bullets.size() - 1]->setDirectionVector(mouseClickedPos);
        bulletRespTime = Constants::BULLET_RESPAWN_TIME; 
        if(bulletSound)
            bulletSound->returnSound().play(); 
    }
} 

void Scene::setTime(float deltaT, float globalT){
    globalTime = globalT;
    deltaTime = deltaT;  
    slimeRespTime -= deltaTime; 
    bulletRespTime -= deltaTime; 
    bushRespTime -= deltaTime; 
} 

void Scene::setMouseClickedPos(sf::Vector2i mousePos){
    mouseClickedPos = mousePos; 
} 

void Scene::draw(sf::RenderWindow& window) {
    try {
        window.clear();

        if (background && background->getVisibleState()) {
            window.draw(background->returnSpritesShape());
            window.draw(background->returnSpritesShape2());
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
       // Update background if it should move
        if (background && background->getBackgroundMoveState()) {
            background->updateBackground(deltaTime, Constants::BACKGROUND_SPEED);
        } 
        // Update player if it should move
        if (playerSprite && playerSprite->getMoveState()) {
            playerSprite->changeAnimation(deltaTime);
            playerSprite->updatePos();
        } 
        // Update slimes
        for (auto& slime : slimes) {
            if (slime) { // Check if slime pointer is not null
                if (slime->getMoveState()) {
                    slime->changePosition(physics::follow(deltaTime, Constants::SLIME_SPEED, slime->getSpritePos(), Constants::SLIME_ACCELERATION, slime->getDirectionVector()));
                    slime->changeAnimation(deltaTime);
                    slime->updatePos();
                }
            } else {
                std::cerr << "Error: slime pointer is null" << std::endl;
            }
        }

        // Update bushes
        for (auto& bush : bushes) {
            if (bush) { // Check if bush pointer is not null
                if (bush->getMoveState()) {
                    bush->changePosition(physics::moveLeft(deltaTime, Constants::BUSH_SPEED, bush->getSpritePos(), Constants::BUSH_ACCELERATION));
                    bush->updatePos();
                }
            } else {
                std::cerr << "Error: bush pointer is null" << std::endl;
            }
        }

        // Update bullets
        for (auto& bullet : bullets) {
            if (bullet) { 
                if (bullet->getMoveState()) {
                    bullet->changePosition(physics::follow(deltaTime, Constants::BULLET_SPEED, bullet->getSpritePos(), Constants::BULLET_ACCELERATION, bullet->getDirectionVector()));
                    bullet->updatePos();
                }
            } else {
                std::cerr << "Error: bullet pointer is null" << std::endl;
            }
        }

        // Remove invisible sprites
        deleteInvisibleSprites();
    }

    catch (const std::exception& e) {
        std::cerr << "Exception in updateSprites: " << e.what() << std::endl;
    }
}

void Scene::handleInput() {

    if(playerSprite && playerSprite->getMoveState()){
        if(FlagEvents.sPressed){
            playerSprite->updatePlayer(physics::moveDown(deltaTime, Constants::PLAYER_SPEED, playerSprite->getSpritePos())); 
        }
        if(FlagEvents.wPressed){
            playerSprite->updatePlayer(physics::moveUp(deltaTime, Constants::PLAYER_SPEED, playerSprite->getSpritePos())); 
        }
        if(FlagEvents.mouseClicked){
            spawnBullets(); 
        }
    }

    if(FlagEvents.bPressed && backgroundMusic){
        backgroundMusic->returnMusic().stop(); 
        restart();
    }
}

void Scene::handleGameEvents() { 
    // increase score
    for (auto it = slimes.begin(); it != slimes.end(); ) {
        if ((*it) && (*it)->getSpritePos().x < playerSprite->getSpritePos().x - Constants::PASSTHROUGH_OFFSET){
            ++score; 
            (*it)->setVisibleState(false); 
            it = slimes.erase(it);
        } else {
            ++it; 
        }
    }
    for (auto it = bushes.begin(); it != bushes.end(); ) {
        if ((*it) && (*it)->getSpritePos().x < playerSprite->getSpritePos().x - Constants::PASSTHROUGH_OFFSET){
            ++score; 
            (*it)->setVisibleState(false); 
            it = bushes.erase(it);
        } else {
            ++it; 
        }
    }

    // player vs bush collision 
    bool bushCollision = physics::checkCollisions( playerSprite, bushes, physics::pixelPerfectCollisionHelper);  
    bool slimeCollision = physics::checkCollisions( playerSprite, slimes, physics::pixelPerfectCollisionHelper); 

    if(physics::checkCollisions( bullets, slimes, physics::boundingBoxCollisionHelper)){
       ++score; 
       obstHitSound->returnSound().play(); 
    } 

    if(bushCollision || slimeCollision){
        std::cout << "Ending Game" << std::endl;
        FlagEvents.gameEnd = true; 
        
        if(playerDeadSound)
            playerDeadSound->returnSound().play();
        if(backgroundMusic)
            backgroundMusic->returnMusic().pause(); 
    }

    if(endingText)
        endingText->updateText("current score: " + std::to_string(score)); 
} 

void Scene::handleGameFlags(){
    if(FlagEvents.gameEnd){
        if(background)
            background->setBackgroundMoveState(false); 

        if(playerSprite)
            playerSprite->setMoveState(false);
       //playerSprite->setAnimChangeState(false);

       for (auto& slime : slimes) {
            if(slime){
                slime->setMoveState(false);
                //slime->setAnimChangeState(false);
            }
        }

        for (auto& bullet : bullets) {
            if(bullet)
                bullet->setMoveState(false);
        }

        for (auto& bush : bushes) {
            if(bush)
                bush->setMoveState(false);
        }

        endingText->updateText("Player dead!\nFinal score: " + std::to_string(score)); 
    }
}

void Scene::restart() {
    if(backgroundMusic)
        backgroundMusic->returnMusic().play();

    if (background)
        background->setBackgroundMoveState(true); 

    if(playerSprite){
        playerSprite->setMoveState(true);
        playerSprite->changePosition(Constants::PLAYER_POSITION);
        std::cout << "set player pos at" << Constants::PLAYER_POSITION.x << "and " << Constants::PLAYER_POSITION.y << std::endl; 
    }

    for (auto& slime : slimes) {
        if(slime){
            slime->setMoveState(true);
            slime->changePosition(Constants::makeSlimePosition()); 
            std::cout << "set slime pos at" << slime->getSpritePos().x << "and " << slime->getSpritePos().y << std::endl; 
        }
    }

    for (auto& bullet : bullets) {
        if(bullet){
            bullet->setMoveState(true);
            bullet->changePosition(Constants::BULLET_POSITION); 
            std::cout << "set bullet pos at" << bullet->getSpritePos().x << "and " << bullet->getSpritePos().y << std::endl; 

        }
    }

    for (auto& bush : bushes) {
        if(bush){
            bush->setMoveState(true);
            bush->changePosition(Constants::BUSH_POSITION);
            std::cout << "set bush pos at" << bush->getSpritePos().x << "and " << bush->getSpritePos().y << std::endl; 

        }
    }

    FlagEvents.resetFlags(); 

    score = 0;

    if(endingText)
        endingText->updateText("current score: " + std::to_string(score)); 
}

void Scene::deleteInvisibleSprites() {
    // Remove invisible slimes
    auto slimeIt = std::remove_if(slimes.begin(), slimes.end(),
                                  [](const std::unique_ptr<Obstacle>& slime) { 
                                    if(slime){
                                        return !slime->getVisibleState();
                                    } 
                                    return false;
                                    });
    slimes.erase(slimeIt, slimes.end());

    // Remove invisible bushes
    auto bushIt = std::remove_if(bushes.begin(), bushes.end(),
                                 [](const std::unique_ptr<Obstacle>& bush) { 
                                    if(bush){
                                        return !bush->getVisibleState();
                                    } 
                                    return false;
                                    });
    bushes.erase(bushIt, bushes.end());

    // Remove invisible bullets
    auto bulletIt = std::remove_if(bullets.begin(), bullets.end(),
                                   [](const std::unique_ptr<Bullet>& bullet) { 
                                    if(bullet){
                                        return !bullet->getVisibleState();
                                    } 
                                    return false;
                                    });
    bullets.erase(bulletIt, bullets.end()); 
}