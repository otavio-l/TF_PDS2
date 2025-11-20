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


struct Entity {
    sf::Sprite drawable;
    // sf::FloatRect hitbox;
    sf::RectangleShape hitbox;
    bool hasCollision;
    bool hasTrigger;
    bool hasTexture;
    Trigger trigger;
};


#endif
