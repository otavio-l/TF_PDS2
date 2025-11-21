#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H


#include "entity.hpp"
#include "mapArea.hpp"

void continuousAction(sf::Event& event, LiveEntity& mainCharacter);

void movePlayer(LiveEntity& mainCharacter, MapArea& mapArea);


#endif
