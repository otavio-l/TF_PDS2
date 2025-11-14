#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "resourceManager.hpp"
#include "systemsEntities.hpp"
#include "parser.hpp"


class Game;


enum SelectedMenuButton {
    PLAY,
    NEW_GAME,
    SETTINGS,
    COUNT
};

struct Button {
    sf::Sprite play;
    sf::Sprite newGame;
    sf::Sprite settings;
    sf::Sprite& getSprite();
    void next();
    void previous();
    SelectedMenuButton getButton();
    SelectedMenuButton selectedButton;
};


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
    GameState(Game& game);
//! Manipula a entrada para este estado.
    virtual void handleInput(sf::Event& event) = 0;
    //! Atualiza a lógica do estado.
//! @param dt Delta de tempo desde o último quadro.
    virtual void update(float dt);
    //! Renderiza o estado para a janela.
    virtual void render(sf::RenderWindow& window) = 0;

    virtual ~GameState() = default;
};

//! Representa o estado do menu principal.
class MenuState : public GameState {
    sf::Sprite background;
    Button button;
public:
    MenuState(Game &game);
    void handleInput(sf::Event& event) override;
    void render(sf::RenderWindow& window) override;
};

//! Representa o estado do jogo.
class PlayState : public GameState {
    Entity mainCharacter;
    MapArea mapArea;
    InputSystem inputSystem;
public:
    PlayState(Game &game);
    void handleInput(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

//! Representa o estado de pausa.
class PausedState : public GameState {
public:
    PausedState(Game &game);
    void handleInput(sf::Event& event) override;
    void render(sf::RenderWindow& window) override;
};

#endif
