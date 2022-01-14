// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Button.cpp, 2022-01-10 - 2022-01-13
// Contains the implementations of the Button-class' functions.
//

#include "Button.h"

/**
 * Parametrized constructor - Makes a button with a given text
 * @param textString The text to have on the button
 */
Button::Button(std::string textString) {
    text.setString(textString);
    if (font.loadFromFile("../resources/fonts/Pacifico.ttf")) {
        text.setFont(font);
        text.setCharacterSize(70);
        text.setFillColor(sf::Color::White);
    }
}

/**
 * Draws the button onto the target.
 * @param target The target to draw on
 * @param states The states received by parent element.
 */
void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(text, states);
}
