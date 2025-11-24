#include <string>
#include <chrono>
#include <thread>
#include <nlohmann/json.hpp>
#include <fstream>
#include "gameStates.hpp"
#include "constants.hpp"
#include "game.hpp"


void Cutscene::loadJson(std::string jsonFile) {
    nlohmann::json cutscene;

    std::ifstream file(jsonFile);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open cutscene file: " + jsonFile);
    }
    file >> cutscene;
    file.close();

    this->spriteFile = cutscene.value("file", "");
    if (this->spriteFile.empty()) {
        throw std::runtime_error("Config file for cutscene doesn't have the image path");
    }
    this->intervalSec = cutscene.value("intervalSec", 0.5f);
    this->repetitions = cutscene.value("repetitions", 1);
    this->next = cutscene.value("next", "");
}

Cutscene::Cutscene(Game &game, std::string jsonFile) 
: GameState(game), currentFrame(0), dtTotal(0.0f), currentRepetition(1) {
    loadJson(jsonFile);

    resources.loadTexture(spriteFile);
    sf::Texture& texture {resources.getTexture(spriteFile)};
    int width { static_cast<int>( texture.getSize().x ) };
    if ((width % constants::xLogicPixels) != 0) {
        throw std::runtime_error("Cutscene image isn't divisible by " 
            + std::to_string(constants::xLogicPixels));
    }

    quantFrame = width / constants::xLogicPixels;
}

void Cutscene::handleInput(sf::Event& event) {
    GameState::handleInput(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            game.actions.emplace_back(
                PendingActionType::Push,
                std::move(std::unique_ptr<PausedState>(new PausedState(game)))
            );
        }
    }
}

void Cutscene::update(float dt) {
    if (dtTotal < intervalSec) {
        dtTotal += dt;
        return;
    }
    dtTotal = 0.0f;
    if ((currentFrame+1) >= quantFrame) {
        ++currentRepetition;
        currentFrame = 0;

        if (currentRepetition > repetitions) {
            if (next.empty()) {
                game.actions.emplace_back(
                    PendingActionType::Pop,
                    std::move(nullptr)
                );
            }
            else {
                game.actions.emplace_back(
                    PendingActionType::Change,
                    std::move(std::unique_ptr<Cutscene>(new Cutscene(game, next)))
                );
            }
        }
    }
    else {
        ++currentFrame;
    }
}

void Cutscene::render(sf::RenderWindow& window) {
    if (currentRepetition > repetitions) return;
    
    int x {currentFrame * constants::xLogicPixels};
    sf::IntRect currentSprite({ x, 0 }, { constants::xLogicPixels, constants::yLogicPixels });
    sf::Texture& texture {resources.getTexture(spriteFile)};
    sf::Sprite frame(texture, currentSprite);
    window.draw(frame);
}
