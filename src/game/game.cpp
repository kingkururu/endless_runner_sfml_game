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
    scene = std::make_unique<Scene>();
}

void GameManager::runGame() {
    try {
        scene->createAssets();
        while (window.isOpen()) {
            if (!FlagEvents.gameEnd) {
                countTime();
                scene->respawnAssets(); 
                scene->handleGameEvents(); 
            }
            scene->handleGameFlags(); 
            handleEventInput();
            scene->update();
            scene->draw(window);
        }
    } catch (const std::exception& e) {
        std::cerr << "exception in runGame: " << e.what() << std::endl;
    }
}

void GameManager::countTime() {
    sf::Time frameTime = clock.restart();
    globalTime += frameTime.asSeconds();

    scene->setTime(frameTime.asSeconds(), globalTime);
}

void GameManager::handleEventInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::A:
                    FlagEvents.aPressed = true;
                    break;
                case sf::Keyboard::S:
                    FlagEvents.sPressed = true;
                    break;
                case sf::Keyboard::W:
                    FlagEvents.wPressed = true;
                    break;
                case sf::Keyboard::D:
                    FlagEvents.dPressed = true;
                    break;
                case sf::Keyboard::B:
                    FlagEvents.bPressed = true;
                    break;
                default:
                    break;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            FlagEvents.flagKeyReleased(); 
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            FlagEvents.mouseClicked = true;
            scene->setMouseClickedPos(sf::Mouse::getPosition(window)); 
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            FlagEvents.mouseClicked = false;
        }
        scene->handleInput();
    }
}
