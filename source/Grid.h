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

/**
 * Node contains a pointer to a shape and the specific object of the shape.
 */
struct node {
    Shape* shape = nullptr;
    sf::RectangleShape* object = nullptr;

    node():shape(), object() {};
    node(Shape& shape, sf::RectangleShape& object):shape(&shape), object(&object) {};
};

/**
 * A 2D-grid of nodes for the shapes to position themselves inside.
 * Having them in such a grid simplifies the collision detection-algorithms.
 */
class Grid {
    std::vector<node> grid;
    const size_t WIDTH;

    /**
     * Takes iterators pointing on pair of grid-indexes. Swaps pair-first with pair-second.
     * @tparam It Iterator-type that must dereference to a std::pair<size_t, size_t>.
     * @param start Iterator of where to start swapping.
     * @param end Iterator of where to stop swapping.
     */
    template<typename It>
    void swapShapes(It start, It end){
        for (auto it = start; it != end; it++){
            std::swap(grid.at((*it).first), grid.at((*it).second));
        }
    }

    /**
     * Parses an index to a position in the grid.
     * @tparam T Numerical value of the index.
     * @param index Index to parse into a sf::Vector2<int>
     * @return Returns a sf::Vector2<int> containing the grid-position.
     */
    template<typename T>
    sf::Vector2<int> indexToVector(T index) const{
        int x = index % WIDTH;
        int y = index / WIDTH;
        return {x, y};
    }

    /**
     * Parses an index to a position in the grid.
     * @tparam T Numerical value of the index.
     * @param index The index to parse.
     * @param width The width of the grid.
     * @return sf::Vector2<int> containing the position of the index.
     */
    template<typename T>
    sf::Vector2<int> indexToVector(T index, size_t width) const{
        int x = index % width;
        int y = index / width;
        return {x, y};
    }

    /**
     * Parses a position to an index in the grid.
     * @tparam T Numerical type of the X and Y coordinates
     * @param position The position to parse.
     * @return Value of the index in the grid.
     */
    template<typename T>
    int vectorToIndex(sf::Vector2<T> position) const{
        return position.y * WIDTH + position.x;
    }

    /**
     * Parses a position to an index in the grid.
     * @tparam T Numerical type of the X and Y coordinates
     * @param position The position to parse.
     * @param width The width of the grid.
     * @return Value of the index in the grid.
     */
    template<typename T>
    int vectorToIndex(sf::Vector2<T> position, size_t width) const{
        return position.y * width + position.x;
    }

public:
    Grid(size_t rows, size_t columns);

    // Getters
    node* get(sf::Vector2<int> position);
    sf::Vector2<int> get(node& n_ptr);
    size_t width();
    size_t height();
    [[nodiscard]] size_t width() const;
    [[nodiscard]] size_t height() const;
    auto begin() { return grid.begin(); }
    auto end() { return grid.end(); }

    // Utility
    void remove(Shape& shape);
    bool insert(Shape& shape, sf::Vector2<int> position = {0, 0});
    bool move(Shape& shape, sf::Vector2<int> direction);
    bool rotate(Shape& shape, bool clockwise);
    bool isRowFull(size_t row);
    bool isRowEmpty(size_t row);
    size_t clearFullRows();

    /**
     * Clears all nodes between to iterators in the grid.
     * @tparam It Iterator that, on dereference, is a node.
     * @param start Iterator where to start clearing
     * @param end Iterator of where to end clearing
     */
    template<typename It>
    void clear(It start, It end){
        size_t width = std::distance(start, end);
        std::for_each(start, end, [](node& n){ n.object->setSize({0, 0});});
        grid.erase(start, end);
        grid.insert(grid.begin(), width, node());
    }
};


#endif //TETRIS_GRID_H
