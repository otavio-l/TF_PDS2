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

template <>
std::vector<Entity> EntityManager::withComponent<Position>() {
    std::vector<Entity> result;
    for (auto& [id, pos] : this->positions)
        result.push_back(id);
    return result;
}
template <>
std::vector<Entity> EntityManager::withComponent<Velocity>() {
    std::vector<Entity> result;
    for (auto& [id, vel] : this->velocities)
        result.push_back(id);
    return result;
}
template <>
std::vector<Entity> EntityManager::withComponent<Sprite>() {
    std::vector<Entity> result;
    for (auto& [id, spr] : this->sprites)
        result.push_back(id);
    return result;
}
