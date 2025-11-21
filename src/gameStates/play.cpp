// #define DEBUG


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
    resources.loadTexture("sprites/Arvore-1");
    resources.loadTexture("church");
    resources.loadTexture("ext_church");
    resources.loadTexture("deadtree");
    resources.loadTexture("house");
    resources.loadTexture("well");
    resources.loadTexture("sprites/main_character");
    
    mainCharacter = LiveEntity(resources.getTexture("sprites/main_character"));
    mainCharacter.drawable.setTextureRect(sf::IntRect(0, 0, 7, 20));

    mapArea.newMap("maps/church.json", "right");
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
    movePlayer(this->mainCharacter, mapArea);
    mainCharacter.animate();
}

void PlayState::render(sf::RenderWindow& window) {
    for (auto& e : mapArea.mapEntities) {
#ifdef DEBUG
        if (e.hasCollision) {
            window.draw(e.hitbox);
        }
#endif
#ifndef DEBUG
        if (e.hasTexture) {
            window.draw(e.drawable);
        }
#endif
    }
    window.draw(mainCharacter.drawable);
}
