// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Game.cpp, 2021-12-15 - 2021-12-15
// kortfattat vad filen innehåller
//

#include "Game.h"

Game::Game(int width, int height, std::string title):window(sf::VideoMode(width, height,32),title){

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }

            window.clear(sf::Color::Black);
            // window.draw(text);
            window.display();
        }
    }
}