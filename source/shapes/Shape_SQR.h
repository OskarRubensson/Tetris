// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_SQR.h, 2021-12-18 - 2021-12-18
// kortfattat vad filen innehåller
//

#ifndef TETRIS_SHAPE_SQR_H
#define TETRIS_SHAPE_SQR_H


#include "Shape.h"

const std::vector<std::vector<sf::RectangleShape> > SQR = {
    {sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
    {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})},
    {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})}
};

class Shape_SQR: public Shape {
public:
    Shape_SQR();
};


#endif //TETRIS_SHAPE_SQR_H
