// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Game.h, 2021-12-15 - 2021-12-15
// kortfattat vad filen innehåller
//

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H


#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;


public:
    Game(int width, int height, std::string title);
    void run();
};


#endif //TETRIS_GAME_H
