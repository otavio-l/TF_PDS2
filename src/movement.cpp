#include "movement.hpp"
#include "constants.hpp"
#include "collision.hpp"


void continuousAction(sf::Event& event, LiveEntity& mainCharacter) {    
    // Main character movement
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) mainCharacter.direction.up = true;
        if (event.key.code == sf::Keyboard::A) mainCharacter.direction.left = true;
        if (event.key.code == sf::Keyboard::S) mainCharacter.direction.down = true;
        if (event.key.code == sf::Keyboard::D) mainCharacter.direction.right = true;
    }
    else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W) mainCharacter.direction.up = false;
        if (event.key.code == sf::Keyboard::A) mainCharacter.direction.left = false;
        if (event.key.code == sf::Keyboard::S) mainCharacter.direction.down = false;
        if (event.key.code == sf::Keyboard::D) mainCharacter.direction.right = false;
    }
}

void updatePosition(LiveEntity& mainCharacter, float dx, float dy) {
    mainCharacter.absX += dx;
    mainCharacter.absY += dy;

    sf::Vector2f spritePos {
        mainCharacter.drawable.getPosition().x + dx,
        mainCharacter.drawable.getPosition().y + dy
    };

    sf::Vector2f hitboxPos {
        mainCharacter.hitbox.getPosition().x + dx,
        mainCharacter.hitbox.getPosition().y + dy
    };

    mainCharacter.drawable.setPosition(spritePos);
    mainCharacter.hitbox.setPosition(hitboxPos);
}
