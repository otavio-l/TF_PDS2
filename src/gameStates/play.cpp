#define DEBUG


#include "gameStates.hpp"
#include "constants.hpp"
#include "game.hpp"


PlayState::PlayState(Game &game) : GameState(game), mapArea(mainCharacter, resources), 
inputSystem(mainCharacter) {
    // TODO: resources.loadTexture();
    
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
    inputSystem.contiunuousAction(event);
}

void PlayState::update(float dt) {
    // TODO: Change game states (PausedState should have a intermediary unique_ptr to store paused PlayState)
    inputSystem.updateUserPosition(mapArea);
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
