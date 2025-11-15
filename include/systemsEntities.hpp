#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H

#include "mapArea.hpp"

struct Direction {
    bool up;
    bool down;
    bool right;
    bool left;
};

class InputSystem {
    Direction direction;
    Entity& mainCharacter;
public:
    InputSystem(Entity& mainCharacter);

    void continuousAction(sf::Event& event);

    bool checkCollision(Entity& e, float dx, float dy);

    void moveEntity(float dx, float dy);

    // To update main character position it has to see the direction flags
    void updateUserPosition(MapArea& mapArea);
};

#endif
