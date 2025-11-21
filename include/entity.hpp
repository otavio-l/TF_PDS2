#ifndef ENTITY_H
#define ENTITY_H


#include <string>
#include <SFML/Graphics.hpp>


enum class TriggerType {
    NONE,
    NEXT_MAP,
    CUTSCENE
};


struct Trigger {
    TriggerType type;
    std::string targetMap;
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

    LiveEntity(sf::Texture& spriteSheet);
    void animate(sf::Texture& spriteSheet);
};

struct MapEntity: public Entity {
    std::string textureFile;
    bool hasCollision;
    bool hasTrigger;
    bool hasTexture;
    Trigger trigger;
};

#endif
