#ifndef GAME_H
#define GAME_H


#include "gameStates.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

/**
* @brief Controla o loop principal do jogo e a janela.
* 
* Lida com a criação de janelas, atualizações de estado, entrada e renderização.
*/
class Game {
    // sf::RenderWindow window;
    //SMART POINTER: quando currentState for ser esquecida (saiu do escopo), chama delete para o obj
    std::unique_ptr<GameState> currentState;
public:
    sf::RenderWindow window;
//! Inicializa o jogo e cria a janela principal.
    Game();
//! Executa o loop principal do jogo.
    void run();
//! Altera o estado atual do jogo (menu, jogar, pausado, etc.).
    void changeGameState(std::unique_ptr<GameState> newState);
};

#endif