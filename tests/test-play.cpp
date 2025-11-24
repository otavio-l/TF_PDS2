#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "gameStates.hpp"
#include "game.hpp"

TEST_CASE("PlayState default constructor") {
    Game game;
    PlayState playState(game);
    CHECK_NOTHROW(playState);
}

TEST_CASE("PlayState handleInput, update and render methods") {
    Game game;
    PlayState playState(game);
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::W;

    CHECK_NOTHROW(playState.handleInput(event));

    CHECK_NOTHROW(playState.update(0.066f));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    CHECK_NOTHROW(playState.render(window));
}
