// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Game.cpp, 2021-12-17 - 2021-12-17
// This file includes the implementations for the Game-functions
//

#include "Game.h"
#include "shapes/Shape.h"
#include "shapes/Shape_SQR.h"
#include "shapes/Shape_J.h"
#include "shapes/Shape_L.h"
#include "shapes/Shape_Z.h"
#include "shapes/Shape_T.h"
#include "shapes/Shape_S.h"
#include "shapes/Shape_I.h"
#include <ctime>
#include <iostream>

/**
 * Default constructor - Uses parametrized constructor with default values
 */
Game::Game():
Game(DEFAULT_ROWS, DEFAULT_COLUMNS){ }

/**
 * Parametrized constructor - Creates a Tetris game with a certain rows and columns-size. Also starts the game directly.
 * @param rows The amount of rows the game should have
 * @param columns The amount of columns the game should have
 */
Game::Game(size_t rows, size_t columns):
grid(std::make_unique<Grid>(rows, columns)),
pauseMenu({"Resume", "Back to Main Menu"}){
    pauseMenu.setScale({0.7f, 0.7f});
    score.setPosition({0, -SQUARE_SIZE - 10});
    start();
}

/**
 * Starts the ticking-clock and sets the game in state Game::RUNNING
 */
void Game::start(){
    srand(time(nullptr));
    ticker.start();
    moveClock.stop();
    state = RUNNING;
}

/**
 * Prints the Game onto a target. Should be run each tick of the runtime.
 * @param target The target to print upon
 * @param states States to apply to the target. Retrieved from sf::Transformable
 */
void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    // Draw border
    sf::RectangleShape border({SQUARE_SIZE * (float)grid->width(), SQUARE_SIZE * ((float)grid->height() - 1)});
    border.setFillColor(sf::Color::Black);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(SQUARE_SIZE);
    border.setPosition(0, SQUARE_SIZE);
    target.draw(border, states);

    // Draw all shapes
    for(auto& s: shapes){
        target.draw(s, states);
    }

    // Draw score
    target.draw(score, states);

    if (getState() == PAUSED)
        target.draw(pauseMenu, states);
}

/**
 * Runs each tick. Performs movement if their respective clocks has ticked.
 */
void Game::update(){
    if (state != RUNNING)
        return;
    tickMove();
    tickDown();
}

/**
 * Tries to move the lastly inserted shape in the according direction.
 * @param dir The direction of the movement. Use Game::UP, Game::DOWN, Game::LEFT or Game::RIGHT
 * @return Bool based on if move was successful or not.
 */
bool Game::move(size_t dir) {
    auto& s = shapes.back();

    switch (dir){
        case LEFT:
            return grid->move(s, {-1, 0});

        case RIGHT:
            return grid->move(s, {1, 0});

        case DOWN:
            return grid->move(s, {0, 1});

        case UP:
            while(grid->move(s, {0, 1}));
            return true;
    }
    return false;
}

/**
 * Performs the tetris-tick that tries to move the last inserted shape downwards.
 * If object is at bottom and has been there for bottomClock-time then a new shape is added.
 */
void Game::tickDown() {
    // If clock-rate has passed, try moving shape down
    if (ticker.hasTicked()){
        // Player gets some secs while reaching bottom before new shape added
        if (addNewObj && (bottomClock.hasTicked() || !bottomClock.isRunning()) ){
            // Clear full rows and add correct score
            size_t rowsCleared = grid->clearFullRows();
            if (rowsCleared > 0)
                score.add(rowsCleared);

            // .tick() returns true on levelUp
            if (levelHandler.tick()){
                score.increaseLevel(levelHandler.getLevel());
                moveClock.setClockrate(moveClock.getClockrate() * 0.7);
            }

            if (!grid->isRowEmpty(0)) {
                state = GAME_OVER;
            }

            addRandomShape();
        }
            //Try ticking down
        auto& s = shapes.back();
        if (!grid->move(s, {0, 1})){
            addNewObj = true;
            if (!bottomClock.isRunning())
                bottomClock.start(true);
        }
    }
}

/**
 * Uses a clock with fast clockrate that moves the object in a certain direction for each tick.
 * Use Game::startMove to start this ticker and set direction, and Game::stopMove to stop it.
 * Also prevents new objects from being added for a short while. Enables for user to hold down movement-button.
 */
void Game::tickMove() {
    if (moveClock.hasTicked()){
        move(moveDir);
        addNewObj = false;
    }
}

/**
 * Starts the move-clock and sets the move-direction so that each time Game::tickMove() is run the latest inserted shape will move.
 * Preferably run when a movement-button is pressed.
 * @param dir The direction for the shape to move in each tick
 */
void Game::startMove(size_t dir) {
    moveDir = dir;
    moveClock.start();
}

/**
 * Stops the move-clock. Preferably run when a movement-button is released.
 * Redirect input to menu if game is in state Game::PAUSED
 */
void Game::stopMove(){
    // Redirect input to pause-menu
    if (state == PAUSED){
        menuInput(moveDir);
    }
    moveClock.stop();
}

/**
 * Inserts a new random shape at the top-center of the grid.
 */
void Game::addRandomShape(){
    Shape available[7] {Shape_I(), Shape_J(), Shape_L(), Shape_S(), Shape_SQR(), Shape_T(), Shape_Z()};
    shapes.push_back(available[ rand() % 7 ]);
    grid->insert(shapes.back(), {static_cast<int>(grid->width() / 2), 0});
    addNewObj = false;
    bottomClock.stop();
}

/**
 * Rotates the latest inserted shape 90-degrees clockwise or counter-clockwise.
 * @param clockwise If true the shape is rotated clockwise, if not it will rotate counter-clockwise.
 */
void Game::rotate(bool clockwise) {
    auto& s = shapes.back();
    grid->rotate(s, clockwise);
    addNewObj = false;
}

/**
 * Translates user-input to functions on pauseMenu.
 * Valid inputs are Game::UP, Game::DOWN and Game::ENTER.
 * @param input Input to translate.
 */
void Game::menuInput(size_t input) {
    if (input == UP)
        pauseMenu.move(Menu::UP);
    else if (input == DOWN)
        pauseMenu.move(Menu::DOWN);
    else if (input == ENTER){
        size_t btnID = pauseMenu.click();
        if (btnID == 0)
            state = RUNNING;
        else
            state = GAME_OVER;
    }
}
