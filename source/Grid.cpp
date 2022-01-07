// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Grid.cpp, 2021-12-20 - 2021-12-20
// kortfattat vad filen innehåller
//

#include "Grid.h"
#include <iterator>
#include <cmath>

Grid::Grid(size_t rows, size_t columns):
grid(rows * columns),
WIDTH(columns){
}


void Grid::remove(Shape& shape){
    node& n = *std::find_if(grid.begin(), grid.end(), [&](node& n_ptr) { return n_ptr.shape == &shape; });

    auto nPos = get(n);

    if (nPos.x == -1)
        return;

    size_t width = shape.getSquares().size();
    size_t height = shape.getSquares().at(0).size();
    auto topLeft = shape.getRelativeCenterPosition(n.object) - sf::Vector2<int>(width / 2, height /  2);
    auto maxIndex = width * height;

    // Put nullptr to the shapes previous nodes
    // A rotation should never fail, therefore we can safely remove it from its previous position
    for(size_t index = 0; index < maxIndex; index++){
        auto currPos = topLeft + indexToVector(index, width);
        node* currPosNode = get(nPos + currPos);

        if (currPosNode == nullptr || currPosNode->shape == nullptr || currPosNode->shape != &shape)
            continue;

        currPosNode->shape = nullptr;
        currPosNode->object = nullptr;
    }
}

bool Grid::insert(Shape& shape, sf::Vector2<int> position) {
    auto& squares = shape.getSquares();
    std::vector<std::pair<size_t, sf::RectangleShape*> > insertion_points;

    for (int rowID = 0; rowID < squares.size(); rowID++){
        for (int colID = 0; colID < squares.at(rowID).size(); colID++){
            auto& square = squares.at(rowID).at(colID);

            // Dont insert "empty" squares
            if (square.getSize().x <= 0 || square.getSize().y <= 0){
                continue;
            }

            sf::Vector2<int> squarePos = {position.x + colID,
                                          position.y + rowID};

            int insertion_point = vectorToIndex(squarePos);

            // Check bounds
            if (squarePos.x < 0 || squarePos.x > width() ||
                squarePos.y < 0 || squarePos.y > height() ||
                insertion_point > grid.size())
                return false;

            // Check is node at insertion_point is not empty
            if (grid.at(insertion_point).shape != nullptr)
                return false;

            insertion_points.emplace_back(insertion_point, &square);
        }
    }
    for (auto pair: insertion_points){
        grid.at(pair.first).object = pair.second;
        grid.at(pair.first).shape = &shape;
    }

    shape.move(position);
    return true;
}

bool Grid::move(node* n, sf::Vector2<int> direction) {
    auto position = get(*n);
    // Error checking
    if (position.x < 0 || position.y < 0)
        return false;

    auto& shape_ptr = n->shape;

    if (shape_ptr == nullptr)
        return false;

    auto newPosCenter = position + shape_ptr->getRelativeCenterPosition(n->object);

    // Collision detection
    // Create a vector of pairs that indicates "The node at this position should go here"
    std::vector< std::pair<size_t, size_t> > from_to;
    for(int rowIndex = (int)shape_ptr->getSquares().size() - 1; rowIndex >= 0; rowIndex--){
        for(int colIndex = (int)shape_ptr->getSquares().at(rowIndex).size() - 1; colIndex >= 0; colIndex--){
            auto square = shape_ptr->getSquares().at(rowIndex).at(colIndex);
            if (square.getSize().x <= 0 || square.getSize().y <= 0){
                continue;
            }

            size_t square_index = vectorToIndex(newPosCenter +
                    sf::Vector2<int>(colIndex - (int)round(shape_ptr->getSquares().size() / 2),
                                     rowIndex - (int)round(shape_ptr->getSquares().at(rowIndex).size() / 2)));

            auto from = grid.at(square_index);
            size_t toIndex = square_index + vectorToIndex(direction);

                // Keeping shape in the play-area
            if (toIndex >= grid.size() || // Bottom border
                (direction.x == 1 && toIndex % WIDTH == 0) || // Right border
                    (direction.x == -1 && (toIndex + 1) % WIDTH == 0)) // Left border
                return false;

            auto to = grid.at(toIndex);

            if (from.shape == nullptr || (to.shape != nullptr && to.shape != shape_ptr)){
                return false;
            }

            from_to.push_back(std::make_pair<>(square_index, toIndex));
        }
    }
    shape_ptr->move(direction);

    // Under normal iteration we start swapping at bottom-right and work row-by-row right-to-left
    // If x == -1 we need to go left-to-right
    if (direction.x == -1)
        swapShapes(from_to.rbegin(), from_to.rend());
    else
        swapShapes(from_to.begin(), from_to.end());

    return true;
}

bool Grid::move(Shape& n, sf::Vector2<int> direction) {
    auto found_node = std::find_if(grid.begin(), grid.end(), [&](node& n_ptr) { return n_ptr.shape == &n; });

    if (found_node == grid.end())
        return false;
    return move(&*found_node, direction);
}

bool Grid::rotate(Shape &shape, bool clockwise) {
    node& n = *std::find_if(grid.begin(), grid.end(), [&](node& n_ptr) { return n_ptr.shape == &shape; });
    auto nPos = get(n);

    // No node found
    if (nPos.x == -1 || nPos.y == -1)
        return false;

    remove(shape);                        // A rotation should never fail, we can therefore safely remove it
    shape.rotate(clockwise);                 // Rotates all squares in the shape
    shape.resetProperties();                 // To reset position since "insert" will set each rectangle's pos later

    size_t width = shape.getSquares().size();
    size_t height = shape.getSquares().at(0).size();
    auto center = nPos + shape.getRelativeCenterPosition(n.object);
    auto topLeft = center - sf::Vector2<int>(width / 2, height /  2);
    auto insertionPos = topLeft;
    while(!insert(shape, insertionPos)){ // Try inserting the rotated shape
        insertionPos.y -= 1;                // Move upwards until rotation is successful

        // If insertion fails to succeed
        // Just insert it at its previous position again
        if (insertionPos.y < 0){
            insertionPos.y = topLeft.y;
            insertionPos.x += (center.x <= width / 2 ? 1 : -1);
        }
        // Check if we need to move it in X in order for the rotation to succeed
    }

    return true;
}

bool Grid::isRowEmpty(size_t row){
    int col = 0;
    while(col < width()){
        if (get({col, (int)row})->shape != nullptr)
            return false;
        col++;
    }
    return true;
}

bool Grid::isRowFull(size_t row){
    int col = 0;
    while(col < width()){
        if (get({col, (int)row})->shape == nullptr)
            break;
        col++;
    }

    // Full row found
    if (col >= width()){
        return true;
    }
    return false;
}

size_t Grid::clearFullRows(){
    std::vector<size_t> rows;

    // Iterate through each row from bottom->up
    for(int row = height() - 1; row >= 0; row--){
        if (isRowFull(row))
            rows.push_back(row * width());
    }

    // std::for_each(rows.begin(), rows.end(), [&](auto rowID){ clear(rowID); });
    if (!rows.empty()){
        // Clear each row that was full
        clear(grid.begin() + rows.back(), grid.begin() + rows.front() + width());

        // Move each object above the cleared rows downwards for the amount of rows that was cleared
        std::for_each(grid.begin(), grid.begin() + rows.front() + width(), [&](node& n){
            if (n.object != nullptr){
                n.object->move({0, rows.size() * SQUARE_SIZE});
            }
        });
    }

    return rows.size();
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

size_t Grid::width() {
    return WIDTH;
}

size_t Grid::height() {
    return grid.size() / WIDTH;
}

size_t Grid::width() const {
    return WIDTH;
}

size_t Grid::height() const{
    return grid.size() / WIDTH;
}