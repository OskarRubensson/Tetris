// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_Z.cpp, 2021-12-19 - 2022-01-13
// Contains the implementation of the Shape_Z-class' functions.
//

#include "Shape_Z.h"

/**
 * Creates a shape with the color and squares of a tetris Z-shape.
 */
Shape_Z::Shape_Z():
Shape({
    {sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
    {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})},
    {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE})}
}, sf::Color::Red){

}