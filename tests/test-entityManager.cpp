#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "entityManager.hpp"

TEST_CASE("EntityManager Creation") {
    EntityManager manager;
    CHECK(true); // apenas verifica se constrói sem falhar
}

TEST_CASE("EntityManager::createEntity") {
    EntityManager manager;
    Entity e1 = manager.createEntity();
    Entity e2 = manager.createEntity();

    CHECK(e1 != e2); // IDs diferentes
    CHECK(e1 > 0);
    CHECK(e2 > 0);
}

TEST_CASE("EntityManager::addComponent and withComponent") {
    EntityManager manager;
    Entity e1 = manager.createEntity();
    Entity e2 = manager.createEntity();

    // Adiciona Position
    manager.addComponent(e1, Position{10.f, 20.f});
    manager.addComponent(e2, Position{30.f, 40.f});

    auto posEntities = manager.withComponent<Position>();
    CHECK(posEntities.size() == 2);

    // Adiciona Velocity
    manager.addComponent(e1, Velocity{1.f, 2.f});
    manager.addComponent(e2, Velocity{3.f, 4.f});

    auto velEntities = manager.withComponent<Velocity>();
    CHECK(velEntities.size() == 2);

    // Adiciona Sprite
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    manager.addComponent(e1, Sprite{sprite1});
    manager.addComponent(e2, Sprite{sprite2});

    auto sprEntities = manager.withComponent<Sprite>();
    CHECK(sprEntities.size() == 2);
}

TEST_CASE("EntityManager Components are separate") {
    EntityManager manager;
    Entity e1 = manager.createEntity();
    Entity e2 = manager.createEntity();

    manager.addComponent(e1, Position{1.f, 1.f});
    manager.addComponent(e2, Velocity{2.f, 2.f});

    auto posEntities = manager.withComponent<Position>();
    auto velEntities = manager.withComponent<Velocity>();

    CHECK(posEntities.size() == 1);
    CHECK(velEntities.size() == 1);
    CHECK(posEntities[0] == e1);
    CHECK(velEntities[0] == e2);
}