#include "gameStates.hpp"
#include "game.hpp"

MenuState::MenuState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture();
}
PlayState::PlayState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture();
    // TODO: Entity player = entities.createEntity();
    // TODO: entities.addComponent<Position>(player, {100.f, 200.f});
    // TODO: if( !tilemap.load(...) );
}
PausedState::PausedState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture();
}


void GameState::handleInput(sf::Event& event)  {
    if (event.type == sf::Event::Closed) {
        game.window.close();
        exit(EXIT_SUCCESS);
    }
}

void MenuState::handleInput(sf::Event& event) {
    GameState::handleInput(event);
}

void PlayState::handleInput(sf::Event& event) {
    GameState::handleInput(event);

    // ACTION WITH INTERVALS (shoot)
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            //make_unique is available on c++17 forward
            game.changeGameState(std::unique_ptr<MenuState>(new MenuState(game)));
    }

    // ACTION WITHOUT INTERVALS (walk)
    inputSystem.contiunuousAction(event);
}

void PausedState::handleInput(sf::Event& event) {
    GameState::handleInput(event);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        game.changeGameState(std::unique_ptr<PlayState>(new PlayState(game)));
}


void MenuState::update(float dt) {}
void PlayState::update(float dt) {
    // TODO: Change game states (PausedState should have a intermediary unique_ptr to store paused PlayState)
    inputSystem.updateUserPosition(entities);
    // TODO: if (...) changeBackground(..., resourceManager)
}
void PausedState::update(float dt) {}


void MenuState::render(sf::RenderWindow& window) {}
void PlayState::render(sf::RenderWindow& window) {
    window.draw(*this->background);
}
void PausedState::render(sf::RenderWindow& window) {}


void PlayState::changeBackground(std::unique_ptr<TileMap> newBackground) {
    this->background = std::move(newBackground);
}
