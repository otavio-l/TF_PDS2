#include <SFML/Graphics.hpp>


class TileMap : public sf::Drawable, public sf::Transformable {
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::vector<std::vector<int>> m_tiles;

public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, 
              const std::vector<std::vector<int>>& tiles);
};
