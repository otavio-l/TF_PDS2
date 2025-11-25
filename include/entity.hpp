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

class Entity {
public:
    sf::Sprite drawable;
    sf::RectangleShape hitbox;
};

class MapEntity: public Entity {
public:
    bool hasCollision;
    bool hasTrigger;
    bool hasTexture;
    Trigger trigger;
};

class LiveEntity: public Entity {
private:
    int animateCounter;
public:
    Direction direction;
    float absX;
    float absY;

    /**
     * @brief Atualiza a textura da entidade com a movimentação
     * 
     */
    void animate();

    LiveEntity();
    LiveEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, float sizeY);
    virtual ~LiveEntity() = default;
};

struct PlayerEntity: public LiveEntity {
public:
    /**
     * @brief Move o player se não houver colisões
     * 
     * @param collisions Direções das movimentações proibidas
     * @param velocity velocidade da enridade
     */
    void move(Direction collisions, float velocity);

    PlayerEntity();
    PlayerEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, float sizeY);
};

class EnemyEntity: public LiveEntity {
public:
    bool onScreen;

    /**
     * @brief Calcula se o inimigo está na tela atual e atualiza suas posições relativas
     * 
     * @param mainCharacter Entidade base para tela atual
     */
    void currentScreen(LiveEntity &mainCharacter);
    /**
     * @brief Calcula as próximas direções do inimgo
     * 
     * @param mainCharacter Alvo da direção
     */
    void setFollowing(LiveEntity &mainCharacter);
    /**
     * @brief Move o inimigo estando ou não na tela atual
     * 
     */
    void move();
    
    EnemyEntity();
    EnemyEntity(sf::Texture& spriteSheet, float posAbsX, float posAbsY, float sizeX, float sizeY);
};

#endif
