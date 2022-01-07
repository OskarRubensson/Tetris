// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape.h, 2021-12-18 - 2021-12-18
// kortfattat vad filen innehåller
//

#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H


#include <SFML/Graphics.hpp>

const float SQUARE_SIZE = 25;

class Shape: public sf::Drawable{
    sf::Color color;
    std::vector<std::vector<sf::RectangleShape> > squares;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Shape() = delete;
    Shape(std::vector<std::vector<sf::RectangleShape> > squares, sf::Color color);

    void resetProperties();

    //Getters
    std::vector<std::vector<sf::RectangleShape> >& getSquares();
    sf::Vector2<int> getRelativeCenterPosition(const sf::RectangleShape* square);

    virtual void move(sf::Vector2<int> direction);
    virtual void rotate(bool clockwise);
};


#endif //TETRIS_SHAPE_H
