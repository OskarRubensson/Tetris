// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Window.cpp, 2021-12-15 - 2021-12-15
// kortfattat vad filen innehåller
//

#include "Window.h"
#include <iostream>

Window::Window(int width, int height, std::string title)
:renderWindow(sf::VideoMode(width, height),title),
handler(),
game(std::make_unique<Game>()),
currentState(GAME){
    initialization();
}

void Window::initialization() {
    renderWindow.setFramerateLimit(60);
    sf::View view{};
    view.setCenter({static_cast<float>(renderWindow.getSize().x / 2), static_cast<float>(renderWindow.getSize().y / 2)});
    renderWindow.setView(view);
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
    sf::Event event{};
    while(renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderWindow.close();
        }
        if (event.type == sf::Event::KeyPressed ||
            event.type == sf::Event::KeyReleased){
            handleInput(event);
        }
    }
}

void Window::handleInput(sf::Event event){
    auto moveFunc = [&](direction dir){
        if (event.type == sf::Event::KeyPressed)
            game->holdMove(dir);
        else if (event.type == sf::Event::KeyReleased)
            game->stopMove();
    };

    switch (currentState){
        case GAME:
            // Do on keyPressed, start clock with high tickrate, stop when keyRelease is called
            if (event.key.code == 71) // LEFT
                moveFunc(LEFT);
            if (event.key.code == 72) // RIGHT
                moveFunc(RIGHT);
            if (event.key.code == 73) // UP
                moveFunc(UP);
            if (event.key.code == 74) // DOWN
                moveFunc(DOWN);
            break;

        case MAIN_MENU:
            break;
        case PAUSE:
            break;
    }
}

State Window::getState() const{
    return currentState;
}

void Window::setState(State newState){
    currentState = newState;
}