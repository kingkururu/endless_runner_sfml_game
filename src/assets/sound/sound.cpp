//
//  sound.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "sound.hpp"

SoundClass::SoundClass(const std::string& soundPath, float volume) : soundBuffer(std::make_unique<sf::SoundBuffer>()), sound(std::make_unique<sf::Sound>()), volume(volume){
    try{
        if(!soundBuffer->loadFromFile(soundPath)){
            throw std::runtime_error("Error in loading sound from file: " + soundPath);
        }
        sound->setBuffer(*soundBuffer);
        sound->setVolume(volume); 
    }

    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        soundBuffer.reset();
        sound.reset(); 
    }
}

MusicClass::MusicClass(const std::string& musicPath, float volume) : SoundClass(musicPath, volume), music(std::make_unique<sf::Music>()) {
    try {
        if (!music->openFromFile(musicPath)) {
            throw std::runtime_error("Error loading music from file: " + musicPath);
        }
        music->setVolume(volume);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        music.reset();
    }
}

void SoundClass::setVolume(float newVolume){
    volume = newVolume;

    if(sound){
        sound->setVolume(volume); 
    }
}

