#include "doctest.h"

#include "collision.hpp"
#include "entity.hpp"

TEST_CASE("checkCollision() base cases") {
    Entity entityA;
    entityA.hitbox.setPosition(0.0f, 0.0f);
    entityA.hitbox.setSize(sf::Vector2f(10.0f, 10.0f));

    Entity entityB;
    entityB.hitbox.setPosition(5.0f, 5.0f);
    entityB.hitbox.setSize(sf::Vector2f(10.0f, 10.0f));

    Entity entityC;
    entityC.hitbox.setPosition(20.0f, 20.0f);
    entityC.hitbox.setSize(sf::Vector2f(5.0f, 5.0f));

    CHECK(checkCollision(entityA, entityB, 0.0f, 0.0f) == true);
    CHECK(checkCollision(entityA, entityC, 0.0f, 0.0f) == false);
}

TEST_CASE("checkCollision() with movement") {
    Entity entityA;
    entityA.hitbox.setPosition(0.0f, 0.0f);
    entityA.hitbox.setSize(sf::Vector2f(10.0f, 10.0f));

    Entity entityB;
    entityB.hitbox.setPosition(15.0f, 0.0f);
    entityB.hitbox.setSize(sf::Vector2f(10.0f, 10.0f));

    CHECK(checkCollision(entityA, entityB, 5.0f, 0.0f) == false);
    CHECK(checkCollision(entityA, entityB, 10.0f, 0.0f) == true);
    CHECK(checkCollision(entityA, entityB, 20.0f, 0.0f) == true);
}

TEST_CASE("checkCollision() edge cases") {
    Entity entityA;
    entityA.hitbox.setPosition(0.0f, 0.0f);
    entityA.hitbox.setSize(sf::Vector2f(10.0f, 10.0f));

    Entity entityB;
    entityB.hitbox.setPosition(10.0f, 0.0f);
    entityB.hitbox.setSize(sf::Vector2f(10.0f, 10.0f));

    CHECK(checkCollision(entityA, entityB, 0.0f, 0.0f) == false);
    CHECK(checkCollision(entityA, entityB, 10.0f, 0.0f) == true);
    CHECK(checkCollision(entityA, entityB, 9.99f, 0.0f) == false);
}
