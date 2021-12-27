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
moveClock(100),
grid(DEFAULT_ROWS, DEFAULT_COLUMNS){
    ticker.start();
    moveClock.stop();
}

Game::Game(size_t rows, size_t columns):
ticker(400),
moveClock(100),
grid(rows, columns){
    ticker.start();
    moveClock.stop();
}

void Game::tickDown() {
    // If clock-rate has passed, try moving shape down
    if (ticker.hasTicked()){
        if (addNewObj){
            shape_queue.push_back(Shape_I());
            grid.insert(shape_queue.back(), {3, 0});
            addNewObj = false;
            lastMoveFailed = false;
        }

        auto& s = shape_queue.back();

        if (lastMoveFailed)
            addNewObj = true;
        else if (!grid.move(s, {0, 1}))
            lastMoveFailed = true;
        else
            lastMoveFailed = false;

        counter++;
    }
}

void Game::tickMove() {
    if (moveClock.hasTicked()){
        move(moveDir);
    }
}


void Game::draw(sf::RenderWindow& window){
    tickMove();
    tickDown();

        // Draw border
    sf::RectangleShape border({SQUARE_SIZE * grid.width(), SQUARE_SIZE * grid.height()});
    border.setFillColor(sf::Color::Black);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(SQUARE_SIZE);
    window.draw(border);

        // Draw all shapes
    for(auto& s: shape_queue){
        s.draw(window);
    }
}

bool Game::move(direction dir) {
    auto& s = shape_queue.back();

    switch (dir){
        case LEFT:
            grid.move(s, {-1, 0});
            lastMoveFailed = false;
            addNewObj = false;
            break;

        case RIGHT:
            grid.move(s, {1, 0});
            lastMoveFailed = false;
            addNewObj = false;
            break;

        case DOWN:
            grid.move(s, {0, 1});
            break;

        case UP:
            break;
    }

    return true;
}

bool Game::holdMove(direction dir) {
    moveDir = dir;
    moveClock.start();
}

void Game::stopMove(){
    moveClock.stop();
}