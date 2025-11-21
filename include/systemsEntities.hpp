#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H


#include "entity.hpp"
#include "mapArea.hpp"

void continuousAction(sf::Event& event, Direction& direction);

void movePlayer(Entity& mainCharacter, MapArea& mapArea);


#endif
