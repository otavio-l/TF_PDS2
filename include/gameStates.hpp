#ifndef GAME_STATE_H
#define GAME_STATE_H


#include <memory>
#include "resourceManager.hpp"
#include "entityManager.hpp"
#include "systemsEntities.hpp"
#include "tilemaps.hpp"

#include <SFML/Graphics.hpp>

class Game;

/**
* @brief Classe base abstrata para diferentes estados do jogo.
* 
* Cada estado define sua própria lógica de manipulação de entrada, atualização e renderização.
*/
class GameState {
protected:
    Game& game;
    ResourceManager resources;
public:
    GameState(Game& game) : game(game) {};
//! Manipula a entrada para este estado.
    virtual void handleInput(sf::Event& event) = 0;
    //! Atualiza a lógica do estado.
//! @param dt Delta de tempo desde o último quadro.
    virtual void update(float dt) = 0;
    //! Renderiza o estado para a janela.
    virtual void render(sf::RenderWindow& window) = 0;

    virtual ~GameState() = default;
};

//! Representa o estado do menu principal.
class MenuState : public GameState {
public:
    MenuState(Game &game);
    void handleInput(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

//! Representa o estado do jogo.
class PlayState : public GameState {
    EntityManager entities;
    InputSystem inputSystem;
    std::unique_ptr<TileMap> background;
public:
    PlayState(Game &game);
    void handleInput(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

    void changeBackground(std::unique_ptr<TileMap> newBackground);
};

//! Representa o estado de pausa.
class PausedState : public GameState {
public:
    PausedState(Game &game);
    void handleInput(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif
