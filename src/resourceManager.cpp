#include "resourceManager.hpp"

void ResourceManager::loadTexture(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile("assets/" + filename + ".png"))
        throw std::runtime_error("Failed to load texture: " + filename);

    textures[filename] = std::move(texture);
}

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    if (textures.find(filename) == textures.end()) {
        throw std::runtime_error("Texture wasn't loaded previously: " + filename);
    }
    return textures.at(filename);
}