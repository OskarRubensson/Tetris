// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Shape.cpp, 2021-12-18 - 2021-12-18
// kortfattat vad filen innehåller
//

#include "Shape.h"
#include <algorithm>
#include <cmath>       /* round */
#include <utility>


Shape::Shape(std::vector<std::vector<sf::RectangleShape> > squares, sf::Color color):
squares(std::move(squares)),
color(color){
    initProperties();
}


Shape::Shape(std::vector<std::vector<sf::RectangleShape> > squares, sf::Color color, sf::Vector2<float> position):
squares(std::move(squares)),
color(color){
    initProperties();
}

void Shape::initProperties() {
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

std::vector<std::vector<sf::RectangleShape> >& Shape::getSquares() {
    return squares;
}

std::vector<int> Shape::getBottomSquaresRow() {
    std::vector<int> bottom(3, -1);

    for(int rowNo = 0; rowNo < squares.size(); rowNo++){
        for(int colNo = 0; colNo < squares.at(rowNo).size(); colNo++){
            auto rectangle = squares.at(rowNo).at(colNo);
            if(rectangle.getSize().x > 0 && rectangle.getSize().y > 0)
                bottom.at(colNo) = rowNo;
        }
    }
    return bottom;
}

sf::Vector2<int> Shape::getRelativeCenterPosition(const sf::RectangleShape& square) {
    for(int rowNo = 0; rowNo < squares.size(); rowNo++){
        for(int colNo = 0; colNo < squares.at(rowNo).size(); colNo++){
            auto& rect = squares.at(rowNo).at(colNo);
            if (&rect == &square){
                sf::Vector2<int> center = {static_cast<int>(round(squares.size() / 2)),
                                              static_cast<int>(round(squares.at(rowNo).size() / 2))};
                center -= sf::Vector2<int>(colNo, rowNo);
                return center;
            }
        }
    }
    return {0, 0};
}

void Shape::draw(sf::RenderWindow &window) {
    int row_index = 0;
    sf::Color c = color;

    std::for_each(squares.begin(), squares.end(), [&](std::vector<sf::RectangleShape>& rows){
        int col_index = 0;
        std::for_each(rows.begin(), rows.end(), [&](sf::RectangleShape& square){
            if (square.getSize().x > 0 || square.getSize().y > 0)
                window.draw(square);
            col_index++;
        });
        row_index++;
    });
}

void Shape::move(sf::Vector2<int> direction){
    sf::Vector2<float> parsedDirection = {(float)direction.x * SQUARE_SIZE,
                                          (float)direction.y * SQUARE_SIZE};

    int row_index = 0;
    for(std::vector<sf::RectangleShape>& rows: squares){
        int col_index = 0;
        for( sf::RectangleShape& square : rows){
            if (square.getSize().x > 0 || square.getSize().y > 0)
                square.move(parsedDirection);
            col_index++;
        }
    }

    /*std::for_each(squares.begin(), squares.end(), [&](std::vector<sf::RectangleShape>& rows){
        int col_index = 0;
        std::for_each(rows.begin(), rows.end(), [&](sf::RectangleShape& square){
            if (square.getSize().x > 0 || square.getSize().y > 0)
                square.move(parsedDirection);
            col_index++;
        });
        row_index++;
    });*/
}