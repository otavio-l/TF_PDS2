#include "gameStates.hpp"

MenuState::MenuState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture();
}
PlayState::PlayState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture();
    /*TODO: Entity player = entities.createEntity();
    entities.addComponent<Position>(player, {100.f, 200.f});
    ...*/
}
PausedState::PausedState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture();
}

void MenuState::handleInput() {}
void PlayState::handleInput() {}
void PausedState::handleInput() {}

void MenuState::update(float dt) {}
void PlayState::update(float dt) {}
void PausedState::update(float dt) {}

void MenuState::render(sf::RenderWindow& window) {}
void PlayState::render(sf::RenderWindow& window) {}
void PausedState::render(sf::RenderWindow& window) {}
