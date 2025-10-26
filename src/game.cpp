#include "game.hpp"


Game::Game() {
    this->currentState = std::unique_ptr<MenuState>(new MenuState(*this));
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        currentState->handleInput();
        currentState->update(dt);
        window.clear();
        currentState->render(window);
        window.display();
    }
}

void Game::changeGameState(std::unique_ptr<GameState> newState) {
    this->currentState = std::move(newState);
}