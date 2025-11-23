// #define DEBUG


#include "gameStates.hpp"
#include <fstream>
#include <vector>
#include <string>
#include "movement.hpp"
#include "collision.hpp"
#include "constants.hpp"
#include "game.hpp"
#include "checkpoint.hpp"


PlayState::PlayState(Game &game) : GameState(game), mapArea(mainCharacter, resources, 
readSave("checkpoint.txt")) {
    resources.loadTexture("sprites/Arvore-1");
    resources.loadTexture("church");
    resources.loadTexture("ext_church");
    resources.loadTexture("deadtree");
    resources.loadTexture("house");
    resources.loadTexture("well");
    resources.loadTexture("sprites/main_character");

    mainCharacter = PlayerEntity(
        resources.getTexture("sprites/main_character"),
        80.0f, 100.0f, 
        constants::mainWidth, constants::mainHeight
    );
    mainCharacter.drawable.setTextureRect(sf::IntRect(0, 0, 7, 20));

    mapArea.newMap(mapLookup[(long unsigned int)mapArea.checkpoint], 
                   spawnLookup[(long unsigned int)mapArea.checkpoint]);

    enemy = EnemyEntity(
        resources.getTexture("sprites/main_character"), 
        constants::enemyPosAbsX, constants::enemyPosAbsY, 
        constants::enemyWidth, constants::enemyHeight
    );
}

void PlayState::handleInput(sf::Event& event) {
    GameState::handleInput(event);

    // ACTION WITH INTERVALS (shoot)
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            game.actions.emplace_back(
                PendingActionType::Push,
                std::move(std::unique_ptr<PausedState>(new PausedState(game)))
            );
        }
    }

    // ACTION WITHOUT INTERVALS (walk)
    continuousAction(event, this->mainCharacter);
}

void PlayState::update(float dt) {
    Direction collisions { 
        collisionReaction(mainCharacter, mapArea, game, constants::mainCharacterVelocity)
    };

    mainCharacter.move(collisions, constants::mainCharacterVelocity);
    mainCharacter.animate();

    if (mapArea.checkpoint != 2) return;

    enemy.setFollowing(mainCharacter);

    enemy.currentScreen(mainCharacter);
    // if (enemy.onScreen) {
        // enemy.animate()
    // }
    enemy.move();

    if (checkCollision(enemy, mainCharacter, 0, 0)) {
        // TODO: GAME OVER
    }
    
}

void PlayState::render(sf::RenderWindow& window) {
    bool drawn {false};
    for (auto& e : mapArea.mapEntities) {
#ifdef DEBUG
        if (e.hasCollision) {
            window.draw(e.hitbox);
        }
#endif
#ifndef DEBUG
        // To make this work the mapEntities must be in ascending order of bottom Y
        if (e.hasTexture) {
            if (!drawn && e.hasCollision) {
                float entityBottom {e.drawable.getPosition().y + e.drawable.getLocalBounds().getSize().y};
                float playerBottom {
                    mainCharacter.drawable.getPosition().y 
                    + mainCharacter.drawable.getLocalBounds().getSize().y
                };
                if (playerBottom < entityBottom) {
                    window.draw(mainCharacter.drawable);
                    drawn = true;
                }
            }
            window.draw(e.drawable);
        }
#endif
    }
    if (!drawn) {
        window.draw(mainCharacter.drawable);
    }
    if (enemy.onScreen) {
        window.draw(enemy.hitbox);
    }
}
