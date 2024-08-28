//
//  sound.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "sound.hpp"

SoundClass::SoundClass(std::weak_ptr<sf::SoundBuffer> soundBuffer, float volume) : soundBuffer(soundBuffer), sound(std::make_unique<sf::Sound>()), volume(volume){
    try{
        auto soundBuff = soundBuffer.lock();
        if(!soundBuff){
            throw std::runtime_error("failed loading sound buffer");
        }
        sound->setBuffer(*soundBuff);
        sound->setVolume(volume); 
    }

    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        soundBuffer.reset();
        sound.reset(); 
    }
}

MusicClass::MusicClass(std::weak_ptr<sf::Music> musicLoad, float volume)
    : SoundClass(std::weak_ptr<sf::SoundBuffer>(), volume), weakMusicPtr(musicLoad) {
    try {
        auto musicptr = weakMusicPtr.lock();
        if (!musicptr) {
            throw std::runtime_error("Error loading music");
        }
        music = std::make_unique<sf::Music>();
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

