#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

/**
* @brief Controla o loop principal do jogo e a janela.
* 
* Lida com a criação de janelas, atualizações de estado, entrada e renderização.
*/
class Game {
    sf::RenderWindow window;
public:
//! Inicializa o jogo e cria a janela principal.
    Game();
//! Executa o loop principal do jogo.
    void run();
//! Altera o estado atual do jogo (menu, jogar, pausado, etc.).
    void changeGameState();
};

#endif