// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Game.cpp, 2021-12-17 - 2021-12-17
// kortfattat vad filen innehåller
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

Game::Game():
ticker(400),
moveClock(50),
grid(DEFAULT_ROWS, DEFAULT_COLUMNS),
score(){
    srand(time(nullptr));
    ticker.start();
    moveClock.stop();
}

Game::Game(size_t rows, size_t columns):
ticker(400),
moveClock(50),
grid(rows, columns),
score(){
    srand(time(nullptr));
    ticker.start();
    moveClock.stop();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Draw border
    sf::RectangleShape border({SQUARE_SIZE * (float)grid.width(), SQUARE_SIZE * ((float)grid.height() - 1)});
    border.setFillColor(sf::Color::Black);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(SQUARE_SIZE);
    border.setPosition(0, SQUARE_SIZE);
    target.draw(border);

    // Draw all shapes
    for(auto& s: shapes){
        target.draw(s);
    }
}

void Game::update(){
    tickMove();
    tickDown();
}

bool Game::move(direction dir) {
    auto& s = shapes.back();

    switch (dir){
        case LEFT:
            grid.move(s, {-1, 0});
            break;

        case RIGHT:
            grid.move(s, {1, 0});
            break;

        case DOWN:
            grid.move(s, {0, 1});
            break;

        case UP:
            while(grid.move(s, {0, 1}));
            break;
    }

    return true;
}

void Game::tickDown() {
    // If clock-rate has passed, try moving shape down
    if (ticker.hasTicked()){
        if (addNewObj){
            size_t rowsCleared = grid.clearFullRows();
            if (rowsCleared > 0)
                score.add(rowsCleared);

            if (!grid.isRowEmpty(0)) {
                // GAME OVER
            }
            addRandomShape();
            addNewObj = false;
        }

        auto& s = shapes.back();
        if (!grid.move(s, {0, 1}))
            addNewObj = true;
    }
}

void Game::tickMove() {
    if (moveClock.hasTicked()){
        move(moveDir);
        addNewObj = false;
    }
}

void Game::startMove(direction dir) {
    moveDir = dir;
    moveClock.start();
}

void Game::stopMove(){
    moveClock.stop();
}

void Game::addRandomShape(){
    Shape available[7] {Shape_I(), Shape_J(), Shape_L(), Shape_S(), Shape_SQR(), Shape_T(), Shape_Z()};
    shapes.push_back(available[ rand() % 7 ]);
    grid.insert(shapes.back(), {static_cast<int>(grid.width() / 2), 0});
}

void Game::rotate(bool clockwise) {
    auto& s = shapes.back();
    grid.rotate(s, clockwise);
    addNewObj = false;
}
