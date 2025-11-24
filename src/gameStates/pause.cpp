#include "gameStates.hpp"
#include "game.hpp"


PausedState::PausedState(Game &game) : GameState(game) {
    resources.loadTexture("paused");
    background.setTexture(resources.getTexture("paused"));
}

void PausedState::handleInput(sf::Event& event) {
    GameState::handleInput(event);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        game.actions.emplace_back(
                    PendingActionType::Pop,
                    std::move(nullptr)
                );
    }
}

void PausedState::render(sf::RenderWindow& window) {
    window.draw(background);
}
