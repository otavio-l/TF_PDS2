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


void GameState::handleInput(sf::Event& event)  {
    if (event.type == sf::Event::Closed)
        // TODO: Close
}

void MenuState::handleInput(sf::Event& event) {}

void PlayState::handleInput(sf::Event& event) {
    // ACTION WITH INTERVALS (shoot)
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            //make_unique is available on c++17 forward
            game.changeGameState(std::unique_ptr<MenuState>(new MenuState(game)));
    }

    inputSystem.contiunuousAction(event);
}

void PausedState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        game.changeGameState(std::unique_ptr<PlayState>(new PlayState(game)));
}


void MenuState::update(float dt) {}
void PlayState::update(float dt) {
    inputSystem.updateVelocity(entities);
}
void PausedState::update(float dt) {}


void MenuState::render(sf::RenderWindow& window) {}
void PlayState::render(sf::RenderWindow& window) {}
void PausedState::render(sf::RenderWindow& window) {}
