// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Window.h, 2021-12-15 - 2021-12-15
// kortfattat vad filen innehåller
//

#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H


#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"


enum State {MAIN_MENU, GAME};

/**
 * The window that everything is displayed within. Manages the interaction between user and game
 */
class Window {
private:
    sf::RenderWindow renderWindow;
    std::unique_ptr<Game> game;
    std::unique_ptr<Menu> mainMenu;
    const sf::Color BG_COLOR = sf::Color::Black;
    State currentState = MAIN_MENU;

    void handleEvent();
    void handleInput(sf::Event& event);
    void handleMainMenuInput(sf::Event& event);
    void handleGameInput(sf::Event& event);
public:
    Window(int width, int height, const std::string& title);
    void initialization();
    void run();


    //Getters
    State getState() const;

    //Setters
    void setState(State newState);
};


#endif //TETRIS_WINDOW_H
