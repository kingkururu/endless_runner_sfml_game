//
//  sound.hpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#ifndef sound_hpp
#define sound_hpp

#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>

class SoundClass{
public:
    explicit SoundClass(const std::string& soundPath, float volume = 100.0f);
    sf::Sound& returnSound() { return *sound; }
    const sf::Sound& returnSound() const { return *sound; }
    ~SoundClass() = default; 
    void setVolume(float volume);
    float const getVolume() { return volume; } 

protected:
    std::unique_ptr<sf::SoundBuffer> soundBuffer;
    std::unique_ptr<sf::Sound> sound;
    float volume {}; 
};

class MusicClass : public SoundClass {
public:
    explicit MusicClass(const std::string& musicPath, float volume = 100.0f);
    
    std::unique_ptr<sf::Music>& returnMusic() { return music; } 
    const std::unique_ptr<sf::Music>& returnMusic() const { return music; }
     ~MusicClass() = default; 

private:
    std::unique_ptr<sf::Music> music;
};

#endif /* sound_hpp */
