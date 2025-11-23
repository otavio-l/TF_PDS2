#ifndef MOVEMENT_H
#define MOVEMENT_H


#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "mapArea.hpp"
#include "game.hpp"


void continuousAction(sf::Event& event, LiveEntity& mainCharacter);

void updatePosition(LiveEntity& mainCharacter, float dx, float dy);


#endif
