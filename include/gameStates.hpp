#ifndef GAME_STATE_H
#define GAME_STATE_H


#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "resourceManager.hpp"
#include "mapArea.hpp"


class Game;


enum SelectedMenuButton {
    PLAY,
    NEW_GAME,
    SETTINGS,
    COUNT
};

/**
 * @brief Botão do menu
 * 
 */
struct Button {
    sf::Sprite play;
    sf::Sprite newGame;
    sf::Sprite settings;
    
    /**
     * @brief Seleciona a textura para o atual botão selecionado
     * 
     * @return sf::Sprite& Textura
     */
    sf::Sprite& getSprite();

    /**
     * @brief Seleciona o próximo botão
     * 
     */
    void next();

    /**
     * @brief Seleciona o botão prévio
     * 
     */
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

    /**
     * @brief Trata a interação com o usuário
     * 
     * @param event Evento do SFML
     */
    virtual void handleInput(sf::Event& event) = 0;

    /**
     * @brief Atualiza o estado do programa
     * 
     * @param dt Intervalo de tempo
     */
    virtual void update(float dt);
    /**
     * @brief Rendeniza os sf::Sprites
     * 
     * @param window Janela para rendenização
     */
    virtual void render(sf::RenderWindow& window) = 0;

    virtual ~GameState() = default;
};

/**
 * @brief Estado de menu
 * 
 */
class MenuState : public GameState {
    sf::Sprite background;
    Button button;
public:
    MenuState(Game &game);
    /**
     * @brief Interação do usuário com os botões
     * 
     * @param event Evento do SFML
     */
    void handleInput(sf::Event& event) override;
    /**
     * @brief Rendeniza o menu com o botão selecionado
     * 
     * @param window Janela de rendenização
     */
    void render(sf::RenderWindow& window) override;
};

/**
 * @brief Estado de gameplay
 * 
 */
class PlayState : public GameState {
    PlayerEntity mainCharacter;
    MapArea mapArea;
    EnemyEntity enemy;
public:
    PlayState(Game &game);

    /**
     * @brief Trata da interação do usuário para movimentação do personagem e pausa
     * 
     * @param event Evento do SFML
     */
    void handleInput(sf::Event& event) override;

    /**
     * @brief Atualiza posições e mapas
     * 
     * @param dt Intervalo de tempo
     */
    void update(float dt) override;

    /**
     * @brief Rendeniza os sprites por profundidade
     * 
     * @param window Janela de rendenização
     */
    void render(sf::RenderWindow& window) override;
};

/**
 * @brief Estado de pausa
 * 
 */
class PausedState : public GameState {
    sf::Sprite background;
public:
    PausedState(Game &game);
    /**
     * @brief Trata do input para retornar ao jogo
     * 
     * @param event Evento do SFML
     */
    void handleInput(sf::Event& event) override;
    void render(sf::RenderWindow& window) override;
};

/**
 * @brief Estado de cutscene
 * 
 */
class Cutscene : public GameState {
    int currentFrame;
    int quantFrame;
    float dtTotal;
    int currentRepetition;

    std::string spriteFile;
    float intervalSec; 
    int repetitions;
    std::string next;
public:
    /**
     * @brief Lê o arquivo de configuração da cutscene
     * 
     * @param jsonFile Arquivo de configuração
     */
    void loadJson(std::string jsonFile);

    Cutscene(Game &game, std::string jsonFile);

    /**
     * @brief Trata a interação do usuário para pausas
     * 
     * @param event Evento do SFML
     */
    void handleInput(sf::Event& event) override;

    /**
     * @brief Atualiza o frame
     * 
     * @param dt Intervalo de tempo
     */
    void update(float dt) override;

    /**
     * @brief Rendeniza frame atual
     * 
     * @param window Janela de rendenização
     */
    void render(sf::RenderWindow& window) override;
};

class GameOverState : public GameState {
    sf::Sprite background;
public:
    GameOverState(Game &game);
    /**
     * @brief Trata do input para retornar ao jogo
     * 
     * @param event Evento do SFML
     */
    void handleInput(sf::Event& event) override;
    void render(sf::RenderWindow& window) override;
};

#endif
