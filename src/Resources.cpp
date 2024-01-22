#include "Resources.h"
#include <stdexcept>

//------------------------------------------------------------------------------
const sf::Texture& GetTexture(const std::string& filename) 
{
    static std::unordered_map<std::string, sf::Texture> textureStore;
    auto it = textureStore.find(filename);
    if (it != textureStore.end()) 
    {
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(std::string(RESOURCES_PATH) + filename)) 
    {
        throw std::runtime_error("Failed to load texture: " + filename);
    }

    auto inserted = textureStore.emplace(filename, std::move(texture));
    return inserted.first->second;
}

//------------------------------------------------------------------------------
const sf::Font& GetFont(const std::string& filename) 
{
    static std::unordered_map<std::string, sf::Font> fontStore;
    auto it = fontStore.find(filename);
    if (it != fontStore.end()) 
    {
        return it->second;
    }

    sf::Font font;
    if (!font.loadFromFile(std::string(RESOURCES_PATH) + filename)) 
    {
        throw std::runtime_error("Failed to load font: " + filename);
    }

    auto inserted = fontStore.emplace(filename, std::move(font));
    return inserted.first->second;
}

//------------------------------------------------------------------------------
const sf::SoundBuffer& GetSoundBuffer(const std::string& filename)
{
    static std::unordered_map<std::string, sf::SoundBuffer> soundBufferStore;
    auto it = soundBufferStore.find(filename);
    if (it != soundBufferStore.end())
    {
        return it->second;
    }

    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile(std::string(RESOURCES_PATH) + filename))
    {
        throw std::runtime_error("Failed to load font: " + filename);
    }

    auto inserted = soundBufferStore.emplace(filename, std::move(soundBuffer));
    return inserted.first->second;
}

//------------------------------------------------------------------------------
sf::Music& GetMusic(const std::string& filename)
{
    static std::unordered_map<std::string, std::unique_ptr<sf::Music>> musicStore;

    auto it = musicStore.find(filename);
    if (it != musicStore.end())
    {
        return *(it->second);
    }

    std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
    if (!music->openFromFile(std::string(RESOURCES_PATH) + filename))
    {
        throw std::runtime_error("Failed to load music: " + filename);
    }

    auto& storedMusic = *music;
    musicStore[filename] = std::move(music);
    
    return storedMusic;
}