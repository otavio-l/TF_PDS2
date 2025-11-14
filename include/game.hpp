#ifndef GAME_H
#define GAME_H


#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gameStates.hpp"


enum class PendingActionType {
    Push,
    Pop,
    Change,
    Nothing
};

struct PendingAction {
    PendingActionType type;
    std::unique_ptr<GameState> state;
};


/**
* @brief Controla o loop principal do jogo e a janela.
* 
* Lida com a criação de janelas, atualizações de estado, entrada e renderização.
*/
class Game {
    // sf::RenderWindow window;
    //SMART POINTER: quando currentState for ser esquecida (saiu do escopo), chama delete para o obj
    // std::unique_ptr<GameState> currentState;
    std::vector<std::unique_ptr<GameState>> stateStack;

    void maintainStates();
public:
    sf::RenderWindow window;
    PendingAction action;
//! Inicializa o jogo e cria a janela principal.
    Game();
//! Executa o loop principal do jogo.
    void run();
};

#endif
