#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H


#include "entity.hpp"
#include "mapArea.hpp"


class Game;

/**
 * @brief Calcula se haverá colisão entre as entidades na próxima posição
 * 
 * @param mainCharacter Entidade 1
 * @param e Entidade 2
 * @param dx Deslocamento horizontal
 * @param dy Deslocamento vertical
 * @return true Haverá colisão
 * @return false Não haverá colisão
 */
bool checkCollision(Entity& mainCharacter, Entity& e, float dx, float dy);

/**
 * @brief Calcula se haverá colisão entre a entidade principal e todas as entidades no mapa na próxima posição
 * 
 * @param mainCharacter Entidade principal
 * @param mapArea Contém todas as entidades do mapa
 * @param game Objeto do gerenciamento do jogo
 * @param vel Velocidade da entidade principal
 * @return Direction Quais direções terão colisão
 */
Direction collisionReaction(LiveEntity& mainCharacter, MapArea& mapArea, Game& game, float vel);

/**
 * @brief Trata colisão com uma entidade com gatilho
 * 
 * @param e Entidade gatilho 
 * @param mapArea Objeto para trocar de mapa
 * @param game Objeto para trocar de estado do jogo
 * @param mainCharacter Entidade principal
 */
void triggerDispatcher(MapEntity& e, MapArea& mapArea, Game& game, LiveEntity& mainCharacter);


#endif
