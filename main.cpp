//
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900)
// main.cpp, 2021-12-15 - 2022-01-13
// Main-file containing int main()
//



/**
 * \mainpage
 * Welcome to my Tetris-project's documentation!
 * Hopefully it will not give you a headache.
 */

#include "source/Window.h"

/**
 * Main function that starts a window that is 40 tetris-squares wide, and 60 high. It also starts the game.
 * @return Always 0.
 */
int main() {
    Window game(40 * SQUARE_SIZE, 60 * SQUARE_SIZE, "Tetris");
    game.run();
    return 0;
}