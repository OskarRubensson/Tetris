// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_J.cpp, 2021-12-19 - 2022-01-13
// Contains the implementation of the Shape_J-class' functions.
//

#include "Shape_J.h"

/**
 * Creates a shape with the color and squares of a tetris J-shape.
 */
Shape_J::Shape_J():
Shape({
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})},
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})},
        {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})}
    }, sf::Color::Blue){
}