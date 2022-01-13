// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape.cpp, 2021-12-18 - 2022-01-13
// Contains the implementation of the shape-class functions.
//

#include "Shape.h"
#include <algorithm>
#include <cmath>       /* round */

/**
 * Creates a shape with a certain set of rectangles (2d-vector) and color.
 * @param squares The squares that the shape consists of
 * @param color The color of the shape
 */
Shape::Shape(std::vector<std::vector<sf::RectangleShape> > squares, sf::Color color):
squares(std::move(squares)),
color(color){
    resetProperties();
}

/**
 * Resets all properties as they were on initialization
 */
void Shape::resetProperties() {
    int row_index = 0;
    std::for_each(squares.begin(), squares.end(), [&](std::vector<sf::RectangleShape>& rows){
        int col_index = 0;
        std::for_each(rows.begin(), rows.end(), [&](sf::RectangleShape& square){
            if (square.getSize().x > 0 || square.getSize().y > 0){
                square.setPosition((float)col_index * SQUARE_SIZE,
                                   (float)row_index * SQUARE_SIZE);
                square.setFillColor(color);
            }
            ++col_index;
        });
        ++row_index;
    });
}

/**
 * Given a certain square inside the shape. Get it's relative position to the middle square.
 * @param square The square to check against.
 * @return sf::Vector2<int> that contains the vector between square and the middle-center.
 */
sf::Vector2<int> Shape::getRelativeCenterPosition(const sf::RectangleShape* square) {
    for(int rowNo = 0; rowNo < squares.size(); rowNo++){
        for(int colNo = 0; colNo < squares.at(rowNo).size(); colNo++){
            auto& rect = squares.at(rowNo).at(colNo);
            if (&rect == square){
                sf::Vector2<int> center = {static_cast<int>(round(squares.size() / 2)),
                                              static_cast<int>(round(squares.at(rowNo).size() / 2))};
                center -= sf::Vector2<int>(colNo, rowNo);
                return center;
            }
        }
    }
    return {0, 0};
}

/**
 * Draws each square that the shape consists of.
 * @param target Target to draw upon.
 * @param states States gotten from transformable-parent
 */
void Shape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    std::for_each(squares.begin(), squares.end(), [&target,&states](const std::vector<sf::RectangleShape>& rows){
        std::for_each(rows.begin(), rows.end(), [&target, &states](const sf::RectangleShape& square){
            if (square.getSize().x > 0 || square.getSize().y > 0)
                target.draw(square, states);
        });
    });
}

/**
 * Move each square in a given direction.
 * @param direction sf::Vector2 containing the direction we want to move in.
 */
void Shape::move(sf::Vector2<int> direction){
    sf::Vector2<float> parsedDirection = {(float)direction.x * SQUARE_SIZE,
                                          (float)direction.y * SQUARE_SIZE};

    for(std::vector<sf::RectangleShape>& rows: squares){
        for( sf::RectangleShape& square : rows){
            if (square.getSize().x > 0 || square.getSize().y > 0)
                square.move(parsedDirection);
        }
    }
}

/**
 * Change index of each square inside their 2d-vector so that the vector "rotates".
 * @param clockwise Rotates clockwise if true, counter-clockwise if not.
 */
void Shape::rotate(bool clockwise) {
    std::vector<std::vector<sf::RectangleShape> > rotated_squares{
        squares[0].size(),
        std::vector<sf::RectangleShape>{squares.size()}
    };

    for(int x = 0; x < squares.size(); x++){
        for(int y = 0; y < squares[x].size(); y++) {
            if (clockwise)
                rotated_squares[y][-x -1 + squares[x].size()] = std::move(squares[x][y]);
            else
                rotated_squares[-y -1 + squares.size()][x] = std::move(squares[x][y]);
        }
    }
    squares = std::move(rotated_squares);
}
