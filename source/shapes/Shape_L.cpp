// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_L.cpp, 2021-12-19 - 2022-01-13
// Contains the implementation of the Shape_L-class' functions.
//

#include "Shape_L.h"

/**
 * Creates a shape with the color and squares of a tetris L-shape.
 */
Shape_L::Shape_L():
Shape({
      {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})},
      {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})},
      {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE})}
    }, sf::Color(255, 165, 0)){ // Orange
}