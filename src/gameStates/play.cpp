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
    resources.loadTexture("sprites/Arvore-1");

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
