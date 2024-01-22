#pragma once

// Third party
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// System
#include <string>
#include <unordered_map>

const sf::Texture& GetTexture(const std::string& filename);
const sf::Font& GetFont(const std::string& filename);
const sf::SoundBuffer& GetSoundBuffer(const std::string& filename);
sf::Music& GetMusic(const std::string& filename);