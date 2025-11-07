#include "tilemaps.hpp"

constexpr int tileSizeBits = 32;

TileMap::TileMap(const std::string& tileset, const TileMapCode& tileCodeMatrix, 
    ResourceManager& resourceManager) {
    this->textureSet = resourceManager.getTexture(tileset);

    this->background.setPrimitiveType(sf::Quads);
    this->background.resize(g_xTiles * g_yTiles * 4);

    for (unsigned i = 0; i < g_xTiles; ++i)
        for (unsigned j = 0; j < g_yTiles; ++j) {
            unsigned int tileCode = tileCodeMatrix[j][i];
            unsigned int rowTexture = tileCode % (this->textureSet.getSize().x / tileSizeBits);
            unsigned int colTexture = tileCode / (this->textureSet.getSize().x / tileSizeBits);

            sf::Vertex* firstVerticeSquare = &this->background[(i + j * g_xTiles) * 4];
            firstVerticeSquare[0].position = sf::Vector2f((float)i * tileSizeBits, (float)j * tileSizeBits);
            firstVerticeSquare[1].position = sf::Vector2f((float)(i + 1) * tileSizeBits, (float)j * tileSizeBits);
            firstVerticeSquare[2].position = sf::Vector2f((float)(i + 1) * tileSizeBits, (float)(j + 1) * tileSizeBits);
            firstVerticeSquare[3].position = sf::Vector2f((float)i * tileSizeBits, (float)(j + 1) * tileSizeBits);

            firstVerticeSquare[0].texCoords = sf::Vector2f((float)rowTexture * tileSizeBits, (float)colTexture * tileSizeBits);
            firstVerticeSquare[1].texCoords = sf::Vector2f((float)(rowTexture + 1) * tileSizeBits, (float)colTexture * tileSizeBits);
            firstVerticeSquare[2].texCoords = sf::Vector2f((float)(rowTexture + 1) * tileSizeBits, (float)(colTexture + 1) * tileSizeBits);
            firstVerticeSquare[3].texCoords = sf::Vector2f((float)rowTexture * tileSizeBits, (float)(colTexture + 1) * tileSizeBits);
        }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &this->textureSet;
    target.draw(this->background, states);
}
