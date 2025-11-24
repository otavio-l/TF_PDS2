#include "game.hpp"
#include "constants.hpp"


Game::Game() {
    window.create(sf::VideoMode(constants::xPixels, constants::yPixels), "Game");
    window.setFramerateLimit(constants::fps);
    sf::View view(sf::FloatRect(0, 0, constants::xLogicPixels, constants::yLogicPixels)); 
    window.setView(view);

    //make_unique is available on c++17 forward
    stateStack.push_back(std::unique_ptr<MenuState>(new MenuState(*this)));
}

void Game::maintainStates() {
    while (actions.size()) {

        PendingAction& action = actions.front();
        switch (action.type)
        {
        case PendingActionType::Push:
            if (!action.state) {
                throw std::logic_error("New game state is invalid");
            }
            stateStack.push_back(std::move(action.state));
            break;
        case PendingActionType::Pop:
            stateStack.pop_back();
            break;
        case PendingActionType::Change:
            if (!action.state) {
                throw std::logic_error("New game state is invalid");
            }
            stateStack.pop_back();
            stateStack.push_back(std::move(action.state));
            break;
        default:
            throw std::logic_error("Invalid game state change");
        }

        actions.pop_front();
    }
}

void Game::run() {
    sf::Clock clock{};
    sf::Event event{};
    while (window.isOpen()) {
        GameState& currentState = *stateStack.back();

        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event)) {
            currentState.handleInput(event);
        }
        currentState.update(dt);
        window.clear();
        currentState.render(window);
        window.display();
        
        maintainStates();
    }
}
