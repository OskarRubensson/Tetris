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
DEFAULT_X(columns / 2),
DEFAULT_Y(3){
}

void Grid::insert(Shape& shape, sf::Vector2<int> position) {
    auto& squares = shape.getSquares();
    int rowID = -1;
    std::for_each(squares.begin(), squares.end(), [&](auto& row){
        int colID = -1;
        std::for_each(row.begin(), row.end(), [&](auto& square){
            if (square.getSize().x <= 0 || square.getSize().y <= 0){
                colID++;
                return;
            }

            sf::Vector2<int> squarePos = {position.x + colID, position.y + rowID};

            int insertion_point = vectorToIndex(squarePos);
            if (squarePos.x < 0 || squarePos.x > WIDTH ||
                squarePos.y < 0 || squarePos.y > (int)(grid.size() / WIDTH))
                return;

            grid.at(insertion_point).object = &square;
            grid.at(insertion_point).shape = &shape;

            colID++;
        });
        rowID++;
    });
    shape.move(position);
}

bool Grid::move(sf::Vector2<int> position, sf::Vector2<int> direction) {
    // Error checking
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
    // Move each entry in grid associated with this shape to its new position
    std::vector< std::pair<size_t, size_t> > from_to;
    for(int rowIndex = shape_ptr->getSquares().size() - 1; rowIndex >= 0; rowIndex--){
        for(int colIndex = shape_ptr->getSquares().at(rowIndex).size() - 1; colIndex >= 0; colIndex--){
            auto square = shape_ptr->getSquares().at(rowIndex).at(colIndex);
            if (square.getSize().x <= 0 || square.getSize().y <= 0){
                continue;
            }

            size_t square_index = vectorToIndex(newPosCenter + sf::Vector2<int>(colIndex - 1, rowIndex - 1));

            auto from = grid.at(square_index);
            size_t toIndex = square_index + vectorToIndex(direction);

            if (toIndex >= grid.size())
                return false;

            auto to = grid.at(toIndex);
            //OK, so thing is - We don't move every node that we should move somehow
            if (from.shape == nullptr || (to.shape != nullptr && to.shape != shape_ptr)){
                return false;
            }

            from_to.push_back(std::make_pair<>(square_index, toIndex));
        }
    }
    shape_ptr->move(direction);

    for(auto it : from_to){
        std::swap(grid.at(it.first), grid.at(it.second));
    }

    return true;
}

bool Grid::move(Shape& n, sf::Vector2<int> direction) {
    bool moved = false;
    /*
    std::for_each(grid.begin(), grid.end(), [&](node& n_ptr){
        if (n_ptr.shape == &n && !moved){
            moved = move(get(n_ptr), direction);
            return false; //Break iteration
        }
        return true; // Continue
    });*/

    auto found_node = std::find_if(grid.begin(), grid.end(), [&](node& n_ptr) { return n_ptr.shape == &n; });
    if (found_node == grid.end())
        return false;
    return move(get(*found_node), direction);
}

node* Grid::get(sf::Vector2<int> position) {
    size_t index = vectorToIndex(position);
    if (grid.size() <= index)
        return nullptr;
    return &grid.at(index);
}

sf::Vector2<int> Grid::get(node& n_ptr) {
    auto found_it = std::find_if(grid.begin(), grid.end(), [&](node& n){ return &n_ptr == &n; });

    // Not found
    if (found_it == grid.end())
        return {-1, -1};

    size_t index = std::distance(grid.begin(), found_it);
    return indexToVector(index);
}