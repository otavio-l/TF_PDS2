#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H


#include "entity.hpp"
#include "mapArea.hpp"
// #include "game.hpp"

class Game;

void continuousAction(sf::Event& event, LiveEntity& mainCharacter);

void movePlayer(LiveEntity& mainCharacter, MapArea& mapArea, Game& game);


#endif
