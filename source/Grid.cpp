// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Grid.cpp, 2021-12-20 - 2021-12-20
// kortfattat vad filen innehåller
//

#include "Grid.h"
#include <iterator>

Grid::Grid(size_t rows, size_t columns):
grid(rows * rows + columns),
WIDTH(rows),
DEFAULT_X(rows / 2),
DEFAULT_Y(0){
}

void Grid::insert(Shape& shape, sf::Vector2<float> position) {

    node n = {shape, shape.getSquares()->at(1).at(1)};
    grid[position.x * WIDTH + position.y] = std::make_unique<node>(n);
}

bool Grid::move(sf::Vector2<int> position, sf::Vector2<int> direction) {
    auto n_ptr = get(position);

    if (n_ptr == nullptr)
        return false;

    auto& n = *n_ptr;
    Shape* shape = n->shape;

    if (shape == nullptr)
        return false;

    auto squares = shape->getBottomSquaresRow();
    auto center = position + shape->getRelativeCenterPosition(*n->object);

    // Collision detection
    size_t colIndex = 0;
    for(auto col: squares){
        if (col != -1){
            sf::Vector2<int> positionToCheck = sf::Vector2<int>{static_cast<int>(col + center.x + direction.x), static_cast<int>(col + center.y + direction.y)};
            if (get(positionToCheck) != nullptr)
                return false;
        }
    }

    shape->move(direction);
    auto from = grid.begin() + position.y * WIDTH + position.x;
    auto to = grid.begin() + (position.y + direction.y) * WIDTH + (position.x + direction.x);
    std::iter_swap(from, to);
    return true;
}

bool Grid::move(Shape& n, sf::Vector2<int> direction) {
    std::for_each(grid.begin(), grid.end(), [&](std::unique_ptr<node>& n_ptr){
        if (n_ptr == nullptr || n_ptr->shape != &n)
            return;
        move(get(n_ptr), direction);
    });
}

std::unique_ptr<node>* Grid::get(sf::Vector2<int> position) {
    if (grid.size() <= position.y * WIDTH + position.x)
        return nullptr;
    return &grid.at(position.y * WIDTH + position.x);
}

sf::Vector2<int> Grid::get(std::unique_ptr<node>& n_ptr) {
    auto found_it = std::find(grid.begin(), grid.end(), *n_ptr);

    // Not found
    if (found_it == grid.end())
        return {-1, -1};

    size_t index = std::distance(grid.begin(), grid.end());
    size_t x = index % WIDTH;
    size_t y = (index - x) / WIDTH;
    return {(int)x, (int)y};
}