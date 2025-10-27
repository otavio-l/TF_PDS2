#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H

#include "entityManager.hpp"

typedef struct Direction {
    bool up;
    bool down;
    bool right;
    bool left;
};

class InputSystem {
    Direction direction;
public:
    void contiunuousAction(sf::Event& event);
    void updateVelocity(EntityManager& entities);
};

#endif
