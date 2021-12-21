// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Window.cpp, 2021-12-15 - 2021-12-15
// kortfattat vad filen innehåller
//

#include "Window.h"

Window::Window(int width, int height, std::string title)
:renderWindow(sf::VideoMode(width, height,32),title),
handler(),
game(std::make_unique<Game>()),
currentState(GAME){
    initialization();
}

void Window::initialization() {
    renderWindow.setFramerateLimit(60);
}

void Window::run(){
    while(renderWindow.isOpen()){
        handleEvent();
        renderWindow.clear(BG_COLOR);

        switch (currentState){
            case GAME       : game->draw(renderWindow); break;
            case MAIN_MENU:
                break;
            case PAUSE:
                break;
        }

        renderWindow.display();
    }
}

void Window::handleEvent() {
    sf::Event event;
    while(renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderWindow.close();
        }
        if (event.type == sf::Event::KeyReleased){
            handleInput(event);
        }
    }
}

void Window::handleInput(sf::Event){
    switch (currentState){
        case GAME:
            break;
        case MAIN_MENU  :
            break;
        case PAUSE      :
            break;
    }
}

State Window::getState() const{
    return currentState;
}

void Window::setState(State newState){
    currentState = newState;
}