//
//  scenes.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "scenes.hpp"

Scene::Scene() : window() {}

void Scene::createAssets() {
    try {
        // Initialize assets
        background = std::make_unique<Background>(Constants::BACKGROUND_POSITION, Constants::BACKGROUND_SCALE, Constants::BACKGROUND_TEXTURE);
        playerSprite = std::make_unique<Player>(Constants::PLAYER_POSITION, Constants::PLAYER_SCALE, Constants::PLAYER_TEXTURE, Constants::PLAYERSPRITE_RECTS, Constants::PLAYER_SPEED, Constants::PLAYERANIM_MAX_INDEX, Constants::PLAYER_BITMASK);
        playerSprite->setRects(0);
        bullets.push_back(std::make_unique<Bullet>(Constants::BULLET_POSITION, Constants::BULLET_SCALE, Constants::BULLET_TEXTURE, Constants::BULLETSPRITES_RECTS, Constants::BULLET_SPEED, Constants::BULLETANIM_MAX_INDEX, Constants::BULLET_BITMASK));
        bushes.push_back(std::make_unique<Obstacle>(Constants::BUSH_POSITION, Constants::BUSH_SCALE, Constants::BUSH_TEXTURE, Constants::BUSHSPRITES_RECTS, Constants::BUSH_SPEED, Constants::BUSHANIM_MAX_INDEX, Constants::BUSH_BITMASK));
        slimes.push_back(std::make_unique<Obstacle>(Constants::SLIME_POSITION, Constants::SLIME_SCALE, Constants::SLIME_TEXTURE, Constants::SLIMESPRITE_RECTS, Constants::SLIME_SPEED, Constants::SLIMEANIM_MAX_INDEX, Constants::SLIME_BITMASK));
        slimes[0]->setRects(0);

        // Initialize sounds and music
        playerDeadSound = std::make_unique<SoundClass>(Constants::PLAYERDEAD_SOUNDBUFF, Constants::PLAYERDEADSOUND_VOLUME);
        playerJumpSound = std::make_unique<SoundClass>(Constants::PLAYERJUMP_SOUNDBUFF, Constants::PLAYERJUMPSOUND_VOLUME);
        bulletSound = std::make_unique<SoundClass>(Constants::BULLET_SOUNDBUFF, Constants::BULLETSOUND_VOLUME);
        obstHitSound = std::make_unique<SoundClass>(Constants::OBSTHIT_SOUNDBUFF, Constants::OBSTHITSOUND_VOLUME);
        backgroundMusic = std::make_unique<MusicClass>(Constants::BACKGROUNDMUSIC_MUSIC, Constants::BACKGROUNDMUSIC_VOLUME);
        backgroundMusic->returnMusic().play();

        // Initialize text
        endingText = std::make_unique<TextClass>(Constants::TEXT_POSITION, Constants::TEXT_SIZE, Constants::TEXT_COLOR, Constants::TEXT_FONT, Constants::TEXT_MESSAGE);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in createAssets: " << e.what() << std::endl;
    }
}

void Scene::update(float deltaTime) {
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
    } catch (const std::exception& e) {
        std::cerr << "Exception in updateSprites: " << e.what() << std::endl;
    }
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

        window.display(); // Display the drawn frame
    } catch (const std::exception& e) {
        std::cerr << "Exception in draw: " << e.what() << std::endl;
    }
}

void Scene::handleInput(const sf::Event& event) {
    // Handle input specific to the scene
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
}
