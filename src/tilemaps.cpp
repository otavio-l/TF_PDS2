#include "tilemaps.hpp"

constexpr int tileSizeBits = 32;

bool TileMap::load(const std::string& tileset, const TileMapCode& tileCodeMatrix) {
    // sf::VertexArray is basically a dynamic flat array of [position and texture]
    if (!this->textureSet.loadFromFile(tileset))
        // TODO: ResourceManager
        return false;

    this->background.setPrimitiveType(sf::Quads);
    this->background.resize(g_xTiles * g_yTiles * 4);

    for (unsigned i = 0; i < g_xTiles; ++i)
        for (unsigned j = 0; j < g_yTiles; ++j) {
            std::uint8_t tileCode = tileCodeMatrix.code[j][i];
            int rowTexture = tileCode % (this->textureSet.getSize().x / tileSizeBits);
            int colTexture = tileCode / (this->textureSet.getSize().x / tileSizeBits);

            sf::Vertex* firstVerticeSquare = &this->background[(i + j * g_xTiles) * 4];
            firstVerticeSquare[0].position = sf::Vector2f(i * tileSizeBits, j * tileSizeBits);
            firstVerticeSquare[1].position = sf::Vector2f((i + 1) * tileSizeBits, j * tileSizeBits);
            firstVerticeSquare[2].position = sf::Vector2f((i + 1) * tileSizeBits, (j + 1) * tileSizeBits);
            firstVerticeSquare[3].position = sf::Vector2f(i * tileSizeBits, (j + 1) * tileSizeBits);

            firstVerticeSquare[0].texCoords = sf::Vector2f(rowTexture * tileSizeBits, colTexture * tileSizeBits);
            firstVerticeSquare[1].texCoords = sf::Vector2f((rowTexture + 1) * tileSizeBits, colTexture * tileSizeBits);
            firstVerticeSquare[2].texCoords = sf::Vector2f((rowTexture + 1) * tileSizeBits, (colTexture + 1) * tileSizeBits);
            firstVerticeSquare[3].texCoords = sf::Vector2f(rowTexture * tileSizeBits, (colTexture + 1) * tileSizeBits);
        }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &this->textureSet;
    target.draw(this->background, states);
}
