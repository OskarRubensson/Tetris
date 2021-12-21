// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_SQR.cpp, 2021-12-18 - 2021-12-18
// kortfattat vad filen innehåller
//

#include "Shape_SQR.h"

Shape_SQR::Shape_SQR():
Shape({
              {sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
              {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})},
              {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})}
      }, sf::Color::Yellow){

}