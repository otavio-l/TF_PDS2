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

struct MapEntity: public Entity {
    bool hasCollision;
    bool hasTrigger;
    bool hasTexture;
    Trigger trigger;
};

struct LiveEntity: public Entity {
    Direction direction;
    int animateCounter;
    float absX;
    float absY;
    virtual void move();
    void animate();

    LiveEntity();
    LiveEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, float sizeY);
    virtual ~LiveEntity() = default;
};

struct PlayerEntity: public LiveEntity {
    PlayerEntity();
    PlayerEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, float sizeY);
};

struct EnemyEntity: public LiveEntity {
    EnemyEntity();
    EnemyEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, float sizeY);
};

#endif
