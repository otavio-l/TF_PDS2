#include "systemsEntities.hpp"
#include "entityManager.hpp"

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
