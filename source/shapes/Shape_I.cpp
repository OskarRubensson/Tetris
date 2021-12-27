// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape_I.cpp, 2021-12-25 - 2021-12-25
// kortfattat vad filen innehåller
//

#include "Shape_I.h"

Shape_I::Shape_I():
    Shape({
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})},
        {sf::RectangleShape({0, 0}), sf::RectangleShape({SQUARE_SIZE, SQUARE_SIZE}), sf::RectangleShape({0, 0}), sf::RectangleShape({0, 0})}
    }, sf::Color::Cyan){

}