#ifndef MOVEMENT_H
#define MOVEMENT_H


#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "mapArea.hpp"
#include "game.hpp"


/**
 * @brief Trata a movimentação contínua do player
 * 
 * @param event Evento do SFML
 * @param mainCharacter Entidade do player
 */
void continuousAction(sf::Event& event, LiveEntity& mainCharacter);

/**
 * @brief Atualiza as posições da entidade
 * 
 * @param mainCharacter Entidade
 * @param dx Deslocamento horizontal
 * @param dy Deslocamento vertical
 */
void updatePosition(LiveEntity& mainCharacter, float dx, float dy);


#endif
