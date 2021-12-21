// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Window.h, 2021-12-15 - 2021-12-15
// kortfattat vad filen innehåller
//

#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H


#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Game.h"


enum State {MAIN_MENU, PAUSE, GAME};

class Window {
private:
    sf::RenderWindow renderWindow;
    InputHandler handler;
    std::unique_ptr<Game> game;
    const sf::Color BG_COLOR = sf::Color::Black;
    State currentState = MAIN_MENU;

    void handleEvent();
    void handleInput(sf::Event);
public:
    Window(int width, int height, std::string title);
    void initialization();
    void run();

    //Getters
    State getState() const;

    //Setters
    void setState(State newState);
};


#endif //TETRIS_WINDOW_H
