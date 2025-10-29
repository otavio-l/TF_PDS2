#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tilemaps.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

TEST_CASE("TileMap Creation") {
    TileMap tileMap;
    CHECK(true);  // apenas checamos se constrói sem falhar
}

TEST_CASE("TileMap::load") {
    TileMap tileMap;
    std::vector<int> tiles = {0, 1, 2, 3};

    // Usar sf::Vector2u para largura e altura do tileset
    CHECK_NOTHROW(tileMap.load("tileset.png", sf::Vector2u(2, 2), tiles, 32));
}

TEST_CASE("TileMap::draw") {
    TileMap tileMap;
    sf::RenderWindow window(sf::VideoMode(64, 64), "test-tilemap-render");

    window.clear();
    CHECK_NOTHROW(window.draw(tileMap));
    window.display();
}
