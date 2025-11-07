#include "gameStates.hpp"
#include "game.hpp"


Button::Button() {
    this->selectedButton = PLAY;
    // TODO:
    // resources.loadTexture("buttonPlay.jpg");
    // resources.loadTexture("buttonNew.jpg");
    // resources.loadTexture("buttonSettings.jpg");

    // this->play.setTexture("buttonPlay.jpg");
    // this->newGame.setTexture("buttonNew.jpg");
    // this->settings.setTexture("buttonSettings.jpg");

    // this->play.setPosition({1.0f, 2.0f});
    // this->newGame.setPosition({1.0f, 3.0f});
    // this->settings.setPosition({1.0f, 4.0f});

}

sf::Sprite& Button::getSprite() {
    switch (this->selectedButton)
    {
    case NEW_GAME:
        return this->newGame;
    case SETTINGS:
        return this->settings;
    // COUNT will return play sprite too
    default:
        return this->play;
    }
}

void Button::next() {
    int next = (static_cast<int>(selectedButton) + 1) % static_cast<int>(SelectedMenuButton::COUNT);
    selectedButton = static_cast<SelectedMenuButton>(next);
}

void Button::previous() {
    int prev = (static_cast<int>(selectedButton) - 1 + static_cast<int>(SelectedMenuButton::COUNT))
               % static_cast<int>(SelectedMenuButton::COUNT);
    selectedButton = static_cast<SelectedMenuButton>(prev);
}

SelectedMenuButton Button::getButton() {
    return this->selectedButton;
}



MenuState::MenuState(Game &game) : GameState(game) {
    // TODO: resources.loadTexture("menu.jpg");
    // this->background.setTexture("menu.jpg");
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
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            if (button.getButton() == SelectedMenuButton::PLAY) {
                game.changeGameState(std::unique_ptr<PlayState>(new PlayState(game)));
            }
        }
        else if (event.key.code == sf::Keyboard::Down) button.next();
        else if (event.key.code == sf::Keyboard::Up) button.previous();
    }
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


void MenuState::render(sf::RenderWindow& window) {
    window.draw(this->background);
    window.draw(this->button.getSprite());
}
void PlayState::render(sf::RenderWindow& window) {
    window.draw(*this->background);
}
void PausedState::render(sf::RenderWindow& window) {}


void PlayState::changeBackground(std::unique_ptr<TileMap> newBackground) {
    this->background = std::move(newBackground);
}
