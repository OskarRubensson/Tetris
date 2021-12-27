#include <SFML/Graphics.hpp>
#include "source/Window.h"

int main() {

    Window game(20 * SQUARE_SIZE, 30 * SQUARE_SIZE, "Tetris");
    game.run();
    return 0;
}