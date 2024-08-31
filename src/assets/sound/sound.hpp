//
//  sound.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//
#pragma once

#ifndef sound_hpp
#define sound_hpp

#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>

class SoundClass{
public:
    explicit SoundClass(std::weak_ptr<sf::SoundBuffer> soundBuffer, float volume);
    sf::Sound& returnSound() { return *sound; }
    const sf::Sound& returnSound() const { return *sound; }
    ~SoundClass() = default; 
    void setVolume(float volume);
    float const getVolume() { return volume; } 

protected:
    std::weak_ptr<sf::SoundBuffer> soundBuffer;
    std::unique_ptr<sf::Sound> sound;
    float volume = 100.0f; 
};

// class MusicClass : public SoundClass {
// public:
//     explicit MusicClass(std::weak_ptr<sf::Music> musicLoad, float volume);

//     sf::Music& returnMusic() { return *music; } 
//     //const sf::Music& returnMusic() const { return *music; }
//     ~MusicClass() = default; 

// private:
//     std::weak_ptr<sf::Music> weakMusicPtr;
//     std::unique_ptr<sf::Music> music;

// };

class MusicClass {
public:
    // Constructor accepts a unique pointer to sf::Music
    MusicClass(std::unique_ptr<sf::Music> musicLoad, float volume);

    // Method to get the sf::Music object
    sf::Music& returnMusic() { return *music; }

private:
    std::unique_ptr<sf::Music> music;
    float volume{};
};

#endif /* sound_hpp */
