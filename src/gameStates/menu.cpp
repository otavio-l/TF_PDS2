#include "gameStates.hpp"
#include "game.hpp"


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
    resources.loadTexture("menuPlay");
    resources.loadTexture("menuNew");
    resources.loadTexture("menuSettings");

    button.play.setTexture(resources.getTexture("menuPlay"));
    button.newGame.setTexture(resources.getTexture("menuNew"));
    button.settings.setTexture(resources.getTexture("menuSettings"));

    button.selectedButton = PLAY;
}

void MenuState::handleInput(sf::Event& event) {
    GameState::handleInput(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            if (button.getButton() == SelectedMenuButton::PLAY) {
                game.actions.emplace_back(
                    PendingActionType::Change, 
                    std::move(std::unique_ptr<PlayState>(new PlayState(game)))
                );
            }
        }
        else if (event.key.code == sf::Keyboard::Down) button.next();
        else if (event.key.code == sf::Keyboard::Up) button.previous();
    }
}

void MenuState::render(sf::RenderWindow& window) {
    window.draw(this->button.getSprite());
}
