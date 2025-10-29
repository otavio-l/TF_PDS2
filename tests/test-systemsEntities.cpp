#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "systemsEntities.hpp"
#include "entityManager.hpp"
#include <SFML/Graphics.hpp>

TEST_CASE("InputSystem Creation") {
    InputSystem inputSystem;
    CHECK(true); // apenas verifica se constrói sem falhar
}

TEST_CASE("InputSystem::contiunuousAction KeyPressed") {
    InputSystem inputSystem;
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::W;

    inputSystem.contiunuousAction(event);
    CHECK(true); // apenas garante que não crasha

    event.key.code = sf::Keyboard::S;
    inputSystem.contiunuousAction(event);
    CHECK(true);

    event.key.code = sf::Keyboard::A;
    inputSystem.contiunuousAction(event);
    CHECK(true);

    event.key.code = sf::Keyboard::D;
    inputSystem.contiunuousAction(event);
    CHECK(true);
}

TEST_CASE("InputSystem::contiunuousAction KeyReleased") {
    InputSystem inputSystem;
    sf::Event event;
    event.type = sf::Event::KeyReleased;
    event.key.code = sf::Keyboard::W;

    inputSystem.contiunuousAction(event);
    CHECK(true); // apenas garante que não crasha

    event.key.code = sf::Keyboard::S;
    inputSystem.contiunuousAction(event);
    CHECK(true);

    event.key.code = sf::Keyboard::A;
    inputSystem.contiunuousAction(event);
    CHECK(true);

    event.key.code = sf::Keyboard::D;
    inputSystem.contiunuousAction(event);
    CHECK(true);
}

TEST_CASE("InputSystem::updateVelocity") {
    EntityManager manager;
    InputSystem inputSystem;

    // cria entidades com Velocity
    Entity e1 = manager.createEntity();
    Entity e2 = manager.createEntity();

    manager.addComponent(e1, Velocity{0.f, 0.f});
    manager.addComponent(e2, Velocity{0.f, 0.f});

    // Chama updateVelocity, deve atualizar sem crash
    inputSystem.updateVelocity(manager);
    CHECK(true);

    // Confirma que as entidades ainda existem
    auto entities = manager.withComponent<Velocity>();
    CHECK(entities.size() == 2);
}