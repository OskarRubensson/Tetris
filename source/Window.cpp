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
    view.setSize(game->height() + 100, game->height() + 100);
    view.setCenter({static_cast<float>(renderWindow.getSize().x - 100) / 2, static_cast<float>(renderWindow.getSize().y) / 2});
    renderWindow.setView(view);
}

void Window::run(){
    while(renderWindow.isOpen()){
        handleEvent();
        renderWindow.clear(BG_COLOR);

        switch (currentState){
            case GAME       :
                game->update();
                renderWindow.draw(*game);
                break;
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
            game->startMove(dir);
        else if (event.type == sf::Event::KeyReleased)
            game->stopMove();
    };

    switch (currentState){
        case GAME:
            if (event.key.code == sf::Keyboard::Left) // LEFT
                moveFunc(LEFT);
            if (event.key.code == sf::Keyboard::Right) // RIGHT
                moveFunc(RIGHT);
            if (event.key.code == sf::Keyboard::Up) // UP
                moveFunc(UP);
            if (event.key.code == sf::Keyboard::Down) // DOWN
                moveFunc(DOWN);
            if (event.key.code == sf::Keyboard::Z && event.type == sf::Event::KeyReleased) // Z
                game->rotate(false);
            if (event.key.code == sf::Keyboard::X && event.type == sf::Event::KeyReleased) // X
                game->rotate(true);
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