// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_S.cpp, 2021-12-19 - 2022-01-13
// kortfattat vad filen innehåller
//

#include "Shape_S.h"

/**
 * Creates a shape with the color and squares of a tetris S-shape.
 */
Shape_S::Shape_S():
Shape({
      {sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
      {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE})},
      {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})}
 }, sf::Color::Green){

}