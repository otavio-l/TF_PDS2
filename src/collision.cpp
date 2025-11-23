#include "collision.hpp"
#include <fstream>
#include "game.hpp"


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

Direction collisionReaction(LiveEntity& mainCharacter, MapArea& mapArea, Game& game, float vel) {
    // TODO: Trigger entities still are treated as blocking
    Direction collisions {false, false, false, false};

    for (auto &e : mapArea.mapEntities) {
        // some areas of the map have the background entity, which has no collision or trigger
        if (!e.hasCollision && !e.hasTrigger) continue;
        bool currentCollision {false};

        if (mainCharacter.direction.up) {
            if (checkCollision(mainCharacter, e, 0, -vel)) {
                collisions.up = true;
                currentCollision = true;
            }
        }
        if (mainCharacter.direction.right) {
            if (checkCollision(mainCharacter, e, vel, 0)) {
                collisions.right = true;
                currentCollision = true;
            }
        }
        if (mainCharacter.direction.down) {
            if (checkCollision(mainCharacter, e, 0, vel)) {
                collisions.down = true;
                currentCollision = true;
            }
            
        }
        if (mainCharacter.direction.left) {
            if (checkCollision(mainCharacter, e, -vel, 0)) {
                collisions.left = true;
                currentCollision = true;
            }
        }

        if (currentCollision && e.hasTrigger) {
            triggerDispatcher(e, mapArea, game, mainCharacter);
        }
    }

    return collisions;
}

void updateSave(MapArea& mapArea) {
    std::ofstream out("checkpoint.txt", std::ios::trunc);
    out << mapArea.checkpoint;
}

void triggerDispatcher(MapEntity& e, MapArea& mapArea, Game& game, LiveEntity& mainCharacter) {
    switch (e.trigger.type)
    {
    case TriggerType::NEXT_MAP:
        mapArea.newMap(e.trigger.targetMap, e.trigger.targetSpawn);
        break;

    case TriggerType::CUTSCENE:
        e.hasCollision = false;
        e.hasTrigger = false;
        game.actions.emplace_back(
            PendingActionType::Push,
            std::move(std::unique_ptr<Cutscene>(new Cutscene(game, e.trigger.targetSpawn)))
        );
        mainCharacter.direction.up = false;
        mainCharacter.direction.down = false;
        mainCharacter.direction.left = false;
        mainCharacter.direction.right = false;

        // prevents cutscene from reoccuring
        ++mapArea.checkpoint;
        break;

    case TriggerType::CHECKPOINT:
        e.hasCollision = false;
        e.hasTrigger = false;
        ++mapArea.checkpoint;
        updateSave(mapArea);
        break;

    default:
        break;
    }
}

