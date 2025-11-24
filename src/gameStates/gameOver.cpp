#include "gameStates.hpp"
#include <memory>
#include "game.hpp"


GameOverState::GameOverState(Game &game) : GameState(game) {
    resources.loadTexture("mortis");
    background.setTexture(resources.getTexture("mortis"));
}

void GameOverState::handleInput(sf::Event& event) {
    GameState::handleInput(event);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        game.actions.emplace_back(
            PendingActionType::Change,
            std::move(std::unique_ptr<PlayState>(new PlayState(game)))
        );
    }
}

void GameOverState::render(sf::RenderWindow& window) {
    window.draw(this->background);
}
