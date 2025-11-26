#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "game.hpp"
#include <memory>

TEST_CASE("Game class creation") {
    Game* game = new Game();
    CHECK(game != nullptr);
    delete game;
}

TEST_CASE("Game state management") {
    Game game;

    // Push a state
    game.actions.emplace_back(
        PendingActionType::Push,
        std::move(std::unique_ptr<MenuState>(new MenuState(game)))
    );
    CHECK(game.actions.size() == 1);

    // Pop a state
    game.actions.emplace_back(
        PendingActionType::Pop,
        nullptr
    );
    CHECK(game.actions.size() == 2);
}
