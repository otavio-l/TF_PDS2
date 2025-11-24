#include "doctest.h"

#include "gameStates.hpp"
#include "game.hpp"

TEST_CASE("PausedState default constructor") {
    Game game;
    PausedState pausedState(game);
    CHECK(true);
}

TEST_CASE("PausedState handleInput and render methods") {
    Game game;
    PausedState pausedState(game);
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Escape;

    CHECK_NOTHROW(pausedState.handleInput(event));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    CHECK_NOTHROW(pausedState.render(window));
}
