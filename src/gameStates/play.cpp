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
    resources.loadTexture("sprites/main_character");
    mainCharacter = LiveEntity(resources.getTexture("sprites/main_character"));  

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
    mainCharacter.animate();
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
