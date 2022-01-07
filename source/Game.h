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
    const size_t DEFAULT_COLUMNS = 15;

    Grid grid;
    Clock ticker;
    std::vector<Shape> shapes;
    Score score;

    // Level related
    size_t levelTicker;
    size_t level;

    Clock bottomClock;                  // Time at bottom
    Clock moveClock;                    // Hold move clock
    direction moveDir;                  // Hold move direction


    bool addNewObj = true;
    void addRandomShape();

    // Clock-related
    void tickDown();
    void tickMove();

    void start();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    Game();
    Game(size_t rows, size_t columns);

    // Getters
    float width()  { return static_cast<float>(grid.width()) * SQUARE_SIZE; }
    float height() { return static_cast<float>(grid.height()) * SQUARE_SIZE; }

    // Draw
    void update();

    // User move
    bool move(direction dir);
    void startMove(direction dir);
    void stopMove();

    void rotate(bool clockwise);

};


#endif //TETRIS_GAME_H
