// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_Z.cpp, 2021-12-19 - 2021-12-19
// kortfattat vad filen innehåller
//

#include "Shape_Z.h"

Shape_Z::Shape_Z():
Shape({
    {sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
    {sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0})},
    {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE})}
}, sf::Color::Red){

}