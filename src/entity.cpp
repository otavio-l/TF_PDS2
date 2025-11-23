#include "entity.hpp"
#include "constants.hpp"


LiveEntity::LiveEntity() {}

LiveEntity::LiveEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, 
    float sizeY) : direction{false, false, false, false}, animateCounter(0), 
    absX(posAbsX), absY(posAbsY) {
    
    drawable.setTexture(spriteSheet);

    float relX = { fmodf(absX, constants::xLogicPixels) };
    float relY = { fmodf(absY, constants::yLogicPixels) };
    hitbox.setPosition(relX, relY);
    drawable.setPosition(relX, relY);

    const sf::Vector2f size(sizeX, sizeY);
    hitbox.setSize(size);
}

void LiveEntity::move() {}

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
    else if (direction.right) {
        if (animateCounter < (constants::fps / 5)) {
            drawable.setTextureRect(sf::IntRect(0, 40, 7, 20));
        }
        else {
            drawable.setTextureRect(sf::IntRect(7, 40, 7, 20));
        }
    }
    else if (direction.left) {
        if (animateCounter < (constants::fps / 5)) {
            drawable.setTextureRect(sf::IntRect(0, 60, 7, 20));
        }
        else {
            drawable.setTextureRect(sf::IntRect(7, 60, 7, 20));
        }
    }
}


PlayerEntity::PlayerEntity() {}

PlayerEntity::PlayerEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, 
    float sizeY) : LiveEntity(spriteSheet, posAbsX, posAbsY, sizeX, sizeY) {}



EnemyEntity::EnemyEntity() {}

EnemyEntity::EnemyEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, 
    float sizeY) : LiveEntity(spriteSheet, posAbsX, posAbsY, sizeX, sizeY), onScreen(false) {}

