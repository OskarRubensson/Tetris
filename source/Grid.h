// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Grid.h, 2021-12-20 - 2021-12-20
// kortfattat vad filen innehåller
//

#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H


#include <cstddef>
#include "shapes/Shape.h"
#include <algorithm>


struct node {
    Shape* shape = nullptr;
    sf::RectangleShape* object = nullptr;

    node():shape(), object() {};
    node(Shape& shape, sf::RectangleShape& object):shape(&shape), object(&object) {};
};

class Grid {
    std::vector<node> grid;
    const size_t WIDTH;
    const size_t DEFAULT_X;
    const size_t DEFAULT_Y;


public:
    Grid(size_t rows, size_t columns);

    void insert(Shape& shape, sf::Vector2<int> position = {3, 3});
    bool move(sf::Vector2<int> position, sf::Vector2<int> direction);
    bool move(Shape& shape, sf::Vector2<int> direction);
    node* get(sf::Vector2<int> position);
    sf::Vector2<int> get(node& n_ptr);

    template<typename T>
    sf::Vector2<int> indexToVector(T index) const{
        int x = index % WIDTH;
        int y = index / WIDTH;
        return {x, y};
    }

    template<typename T>
    int vectorToIndex(sf::Vector2<T> position) const{
        return position.y * WIDTH + position.x;
    }

};


#endif //TETRIS_GRID_H
