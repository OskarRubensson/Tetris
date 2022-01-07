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
#include "Score.h"

enum direction{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Game: public sf::Drawable {
private:
    //Defaults
    const size_t DEFAULT_ROWS = 30;
    const size_t DEFAULT_COLUMNS = 20;

    Grid grid;
    Clock ticker;
    std::vector<Shape> shapes;
    Score score;

    Clock moveClock;                    // Hold move clock
    direction moveDir = DOWN;           // Hold move direction

    // Settings
    const int MOVE_HOLD_SPEED = 80;

    bool addNewObj = true;
    void addRandomShape();

    // Clock-related
    void tickDown();
    void tickMove();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    Game();
    Game(size_t rows, size_t columns);

    // Draw
    void update();

    // User move
    bool move(direction dir);
    void startMove(direction dir);
    void stopMove();

    void rotate(bool clockwise);

};


#endif //TETRIS_GAME_H
