#include "resourceManager.hpp"

void ResourceManager::loadTexture(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile("assets/" + filename + ".png"))
        throw std::runtime_error("Failed to load texture: " + filename);

    this->textures[filename] = std::move(texture);
}

void ResourceManager::loadSound(const std::string& filename) {
    sf::SoundBuffer sound;
    if (!sound.loadFromFile("assets/" + filename + ".png"))
        throw std::runtime_error("Failed to load sound: " + filename);

    this->sounds[filename] = std::move(sound);
}

void ResourceManager::loadFont(const std::string& filename) {
    sf::Font font;
    if (!font.loadFromFile("assets/" + filename + ".png"))
        throw std::runtime_error("Failed to load font: " + filename);

    this->fonts[filename] = std::move(font);
}

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    if (textures.find(filename) == textures.end()) {
        throw std::runtime_error("Texture wasn't loaded previously: " + filename);
    }
    return this->textures.at(filename);
}

sf::SoundBuffer& ResourceManager::getSound(const std::string& filename) {
    if (this->sounds.find(filename) == this->sounds.end()) {
        throw std::runtime_error("Sound wasn't loaded previously: " + filename);
    }
    return this->sounds.at(filename);
}

sf::Font& ResourceManager::getFont(const std::string& filename) {
    if (this->fonts.find(filename) == this->fonts.end()) {
        throw std::runtime_error("Font wasn't loaded previously: " + filename);
    }
    return this->fonts.at(filename);
}