#include "game.hpp"


Game::Game() {
    //make_unique is available on c++17 forward
    this->currentState = std::unique_ptr<MenuState>(new MenuState(*this));
}

void Game::run() {
    sf::Clock clock{};
    sf::Event event{};
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event))
            currentState->handleInput(event);
        currentState->update(dt);
        window.clear();
        currentState->render(window);
        window.display();
    }
}

void Game::changeGameState(std::unique_ptr<GameState> newState) {
    // deletes currentState and change the owner of newState
    this->currentState = std::move(newState);
}