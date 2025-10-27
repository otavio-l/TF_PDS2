#include "entityManager.hpp"

EntityManager::EntityManager() : nextEntity(0) {}

Entity EntityManager::createEntity() { 
    // post ++, evaluates to nextEntity and then increment
    return nextEntity++;
}

template <typename T>
void EntityManager::addComponent(Entity e, const T& comp) {
    
}

// Edge case: where the previous template logic doesn't work
template <>
void EntityManager::addComponent<Position>(Entity e, const Position& p) {
    positions[e] = p;
}

std::vector<Entity> EntityManager::viewWithSprite() {
    std::vector<Entity> result;
    for (auto& [id, sprite] : sprites) result.push_back(id);
    return result;
}