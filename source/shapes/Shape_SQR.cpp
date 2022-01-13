// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_SQR.cpp, 2021-12-18 - 2022-01-13
// kortfattat vad filen innehåller
//

#include "Shape_SQR.h"

/**
 * Creates a shape with the color and squares of a tetris Square-shape.
 */
Shape_SQR::Shape_SQR():
Shape({
              {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE})},
              {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE})}
      }, sf::Color::Yellow){

}