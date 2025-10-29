#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "gameStates.hpp"

// aqui, como sao metodos basicos, apenas verificamos se podem ser chamados sem crash

// instancia MenuState e verifica possivel falha na construcao
TEST_CASE("MenuState Creation") {
    Game game;
    MenuState menuState(game);
    CHECK(true);
}

// testa o handleInput - cria um evento simples e chama o metodo
TEST_CASE("MenuState::handleInput") {
    Game game;
    MenuState menuState(game);
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    menuState.handleInput(event);
    CHECK(true);
}

// chama update com um deltaTime simples
TEST_CASE("MenuState::update") {
    Game game;
    MenuState menuState(game);
    menuState.update(0.1);
    CHECK(true);
}

// chama render com uma janela simples
TEST_CASE("MenuState::render") {
    Game game;
    MenuState menuState(game);
    sf::RenderWindow window(sf::VideoMode(800, 600), "test-menu-render");
    menuState.render(window);
    CHECK(true);
}

// mesmos testes aplicados as outras classes
TEST_CASE("PlayState Creation") {
    Game game;
    PlayState playState(game);
    CHECK(true);
}

TEST_CASE("PlayState::handleInput") {
    Game game;
    PlayState playState(game);
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    playState.handleInput(event);
    CHECK(true);
}

TEST_CASE("PlayState::update") {
    Game game;
    PlayState playState(game);
    playState.update(0.1);
    CHECK(true);
}

TEST_CASE("PlayState::render") {
    Game game;
    PlayState playState(game);
    sf::RenderWindow window(sf::VideoMode(800, 600), "test-play-render");
    playState.render(window);
    CHECK(true);
}

TEST_CASE("PausedState Creation") {
    Game game;
    PausedState pausedState(game);
    CHECK(true);
}

TEST_CASE("PausedState::handleInput") {
    Game game;
    PausedState pausedState(game);
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    pausedState.handleInput(event);
    CHECK(true);
}

TEST_CASE("PausedState::update") {
    Game game;
    PausedState pausedState(game);
    pausedState.update(0.1);
    CHECK(true);
}

TEST_CASE("PausedState::render") {
    Game game;
    PausedState pausedState(game);
    sf::RenderWindow window(sf::VideoMode(800, 600), "test-paused-render");
    pausedState.render(window);
    CHECK(true);
}
