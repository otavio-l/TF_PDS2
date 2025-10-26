#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>
/**
* @brief Classe base abstrata para diferentes estados do jogo.
* 
* Cada estado define sua própria lógica de manipulação de entrada, atualização e renderização.
*/
class GameState {
public:
//! Manipula a entrada para este estado.
    virtual void handleInput() = 0;
    //! Atualiza a lógica do estado.
//! @param dt Delta de tempo desde o último quadro.
    virtual void update(float dt) = 0;
    //! Renderiza o estado para a janela.
    virtual void render(sf::RenderWindow& window) = 0;

    virtual ~GameState() = default;
};
//! Representa o estado do menu principal.
class MenuState : public GameState {};
//! Representa o estado do jogo.
class PlayState : public GameState {};
//! Representa o estado de pausa.
class PausedState : public GameState {};

#endif
