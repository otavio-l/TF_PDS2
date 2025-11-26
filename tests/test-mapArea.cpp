#include "doctest.h"

#include "mapArea.hpp"
#include "resourceManager.hpp"
#include "entity.hpp"

TEST_CASE("MapArea default loading") {
    sf::Texture texture;
    LiveEntity mainCharacter(texture, 50.0f, 100.0f, 7.0f, 20.0f);
    ResourceManager rM;
    rM.loadTexture("church");
    MapArea mapArea(mainCharacter, rM, 0);

    CHECK_NOTHROW(mapArea.newMap(9, "right"));
    CHECK(mapArea.mapEntities.size() == 11);
}

TEST_CASE("MapArea loadJson with invalid file") {
    sf::Texture texture;
    LiveEntity mainCharacter(texture, 50.0f, 100.0f, 7.0f, 20.0f);
    ResourceManager rM;
    MapArea mapArea(mainCharacter, rM, 0);

    CHECK_THROWS_AS(mapArea.newMap(10, "right"), std::runtime_error);
}

TEST_CASE("MapArea loadCurrentSpawn with invalid spawn") {
    sf::Texture texture;
    LiveEntity mainCharacter(texture, 50.0f, 100.0f, 7.0f, 20.0f);
    ResourceManager rM;
    rM.loadTexture("church");
    MapArea mapArea(mainCharacter, rM, 0);

    mapArea.newMap(9, "right");

    CHECK_THROWS_AS(mapArea.newMap(9, "invalid_spawn"), std::runtime_error);
}
