#ifndef TILEMAPS_H
#define TILEMAPS_H

#include <SFML/Graphics.hpp>

/**
* @brief Representa um mapa de blocos 2D que pode ser renderizado com eficiência.
*/
class TileMap : public sf::Drawable, public sf::Transformable {
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::vector<std::vector<int>> m_matrixTiles;

public:
/**
* @brief Carrega um mapa de blocos de um conjunto de blocos e uma matriz de layout 2D.
* @param fileName Caminho para a imagem do conjunto de blocos.
* @param tileSize Tamanho de cada bloco.
* @param matrixTiles Matriz 2D de índices de blocos.
* @return True se o carregamento foi bem-sucedido.
*/
    bool load(const std::string& fileName, sf::Vector2u tileSize, 
              const std::vector<std::vector<int>>& matrixTiles);
};

#endif