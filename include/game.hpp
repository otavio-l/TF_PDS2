#ifndef GAME_H
#define GAME_H


#include <memory>
#include <vector>
#include <list>
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

    PendingAction(PendingActionType type, std::unique_ptr<GameState> state) 
    : type(type), state(std::move(state)) {}
};


/**
 * @brief Controla o loop principal do jogo e a janela
 * 
 */
class Game {
private:
    std::vector<std::unique_ptr<GameState>> stateStack;

    /**
     * @brief Trata as requisições de alteração de estado do jogo
     * 
     */
    void maintainStates();
public:
    sf::RenderWindow window;
    std::list<PendingAction> actions;

    /**
     * @brief Inicializa a janela e o estado atual do jogo
     * 
     */
    Game();

    /**
     * @brief Executa o loop principal do jogo
     * 
     */
    void run();
};

#endif
