#include "gameStates.hpp"
#include "game.hpp"


PausedState::PausedState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture();
}

void PausedState::handleInput(sf::Event& event) {
    GameState::handleInput(event);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        game.action.type = PendingActionType::Pop;
}

void PausedState::render(sf::RenderWindow& window) {}
