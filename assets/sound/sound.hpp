//
//  sound.hpp
//  sfmlgame1
//
//  Created by Sunmyoung Yun on 2024/02/03.
//

#ifndef sound_hpp
#define sound_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <iostream>

class MusicClass{
public:
    MusicClass(const std::string& musicPath);
    sf::Music* const returnMusic() const { return music; }
    ~MusicClass(){ delete music; music = nullptr; }
    
private:
    sf::Music* music;
};

class SoundClass{
public:
    SoundClass(const std::string& musicPath);
    sf::Sound* const returnSound() const { return sound; }
    ~SoundClass(){ delete sound; sound = nullptr; delete soundBuffer; soundBuffer = nullptr; }

private:
    sf::SoundBuffer* soundBuffer;
    sf::Sound* sound;
};

#endif /* sound_hpp */
