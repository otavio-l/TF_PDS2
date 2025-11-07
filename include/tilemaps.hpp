#ifndef TILEMAPS_H
#define TILEMAPS_H

#include <array>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "resourceManager.hpp"


// 4:3 classic | 20×15 tiles | 640×480 | 32bits
constexpr int g_xTiles = 20;
constexpr int g_yTiles = 15;

using TileMapCode = std::array<std::array<std::uint8_t, g_xTiles>, g_yTiles>;

/**
* @brief Representa um mapa de blocos 2D que pode ser renderizado com eficiência.
*/
class TileMap : public sf::Drawable, public sf::Transformable {
    // sf::VertexArray is basically a dynamic flat array of [position and texture]
    sf::VertexArray background;
    sf::Texture textureSet;

public:
/**
* @brief Carrega um mapa de blocos de um conjunto de blocos e uma matriz de layout 2D.
* @param fileName Caminho para a imagem do conjunto de blocos.
* @param tileSize Tamanho de cada bloco.
* @param matrixTiles Matriz 2D de índices de blocos.
* @return True se o carregamento foi bem-sucedido.
*/
    TileMap(const std::string& fileName, const TileMapCode& tileCodeMatrix, 
        ResourceManager& resourceManager);

private:
    // Override from SFML drawable class
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif