#ifndef ENTITY_H
#define ENTITY_H


#include <string>
#include <SFML/Graphics.hpp>


enum class TriggerType {
    NONE,
    NEXT_MAP,
    CUTSCENE,
    CHECKPOINT
};


struct Trigger {
    TriggerType type;
    int targetMap;
    std::string targetSpawn;
};

struct Direction {
    bool up;
    bool down;
    bool right;
    bool left;
};

struct Entity {
    sf::Sprite drawable;
    // sf::FloatRect hitbox;
    sf::RectangleShape hitbox;
};

struct LiveEntity: public Entity {
    Direction direction;
    int animateCounter;
    float absX;
    float absY;

    LiveEntity();
    LiveEntity(sf::Texture& spriteSheet);
    void animate();
};

struct MapEntity: public Entity {
    bool hasCollision;
    bool hasTrigger;
    bool hasTexture;
    Trigger trigger;
};


#endif
