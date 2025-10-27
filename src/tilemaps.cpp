#include "tilemaps.hpp"

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, 
                   const std::vector<std::vector<int>>& matrixTiles) {
    // sf::VertexArray is basically a dynamic flat array of [position and texture]
    // m_tileset is a matrix of blocks of texture
    if (!m_tileset.loadFromFile(tileset))
        // TODO: ResourceManager
        return false;

    unsigned widthInSquares = matrixTiles[0].size();
    unsigned heightInSquares = matrixTiles.size();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(widthInSquares * heightInSquares * 4);
    m_matrixTiles = matrixTiles;

    for (unsigned i = 0; i < widthInSquares; ++i)
        for (unsigned j = 0; j < heightInSquares; ++j) {
            int tileNumber = matrixTiles[j][i];
            int rowTexture = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int colTexture = tileNumber / (m_tileset.getSize().x / tileSize.x);

            sf::Vertex* firstVerticeSquare = &m_vertices[(i + j * widthInSquares) * 4];
            firstVerticeSquare[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            firstVerticeSquare[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            firstVerticeSquare[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            firstVerticeSquare[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            firstVerticeSquare[0].texCoords = sf::Vector2f(rowTexture * tileSize.x, colTexture * tileSize.y);
            firstVerticeSquare[1].texCoords = sf::Vector2f((rowTexture + 1) * tileSize.x, colTexture * tileSize.y);
            firstVerticeSquare[2].texCoords = sf::Vector2f((rowTexture + 1) * tileSize.x, (colTexture + 1) * tileSize.y);
            firstVerticeSquare[3].texCoords = sf::Vector2f(rowTexture * tileSize.x, (colTexture + 1) * tileSize.y);
        }

    return true;
}