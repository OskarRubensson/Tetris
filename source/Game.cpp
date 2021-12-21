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
#include <ctime>
#include <iostream>

Game::Game():
clock(250),
grid(DEFAULT_ROWS, DEFAULT_COLUMNS){
}

Game::Game(size_t rows, size_t columns):
clock(250),
grid(rows, columns){
}

static bool addNewObj = true;
static int counter = 0;
void Game::draw(sf::RenderWindow& window){
    //If clockrate has passed, move
    if (clock.hasTicked()){
        if (addNewObj || counter % 20 == 0){
            std::vector<Shape> miniVector = {Shape_S(), Shape_L(), Shape_T(), Shape_SQR()};
            shape_queue.push_back(miniVector.at(counter % 4));
            addNewObj = false;
            counter = 0;
        }
        auto& s = *(shape_queue.end() - 1);
        grid.insert(s, {5, 0});
        if (!grid.move(s, {0, 1}))
            addNewObj = true;
        counter++;
    }

    for(auto& s: shape_queue){
        s.draw(window);
    }
}