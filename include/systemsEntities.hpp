#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H


#include "entity.hpp"
#include "mapArea.hpp"


struct Direction {
    bool up;
    bool down;
    bool right;
    bool left;
};


void continuousAction(sf::Event& event, Direction& direction);

void movePlayer(Entity& mainCharacter, MapArea& mapArea, Direction& direction);


#endif
