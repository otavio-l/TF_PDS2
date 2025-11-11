#include "resourceManager.hpp"

void ResourceManager::loadTexture(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile("assets/" + filename + ".png"))
        throw std::runtime_error("Failed to load: " + filename);

    textures[filename] = std::move(texture);
}

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    return textures.at(filename);
}