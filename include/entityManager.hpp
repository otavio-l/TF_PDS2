#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <unordered_map>

//! Tipo de identificador exclusivo para entidades.
using Entity = std::uint32_t;
//! Representa a posição de uma entidade no espaço 2D.
struct Position { float x, y; };
//! Representa a velocidade de uma entidade no espaço 2D.
struct Velocity { float vx, vy; };
//! Envolve um sprite SFML como um componente desenhável.
struct Sprite  { sf::Sprite sprite; };

/**
* @brief Gerencia entidades e seus componentes.
* 
* O EntityManager armazena e organiza entidades do jogo e seus
* componentes associados (Posição, Velocidade, Sprite, etc.).
* Ele fornece métodos para criar novas entidades e recuperar
* aquelas que possuem componentes específicos.
*/
class EntityManager {
    // Each entity may or may not have this components
    std::unordered_map<Entity, Position> positions;
    std::unordered_map<Entity, Velocity> velocities;
    std::unordered_map<Entity, Sprite> sprites;
    Entity nextEntity;

public:
    EntityManager();

//! Cria uma nova entidade única e retorna seu identificador.
    Entity createEntity();

    template <typename T>
    //! Adiciona componentes à entidade fornecida (implementação a ser definida).
    void addComponent(Entity e, const T& comp);

    //! Retorna todas as entidades que possuem um componente de dado tipo
    template <typename Component>
    std::vector<Entity> withComponent();
};

#endif
