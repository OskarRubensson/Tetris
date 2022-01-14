// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_I.cpp, 2021-12-25 - 2022-01-13
// Contains the implementation of the Shape_I-class' functions.
//

#include "Shape_I.h"

/**
 * Creates a shape with the color and squares of a tetris I-shape.
 */
Shape_I::Shape_I():
    Shape({
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})}
    }, sf::Color::Cyan){

}