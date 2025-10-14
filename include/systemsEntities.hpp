#include "entityManager.hpp"

class PhysicsSystem {
public:
    void update(EntityManager& em, float dt);
};

class RenderSystem {
public:
    void draw(EntityManager& em, sf::RenderWindow& window);
};


