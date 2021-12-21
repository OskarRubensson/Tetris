#include <SFML/Graphics.hpp>
#include "source/Window.h"

int main() {

    Window game(500, 500, "Tetris");
    game.run();
    return 0;
}