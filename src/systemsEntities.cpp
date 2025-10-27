#include "systemsEntities.hpp"
#include "entityManager.hpp"

void InputSystem::contiunuousAction(sf::Event& event) {
    // while (window.pollEvent(event)) {
    
    // It handles continuous actions first
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) direction.up = true;
    }
    else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W) direction.up = false;
    }
}
