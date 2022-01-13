#include <SFML/Graphics.hpp>
#include "source/Window.h"

int main() {
    Window game(40 * SQUARE_SIZE, 60 * SQUARE_SIZE, "Tetris");
    game.run();
    return 0;
}