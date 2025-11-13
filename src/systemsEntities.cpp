#include "systemsEntities.hpp"
#include "constants.hpp"


InputSystem::InputSystem(MapArea &mapArea, Entity& mainCharacter) : mapArea(mapArea), 
mainCharacter(mainCharacter) {
    direction.down = false;
    direction.left = false;
    direction.right = false;
    direction.down = false;
}


void InputSystem::contiunuousAction(sf::Event& event) {    
    // Main character movement
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) direction.up = true;
        if (event.key.code == sf::Keyboard::A) direction.left = true;
        if (event.key.code == sf::Keyboard::S) direction.down = true;
        if (event.key.code == sf::Keyboard::D) direction.right = true;
    }
    else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W) direction.up = false;
        if (event.key.code == sf::Keyboard::A) direction.left = false;
        if (event.key.code == sf::Keyboard::S) direction.down = false;
        if (event.key.code == sf::Keyboard::D) direction.right = false;
    }
}

void InputSystem::updateUserPosition(EntityManager& entities) {
    // TODO:
    // Entity entity = entities.withComponent<PlayerTag>
    // Velocity vel = entity.get(Velocity);
    // Position& pos = entity.get(Position)
    // if (direction.up) pos.y -= vel;
    // if (direction.down) pos.y += vel;
    // if (direction.right) pos.x += vel;
    // if (direction.left) pos.x -= vel;
}
