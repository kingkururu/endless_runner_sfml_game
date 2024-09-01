//
//  constants.cpp
//  sfmlgame3
//
//  Created by Sunmyoung Yun on 2024/08
//

#include "constants.hpp"

namespace Constants {
// background components (static)
    const sf::Vector2f BACKGROUND_POSITION = {0.0f, 0.0f};
    const sf::Vector2f BACKGROUND_SCALE = {0.5f, 0.5f};
    std::shared_ptr<sf::Texture> BACKGROUND_TEXTURE = std::make_shared<sf::Texture>();
    
    // player components (non-static) / animated 
    const sf::Vector2f PLAYER_POSITION = {0.0f, SCREEN_HEIGHT - 120};
    const sf::Vector2f PLAYER_SCALE = {3.0f, 3.0f};
    std::vector<sf::IntRect> PLAYERSPRITE_RECTS;
    const sf::Color PLAYER_DEAD_COLOR = sf::Color(200, 0, 0);
    std::shared_ptr<sf::Texture> PLAYER_TEXTURE = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Uint8[]> PLAYER_BITMASK;

    // bullet components (non-static) / non-animated
    const sf::Vector2f BULLET_POSITION = PLAYER_POSITION;
    const sf::Vector2f BULLET_SCALE = {2.5f, 2.5f};
    std::vector<sf::IntRect> BULLETSPRITES_RECTS;
    std::shared_ptr<sf::Texture> BULLET_TEXTURE = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Uint8[]> BULLET_BITMASK;
    const sf::Vector2f BULLET_POS_OFFSET = { 60.0f, 60.0f};  

    // slime components (non-static) / animated   
    const sf::Vector2f SLIME_SCALE = {0.35f, 0.35f};
    std::vector<sf::IntRect> SLIMESPRITE_RECTS;
    std::shared_ptr<sf::Texture> SLIME_TEXTURE = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Uint8[]> SLIME_BITMASK;

    // bush components (non-static) / non-animated
    const sf::Vector2f BUSH_POSITION = {SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 130.0f};
    const sf::Vector2f BUSH_SCALE = {3.0f, 3.0f};
    std::vector<sf::IntRect> BUSHSPRITES_RECTS;
    std::shared_ptr<sf::Texture> BUSH_TEXTURE = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Uint8[]> BUSH_BITMASK;

    // text components
    const sf::Vector2f TEXT_POSITION = {0.0f, 0.0f};
    const sf::Color TEXT_COLOR = sf::Color::White;
    std::shared_ptr<sf::Font> TEXT_FONT = std::make_shared<sf::Font>(); 

    // music components 
    std::unique_ptr<sf::Music> BACKGROUNDMUSIC_MUSIC = std::make_unique<sf::Music>(); 

    // sound components
    std::shared_ptr<sf::SoundBuffer> PLAYERDEAD_SOUNDBUFF = std::make_shared<sf::SoundBuffer>(); 

    std::shared_ptr<sf::SoundBuffer> PLAYERJUMP_SOUNDBUFF = std::make_shared<sf::SoundBuffer>(); 

    std::shared_ptr<sf::SoundBuffer> BULLET_SOUNDBUFF = std::make_shared<sf::SoundBuffer>(); 

    std::shared_ptr<sf::SoundBuffer> OBSTHIT_SOUNDBUFF = std::make_shared<sf::SoundBuffer>(); 

    //set slime position (random from upper right corner)
    sf::Vector2f makeSlimePosition(){
        float xPos = static_cast<float>(SCREEN_WIDTH - std::rand() % static_cast<int>(SCREEN_WIDTH / 2));
        float yPos = 0.0f;
        return sf::Vector2f{ xPos, yPos }; 
    }

    //initialize bitmask 
    std::shared_ptr<sf::Uint8[]> createBitmask(const std::shared_ptr<sf::Texture>& texture) {
        if (!texture) {
            return nullptr;
        }

        sf::Image image = texture->copyToImage();
        unsigned int width = image.getSize().x;
        unsigned int height = image.getSize().y;

        unsigned int bitmaskSize = (width * height) / 8 + ((width * height) % 8 != 0); // rounding up
        std::shared_ptr<sf::Uint8[]> bitmask(new sf::Uint8[bitmaskSize](), std::default_delete<sf::Uint8[]>());

        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                sf::Color pixelColor = image.getPixel(x, y);
                unsigned int bitIndex = y * width + x;
                unsigned int byteIndex = bitIndex / 8;
                unsigned int bitPosition = bitIndex % 8;

                if (pixelColor.a > 128) {
                    bitmask[byteIndex] |= (1 << bitPosition);
                }
            }
        }

        return bitmask; 
    }

    //initializer function
    void initialize() {
        //load sprite texture
        if (!BACKGROUND_TEXTURE->loadFromFile(BACKGROUNDSPRITE_PATH)) {
            std::cerr << "Failed to load background texture from file: " << BACKGROUNDSPRITE_PATH << std::endl;
        }
        if (!PLAYER_TEXTURE->loadFromFile(PLAYERSPRITE_PATH)) {
            std::cerr << "Failed to load player texture from file: " << PLAYERSPRITE_PATH << std::endl;
        }
        if (!BULLET_TEXTURE->loadFromFile(BULLETSPRITE_PATH)) {
            std::cerr << "Failed to load bullet texture from file: " << BULLETSPRITE_PATH << std::endl;
        }
        if (!SLIME_TEXTURE->loadFromFile(SLIMESPRITE_PATH)) {
            std::cerr << "Failed to load slime texture from file: " << SLIMESPRITE_PATH << std::endl;
        }
        if (!BUSH_TEXTURE->loadFromFile(BUSHSPRITE_PATH)) {
            std::cerr << "Failed to load bush texture from file: " << BUSHSPRITE_PATH << std::endl;
        }

        //load font
        if (!TEXT_FONT->loadFromFile(TEXT_PATH)){
            std::cerr << "Failed to load font from file: " << TEXT_PATH << std::endl; 
        }

        //load music
        if (!BACKGROUNDMUSIC_MUSIC->openFromFile(BACKGROUNDMUSIC_PATH)) {
            std::cerr << "Failed to load background music from file: " << BACKGROUNDMUSIC_PATH << std::endl;
        }
        
        //load sound
        if (!PLAYERDEAD_SOUNDBUFF->loadFromFile(PLAYERDEADSOUND_PATH)) {
            std::cerr << "Failed to load playerdead sound from file: " << PLAYERDEADSOUND_PATH << std::endl;
        }
        if (!PLAYERJUMP_SOUNDBUFF->loadFromFile(PLAYERJUMPSOUND_PATH)) {
            std::cerr << "Failed to load bush texture from file: " << PLAYERJUMPSOUND_PATH << std::endl;
        }
        if (!BULLET_SOUNDBUFF->loadFromFile(BULLETSOUND_PATH)) {
            std::cerr << "Failed to load playerdead sound from file: " << BULLETSOUND_PATH << std::endl;
        }
        if (!OBSTHIT_SOUNDBUFF->loadFromFile(OBSTHITSOUND_PATH)) {
            std::cerr << "Failed to load bush texture from file: " << OBSTHITSOUND_PATH << std::endl;
        }

        //make rects for animations     //at this current moment player is only player_run.png
        for(int i = 0; i < 5; ++i ){
            PLAYERSPRITE_RECTS.push_back(sf::IntRect{ 32 * i, 0, 32, 32}); 
        }
        for(int i = 0; i < 5; ++i ){
            SLIMESPRITE_RECTS.push_back(sf::IntRect{ 490 * i, 0, 490, 242}); 
        }

        // make bitmasks
        PLAYER_BITMASK = createBitmask(PLAYER_TEXTURE);
        BULLET_BITMASK = createBitmask(BULLET_TEXTURE); 
        SLIME_BITMASK = createBitmask(SLIME_TEXTURE);
        BUSH_BITMASK = createBitmask(BUSH_TEXTURE);
    }
}


