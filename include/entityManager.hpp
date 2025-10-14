#include <cstdint>
#include <SFML/Graphics.hpp>
#include <unordered_map>


using Entity = std::uint32_t;

struct Position { float x, y; };
struct Velocity { float vx, vy; };
struct Sprite  { sf::Sprite sprite; };


class EntityManager {
    std::unordered_map<Entity, Position> positions;
    std::unordered_map<Entity, Velocity> velocities;
    std::unordered_map<Entity, Sprite> sprites;
    Entity nextEntity;

public:
    Entity createEntity();

    void addComponent(Entity e);

    std::vector<Entity> viewWithSprite();
};
