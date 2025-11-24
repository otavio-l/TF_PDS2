#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "gameStates.hpp"
#include "game.hpp"

TEST_CASE("GameState:: default constructor") {
    Game game;
    MenuState gameState(game);
    CHECK(true);
}
