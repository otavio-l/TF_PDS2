#include "entityManager.hpp"
/**
* @brief Atualiza as posições das entidades com base em suas velocidades.
*/
class PhysicsSystem {
public:
//! Atualiza todas as entidades habilitadas para física.
    void update(EntityManager& em, float dt);
};
/**
* @brief Desenha entidades que possuem um componente Sprite.
*/
class RenderSystem {
public:
//! Renderiza todas as entidades de sprite na janela.
    void draw(EntityManager& em, sf::RenderWindow& window);
};


