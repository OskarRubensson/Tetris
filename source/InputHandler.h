// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// InputHandler.h, 2021-12-16 - 2021-12-16
// kortfattat vad filen innehåller
//

#ifndef TETRIS_INPUTHANDLER_H
#define TETRIS_INPUTHANDLER_H


#include <SFML/Window/Event.hpp>

class InputHandler {
public:
    void handleInput(sf::Event& event);
};


#endif //TETRIS_INPUTHANDLER_H
