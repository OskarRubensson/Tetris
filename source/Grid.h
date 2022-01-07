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

public:
    Grid(size_t rows, size_t columns);

    // Getters
    node* get(sf::Vector2<int> position);
    sf::Vector2<int> get(node& n_ptr);
    size_t width();
    size_t height();
    size_t width() const;
    size_t height() const;

    // Utility
    void remove(Shape& shape);
    bool insert(Shape& shape, sf::Vector2<int> position = {0, 0});
    bool move(node* n, sf::Vector2<int> direction);
    bool move(Shape& shape, sf::Vector2<int> direction);
    bool rotate(Shape& shape, bool clockwise);
    bool isRowFull(size_t row);
    bool isRowEmpty(size_t row);
    size_t clearFullRows();

    template<typename It>
    void clear(It start, It end){
        size_t width = std::distance(start, end);
        std::for_each(start, end, [](node& n){ n.object->setSize({0, 0});});
        grid.erase(start, end);
        grid.insert(grid.begin(), width, node());
    }

    template<typename It>
    void swapShapes(It start, It end){
        for (auto it = start; it != end; it++){
            std::swap(grid.at((*it).first), grid.at((*it).second));
        }
    }

    /***** Vector <-> Index parsers *****/
    template<typename T>
    sf::Vector2<int> indexToVector(T index) const{
        int x = index % WIDTH;
        int y = index / WIDTH;
        return {x, y};
    }

    template<typename T>
    sf::Vector2<int> indexToVector(T index, size_t width) const{
        int x = index % width;
        int y = index / width;
        return {x, y};
    }

    template<typename T>
    int vectorToIndex(sf::Vector2<T> position) const{
        return position.y * WIDTH + position.x;
    }

    template<typename T>
    int vectorToIndex(sf::Vector2<T> position, size_t width) const{
        return position.y * width + position.x;
    }

};


#endif //TETRIS_GRID_H
