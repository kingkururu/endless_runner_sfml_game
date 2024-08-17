//
//  sound.cpp
//  sfmlgame2
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "sound.hpp"

MusicClass::MusicClass(const std::string& musicPath) : music(new sf::Music){
    if(!music->openFromFile(musicPath)){
        std::cerr << "Error loading music from file: " << musicPath << std::endl;
    }
}

SoundClass::SoundClass(const std::string& musicPath) : soundBuffer(new sf::SoundBuffer), sound(new sf::Sound){
    if(!soundBuffer->loadFromFile(musicPath)){
        std::cerr << "Error loading sound from file: " << musicPath << std::endl;
        return;
    }
    sound->setBuffer(*soundBuffer);
}
