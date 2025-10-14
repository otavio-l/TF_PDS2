#include <SFML/Graphics.hpp>


class Game {
    sf::RenderWindow window;
public:
    Game();

    void run();

    void changeGameState();
};
