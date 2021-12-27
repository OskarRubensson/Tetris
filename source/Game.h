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

enum direction{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Game {
private:
    //Defaults
    const size_t DEFAULT_ROWS = 30;
    const size_t DEFAULT_COLUMNS = 20;

    Clock ticker;
    std::vector<Shape> shape_queue;
    Grid grid;

    Clock moveClock;                    // Hold move clock
    direction moveDir;                  // Hold move direction

    // Settings
    const int MOVE_HOLD_SPEED = 100;

    bool addNewObj = true;
    int counter = 0;
    bool lastMoveFailed = false;

public:
    Game();
    Game(size_t rows, size_t columns);

    // Clock-related
    void tickDown();
    void tickMove();

    // Draw
    void draw(sf::RenderWindow& window);

    bool move(direction dir);
    bool holdMove(direction dir);
    void stopMove();

};


#endif //TETRIS_GAME_H
