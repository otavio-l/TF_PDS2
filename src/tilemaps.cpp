#include "tilemaps.hpp"
#include "constants.hpp"


TileMap::TileMap(const std::string& tileset, const TileMapCode& tileCodeMatrix, 
    ResourceManager& resourceManager) {
    this->textureSet = resourceManager.getTexture(tileset);

    this->background.setPrimitiveType(sf::Quads);
    this->background.resize(constants::xTiles * constants::yTiles * 4);

    using constants::tileSizePixels;
    for (unsigned i = 0; i < constants::xTiles; ++i)
        for (unsigned j = 0; j < constants::yTiles; ++j) {
            unsigned int tileCode = tileCodeMatrix[j][i];
            unsigned int rowTexture = tileCode % (this->textureSet.getSize().x / tileSizePixels);
            unsigned int colTexture = tileCode / (this->textureSet.getSize().x / tileSizePixels);

            sf::Vertex* firstVerticeSquare = &this->background[(i + j * constants::xTiles) * 4];
            firstVerticeSquare[0].position = sf::Vector2f((float)i * tileSizePixels, (float)j * tileSizePixels);
            firstVerticeSquare[1].position = sf::Vector2f((float)(i + 1) * tileSizePixels, (float)j * tileSizePixels);
            firstVerticeSquare[2].position = sf::Vector2f((float)(i + 1) * tileSizePixels, (float)(j + 1) * tileSizePixels);
            firstVerticeSquare[3].position = sf::Vector2f((float)i * tileSizePixels, (float)(j + 1) * tileSizePixels);

            firstVerticeSquare[0].texCoords = sf::Vector2f((float)rowTexture * tileSizePixels, (float)colTexture * tileSizePixels);
            firstVerticeSquare[1].texCoords = sf::Vector2f((float)(rowTexture + 1) * tileSizePixels, (float)colTexture * tileSizePixels);
            firstVerticeSquare[2].texCoords = sf::Vector2f((float)(rowTexture + 1) * tileSizePixels, (float)(colTexture + 1) * tileSizePixels);
            firstVerticeSquare[3].texCoords = sf::Vector2f((float)rowTexture * tileSizePixels, (float)(colTexture + 1) * tileSizePixels);
        }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &this->textureSet;
    target.draw(this->background, states);
}
