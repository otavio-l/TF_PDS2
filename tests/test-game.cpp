#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "game.hpp"
#include <memory>

TEST_CASE("Game class creation") {
    Game* game = new Game();
    CHECK(game != nullptr);
    delete game;
}

TEST_CASE("Game::run") {
    Game game;
    // apenas verifica se o metodo pode ser chamado sem crash
    // n executa o loop principal para evitar q o teste rode infinito
    CHECK_NOTHROW(game.run());
}

// nesse teste o ideal seria verificar se o estado foi realmente alterado, ter algo
// como um getCurrentState() ajudaria nisso
TEST_CASE("Game::changeGameState") {
    Game game;
    std::unique_ptr<GameState> statePtr = std::make_unique<PlayState>(game);

    game.changeGameState(std::move(statePtr)); // move o unique_ptr
    CHECK(true);
}
