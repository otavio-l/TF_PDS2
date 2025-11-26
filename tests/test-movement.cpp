#include "doctest.h"

#include "movement.hpp"
#include "constants.hpp"

TEST_CASE("InputSystem::contiunuousAction() KeyPressed & KeyReleased") {
    PlayerEntity mainCharacter;
    
    sf::Event event_pressed;
    event_pressed.type = sf::Event::KeyPressed;
    sf::Event event_released;
    event_released.type = sf::Event::KeyReleased;

    // press and release W key
    event_pressed.key.code = sf::Keyboard::W;
    continuousAction(event_pressed, mainCharacter);
    CHECK(mainCharacter.direction.up);
    event_released.key.code = sf::Keyboard::W;
    continuousAction(event_released, mainCharacter);
    CHECK(!mainCharacter.direction.up);

    // press and release S key
    event_pressed.key.code = sf::Keyboard::S;
    continuousAction(event_pressed, mainCharacter);
    CHECK(mainCharacter.direction.down);
    event_released.key.code = sf::Keyboard::S;
    continuousAction(event_released, mainCharacter);
    CHECK(!mainCharacter.direction.down);

    // press and release A key
    event_pressed.key.code = sf::Keyboard::A;
    continuousAction(event_pressed, mainCharacter);
    CHECK(mainCharacter.direction.left);
    event_released.key.code = sf::Keyboard::A;
    continuousAction(event_released, mainCharacter);
    CHECK(!mainCharacter.direction.left);

    // press and release D key
    event_pressed.key.code = sf::Keyboard::D;
    continuousAction(event_pressed, mainCharacter);
    CHECK(mainCharacter.direction.right);
    event_released.key.code = sf::Keyboard::D;
    continuousAction(event_released, mainCharacter);
    CHECK(!mainCharacter.direction.right);
}

TEST_CASE("InputSystem::contiunuousAction() Invalid Key") {
    PlayerEntity mainCharacter;
    
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::F1; // invalid key for movement

    continuousAction(event, mainCharacter);
    CHECK(!mainCharacter.direction.up);
    CHECK(!mainCharacter.direction.down);
    CHECK(!mainCharacter.direction.left);
    CHECK(!mainCharacter.direction.right);
}

TEST_CASE("updatePosition() movement") {
    PlayerEntity mainCharacter;
    mainCharacter.hitbox.setPosition(100.0f, 100.0f);
    mainCharacter.direction = { true, false, false, false }; // moving up
    float velocity = static_cast<float>(constants::mainCharacterVelocity);

    mainCharacter.move({ false, false, false, false }, velocity);
    CHECK(mainCharacter.hitbox.getPosition().y == 100.0f - velocity);

    mainCharacter.direction = { false, true, false, false }; // moving down
    mainCharacter.move({ false, false, false, false }, velocity);
    CHECK(mainCharacter.hitbox.getPosition().y == 100.0f);

    mainCharacter.direction = { false, false, true, false }; // moving left
    mainCharacter.move({ false, false, false, false }, velocity);
    CHECK(mainCharacter.hitbox.getPosition().x == 100.0f + velocity);

    mainCharacter.direction = { false, false, false, true }; // moving right
    mainCharacter.move({ false, false, false, false }, velocity);
    CHECK(mainCharacter.hitbox.getPosition().x == 100.0f);
}
