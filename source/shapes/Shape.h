// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape.h, 2021-12-18 - 2022-01-13
// Contains the class-declaration of the shape-class.
//

#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H


#include <SFML/Graphics.hpp>

static const float SQUARE_SIZE = 25;

/**
 * Manages a set of sf::Rectangles so that they together form a tetris-shape.
 */
class Shape: public sf::Drawable{
    sf::Color color;
    std::vector<std::vector<sf::RectangleShape> > squares;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Shape() = delete;
    Shape(std::vector<std::vector<sf::RectangleShape> > squares, sf::Color color);

    void resetProperties();

    //Getters
    /**
     * Getter for the shapes squares.
     * @return 2D-vector containing the squares.
     */
    std::vector<std::vector<sf::RectangleShape> >& getSquares(){ return squares; };
    sf::Vector2<int> getRelativeCenterPosition(const sf::RectangleShape* square);

    virtual void move(sf::Vector2<int> direction);
    virtual void rotate(bool clockwise);
};


#endif //TETRIS_SHAPE_H
