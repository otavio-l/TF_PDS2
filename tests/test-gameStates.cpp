#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "gameStates.hpp"

TEST_CASE("GameState:: default constructor") {
    Game game;
    GameState gameState(game);
    CHECK_NOTHROW(gameState);
}
