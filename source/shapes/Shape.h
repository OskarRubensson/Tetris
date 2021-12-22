// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape.h, 2021-12-18 - 2021-12-18
// kortfattat vad filen innehåller
//

#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H


#include <SFML/Graphics.hpp>

const float SQUARE_SIZE = 10;

class Shape {
    sf::Color color;
    std::vector<std::vector<sf::RectangleShape> > squares;

    void initProperties();
public:
    Shape() = delete;
    Shape(std::vector<std::vector<sf::RectangleShape> > squares, sf::Color color);
    Shape(std::vector<std::vector<sf::RectangleShape> > squares, sf::Color color, sf::Vector2<float> position);

    //Getters
    std::vector<std::vector<sf::RectangleShape> >& getSquares();
    std::vector<int> getBottomSquaresRow();
    sf::Vector2<int> getRelativeCenterPosition(const sf::RectangleShape& square);


    virtual void draw(sf::RenderWindow& window);
    virtual void move(sf::Vector2<int> direction);
};


#endif //TETRIS_SHAPE_H
