// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Grid.cpp, 2021-12-20 - 2021-12-20
// kortfattat vad filen innehåller
//

#include "Grid.h"
#include <iterator>

Grid::Grid(size_t rows, size_t columns):
grid(rows * columns),
WIDTH(columns),
DEFAULT_X(rows / 2),
DEFAULT_Y(0){
}

void Grid::insert(Shape& shape, sf::Vector2<float> position) {
    grid.at(position.y * WIDTH + position.x).object = &shape.getSquares().at(1).at(1);
    grid.at(position.y * WIDTH + position.x).shape = &shape;
    shape.move({(int)position.x, (int)position.y});
}

bool Grid::move(sf::Vector2<int> position, sf::Vector2<int> direction) {
    if (position.x < 0 || position.y < 0)
        return false;
    auto* n = get(position);

    if (n == nullptr)
        return false;

    auto& shape_ptr = n->shape;

    if (shape_ptr == nullptr)
        return false;

    auto squares = shape_ptr->getBottomSquaresRow();
    auto newPosCenter = position + shape_ptr->getRelativeCenterPosition(*n->object);

    // Collision detection
    int colIndex = -1;
    for(auto col: squares){
        if (col != -1){
            sf::Vector2<int> positionToCheck = sf::Vector2<int>{static_cast<int>(newPosCenter.x + colIndex + direction.x), static_cast<int>(newPosCenter.y + direction.y + (col - 2))};
            node* obj_at_pos = get(positionToCheck);
            if (obj_at_pos != nullptr && obj_at_pos->shape != nullptr && obj_at_pos->shape != shape_ptr)
                return false;
        }
        colIndex++;
    }
    auto from = grid.begin() + position.y * WIDTH + position.x;
    auto to = grid.begin() + (position.y + direction.y) * WIDTH + (position.x + direction.x);

    if (to >= grid.end())
        return false;

    shape_ptr->move(direction);
    std::iter_swap(from, to);
    return true;
}

bool Grid::move(Shape& n, sf::Vector2<int> direction) {
    bool moved = false;
    std::for_each(grid.begin(), grid.end(), [&](node& n_ptr){
        if (n_ptr.shape == &n){
            moved = move(get(n_ptr), direction);
            return false; //Break iteration
        }
        return true; // Continue
    });
    return moved;
}

node* Grid::get(sf::Vector2<int> position) {
    if (grid.size() <= position.y * WIDTH + position.x)
        return nullptr;
    return &grid.at(position.y * WIDTH + position.x);
}

sf::Vector2<int> Grid::get(node& n_ptr) {
    auto found_it = std::find_if(grid.begin(), grid.end(), [&](node& n){ return &n_ptr == &n; });

    // Not found
    if (found_it == grid.end())
        return {-1, -1};

    size_t index = std::distance(grid.begin(), found_it);
    size_t x = index % WIDTH;
    size_t y = index / WIDTH;
    return {(int)x, (int)y};
}