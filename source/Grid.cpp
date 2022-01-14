// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Grid.cpp, 2021-12-20 - 2022-01-13
// Contains the implementations of the Grid-class' functions.
//

#include "Grid.h"
#include <iterator>
#include <cmath>

/**
 * Parametrized constructor. Creates a tetris-grid with a given rows- and columns-count.
 * @param rows The amount of rows in the grid.
 * @param columns The amount of columns in the grid.
 */
Grid::Grid(size_t rows, size_t columns):
grid(rows * columns),
WIDTH(columns){
    // Initialize gridLines with line-shapes
    float lineWidth = 1;
    sf::Color lineColor(255, 255, 255, 100);
    sf::RectangleShape verticalLine(sf::Vector2<float>(lineWidth, height() * SQUARE_SIZE));
    sf::RectangleShape horizontalLine(sf::Vector2<float>(width() * SQUARE_SIZE, lineWidth));
    verticalLine.setFillColor(lineColor);
    horizontalLine.setFillColor(lineColor);
    for(int i = 0; i < rows; i++){
        horizontalLine.setPosition(-lineWidth / 2, i * SQUARE_SIZE - (lineWidth / 2));
        gridLines.push_back(horizontalLine);
    }
    for(int i = 0; i < columns; i++){
        verticalLine.setPosition(i * SQUARE_SIZE - (lineWidth / 2), -lineWidth / 2);
        gridLines.push_back(verticalLine);
    }
}

/**
 * Draws the grid-lines into the game.
 * @param target Target to draw upon.
 * @param states States gotten from parent.
 */
void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for(auto& line: gridLines)
        target.draw(line, states);

}

/**
 * Removes a given shape from the grid, i.e. clears all nodes that includes the shape.
 * @param shape A reference to the shape that should be removed.
 */
void Grid::remove(Shape& shape){
    // Find a node with this shape
    node& n = *std::find_if(grid.begin(), grid.end(), [&](node& n_ptr) { return n_ptr.shape == &shape; });
    auto nPos = get(n);
    if (nPos.x == -1)
        return;

    // Information about the shape and it's position
    size_t width = shape.getSquares().size();
    size_t height = shape.getSquares().at(0).size();
    // The top-left objects position in the grid.
    auto topLeft = shape.getRelativeCenterPosition(n.object) - sf::Vector2<int>(width / 2, height /  2);
    auto maxIndex = width * height;

    // Put nullptr to the shapes previous nodes
    // With this we only look at the nodes where the shape could possibly be instead of looking at the entire grid.
    for(size_t index = 0; index < maxIndex; index++){
        auto currPos = topLeft + indexToVector(index, width);
        node* currPosNode = get(nPos + currPos);

        // To prevent removal of any other shape.
        if (currPosNode == nullptr || currPosNode->shape == nullptr || currPosNode->shape != &shape)
            continue;

        // Clear shape.
        currPosNode->shape = nullptr;
        currPosNode->object = nullptr;
    }
}

/**
 * Try inserting a shape at given position in the grid.
 * @param shape The shape to be inserted.
 * @param position The top-left position of the insertion
 * @return Boolean based on if the insertion was successful or not.
 */
bool Grid::insert(Shape& shape, sf::Vector2<int> position) {
    auto& squares = shape.getSquares();
    std::vector<std::pair<size_t, sf::RectangleShape*> > insertion_points;

    // Iterate each square that the shape includes
    for (int rowID = 0; rowID < squares.size(); rowID++){
        for (int colID = 0; colID < squares.at(rowID).size(); colID++){
            auto& square = squares.at(rowID).at(colID);

            // Dont insert "empty" squares
            if (square.getSize().x <= 0 || square.getSize().y <= 0){
                continue;
            }

            // Position for this square
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
    // All checks succeeded and the insertion can be made
    for (auto pair: insertion_points){
        grid.at(pair.first).object = pair.second;
        grid.at(pair.first).shape = &shape;
    }

    // For setting the visual position on the screen of the shape.
    shape.move(position);
    return true;
}

/**
 * Try moving a shape in a set direction.
 * @param s The shape to move.
 * @param direction sf::Vector2 containing the x and y that the shape should be moved with-
 * @return Boolean based on if the move was successful or not.
 */
bool Grid::move(Shape& s, sf::Vector2<int> direction) {
    auto n = std::find_if(grid.begin(), grid.end(), [&](node& n_ptr) { return n_ptr.shape == &s; });

    if (n == grid.end())
        return false;

    sf::Vector2<int> position;

    try{
        position = get(*n);
    } catch(const std::out_of_range& err){
        return false;
    }

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
    // If x == -1 we need to go left-to-right since we are doing a std::swap.
    if (direction.x == -1)
        swapShapes(from_to.rbegin(), from_to.rend());
    else
        swapShapes(from_to.begin(), from_to.end());

    return true;
}

/**
 * Try rotating a shape 90-degrees clockwise or counter-clockwise.
 * @param shape Shape to be rotated
 * @param clockwise Rotates clockwise if true, otherwise counter-clockwise.
 * @return Boolean based of if the rotation was successful.
 */
bool Grid::rotate(Shape &shape, bool clockwise) {
    node& n = *std::find_if(grid.begin(), grid.end(), [&](node& n_ptr) { return n_ptr.shape == &shape; });
    sf::Vector2<int> nPos;

    try{
        nPos = get(n);
    }catch (const std::out_of_range& err){
        return false;
    }

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

/**
 * For a given row-index. Check if it contains no shapes.
 * @param row Index of the row to check
 * @return Boolean based on if the row was empty or not.
 */
bool Grid::isRowEmpty(size_t row){
    int col = 0;
    while(col < width()){
        node* n;
        try{
            n = get({col, (int)row});
        }catch (const std::out_of_range& err) {
            return false;
        }

        if (n->shape != nullptr)
            return false;
        col++;
    }
    return true;
}

/**
 * For a given row-index. Check if each node contains a shape.
 * @param row Index of the row to check.
 * @return Boolean based on if the row was full or not.
 */
bool Grid::isRowFull(size_t row){
    int col = 0;
    while(col < width()){
        node* n;
        try{
            n = get({col, (int)row});
        }catch(const std::out_of_range& e){
            return false;
        }

        if (n->shape == nullptr)
            break;
        col++;
    }

    // Full row found
    if (col >= width()){
        return true;
    }
    return false;
}

/**
 * Checks each row in the grid. If it is full each node is cleared. Also, all nodes above this row is bumped down.
 * @return The amount of rows that was cleared.
 */
size_t Grid::clearFullRows(){
    std::vector<size_t> rows;

    // Iterate through each row from bottom->up
    for(int row = height() - 1; row >= 0; row--){
        if (isRowFull(row))
            rows.push_back(row * width());
    }

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

/**
 * For a given position, return the node-object.
 * @param position The position of the node to get.
 * @throws out_of_range when not found.
 * @return Returns node at the position. Nullptr if position is invalid.
 */
node* Grid::get(sf::Vector2<int> position) {
    size_t index = vectorToIndex(position);
    if (grid.size() <= index)
        throw std::out_of_range("Given index is out of range");
    return &grid.at(index);
}

/**
 * Getter for finding a given nodes position in the grid.
 * @throws out_of_range when not found.
 * @param n_ptr Pointer to the node to find.
 * @return Position of the node. {-1, -1} if it wasn't found.
 */
sf::Vector2<int> Grid::get(node& n_ptr) {
    auto found_it = std::find_if(grid.begin(), grid.end(), [&](node& n){ return &n_ptr == &n; });

    // Not found
    if (found_it == grid.end())
        throw std::out_of_range("Node not in grid");

    size_t index = std::distance(grid.begin(), found_it);
    return indexToVector(index);
}

/**
 * Getter for the width of the grid.
 * @return the grid's width.
 */
size_t Grid::width() {
    return WIDTH;
}

/**
 * Getter for the height of the grid.
 * @return the grid's height.
 */
size_t Grid::height() {
    return grid.size() / WIDTH;
}

/**
 * Getter for the width of the grid.
 * @return the grid's width.
 */
size_t Grid::width() const {
    return WIDTH;
}

/**
 * Getter for the height of the grid.
 * @return the grid's height.
 */
size_t Grid::height() const{
    return grid.size() / WIDTH;
}
