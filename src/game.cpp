#include "game.hpp"
#include <cassert>
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
            assert (action.state);
            stateStack.push_back(std::move(action.state));
            break;
        case PendingActionType::Pop:
            stateStack.pop_back();
            break;
        case PendingActionType::Change:
            assert (action.state);
            stateStack.pop_back();
            stateStack.push_back(std::move(action.state));
            break;
        default:
            break;
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
