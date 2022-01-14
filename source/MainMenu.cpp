// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// MainMenu.cpp, 2022-01-13 - 2022-01-13
// Contains the implementations for the MainMenu-class' functions.
//

#include "MainMenu.h"

/**
 * Draw function for the main menu. Calls its child-menu and logo elements' draw-functions.
 * @param target Target to draw upon.
 * @param states States from sf::Transformable
 */
void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(menu, states);
    target.draw(logo, states);
}
