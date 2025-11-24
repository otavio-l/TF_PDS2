#include "doctest.h"

#include "gameStates.hpp"
#include "game.hpp"

TEST_CASE("GameState:: default constructor") {
    Game game;
    MenuState gameState(game);
    CHECK(true);
}
