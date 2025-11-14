#include "gameStates.hpp"
#include "game.hpp"


GameState::GameState(Game& game) : game(game) {};

void GameState::handleInput(sf::Event& event)  {
    if (event.type == sf::Event::Closed) {
        game.window.close();
        exit(EXIT_SUCCESS);
    }
}

void GameState::update(float dt) {}

void GameState::render(sf::RenderWindow& window) {}
