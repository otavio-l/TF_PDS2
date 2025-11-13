#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H

#include "parser.hpp"

struct Direction {
    bool up;
    bool down;
    bool right;
    bool left;
};

class InputSystem {
    Direction direction;
    MapArea &mapArea;
    Entity& mainCharacter;
public:
    InputSystem(MapArea &mapArea, Entity& mainCharacter);

    void contiunuousAction(sf::Event& event);

    bool checkCollision(Entity& e, float dx, float dy);

    void moveEntity(float dx, float dy);

    // To update main character position it has to see the direction flags
    void updateUserPosition(std::vector<Entity>& mapEntities);
};

#endif
