#include "gameStates.hpp"
#include "game.hpp"


PausedState::PausedState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture();
}

void PausedState::handleInput(sf::Event& event) {
    GameState::handleInput(event);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        game.changeGameState(std::unique_ptr<PlayState>(new PlayState(game)));
}

void PausedState::render(sf::RenderWindow& window) {}
