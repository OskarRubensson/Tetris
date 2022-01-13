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
#include "LevelHandler.h"
#include "Menu.h"

/**
 * Game-class. Creates and runs the tetris-game. Make sure to run Game::Update() and Game::Draw() constantly.
 */
class Game: public sf::Drawable, public sf::Transformable {
private:
    //Defaults
    const static size_t DEFAULT_ROWS = 30;
    const static size_t DEFAULT_COLUMNS = 15;

    std::unique_ptr<Grid> grid;
    std::vector<Shape> shapes;
    Score score;
    int state = 0;
    Menu pauseMenu;

    // Level related
    LevelHandler levelHandler;

    Clock ticker{400};             // Main clock
    Clock bottomClock{1000};       // Time at bottom before new Shape
    Clock moveClock{70};           // Hold move clock
    size_t moveDir;                         // Hold move direction

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

    // State values
    static const int PAUSED = 0;
    static const int RUNNING = 1;
    static const int GAME_OVER = 2;

    // Input keycodes
    static const size_t UP = 1;
    static const size_t DOWN = 2;
    static const size_t LEFT = 3;
    static const size_t RIGHT = 4;
    static const size_t ENTER = 0;

    // Getters
    /**
     * Getter for the total width of the game.
     * @return float-value of the game's width,
     */
    float width()  { return static_cast<float>(grid->width()) * SQUARE_SIZE * getScale().x; }
    /**
     * Getter for the total height of the game.
     * @return float-value of the game's height.
     */
    float height() { return static_cast<float>(grid->height()) * SQUARE_SIZE * getScale().y; }
    /**
     * Getter for the amount of columns in the game's grid.
     * @return size_t-value of the grid's column-count.
     */
    size_t gridWidth()  { return grid->width(); }
    /**
     * Getter for the amount of rows in the game's grid.
     * @return size_t-value of the grid's row-count.
     */
    size_t gridHeight() { return grid->height(); }
    /**
     * Getter for the games state.
     * @return games current state.
     */
    int getState() const { return state; }

    // Draw
    void update();

    // User move
    bool move(size_t dir);
    void startMove(size_t dir);
    void stopMove();
    void rotate(bool clockwise);

    void pause() { state = PAUSED; }
    void menuInput(size_t input);
};


#endif //TETRIS_GAME_H
