// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Game.h, 2021-12-17 - 2021-12-17
// kortfattat vad filen innehåller
//

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <SFML/Graphics.hpp>
#include "Clock.h"
#include "shapes/Shape.h"
#include "Grid.h"

class Game {
private:
    //Defaults
    const size_t DEFAULT_ROWS = 40;
    const size_t DEFAULT_COLUMNS = 40;

    Clock clock;
    std::vector<Shape> shape_queue;
    Grid grid;

    bool addNewObj = true;
    int counter = 0;

public:
    Game();
    Game(size_t rows, size_t columns);

    //Draw
    void draw(sf::RenderWindow& window);

};


#endif //TETRIS_GAME_H
