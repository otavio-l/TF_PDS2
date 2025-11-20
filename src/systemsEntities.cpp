#include "systemsEntities.hpp"
#include "constants.hpp"


void continuousAction(sf::Event& event, Direction& direction) {    
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

bool checkCollision(Entity& mainCharacter, Entity& e, float dx, float dy) {
    // If the velocity is faster it can pass through 
    sf::FloatRect eHitbox = e.hitbox.getGlobalBounds();
    sf::FloatRect eMain { 
        mainCharacter.hitbox.getPosition().x + dx,
        mainCharacter.hitbox.getPosition().y + dy,
        mainCharacter.hitbox.getSize().x,
        mainCharacter.hitbox.getSize().y
    };

    return eMain.intersects(eHitbox);
}

void updatePosition(Entity& mainCharacter, float dx, float dy) {
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

void triggerDispatcher(Entity& e, MapArea& mapArea) {
    switch (e.trigger.type)
    {
    case TriggerType::NEXT_MAP:
        mapArea.newMap(e.trigger.targetMap, e.trigger.targetSpawn);
        break;
    
    default:
        break;
    }
}

void movePlayer(Entity& mainCharacter, MapArea& mapArea, Direction& direction) {
    // TODO: Trigger entities still are treated as blocking
    bool collisionUp{false};
    bool collisionRight{false};
    bool collisionDown{false};
    bool collisionLeft{false};

    for (auto &e : mapArea.mapEntities) {
        // some areas of the map have the background entity, which has no collision or trigger
        if (!e.hasCollision && !e.hasTrigger) continue;
        bool currentCollision {false};

        if (!collisionUp && direction.up) {
            if (checkCollision(mainCharacter, e, 0, -constants::mainCharacterVelocity)) {
                collisionUp = true;
                currentCollision = true;
            }
        }
        if (!collisionRight && direction.right) {
            if (checkCollision(mainCharacter, e, constants::mainCharacterVelocity, 0)) {
                collisionRight = true;
                currentCollision = true;
            }
        }
        if (!collisionDown && direction.down) {
            if (checkCollision(mainCharacter, e, 0, constants::mainCharacterVelocity)) {
                collisionDown = true;
                currentCollision = true;
            }
            
        }
        if (!collisionLeft && direction.left) {
            if (checkCollision(mainCharacter, e, -constants::mainCharacterVelocity, 0)) {
                collisionLeft = true;
                currentCollision = true;
            }
        }

        if (currentCollision && e.hasTrigger) {
            triggerDispatcher(e, mapArea);
            return;
        }
    }

    if (direction.up && !collisionUp) {
        updatePosition(mainCharacter, 0, -constants::mainCharacterVelocity);
    }
    if (direction.right && !collisionRight) {
        updatePosition(mainCharacter, constants::mainCharacterVelocity, 0);
    }
    if (direction.left && !collisionLeft) {
        updatePosition(mainCharacter, -constants::mainCharacterVelocity, 0);
    }
    if (direction.down && !collisionDown) {
        updatePosition(mainCharacter, 0, constants::mainCharacterVelocity);
    }
}
