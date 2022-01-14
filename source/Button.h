// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Button.h, 2022-01-10 - 2022-01-13
// Contains the declaration of the Button-class.
//

#ifndef TETRIS_BUTTON_H
#define TETRIS_BUTTON_H

#include <SFML/Graphics.hpp>

class Button: public sf::Drawable, public sf::Transformable {
    sf::Text text;
    sf::Font font;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    Button() = delete;
    explicit Button(std::string textString);

    /**
     * Getter for the text-objects height
     * @return Text height
     */
    float getHeight() { return text.getCharacterSize(); }

    /**
     * Getter for the text-objects width
     * @return Text width
     */
    float getWidth() { return text.getLocalBounds().width; }
};


#endif //TETRIS_BUTTON_H
