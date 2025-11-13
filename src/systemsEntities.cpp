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

bool InputSystem::checkCollision(Entity& e, float dx, float dy) {
    sf::FloatRect eHitbox = e.hitbox.getGlobalBounds();
    sf::FloatRect eMain { 
        mainCharacter.hitbox.getPosition().x + dx,
        mainCharacter.hitbox.getPosition().y + dy,
        mainCharacter.hitbox.getSize().x,
        mainCharacter.hitbox.getSize().y
    };

    return eMain.intersects(eHitbox);
}

void InputSystem::moveEntity(float dx, float dy) {
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


void InputSystem::updateUserPosition(std::vector<Entity>& mapEntities) {
    bool collisionUp{false};
    bool collisionRight{false};
    bool collisionDown{false};
    bool collisionLeft{false};

    for (std::size_t i = 0; i < mapEntities.size(); ++i) {
        auto& e = mapEntities[i];
        // some areas of the map have the background entity, which has no collision or trigger
        if (!e.hasCollision && !e.hasTrigger) continue;

        if (direction.up) {
            if (checkCollision(e, 0, -constants::mainCharacterVelocity)) { 
                collisionUp = true;               
                if (e.hasTrigger) {
                    // TODO: trigger
                }
            }
            else {
                if (!collisionUp && (i == mapEntities.size() - 1)) {
                    moveEntity(0, -constants::mainCharacterVelocity);
                }
            }
        }
        if (direction.right) {
            if (checkCollision(e, constants::mainCharacterVelocity, 0)) {
                collisionRight = true;
                if (e.hasTrigger) {
                    // TODO: trigger
                }
            }
            else {
                if (!collisionRight && (i == mapEntities.size() - 1)) {
                    moveEntity(constants::mainCharacterVelocity, 0);
                }
            } 
        }
        if (direction.down) {
            if (checkCollision(e, 0, constants::mainCharacterVelocity)) {                
                collisionDown = true;
                if (e.hasTrigger) {
                    // TODO: trigger
                }
            }
            else {
                if (!collisionDown && (i == mapEntities.size() - 1)) {
                    moveEntity(0, constants::mainCharacterVelocity);
                }
            }
        }
        if (direction.left) {
            if (checkCollision(e, -constants::mainCharacterVelocity, 0)) {
                collisionLeft = true;
                if (e.hasTrigger) {
                    // TODO: trigger
                }
            }
            else {
                if (!collisionLeft && (i == mapEntities.size() - 1)) {
                    moveEntity(-constants::mainCharacterVelocity, 0);
                }
            }
        }
    }
}
