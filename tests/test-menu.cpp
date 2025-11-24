#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "gameStates.hpp"
#include "game.hpp"

TEST_CASE("MenuState default constructor") {
    Game game;
    MenuState menuState(game);
    CHECK(true);
}

TEST_CASE("MenuState handleInput and render methods") {
    Game game;
    MenuState menuState(game);
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Down;

    CHECK_NOTHROW(menuState.handleInput(event));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    CHECK_NOTHROW(menuState.render(window));
}
