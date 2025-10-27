#include "resourceManager.hpp"

void ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename))
        throw std::runtime_error("Failed to load " + filename);

    textures[name] = std::move(texture);
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}