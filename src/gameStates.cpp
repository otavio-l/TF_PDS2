#include "gameStates.hpp"

MenuState::MenuState(Game &game) : GameState(game) {}
PlayState::PlayState(Game &game) : GameState(game) {}
PausedState::PausedState(Game &game) : GameState(game) {}

void MenuState::handleInput() {}
void PlayState::handleInput() {}
void PausedState::handleInput() {}

void MenuState::update(float dt) {}
void PlayState::update(float dt) {}
void PausedState::update(float dt) {}

void MenuState::render(sf::RenderWindow& window) {}
void PlayState::render(sf::RenderWindow& window) {}
void PausedState::render(sf::RenderWindow& window) {}
