#ifndef SYSTEMS_ENTITIES_H
#define SYSTEMS_ENTITIES_H


#include "entity.hpp"
#include "mapArea.hpp"


class Game;


bool checkCollision(Entity& mainCharacter, Entity& e, float dx, float dy);

Direction collisionReaction(LiveEntity& mainCharacter, MapArea& mapArea, Game& game, float vel);

void triggerDispatcher(MapEntity& e, MapArea& mapArea, Game& game, LiveEntity& mainCharacter);


#endif
