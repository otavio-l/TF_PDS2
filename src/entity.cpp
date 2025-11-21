#include "entity.hpp"
#include "constants.hpp"

LiveEntity::LiveEntity() : Entity(), direction{false, false, false, false}, animateCounter(0) {}

LiveEntity::LiveEntity(sf::Texture& spriteSheet) : Entity(), direction{false, false, false, false}, animateCounter(0) {
    drawable.setTexture(spriteSheet);
    hitbox.setPosition(100.0f, 80.0f);
    hitbox.setSize({constants::mainWidth, constants::mainHeight});
}

void LiveEntity::animate() {
    if (direction.up || direction.down || direction.left || direction.right) {
        animateCounter = (animateCounter + 1) % (constants::fps / 2); // troca de frame a cada 0.5s
    }
    else {
        animateCounter = 0;
    }

    if (direction.down) {
        if (animateCounter < (constants::fps / 5)) {
            drawable.setTextureRect(sf::IntRect(0, 0, 7, 20));
        }
        else {
            drawable.setTextureRect(sf::IntRect(7, 0, 7, 20));
        }
    }
    else if (direction.up) {
        if (animateCounter < (constants::fps / 5)) {
            drawable.setTextureRect(sf::IntRect(0, 20, 7, 20));
        }
        else {
            drawable.setTextureRect(sf::IntRect(7, 20, 7, 20));
        }
    }
    else if (direction.left) {
        if (animateCounter < (constants::fps / 5)) {
            drawable.setTextureRect(sf::IntRect(0, 40, 7, 20));
        }
        else {
            drawable.setTextureRect(sf::IntRect(7, 40, 7, 20));
        }
    }
    else if (direction.right) {
        if (animateCounter < (constants::fps / 5)) {
            drawable.setTextureRect(sf::IntRect(0, 60, 7, 20));
        }
        else {
            drawable.setTextureRect(sf::IntRect(7, 60, 7, 20));
        }
    }
}
