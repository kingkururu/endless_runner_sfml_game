//
//  sound.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "sound.hpp"

MusicClass::MusicClass(const std::string& musicPath) : music(new sf::Music){
    try{
        if(!music->openFromFile(musicPath)){
            throw std::runtime_error("Error in loading music from file: " + musicPath);
        }
    }

    catch (const std::exception& e ){
        std::cerr << e.what() << std::endl;
        delete music;
        music = nullptr; 
    }
}

SoundClass::SoundClass(const std::string& soundPath) : soundBuffer(new sf::SoundBuffer), sound(new sf::Sound){
    try{
        if(!soundBuffer->loadFromFile(soundPath)){
            throw std::runtime_error("Error in loading sound from file: " + soundPath);
        }
        sound->setBuffer(*soundBuffer);
    }

    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        delete soundBuffer;
        delete sound;
        soundBuffer = nullptr;
        sound = nullptr; 
    }
}
