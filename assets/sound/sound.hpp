//
//  sound.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#ifndef sound_hpp
#define sound_hpp

#include <string>
#include <stdexcept>
#include <SFML/Audio.hpp>
#include <iostream>

class MusicClass{
public:
    explicit MusicClass(const std::string& musicPath);
    sf::Music* const returnMusic() const { return music; }
    ~MusicClass(){ delete music; music = nullptr; }
    
private:
    sf::Music* music;
};

class SoundClass{
public:
    explicit SoundClass(const std::string& soundPath);
    sf::Sound* const returnSound() const { return sound; }
    ~SoundClass(){ delete sound; sound = nullptr; delete soundBuffer; soundBuffer = nullptr; }

private:
    sf::SoundBuffer* soundBuffer;
    sf::Sound* sound;
};

#endif /* sound_hpp */
