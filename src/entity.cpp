#include "entity.hpp"
#include <cmath>
#include "constants.hpp"
#include "movement.hpp"


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

void PlayerEntity::move(Direction collisions, float velocity) {
    if (this->direction.up && !collisions.up) {
        updatePosition(*this, 0, -velocity);
    }
    if (this->direction.right && !collisions.right) {
        updatePosition(*this, velocity, 0);
    }
    if (this->direction.left && !collisions.left) {
        updatePosition(*this, -velocity, 0);
    }
    if (this->direction.down && !collisions.down) {
        updatePosition(*this, 0, velocity);
    }
}


EnemyEntity::EnemyEntity() {}

EnemyEntity::EnemyEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, 
    float sizeY) : LiveEntity(spriteSheet, posAbsX, posAbsY, sizeX, sizeY), onScreen(false) {}

void EnemyEntity::currentScreen(LiveEntity &mainCharacter) {
    // when the leftmost upmost vertice is not in screen but the enemy is, the enemy needs negative
    // relative coordinates
    int characterScreenX { (int)mainCharacter.absX / constants::xLogicPixels };
    int characterScreenY { (int)mainCharacter.absY / constants::yLogicPixels };

    bool sameColumn {
        ((int)this->absX / constants::xLogicPixels) == characterScreenX
    };
    bool sameLine {
        ((int)this->absY / constants::yLogicPixels) == characterScreenY
    };


    bool upLeftOnScreen { sameColumn && sameLine };

    bool upRightOnScreen {
            ((int)(absX + hitbox.getSize().x) / constants::xLogicPixels) == characterScreenX
        && 
            sameLine
    };

    bool downLeftOnScreen {
            sameColumn
        &&
            ((int)(absY + hitbox.getSize().y) / constants::yLogicPixels) == characterScreenY
    };
    

    onScreen = upLeftOnScreen || downLeftOnScreen || upRightOnScreen;
    float relX { fmodf(absX, constants::xLogicPixels) };
    float relY { fmodf(absY, constants::yLogicPixels) };
    float finalX {relX};
    float finalY {relY};
    
    if (!upLeftOnScreen && downLeftOnScreen) {
        finalY = -constants::yLogicPixels + relY;
    }
    else if (!upLeftOnScreen && upRightOnScreen) {
        finalX = -constants::xLogicPixels + relX;
    }
    hitbox.setPosition(finalX, finalY);
    drawable.setPosition(finalX, finalY);
}

void EnemyEntity::setFollowing(LiveEntity &mainCharacter) {
    if (mainCharacter.absX > absX) {
        direction.right = true;
        direction.left = false;
    }
    else if (fabs(mainCharacter.absX - absX) < constants::enemyVelocity) {
        direction.right = false;
        direction.left = false;
    }
    else {
        direction.right = false;
        direction.left = true;
    }

    if (mainCharacter.absY > absY) {
        direction.down = true;
        direction.up = false;
    }
    else if (fabs(mainCharacter.absY - absY) < constants::enemyVelocity) {
        direction.down = false;
        direction.up = false;
    }
    else {
        direction.down = false;
        direction.up = true;
    }
}

void EnemyEntity::move() {
    float dx {0.0f};
    if (direction.left) {
        dx = -constants::enemyVelocity;
    }
    else if (direction.right) {
        dx = constants::enemyVelocity;
    }
    float dy{0.0f};
    if (direction.up) {
        dy = -constants::enemyVelocity;
    }
    else if (direction.down) {
        dy = constants::enemyVelocity;
    }
    if (onScreen) {
        updatePosition(*this, dx, dy);
    }
    else {
        absX += dx;
        absY += dy;
    }
}
