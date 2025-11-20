#define DEBUG


#include <fstream>
#include "gameStates.hpp"
#include "constants.hpp"
#include "game.hpp"


int readSave() {
    // TODO: exception when file doesn't exist
    std::fstream file("checkpoint.txt", std::ios::in);
    int checkpoint;
    file >> checkpoint;
    file.close();

    return checkpoint;
}


PlayState::PlayState(Game &game) : GameState(game), mapArea(mainCharacter, resources, readSave()) {
    // TODO: resources.loadTexture();
    resources.loadTexture("sprites/Personagem-baixo1");
    resources.loadTexture("sprites/Personagem-baixo2");
    resources.loadTexture("sprites/Personagem-cima1");
    resources.loadTexture("sprites/Personagem-cima2");
    resources.loadTexture("sprites/Personagem-esquerda1");
    resources.loadTexture("sprites/Personagem-esquerda2");
    resources.loadTexture("sprites/Personagem-direita1");
    resources.loadTexture("sprites/Personagem-direita2");

    walkFrameCounter = 0;

    direction.down = false;
    direction.left = false;
    direction.right = false;
    direction.up = false;

    mainCharacter.hasCollision = true;
    mainCharacter.hasTexture = true;
    // TODO: mainCharacter.drawable.
    mainCharacter.hitbox.setPosition(100.0f, 80.0f);
    mainCharacter.hitbox.setSize({constants::mainWidth, constants::mainHeight});

    mapArea.newMap("maps/home.json", "right");
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
    continuousAction(event, direction);
}

void PlayState::update(float dt) {
    movePlayer(mainCharacter, mapArea, direction);

    // Update walk animation
    if (direction.up || direction.down || direction.left || direction.right) {
        walkFrameCounter = (walkFrameCounter + 1) % (constants::fps / 2); // troca de frame a cada 0.5s
    }
    else {
        walkFrameCounter = 0;
    }
    
    if (direction.up) {
        if (walkFrameCounter < (constants::fps / 5)) {
            mainCharacter.drawable.setTexture(resources.getTexture("sprites/Personagem-cima1"));
        }
        else {
            mainCharacter.drawable.setTexture(resources.getTexture("sprites/Personagem-cima2"));
        }
    }
    else if (direction.down) {
        if (walkFrameCounter < (constants::fps / 5)) {
            mainCharacter.drawable.setTexture(resources.getTexture("sprites/Personagem-baixo1"));
        }
        else {
            mainCharacter.drawable.setTexture(resources.getTexture("sprites/Personagem-baixo2"));
        }
    }
    else if (direction.left) {
        if (walkFrameCounter < (constants::fps / 5)) {
            mainCharacter.drawable.setTexture(resources.getTexture("sprites/Personagem-esquerda1"));
        }
        else {
            mainCharacter.drawable.setTexture(resources.getTexture("sprites/Personagem-esquerda2"));
        }
    }
    else if (direction.right) {
        if (walkFrameCounter < (constants::fps / 5)) {
            mainCharacter.drawable.setTexture(resources.getTexture("sprites/Personagem-direita1"));
        }
        else {
            mainCharacter.drawable.setTexture(resources.getTexture("sprites/Personagem-direita2"));
        }
    }
}

void PlayState::render(sf::RenderWindow& window) {
#ifdef DEBUG
    window.draw(mainCharacter.hitbox);
    for (auto& e : mapArea.mapEntities) {
        if (e.hasCollision) {
            window.draw(e.hitbox);
        }
    }
#endif
}
